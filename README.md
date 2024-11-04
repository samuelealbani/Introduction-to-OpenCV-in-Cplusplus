# Introduction to OpenCV in C++

In this workshop, we will explore how to use the OpenCV library in C++ to create programs for image processing and computer vision. The session will start with an introduction to the fundamentals of C++ programming. Next, we’ll explore OpenCV, from basic image and video input/output to advanced techniques in image manipulation and analysis.

You’ll learn to execute computation on images, applying filters, detecting edges, and using blob detection. We’ll also explore advanced OpenCV features, like object recognition and integrating deep learning models. Throughout, I’ll introduce technical demonstrations drawing from my practice as an artist and experience as a creative technologist, including applications in creative robotics.


## Requirements

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
   1. Create a folder called opencv
   2. Download as zip and extract into this folder the [opencv](https://github.com/opencv/opencv) main repository.
   3. Download as zip and extract into this folder the [opencv_contrib](https://github.com/opencv/opencv_contrib.git) repository.
   4. Create an empty folder called `build`
4. **Build** OpenCV with extra modules using CMAKE:
   1. Start cmake-gui.
   2. Select the opencv source code folder and the folder where binaries will be built (using the two upper fields in the interface).
   3. Press the `Configure` button to display all OpenCV build parameters.
   4. Search for `OPENCV_EXTRA_MODULES_PATH` and set it to the path of `<opencv_contrib>/modules` by using the browse button..
   5. Press `Configure` again, then `Generate` (the first time, you’ll need to select a makefile style).
   6. Build the opencv core with the method you chose (make and make install if you chose Unix makefile at step 6).
   7. To run, linker flags to contrib modules will need to be added to use them in your code/IDE. For example to use the aruco module, "-lopencv_aruco" flag will be added.
5. **Install** OpenCV using Visual Studio 
   1. Click `Open Project` in CMake gui to load the Visual Studio Project
   2.  Open `Solution Explorer`.
   3.  Right-click on `CMakeTargets/ALL_BUILD`. Then press `Build` for both "Debug" and "Release" Mode
   4.  Right-click on `CMakeTargets/INSTALL`. Then press `Build` for both "Debug" and "Release" Mode
6.  Edit Environment Variable:
    1. Go to `System variables> Path > Edit > New` and add the path:
        > C:\opencv\build\install\x64\vc17\bin


---
In this workshop, we will explore how to use OpenCV library in C++ to create programs for image processing and computer vision. The session will start with an introduction to the fundamentals of C++ programming language. Next, we will explore OpenCV, from basic image and video input/output to advanced image manipulation and analysis techniques.

You’ll learn to execute computation on images, applaying filters, detecting edges, and using blob detection. We’ll also explore advanced OpenCV features, like object recognition, integrating deep learning models. Throughout, I’ll introduce technical demonstrations drawing from my practice as an artist and experience as creative technologist, including applications in creative robotics.

Please, be punctual and bring your laptop! I recommend installing the OpenCV library before the start of the lesson. Here you can find instructions for both Mac and Windows. If any installation issues arise, I’ll be available to assist you in class.

See you coding soon!


In this workshop, hands on we will explore 
- fundamentals of C++ programming languages
- Introduction to OpenCV in C++
- fundamental concepts of Computer Vision technology, 
- manipulation and analysis of images data
- technical demonstration drawing from my practice of artist and creative technologis
- application in Creative Robotics
- Advanced application of deep learning models UAL

### Outline:
#### C++
0. Installation
1. Hello World (simple output)
2. Data (input management)
3. Computation 
   1. Expression (operands)
   2. Selection (if / switch)
   3. Iteration (for / while loops)
4. Functions
   1. Exit codes
   2. Return types
   3. Custom Functions
5. Collections (vectors)
6. Pointers [`extra`]
7. Classes [`extra`]

#### OpenCV
0. Installation
1. Hello World (simple read/output image file)
2. Video (file/camera input)
3. Graphics (2D shapes / text)
4. Image Manipulation (BW, blur, edge detection, segmentation)
5. Image Analysis (Blob Detection)
6. Applications/Examples
   1. Brightest spot (torch)
   2. Aruco (chess)
7. [Face Recognition](https://docs.opencv.org/4.x/da/d60/tutorial_face_main.html)
8. [Deep Learning Models](https://docs.opencv.org/4.x/d0/dd4/tutorial_dnn_face.html) [`extra`]
9. Robot Demonstration [`testing`]

## OpenCV
**OpenCV (Open Source Computer Vision Library) is an open source computer vision and machine learning software library.**

**OpenCV was built to provide a common infrastructure for computer vision applications** and to accelerate the use of machine perception in the commercial products. Being an Apache 2 licensed product, OpenCV makes it easy for businesses to utilize and modify the code.

The library has more than 2500 optimized algorithms, which includes a comprehensive set of both classic and state-of-the-art computer vision and machine learning algorithms. **These algorithms can be used to detect and recognize faces, identify objects, classify human actions in videos, track camera movements, track moving objects, extract 3D models of objects, produce 3D point clouds from stereo cameras, stitch images together to produce a high resolution image of an entire scene, find similar images from an image database, remove red eyes from images taken using flash, follow eye movements, recognize scenery and establish markers to overlay it with augmented reality, etc.** OpenCV has more than 47 thousand people of user community and estimated number of downloads exceeding 18 million. The library is used extensively in companies, research groups and by governmental bodies.

**It has C++, Python, Java and MATLAB interfaces and supports Windows, Linux, Android and Mac OS**. OpenCV leans mostly towards real-time vision applications and takes advantage of MMX and SSE instructions when available. A full-featured CUDAand OpenCL interfaces are being actively developed right now. There are over 500 algorithms and about 10 times as many functions that compose or support those algorithms. **OpenCV is written natively in C++** and has a templated interface that works seamlessly with STL containers.

## Resources
### Web
**C++**:
- [Standard C++ Foundation](https://isocpp.org/)
- [C++ Reference](https://en.cppreference.com/w/)
- [cplusplus.com](https://cplusplus.com/) | A site with general information about the C++ language, a reference, tutorial, and an articles section.
- 

**OpenCV**:
- [OpenCV | Home](https://opencv.org/)
- [Deep Learning with OpenCV DNN Module](https://learnopencv.com/deep-learning-with-opencvs-dnn-module-a-definitive-guide/)
### Books
- [Programming: Principles and Practice Using C++, 2nd Ed.](https://www.informit.com/store/programming-principles-and-practice-using-c-plus-plus-9780321992789)
- [C++ Primer](https://www.amazon.com/Primer-5th-Stanley-B-Lippman/dp/0321714113?s=books&ie=UTF8&qid=1343780237&sr=1-1&keywords=c%2B%2B+primer)
