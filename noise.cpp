#include "SimpleImage.h"
#include <vector>
#include <algorithm> 
#include <string>

using namespace std;

static vector<float> windowR; //the window of red values
static vector<float> windowG; //the window of green values
static vector<float> windowB; //the window of blue values

int reduceNoise(SimpleImage& source, SimpleImage& result) {

    // Iterate over pixels and set color for result image
  for (int y = 0; y < source.height(); ++y) {
    for (int x = 0; x < source.width(); ++x) {

      windowR.clear();
      windowG.clear();
      windowB.clear();

      RGBColor c = source(x, y); //current pixel

      //check if we are at the bounds of the image
      if (y - 1 > 0 && y + 1 < source.height()
        && x - 1 > 0 && x + 1 < source.width()) {
        //we'll filter the image in 3x3 windows
        for (int y1 = -1; y1 < 2; ++y1) {
          for (int x1 = -1; x1 < 2; ++x1) {
              //these loops keep our central pixel at the current x,y
            RGBColor tempC = source(x+x1, y+y1);

              //add values to RGB
            windowR.push_back(tempC.r);
            windowG.push_back(tempC.g);
            windowB.push_back(tempC.b);

          }
        }

          /* these represent our current pixel's RGB values 
           * which may be updated depending upon noise
           */
        float r, g, b;

          //sort the RGB vectors to find median pixel values
        sort(windowR.begin(), windowR.end());
        sort(windowG.begin(), windowG.end());
        sort(windowB.begin(), windowB.end());

        if (c.r == windowR[0] || c.r == windowR[8]) {
          /* if our central pixel's red value is the max
           * in the window, we'll replace it with the median red
           */
           r = windowR[4];
        }
        else {
          r = c.r;
        }

        /***** we'll repeat the above process for green and blue ******/
        if (c.g == windowG[0] || c.g == windowG[8]) {
           g = windowG[4];
        }
        else {
          g = c.g;
        }

        if (c.b == windowB[0] || c.b == windowB[8]) {
           b = windowB[4];
        }
        else {
          b = c.b;
        }

        //let's make a new color with our correct RGB values
        RGBColor replacement(r, g, b);
        result.set(x, y, replacement);

      }
      else {
        result.set(x, y, c);
      }
    }
  }

  return 0;
}

int main(int argc, char** argv) {
  // Load image from file
  SimpleImage img(argv[1]);

  //initialize intermediate images
  SimpleImage intermediate1(img.width(), img.height(), RGBColor(0, 0, 0));
  SimpleImage intermediate2(img.width(), img.height(), RGBColor(0, 0, 0));
  SimpleImage intermediate3(img.width(), img.height(), RGBColor(0, 0, 0));
  SimpleImage intermediate4(img.width(), img.height(), RGBColor(0, 0, 0));

  // Initialize result image
  SimpleImage result(img.width(), img.height(), RGBColor(0, 0, 0));

  reduceNoise(img, intermediate1);
  reduceNoise(intermediate1, intermediate2);
  reduceNoise(intermediate2, intermediate3);
  reduceNoise(intermediate3, intermediate4);
  reduceNoise(intermediate4, result);

    // Save result image to file
  result.save("result.png");

  return 0;
}