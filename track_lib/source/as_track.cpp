#include <stdio.h>
#include <math.h>
#include "string.h"
#include "../include/as_alg_private.h"
#include "../include/as_track.h"

extern AlgInfo gAlgInfo;
extern const int PREDICT_X_REGION ;
extern const int PREDICT_Y_REGION;


void cornerMatchStatusInit()
{
	memset(&gAlgInfo.asCornerMatchStatus, 0, sizeof(gAlgInfo.asCornerMatchStatus));
}


void addNewTrack(TrackAlgInfo *pTrack, AsCorner *corner, int frame_id, unsigned long long frame_tts)
{
	pTrack->trackId = frame_id;
	pTrack->beginTTs = frame_tts;
	pTrack->trackPoint[0].x = corner->x;
	pTrack->trackPoint[0].y = corner->y;
	pTrack->trackPoint[0].val = corner->val;
	memcpy(pTrack->trackPoint[0].brief, corner->brief, 32);
	pTrack->trackLength = 1;
}


void addTrackPoint(TrackAlgInfo *pTrack, AsCorner *corner, int frame_id, unsigned long long frame_tts)
{
	pTrack->trackId = frame_id;
	pTrack->lastTTs = frame_tts;
	pTrack->trackPoint[pTrack->trackLength].x = corner->x;
	pTrack->trackPoint[pTrack->trackLength].y = corner->y;
	pTrack->trackPoint[pTrack->trackLength].val = corner->val;
	memcpy(pTrack->trackPoint[pTrack->trackLength].brief, corner->brief, 32);
	pTrack->trackLength++;
}


void deleteTrack(TrackAlgInfo *pTrack)
{
	memset(pTrack, 0, sizeof(TrackAlgInfo));
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
	//boxs
	return 0;

}



unsigned int hamming_dist(unsigned char* query_desc, unsigned char* train_desc)
{
	unsigned short count = 0;
	for (int i = 0; i < 32; i++){
		unsigned int x = query_desc[i] ^ train_desc[i];
		while (x){
			count++;
			x &= x - 1;
		}
	}
	return count;
};


bool descriptor_match(unsigned char* query_desc, unsigned char* train_desc, unsigned int thresh)//todo 单个描述子匹配
{
	unsigned int dist = hamming_dist(query_desc, train_desc);
	if (dist < thresh)
		return true;
	else
		return false;
};


void asTrackProcess(AsCorner *corner, int cornerNum, int frame_id, unsigned long long frame_tts)
{
	TrackAlgInfo *pTrack = gAlgInfo.asTrack;
	if (frame_id == 0)
	{
		for (int i = 0; i < cornerNum; i++)
		{
			addNewTrack(&(pTrack[i]), &(corner[i]), frame_id, frame_tts);
			gAlgInfo.asTrackNum++;
		}
	}
	else if (frame_id > 0)
	{
		cornerMatchStatusInit();
		for (int i = 0; i < gAlgInfo.asTrackNum; i++)
		{
			if ((frame_id - pTrack[i].trackId) > 2)
			{
				deleteTrack(&(pTrack[i]));
				gAlgInfo.emptyTrackIdx[gAlgInfo.emptyTrackNum] = i;
				gAlgInfo.emptyTrackNum++;
			}
			else
			{
				for (int j = 0; j < cornerNum; j++)
				{
					bool match_state = false;
					if (abs(pTrack[i].trackPoint[pTrack[i].trackLength - 1].x - corner[j].x) < PREDICT_X_REGION &&//PREDICT_X_REGION
						abs(pTrack[i].trackPoint[pTrack[i].trackLength - 1].y - corner[j].y) < PREDICT_Y_REGION)//PREDICT_Y_REGION
						match_state = descriptor_match(pTrack[i].trackPoint[pTrack[i].trackLength - 1].brief, corner[j].brief, 50);
					if (match_state)
					{
						addTrackPoint(&(pTrack[i]), &(corner[j]), frame_id, frame_tts);
						gAlgInfo.asCornerMatchStatus[j] = 1;
						break;
					}
				}
			}
		}
		for (int i = 0; i < cornerNum; i++)
		{
			if (!gAlgInfo.asCornerMatchStatus[i])
			{
				if (gAlgInfo.emptyTrackNum)
				{
					gAlgInfo.emptyTrackNum--;
					addNewTrack(&(pTrack[gAlgInfo.emptyTrackIdx[gAlgInfo.emptyTrackNum]]), &(corner[i]), frame_id, frame_tts);
				}
				else
				{
					addNewTrack(&(pTrack[gAlgInfo.emptyTrackNum]), &(corner[i]), frame_id, frame_tts);
					gAlgInfo.asTrackNum++;
				}
			}

		}
	}
	else
		printf("frame_id error\n");
	for (int i = 0; i < gAlgInfo.asTrackNum; i++)
	{
		generateMatchRect(&pTrack[i]);

	}

}





