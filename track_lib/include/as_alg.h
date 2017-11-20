#ifndef __AS_ALG_H__
#define __AS_ALG_H__

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */

typedef struct _AlgParams
{
	//mask ROI
	// control sect..so on
	int img_w;
	int img_h;
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


void asAlgInit(AlgParams*params);
void asAlgProcess(AlgFrame*frame);
void asAlgUinit();




#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif