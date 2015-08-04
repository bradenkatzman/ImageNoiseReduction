#include "SimpleImage.h"

int main() {
  // Load image from file
  SimpleImage img("noisy.png");

  // Initialize result image
  SimpleImage result(img.width(), img.height(), RGBColor(0, 0, 0));

  // Iterate over pixels and set color for result image
  for (int y = 0; y < img.height(); ++y) {
    for (int x = 0; x < img.width(); ++x) {
      RGBColor c = img(x, y);
      result.set(x, y, c);

      // Below is identical in effect to above, simply directly
      // accessing the underlying array of pixels, stored in row-major order
      //result.set(x, y, img.data()[y*img.width()+x]);
    }
  }

  // Save result image to file
  result.save("noiseReduce.png");

  return 0;
}