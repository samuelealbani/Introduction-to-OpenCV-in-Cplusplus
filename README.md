# Introduction to OpenCV in C++

In this workshop, we will explore how to use the OpenCV library in C++ to create programs for image processing and computer vision. The session will start with an introduction to the fundamentals of C++ programming. Next, we’ll explore OpenCV, from basic image and video input/output to advanced techniques in image manipulation and analysis.

You’ll learn to execute computation on images, applying filters, detecting edges, and using blob detection. We’ll also explore advanced OpenCV features, like object recognition and integrating deep learning models. Throughout, I’ll introduce technical demonstrations drawing from my practice as an artist and experience as a creative technologist. We’ll conclude with reflections on applications in creative robotics.


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
