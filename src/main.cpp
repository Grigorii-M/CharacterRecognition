#include <algorithm>
#include <iostream>

#include "OCR.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Application : public olc::PixelGameEngine {
 private:
  const int DRAWING_AREA_X = 8;
  const int DRAWING_AREA_Y = 8;
  const int KERNEL_AREA_X = 40;
  const int KERNEL_AREA_Y = 8;
  const uint8_t DRAWING_AREA_SIDE = 16;
  OCR ocr;
  Bitmap bitmap;

 public:
  Application() : bitmap{16, 16} { sAppName = "Image Recognition"; }

  bool OnUserCreate() override {
    Clear(olc::BLACK);

    std::vector<std::string> fonts = {
        "/usr/share/fonts/TTF/NotoSansMono-Regular-Nerd-Font-Complete.ttf",
        "/usr/share/fonts/TTF/Hack-Regular.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/MuktiNarrow.ttf",
        "/usr/share/fonts/TTF/Inconsolata-Regular.ttf",
        "/usr/share/fonts/adobe-source-code-pro/SourceCodePro-Light.otf",
        "/usr/share/fonts/cantarell/Cantarell-VF.otf",
        // "/usr/share/fonts/noto/NotoSans-Light.ttf",
        // "/usr/share/fonts/gsfonts/NimbusRoman-Regular.otf",
    };

    std::string glyphs =
        "1234567890";  // ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    this->ocr = {glyphs, fonts};

    // Clear(olc::VERY_DARK_BLUE);
    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override {
    DrawRect({DRAWING_AREA_X - 1, DRAWING_AREA_Y - 1},
             {DRAWING_AREA_SIDE + 1, DRAWING_AREA_SIDE + 1}, olc::DARK_BLUE);
    DrawRect({KERNEL_AREA_X - 1, KERNEL_AREA_Y - 1},
             {DRAWING_AREA_SIDE + 1, DRAWING_AREA_SIDE + 1}, olc::DARK_BLUE);
    // DrawStringDecal({32, 32}, "Hello world");

    auto mouse = GetMousePos();
    if (mouse.x >= DRAWING_AREA_X &&
        mouse.x < DRAWING_AREA_X + DRAWING_AREA_SIDE &&
        mouse.y >= DRAWING_AREA_Y &&
        mouse.y < DRAWING_AREA_Y + DRAWING_AREA_SIDE) {
      if (GetMouse(olc::Mouse::LEFT).bHeld) {
        auto x = mouse.x - DRAWING_AREA_X;
        auto y = mouse.y - DRAWING_AREA_Y;
        bitmap.Set(x, y, 255);
        Draw(mouse, olc::WHITE);
      }
    }

    if (GetKey(olc::Key::ESCAPE).bPressed) {
      Clear(olc::BLACK);
      this->bitmap.Clear();
    }

    if (GetKey(olc::Key::ENTER).bPressed) {
      auto res = ocr.Recognize(bitmap);

      char smallest;
      double val = std::numeric_limits<double>::infinity();
      for (auto entry : res) {
        if (entry.second < val) {
          smallest = entry.first;
          val = entry.second;
        }
        std::cout << entry.first << ": " << entry.second << std::endl;
      }
      std::cout << "=========================\n";

      auto bm = ocr.kernels[smallest];
      for (int y = KERNEL_AREA_Y; y < KERNEL_AREA_Y + DRAWING_AREA_SIDE; y++) {
        for (int x = KERNEL_AREA_X; x < KERNEL_AREA_X + DRAWING_AREA_SIDE;
             x++) {
          auto val = bm.Get(x - KERNEL_AREA_X, y - KERNEL_AREA_Y);
          Draw({x, y}, olc::Pixel(val, val, val));
        }
      }
    }

    return true;
  }
};

int main(int argc, char *argv[]) {
  Application app;
  if (app.Construct(64, 32, 10, 10)) {
    app.Start();
  }
  return 0;
}
