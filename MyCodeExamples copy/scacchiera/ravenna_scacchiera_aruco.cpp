#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/calib3d.hpp>
#include <opencv2/video.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string> 
#include <stdio.h>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "pugixml.hpp"
#include <chrono>
#include <ctime>  
#include <iomanip>

using namespace cv;
using namespace std;
using boost::asio::ip::udp;

// timer
int waiting_time;
class timer {
private:
	unsigned long begTime;
public:

	void start() {
		begTime = clock();
	}

	unsigned long elapsedTime() {
		return ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
	}

	bool isTimeout(unsigned long seconds) {
		return seconds >= elapsedTime();
	}
};

timer t;
//[end] timer

// aruco
const float calibrationSquareDimension = 0.01905f; // meters
const float arucoSquareDimension = 0.1016f; // meters
const Size chessboardDimensions = Size(6, 9);
int calibrationStatus;
int is_fileCalibration_exist(const char *fileName) {
	std::ifstream infile(fileName);
	if (infile.good()) {
		return 1;
	}
	else {
		return 0;
	}
	// return infile.good(); // if bool type
}
void createKnownBoardPosition(Size boardSize, float squareEdgeLength, vector<Point3f>& corners) {
	for (int i = 0; i < boardSize.height; i++) {
		for (int j = 0; j < boardSize.width; j++) {
			corners.push_back(Point3f(j * squareEdgeLength, i * squareEdgeLength, 0.0f));
		}
	}
}
void getChessboardCorners(vector<Mat> images, vector<vector<Point2f>>&allFoundCorners, bool showResult = false) {
	for (vector<Mat>::iterator iter = images.begin(); iter != images.end(); iter++) {
		vector<Point2f> pointBuf;
		bool found = findChessboardCorners(*iter, Size(9, 6), pointBuf, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

		if (found) {
			allFoundCorners.push_back(pointBuf);
		}
		if (showResult) {
			drawChessboardCorners(*iter, Size(9, 6), pointBuf, found);
			imshow("LookingforCorners", *iter);
			waitKey(0);
		}
	}
}
void cameraCalibration(vector<Mat> calibrationImages, Size boardSize, float squareEdgeLength, Mat& cameraMatrix, Mat& distanceCoefficients) {
	vector<vector < Point2f>> checkerboardImagePoints;
	getChessboardCorners(calibrationImages, checkerboardImagePoints, false);

	vector<vector < Point3f >> worldSpaceCornerPoints(1);

	createKnownBoardPosition(boardSize, squareEdgeLength, worldSpaceCornerPoints[0]);

	worldSpaceCornerPoints.resize(checkerboardImagePoints.size(), worldSpaceCornerPoints[0]);

	vector<Mat> rVectors, tVectors;
	distanceCoefficients = Mat::zeros(8, 1, CV_64F);

	calibrateCamera(worldSpaceCornerPoints, checkerboardImagePoints, boardSize, cameraMatrix, distanceCoefficients, rVectors, tVectors);
}
bool savedCameraCalibration(string name, Mat cameraMatrix, Mat distanceCoefficients) {
	ofstream outStream(name);
	if (outStream) {
		uint16_t rows = cameraMatrix.rows;
		uint16_t columns = cameraMatrix.cols;

		outStream << rows << endl;
		outStream << columns << endl;

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				double value = cameraMatrix.at<double>(r, c);
				outStream << value << endl;
			}
		}

		rows = distanceCoefficients.rows;
		columns = distanceCoefficients.cols;

		outStream << rows << endl;
		outStream << columns << endl;

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				double value = distanceCoefficients.at<double>(r, c);
				outStream << value << endl;
			}
		}

		outStream.close();
		return true;
	}

	return false;
}
bool loadCameraCalibrations(string name, Mat& cameraMatrix, Mat& distanceCoefficients) {
	ifstream inStream(name);
	if (inStream) {
		uint16_t rows;
		uint16_t columns;

		inStream >> rows;
		inStream >> columns;

		cameraMatrix = Mat(Size(columns, rows), CV_64F);

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				double read = 0.0f;
				inStream >> read;
				cameraMatrix.at<double>(r, c) = read;
				std::cout << cameraMatrix.at<double>(r, c) << "\n";
			}
		}
		// distance Coefficients
		inStream >> rows;
		inStream >> columns;

		distanceCoefficients = Mat::zeros(rows, columns, CV_64F);
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				double read = 0.0f;
				inStream >> read;
				distanceCoefficients.at<double>(r, c) = read;
				cout << distanceCoefficients.at<double>(r, c) << "\n";
			}
		}
		inStream.close();
		return true;
	}
	return false;
}
void cameraCalibrationProcess(Mat& cameraMatrix, Mat & distanceCoefficients) {
	Mat frame;
	Mat drawToFrame;

	vector<Mat> savedImages;

	vector<vector < Point2f>> markerCorners, rejectedCandidates;

	VideoCapture vid(0);
	if (!vid.isOpened()) {
		return;
	}

	int framesPerSecond = 20;

	namedWindow("Webcam", WINDOW_AUTOSIZE);

	while (true) {
		if (!vid.read(frame)) {
			break;
		}
		vector<Vec2f> foundPoints;
		bool found = false;

		found = findChessboardCorners(frame, chessboardDimensions, foundPoints, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);
		frame.copyTo(drawToFrame);
		drawChessboardCorners(drawToFrame, chessboardDimensions, foundPoints, found);

		if (found) {
			imshow("Webcam", drawToFrame);
		}
		else {
			imshow("Webcam", frame);
		}
		char character = waitKey(1000 / framesPerSecond);


		switch (character) {
		case ' ': // space-bar key
			//saving image
			if (found) {
				Mat temp;
				frame.copyTo(temp);
				savedImages.push_back(temp);
				std::cout << "saved image n° " << savedImages.size() << endl;
			}
			break;

		case 13: // enter key
			//start calibration
			if (savedImages.size() > 15) {
				std::cout << "Calibration process started\n" << endl;
				cameraCalibration(savedImages, chessboardDimensions, calibrationSquareDimension, cameraMatrix, distanceCoefficients);
				savedCameraCalibration("./data/CameraCalibrationResult", cameraMatrix, distanceCoefficients);
				std::cout << "Calibration done and file saved" << endl;
				return; // exit from callback function
			}
			else {
				cout << "files saved are not enough! please save at least another " << (15 - savedImages.size()) << " images!\n" << endl;
			}
			//std::std::cout << "press Esc to exit or do it again" << endl;
			break;
		case 27: // exit key
			//exit
			return;
			break;
		}
	}
}
//[end] aruco

