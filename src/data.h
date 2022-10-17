#pragma once

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <vector>
#include <map>
#include <inttypes.h>

class Bitmap {
 public:
  uint32_t width; // j
  uint32_t height; // i
  std::vector<uint8_t> data;

 public:
  Bitmap() = default;
  Bitmap(uint32_t width, uint32_t height);
  void Set(uint32_t i, uint32_t j, uint8_t val);
  uint8_t Get(uint32_t i, uint32_t j);
 
 public: // Overloaded operators
  Bitmap& operator+=(const Bitmap& rhs);
  friend Bitmap operator+(Bitmap lhs, const Bitmap& rhs);
};

class Data {
 public:
  std::map<char, Bitmap> kernels;
  
 public:
  Data();
};

FT_Face OpenFont(std::string fontPath);
FT_Bitmap GetGlyphBitmap(FT_Face fontFace, char glyph);
