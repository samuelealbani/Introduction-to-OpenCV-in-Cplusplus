# C++

C++ is a programming language created by Bjarne Stroustrup and his team at Bell Laboratories in 1979. Forty years later, it is one of the most widely used languages in the world; we can find C++ applications everywhere, from the bottom of the oceans to the surface of Mars.

As the name implies, 
Preview: Docs C++ is a very powerful programming language for performance-critical applications that rely on speed and efficient memory management. It’s used in a wide range of industries including software and game development, robotics, microcontrollers, VR/AR, and scientific computing.
C++
 was derived from the C language; Bjarne’s goal was to add 
Preview: Docs Loading link description
object-oriented programming
 into C, a language well-respected for its portability and low-level functionality.

So why learn C++? Among many other things:

- It is fast and flexible.
- It is well-supported.
- It forces you to think in new and creative ways.


``` Good software is invisible. You can't see it, feel it, weigh it, knock on it. *Software* is a collection of programs running on some computer. Sometimes, we can see the computer. Often, we can see only something that contains the computer, such as a telephone, a camera, a bread maker, a car or a wind turbine. We can see what that software does. We can be annoyed or hurt if what it is supposed to do doesn't suit our needs. ```

``` programming is only part of the overall picture. [...] You might become an engineer focusing on computers or a computer scientist, but even then you will not "program all the time". Programming is a way of presenting ideas in code - a way of aiding problem solving. It is nothing - absolutely a waste of time - unless you have ideas that are worth presenting and problems worth solving.```

``` programming language theory studies approaches to descibing computations, while computer programming applies specific programming languages to solve specific computational problems.\n Programming is a tool; it is a fundamental tool for expressing solutions to fundamental and practical problems so that they can be tested, improved through experiment, and used. Programming is where ideas and theories meet reality. This is where computer science can become an experimental discipline, rather than pure theory, and impact the world.```

``` What do we want from our programs? What do we want in general, as opposed to a particual feature of a particular program? We want *correctness* and as part of that, *reliability*. If the program doesn't do what it is supposed to do, and do so in a way so that we can rely on it, it is at best a serious nuisance, at worst a danger. We want it to be *well designed* so that it addresses a real need well; it doesn really matter that a program is correct if what it does is irrelevant to us or if it correctly does something in a way that annoys us. We also want it to be *affordable*.```

```We can describe the process of developing a program as having four stages: 1. Analysis: What's the problem? 2. Design: How do we solve the problem? What should be the overall structure of the system? How does the system communicate with its users? 3. Programming: Express the solution to the problem in code. 4. Testing: make sure the system works correctly under all circumstances required by systematically trying it out.```

## Outline
1. Hello world ( pure output production)
2. Data (**real software tend to produce results based on some input, rather than just doing exactly the same thing each time we excecute them**. To read sth, we need somewhere to read into, in the computer's memory to place what to read. We call such a "place" an object. An *object* is a region of memory with a *type* that specifies what kind of information can be placed in it. **A named object is called a *variable***. The data we put into the variables are called *values*. A statement that defines a variable is called a *definition*. A definition can provide an initial value.)

#### What do we need?
1. Install an IDE (XCode on Mac or Visual Studio on Windows)
2. Install a compiler (included in the IDE)

The details of how to compile, link, and run a C++ program differ from system to system. If you want to use the command line: `c++ -o my_program myfile.cpp` and type `./my_program` to execute it.

### Mac (XCode)

1. Install XCode
2. Create New Project
3. Select `macOS` tab
4. Select `Command Line Tool` and press `Next`
5. Type a title, Select `C++` as Language, and press `Next`
6. Choose the directory for your project
7. press play to build and run or Product>Build and Product>Run

### Windows (Visual Studio)

1. Run Visual Studio Community Installer
2. Select Language packs tab and flag the option `Desktop development with C++`
3. File > New Project
4. Select `Console App` and press `Next`
5. Type the Project name, choose the directory, and press `Create`
6. Press `Play` button to build and run the program

# OpenCV
- OpenCV (Open Source Computer Vision Library) is an open source computer vision and machine learning software library.

- The library has more than 2500 optimized algorithms, which includes a comprehensive set of both classic and state-of-the-art computer vision and machine learning algorithms. 

- These algorithms can be used to detect and recognize faces, identify objects, classify human actions in videos, track camera movements, track moving objects, extract 3D models of objects, produce 3D point clouds from stereo cameras, stitch images together to produce a high resolution image of an entire scene, find similar images from an image database, remove red eyes from images taken using flash, follow eye movements, recognize scenery and establish markers to overlay it with augmented reality, etc. 

- It has C++, Python, Java and MATLAB interfaces and supports Windows, Linux, Android and Mac OS. OpenCV leans mostly towards real-time vision applications and takes advantage of MMX and SSE instructions when available. A full-featured CUDA and OpenCL interfaces are being actively developed right now. 

- OpenCV is written natively in C++ and has a templated interface that works seamlessly with STL containers.



Computer vision fundamental functionalities which could be interesting in the context of robotics:

- Automation:
  - edge/contours detection (find the object to grasp - detect coordinates)
  - colour detection
  - object recognition
  - line recognition / path following
  - aruco/qr code

- Human Computer Interaction:
  - gesture recognition
  - face recognition
  - eye recognition
  - hand pose detection

Introduction to the C++ language fundamentals?

Networking/Connectivity? _How to connect OpenCV applications with other software such as Arduino or ROS/Gazebo? (Serial, UDP/TCP-IP, OSC)_

core functionalities or contrib modules as well?

tutorial on the library's installation?

template on robot simulator or plain computer vision?

## Install on Mac



### Basic

1. Open the Terminal
2. Type this command: `brew install opencv` 





## Install on Windows

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
   
#### 4) Edit Environment Variable:
1. System variables> Path > Edit > New
    > C:\opencv\build\install\x64\vc17\bin
2. Restart Visual Studio

#### 5) Test Install

In Visual Studio:
1. Press `Create New Project` or press `File > New > Project`
2. C++ Empty Project
3. RMB on Source Files > Add > New Item
4. Rename the file `Source.cpp`

Include Libraries into the project (for both Debug and Release)
1. RMB on Project Name > Press `Properties`
2. C/C++ > General > Additional Include Directories > Add `C:\opencv\build\install\include`
3. Linker > General > Additional Include Directories > Add `C:\opencv\build\install\x64\vc17\lib`
4. Linker > Input > Additional Dependencies > Add the names of the lib files relative to the libraries you need to link (i.e. core, opencv_highgui4100.lib, imgcodecs, etc) (N.B. `d` version for Debug Configuration)


## Resources

[Tutorials](https://docs.opencv.org/4.x/d9/df8/tutorial_root.html)
[Coding_Style_Guide](https://github.com/opencv/opencv/wiki/Coding_Style_Guide)