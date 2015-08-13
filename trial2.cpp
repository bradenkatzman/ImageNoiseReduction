#include "SimpleImage.h"
#include <vector>
#include <algorithm> 

using namespace std;

static vector<float> windowR; //the window of red values
static vector<float> windowG; //the window of green values
static vector<float> windowB; //the window of blue values

int main() {
  // Load image from file
  SimpleImage img("noiseReduceStart.png");

  // Initialize result image
  SimpleImage result(img.width(), img.height(), RGBColor(0, 0, 0));

  bool inWindow = false;

  // Iterate over pixels and set color for result image
  for (int y = 0; y < img.height(); ++y) {
    for (int x = 0; x < img.width(); ++x) {

      windowR.clear();
      windowG.clear();
      windowB.clear();

      RGBColor c = img(x, y); //current pixel

      //check for noise in 3x3 windows of pixels
      for (int y1 = 0; y1 < 3; ++y1) {
        for (int x1 = 0; x1 < 3; ++x1) {

          //make sure our window will remain in the photo dimensions
         if (y - 3 >= 0 && y + 3 <= img.height()
          && x - 3 >= 0 && x + 3 <= img.width()) {

          inWindow = true;

        RGBColor tempC = img(x+x1, y+y1);

        //add values to RGB
        windowR.push_back(tempC.r);
        windowG.push_back(tempC.g);
        windowB.push_back(tempC.b);

      }
      else {
        inWindow = false;
      }
    }
  }

  if(inWindow) {
  	//sort the RGB vectors to find median pixel values
  	sort(windowR.begin(), windowR.end());
  	sort(windowG.begin(), windowG.end());
  	sort(windowB.begin(), windowB.end());

  	RGBColor replacement(windowR[4], windowG[4], windowB[4]);

    result.set(x, y, replacement);
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

  // bilateral filtering