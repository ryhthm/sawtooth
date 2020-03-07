//extern short sawtoothValue[64];
void generateSawtooth_original(short* pSawtoothVlaue);
void generateSawtooth(short* pSawtoothVlaue);
void generateSawtooth_opt(short* pSawtoothVlaue);
void generateSawtooth_optimize(short* pSawtoothVlaue);


//extern short first64Values[64];
void generate64BaseSawtooth(short* pSawtoothVlaue);
void generateSawtooth_simple(short* pSawtoothVlaue, short* pFirst64Values);

这里面的的基本思想：
1	最原始的方法，浮点
2	消除原始方法中浮点的除法
3	利用插值法，同时，消除浮点运算
4	消除for循环中多余的运算操作【最为关键】，消除for循环中的判断语句
5	利用部分查表法，可以充分利用DSP的流水性能。	