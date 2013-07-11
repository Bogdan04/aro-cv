/*
 * myapp.cpp
 *
 *  Created on: Jul 3, 2013
 *      Author: wedeveloper
 */

/*

#include "stdafx.h"
#include <cv.h>
#include <highgui.h>
using namespace std;

IplImage* imgTracking = 0;

int lastX1 = -1;
int lastY1 = -1;

int lastX2 = -1;
int lastY2 = -1;

void trackObject(IplImage* imgThresh, IplImage* frame) {
	CvSeq* contour; //hold the pointer to a contour
	CvSeq* result; //hold sequence of points of a contour
	CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours

	//finding all contours in the image
	cvFindContours(imgThresh, storage, &contour, sizeof(CvContour),
			CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));


		 while(contour)
		{
		//obtain a sequence of points of contour, pointed by the variable 'contour'
		result = cvApproxPoly(contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contour)*0.03, 0);

		//if there are 3  vertices  in the contour(It should be a triangle)
		if(result->total==3 && fabs(cvContourArea(result, CV_WHOLE_SEQ))>200)
		{
		//iterating through each point
		CvPoint *pt[3];
		for(int i=0;i<3;i++){
		pt[i] = (CvPoint*)cvGetSeqElem(result, i);
		}

		//drawing lines around the triangle
		cvLine(frame, *pt[0], *pt[1], cvScalar(255,0,0),4);
		cvLine(frame, *pt[1], *pt[2], cvScalar(255,0,0),4);
		cvLine(frame, *pt[2], *pt[0], cvScalar(255,0,0),4);

		}

		//if there are 4 vertices in the contour(It should be a quadrilateral)
		else if(result->total==4 && fabs(cvContourArea(result, CV_WHOLE_SEQ))>200)
		{
		//iterating through each point
		CvPoint *pt[4];
		for(int i=0;i<4;i++){
		pt[i] = (CvPoint*)cvGetSeqElem(result, i);
		}

		//drawing lines around the quadrilateral
		cvLine(frame, *pt[0], *pt[1], cvScalar(0,255,0),4);
		cvLine(frame, *pt[1], *pt[2], cvScalar(0,255,0),4);
		cvLine(frame, *pt[2], *pt[3], cvScalar(0,255,0),4);
		cvLine(frame, *pt[3], *pt[0], cvScalar(0,255,0),4);
		}

		//if there are 7  vertices  in the contour(It should be a heptagon)
		else if(result->total ==7  && fabs(cvContourArea(result, CV_WHOLE_SEQ))>200)
		{
		//iterating through each point
		CvPoint *pt[7];
		for(int i=0;i<7;i++){
		pt[i] = (CvPoint*)cvGetSeqElem(result, i);
		}

		//drawing lines around the heptagon
		cvLine(frame, *pt[0], *pt[1], cvScalar(0,0,255),4);
		cvLine(frame, *pt[1], *pt[2], cvScalar(0,0,255),4);
		cvLine(frame, *pt[2], *pt[3], cvScalar(0,0,255),4);
		cvLine(frame, *pt[3], *pt[4], cvScalar(0,0,255),4);
		cvLine(frame, *pt[4], *pt[5], cvScalar(0,0,255),4);
		cvLine(frame, *pt[5], *pt[6], cvScalar(0,0,255),4);
		cvLine(frame, *pt[6], *pt[0], cvScalar(0,0,255),4);
		}

		//obtain the next contour
		contour = contour->h_next;
	}

	cvReleaseMemStorage(&storage);
}

int main() {
	//load the video file to the memory
	CvCapture *capture = cvCaptureFromCAM(0);

	if (!capture) {
		printf("Capture failure\n");
		return -1;
	}

	IplImage* frame = 0;
		frame = cvQueryFrame(capture);
		if (!frame)
			return -1;

		//create a blank image and assigned to 'imgTracking' which has the same size of original video
		imgTracking = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
		cvZero(imgTracking); //covert the image, 'imgTracking' to black



	cvNamedWindow("Video");
	//cvNamedWindow("Thresholding");

	//iterate through each frames of the video
	while (true) {

		frame = cvQueryFrame(capture);
		if (!frame)
			break;
		frame = cvCloneImage(frame);

		//smooth the original image using Gaussian kernel
		cvSmooth(frame, frame, CV_GAUSSIAN, 3, 3);

		//converting the original image into grayscale
		IplImage* imgGrayScale = cvCreateImage(cvGetSize(frame), 8, 1);
		cvCvtColor(frame, imgGrayScale, CV_BGR2GRAY);

		//thresholding the grayscale image to get better results
		cvThreshold(imgGrayScale, imgGrayScale, 100, 255, CV_THRESH_BINARY_INV);

		//track the possition of the ball
		trackObject(imgGrayScale, frame);

		// Add the tracking image and the frame
		cvAdd(frame, imgTracking, frame);

		cvShowImage("Video", frame);
		//cvShowImage("Thresholding", imgGrayScale);

		//Clean up used images
		cvReleaseImage(&imgGrayScale);
		cvReleaseImage(&frame);

		//Wait 10mS
		int c = cvWaitKey(10);
		//If 'ESC' is pressed, break the loop
		if ((char) c == 27)
			break;
	}

	cvDestroyAllWindows();
	cvReleaseImage(&imgTracking);
	cvReleaseCapture(&capture);

	return 0;
}
//////////////////////////////////////*/
