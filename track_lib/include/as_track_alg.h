#ifndef __AS_TRACK_ALG_H__
#define __AS_TRACK_ALG_H__

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */

#define MAX_DETECTED_BOXES_NUM 50

typedef struct _AsRect
{
	int x;
	int y;
	int width;
	int height;
}AsRect;
typedef struct _AsBox
{
	int x;
	int y;
	int width;
	int height;
	float score;
	int type;
}AsBox;

typedef struct AsPoint
{
	int x;
	int y;
}AsPoint;



typedef struct _TrackAlgInfo
{
	unsigned  char *img_y;
	unsigned  char *img_uv;
	int img_w;
	int img_h;
	int asDetectNum;
	AsBox asDetectedBoxes[MAX_DETECTED_BOXES_NUM];

}TrackAlgInfo;












#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif