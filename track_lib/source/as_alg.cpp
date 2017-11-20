#include "stdio.h"

#include "../include/as_alg.h"
#include "../include/as_alg_private.h"
#include "../../detect_lib/include/as_detect.h"
#include "../include/as_corner.h"
TrackAlgInfo gAlgInfo;
extern void showAlgInfo();
void asAlgInit(AlgParams*params)
{
	printf("%s\n", __FUNCTION__);
	asDetectInit(params->img_w, params->img_h);
	asCornerInit(params->img_w, params->img_h);

}
void asAlgProcess(AlgFrame*frame)
{
	gAlgInfo.img_y = frame->y;
	gAlgInfo.img_w = frame->img_w;
	gAlgInfo.img_h = frame->img_h;
	printf("frameid %d tts %lld\n,", frame->frameId, frame->tts);
	asDetectProcess(gAlgInfo.img_y, gAlgInfo.img_w, gAlgInfo.img_h, gAlgInfo.asDetectedBoxes, &gAlgInfo.asDetectNum);
	asCornerProcess(gAlgInfo.img_y, gAlgInfo.asCorner, &gAlgInfo.asCornerNum);
	showAlgInfo();
	printf("%s\n", __FUNCTION__);
}
void asAlgUinit()
{
	printf("%s\n", __FUNCTION__);
}