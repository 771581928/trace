#include "cv.h"
#include "highgui.h"

#include "stdio.h"
#include "../include/as_alg_private.h"
extern AlgInfo gAlgInfo;

void drawDetectBoxes(IplImage *imgRGB)
{

	for (int i = 0; i < gAlgInfo.asDetectNum;i++)
	{
		CvRect r;
		r.x = gAlgInfo.asDetectedBoxes[i].x;
		r.y = gAlgInfo.asDetectedBoxes[i].y;
		r.width = gAlgInfo.asDetectedBoxes[i].width;
		r.height = gAlgInfo.asDetectedBoxes[i].height;
		cvRectangleR(imgRGB, r, cvScalar(255, 0, 0), 2, 4, 0);
	}

}
void drawCorner(IplImage*imgRGB)
{
	for (int  i = 0; i < gAlgInfo.asCornerNum; i++)
	{
		CvPoint point;
		point.x = gAlgInfo.asCorner[i].x;
		point.y = gAlgInfo.asCorner[i].y;
		cvCircle(imgRGB, point, 2, cvScalar(0, 0, 255), 2, 8, 0);
	}
}

void drawTrack(IplImage*imgRGB)
{
	for (int i = 0; i < gAlgInfo.asTrackNum; i++)
	{
		if (gAlgInfo.asTrack[i].trackLength > 2)
		{
			for (int j = 0; j < gAlgInfo.asTrack[i].trackLength - 1; j++)
			{
				CvPoint start_point, end_point;
				start_point.x = gAlgInfo.asTrack[i].trackPoint[j].x;
				start_point.y = gAlgInfo.asTrack[i].trackPoint[j].y;
				end_point.x = gAlgInfo.asTrack[i].trackPoint[j+1].x;
				end_point.y = gAlgInfo.asTrack[i].trackPoint[j+1].y;
				cvLine(imgRGB, start_point, end_point, cvScalar(0, 255, 0), 2, 8, 0);
 				//cvShowImage("img", imgRGB);
				//printf("start point(%3d,%3d)\t end point(%3d,%3d)\n", start_point.x = gAlgInfo.asTrack[i].trackPoint[j].x, start_point.y = gAlgInfo.asTrack[i].trackPoint[j].y,
				//	end_point.x = gAlgInfo.asTrack[i].trackPoint[j + 1].x, end_point.y = gAlgInfo.asTrack[i].trackPoint[j + 1].y);
				//cvWaitKey(0);
			}
		}
	}
}
void showAlgInfo()
{
	printf("algInfo->asDetectNum = %d\t algInfo->asCornerNum: %d\n", gAlgInfo.asDetectNum,gAlgInfo.asCornerNum);
	IplImage *img = cvCreateImage(cvSize(gAlgInfo.img_w, gAlgInfo.img_h), IPL_DEPTH_8U, 1);
	IplImage *imgRGB = cvCreateImage(cvSize(gAlgInfo.img_w, gAlgInfo.img_h), IPL_DEPTH_8U, 3);
	for (int i = 0; i < gAlgInfo.img_h; i++)
	{
		memcpy(img->imageData + i*img->widthStep, gAlgInfo.img_y + i*gAlgInfo.img_w, gAlgInfo.img_w);
	}
	
	cvCvtColor(img, imgRGB, CV_GRAY2RGB);
	drawDetectBoxes(imgRGB);
	drawCorner(imgRGB);
	drawTrack(imgRGB);

	cvShowImage("img", imgRGB);
	cvWaitKey(1);
	cvReleaseImage(&img);
	cvReleaseImage(&imgRGB);
}