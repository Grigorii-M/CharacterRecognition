#include "data.h"

#include <iostream>

#include "freetype/freetype.h"
#include "freetype/fttypes.h"

// TODO: handle errors
FT_Face OpenFont(std::string fontPath) {
  FT_Library library;
  FT_Face face;

  FT_Error error = FT_Init_FreeType(&library);
  if (error) {
    std::cerr << "Could not init FreeType\n";
    std::exit(1);
  }

  error = FT_New_Face(library, fontPath.c_str(), 0, &face);

  if (error == FT_Err_Unknown_File_Format) {
    std::cerr << "Font file was opened but could not be read\n";
    std::exit(1);
  } else if (error) {
    std::cerr << "Could not open font file\n";
  }

  error = FT_Set_Pixel_Sizes(face, 16, 0);

  return face;
}

FT_Bitmap GetGlyphBitmap(FT_Face fontFace, char glyph) {
  auto glyph_index = FT_Get_Char_Index(fontFace, glyph);

  FT_Error error = FT_Load_Glyph(fontFace, glyph_index, FT_LOAD_DEFAULT);
  error = FT_Render_Glyph(fontFace->glyph, FT_RENDER_MODE_NORMAL);

  return fontFace->glyph->bitmap;
}

Bitmap::Bitmap(uint32_t width, uint32_t height) : width{width}, height{height} {
  data = Eigen::VectorXd(width * height);
  data.setZero();
}

Bitmap::Bitmap(uint32_t width, uint32_t height, FT_Bitmap glyphBitmap)
    : width{width}, height{height} {
  data = Eigen::VectorXd(width * height);
  for (int y = 0; y < glyphBitmap.rows; y++)
    for (int x = 0; x < glyphBitmap.width; x++) {
      auto value = (uint8_t)glyphBitmap.buffer[y * glyphBitmap.width + x];
      this->Set(x, y, value);
    }
}

uint8_t Bitmap::Get(uint32_t x, uint32_t y) {
  return this->data[y * width + x];
}

void Bitmap::Set(uint32_t x, uint32_t y, int val) {
  if (x < width && y < height) {
    val = val > 255 ? 255 : val < 0 ? 0 : val;
    this->data[y * width + x] = val;
  }
}

void Bitmap::Clear() { data.setZero(); }

Bitmap& Bitmap::operator+=(const Bitmap& rhs) {
  if (this->data.size() != rhs.data.size()) {
    std::cerr << "Cannot add two bitmaps of different sizes\n";
    std::exit(1);
  }

  for (int i = 0; i < this->data.size(); i++) {
    this->data[i] += rhs.data[i];
  }

  return *this;
}

Bitmap operator+(Bitmap lhs, const Bitmap& rhs) {
  lhs += rhs;
  return lhs;
}

Bitmap Bitmap::shift(uint32_t w, uint32_t h) {
  Bitmap new_bm(this->width, this->height);
  // Shift the bitmap by w pixels to the right and h pixels down, wrapping
  // around
  for (uint32_t y = 0; y < this->height; y++) {
    for (uint32_t x = 0; x < this->width; x++) {
      new_bm.Set(x, y,
                 this->Get((x - w) % this->width, (y - h) % this->height));
    }
  }
  return new_bm;
}

void Bitmap::shift_ip(uint32_t w, uint32_t h) {
  // Create a new bitmap that is a shifted copy of this one
  Bitmap new_bm = this->shift(w, h);
  // Copy the new bitmap into this one
  for (uint32_t y = 0; y < this->height; y++) {
    for (uint32_t x = 0; x < this->width; x++) {
      this->Set(x, y, new_bm.Get(x, y));
    }
  }
}
