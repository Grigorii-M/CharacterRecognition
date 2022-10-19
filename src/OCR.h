#pragma once
#include "calc.h"
#include "data.h"

class OCR {
 public:
  std::map<char, Bitmap> kernels;
  std::map<char, Eigen::MatrixXd> covars;

 private:
  static std::map<char, Bitmap> ComputeKernels(
      std::string glyphs, std::vector<std::string> fontPaths);
  static std::map<char, Eigen::MatrixXd> ComputeCovars(
      std::string glyphs, std::vector<std::string> fontPaths,
      std::map<char, Bitmap> kernels);

 public:
  OCR() = default;
  OCR(std::string glyphs, std::vector<std::string> fontPaths);
  std::map<char, double> Recognize(Bitmap bitmap);

 private:
};
