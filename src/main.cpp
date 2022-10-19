#include <iostream>

#include "OCR.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Application : public olc::PixelGameEngine {
 private:
 public:
  Application() { sAppName = "Image Recognition Software"; }

  bool OnUserCreate() override {
    for (int y = 0; y < ScreenHeight(); y++)
      for (int x = 0; x < ScreenWidth(); x++) Draw(x, y, olc::DARK_BLUE);

    std::vector<std::string> fonts = {
        "/usr/share/fonts/TTF/NotoSansMono-Regular-Nerd-Font-Complete.ttf",
        "/usr/share/fonts/TTF/Hack-Regular.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        // "/usr/share/fonts/TTF/TSCu_Times.ttf",
    };

    std::string glyphs = "gjflQmn(";
    OCR ocr(glyphs, fonts);

    int offset = 0;
    for (auto kernel : ocr.kernels) {
      Bitmap bitmap = kernel.second;

      for (int i = 0; i < bitmap.height; i++)
        for (int j = 0; j < bitmap.width; j++) {
          auto value = bitmap.Get(i, j);
          Draw(offset + j, i, olc::Pixel(value, value, value));
        }

      offset += bitmap.width + 1;
    }

    ocr.Recognize({2, 2});

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override {
    auto mouse = GetMousePos();
    // std::cout << mouse.x << "x" << mouse.y << std::endl;
    if (GetMouse(olc::Mouse::LEFT).bHeld) Draw(mouse, olc::GREEN);
    return true;
  }
};

int main(int argc, char *argv[]) {
  Application app;
  if (app.Construct(16 * 10 + 10, 16 * 1, 10, 10)) {
    app.Start();
  }
  return 0;
}
