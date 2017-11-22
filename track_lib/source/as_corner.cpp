#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <features2d/features2d.hpp>
#include<opencv2/legacy/legacy.hpp>


#include "../include/as_corner.h"
#include "../../platform_lib/include/as_platform.h"
#include "stdio.h"

using namespace cv;
CornerAlgInfo *p_gCornerAlg = NULL;

void asCornerInit(int img_w, int img_h)
{
	p_gCornerAlg = (CornerAlgInfo*)asMalloc(0,sizeof(CornerAlgInfo), AS_ALIGN_32BYTE_SIZE);
	asAssert(p_gCornerAlg != NULL);
	p_gCornerAlg->img_h = img_h;
	p_gCornerAlg->img_w = img_w;
	printf("%s\n", __FUNCTION__);

}

void write_points(FILE* fp, AsCorner* corner, int num_of_points)
{
	fprintf(fp, "number of points: %d\n", num_of_points);
	for (int i = 0; i < num_of_points; i++)
	{
		unsigned int* d = (unsigned int*)(&(corner[i].brief));
		fprintf(fp, "[%4u, %4u, %4u]\t", corner[i].x, corner[i].y, corner[i].val);
		fprintf(fp, "[%8x, %12x, %12x, %12x, %12x, %12x, %12x, %12x]\n", d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7]);
	}
}


void asCornerProcess(unsigned char *img, AsCorner *corner, int *cornerNum)
{
	printf("%s\n", __FUNCTION__);

	//add orb daima
	vector<KeyPoint> keypoints;
	Mat descriptors;
	Mat img_proc(p_gCornerAlg->img_h, p_gCornerAlg->img_w, CV_8UC1, img);
	//img_proc.data = img;
	//img_proc.cols = img_w;
	//img_proc.rows = img_h;
	/*//orb factors
	int nfeatures = 500;//or init cornerNum and using this
	int threshold = 50;//or init corner thresh and using this
	float scaleFactor = 1.2f;
	int nlevels = 8;
	int edgeThreshold = 31;//derect keypoints outside edgeThreshold pixels
	int firstLevel = 0;
	int WTA_K = 2;
	int scoreType = ORB::HARRIS_SCORE;
	int patchSize = 31;
	}
	ORB(nfeatures, scaleFactor, nlevels, edgeThreshold, firstLevel, WTA_K, scoreType, patchSize);*/
	ORB orb;
	orb(img_proc, Mat(), keypoints, descriptors);
	*cornerNum = keypoints.size();
	for (int i = 0; i < *cornerNum; i++)
	{
		corner[i].x = keypoints[i].pt.x;
		corner[i].y = keypoints[i].pt.y;
		corner[i].val = keypoints[i].size;
		memcpy(corner[i].brief, descriptors.ptr<char>(i), 32);
		//corner[i].brief = descriptors.ptr<char>(i);
	}
	if (1)
	{
		FILE* fp;
		fp = fopen("../output/descriptor.txt", "wb");
		write_points(fp, corner, *cornerNum);
		fclose(fp);
	}


}
void asCornerUnInit()
{
	asFree(p_gCornerAlg, sizeof(CornerAlgInfo));
	p_gCornerAlg = NULL;
	printf("%s\n", __FUNCTION__);
}