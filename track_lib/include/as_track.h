#ifndef __AS_TRACK_H__
#define __AS_TRACK_H__

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */


//void asTrackInit(AlgParams*params);
//void asTrackProcess(AlgFrame*frame);
//void asTrackUinit();
	void asTrackProcess(AsCorner *corner, int cornerNum, int frame_id, unsigned long long frame_TTS);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif