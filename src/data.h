#pragma once

#include <freetype2/ft2build.h>

#include "eigen3/Eigen/Dense"
#include FT_FREETYPE_H
#include <inttypes.h>

#include <map>
#include <string>
#include <vector>

class Bitmap {
 public:
  uint32_t width;   // j
  uint32_t height;  // i
  Eigen::VectorXd data;

 public:
  Bitmap() = default;
  Bitmap(uint32_t width, uint32_t height);
  Bitmap(uint32_t width, uint32_t height, FT_Bitmap glyphBitmap);
  void Set(uint32_t i, uint32_t j, uint8_t val);
  uint8_t Get(uint32_t i, uint32_t j);
  void Clear();

 public:  // Overloaded operators
  Bitmap& operator+=(const Bitmap& rhs);
  friend Bitmap operator+(Bitmap lhs, const Bitmap& rhs);

  Bitmap shift(uint32_t w, uint32_t h);
  void shift_ip(uint32_t w, uint32_t h);
};

FT_Face OpenFont(std::string fontPath);
FT_Bitmap GetGlyphBitmap(FT_Face fontFace, char glyph);
Eigen::MatrixXd ToEigenVector(FT_Bitmap bitmap);
