#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "string.h"
#include "../include/as_Platform.h"
#ifdef WIN32
#include "cv.h"
#endif


void* alMalloc( unsigned int size, int alignment ) ;
void alFree(void* aligned);

#if 0
void asPrintf(char *format, ...) 
{ 
	char BMprintfbuf[1024];
	va_list ap; 
	va_start(ap,format); 
	memset(BMprintfbuf,0,sizeof(BMprintfbuf)); 
	vsprintf(BMprintfbuf,format,ap); 

	printf(BMprintfbuf);
	va_end(ap); 
}
#endif
void* asMalloc(unsigned int Flg,unsigned int len,unsigned int align)
{
	void *p =NULL;
	if( len > 0 )
	{
#if (!defined OPTS_CODE) ||(defined WIN32)
		p = alMalloc(len, align);
#else
#ifdef HK_DSP
		if(Flg)
		{
			Flg = (1<<5);
		}
		else
		{
			Flg = (1<<4);
		}
		p = MP_AllocMem(Flg,len,align);
#endif

#ifdef TIANDY_DSP
		if(Flg)
		{
			Flg = (1<<5);
		}
		else
		{
			Flg = (1<<4);
		}
		p = ITS_AllocMem(Flg,len,align);
#endif
#endif
		if(p == NULL)
		{
			asPrintf("asMalloc error\n");
			asAssert(0);
		}
	}
	return(p);
}

void asFree(void* ptr,unsigned int len)
{

	if( len > 0 )
	{
		if (ptr != NULL)
		{
			alFree(ptr);//标准C内存对齐分配后释放
		}
		else
		{
			asPrintf("TD_Alg_MEM_free error\n");
			asAssert(0);
		}

	}

}

long long  asGetTickCount(void)
{
#ifdef WIN32
	long long time = cvGetTickCount();
	return time;
#endif

}




// wrapper functions if compiling from C/C++}
void* wrMalloc( unsigned int size ) 
{ 
	return malloc(size);
}
void wrFree( void * ptr )
{ 
	free(ptr);
}
// platform independent aligned memory allocation (see also alFree)
void* alMalloc( unsigned int size, int alignment ) 
{
#ifndef __x86_64__
	const unsigned int pSize = sizeof(void*), a = alignment-1;
	void *raw = wrMalloc(size + a + pSize);
	void *aligned = (void*) (((unsigned int) raw + pSize + a) & ~a);
	*(void**) ((unsigned int) aligned-pSize) = raw;
	return aligned;
#else
	void *raw;
	void *aligned;
	const unsigned long long pSize = sizeof(void*), a = alignment-1;
	raw = wrMalloc(size + a + pSize);
	aligned = (void*) (((unsigned long long) raw + pSize + a) & ~a);
	*(void**) ((unsigned long long) aligned-pSize) = raw;
	return aligned;
#endif
}
// platform independent alignned memory de-allocation (see also alMalloc)
void alFree(void* aligned)
{
	void* raw = *(void**)((char*)aligned-sizeof(void*));
	wrFree(raw);
}
