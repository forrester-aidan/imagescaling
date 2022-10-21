#include <iostream>
#include "ConsoleGfx.h"
#include "Image.h"
#include <math.h>

using namespace std;


unsigned char *scaledImage(unsigned char *imageData, int orders);  // Declares a scaledImage function
int main() {  // Main method; runs the program


    //initializes a pointer to a new instance of ConsoleGfx
    ConsoleGfx* console = ConsoleGfx::getInstance();
    int option;
    Image img = Image(nullptr);

    cout << "Welcome to the Image Scaler!\n";

    //displays the rainbow image
    cout << "\nDisplaying Spectrum Image:\n";
    console->displayImage(console->testRainbow);


    int x = 0;
    while (x < 1){

        //displays the menu for the Image Scaling program.
        cout << "\nScaler Menu\n-----------\n0. Exit\n1. Load File\n2. Load Test Image\n3. Display Image\n4. Enlarge Image"
                "\n5. Shrink Image\n6. Show Image Properties\n";
        cout << "\nSelect a Menu Option: ";
        cin >> option;

        // Exits the program
        if (option == 0) {
            x++;
        } else if (option == 1) {  // Loads a file into the program
            string file;
            cout << "Enter name of file to load: ";
            cin >> file;
            if(console->loadFile(file) == nullptr) {
                cout << "Error: could not load file.";
                continue;
            }
            img.setImageData(console->loadFile(file));
        } else if (option == 2) { // Loads the test image data
            cout << "Test image data loaded.";
            img.setImageData(console->testImage);
        } else if (option == 3) { // Displays the loaded image
            if (img.getImageData() == nullptr) {
                cout << "Error: no image loaded.";
            } else {
                console->displayImage(img.getImageData());
            }
        } else if (option == 4) { // Scaling an image to be bigger
            int input;

            cout << "Enter orders of magnitude for enlargement: ";
            cin >> input;

            img.setImageData(scaledImage(img.getImageData(), input));
        } else if (option == 5) { // Scaling an image to be smaller
            int input;

            cout << "Enter orders of magnitude for reduction: ";
            cin >> input;

            img.setImageData(scaledImage(img.getImageData(), -input));
        } else if (option == 6) { // Returns the image dimensions
            cout << "Image Dimensions: (" << (int)img.getWidth() << ", " << (int)img.getHeight() << ")";
        }
    }
    delete[] img.getImageData();
    return 0;
}


unsigned char *scaledImage(unsigned char *imageData, int orders) { // Function used to scale image up or down
    float scalingFactor = pow(2, orders);

    int originalWidth = *imageData;
    int originalHeight = *(imageData + 1);


    int newWidth = scalingFactor * originalWidth;
    int newHeight = scalingFactor * originalHeight;

    //handles the case if the new width is less than 1 or if the new height is less than 1
    if(newWidth < 1)
        newWidth = 1;
    if(newHeight < 1)
        newHeight = 1;

    int newDimension = max(newWidth, newHeight);

    //handles the case if one of the new dimensions is greater than 256
    if(newDimension > 256) {
        scalingFactor = pow(2, (int) (log(256 / newDimension) / log(2)));
        newWidth = scalingFactor * originalWidth;
        newHeight = scalingFactor * originalHeight;
    }

    // New image data
    unsigned char *scaledImageData = new unsigned char[int(originalWidth * originalHeight * scalingFactor * scalingFactor + 2)];


    scaledImageData[0] = newWidth;
    scaledImageData[1] = newHeight;

    //goes through the scaled image array and copies the corresponding pixel data from the original array
    for(int x = 2; x < newWidth * newHeight + 2; x++){
        int myIndex = (int)((x - 2) / newWidth / scalingFactor) * originalWidth + (int)(((x - 2) % newWidth) / scalingFactor + 2);
        scaledImageData[x] = imageData[myIndex];
    }

    return scaledImageData;

}
