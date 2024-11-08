//
//  main.cpp
//  Drawing
//
//  Created by Samuele Albani on 05/11/2024.
//

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int thickness = 2;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Mat my_image = Mat::zeros(400, 400, CV_8UC4);
    
    
    line(my_image,
         Point(1, 4),
         Point(9, 7),
         Scalar(0, 255, 0),
         thickness,
         LINE_AA);
    

    rectangle(my_image,
              Point(180, 200),
              Point(380, 350),
              Scalar(0, 0, 255, 10),
              -1, // or FILLED
              LINE_AA);
    
    ellipse( my_image,
           Point( 6, 5 ),
           Size( 4, 6),
           45, // angle rotation
           0, // startAngle
           360, // stopAngle
           Scalar( 255, 0, 0 ),
           4, // Thickness
           LINE_AA );
    
    imshow("Output", my_image);
    
    waitKey(0);
    return 0;
}
