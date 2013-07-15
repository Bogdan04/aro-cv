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


	//Mat *Q = (Mat *)cvLoad("Q.xml");
	double qu[4][4] ={{1.0, 0.0, 0.0, -1.0384888534545898e+03},
		    {0.0, 1.0, 0.0, -8.9958347320556641e+01},
		    {0.0, 0.0, 0.0, 9.8627901063924435e+02},
		    {0.0, 0.0, 1.5284315798247780e-01, 2.9219960278349775e+00}};


	int aux=0;



	Mat frame_circles_r, frame_circles_l, frame_polygons_r, frame_polygons_l, frame_orig_r,frame_orig_l, frame_left, frame_right;
	Mat frame_undistorted_r, frame_undistorted_l;
	vector<Vec3f> circles_r, circles_l;
//
//	//create output window
//	//cvNamedWindow("Output video", CV_WINDOW_AUTOSIZE);
//	//cvNamedWindow("Canny video", CV_WINDOW_AUTOSIZE);
//
	//cvNamedWindow("left", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("right", CV_WINDOW_AUTOSIZE);
//	//iterate through each frame of the video
	while (1)
	{

		//load the video stream
		CvCapture *capture_r = cvCaptureFromCAM(1);
		//set video rezolution
		cvSetCaptureProperty(capture_r, CV_CAP_PROP_FRAME_WIDTH, 320);
		cvSetCaptureProperty(capture_r, CV_CAP_PROP_FRAME_HEIGHT, 240);

		if (!capture_r) {
			printf("Capture right failed!\n");
			return -1;
		}
		frame_orig_r = cvQueryFrame(capture_r);
		cvReleaseCapture(&capture_r);

		CvCapture *capture_l = cvCaptureFromCAM(0);
		cvSetCaptureProperty(capture_l, CV_CAP_PROP_FRAME_WIDTH, 320);
		cvSetCaptureProperty(capture_l, CV_CAP_PROP_FRAME_HEIGHT, 240);
		if (!capture_l) {
			printf("Capture left failed!\n");
			return -1;
		}
		frame_orig_l = cvQueryFrame(capture_l);
		cvReleaseCapture(&capture_l);

		frame_polygons_r = frame_orig_r.clone();
		frame_polygons_l = frame_orig_l.clone();




		/// Convert it to gray
		cvtColor( frame_orig_r, frame_circles_r, CV_BGR2GRAY );
		cvtColor( frame_orig_l, frame_circles_l, CV_BGR2GRAY );

		/// Reduce the noise so we avoid false circle detection
		GaussianBlur( frame_circles_r, frame_circles_r, Size(9, 9), 2, 2 );
		GaussianBlur( frame_circles_l, frame_circles_l, Size(9, 9), 2, 2 );

		/// Apply the Hough Transform to find the circles
		HoughCircles( frame_circles_r, circles_r, CV_HOUGH_GRADIENT, 1, frame_circles_r.rows/8, 150, 30, 0, 0 );
		HoughCircles( frame_circles_l, circles_l, CV_HOUGH_GRADIENT, 1, frame_circles_l.rows/8, 150, 30, 0, 0 );

		/// Draw the circles detected
		int cx, cy, center_x_r, center_y_r, center_x_l, center_y_l;
		//	for( size_t i = 0; i < circles.size(); i++ )
		//	{
		if (circles_r.size() > 0)
		{
			int i  = 0;
			Point center(cvRound(circles_r[i][0]), cvRound(circles_r[i][1]));
			int radius = cvRound(circles_r[i][2]);

			cx = center.x / 117 + 1;
			cy = center.y / 96 + 1;

			center_x_r = center.x;
			center_y_r = center.y;

			// circle center
			circle( frame_orig_r, center, 3, Scalar(0,255,0), -1, 8, 0 );
			//printf("%d: CX%d-CY%d    %d, %d\n",i, cx, cy,  center.x, center.y);
			// circle outline
			circle( frame_orig_r, center, radius, Scalar(0,0,255), 3, 8, 0 );
		}

		if (circles_l.size() > 0)
		{
			int i  = 0;
			Point center(cvRound(circles_l[i][0]), cvRound(circles_l[i][1]));
			int radius = cvRound(circles_l[i][2]);

			cx = center.x / 117 + 1;
			cy = center.y / 96 + 1;

			center_x_l = center.x;
			center_y_l = center.y;

			// circle center
			circle( frame_orig_l, center, 3, Scalar(0,255,0), -1, 8, 0 );
			//printf("%d: CX%d-CY%d    %d, %d\n",i, cx, cy,  center.x, center.y);
			// circle outline
			circle( frame_orig_l, center, radius, Scalar(0,0,255), 3, 8, 0 );
		}

		int d = center_x_r - center_x_l;

		double X = center_x_l * qu[0][0] + qu[0][3];




		double Y = center_y_l * qu[1][1] + qu[1][3];
		double Z = qu[2][3];
		double W = d * qu[3][2] + qu[3][3];

		X = X / W;
		Y = Y / W;
		Z = Z / W;

		printf("X: %d  Y: %d   Z: %d\n", (int)X, (int)Y, (int)Z);


		// Convert cv::Mat to IplImage
		//IplImage *frame_orig_ipl = new IplImage(frame_orig);

		//IplImage* frame_canny_ipl= cvCreateImage(cvGetSize(frame_ipl),8,1);
		//cvCanny(frame_ipl,frame_canny_ipl,100,200,3);
//		Canny(frame_polygons, frame_polygons, 100, 200, 3);
//		trackObject(frame_polygons, frame_orig);



		//cvShowImage( "Output video", frame_orig_ipl ); //original image + circle & polygons contours
		//imshow("Output video", frame_orig);
		//imshow("Canny video", frame_polygons);
		//cvShowImage( "Canny video", (const CvArr*)frame_orig ); //canny input for polygons detection

		//clear memory
		//cvReleaseImage(&frame_orig_ipl);
		//cvReleaseImage(&frame_canny_ipl);
		//cvReleaseImage(&frame_ipl);

		//Save image to disk (preview from beaglebone)
		//cvSaveImage("scary_l.jpg", frame_orig_l);
		//cvSaveImage("scary_r.jpg", frame_orig_r);


		imwrite("scary_l.jpg", frame_orig_l);
		imwrite("scary_r.jpr", frame_orig_r);


		int c = cvWaitKey(10);

//		if ((char) c == 65){
//			char l[15],r[15];
//
//			sprintf(l, "left%02d.ppm", aux);
//			sprintf(r, "right%02d.ppm", aux);
//
//			//cvSaveImage(l, &frame_left);
//			imwrite(l, frame_left);
//			imwrite(r, frame_right);
//
//			//imsa
//			//cvSaveImage(r, frame_right);
//
//			aux++;
//		}
		//If 'ESC' is pressed, break the loop
		if ((char) c == 27)
			break;
		//cvReleaseImage(&img_save);
	}

	//cvDestroyAllWindows();
	return 0;
}


