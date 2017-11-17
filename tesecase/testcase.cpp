#include "cv.h"
#include "highgui.h"
#include "../track_lib/include/as_track.h"

#define PROCESS_IMG_W 640
#define PROCESS_IMG_H 480

using namespace cv;

unsigned char gImg[1920 * 1080 * 2];
void showImg(unsigned char *buff, int w, int h)
{
	IplImage *img = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
	for (int i = 0; i < h; i++)
	{
		memcpy(img->imageData + i*img->widthStep, buff + i*w, w);
	}
	cvShowImage("img", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
}
int main()
{

	char *pathname = "./data/1.avi";
	VideoCapture capture(pathname);
	double frame_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	double frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	AlgParams params;
	
	asTrackInit(&params);

	Mat frame;
	int index = 0;
	while(1)
	{
		Mat procFrame,gray;
		if (!capture.read(frame)) {
			printf("read frame failed\n");
			break;
		}
		int64 msec = capture.get(CV_CAP_PROP_POS_MSEC);
		resize(frame, procFrame,Size(PROCESS_IMG_W, PROCESS_IMG_H));

		cvtColor(procFrame, gray, CV_BGR2GRAY);
		for (int i = 0; i < gray.rows; i++)
		{
			memcpy(gImg + i*gray.cols, gray.data + i*gray.step, gray.cols);
		}
		AlgFrame algFrame;
		algFrame.tts = msec;
		algFrame.frameId = index;
		algFrame.y = gImg;
		algFrame.uv = NULL;
		algFrame.img_w = gray.cols;
		algFrame.img_h = gray.rows;
		showImg(algFrame.y, algFrame.img_w, algFrame.img_h);

		asTrackProcess(&algFrame);
		
		index++;
	}
	asTrackUinit();

	system("pause");
}