#include <iostream>

#include "OCR.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Application : public olc::PixelGameEngine {
 private:
  const uint8_t DRAWING_AREA_X = 8;
  const uint8_t DRAWING_AREA_Y = 8;
  const uint8_t DRAWING_AREA_SIDE = 16;
  OCR ocr;
  Bitmap bitmap;

 public:
  Application() : bitmap{16, 16} { sAppName = "Image Recognition"; }

  bool OnUserCreate() override {
    std::vector<std::string> fonts = {
        "/usr/share/fonts/TTF/NotoSansMono-Regular-Nerd-Font-Complete.ttf",
        "/usr/share/fonts/TTF/Hack-Regular.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        // "/usr/share/fonts/TTF/TSCu_Times.ttf",
    };

    std::string glyphs = "0123456789";
    Clear(olc::VERY_DARK_BLUE);
    this->ocr = {glyphs, fonts};

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override {
    DrawRect({DRAWING_AREA_X - 1, DRAWING_AREA_Y - 1},
             {DRAWING_AREA_SIDE + 1, DRAWING_AREA_SIDE + 1});

    auto mouse = GetMousePos();
    if (mouse.x >= DRAWING_AREA_X &&
        mouse.x <= DRAWING_AREA_X + DRAWING_AREA_SIDE &&
        mouse.y >= DRAWING_AREA_Y &&
        mouse.y <= DRAWING_AREA_Y + DRAWING_AREA_SIDE) {
      if (GetMouse(olc::Mouse::LEFT).bHeld) {
        Draw(mouse, olc::GREEN);
        bitmap.Set(mouse.x % 16, mouse.y % 16, 255);
      }
    }

    if (GetKey(olc::Key::ESCAPE).bPressed) {
      Clear(olc::VERY_DARK_BLUE);
      this->bitmap.Clear();
    }

    if (GetKey(olc::Key::ENTER).bPressed) {
      auto res = ocr.Recognize(bitmap);

      for (auto entry : res) {
        std::cout << entry.first << ": " << entry.second << std::endl;
      }
      std::cout << "=========================\n\n";
    }

    return true;
  }
};

int main(int argc, char *argv[]) {
  Application app;
  if (app.Construct(64, 64, 10, 10)) {
    app.Start();
  }
  return 0;
}
