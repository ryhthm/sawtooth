#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sawtooth.h"

#define TEST0 0
#define TEST1 0
#define TEST2 0
#define TEST3 0
#define TEST4 1

#define PeriodCount 5
int main()
{
	FILE* fp0 = fopen("0.pcm", "wb");
	FILE* fp1 = fopen("1.pcm","wb");
	FILE* fp2 = fopen("2.pcm","wb");
	FILE* fp3 = fopen("3.pcm", "wb");
	FILE* fp4 = fopen("4.pcm", "wb");

	clock_t start, finish;
	double duration = 0.0;

	int loopCount=0;
	int i = 0;
	short pBuf[64] = {0};
#if TEST0

	start = clock();
	for (loopCount = 0; loopCount < 750 * PeriodCount; loopCount++)
	{
		generateSawtooth_original(pBuf);
		//fwrite(pBuf, 1, 2 * 64, fp0);
		//fflush(fp0);
	}
	finish = clock();
	duration = (double)((double)finish - (double)start) / CLOCKS_PER_SEC;
	printf("%f		,", duration);
#endif
#if TEST1

	start = clock();
	for (loopCount = 0; loopCount < 750 * PeriodCount ; loopCount++)
	{
		generateSawtooth(pBuf);
		//fwrite(pBuf,1,2*64,fp1);
		//fflush(fp1);
	}
	finish = clock();
	duration = (double)((double)finish - (double)start) / CLOCKS_PER_SEC;
	printf("%f		,",duration);
#endif

#if	TEST2
	start = clock();
	for (loopCount = 0; loopCount < 750 * PeriodCount; loopCount++)
	{
		generateSawtooth_opt(pBuf);
		//fwrite(pBuf, 1, 2 * 64, fp2);
		//fflush(fp2);
	}
	finish = clock();
	duration = (double)((double)finish - (double)start) / CLOCKS_PER_SEC;
	printf("%f		,", duration);
#endif
#if TEST3
	start = clock();
	for (loopCount = 0; loopCount < 750 * PeriodCount; loopCount++)
	{
		generateSawtooth_optimize(pBuf);
		//fwrite(pBuf, 1, 2 * 64, fp3);
		//fflush(fp3);
	}
	finish = clock();
	duration = (double)((double)finish - (double)start) / CLOCKS_PER_SEC;
	printf("%f		,", duration);
#endif
#if TEST4
	short baseBuf[64];
	start = clock();
	generate64BaseSawtooth(baseBuf);
	for (loopCount = 0; loopCount < 750 * PeriodCount; loopCount++)
	{
		generateSawtooth_simple(pBuf, baseBuf);
		fwrite(pBuf, 1, 2 * 64, fp4);
		fflush(fp4);
	}
	finish = clock();
	duration = (double)((double)finish - (double)start) / CLOCKS_PER_SEC;
	printf("%f		,", duration);
#endif
	fclose(fp0);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	return 0;
}