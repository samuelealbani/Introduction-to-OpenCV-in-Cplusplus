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


## OpenCV

### Fundamental OpenCV Data Structure

#### cv::Mat

### Drawing functions

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

### Canny threshold
```cpp
Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
```
#### Example

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
  CommandLineParser parser( argc, argv, "{@input | fruits.jpg | input image}" );
  src = imread( samples::findFile( parser.get<String>( "@input" ) ), IMREAD_COLOR ); // Load an image

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

### Mapping
```cpp
x = (inValue - minInRange) / (maxInRange - minInRange);
result = minOutRange + (maxOutRange - minOutRange) * x;
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