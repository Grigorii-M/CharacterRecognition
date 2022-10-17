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
    for (int y = 0; y < ScreenHeight(); y++)
      for (int x = 0; x < ScreenWidth(); x++)
        Draw(x, y, olc::DARK_BLUE);

    Data data;

    int offset = 0;
    for (auto kernel : data.kernels) {
      Bitmap bitmap = kernel.second;

      for (int i = 0; i < bitmap.height; i++)
        for (int j = 0; j < bitmap.width; j++) {
          auto value = bitmap.Get(i, j);
          Draw(offset + j, i, olc::Pixel(value, value, value));
        }

      offset += bitmap.width + 1;
    }

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override {
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
