This repository contains code that reduces "noise" in images. This is a branch repository of a larger photoshop-like program that implements auto color, levels, and contrast, HDR using 3 images and HDR simulation using one image, noise reduction of noisy images, and preset filters.

I integrated a few files to work with in this program that are were not originally developed by me. They include:
SimpleImage.cpp --> contains my additions that marked so
SimpleImage.h --> contains my additions that marked so
stb.cpp
stb_image.h
stb_image_write.h


CURRENT STATE OF PROGRAM:
Converts any image to it's grayscale equivalent at every pixel
