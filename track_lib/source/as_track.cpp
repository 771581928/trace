#include "string.h"
#include "../include/as_alg_private.h"
extern AlgInfo gAlgInfo;
void cornerMatchStatusInit()
{
	memset(&gAlgInfo.asCornerMatchStatus, 0, sizeof(gAlgInfo.asCornerMatchStatus));
}
void addNewTrack()
{

}
AsRect generateMatchRect(TrackAlgInfo *pTrack)
{
	AsRect ret;
	AsPoint ptPredict;
	
	int dx;
	int dy;
	int nTrackLen;
	nTrackLen = pTrack->trackLength;

	if (1 == nTrackLen)
	{
		ptPredict.x = pTrack->trackPoint[0].x;
		ptPredict.y = pTrack->trackPoint[0].y;
	}
	else if (2 == nTrackLen)
	{
		dx = pTrack->trackPoint[1].x - pTrack->trackPoint[0].x;
		dy = pTrack->trackPoint[1].y - pTrack->trackPoint[0].y;
		ptPredict.x = pTrack->trackPoint[1].x + dx;
		ptPredict.y = pTrack->trackPoint[1].y + dy;
	}
	else
	{
		dx = (pTrack->trackPoint[nTrackLen - 1].x - pTrack->trackPoint[nTrackLen - 3].x) >> 1;
		dy = (pTrack->trackPoint[nTrackLen - 1].y - pTrack->trackPoint[nTrackLen - 3].y) >> 1;
		ptPredict.x = pTrack->trackPoint[nTrackLen - 1].x + dx;
		ptPredict.y = pTrack->trackPoint[nTrackLen - 1].y + dy;
	}

	if (ptPredict.x < 0
		|| ptPredict.x >= gAlgInfo.img_w
		|| ptPredict.y < 0
		|| ptPredict.y >= gAlgInfo.img_w)
	{
		ptPredict.x = pTrack->trackPoint[nTrackLen - 1].x;
		ptPredict.y = pTrack->trackPoint[nTrackLen - 1].y;
	}
	//TODO: point2rect
	ret.x = 0;
	ret.y = 0;
	ret.width = 0;
	ret.height = 0;
	return ret;
}
int findMatchTrackPoint()
{
	//box里面取的匹配的值
	return 0;

}
void addTrackPoint()
{

}
void asTrackProcess()
{
	TrackAlgInfo *pTrack = gAlgInfo.asTrack;
	cornerMatchStatusInit();
	
	for (int i = 0; i < gAlgInfo.asTrackNum;i++)
	{
		generateMatchRect(&pTrack[i]);



	}



}





