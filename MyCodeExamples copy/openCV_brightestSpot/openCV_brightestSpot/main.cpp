/**
 * @file Threshold.cpp
 * @brief Sample code that shows how to use the diverse threshold options offered by OpenCV
 * @author OpenCV team
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string> 
#include <WS2tcpip.h>

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "opencv2/tracking.hpp"


#pragma comment (lib, "ws2_32.lib")

using namespace std;
using namespace cv;
using std::cout;

/// Global variables
//threshold
int threshold_value = 240;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

//blur
int blur_value = 30;
int const max_blur_value = 100;

Mat src, src_gray, dst;
Mat tempSrc;
const char* threshold_window_name = "threshold process";
const char* input_window_name = "video input";
const char* blob_window_name = "blob detection";

const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";
const char* trackbar_blur_value = "blur value";

//find contour
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
void thresh_callback(int, void*);
const char* source_window = "Source";

Point2f targetPos;
bool targetDetected = false;
int zoneActivatedID;
bool zoneActivated;
bool zoneActivationPrevStatus;
long currentElapsedTime;
string controlMarkerID;

bool sendingMessageStatus = false;
bool sendingMessagePrevStatus = false;
bool messageSent = false;

union Vector {
	struct {
		int x;
		int y;
		int w;
		int h;
	};

	int xywh[4];
};

class timer {
private:
	unsigned long begTime;
	bool isRunningStatus;
public:
	

	void start() {
		begTime = clock();
		cout << "Timer restarted." << endl;
	}

	unsigned long getBeginTime() {
		return begTime;
	}

	unsigned long elapsedTime() {
		return ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
	}

	bool isTimeout(unsigned long seconds) {
		return seconds >= elapsedTime();
	}

	void setRunningStatus(bool _status) {
		isRunningStatus = _status;
	}

	bool isRunning() {
		return isRunningStatus;
	}
};

void clientUDPsendMsg(string _msg) {
	// Startup Winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0) {
		cout << "Can't start Winsock!" << wsOk;
		return;
	}

	// create a hint structur for the server
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(55000);
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

	// Socket creation
	string s(_msg);
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

	// Write out to that socket
	int sendOk = sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR) {
		cout << "That didn't work! " << WSAGetLastError() << endl;
	}

	// Close the socket
	closesocket(out);
	// Shutdown winsock
	WSACleanup();
}

//![Threshold_Demo]
/**
 * @function Threshold_Demo
 */
static void Threshold_Demo(int, void*)
{
	/* 0: Binary
	 1: Binary Inverted
	 2: Threshold Truncated
	 3: Threshold to Zero
	 4: Threshold to Zero Inverted
	*/

	threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
	imshow(threshold_window_name, dst);

	createTrackbar("Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
	
}
//![Threshold_Demo]

//![blur function test]
void applyBlur(int, void*) {
	if (blur_value <= 2) blur_value = 2;
	blur(src_gray, src_gray, Size(blur_value, blur_value)); // blur it
}
//![blur function test]

/** @function thresh_callback */
void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using canny
	Canny(dst, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));


	/// Get the moments
	vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	///  Get the mass centers:
	vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	/// Draw contours
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}

	/// Show in a window
	imshow(blob_window_name, drawing);

	if (contours.size() > 0) {
		/// Calculate the area with the moments 00 and compare with the result of the OpenCV function
		// printf("\t Info: Area and Contour Length \n");
		for (int i = 0; i < contours.size(); i++)
		{
			// printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f   \n", i, mu[i].m00, contourArea(contours[i]), arcLength(contours[i], true));
			// cout << "id: " << i << " - x: " << mc[i].x << " - y: " << mc[i].y << endl;
		}
		
		targetDetected = true;
		targetPos = mc[0];
	}
	else {
		targetDetected = false;
	}

}

void displayTimer(const Mat& _matrix) {
	putText(_matrix, to_string(currentElapsedTime), Point2f((_matrix.size().width / 8 * 7) , 40), FONT_HERSHEY_PLAIN, 3, Scalar(255, 255, 255), 2, 8, false);
}

void zoneCheckTesta(int, void*) {
	Mat zoneGraphics = Mat::zeros(dst.size(), CV_8UC3);

	///define zones
// [testa]
	Vector* zTestaCoordVec = new Vector();
	zTestaCoordVec->x = 125;
	zTestaCoordVec->y = 200;
	zTestaCoordVec->w = 120;
	zTestaCoordVec->h = 80;
	Rect zTestaRect = Rect(zTestaCoordVec->x, zTestaCoordVec->y, zTestaCoordVec->w, zTestaCoordVec->h);

	Vector* zBustoCoordVec = new Vector();
	zBustoCoordVec->x = 320;
	zBustoCoordVec->y = 180;
	zBustoCoordVec->w = 260;
	zBustoCoordVec->h = 120;
	Rect zBustoRect = Rect(zBustoCoordVec->x, zBustoCoordVec->y, zBustoCoordVec->w, zBustoCoordVec->h);
	// end [testa]

	Rect idBckgrnd((zoneGraphics.size().width / 4) * 3, 0, 50, 50);
	Rect messageSentIcon((zoneGraphics.size().width / 8 * 7), 0, 50, 50);

	rectangle(zoneGraphics, zTestaRect, Scalar(0, 0, 255), 1, 8, 0); // stroke
	rectangle(zoneGraphics, zBustoRect, Scalar(0, 255, 0), 1, 8, 0); // stroke


	if (targetDetected) {
		// cout << "zoneRect2.x: " << z2coordVec->x << " - zoneRect2.y: " << z2coordVec->y << " - zoneRect2.w: " << z2coordVec->w << " - zoneRect2.h: " << z2coordVec->y; 
		//circle(zoneGraphics, Point2f(zoneGraphics.size().width / 2, zoneGraphics.size().height / 2), 4, Scalar(0, 0, 255), -1, 8, 0);
		circle(zoneGraphics, targetPos, 4, Scalar(0, 0, 255), -1, 8, 0);
		if (targetPos.x > zTestaCoordVec->x && targetPos.y > zTestaCoordVec->y
			&& targetPos.x < (zTestaCoordVec->x + zTestaCoordVec->w) && targetPos.y < (zTestaCoordVec->y + zTestaCoordVec->h)) {
			zoneActivatedID = 0;
			controlMarkerID = to_string(zoneActivatedID);
			zoneActivated = true;
			if (zoneActivated != zoneActivationPrevStatus) {
				cout << "The target is in the zone " << zoneActivatedID << " !" << endl;
			}
			rectangle(zoneGraphics, zTestaRect, Scalar(0, 0, 255), -1, 8, 0); // filled
		}
		else if (targetPos.x > zBustoCoordVec->x && targetPos.y > zBustoCoordVec->y
			&& targetPos.x < (zBustoCoordVec->x + zBustoCoordVec->w) && targetPos.y < (zBustoCoordVec->y + zBustoCoordVec->h)) {
			zoneActivatedID = 1;
			controlMarkerID = to_string(zoneActivatedID);
			zoneActivated = true;
			if (zoneActivated != zoneActivationPrevStatus) {
				cout << "The target is in the zone " << zoneActivatedID << " !" << endl;
			}
			rectangle(zoneGraphics, zBustoRect, Scalar(0, 255, 0), -1, 8, 0); // filled
		}
		else {
			controlMarkerID = "X";
			zoneActivated = false;
			//zoneActivationPrevStatus = zoneActivated;
		}

		circle(zoneGraphics, targetPos, 4, Scalar(255, 255, 255), -1, 8, 0);
	}
	else {
		controlMarkerID = "X";
		zoneActivated = false;
	}

	rectangle(zoneGraphics, idBckgrnd, Scalar(255, 0, 0), -1, 8, 0);
	putText(zoneGraphics, controlMarkerID, Point2f((zoneGraphics.size().width / 4) * 3, 40), FONT_HERSHEY_PLAIN, 3, Scalar(255, 255, 255), 2, 8, false);

	if (messageSent) {
		rectangle(zoneGraphics, messageSentIcon, Scalar(0, 0, 255), -1, 8, 0);
	}
	//if (zoneActivated)
	displayTimer(zoneGraphics);


	imshow("zone check", zoneGraphics);
}

