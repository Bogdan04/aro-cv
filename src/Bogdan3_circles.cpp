/*
 * Bogdan3(circles).cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: dexter
 */



/*
#include <cv.h>
#include <highgui.h>
#include <math.h>

using namespace cv;

int main()
{
	//load the video stream
		CvCapture *capture = cvCaptureFromCAM(0);

		if (!capture) {
			printf("Capture failed!\n");
			return -1;
		}

		IplImage* frame =0;
		frame = cvQueryFrame(capture);
		if (!frame)
			return -1;

	Mat img(frame), gray;
    //img=imread(argv[1], 1).data;

    cvtColor(img, gray, CV_BGR2GRAY);
    // smooth it, otherwise a lot of false circles may be detected
    GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
    vector<Vec3f> circles;
    HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 2, gray.rows/4, 200, 100);
    //HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 2, gray->rows/4, 200, 100 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
         // draw the circle center
         circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
         // draw the circle outline
         circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
    namedWindow( "circles", 1 );
    imshow( "circles", img );
    return 0;
}*/
