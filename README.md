# OpenCV
- OpenCV (Open Source Computer Vision Library) is an open source computer vision and machine learning software library.

- The library has more than 2500 optimized algorithms, which includes a comprehensive set of both classic and state-of-the-art computer vision and machine learning algorithms. 

- These algorithms can be used to detect and recognize faces, identify objects, classify human actions in videos, track camera movements, track moving objects, extract 3D models of objects, produce 3D point clouds from stereo cameras, stitch images together to produce a high resolution image of an entire scene, find similar images from an image database, remove red eyes from images taken using flash, follow eye movements, recognize scenery and establish markers to overlay it with augmented reality, etc. 

- It has C++, Python, Java and MATLAB interfaces and supports Windows, Linux, Android and Mac OS. OpenCV leans mostly towards real-time vision applications and takes advantage of MMX and SSE instructions when available. A full-featured CUDA and OpenCL interfaces are being actively developed right now. 

- OpenCV is written natively in C++ and has a templated interface that works seamlessly with STL containers.

# C++

Computer vision fundamental functionalities applied to robotics endeavours:
- automation:
  - edge/contours detection (find the object to grasp - detect coordinates)
  - colour detection
  - object recognition
  - line recognition / path following
  - aruco/qr code
- Human Computer Interaction
  - gesture recognition
  - face recognition
  - eye recognition
  - hand pose detection

Introduction to the C++ language fundamentals?

Networking/Connectivity? _How to connect OpenCV applications with other software such as Arduino or ROS/Gazebo? (Serial, UDP/TCP-IP, OSC)_

contrib folder or just vanilla opencv?

tutorial on the library's installation?

template on robot simulator or plain computer vision?

## Install

[Get Started Guide](https://opencv.org/get-started/)


### Basic

[tutorial install on windows](https://docs.opencv.org/4.x/d3/d52/tutorial_windows_install.html#tutorial_windows_gitbash_build)

1. Download  the  latest  version of OpenCV for Windows from this [link](https://github.com/opencv/opencv/releases/latest).
2. Run the exe -> Extract in `C:`
3. type in the command prompt (run as administrator)
   > setx -m OPENCV_DIR C:\opencv\build\x64\vc16
4. To use OpenCV  _dynamic  link  libraries_  (DLLs),  add  `%OPENCV_DIR%\bin`  to  your
library path. (For example, in Windows 10, right-click on your computer icon, select
Properties, and then click on Advanced System Settings. Finally, select Environment
Variables and add the OpenCV binary path to the Path variable.)

### Contribution Folder

#### Requirements:
- **Install Visual Studio Community and install `Desktop development with C++`**.
- Install CMake. Download the binary [here](https://cmake.org/download/).


#### 1) Setup Source

1. Create a folder called opencv
3. Download as zip and extract here the [opencv](https://github.com/opencv/opencv) main repository.
4. Download as zip and extract here the [opencv_contrib](https://github.com/opencv/opencv_contrib.git) repository.
5. Create folder `build`



#### 2) Build OpenCV with extra modules using CMAKE:

1. Start cmake-gui.

2. Select the opencv source code folder and the folder where binaries will be built (the 2 upper forms of the interface).

3. Press the configure button. You will see all the opencv build parameters in the central interface.

4. Browse the parameters and look for the form called OPENCV_EXTRA_MODULES_PATH (use the search form to focus rapidly on it).

5. Complete this OPENCV_EXTRA_MODULES_PATH by the proper pathname to the <opencv_contrib>/modules value using its browse button.

6. Press the configure button followed by the generate button (the first time, you will be asked which makefile style to use).

7. Build the opencv core with the method you chose (make and make install if you chose Unix makefile at step 6).

8. To run, linker flags to contrib modules will need to be added to use them in your code/IDE. For example to use the aruco module, "-lopencv_aruco" flag will be added.


#### 3) Install using Visual Studio 

1. Press `Open Project` to open the Visual Studio Project
2.  Open Solution Explorer
3.  RMB on `CMakeTargets/ALL_BUILD`. Then press `Build` for both "Debug" and "Release" Mode
4.  RMB on `CMakeTargets/INSTALL`. Then press `Build` for both "Debug" and "Release" Mode

#### 4) Test Install

In Visual Studio:
1. Press `Create New Project` or press File > New > Project
2. C++ Empty Project
3. RMB on Source Files > Add > New Item `Source.cpp`

4. Edit Environment Variable > System variables> Path > Edit > New
    > C:\opencv\build\install\x64\vc17\bin
5. Restart Visual Studio

Include Libraries into the project (for both Debug and Release)
1. RMB on Project Name > Press `Properties`
2. C/C++ > General > Additional Include Directories > Add `C:\opencv\build\install\include`
3. Linker > General > Additional Include Directories > Add `C:\opencv\build\install\x64\vc17\lib`
4. Linker > Input > Additional Dependencies > Add the names of the lib files relative to the libraries you need to link (i.e. core, opencv_highgui4100.lib, imgcodecs, etc) (N.B. `d` version for Debug Configuration)
## Resources

[Tutorials](https://docs.opencv.org/4.x/d9/df8/tutorial_root.html)
[Coding_Style_Guide](https://github.com/opencv/opencv/wiki/Coding_Style_Guide)