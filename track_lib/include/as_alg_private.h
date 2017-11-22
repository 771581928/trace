#ifndef __AS_ALG_PRIVATE_H__
#define __AS_ALG_PRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */

#define MAX_DETECTED_BOXES_NUM 50

#define MAX_ORB_CORNERS 512 
#define MAX_CORNERS_PER_FRAME 512       
#define MAX_CORNERS_PER_TRACK 512     
#define MAX_TRACKS_PER_FRAME  512     
#define MAX_TRACKS_PER_GROUP 160        
#define MAX_TRACKS_NUMBER (2048*2)
	const int PREDICT_X_REGION = 28;
	const int PREDICT_Y_REGION = 18;


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

typedef struct _AsPoint
{
	int x;
	int y;
}AsPoint;
typedef struct _AsCorner
{
	int x;
	int y;
	int val;
	unsigned char brief[32];//256bit briefDescriptor
} AsCorner;

typedef struct _CornerAlgInfo
{
	int img_w;
	int img_h;
	int cornerThresh;
	int detectCornerNum;
	AsCorner detectCorner[MAX_ORB_CORNERS];
	//int nonMaxCornerNum;
	//AsCorner nonMaxCorner[MAX_CORNERS_PER_FRAME];
}CornerAlgInfo;


typedef struct _TrackAlgInfo
{
	int trackId;
	unsigned long long beginTTs;
	unsigned long long lastTTs;
	int trackLength;
	AsCorner trackPoint[MAX_CORNERS_PER_TRACK];
	unsigned char color[3];//for show
	AsRect matchRect;

}TrackAlgInfo;

typedef struct _AlgInfo
{
	unsigned  char *img_y;
	unsigned  char *img_uv;
	int img_w;
	int img_h;
	int asDetectNum;
	AsBox asDetectedBoxes[MAX_DETECTED_BOXES_NUM];
	int asCornerNum;
	AsCorner asCorner[MAX_CORNERS_PER_FRAME];
	char asCornerMatchStatus[MAX_CORNERS_PER_FRAME];
	int asTrackNum;
	int emptyTrackNum;
	int emptyTrackIdx[MAX_TRACKS_NUMBER];
	TrackAlgInfo asTrack[MAX_TRACKS_NUMBER];

}AlgInfo;












#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif