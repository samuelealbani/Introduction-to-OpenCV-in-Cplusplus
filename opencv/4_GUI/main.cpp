//
//  main.cpp
//  GUI_controls
//
//  Created by Samuele Albani on 07/11/2024.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const int alpha_slider_max = 100;
int alpha_slider;
double alpha;

static void on_trackbar(int, void*){
    alpha = (double)alpha_slider/alpha_slider_max;
    cout << alpha << endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    alpha_slider = 0;
    
    namedWindow("Display", WINDOW_AUTOSIZE);
    
    char TrackbarName[50] = "Alpha:"; // label
    createTrackbar(TrackbarName, "Display", &alpha_slider, alpha_slider_max, on_trackbar);
    
    // on_trackbar(alpha_slider, 0);
    
    waitKey(0);
    
    return 0;
}
