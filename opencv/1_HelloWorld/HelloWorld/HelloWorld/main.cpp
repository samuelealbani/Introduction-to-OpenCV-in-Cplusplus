//
//  main.cpp
//  HelloWorld
//
//  Created by Samuele Albani on 01/11/2024.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main(int argc, const char * argv[]) {
   std::string image_path = samples::findFile("lisa.jpeg");
        Mat img = imread(image_path, IMREAD_COLOR);
     
        if(img.empty())
        {
            std::cout << "Could not read the image: " << std::endl;
            return 1;
        }
     
        imshow("Display window", img);
        int k = waitKey(0); // Wait for a keystroke in the window
     
        if(k == 's')
        {
            imwrite("starry_night.png", img);
        }
     
        return 0;
}
