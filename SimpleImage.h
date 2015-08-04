#ifndef _SIMPLEIMAGE_H_
#define _SIMPLEIMAGE_H_

#include <string>
#include <iostream>
#include <assert.h>

using namespace std;


/**
 * A simple RGB color struct with [0,1] floating point values for each color channel
 */
class RGBColor {
 public:
  float r, g, b;

  RGBColor(float red, float green, float blue) :
    r(red),
    g(green),
    b(blue) { }

  RGBColor() :
    r(0),
    g(0),
    b(0) { }

  RGBColor operator+(RGBColor const o) {
    return RGBColor(r + o.r, g + o.g, b + o.b);
  }

  RGBColor operator-(RGBColor const o) {
    return RGBColor(r - o.r, g - o.g, b - o.b);
  }

  RGBColor operator*(float s) {
    return RGBColor(r * s, g * s, b * s);
  }
};

/* THIS STRUCT AUTHORED BY BRADEN KATZMAN
* A grayscale struct that can be used to convert a simple RGB struct
* into its corresponding grayscale value. This uses a luminosity method
* to compute a grayscale. This method averages the values and, "forms a
weighted average to account for human perception.  We're more sensitive to
green than other colors, so green is weighted most heavily. The formula
for luminosity is (0.21 * RED) + (0.72 * GREEN) + (0.07 * B)."
*
* Method adapted from:
* http://www.johndcook.com/blog/2009/08/24/algorithms-convert-color-grayscale/
*/
class GrayscaleColor {
  public:
    float g;

    GrayscaleColor(float red, float green, float blue) {
      g = (0.21f * red) + (0.72f * green) + (0.07f * blue);
    }

    GrayscaleColor(float _g) {
      g = _g;
    }

    GrayscaleColor() {
      g = 0.f;
    }
};

/**
 * An image class, adapted from libST's STImage.
 * The class stores colors in RGB form and can load and write PNG files.
 * Colors are stored as RGB floats with values between 0 and 1.
 *
 * Pixel values for a SimpleImage I can be accessed using I(x,y) and can be set to an RGBColor c through I.set(x, y, c).
 * All functions that operate on pixels clamp their indices to within the range of the image.
 */
class SimpleImage {
 public:
  SimpleImage();
  ~SimpleImage();

  // Constructors
  SimpleImage(const SimpleImage& img);
  SimpleImage(int width, int height, const GrayscaleColor& g);
  SimpleImage(int width, int height, const RGBColor& bg);
  SimpleImage(int width, int height, unsigned char* data);
  SimpleImage(const std::string& filename);

  // Initialize SimpleImage to given width and height
  void initialize(int width, int height);

  // Return by reference pixel value at (x, y)
  RGBColor& operator() (int x, int y) {
    x = (x >= 0) ? ((x < _width) ? x : _width - 1) : 0;
    y = (y >= 0) ? ((y < _height) ? y : _height - 1) : 0;
    return _data[_width * y + x];
  }

  // Return pixel value at (x, y)
  RGBColor operator() (int x, int y) const {
    x = (x >= 0) ? ((x < _width) ? x : _width - 1) : 0;
    y = (y >= 0) ? ((y < _height) ? y : _height - 1) : 0;
    return _data[_width * y + x];
  }

  // Set value of pixel at (x, y) to c. NOTE: clamps x and y to be within image.
  void set(int x, int y, RGBColor c) {
    x = (x >= 0) ? ((x < _width) ? x : _width - 1) : 0;
    y = (y >= 0) ? ((y < _height) ? y : _height - 1) : 0;
    _data[_width * y + x] = c;
  }

  // Set value of pixel at (x, y) to grayscale color. NOTE: clamps x and y to be within image.
  void setG(int x, int y, GrayscaleColor g) {
    x = (x >= 0) ? ((x < _width) ? x : _width - 1) : 0;
    y = (y >= 0) ? ((y < _height) ? y : _height - 1) : 0;
    _dataG[_width * y + x] = g;
  }

  // Load image from filename
  void load(const std::string& filename);
  
  // Save image to filename
  bool save(const std::string& filename);

  // Return whether this SimpleImage is empty
  bool empty() const;

  // Return the width of this SimpleImage in pixels
  int width() const {
    return _width;
  }

  // Return the height of this SimpleImage in pixels
  int height() const {
    return _height;
  }

  // Return pointer to color data array
  RGBColor* data() const {
    return _data;
  }

  /* AUTHORED BY BRADEN KATZMAN
   * Return pointer to grayscale data array
   */
  GrayscaleColor* dataG() const {
    return _dataG;
  }

 private:
  RGBColor* _data;
  GrayscaleColor* _dataG;
  int _width;
  int _height;

  bool inBounds(int x, int y) const { return x >= 0 && x < _width && y >= 0 && y < _height; }
};

#endif  // _SIMPLEIMAGE_H_
