#include "SimpleImage.h"
#include <vector>
#include <algorithm> 

using namespace std;

static vector<GrayscaleColor> windowG; //the window of grayscale colors
static vector<RGBColor> windowC; //the window of RGB colors

int main() {
  // Load image from file
  SimpleImage img("birds.jpg");

  // Initialize result image
  SimpleImage result(img.width(), img.height(), RGBColor(0, 0, 0));

  bool inWindow = false;

  // Iterate over pixels and set color for result image
  for (int y = 0; y < img.height(); ++y) {
    for (int x = 0; x < img.width(); ++x) {

      windowG.clear();
      windowC.clear();

      RGBColor c = img(x, y); //current pixel

      //check for noise in 3x3 windows of pixels
      for (int y1 = 0; y1 < 3; ++y1) {
        for (int x1 = 0; x1 < 3; ++x1) {

          //make sure our window will remain in the photo dimensions
         if (y - 3 >= 0 && y + 3 <= img.height()
          && x - 3 >= 0 && x + 3 <= img.width()) {

          inWindow = true;

        RGBColor tempC = img(x+x1, y+y1);

              //add our temporary RGB color to RGB color vector
        windowC.push_back(tempC);

              //add the temporary RGB color's grayscale value to grayscale vector
        GrayscaleColor tempG(tempC.r, tempC.g, tempC.b);
        windowG.push_back(tempG);
      }
      else {
        inWindow = false;
      }
    }
  }

  if(inWindow) {
    //save central pixel
    GrayscaleColor centralG = windowG[4];
    RGBColor centralC = windowC[4];

    //sort the grayscale vector to find grayscale-max and grayscale-min
    sort(windowG.begin(), windowG.end());

    //sort(windowC.begin(), windowC.end());

    if (windowG[0].g == centralG.g || windowG[8].g == centralG.g) {

      // RGBColor replacement(windowG[4].g, windowG[4].g, windowG[4].g);
      RGBColor replacement(0.5f,0.5f, 0.5f);

      result.set(x, y, replacement);
    }
    else {
      result.set(x, y, c);
    }

  }
}
}
  // Save result image to file
result.save("noiseReduce.png");

return 0;
}


/* median filtering:
  take 3x3 window, compute the median value of R, G, B --> replace central pixel with median color
  */