// boost_UDP client
//UDP
string ip_out, out_port;
void boostClientUDP(string _msg) {
	try {

		boost::asio::io_context io_context;

		udp::resolver resolver(io_context);
		udp::endpoint receiver_endpoint =
			*resolver.resolve(udp::v4(), ip_out, out_port).begin(); // ("IP", "port")

		udp::socket socket(io_context);
		socket.open(udp::v4());

		socket.send_to(boost::asio::buffer(_msg), receiver_endpoint);
		std::cout << "udp client:\tmessage="<<_msg <<"\tdestination="<< ip_out << ":" << out_port <<"\tstatus=SENT" << endl;

	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
//[end] boost_UDP client

// threshold vars
int threshold_value;
int threshold_type;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;
int save_value = 0;
Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";
static void Threshold_Demo(int, void*)
{
	/* 0: Binary
	 1: Binary Inverted
	 2: Threshold Truncated
	 3: Threshold to Zero
	 4: Threshold to Zero Inverted
	*/
	threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
	imshow(window_name, dst);
}
const char* trackbar_save = "Save";
Mat segmented;
//[end] threshold vars

// output window var
const char* output_window_name = "OUTPUT";
const char* trackbar_switchBackgroundSubtraction = "Background subtraction I/O"; // serve?
//[end] output window var

// zone sensibili vars
std::vector<std::array<int, 5 >> zoneSettings;
std::vector<string> zoneIds;
vector<Rect> zoneRects;
int videoNumToPlay;
vector<vector<std::array<int, 2 >>> zone_tag_matches;
// vector<vector<int>> zone_tag_matches;
//[end] zone sensibili vars

// marker detenction vars
int markerDetectedID = 0;
string controlMarkerID;
bool new_marker_detected = false;
bool timerIsRunning = false;
bool sendingMessageStatus = false;
bool sendingMessagePrevStatus = false;
vector<int> prevDetectedIDs; //  il current è markerIds
String active_tag_id;
int active_tag_index;
//[end] marker detenction vars

// control GUI vars
String console_active_tag_id;
Rect idBckgrnd(0, 0, 50, 50);
Rect videoStatusIcon(150, 0, 50, 50);
//[end] control GUI

//mouse click function
void CallBackFunc(int event, int x, int y, int flags, void* userdata) {
	if (event == EVENT_LBUTTONDOWN) {
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_RBUTTONDOWN) {
		cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MBUTTONDOWN) {
		cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_LBUTTONDBLCLK) {
		cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
	}
}
//[end] mouse click function

int main(int argc, char*argv[])
{
	// xml settings loading
	pugi::xml_document xml_doc;
	if (!xml_doc.load_file("./data/settings.xml")) {
		std::cout << "file settings loading error" << endl;
		return -1;
	}
	else {
		std::cout << "Loading file setting...\n" << endl;
	}
	std::cout << "Setting Zone Sensibili:" << endl;
	pugi::xml_node xml_zones_node = xml_doc.child("settings").child("zone_settings");
	for (pugi::xml_node zone = xml_zones_node.first_child(); zone; zone = zone.next_sibling()) {
		std::cout << "Zona:";
		for (pugi::xml_attribute attr = zone.first_attribute(); attr; attr = attr.next_attribute()) {
			std::cout << " " << attr.name() << "=" << attr.value();
		}
		std::cout << endl;

		string name, id, x, y, w, h;
		// name = zone.attribute("name").value(); // per ora inutilizzato
		id = zone.attribute("Id").value();
		x = zone.attribute("x").value();
		y = zone.attribute("y").value();
		w = zone.attribute("w").value();
		h = zone.attribute("h").value();

		array<int, 5> currentSettings{ stoi(id), stoi(x), stoi(y), stoi(w), stoi(h) }; // non carico il nome
		zoneSettings.push_back(currentSettings);
		zoneIds.push_back(id);
	}
	// creo il vettore di rettangoli secondo i parametri delle zone sensibili
	for (string i : zoneIds) {  // l'index dei rettangoli in zoneRects è uguale all'ID della zona
		Rect currRect = Rect(zoneSettings[stoi(i)][1], zoneSettings[stoi(i)][2], zoneSettings[stoi(i)][3], zoneSettings[stoi(i)][4]);
		zoneRects.push_back(currRect);
	}
	pugi::xml_node xml_zone_tag = xml_doc.child("settings").child("tags");
	for (pugi::xml_node zone_tag = xml_zone_tag.first_child(); zone_tag; zone_tag = zone_tag.next_sibling()) {
		vector<std::array<int, 2 >> current_tag_association;
		for (pugi::xml_node match = zone_tag.first_child(); match; match = match.next_sibling()) {
			string z_id, v_n;
			z_id = match.attribute("zone_id").value();
			v_n = match.attribute("video_n").value();
			array<int, 2> current_match{ stoi(z_id), stoi(v_n) };
			current_tag_association.push_back(current_match);
		}
		zone_tag_matches.push_back(current_tag_association);
	}
	std::cout << "\ntags settings loaded: " << endl;
	int d_count = 0;
	for (vector<std::array<int, 2 >> i : zone_tag_matches) {
		std::cout << "tag " << d_count << ": [ ";
		for (std::array<int, 2 > j : i) {
			std::cout << " [zone_id=" << j[0] << ", video_n=" << j[1] << "] ";
		}
		std::cout << " ]" << std::endl;
		d_count++;
	}

	pugi::xml_node udp_node = xml_doc.child("settings").child("UDP_Player");
	ip_out = udp_node.attribute("IP").value();
	out_port = udp_node.attribute("Port").value();
	std::cout << "\nSetting UDP Player loaded: " << "IP=" << ip_out << " Port=" << out_port << endl;

	pugi::xml_node timer_node = xml_doc.child("settings").child("timer");
	waiting_time = stoi(timer_node.attribute("wait_sec").value());
	std::cout << "\nTimer settings loaded: " << "waiting_time=" << waiting_time << endl;

	pugi::xml_node segmentation_node = xml_doc.child("settings").child("segmentation");
	threshold_type = stoi(segmentation_node.attribute("type").value());
	threshold_value = stoi(segmentation_node.attribute("value").value());
	std::cout << "\nSegmentation settings loaded: " << "type=" << threshold_type << "value=" << threshold_value << endl;

	std::cout << "\nfile setting loading: done.\n-----------\n" << std::endl;

	//aruco
	vector<int> markerIds;
	vector<vector < Point2f>> markerCorners, rejectedCandidates;
	aruco::DetectorParameters parameters;
	Ptr<aruco::Dictionary> markerDictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);

	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
	Mat distanceCoefficients;

	calibrationStatus = is_fileCalibration_exist("./data/CameraCalibrationResult"); // verify existance of calibration file
	switch (calibrationStatus) {
	case(0):
		std::cout << "calibration file not found \n" << endl;
		std::cout << "please calibrate your camera... \n " << "press bar-space for save images (among 15 - 20 timese);\nthen press enter key for start calibration \n(press exit to quit process)\n \n " << endl;
		cameraCalibrationProcess(cameraMatrix, distanceCoefficients);
		calibrationStatus = is_fileCalibration_exist("./data/CameraCalibrationResult");
		break;
	default:
		std::cout << "calibration file found!" << endl;
		break;
	}

	std::cout << "\nI'm loading calibration file:\n" << endl;
	loadCameraCalibrations("./data/CameraCalibrationResult", cameraMatrix, distanceCoefficients);

	std::cout << "\nI'm starting the webcam monitoring...\n" << endl;
	vector<Vec3d> rotationVectors, translationVectors;
	Mat arucoFrame;
	//[end] aruco

	Mat frame;
	//--- INITIALIZE VIDEOCAPTURE	
	VideoCapture cap;
	// open the default camera using default API
	// cap.open(0);
	// OR advance usage: select any API backend
	int deviceID = 0;             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
	// open selected camera using selected API
	cap.open(deviceID + apiID);
	// check if we succeeded
	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return -1;
	}

	//--- GRAB AND WRITE LOOP
	std::cout << "Start grabbing" << endl
		<< "Press any key to terminate" << endl;
	for (;;)
	{
		//set the callback function for any mouse event on output window
		setMouseCallback(output_window_name, CallBackFunc, NULL);

		// wait for a new frame from camera and store it into 'frame'
		cap.read(frame);
		// check if we succeeded
		if (frame.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		
		// cap.read(src);
		// flip(frame, frame, 1);

		// prepare_output window
		namedWindow(output_window_name, WINDOW_AUTOSIZE); // Create a window to display results
		createTrackbar(trackbar_type,
			output_window_name, &threshold_type,
			max_type/*, Threshold_Demo*/); // Create a Trackbar to choose type of Threshold
		createTrackbar(trackbar_value,
			output_window_name, &threshold_value,
			max_value/*, Threshold_Demo*/); // Create a Trackbar to choose Threshold value
		createTrackbar(trackbar_save,
			output_window_name, &save_value,
			1); // Create a Trackbar to save segmentation setting

		// segmentation_process
		cvtColor(frame, src_gray, COLOR_BGR2GRAY); // Convert the image to Gray
		threshold(src_gray, segmented, threshold_value, max_binary_value, threshold_type); // apply threshold

		// aruco_detenction
		aruco::detectMarkers(segmented, markerDictionary, markerCorners, markerIds); // detect on segmented frame and add tags id to markerIds
		aruco::estimatePoseSingleMarkers(markerCorners, arucoSquareDimension, cameraMatrix, distanceCoefficients, rotationVectors, translationVectors);
		Mat out_rgb(segmented.size(), CV_8UC3); // create color matrix // CV_8UC3 or CV_64F
		cvtColor(segmented, out_rgb, COLOR_GRAY2RGB); // convert grayscale to color image (per vedere gli assi del marker a colori)
		// draw axis on marker
		for (int i = 0; i < markerIds.size(); i++) {
			aruco::drawAxis(out_rgb, cameraMatrix, distanceCoefficients, rotationVectors[i], translationVectors[i], 0.1f);
		}
		//[end] aruco_detenction

		// check
		// trova il nuovo marker sulla board
		if (markerIds.size() != prevDetectedIDs.size()) {
			std::cout << "------------------\n" << markerIds.size() << " tag(s) on board." << endl;
			if (prevDetectedIDs.size() > markerIds.size()) { // se gli attuali sono tag sono meno di prima
				new_marker_detected = false;
				console_active_tag_id = "X";
				timerIsRunning = false; // fermo il timer
				//std::cout << "ci sono meno tag di prima\nnon ci sono tag attivi attualmente";

			}
			if (markerIds.size() > 0) {
				//sort(markerIds.begin(), markerIds.end()); // riordino i tag degli id rilevati
				std::cout << "tag(s)_ID detected:";
				for (int i = 0; i < markerIds.size(); ++i) {
					std::cout << markerIds[i] << " ";
				}
				std::cout << "\n";

				// trova il nuovo
				if (prevDetectedIDs.size() == 0) { // prima non ce n'erano?		
					// std::cout << "prevDetectedIDs era vuoto" << endl;
					active_tag_id = to_string(markerIds[0]); // il nuovo marker è l'unico e primo rilevato tra i presenti (se più di uno all'avvio)					
					console_active_tag_id = active_tag_id;
					active_tag_index = 0;
					new_marker_detected = true;
					// std::cout << "NEW TAG ON BOARD" << endl;
					std::cout << "active_tag_id=" << active_tag_id << endl;
				}
				else {
					if (markerIds.size() > prevDetectedIDs.size()) { // ce ne sono di più ?
						bool found_new = false;
						for (int i = 0; i < prevDetectedIDs.size(); ++i) { // cerco se è nelle prime posizioni
							if (markerIds[i] != prevDetectedIDs[i]) {
								active_tag_id = to_string(markerIds[i]); // il nuovo marker è quello diverso rispetto ai rilevati precedentemente
								active_tag_index = i;
								// std::cout << "trovato nelle prime posizione" << endl;
								found_new = true;
								break;
							}
						}
						if (!found_new) { // se non era nelle prime posizioni 
							active_tag_id = to_string(markerIds[markerIds.size() - 1]); // il nuovo è l'ultimo del vettore
							active_tag_index = markerIds.size() - 1;
							new_marker_detected = true;
							// std::cout << "assegnato l'ultimo" << endl;
						}
						// std::cout << "NEW TAG ON BOARD" << endl;
						new_marker_detected = true;
						console_active_tag_id = active_tag_id;
						std::cout << "active_tag_id=" << active_tag_id << endl;
					}
				}
				//[end] trova il nuovo
			}
			else {
				console_active_tag_id = "X";
			}
			// ricreo e aggiorno il vettore dei prevDetectedIDs con il corrente
			prevDetectedIDs.clear();
			prevDetectedIDs.resize(markerIds.size());
			prevDetectedIDs = markerIds; // ilproblema di questo è che aggiunge nel prevDetectedIDs eventuali tag non ammessi

			std::cout << "\n";
		}

		if (new_marker_detected && markerIds.size() > 0) {
			// find center point of the active marker (the new one)
			Point2f center_active_marker = Point2f(((markerCorners[active_tag_index][0].x + markerCorners[active_tag_index][2].x) / 2), ((markerCorners[active_tag_index][0].y + markerCorners[active_tag_index][2].y) / 2));
			if (stoi(active_tag_id) < zone_tag_matches.size()) {
				putText(out_rgb, "A", center_active_marker, FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 0, 255), 1, 8, false);

				// controlla se il marker attivo è in una delle sue posizioni assegnate
				for (int i = 0; i < zone_tag_matches[stoi(active_tag_id)].size(); ++i) {
				// for (int i = 0; i < 2; ++i) {
					int zone_id_assigned = zone_tag_matches[stoi(active_tag_id)][i][0];

					if (center_active_marker.x > zoneRects[zone_id_assigned].x
						&& center_active_marker.x < zoneRects[zone_id_assigned].x + zoneRects[zone_id_assigned].width
						&& center_active_marker.y > zoneRects[zone_id_assigned].y
						&& center_active_marker.y < zoneRects[zone_id_assigned].y + zoneRects[zone_id_assigned].height) {
						
						std::time_t const now_c = std::time(NULL);
						std::cout << std::put_time(std::localtime(&now_c), "%F %T") << "\t-->\t";
						cout << "tag " << active_tag_id <<" is on zone " << zone_id_assigned ;
						videoNumToPlay = zone_tag_matches[stoi(active_tag_id)][i][1];
						timerIsRunning = true;
						t.start();
						new_marker_detected = false;
						cout << "\t-->\ttimer started!" << endl;
						break;
					}
				}
			}
			else {
				std::cout << "active_tag_id unknown" << endl;
			}			
		}
		//[end] check

		// GUI _scrivo il numero del marker attivo
		rectangle(out_rgb, idBckgrnd, Scalar(255, 255, 255), -1, 8, 0);
		putText(out_rgb, console_active_tag_id, Point2f(15, 40), FONT_HERSHEY_PLAIN, 3, Scalar(0, 0, 255), 2, 8, false);
		// disegno i rettangoli delle zone sensibili
		for (int i = 0; i < zoneSettings.size(); ++i) {
			rectangle(out_rgb, zoneRects[i], Scalar(0, 175, 0), 1, 8, 0);
			putText(out_rgb, zoneIds[i], Point2f(zoneSettings[i][1], zoneSettings[i][2] + 12), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1, 8, false);
		}

		if (timerIsRunning) {
			if (t.isTimeout(waiting_time)) { // while timer is running
				putText(out_rgb, to_string(t.elapsedTime()), Point2f(55, 40), FONT_HERSHEY_PLAIN, 3, Scalar(0, 255, 0), 2, 8, false);
				// std::cout << t.elapsedTime();
			}
			if (t.elapsedTime() >= waiting_time) {
				rectangle(out_rgb, videoStatusIcon, Scalar(0, 0, 255), -1, 8, 0);
				sendingMessageStatus = true;
				if (sendingMessageStatus != sendingMessagePrevStatus) {
					boostClientUDP(to_string(videoNumToPlay));

					// std::cout << "message sent: " << to_string(videoNumToPlay) << endl;
				}
				sendingMessagePrevStatus = sendingMessageStatus;
			}
			else {
				sendingMessageStatus = false;
				sendingMessagePrevStatus = sendingMessageStatus;
			}
		}

		imshow(output_window_name, out_rgb);

		// save_segmentation_value
		if (save_value > 0)
		{
			pugi::xml_document doc;
			if (!doc.load_file("./data/settings.xml"))
			{
				std::cout << "file settings loading error" << endl;
				return -1;
			}
			else {
				std::cout << "Saving file setting...\n" << endl;

				pugi::xml_node segmentation_node = doc.child("settings").child("segmentation");
				pugi::xml_attribute type_attr = segmentation_node.attribute("type");
				type_attr.set_value(threshold_type);
				pugi::xml_attribute value_attr = segmentation_node.attribute("value");
				value_attr.set_value(threshold_value);

				// save document to file
				std::cout << "Saving result: " << doc.save_file("./data/settings.xml") << std::endl;
			}
			save_value = 0;
			std::cout << "save!" << endl;
		}

		// show live and wait for a key with timeout long enough to show images
		// imshow("Live", frame);

		if (waitKey(5) >= 0)
			break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}