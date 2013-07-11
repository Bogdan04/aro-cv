#include <opencv2/opencv.hpp>
#include "stdio.h"

/*using namespace cv;

int main( int argc, char** argv )
{
  Mat image;
  image = imread( argv[1], 1 );

  if( argc != 2 || !image.data )
    {
      printf( "No image data \n" );
      return -1;
    }

  namedWindow( "Display Image", WINDOW_AUTOSIZE );
  imshow( "Display Image", image );

  waitKey(0);

  return 0;
}*/


/////////////////////////////////////////////////////
// trialcam1a.cpp
// A Simple Camera Capture Framework
// This program will connect to a camera then
// show the frames in a window
/////////////////////////////////////////////////////
/*#include <stdio.h>
#include <cv.h>
#include <highgui.h>

int main()
{
IplImage *frame = NULL; //Preparing frame pointer
int key;

//Allocates and initializes cvCapture structure
// for reading a video stream from the camera.
//Index of camera is -1 since only one camera
// connected to the computer or it does not
// matter what camera to use.
CvCapture *input_camera = cvCaptureFromCAM(0);

//Grabs and returns a frame from camera
frame = cvQueryFrame(input_camera);

//Creates window for displaying the frames
//Flag is reset (0) --> change window size
// manually
cvNamedWindow("Capturing Image ...", 0);

//Change to the appropriate size. In GTK, the
// inappropriate size will return a segmentation
// fault. I don't know why ...
//Gets the appropriate size using cvGetCaptureProperty
// with CV_CAP_PROP_FRAME_HEIGHT and CV_CAP_PROP_FRAME_WIDTH
// as property_id
cvResizeWindow("Capturing Image ...",
(int) cvGetCaptureProperty(input_camera, CV_CAP_PROP_FRAME_HEIGHT),
(int) cvGetCaptureProperty(input_camera, CV_CAP_PROP_FRAME_WIDTH));

while(frame != NULL)
{
//Shows a frame
cvShowImage("Capturing Image ...", frame);

//Checks if ESC is pressed and gives a delay
// so that the frame can be displayed properly
key = cvWaitKey(10);
if(key == 27)
break;
//Grabs and returns the next frame
frame = cvQueryFrame(input_camera);
}

//Release cvCapture structure
cvReleaseCapture(&input_camera);

//Destroy the window
cvDestroyWindow("Capturing Image ...");

return 0;
}*/


/*#include "highgui.h"

int main (int argc, char** argv)
{
	cvNamedWindow("Example", CV_WINDOW_AUTOSIZE);

	CvCapture* capture = cvCreateCameraCapture(0);
	IplImage* frame;

	while(1){
		frame=cvQueryFrame(capture);
		if(!frame) break;
		cvShowImage("Example", frame);

		char c = cvWaitKey(33);
		if (c=27) break;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("Example");
}*/

/*#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
/*void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  src.copyTo( dst, detected_edges);
  imshow( window_name, dst );
 }


/** @function main */
/*int main( int argc, char** argv )
{
  /// Load an image

  src = imread( argv[1] );

  if( !src.data )
  { return -1; }

  /// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );

  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create a window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

  /// Show the image
  CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;
  }*/


/*#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cv.h>
#include <cvaux.h>
#include <cxcore.h>
#include <highgui.h>
#include <math.h>
#include <string.h>


using namespace std;
using namespace cv;

int main(int, char**)
{

    cvNamedWindow("Edges", CV_WINDOW_AUTOSIZE);
CvCapture* capture = cvCaptureFromCAM(0);

IplImage* frame;
    while(1) {
        frame = cvQueryFrame( capture );

        int depth_img =frame->depth;
        int height_img =frame->height;
        int width_img =frame->width;
        int size_img =frame->imageSize;
        int nchan_img =frame->nChannels;
        int nsize_img =frame->nSize;

        cout << setw(15) << "depth" <<  depth_img << endl;
        cout << setw(15) << "height" <<  height_img << endl;
        cout << setw(15) << "width" <<  width_img << endl;
        cout << setw(15) << "size" <<  size_img << endl;
        cout << setw(15) << "nchan" <<  nchan_img << endl;
        cout << setw(15) << "nsize" <<  nsize_img << endl;


        IplImage* out = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 3 );
        IplImage* gray_out = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );
        IplImage* canny_out = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );
        cvSmooth( frame, out, CV_GAUSSIAN, 11, 11 );
        cvCvtColor(out , gray_out, CV_RGB2GRAY);
        cvCanny( gray_out, canny_out, 10, 10, 3 );

        if( !frame ) break;
        cvShowImage( "Edge", canny_out );
        char c = cvWaitKey(33);
        if( c == 27 ) break;
    }
    cvReleaseCapture( &capture );
    cvDestroyWindow( "Edge" );
    return 0;
}*/
