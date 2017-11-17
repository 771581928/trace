#ifndef __AS_TRACK_H__
#define __AS_TRACK_H__

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */

typedef struct _AlgParams
{
	//mask ROI
	// control sect..so on
}AlgParams;

typedef struct _AlgFrame
{
	//
	unsigned long long tts;
	unsigned int  frameId;
	unsigned char *y;
	unsigned char*uv;
	int img_w;
	int img_h;
}AlgFrame;


void asTrackInit(AlgParams*params);
void asTrackProcess(AlgFrame*frame);
void asTrackUinit();




#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif