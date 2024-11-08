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

Our job as programmers is to express computations CORRECTLY, SIMPLY, and EFFICIENTLY. 
It doesn't matter how fast a program is if it gives the wrong results.

Our main tool for organizing a program - and for organizing our thoughts as we program - is to break up a big computation into many little ones.
The reason is that we are not very good at dealing with large problems. The way we actually deal with those is to break them down into smaller problems, and we keep breaking those into even smaller parts until we get something simple enough to understand and solve.

When we consider dividing up a program, we must always consider what tools we have available to express the parts and their communications. We must consider what libraries we have available to express the parts and their communication.

## Outline
1. Hello world ( pure output production)
2. Data 
   (**real software tend to produce results based on some input, rather than just doing exactly the same thing each time we excecute them**. To read sth, we need somewhere to read into, in the computer's memory to place what to read. We call such a "place" an object. An *object* is a region of memory with a *type* that specifies what kind of information can be placed in it. **A named object is called a *variable***. The data we put into the variables are called *values*. A statement that defines a variable is called a *definition*. A definition can provide an initial value.)
3. Computation 
    Computation is the act of producing some outputs (result) based on some inputs (arguments)
   1. Expression (How to compute a value from a set of operands)
     - An expression computes a value from a set of operators(+,-,/,%,etc)
     - We define a function when we want a separate computation with a name to make the computation logically separate, make it possible to use the function in more than one plase
   2. Selection (How to choose among alternative actions)
   3. Iteration (How to repeat a computation for a series of values)
     - vector (type to hold sequences of values)  
4. Functions
   1. Exit codes
        The purpose of the exit() function is to terminate the execution of a program. The “return 0”(or EXIT_SUCCESS) implies that the code has executed successfully without any error. Exit codes other than “0”(or EXIT_FAILURE) indicate the presence of an error in the code. [link](https://www.geeksforgeeks.org/exit-codes-in-c-c-with-examples/) 
   2. Custom Functions
      The standard library provides a lot of useful functions, such as the square root function `sqrt()`. However, we write many functions ourselves. We don't have to use the result of a function call, but we do have to give a function exactly the arguments it requires. Usually, all the information needed to call a funcion is in the first line of its declaration. For example:
      > int square (int x)
      We don't really need to llok at the function body. Most of the time, we are just interested in knowing how to call a function. Fortunately, C++ provides a way of supplying that information separate from the complete function definition. It is called *function declaration*:
      > int square(int);
      A semicolon is used in a function declaration instead of the body used in the corresponding *function definition*
      ```cpp
      int square (int x)
      {
         return x*x;
      }
      ```
      So, if you want to use a function, you simply write, or `#include`, its declaration. The function definition can be elsewhere. This distinction between declaration and definitions becomes essential in larger programs where we use declarations to keep most of the code out of sight to allow us to concentrate on single part of program at a time.
      A *declaration* is a statement that introduces a name into a scope:
      - specifying a type for what is named
      - optionally, specifying an initialiser (i.e. an initial value or a function body)
      Before a name can be used in a C++ program, it must be declared.
      Every *definition* is also a declaraton, but only some declaration are also definitions. A definition specifies exactly what a name refers to. In particular, a definition of a variable sets aside memory for that variable. Consequently, you can't define something twice.
      In contrast, a declaration that isn't also a definition simply tells how to use a name; it is just an interface and doesn't allocate memory or specify a function body
5. Collections
   [Advantages of vector over array in C++](https://www.geeksforgeeks.org/advantages-of-vector-over-array-in-c/)
   Vectors: A vector is a sequence of elements that you can access by an index. That is, the first element has index 0, the second index 1, and so on. The vectors are resizable i.e they can grow and shrink as vectors are allocated on heap memory. 
   > vector<int> my_vector = {2, 42};
   > my_vector.size();
   > my_vector.push_back(23);
6. Pointers
    A computer's memory is a sequence of bytes. We can number the bytes from 0 to the last one.
    An `address` is "a number that indicates a location in memory".
    You can think of an address as a kind of integer value. The first byte of memory has the address of 0, the next the address 1, and so on.
    Everything we put in memory has an address.
    We use the `&` operand to get the address of an object.
    We use the `*` operand to get the content of an address.
    ```C++
    int var = 17;
    int* ptr = &var; // ptr holds the address of var
    ```
    We are really close to the hardware here.

    [In-depth Pointers](https://cplusplus.com/doc/tutorial/pointers/)

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

The compiled program is Product > Show Build Folder in Finder

### Windows (Visual Studio)

1. Install Visual Studio
   1. Run Visual Studio Community Installer
   2. Select Language packs tab and flag the option `Desktop development with C++`
2. File > New Project
3. Select `Console App` and press `Next`
4. Type the Project name, choose the directory, and press `Create`
5. Press `Play` button to build and run the program

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

## Color Spaces
[ranges](https://docs.opencv.org/4.x/d8/d01/group__imgproc__color__conversions.html#gga4e0972be5de079fed4e3a10e24ef5ef0a353a4b8db9040165db4dacb5bcefb6ea:~:text=%E2%97%86-,cvtColor,-())
The conventional ranges for R, G, and B channel values are:
- 0 to 255 for CV_8U images
- 0 to 65535 for CV_16U images
- 0 to 1 for CV_32F images

## Install on Mac

1. Install [Xcode **selecting 'macOS platform' support**](https://developer.apple.com/xcode/)
2. Install [Homebrew](https://brew.sh/)
3. Install OpenCV:
   1. Open the Terminal
   2. run this command: `brew install opencv`.

The library is now installed in `/opt/homebrew/Cellar/opencv/<VERSION>` (Apple Silicon) or `/usr/local/Cellar/opencv/<VERSION>` (Intel).
Please, check and find your opencv installation folder either using Terminal or Finder (Go > Go To Folder > type the path). _If you use the Finder method, open the folder and drag it on the Terminal Icon to print its path. It will be useful during the creation of new projects in Xcode!_

## Create a new Project using Xcode

1. Open XCode.
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


Signing & Capabilities > Flag "Disable Library Validation" https://stackoverflow.com/questions/64828034/mapping-process-and-mapped-file-non-platform-have-different-team-ids


If XCode opens a new terminal page follow this procedure:
1.	In Xcode, go to the menu bar and select Product > Scheme > Edit Scheme.
2.	In the Run section on the left panel, look for the Info tab.
3.	Under Executable, you’ll see options:
   - unflag `Debug executable`

## Install on Windows




#### Requirements:
- [Install Visual Studio Community](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&passive=false&cid=2030#installvs) selecting the component **`Desktop development with C++`**
- [Install CMake](https://cmake.org/download/)


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

## Create a new Project in Visual Studio

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


## Method 2

1. Open XCode
2. Create New Project
3. Select `macOS` tab
4. Select `Command Line Tool` and press `Next`
5. Type a title, Type an Organization Identifier (i.e. `com.yourname`), Select `C++` as Language, and press `Next`
6. Choose the directory for your project
7. Link OpenCV library files
   1. right-click on the left side panel > `Add files to "YourProjectName"`
   2. Type '/', and go to the `lib` folder inside the installation opencv directory (i.e. `/opt/homebrew/Cellar/opencv/4.10.0_12/lib` )
   3. Select all the last version of the files you need for your project (i.e. `libopencv_core.4.10.0.dylib`, `libopencv_highgui.4.10.0.dylib`, and `libopencv_imgcodecs.4.10.0.dylib`)
8. Link the OpenCV Header files
   1. /opt/homebrew/Cellar/opencv/4.10.0_12/include/opencv4
   $(PROJECT_DIR)

9. Sigining & Capabilities
   1. Flag Disable Library Validation

## Basic Installation in Windows

[Get Started Guide](https://opencv.org/get-started/)

[tutorial install on windows](https://docs.opencv.org/4.x/d3/d52/tutorial_windows_install.html#tutorial_windows_gitbash_build)

1. Download  the  latest  version of OpenCV for Windows from this [link](https://github.com/opencv/opencv/releases/latest).
2. Run the exe -> Extract in `C:`
3. type in the command prompt (run as administrator)
   > setx -m OPENCV_DIR C:\opencv\build\x64\vc16
4. To use OpenCV  _dynamic  link  libraries_  (DLLs),  add  `%OPENCV_DIR%\bin`  to  your
library path. (For example, in Windows 10, right-click on your computer icon, select
Properties, and then click on Advanced System Settings. Finally, select Environment
Variables and add the OpenCV binary path to the Path variable.)