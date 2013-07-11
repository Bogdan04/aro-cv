/*
 * Bogdan.cpp
 *
 *  Created on: Jul 4, 2013
 *      Author: wedeveloper
 */


#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;


void trackObject(Mat imgCanny, Mat frame) {
	CvSeq* contour; //hold the pointer to a contour
	CvSeq* result; //hold sequence of points of a contour
	CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours

	//finding all contours in the image
	IplImage *imgCannyIpl = new IplImage(imgCanny);


	cvFindContours(imgCannyIpl, storage, &contour, sizeof(CvContour),
			CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

	free(imgCannyIpl);

	while(contour)
	{
		//obtain a sequence of points of contour, pointed by the variable 'contour'
		result = cvApproxPoly(contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contour)*0.03, 0);

		//if there are 3  vertices  in the contour(It should be a triangle)
		if(result->total==3 && fabs(cvContourArea(result, CV_WHOLE_SEQ))>400)
		{
			//iterating through each point
			CvPoint *pt[3];
			for(int i=0;i<3;i++){
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}

			//drawing lines around the triangle
			line(frame, *pt[0], *pt[1], cvScalar(255,0,0),4);
			line(frame, *pt[1], *pt[2], cvScalar(255,0,0),4);
			line(frame, *pt[2], *pt[0], cvScalar(255,0,0),4);

			//drawing gravity center
			CvPoint center;
			center.x=(int) (pt[0]->x + pt[1]->x + pt[2]->x)/3;
			center.y=(int) (pt[0]->y + pt[1]->y + pt[2]->y)/3;
			circle( frame, center, 3, Scalar(0,255,0), -1, 8, 0 );

		}

		//if there are 4 vertices in the contour(It should be a quadrilateral)
		else if(result->total==4 && fabs(cvContourArea(result, CV_WHOLE_SEQ))>400)
		{
			//iterating through each point
			CvPoint *pt[4];
			for(int i=0;i<4;i++){
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}

			//drawing lines around the quadrilateral
			line(frame, *pt[0], *pt[1], cvScalar(0,255,0),4);
			line(frame, *pt[1], *pt[2], cvScalar(0,255,0),4);
			line(frame, *pt[2], *pt[3], cvScalar(0,255,0),4);
			line(frame, *pt[3], *pt[0], cvScalar(0,255,0),4);

			//drawing gravity center
			CvPoint center;
			center.x=(int) (pt[0]->x + pt[1]->x + pt[2]->x + pt[3]->x)/4;
			center.y=(int) (pt[0]->y + pt[1]->y + pt[2]->y + pt[3]->y)/4;
			circle( frame, center, 3, Scalar(0,255,0), -1, 8, 0 );
		}

		//if there are 7  vertices  in the contour(It should be a heptagon)
//		else if(result->total ==7  && fabs(cvContourArea(result, CV_WHOLE_SEQ))>400)
//		{
//			//iterating through each point
//			CvPoint *pt[7];
//			for(int i=0;i<7;i++){
//				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
//			}
//
//			//drawing lines around the heptagon
//			line(frame, *pt[0], *pt[1], cvScalar(0,0,255),4);
//			line(frame, *pt[1], *pt[2], cvScalar(0,0,255),4);
//			line(frame, *pt[2], *pt[3], cvScalar(0,0,255),4);
//			line(frame, *pt[3], *pt[4], cvScalar(0,0,255),4);
//			line(frame, *pt[4], *pt[5], cvScalar(0,0,255),4);
//			line(frame, *pt[5], *pt[6], cvScalar(0,0,255),4);
//			line(frame, *pt[6], *pt[0], cvScalar(0,0,255),4);
//
//			//drawing gravity center
//			CvPoint center;
//			center.x=(int) (pt[0]->x + pt[1]->x + pt[2]->x + pt[3]->x + pt[4]->x +pt[5]->x + pt[6]->x)/7;
//			center.y=(int) (pt[0]->y + pt[1]->y + pt[2]->y + pt[3]->y + pt[4]->y +pt[5]->y + pt[6]->y)/7;
//			circle( frame, center, 3, Scalar(0,255,0), -1, 8, 0 );
//		}

		//obtain the next contour
		contour = contour->h_next;
	}

	cvReleaseMemStorage(&storage);
}


int main()
{
	//load the video stream
	CvCapture *capture = cvCaptureFromCAM(-1);
	//set video rezolution
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);

	if (!capture) {
		printf("Capture failed!\n");
		return -1;
	}


	Mat frame_circles, frame_polygons, frame_orig;
	vector<Vec3f> circles;

	//create output window
	//cvNamedWindow("Output video", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("Canny video", CV_WINDOW_AUTOSIZE);

	//iterate through each frame of the video
	while (1)
	{
		frame_orig = cvQueryFrame(capture);
		frame_polygons = frame_orig.clone();
		//IplImage* frame_ipl= new IplImage(frame_orig);
		//frame_ipl = cvCloneImage(frame_ipl);


		/// Convert it to gray
		cvtColor( frame_orig, frame_circles, CV_BGR2GRAY );

		/// Reduce the noise so we avoid false circle detection
		GaussianBlur( frame_circles, frame_circles, Size(9, 9), 2, 2 );

		/// Apply the Hough Transform to find the circles
		HoughCircles( frame_circles, circles, CV_HOUGH_GRADIENT, 1, frame_circles.rows/8, 150, 25, 0, 0 );

		/// Draw the circles detected
		int cx, cy;
		//	for( size_t i = 0; i < circles.size(); i++ )
		//	{
		if (circles.size() > 0)
		{
			int i  = 0;
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);

			cx = center.x / 117 + 1;
			cy = center.y / 96 + 1;

			// circle center
			circle( frame_orig, center, 3, Scalar(0,255,0), -1, 8, 0 );
			printf("%d: CX%d-CY%d    %d, %d\n",i, cx, cy,  center.x, center.y);
			// circle outline
			circle( frame_orig, center, radius, Scalar(0,0,255), 3, 8, 0 );
		}


		// Convert cv::Mat to IplImage
		//IplImage *frame_orig_ipl = new IplImage(frame_orig);

		//IplImage* frame_canny_ipl= cvCreateImage(cvGetSize(frame_ipl),8,1);
		//cvCanny(frame_ipl,frame_canny_ipl,100,200,3);
		Canny(frame_polygons, frame_polygons, 100, 200, 3);
		trackObject(frame_polygons, frame_orig);



		//cvShowImage( "Output video", frame_orig_ipl ); //original image + circle & polygons contours
		imshow("Output video", frame_orig);
		//imshow("Canny video", frame_polygons);
		//cvShowImage( "Canny video", (const CvArr*)frame_orig ); //canny input for polygons detection

		//clear memory
		//cvReleaseImage(&frame_orig_ipl);
		//cvReleaseImage(&frame_canny_ipl);
		//cvReleaseImage(&frame_ipl);

		//Save image to disk (preview from beaglebone)
		//cvSaveImage("scary.jpg", frame_orig_ipl);


		int c = cvWaitKey(10);
		//If 'ESC' is pressed, break the loop
		if ((char) c == 27)
			break;
		//cvReleaseImage(&img_save);
	}

	cvDestroyAllWindows();
	return 0;
}
