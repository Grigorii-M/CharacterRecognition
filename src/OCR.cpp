#include "OCR.h"

#include <iostream>

#include "calc.h"

OCR::OCR(std::string glyphs, std::vector<std::string> fontPaths) {
  this->kernels = ComputeKernels(glyphs, fontPaths);
  this->covars = ComputeCovars(glyphs, fontPaths, this->kernels);
}

std::map<char, Bitmap> OCR::ComputeKernels(std::string glyphs,
                                           std::vector<std::string> fontPaths) {
  std::map<char, Bitmap> kernels;

  for (std::string fontPath : fontPaths) {
    auto fontFace = OpenFont(fontPath);

    for (char ch : glyphs) {
      Bitmap bitmap(16, 16);
      auto glyphBitmap = GetGlyphBitmap(fontFace, ch);

      for (int i = 0; i < glyphBitmap.rows; i++)
        for (int j = 0; j < glyphBitmap.width; j++) {
          // Pre-divede the value by the number of fonts to compute average font
          // by font
          auto value = (uint8_t)glyphBitmap.buffer[i * glyphBitmap.width + j] /
                       fontPaths.size();
          bitmap.Set(i, j, value);
        }

      bitmap.shift_ip((bitmap.width - glyphBitmap.width) / 2, 0);

      if (kernels.contains(ch)) {
        kernels[ch] += bitmap;
      } else {
        kernels[ch] = bitmap;
      }
    }
  }

  return kernels;
}

std::map<char, Eigen::MatrixXd> OCR::ComputeCovars(
    std::string glyphs, std::vector<std::string> fontPaths,
    std::map<char, Bitmap> kernels) {
  std::map<char, Eigen::MatrixXd> output;
  for (char ch : glyphs) {
    std::vector<Eigen::VectorXd> objects;
    for (std::string fontPath : fontPaths) {
      auto fontFace = OpenFont(fontPath);
      auto glyphBitmap = GetGlyphBitmap(fontFace, ch);
      auto mat = Bitmap(16, 16, glyphBitmap);
      objects.push_back(mat.data);
    }

    auto covar = CovarianceMahalanobis(objects, kernels[ch].data);
    output[ch] = covar;
  }

  return output;
}

std::map<char, double> OCR::Recognize(Bitmap bitmap) {
  std::map<char, double> res;

  for (auto entry : this->kernels) {
    auto kernel = entry.second;
    auto covar = this->covars[entry.first];
    auto val = CalculateEMD(bitmap.data, kernel.data, covar);
    res[entry.first] = val;
  }

  return res;
}
