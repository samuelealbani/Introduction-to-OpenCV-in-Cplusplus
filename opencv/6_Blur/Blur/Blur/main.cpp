//
//  main.cpp
//  Blur
//
//  Created by Samuele Albani on 08/11/2024.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int MAX_KERNEL_LENGTH = 31;

Mat src, dst;

char window_name[] = "Smoothing Demo";

int main(int argc, const char * argv[]) {
    // insert code here...
    VideoCapture cap(0);
    
    if(!cap.isOpened()){
        cerr << "Error!" << endl;
        return -1;
    }
    
    cap.set(CAP_PROP_FRAME_WIDTH, 1270);
    cap.set(CAP_PROP_FRAME_HEIGHT, 720);
    
    while (true) {
        cap >> src;
        if(src.empty())
            break;
        
        for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ){
            GaussianBlur( src, dst, Size( i, i ), 0, 0 );
        }
        
        imshow(window_name, dst);
        
        if(waitKey(10) == 27){
            break;
        }
    }
    return 0;
}
