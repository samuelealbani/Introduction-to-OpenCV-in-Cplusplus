# Introduction to OpenCV in C++

In this workshop, we will explore how to use the OpenCV library in C++ to create programs for image processing and computer vision. The session will start with an introduction to the fundamentals of C++ programming. Next, we’ll explore OpenCV, from basic image and video input/output to advanced techniques in image manipulation and analysis.

You’ll learn to execute computation on images, applying filters, detecting edges, and using blob detection. We’ll also explore advanced OpenCV features, like object recognition and integrating deep learning models. Throughout, I’ll introduce technical demonstrations drawing from my practice as an artist and experience as a creative technologist. We’ll conclude with reflections on applications in creative robotics.


## Installation

### Installation on Mac
1. Install [Xcode **selecting 'macOS platform' support**](https://developer.apple.com/xcode/)
2. Install [Homebrew](https://brew.sh/)
3. Install OpenCV:
   1. Open the Terminal
   2. run this command: `brew install opencv`.

The library is now installed in `/opt/homebrew/Cellar/opencv/<VERSION>` (Apple Silicon) or `/usr/local/Cellar/opencv/<VERSION>` (Intel).
Please, check and find your opencv installation folder either using Terminal or Finder (Go > Go To Folder > type the path). _If you use the Finder method, open the folder and drag it on the Terminal Icon to print its path. It will be useful during the creation of new projects in Xcode!_


### Installation on Windows

1. [Install Visual Studio Community](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&passive=false&cid=2030#installvs) selecting the component **`Desktop development with C++`**
2. [Install CMake](https://cmake.org/download/)
3. **Setup** OpenCV Source: 
   1. Create a folder called opencv (i.e. `C:\opencv`).
   2. Download as zip and extract into this folder the [opencv](https://github.com/opencv/opencv) main repository (i.e. `C:\opencv\opencv-4.x`).
   3. Download as zip and extract into this folder the [opencv_contrib](https://github.com/opencv/opencv_contrib.git) repository (i.e. `C:\opencv\opencv_contrib-4.x`).
   4. Create an empty folder called `build` in into the opencv folder (i.e. `C:\opencv\build`).
4. **Build** OpenCV with extra modules using CMAKE:
   1. Start cmake-gui.
   2. Select the opencv source code folder (i.e. `C:\opencv\opencv-4.x`) and the folder where binaries will be built (i.e. `C:\opencv\build`) (using the two upper fields in the interface).
   3. Press the `Configure` button to display all OpenCV build parameters.
   4. The first time it will ask you to specify the generator for this project. Select `Visual Studio 17 2022`.
   5. Search for `OPENCV_EXTRA_MODULES_PATH` and set it to the path of `<opencv_contrib_path>/modules` by using the browse button.
   6. Flag the option `BUILD_opencv_world`.
   7. Press `Configure` again, then `Generate` (the first time, you’ll need to select a makefile style).
5. **Install** OpenCV using Visual Studio 
   1. Click `Open Project` in CMake gui to load the Visual Studio Project
   2.  Open `Solution Explorer`.
   3.  Right-click on `CMakeTargets/ALL_BUILD`. Then press `Build` for both "Debug" and "Release" Mode
   4.  Right-click on `CMakeTargets/INSTALL`. Then press `Build` for both "Debug" and "Release" Mode
6.  Edit Environment Variable:
    1. Go to `System variables> Path > Edit > New` and add the path:
        > C:\opencv\build\install\x64\vc17\bin

## How to create a new project

### on MacOS using XCode

1. Run XCode.
2. Press `Create New Project` on the Splash Page  or `File > New > Project`. 
3. Select `macOS` tab, and press `Next`.
4. Select `Command Line Tool` and press `Next`.
5. Type a title, Type an Organization Identifier (i.e. `com.yourname`), Select `C++` as Language, and press `Next`.
6. Choose the directory for your project, and press `Create`.
7. Find OpenCV library files and paths
   1. Open a terminal and type `brew install pkg-config`
   2. View the linker flags for OpenCV running `pkg-config --cflags --libs /opt/homebrew/Cellar/opencv/<VERSION>/lib/pkgconfig/opencv4.pc` (Change <VERSION> with your saved version of OpenCV! i.e. `pkg-config --cflags --libs /opt/homebrew/Cellar/opencv/4.10.0_12/lib/pkgconfig/opencv4.pc`)
   The output will be something like:
   ```bash
   -I/opt/homebrew/opt/opencv/include/opencv4 -L/opt/homebrew/opt/opencv/lib -lopencv_gapi -lopencv_stitching -lopencv_alphamat -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform -lopencv_line_descriptor -lopencv_mcc -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_signal -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_highgui -lopencv_datasets -lopencv_text -lopencv_plot -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_wechat_qrcode -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_dnn -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core
   ```

   The above shows you the includes and the libraries for OpenCV:
   - The _include search path_ (after '-I'): `/opt/homebrew/opt/opencv/include/opencv4`
   - The _library search path_ (after '-L'): `/opt/homebrew/opt/opencv/lib`
   - The library files _linker flags_: `-lopencv_gapi`, `-lopencv_stitching`, `-lopencv_alphamat`, `-lopencv_aruco`, etc.

8. Set Header Search Paths:
   1. click on the Xcode project name in the left side panel, go to `Build Settings` tab and then search for `Header Search Paths`  in the search bar.
   2. double click to add the _include search path_ (paste the path you found with pkg-config) (i.e. `/opt/homebrew/opt/opencv/include/opencv4`)
9. Set Library Search Paths:
   1. click on the Xcode project name in the left side panel, go to `Build Settings` tab and then search for `Library Search Paths`  in the search bar.
   2. double click to add the _library search path_ (paste the path you found with pkg-config) (i.e.  `/opt/homebrew/opt/opencv/lib`)
10. Set Other Linker Flags:
   1. click on the Xcode project name in the left side panel, go to `Build Settings` tab and then search for `Other linker flags`  in the search bar.
   2. double click to add the _library search path_ (paste the path you found with pkg-config) (i.e. `libopencv_core.4.10.0.dylib`, `libopencv_highgui.4.10.0.dylib`, and `libopencv_imgcodecs.4.10.0.dylib`)
11. Sigining & Capabilities (if necessary)
   1. Flag Disable Library Validation
[Tutorial source](https://medium.com/@jaskaranvirdi/setting-up-opencv-and-c-development-environment-in-xcode-b6027728003)


### On Windows using Visual Studio 

1. Create a new project:
   1. Run Visual Studio 2022,
   2. Press `Create New Project` or press `File > New > Project`,
   3. Select "Console App C++" Template and click `Next`,
   4. Rename your project, Select the Location, and click `Create`.
2. Include Libraries into the project (for both `Debug` and `Release`):
   1. Right-click on the Project Name (in Solution Explorer panel) > Click `Properties`,
   2. C/C++ > General > Additional Include Directories > Add `C:\opencv\build\install\include`,
   3. Linker > General > Additional Library Directories > Add `C:\opencv\build\install\x64\vc17\lib`,
   4. Linker > Input > Additional Dependencies > Add the names of the lib files relative to the libraries you need to link (i.e. opencv_core4100.lib, opencv_highgui4100.lib, opencv_imgcodecs4100.lib, etc)  or the world lib if you flagged build 'world' in CMAKE.(N.B. `d` version for Debug Configuration)

## C++ fundamentals
### Computation
#### Operands:
|                          | `bool` | `char` | `int` | `double` | `string` |
|:-------------------------|:------:|:------:|:-----:|:--------:|:--------:|
| assignment               | =      | =      | =     | =        | =        |
| add to end               |        |        | +=    | +=       | +=       |
| multiply and assign      |        |        | *=    | *=       |          |
| divide and assign        |        |        | /=    | /=       |          |
| remainder and assign     |        |        | %=    |          |          |
| read from `s` into `x`   | s>>x   | s>>x   | s>>x  | s>>x     | s>>x     |
| write `x` to `s`         | s<<x   | s<<x   | s<<x  | s<<x     | s<<x     |
| equals                   | ==     | ==     | ==    | ==       | ==       |
| not equal                | !=     | !=     | !=    | !=       | !=       |
| greater than             | >      | >      | >     | >        | >        |
| greater than or equal    | >=     | >=     | >=    | >=       | >=       |
| less than                | <      | <      | <     | <        | <        |
| less than or equal       | <=     | <=     | <=    | <=       | <=       |
| addition                 |        |        | +     | +        |          |
| concatenation            |        |        |       |          | +        |
| subtraction              |        |        | -     | -        |          |
| multiplication           |        |        | *     | *        |          |
| division                 |        |        | /     | /        |          |
| remainder (modulo)       |        |        | %     |          |          |
| increment by 1           |        |        | ++    | ++       |          |
| decrement by 1           |        |        | --    | --       |          |
| increment by `n`         |        |        | +=n   | +=n      |          |
| decrement by `n`         |        |        | -=n   | -=n      |          |

### Selection

#### if statement
```cpp
if(my_age>32) {
    cout << "Quite old!" << endl;
} else if (my_age < 18) {
    cout << "You're a kid!" << endl;
} else {
    cout << "cool!" << endl;
}
```

#### switch
```cpp
switch (my_age) {
    case 25:
        cout << "you're 25\n";
        break;
    
    case 10:
    case 20:
        cout << "you're 10 or 20\n";
        break;
        
    default:
        cout << "anything else\n";
        break;
}
```
### Iteration
#### for loop
```cpp
for(int i = 0; i < 5; ++i){
    cout << i << endl;
}
```

Infinite loop:
```cpp
for(;;){
    // statements
}
```

#### while
```cpp
while (condition) {
    // statements
}
```
```cpp
while (counter <= max_counter) {
    cout << counter << endl;
    ++counter;
}
```

### Collections
[Advantages of vector over array in C++](https://www.geeksforgeeks.org/advantages-of-vector-over-array-in-c/).

#### Vectors
A vector is a sequence of elements that you can access by an index. That is, the first element has index 0, the second index 1, and so on. The vectors are resizable i.e they can grow and shrink as vectors are allocated on heap memory.
```cpp
vector<int> my_vector = {13, 1, 253, 0}; // vector declaration
my_vector.push_back(455);   // add one element
my_vector.pop_back();       // delete the last element

// print every element
for(size_t i = 0; i < my_vector.size(); ++i){   // use `size_t` type when you iterate through the size of an object
    cout << my_vector[i] << endl;
}
```

### Pointers
A computer's memory is a sequence of bytes. We can number the bytes from 0 to the last one.
An `address` is "a number that indicates a location in memory".
You can think of an address as a kind of integer value. The first byte of memory has the address of 0, the next the address 1, and so on.
Everything we put in memory has an address.
We use the `&` operand to get the address of an object.
We use the `*` operand to get the content of an address.

Remember that:
- A *“pointer to int”* type `int*` holds the address of an int
- The *“address of”* operator `&` returns the address of a variable
- The *“content of”* operator `*` returns the value of the object pointed to
```cpp
int var = 17;
int* ptr = &var;	// ptr will hold the address of var (i.e. 4096)
cout << *ptr;		// it will print 17



```


## OpenCV code examples

### Drawing functions

```cpp
// declare and initialise a Mat object
Mat graph = Mat::zeros(600, 800, CV_8UC3);

// draw a circle
circle(graph, Point(400, 300), 100, Scalar(255, 255, 255), 3); // Mat, Point(x,y), Scalar(B,G,R), thickness
```



### Mouse Events

```cpp
// declare the callback function
void onMouseCallback(int event, int x, int y, int flags, void* userdata){
    // cout << "x: " << x << " - y: " << y << endl; // called for every event
    if(event == EVENT_LBUTTONDOWN){
        cout << "LMB clicked at " << x << ' ' << y << endl;
    } else if(event == EVENT_LBUTTONUP){
        cout << "LMB released at " << x << ' ' << y << endl;
    }

    // update the output (if necessary)
    imshow(window_name, image); 
}

int main(){

    // ...

     //set the callback function for any mouse event
    setMouseCallback(window_name, onMouseCallback);

    //...
}
```

### Trackbars
```cpp
const char* trackbar_name = "Name";
int slider_value = 0;
int const max_slider = 255;

void trackbarCallback(int, void*){
    // compute using the slider value
    //...

    // show the results
    imshow("Display", image); 
}

int main(){
//...

// create trackbar
createTrackbar( trackbar_name, window_name, &slider_value, max_slider, trackbarCallback );

// call it to show the first result
trackbarCallback(0, 0);

//..

}
```


### Convert to grey scale
```cpp
cvtColor( src, src_gray, COLOR_BGR2GRAY );
```

### Blur
```cpp
blur(src, dst, Size(3, 3));
```

### Gaussian Blur
```cpp
for(int i = 1; i < MAX_KERNEL_LENGTH; i+=2){
    GaussianBlur(gray, dst, Size(i, i), 0, 0);
}
```
### Threshold
```cpp

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
 
using namespace cv;
using std::cout;
 
 
int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;
 
Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";
 
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";
 
 
static void Threshold_Demo( int, void* )
{
    /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
    */
    threshold( src_gray, dst, threshold_value, max_binary_value, threshold_type );
    imshow( window_name, dst );
}
 
int main( int argc, char** argv )
{
    String imageName("stuff.jpg"); // by default

    src = imread( "path/to/stuff.jpg" ); // Load an image
 
    if (src.empty())
    {
        cout << "Cannot read the image: " << imageName << std::endl;
        return -1;
    }
 
    cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to Gray
 
    namedWindow( window_name, WINDOW_AUTOSIZE ); // Create a window to display results
 
    createTrackbar( trackbar_type,
                    window_name, &threshold_type,
                    max_type, Threshold_Demo ); // Create a Trackbar to choose type of Threshold
 
    createTrackbar( trackbar_value,
                    window_name, &threshold_value,
                    max_value, Threshold_Demo ); // Create a Trackbar to choose Threshold value
 
    Threshold_Demo( 0, 0 ); // Call the function to initialize
 
    waitKey();
    return 0;
}
```

### Canny threshold
```cpp
/**
 * source: https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/ImgTrans/CannyDetector_Demo.cpp
 * 
 * @file CannyDetector_Demo.cpp
 * @brief Sample code showing how to detect edges using the Canny Detector
 * @author OpenCV team
 */

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

//![variables]
Mat src, src_gray;
Mat dst, detected_edges;

int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";
//![variables]

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
static void CannyThreshold(int, void*)
{
    //![reduce_noise]
    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );
    //![reduce_noise]

    //![canny]
    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
    //![canny]

    /// Using Canny's output as a mask, we display our result
    //![fill]
    dst = Scalar::all(0);
    //![fill]

    //![copyto]
    src.copyTo( dst, detected_edges);
    //![copyto]

    //![display]
    imshow( window_name, dst );
    //![display]
}


/**
 * @function main
 */
int main( int argc, char** argv )
{
  //![load]
   src = imread( "path/to/stuff.jpg" ); // Load an image

  if( src.empty() )
  {
    std::cout << "Could not open or find the image!\n" << std::endl;
    std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
    return -1;
  }
  //![load]

  //![create_mat]
  /// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );
  //![create_mat]

  //![convert_to_gray]
  cvtColor( src, src_gray, COLOR_BGR2GRAY );
  //![convert_to_gray]

  //![create_window]
  namedWindow( window_name, WINDOW_AUTOSIZE );
  //![create_window]

  //![create_trackbar]
  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
  //![create_trackbar]

  /// Show the image
  CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;
}
```

### Find Contours
```cpp
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
 
using namespace cv;
using namespace std;
 
Mat src_gray;
int thresh = 100;
RNG rng(12345);
 
void thresh_callback(int, void* );
 
int main( int argc, char** argv )
{
    Mat src = imread( "path/to/stuff.jpg" );
    if( src.empty() )
    {
      cout << "Could not open or find the image!\n" << endl;
      cout << "Usage: " << argv[0] << " <Input image>" << endl;
      return -1;
    }
 
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );
 
    const char* source_window = "Source";
    namedWindow( source_window );
    imshow( source_window, src );
 
    const int max_thresh = 255;
    createTrackbar( "Canny thresh:", source_window, &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );
 
    waitKey();
    return 0;
}
 
void thresh_callback(int, void* )
{
    Mat canny_output;
    Canny( src_gray, canny_output, thresh, thresh*2 );
 
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );
 
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        drawContours( drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
    }
 
    imshow( "Contours", drawing );
}
```

### Bounding Box
```cpp
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
Mat src_gray;
int thresh = 100;
RNG rng(12345);
void thresh_callback(int, void* );
int main( int argc, char** argv )
{
    Mat src = imread( "path/to/stuff.jpg" );
    if( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );
    const char* source_window = "Source";
    namedWindow( source_window );
    imshow( source_window, src );
    const int max_thresh = 255;
    createTrackbar( "Canny thresh:", source_window, &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );
    waitKey();
    return 0;
}
void thresh_callback(int, void* )
{
    Mat canny_output;
    Canny( src_gray, canny_output, thresh, thresh*2 );
    vector<vector<Point> > contours;
    findContours( canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE );
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    vector<Point2f>centers( contours.size() );
    vector<float>radius( contours.size() );
    for( size_t i = 0; i < contours.size(); i++ )
    {
        approxPolyDP( contours[i], contours_poly[i], 3, true );
        boundRect[i] = boundingRect( contours_poly[i] );
        minEnclosingCircle( contours_poly[i], centers[i], radius[i] );
    }
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        drawContours( drawing, contours_poly, (int)i, color );
        rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2 );
        circle( drawing, centers[i], (int)radius[i], color, 2 );
    }
    imshow( "Contours", drawing );
}
```

### Video Input
```cpp
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
 
using namespace cv;
using namespace std;
 
int main(int, char**)
{
    Mat frame;
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    cap.set(CAP_PROP_FRAME_WIDTH, 400);
    cap.set(CAP_PROP_FRAME_HEIGHT, 300);
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame);
        if (waitKey(5) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
```
## Aruco
1. create the utility file
   1. Create a file in the same folder of the main.cpp called 'aruco_samples_utilities.hpp'
   2. Paste the content of this [file](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/objectDetection/aruco_samples_utility.hpp)
2. collect the data
   1. Create a file called `aruco_samples_utility.hpp`
   2. Paste the content of this [file](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/objectDetection/aruco_samples_utility.hpp)
   3. Create a file called `tutorial_camera_params.yml`
   4. Paste the content of this [file](hhttps://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/objectDetection/tutorial_camera_params.yml)
   5. Create a file called `tutorial_dict.yml`
   6. Paste the content of this [file](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/objectDetection/tutorial_dict.yml)
   7. paste in the same folder this [file](https://github.com/opencv/opencv/blob/4.x/doc/tutorials/objdetect/aruco_board_detection/images/gboriginal.jpg) 
3. Set these command line paramenter in you IDE (change the paths accordingly):
```
-w=5 -h=7 -l=100 -s=10
-v=/path_to/gboriginal.jpg
-c=/path_to/tutorial_camera_params.yml
-cd=/path_to/tutorial_dict.yml
```

```cpp
#include <iostream>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include "./aruco_samples_utilities.hpp"

using namespace std;
using namespace cv;

namespace {
const char* about = "Pose estimation using a ArUco Planar Grid board";

//! [aruco_detect_board_keys]
const char* keys  =
        "{w        |       | Number of squares in X direction }"
        "{h        |       | Number of squares in Y direction }"
        "{l        |       | Marker side length (in pixels) }"
        "{s        |       | Separation between two consecutive markers in the grid (in pixels)}"
        "{d        |       | dictionary: DICT_4X4_50=0, DICT_4X4_100=1, DICT_4X4_250=2,"
        "DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, DICT_5X5_250=6, DICT_5X5_1000=7, "
        "DICT_6X6_50=8, DICT_6X6_100=9, DICT_6X6_250=10, DICT_6X6_1000=11, DICT_7X7_50=12,"
        "DICT_7X7_100=13, DICT_7X7_250=14, DICT_7X7_1000=15, DICT_ARUCO_ORIGINAL = 16}"
        "{cd       |       | Input file with custom dictionary }"
        "{c        |       | Output file with calibrated camera parameters }"
        "{v        |       | Input from video or image file, if omitted, input comes from camera }"
        "{ci       | 0     | Camera id if input doesnt come from video (-v) }"
        "{dp       |       | File of marker detector parameters }"
        "{rs       |       | Apply refind strategy }"
        "{r        |       | show rejected candidates too }";
}
//! [aruco_detect_board_keys]

int main(int argc, char *argv[]) {
    CommandLineParser parser(argc, argv, keys);
    parser.about(about);

    if(argc < 7) {
        parser.printMessage();
        return 0;
    }

    //! [aruco_detect_board_full_sample]
    int markersX = parser.get<int>("w");
    int markersY = parser.get<int>("h");
    float markerLength = parser.get<float>("l");
    float markerSeparation = parser.get<float>("s");
    bool showRejected = parser.has("r");
    bool refindStrategy = parser.has("rs");
    int camId = parser.get<int>("ci");


    Mat camMatrix, distCoeffs;
    readCameraParamsFromCommandLine(parser, camMatrix, distCoeffs);
    aruco::Dictionary dictionary = readDictionatyFromCommandLine(parser);
    aruco::DetectorParameters detectorParams = readDetectorParamsFromCommandLine(parser);

    String video;
    if(parser.has("v")) {
        video = parser.get<String>("v");
    }

    if(!parser.check()) {
        parser.printErrors();
        return 0;
    }

    aruco::ArucoDetector detector(dictionary, detectorParams);
    VideoCapture inputVideo;
    int waitTime;
    if(!video.empty()) {
        inputVideo.open(video);
        waitTime = 0;
    } else {
        inputVideo.open(camId);
        waitTime = 10;
    }

    float axisLength = 0.5f * ((float)min(markersX, markersY) * (markerLength + markerSeparation) +
                               markerSeparation);

    // Create GridBoard object
    //! [aruco_create_board]
    aruco::GridBoard board(Size(markersX, markersY), markerLength, markerSeparation, dictionary);
    //! [aruco_create_board]

    // Also you could create Board object
    //vector<vector<Point3f> > objPoints; // array of object points of all the marker corners in the board
    //vector<int> ids; // vector of the identifiers of the markers in the board
    //aruco::Board board(objPoints, dictionary, ids);

    double totalTime = 0;
    int totalIterations = 0;

    while(inputVideo.grab()) {
        Mat image, imageCopy;
        inputVideo.retrieve(image);

        double tick = (double)getTickCount();

        vector<int> ids;
        vector<vector<Point2f>> corners, rejected;
        Vec3d rvec, tvec;

        //! [aruco_detect_and_refine]

        // Detect markers
        detector.detectMarkers(image, corners, ids, rejected);

        // Refind strategy to detect more markers
        if(refindStrategy)
            detector.refineDetectedMarkers(image, board, corners, ids, rejected, camMatrix,
                                           distCoeffs);

        //! [aruco_detect_and_refine]

        // Estimate board pose
        int markersOfBoardDetected = 0;
        if(!ids.empty()) {
            // Get object and image points for the solvePnP function
            cv::Mat objPoints, imgPoints;
            board.matchImagePoints(corners, ids, objPoints, imgPoints);

            // Find pose
            cv::solvePnP(objPoints, imgPoints, camMatrix, distCoeffs, rvec, tvec);

            markersOfBoardDetected = (int)objPoints.total() / 4;
        }

        double currentTime = ((double)getTickCount() - tick) / getTickFrequency();
        totalTime += currentTime;
        totalIterations++;
        if(totalIterations % 30 == 0) {
            cout << "Detection Time = " << currentTime * 1000 << " ms "
                 << "(Mean = " << 1000 * totalTime / double(totalIterations) << " ms)" << endl;
        }

        // Draw results
        image.copyTo(imageCopy);
        if(!ids.empty())
            aruco::drawDetectedMarkers(imageCopy, corners, ids);

        if(showRejected && !rejected.empty())
            aruco::drawDetectedMarkers(imageCopy, rejected, noArray(), Scalar(100, 0, 255));

        if(markersOfBoardDetected > 0)
            cv::drawFrameAxes(imageCopy, camMatrix, distCoeffs, rvec, tvec, axisLength);

        imshow("out", imageCopy);
        char key = (char)waitKey(waitTime);
        if(key == 27) break;
    //! [aruco_detect_board_full_sample]
    }

    return 0;
}
```

[Complete Tutorial](https://docs.opencv.org/4.x/db/da9/tutorial_aruco_board_detection.html)




## Resources
### Web
**C++**:
- [Standard C++ Foundation](https://isocpp.org/)
- [C++ Reference](https://en.cppreference.com/w/)
- [cplusplus.com](https://cplusplus.com/) | A site with general information about the C++ language, a reference, tutorial, and an articles section.

**OpenCV**:
- [OpenCV | Home](https://opencv.org/)
- [OpenCV | github repository](https://github.com/opencv/opencv)
- [OpenCV | github extra modules repository](https://github.com/opencv/opencv)
- [Deep Learning with OpenCV DNN Module](https://learnopencv.com/deep-learning-with-opencvs-dnn-module-a-definitive-guide/)
- [Computer Vision: Algorithms and Applications, 2nd ed.](https://szeliski.org/Book/)
### Books
- [Programming: Principles and Practice Using C++, 2nd Ed.](https://www.informit.com/store/programming-principles-and-practice-using-c-plus-plus-9780321992789)
- [C++ Primer](https://www.amazon.com/Primer-5th-Stanley-B-Lippman/dp/0321714113?s=books&ie=UTF8&qid=1343780237&sr=1-1&keywords=c%2B%2B+primer)
