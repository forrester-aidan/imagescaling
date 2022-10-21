#include "Image.h"

//constructor for the image class
Image::Image(unsigned char* imageData) {
    this->imageData = imageData;
}

//returns the image data
unsigned char* Image::getImageData() {
    return imageData;
};

//returns the pixel data
unsigned char* Image::getPixelData() {
    return imageData + 2;
}

//returns the width of the image object
unsigned char Image::getWidth() {
    return *(imageData);
}

//returns the height of the image object
unsigned char Image::getHeight() {
    return *(imageData + 1);
}

//sets the image data to a newData variable
void Image::setImageData(unsigned char *newData) {
    delete[] this->imageData;
    this->imageData = newData;
}