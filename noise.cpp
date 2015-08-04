#include "SimpleImage.h"

using namespace std;

int main() {
  // Load image from file
  SimpleImage img("flower.png");

  // Initialize result image
  // SimpleImage result(img.width(), img.height(), RGBColor(0, 0, 0));
  SimpleImage result(img.width(), img.height(), GrayscaleColor(0.5f));

  // Iterate over pixels and set color for result image
  for (int y = 0; y < img.height(); ++y) {
    for (int x = 0; x < img.width(); ++x) {
      RGBColor c = img(x, y);
      GrayscaleColor g(c.r, c.g, c.b);

      result.setG(x, y, g);
    }
  }

  // Save result image to file
  result.save("noiseReduce.png");

  return 0;
}