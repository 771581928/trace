#ifndef __AS_CORNER_H__
#define __AS_CORNER_H__
#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */
#include "../include/as_alg_private.h"

void asCornerInit(int img_w,int img_h);
void asCornerProcess(unsigned char *img, AsCorner *corner, int *cornerNum);
void asCornerUnInit();

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif