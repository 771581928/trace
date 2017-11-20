/*******************************************************************************
* KKDJ_Platform.h
*
* Copyright (C) 2010-2013 Bocom Technology CO.,LTD.
*
* Author : 
* Version: V1.00.0  2015-10-14 Create
*
* Description: �羯������ƽ̨���
*
* Modification: 
* 1. Date    : 2015-10-14
*    Revision: V1.01.0
*    Author  : 
*    Contents: 
*******************************************************************************/
#ifndef __AS_PLATFORM_H__
#define __AS_PLATFORM_H__

#ifdef __cplusplus
extern "C"{
#endif
#include <assert.h>
#include <stdio.h>




#define ALG_MEM_NO_CACHE 0 /* ��ʹ��CACHE */ 
#define ALG_MEM_CACHED 1 /* ʹ��CACHE */ 

#define AS_ALIGN_BYTE 1
#define AS_ALIGN_4BYTE_SIZE 4
#define AS_ALIGN_16BYTE_SIZE 16
#define AS_ALIGN_32BYTE_SIZE 32
#define AS_ALIGN_128BYTE_SIZE 128
#define AS_ALIGN_256BYTE_SIZE 256

#define asAssert assert
#define asPrintf printf



void* asMalloc(unsigned int Flg,unsigned int len,unsigned int align);


void asFree(void* ptr,unsigned int len);

long long asGetTickCount(void);

#ifdef __cplusplus
}
#endif

#endif  /* __KKDJ_PLATFORM_H__ */
