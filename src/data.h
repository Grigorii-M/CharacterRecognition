#pragma once

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <string>

class Data {
 private:
  FT_Library library;
  FT_Face face;

 public:
  Data() = default;
  Data(std::string fontPath);
  FT_Bitmap GetGlyphBitmap(char glyph);
};
