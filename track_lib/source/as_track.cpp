#include "stdio.h"

#include "../include/as_track.h"
#include "../include/as_track_alg.h"

void asTrackInit(AlgParams*params)
{
	printf("%s\n",__FUNCTION__);
}
void asTrackProcess(AlgFrame*frame)
{
	printf("frameid %d tts %lld\n,", frame->frameId, frame->tts);
	printf("%s\n", __FUNCTION__);
}
void asTrackUinit()
{
	printf("%s\n", __FUNCTION__);
}