void zoneCheck(int, void*) {

	Mat zoneGraphics = Mat::zeros(dst.size(), CV_8UC3);
#pragma region zoneCoordVectorsDefinition
	// creo vettori con le coordinate delle zone;
	Vector* z0coordVec = new Vector();
	z0coordVec->x = zoneGraphics.size().width / 2;
	z0coordVec->y = 20;
	z0coordVec->w = zoneGraphics.size().width / 4;
	z0coordVec->h = (zoneGraphics.size().height - 50);
	Vector* z1coordVec = new Vector();
	z1coordVec->x = 10;
	z1coordVec->y = 20;
	z1coordVec->w = (zoneGraphics.size().width / 2) - 50;
	z1coordVec->h = (zoneGraphics.size().height / 2) - 50;
	Vector* z2coordVec = new Vector();
	z2coordVec->x = 10;
	z2coordVec->y = (zoneGraphics.size().height / 2) + 10;
	z2coordVec->w = (zoneGraphics.size().width / 2) - 50;
	z2coordVec->h = (zoneGraphics.size().height / 2) - 50;
	
#pragma endregion
	// control GUI
	Rect idBckgrnd((zoneGraphics.size().width / 4) * 3, 0, 50, 50);
	Rect messageSentIcon((zoneGraphics.size().width / 8 * 7), 0, 50, 50);

	Rect zoneRect0 = Rect(z0coordVec->x, z0coordVec->y, z0coordVec->w, z0coordVec->h);
	Rect zoneRect1 = Rect(z1coordVec->x, z1coordVec->y, z1coordVec->w, z1coordVec->h);
	Rect zoneRect2 = Rect(z2coordVec->x, z2coordVec->y, z2coordVec->w, z2coordVec->h);

	//Rect zoneRect1 = Rect(10, 20, (zoneGraphics.size().width / 2)-20, (zoneGraphics.size().height / 2) - 20);
	//Rect zoneRect2 = Rect(10, (zoneGraphics.size().height / 2) + 10, (zoneGraphics.size().width / 2) - 20, (zoneGraphics.size().height / 2) - 20);
	//Rect zoneRect3 = Rect(zoneGraphics.size().width / 2, 20, zoneGraphics.size().width / 4, (zoneGraphics.size().height - 30));
	
	rectangle(zoneGraphics, zoneRect0, Scalar(0, 0, 255), 1, 8, 0); // stroke
	rectangle(zoneGraphics, zoneRect1, Scalar(0, 255, 0), 1, 8, 0); // stroke
	rectangle(zoneGraphics, zoneRect2, Scalar(255, 0, 0), 1, 8, 0); // stroke
	
	if (targetDetected) {
		
		// cout << "zoneRect2.x: " << z2coordVec->x << " - zoneRect2.y: " << z2coordVec->y << " - zoneRect2.w: " << z2coordVec->w << " - zoneRect2.h: " << z2coordVec->y; 
		//circle(zoneGraphics, Point2f(zoneGraphics.size().width / 2, zoneGraphics.size().height / 2), 4, Scalar(0, 0, 255), -1, 8, 0);
		circle(zoneGraphics, targetPos, 4, Scalar(0, 0, 255), -1, 8, 0);
		if (targetPos.x > z0coordVec->x && targetPos.y > z0coordVec->y
			&& targetPos.x < (z0coordVec->x + z0coordVec->w) && targetPos.y < (z0coordVec->y + z0coordVec->h)) {
			zoneActivatedID = 0;
			controlMarkerID = to_string(zoneActivatedID);
			zoneActivated = true;
			if (zoneActivated != zoneActivationPrevStatus) {
				cout << "The target is in the zone " << zoneActivatedID << " !" << endl;
			}
			rectangle(zoneGraphics, zoneRect0, Scalar(0, 0, 255), -1, 8, 0); // filled
		}
		else if (targetPos.x > z1coordVec->x && targetPos.y > z1coordVec->y
			&& targetPos.x < (z1coordVec->x + z1coordVec->w) && targetPos.y < (z1coordVec->y + z1coordVec->h) ) {
			zoneActivatedID = 1;
			controlMarkerID = to_string(zoneActivatedID);
			zoneActivated = true;
			if (zoneActivated != zoneActivationPrevStatus) {
				cout << "The target is in the zone " << zoneActivatedID << " !" << endl;
			}
			rectangle(zoneGraphics, zoneRect1, Scalar(0, 255, 0), -1, 8, 0); // filled
		}
		else if (targetPos.x > z2coordVec->x && targetPos.y > z2coordVec->y
			&& targetPos.x < (z2coordVec->x + z2coordVec->w) && targetPos.y < (z2coordVec->y + z2coordVec->h)) {
			zoneActivatedID = 2;
			controlMarkerID = to_string(zoneActivatedID);
			zoneActivated = true;
			if (zoneActivated != zoneActivationPrevStatus) {
				cout << "The target is in the zone " << zoneActivatedID << " !" << endl;
			}
			rectangle(zoneGraphics, zoneRect2, Scalar(255, 0, 0), -1, 8, 0); // filled
		}
		else {
			controlMarkerID = "X";
			zoneActivated = false;
			
			//zoneActivationPrevStatus = zoneActivated;
		}

		circle(zoneGraphics, targetPos, 4, Scalar(255, 255, 255), -1, 8, 0);
	}
	else {
		controlMarkerID = "X";
		zoneActivated = false;
	}



	rectangle(zoneGraphics, idBckgrnd, Scalar(255, 0, 0), -1, 8, 0);
	putText(zoneGraphics, controlMarkerID, Point2f((zoneGraphics.size().width / 4) * 3, 40), FONT_HERSHEY_PLAIN, 3, Scalar(255, 255, 255), 2, 8, false);
	
	

	if (messageSent) {
		rectangle(zoneGraphics, messageSentIcon, Scalar(0, 0, 255), -1, 8, 0);
	}

	//if (zoneActivated)
		displayTimer(zoneGraphics);
		

	imshow("zone check", zoneGraphics);

}


/**
 * @function main
 */
int main(int argc, char** argv)
{
	timer t;
	t.start();


	///define zones
	// [testa]
	Vector* zTestaCoordVec = new Vector();
	zTestaCoordVec->x = 125;
	zTestaCoordVec->y = 200;
	zTestaCoordVec->w = 120;
	zTestaCoordVec->h = 80;
	Rect zTestaRect = Rect(zTestaCoordVec->x, zTestaCoordVec->y, zTestaCoordVec->w, zTestaCoordVec->h);

	Vector* zBustoCoordVec = new Vector();
	zBustoCoordVec->x = 320;
	zBustoCoordVec->y = 180;
	zBustoCoordVec->w = 260;
	zBustoCoordVec->h = 120;
	Rect zBustoRect = Rect(zBustoCoordVec->x, zBustoCoordVec->y, zBustoCoordVec->w, zBustoCoordVec->h);
	//! [testa]


	// [input]
	/// still image
	//! [load]
	//String imageName("img_brightestSpot_test1.JPG"); // by default
	//if (argc > 1)
	//{
	//	imageName = argv[1];
	//}
	//src = imread(imageName, IMREAD_COLOR); // Load an image
	//if (src.empty())
	//{
	//	cout << "Cannot read image: " << imageName << std::endl;
	//	return -1;
	//}

	/// video camera in
	// VERSION VideoCapture ok
	 VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;
	
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 768);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	//! [input]

	

	// [window]
	namedWindow(input_window_name, WINDOW_AUTOSIZE);
	
	cvMoveWindow(input_window_name, 0, 10);
	namedWindow(threshold_window_name, WINDOW_AUTOSIZE);
	cvMoveWindow(threshold_window_name, 700, 10);
	namedWindow(blob_window_name, WINDOW_AUTOSIZE);
	cvMoveWindow(blob_window_name, 0, 600);
	namedWindow("zone check", WINDOW_AUTOSIZE);
	cvMoveWindow("zone check", 700, 600);
	//! [window]

	// [define mask]
	Rect maskRect1 = Rect(0, 0, 768, 180);
	Rect maskRect2 = Rect(0, 480 - 180, 768, 480-180);
	//! [define mask]

	for (;;){

		//! [frame load]
		cap >> src;
		
		// [draw mask]
		rectangle(src, maskRect1, Scalar(255), -1, 8, 0);
		rectangle(src, maskRect2, Scalar(255), -1, 8, 0);
		//! [draw mask]

		// img processing
		cvtColor(src, src_gray, COLOR_BGR2GRAY); // Convert the image to Gray
		applyBlur(0, 0);

		// [trackbars]
		createTrackbar(trackbar_type,
			threshold_window_name, &threshold_type,
			max_type, Threshold_Demo); // Create Trackbar to choose type of Threshold

		createTrackbar(trackbar_value,
			threshold_window_name, &threshold_value,
			max_value, Threshold_Demo); // Create Trackbar to choose Threshold value

		createTrackbar(trackbar_blur_value,
			input_window_name, &blur_value,
			max_blur_value, applyBlur); // Create Trackbar to choose Blur value
		//! [trackbar]

		/// test zones on videoInput
		/*rectangle(src_gray, zTestaRect, Scalar(255), 1, 8, 0);
		rectangle(src_gray, zBustoRect, Scalar(255), 1, 8, 0);*/
		
		//rectangle(src_gray, zTestaRect, Scalar(255), 1, 8, 0);
		//rectangle(src_gray, zBustoRect, Scalar(255), 1, 8, 0);

		//display video_input
		imshow(input_window_name, src_gray);
		
		bool currentActivation = zoneActivated;
		if (zoneActivated) {
			
			if (currentActivation != zoneActivationPrevStatus) {
				t.start(); // restart
			}

			if (t.elapsedTime() >= 1) {
				sendingMessageStatus = true; 
				if (sendingMessageStatus != sendingMessagePrevStatus) {
					cout << "message sent: " << zoneActivatedID << endl;
					clientUDPsendMsg(to_string(zoneActivatedID));
					messageSent = true;
				}
				sendingMessagePrevStatus = sendingMessageStatus;
			}
			else {
				
				sendingMessageStatus = false;
				sendingMessagePrevStatus = sendingMessageStatus;
			}

			currentElapsedTime = t.elapsedTime();

			zoneActivationPrevStatus = currentActivation;
		}
		else {
			currentElapsedTime = 0;
			if (currentActivation != zoneActivationPrevStatus) {
				
				cout << "active zone: none." << endl;
			}
			messageSent = false;
			zoneActivationPrevStatus = currentActivation;
		}

		// call functions
		Threshold_Demo(0, 0); // Call the function to initialize
		thresh_callback(0, 0);
		//zoneCheck(0, 0);
		zoneCheckTesta(0, 0);
		
		/// Wait until user finishes program
		if (waitKey(30) >= 0) break;
	}
	return 0;
}
