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
void asCornerProcess(unsigned char *img, AsCorner *corner, int *cornerNum)
{
	printf("%s\n", __FUNCTION__);

	//add orb daima



}
void asCornerUnInit()
{
	asFree(p_gCornerAlg, sizeof(CornerAlgInfo));
	p_gCornerAlg = NULL;
	printf("%s\n", __FUNCTION__);
}