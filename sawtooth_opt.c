
#include <stdio.h>
#include <stdlib.h>

/************************************************************
frequency	: 	1HZ
fs			:	0.8
fullscale	:	PCM16bit,(short)1<<15-1)=32767
sampleRate	:	48000HZ
pointNumInPeriod	:	48000, for 1HZ (1second)

initAmplitudeValue	:	-0.8*fullscale=-0.8*32767=-26213.6
deltAmplitudeValue	:	(0.8-(-0.8))*(fullscale)/48000

core function		:	(0.8/24000)(x-24000),x~(0,47999)
					:	=>1/30000(x-24000)
author				:	lihuosheng; virlhs@sina.com
data				:	2020.03.06,23:52

*************************************************************/

/*************************************************************
the frequency of the caller MAIF is 750HZ,so for the 48000 sampleRate,
there are about 48000*(1/750)=64 point for onece call.

*************************************************************/
void generateSawtooth_original(short* pSawtoothVlaue)
{
	static int _x1 = 0;
	//static float _baseValue0 = -26213.6;
	//float deltAmplitudeValue = 1.0922333;
	float value = 0;
	int y = 0;

	for (y = 0; y < 64; y++)
	{
		_x1 %= 48000;
		/*
		if (!_x1)
		{
			_baseValue0 = -26213.6;
		}
		*/
		value = (1.0/30000) * (_x1 - 24000) * (((short)1 << 15) - 1);
		pSawtoothVlaue[y] = (short)value;
		//_baseValue0 += deltAmplitudeValue;
		++_x1;
	}
}

/*************************************************************/
//short sawtoothValue[64];
void generateSawtooth(short *pSawtoothVlaue)
{
	static int _x1=0;
	static float _baseValue0 = -26213.6;
	float deltAmplitudeValue = 1.0922333;
	int y=0;
	
	for(y=0;y<64;y++)
	{	
		_x1 %=48000;
		if(!_x1)
		{
			_baseValue0=-26213.6;
		}
		pSawtoothVlaue[y]=(short)_baseValue0;
		_baseValue0+= deltAmplitudeValue;
		++_x1;
	}
}

/*************************************************************
convert the float point  to fix point.
*************************************************************/
void generateSawtooth_opt(short *pSawtoothVlaue)
{
	static int _x2=0;
	//static short baseValue = -26213.6;
	//float deltAmplitudeValue = 1.0922333;
	static int _baseValue2 = -26764085; //26213.6 *1024;
	int deltAmplitudeValue = 1118;//1.0922333*1024;
	int y=0;
	
	for(y=0;y<64;y++)
	{	
		_x2 %=48000;
		if(!_x2)
		{
			_baseValue2=-26764085;
		}
		pSawtoothVlaue[y]=(short)(_baseValue2 >>10);
		_baseValue2 += deltAmplitudeValue;
		++_x2;
	}
}
/*************************************************************
cancle the judgment in the for loop.
*************************************************************/
void generateSawtooth_optimize(short *pSawtoothVlaue)
{
	static int x=0;
	//static short baseValue = -26213.6;
	//float deltAmplitudeValue = 1.0922333;
	static int baseValue = -26764085; //26213.6 *1024;
	int deltAmplitudeValue = 1118;//1.0922333*1024;
	int y=0;
	
	for(y=0;y<64;y++)
	{	/*
		x%=48000;
		if(!x)
		{
			baseValue=-26764085;
		}*/
		pSawtoothVlaue[y]=(short)(baseValue>>10);
		baseValue+= deltAmplitudeValue;
		//++x;
	}
	x += 64;
	x%=48000;
	if(!x)
	{
		baseValue=-26764085;
	}
}
/*************************************************************
enable the pipeline for loop.
*************************************************************/
//short first64Values[64];
void generate64BaseSawtooth(short *pSawtoothVlaue)
{
	//int x=0;
	//static short baseValue = -26213.6;
	//float deltAmplitudeValue = 1.0922333;
	int _baseValue = -26764085; //26213.6 *1024;
	int _deltAmplitudeValue = 1118;//1.0922333*1024;
	int y=0;
	
	for(y=0;y<64;y++)
	{	/*
		x%=48000;
		if(!x)
		{
			baseValue=-26764085;
		}*/
		pSawtoothVlaue[y]=(short)(_baseValue>>10);
		_baseValue+= _deltAmplitudeValue;
		//++x;
	}
	
/*	x%=48000;
	if(!x)
	{
		baseValue=-26764085;
	}*/
}

void generateSawtooth_simple(short * pSawtoothVlaue,short *pFirst64Values)
{
	static int x=0;
	//static short baseValue = -26213.6;
	//float deltAmplitudeValue = 1.0922333;
	//static int baseValue = -26764085; //26213.6 *1024;
	int deltAmplitudeValue = 70;//1.0922333*64=69.902912;
	int y=0;
	

	
	x%=48000;
	if(!x)
	{
		//memcpy(pSawtoothVlaue, first64Values,sizeof(short)*64);
		for (y = 0; y < 64; y++)
		{
			pSawtoothVlaue[y] = pFirst64Values[y];
		}
	}
	else
	{
		for (y = 0; y < 64; y++)
		{	/*
			x%=48000;
			if(!x)
			{
				baseValue=-26764085;
			}*/
			pSawtoothVlaue[y] += deltAmplitudeValue;
			//baseValue+= deltAmplitudeValue;
			//++x;
		}
	}
	x += 64;
}


/*************************************************************
enable the pipeline for loop.for DSP
*************************************************************/
//short first64Values[64];
void generate64BaseSawtooth(short* pSawtoothVlaue)
{
	//int x=0;
	//static short baseValue = -26213.6;
	//float deltAmplitudeValue = 1.0922333;
	int _baseValue = -26764085; //26213.6 *1024;
	int _deltAmplitudeValue = 1118;//1.0922333*1024;
	int y = 0;

	for (y = 0; y < 64; y++)
	{	/*
		x%=48000;
		if(!x)
		{
			baseValue=-26764085;
		}*/
		pSawtoothVlaue[y] = (short)(_baseValue >> 10);
		_baseValue += _deltAmplitudeValue;
		//++x;
	}

	/*	x%=48000;
		if(!x)
		{
			baseValue=-26764085;
		}*/
}

void generateSawtooth_simple(short* restrict pSawtoothVlaue, short* restrict pFirst64Values)
{
	static int x = 0;
	//static short baseValue = -26213.6;
	//float deltAmplitudeValue = 1.0922333;
	//static int baseValue = -26764085; //26213.6 *1024;
	int deltAmplitudeValue = 70;//1.0922333*64=69.902912;
	int y = 0;



	x %= 48000;
	if (!x)
	{
		//memcpy(pSawtoothVlaue, first64Values,sizeof(short)*64);
		for (y = 0; y < 64; y++)
		{
			pSawtoothVlaue[y] = pFirst64Values[y];
		}
	}
	else
	{
		for (y = 0; y < 64; y++)
		{	/*
			x%=48000;
			if(!x)
			{
				baseValue=-26764085;
			}*/
			pSawtoothVlaue[y] += deltAmplitudeValue;
			//baseValue+= deltAmplitudeValue;
			//++x;
		}
	}
	x += 64;
}


