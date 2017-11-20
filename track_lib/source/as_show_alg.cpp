#include "cv.h"
#include "highgui.h"

#include "stdio.h"
#include "../include/as_track_alg.h"
extern TrackAlgInfo gAlgInfo;

void drawDetectBoxes(IplImage *imgRGB)
{

	for (int i = 0; i < gAlgInfo.asDetectNum;i++)
	{
		CvRect r;
		r.x = gAlgInfo.asDetectedBoxes[i].x;
		r.y = gAlgInfo.asDetectedBoxes[i].y;
		r.width = gAlgInfo.asDetectedBoxes[i].width;
		r.height = gAlgInfo.asDetectedBoxes[i].height;
		cvRectangleR(imgRGB, r, cvScalar(0, 0, 255), 3, 4, 0);
	}


}
void showAlgInfo()
{
	printf("algInfo->asDetectNum = %d\n", gAlgInfo.asDetectNum);
	IplImage *img = cvCreateImage(cvSize(gAlgInfo.img_w, gAlgInfo.img_h), IPL_DEPTH_8U, 1);
	IplImage *imgRGB = cvCreateImage(cvSize(gAlgInfo.img_w, gAlgInfo.img_h), IPL_DEPTH_8U, 3);
	for (int i = 0; i < gAlgInfo.img_h; i++)
	{
		memcpy(img->imageData + i*img->widthStep, gAlgInfo.img_y + i*gAlgInfo.img_w, gAlgInfo.img_w);
	}
	
	cvCvtColor(img, imgRGB, CV_GRAY2RGB);
	drawDetectBoxes(imgRGB);

	cvShowImage("img", imgRGB);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvReleaseImage(&imgRGB);
}