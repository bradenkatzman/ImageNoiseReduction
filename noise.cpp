#include "SimpleImage.h"

using namespace std;

int main() {
  // Load image from file
  SimpleImage img("colorBarsNoise.bmp");

  // Initialize result image
   SimpleImage result(img.width(), img.height(), RGBColor(0, 0, 0));
  // SimpleImage result(img.width(), img.height(), GrayscaleColor(0.5f));

  // Iterate over pixels and set color for result image
  for (int y = 0; y < img.height(); ++y) {
    for (int x = 0; x < img.width(); ++x) {

      RGBColor c = img(x, y);

 //we're going to check the image in 2x2 rows of pixel
      //these will hold the values of the grayscales in the 2x2 pixel grid
      GrayscaleColor a,b,d,e;
      int counter = 0;
      for (int y1 = 0; y1 < 2; ++y1) {
        for (int x1 = 0; x1 < 2; ++x1) {
          //make sure we're not at the edges
          if (y - 2 >= 0 && y + 2 <= img.height()
            && x - 2 >= 0 && x + 2 <= img.width()) {
            RGBColor tempC = img(x+x1, y+y1);
            GrayscaleColor tempG(tempC.r, tempC.g, tempC.b);
          if(counter == 0) {
            a = tempG;
          }
          else if (counter == 1) { 
            b = tempG;
          }
          else if (counter == 2) {
            d = tempG;
          }
          else {
            e = tempG;
          }
            ++counter;
          }
        }
      }

      //now we want to compare our top left pixel (a)
      //to the other 3 to find out if it is noise
      GrayscaleColor max = a;

      if (b.g > max.g) {
        max = b;
      }
      if (d.g > max.g) {
        max = d;
      }
      if (e.g > max.g) {
        max = e;
      }

      //now we want to compare our top left pixel (a)
      //to the other 3 to find out if it is noise
      GrayscaleColor min = a;

      if (b.g < min.g) {
        min = b;
      }
      if (d.g < min.g) {
        min = d;
      }
      if (e.g < min.g) {
        min = e;
      }

      //now let's check if a's grayscale is the max in this section
      //if it is, we will consider it to be noisy
      if(a.g == max.g || a.g == min.g) {
        RGBColor c2(1.0f, 0.0f, 0.0f);
        result.set(x, y, c2);
      }
      else {
        result.set(x, y, c);
      }

      
    }
  }

  // Save result image to file
  result.save("noiseReduce.png");

  return 0;
}