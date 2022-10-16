#include <iostream>

#include "data.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Application : public olc::PixelGameEngine {
 private:

 public:
  Application() {
    sAppName = "Image Recognition Software";
  }

  bool OnUserCreate() override {
    std::string glyphs = "1234567890";
    Data font1("/usr/share/fonts/TTF/NotoSansMono-Regular-Nerd-Font-Complete.ttf");

    for (int x = 0; x < 10; x++) {
      int y = 0;
      auto glyph = font1.GetGlyphBitmap(glyphs[x]);
      auto width = glyph.width;

      for (int i = 0; i < glyph.width; i++) {
        for (int j = 0; j < glyph.rows; j++) {
          auto value = glyph.buffer[j * width + i];
          Draw(x * 16 + i, y * 16 + j, olc::Pixel(value, value, value));
        }
      }
    }

    Data font2("/usr/share/fonts/TTF/Hack-Regular.ttf");

    for (int x = 0; x < 10; x++) {
      int y = 1;
      auto glyph = font2.GetGlyphBitmap(glyphs[x]);
      auto width = glyph.width;

      for (int i = 0; i < glyph.width; i++) {
        for (int j = 0; j < glyph.rows; j++) {
          auto value = glyph.buffer[j * width + i];
          Draw(x * 16 + i, y * 16 + j, olc::Pixel(value, value, value));
        }
      }
    }

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override {
    return true;
  }
};

int main(int argc, char *argv[]) {
  Application app;
  if (app.Construct(16 * 10, 32, 20, 20)) {
    app.Start();
  }
  return 0;
}
