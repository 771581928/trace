#include "stdio.h"

#include "../include/as_track.h"
#include "../include/as_track_alg.h"
#include "../../detect_lib/include/as_detect.h"
TrackAlgInfo gAlgInfo;
extern void showAlgInfo();
void asTrackInit(AlgParams*params)
{
	printf("%s\n",__FUNCTION__);
	asDetectInit(params->img_w, params->img_h);

}
void asTrackProcess(AlgFrame*frame)
{
	gAlgInfo.img_y = frame->y;
	gAlgInfo.img_w = frame->img_w;
	gAlgInfo.img_h = frame->img_h;
	printf("frameid %d tts %lld\n,", frame->frameId, frame->tts);
	asDetectProcess(gAlgInfo.img_y, gAlgInfo.img_w, gAlgInfo.img_h, gAlgInfo.asDetectedBoxes,&gAlgInfo.asDetectNum);
	showAlgInfo();
	printf("%s\n", __FUNCTION__);
}
void asTrackUinit()
{
	printf("%s\n", __FUNCTION__);
}


