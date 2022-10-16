#include "data.h"

#include <iostream>

#include "freetype/freetype.h"
#include "freetype/fttypes.h"

Data::Data(std::string fontPath) {
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

  // error = FT_Set_Char_Size(face, 0, 16 * 64, 96, 96);
  error = FT_Set_Pixel_Sizes(face, 16, 0);

  this->library = library;
  this->face = face;
}

FT_Bitmap Data::GetGlyphBitmap(char glyph) {
  auto glyph_index = FT_Get_Char_Index(face, glyph);

  FT_Error error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
  error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

  return face->glyph->bitmap;
}
