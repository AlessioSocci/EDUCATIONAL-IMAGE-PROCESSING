#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <opencv2\opencv.hpp>


using namespace std;
using namespace cv;

int main()
{
	double scale = 2.0;

	int stop_time = 0;
	int counter = 0;

	short int selector = 0;
	
	CascadeClassifier faceCascade;

	faceCascade.load("C:\\Users\\A\\Documents\\Progetti C++\\Libraries\\OpenCV\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");

	VideoCapture videoCap(0);

	if (videoCap.isOpened())
	{
		cout << "CAMERA 0 --> READY!";
	}
	else
	{
		cout << "CAMERA 0 --> ERROR!";
	}

	while (1)
	{
		destroyWindow("CAMERA 0");
		destroyWindow("CAMERA 0 PROCESSED");
		destroyWindow("CAMERA 0 PROCESSED 2");
		destroyWindow("BARS");

		cout << endl << endl;
		cout << endl << "Select one filter to be applied:" << endl << "(Type number and press enter!)" << endl;
		cout << endl << " - 1 --> GREYSCALE AND FACE TRACKING" << endl;
		cout << endl << " - 2 --> GAUSSIAN BLUR" << endl;
		cout << endl << " - 3 --> IMAGE CROP" << endl;
		cout << endl << " - 4 --> CANNY" << endl;
		cout << endl << " - 5 --> BLANK" << endl;
		cout << endl << " - 6 --> COLOR DETECTION" << endl;
		cout << endl << " - 7 --> FIND CONTOUR" << endl;

		cin >> selector;

		cout << endl << endl;
		cout << endl << "Insert stop_time" << endl << "(Type number and press enter!)" << endl;

		cin >> stop_time;

		if(stop_time > 500)
		{
			stop_time = 500;
		}

		counter = 0;

		Mat flat_frame;

		videoCap >> flat_frame;

		resize(flat_frame, flat_frame, Size(flat_frame.size().width / scale, flat_frame.size().height / scale));

		imshow("CAMERA 0", flat_frame);

		if (waitKey(30) >= 0) { return 0; }

		switch (selector)
		{
			// GREY FILTER AND FACE TRACKING

			case 1:
			{
				while (counter != stop_time)
				{
					counter++;
				
					videoCap >> flat_frame;

					imshow("CAMERA 0", flat_frame);

					moveWindow("CAMERA 0", 0, 0);

					Mat greyScale_frame;

					cvtColor(flat_frame, greyScale_frame, COLOR_BGR2GRAY);

					resize(greyScale_frame, greyScale_frame, Size(greyScale_frame.size().width / scale, greyScale_frame.size().height / scale));

					vector<Rect> faces;

					faceCascade.detectMultiScale(greyScale_frame, faces, 1.1, 3, 0, Size(30, 30));

					for (Rect area : faces)
					{
						Scalar drawColor = Scalar(255, 255, 255); // correspond BGR color -> withe... but filtered in gray scale 

						rectangle(greyScale_frame, Point(cvRound(area.x), cvRound(area.y)), Point(cvRound(area.x + area.width - 1), cvRound(area.y + area.height - 1)), drawColor);
					}

					imshow("CAMERA 0 PROCESSED", greyScale_frame);

					moveWindow("CAMERA 0 PROCESSED", 900, 0);

					if (waitKey(30) >= 0) { return 0; }
				}
			}
				
			// GAUSSIAN BLUR

			case 2:
			{
				while (counter != stop_time)
				{
					counter++;

					videoCap >> flat_frame;

					imshow("CAMERA 0", flat_frame);

					moveWindow("CAMERA 0", 0, 0);

					Mat gaussianBlur_frame;

					GaussianBlur(flat_frame, gaussianBlur_frame, Size(gaussianBlur_frame.size().width, gaussianBlur_frame.size().height), 3, 0);

					resize(gaussianBlur_frame, gaussianBlur_frame, Size(gaussianBlur_frame.size().width / scale, gaussianBlur_frame.size().height / scale));

					imshow("CAMERA 0 PROCESSED", gaussianBlur_frame);

					moveWindow("CAMERA 0 PROCESSED", 900, 0);

					if(waitKey(30) >= 0) { return 0; }	
				}
			}
				
			// IMAGE CROP
			
			case 3:
			{
				while (counter != stop_time)
				{
					counter++;

					videoCap >> flat_frame;

					imshow("CAMERA 0", flat_frame);
						
					moveWindow("CAMERA 0", 0, 0);

					Mat crop_frame;

					Rect roi(100, 80, 350, 150);

					crop_frame = flat_frame(roi);

					imshow("CAMERA 0 PROCESSED", crop_frame);

					moveWindow("CAMERA 0 PROCESSED", 900, 0);

					if(waitKey(30) >= 0) { return 0; }
				}
			}
				
			// CANNY
			
			case 4:
			{
				while (counter != stop_time)
				{
					counter++;

					videoCap >> flat_frame;

					imshow("CAMERA 0", flat_frame);

					moveWindow("CAMERA 0", 0, 0);

					Mat canny_frame;

					Canny(flat_frame, canny_frame, 15, 25, 3, true);

					resize(canny_frame, canny_frame, Size(canny_frame.size().width / scale, canny_frame.size().height / scale));

					imshow("CAMERA 0 PROCESSED", canny_frame);

					moveWindow("CAMERA 0 PROCESSED", 900, 0);

					if(waitKey(30) >= 0) { return 0; }
				}
			}
				
			// BLANK
			
			case 5:
			{
				while (counter != stop_time)
				{
					counter++;

					videoCap >> flat_frame;

					imshow("CAMERA 0", flat_frame);

					moveWindow("CAMERA 0", 0, 0);

					Mat blank_frame(150, 350, CV_8UC3, Scalar(255, 0, 0));

					circle(blank_frame, Point(75, 75), 50, Scalar(0, 0, 255), FILLED);
					circle(blank_frame, Point(195, 75), 50, Scalar(0, 0, 255), FILLED);

					rectangle(blank_frame, Point(75, 75), Point(105, 105), Scalar(0, 255, 0), FILLED);
					rectangle(blank_frame, Point(195, 75), Point(225, 105), Scalar(0, 255, 0), FILLED);

					imshow("CAMERA 0 PROCESSED", blank_frame);

					moveWindow("CAMERA 0 PROCESSED", 900, 0);

					if(waitKey(30) >= 0) { return 0; }
				}
			}
				
			// COLOR DETECTION
			
			case 6:
			{
				int Hmin = 0, Smin = 10, Vmin = 150;
				int Hmax = 20, Smax = 240, Vmax = 255;

				namedWindow("BARS", (50, 50));
			
				moveWindow("BARS", 600, 0);

				while (counter != stop_time)
				{
					counter++;

					createTrackbar("HUE MIN", "BARS", &Hmin, 179);
					createTrackbar("SAT MIN", "BARS", &Smin, 179);
					createTrackbar("VAL MIN", "BARS", &Vmin, 179);
					createTrackbar("HUE MAX", "BARS", &Hmax, 255);
					createTrackbar("SAT MAX", "BARS", &Smax, 255);
					createTrackbar("VAL MAX", "BARS", &Vmax, 255);

					videoCap >> flat_frame;

					imshow("CAMERA 0", flat_frame);

					moveWindow("CAMERA 0", 0, 0);

					Mat colorDetect_frame;
					Mat mask_frame;

					cvtColor(flat_frame, colorDetect_frame, COLOR_BGR2HSV);

					Scalar lower(Hmin, Smin, Vmin);
					Scalar upper(Hmax, Smax, Vmax);

					inRange(colorDetect_frame, lower, upper, mask_frame);

					resize(colorDetect_frame, colorDetect_frame, Size(colorDetect_frame.size().width / scale, colorDetect_frame.size().height / scale));

					imshow("CAMERA 0 PROCESSED", colorDetect_frame);

					moveWindow("CAMERA 0 PROCESSED", 900, 0);

					if (waitKey(30) >= 0) { return 0; }

					resize(mask_frame, mask_frame, Size(mask_frame.size().width / scale, mask_frame.size().height / scale));

					imshow("CAMERA 0 PROCESSED 2", mask_frame);

					moveWindow("CAMERA 0 PROCESSED 2", 900, 300);

					if (waitKey(30) >= 0) { return 0; }
				}
			}

			// FIND CONTOUR 

			case 7:
			{
				string path = "Resources/shapes.png";
				
				Mat shapes_image = imread(path);

				Mat shapes_image_processed = imread(path);

				if ((!shapes_image.data) || (!shapes_image_processed.data))
				{
					cout << "FILE NOT FOUND ! \n";
				
					return 1;
				}

				Mat contour_image;

				vector<vector<Point>> contour;
				vector<Vec4i> hierarchy;
				
				cvtColor(shapes_image_processed, contour_image, COLOR_BGR2GRAY);

				threshold(contour_image, contour_image, 250, 255, THRESH_BINARY);

				findContours(contour_image, contour, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

				drawContours(shapes_image_processed, contour, -1, Scalar(0, 255, 0), 1);

				while (counter != stop_time)
				{
					counter++;

					imshow("CAMERA 0", shapes_image);

					moveWindow("CAMERA 0", 0, 0);

					if (waitKey(30) >= 0) { return 0; }

					imshow("CAMERA 0 PROCESSED", shapes_image_processed);

					moveWindow("CAMERA 0 PROCESSED", 640, 0);

					if (waitKey(30) >= 0) { return 0; }
				}
			}
			
			break;
		}
	}
}


