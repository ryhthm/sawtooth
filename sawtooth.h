#ifndef _SAWTOOTH_H_
#define  _SAWTOOTH_H_

//extern short sawtoothValue[64];
void generateSawtooth_original(short* pSawtoothVlaue);
void generateSawtooth(short* pSawtoothVlaue);
void generateSawtooth_opt(short* pSawtoothVlaue);
void generateSawtooth_optimize(short* pSawtoothVlaue);


//extern short first64Values[64];
void generate64BaseSawtooth(short* pSawtoothVlaue);
void generateSawtooth_simple(short* pSawtoothVlaue, short* pFirst64Values);

#endif // !_SAWTOOTH_H_