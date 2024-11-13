//
//  main.cpp
//  Threshold
//
//  Created by Samuele Albani on 07/11/2024.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int threshold_value = 200;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

Mat frame, src_gray, dst;
const char* window_name = "Display";
const char* trackbar_name = "Type:";
const char* trackbar_value = "Value:";

void on_trackbar(int, void*){
    threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
    imshow(window_name, dst);
}

int main(int argc, const char * argv[]) {
    namedWindow(window_name, WINDOW_AUTOSIZE);

    VideoCapture cap;
    cap.open(0);
        
    if(!cap.isOpened()){
        cerr << "Error!" << endl;
        return -1;
    }
    
    cap.set(CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CAP_PROP_FRAME_HEIGHT, 720);
    
    createTrackbar(trackbar_name, window_name, &threshold_type, max_type, on_trackbar);
    createTrackbar(trackbar_value, window_name, &threshold_value, max_binary_value, on_trackbar);
     
    while(true){
        cap >> frame;
        
        if(frame.empty())
            break;
        
        cvtColor(frame, src_gray, COLOR_BGR2GRAY); // Convert the image to Gray
        
        on_trackbar(0, 0);
        
        if(waitKey(10) == 27)
            break;
    }
    
    return 0;
}
