#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    
    VideoCapture cap;
    cap.open(0); // pass the id of a video input (0, 1, ...) or the absolute path of a video
    if(!cap.isOpened()){
        cerr << "Error: couldn't open video" << endl;
        return -1;
    }
    
    cap.set(CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CAP_PROP_FRAME_HEIGHT, 720);
    
    Mat frame;
    
    while(true){
        cap >> frame;
        if(frame.empty())
            break;
        
        imshow("Camera", frame);
        
        if(waitKey(10) == 27)
            break;
    }
        
    return 0;
}
