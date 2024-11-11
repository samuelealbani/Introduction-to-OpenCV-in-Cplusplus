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
