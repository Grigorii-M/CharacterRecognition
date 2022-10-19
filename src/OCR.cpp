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
      auto mat = Bitmap(16, 16, glyphBitmap).ToEigenVector();
      objects.push_back(mat);
    }

    auto covar = CovarianceMahalanobis(objects, kernels[ch].ToEigenVector());
    output[ch] = covar;
  }

  return output;
}

std::map<char, double> OCR::Recognize(Bitmap bitmap) {
  CalculateEMD(Bitmap(16, 16).ToEigenVector(),
               this->kernels['n'].ToEigenVector(), this->covars['n']);

  return {};
}
