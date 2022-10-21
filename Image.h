class Image {
public:
    unsigned char* imageData;

    Image(unsigned char *imageData);
    unsigned char *getImageData();
    unsigned char *getPixelData();
    unsigned char getWidth();
    unsigned char getHeight();
    void setImageData(unsigned char *newData);
};