//#include <opencv2/opencv.hpp>
//
//int main()
//{
//    //initialize and allocate memory to load the video stream from camera
//    CvCapture *capture1 = cvCaptureFromCAM(0);
//    CvCapture *capture2 = cvCaptureFromCAM(1);
//
//	cvSetCaptureProperty(capture1, CV_CAP_PROP_FRAME_WIDTH, 320);
//	//cvSetCaptureProperty(capture1, CV_CAP_PROP_FRAME_HEIGHT, 240);
//	cvSetCaptureProperty(capture2, CV_CAP_PROP_FRAME_WIDTH, 320);
//	//cvSetCaptureProperty(capture2, CV_CAP_PROP_FRAME_HEIGHT, 240);
//
//
//    if( !capture1 ) return 1;
//    if (!capture2) return 1 ;
//    cvNamedWindow("Video1");
//    cvNamedWindow("Video2") ;
//
//    while(true) {
//        //grab and retrieve each frames of the video sequentially
//        IplImage* frame1 = cvQueryFrame( capture1 );
//        IplImage* frame2 = cvQueryFrame( capture2 );
//
//        if( frame1 )
//        {
//			cvShowImage( "Video1", frame1 );
//        }
//        if (frame2)
//			cvShowImage( "Video2", frame2 );
//
//
//        //wait for 40 milliseconds
//        int c = cvWaitKey(40);
//
//        //exit the loop if user press "Esc" key  (ASCII value of "Esc" is 27)
//        if((char)c==27 ) break;
//    }
//
//    return 0;
//}
