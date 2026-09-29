/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if((x & (1 << 31)) ^ (y & (1<<31))) return 0;
    if(!(x && y)){
        if(x ^ y) return 0;
        else return 1;
    }
    return 1;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int a = ((v >> 16) > 0) << 4;
    v = v >> a;
    int b = ((v >> 8) > 0) << 3;
    v = v >> b;
    int c = ((v >> 4) > 0) << 2;
    v = v >> c;
    int d = ((v >> 2) > 0) << 1;
    v = v >> d;
    int e = (v >> 1) > 0; 

    return a | b | c | d | e;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int mov1 = n << 3;
    int mov2 = m << 3;
    int get1 = ((x >> mov1) & 0xFF) << mov2;
    int get2 = ((x >> mov2) & 0xFF) << mov1;
    x = x & (~((0xFF << mov1) | (0xFF << mov2)));
    x = x | get1 | get2;
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    int n = 16;
    while(n){
        int i = 16 - n;
        int headidx = 31 - i;
        int num1 = ((v >> headidx) & 1) << i;
        int num2 = ((v >> i) & 1) << headidx;
        v = ((~((1 << headidx) | (1 << i))) & v) | num1 | num2;
        n = n - 1;
    }
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask = ~(((1 << 31) >> n) << 1);
    x = (x >> n) & mask;
    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int v = ~x;

    int a = (!!(v >> 16)) << 4;
    v = v >> a;
    int b = (!!(v >> 8)) << 3;
    v = v >> b;
    int c = (!!(v >> 4)) << 2;
    v = v >> c;
    int d = (!!(v >> 2)) << 1;
    v = v >> d;
    int e = !!(v >> 1); 
    v = v >> e;

    int n = 32 + (~(a + b + c + d + e + v) + 1);
    return n & (x >> 31);
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    int mask = 1 << 31;
    int fuhao = x & mask;
    int n = 0;
    int drop;
    int weishu;
    int jiema;
    if (!x) return 0;
    if (x < 0) x = -x;
    while (!(x & mask)){
        x = x << 1;
        n = n + 1;
    }
    drop = x & 0xFF;
    weishu = (x >> 8) & ((1 << 23) - 1);
    if (drop > 128){
        weishu = weishu + 1;
    } 
    else if(drop == 128){
        if(weishu & 1){
            weishu = weishu + 1;
        }
    }
    jiema = 158 - n;
    return fuhao | ((jiema << 23) + weishu);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    int mask = 0xFF;
    int jiema = ((uf >> 23) & 0xFF) + 1;
    int fuhao = uf & (1 << 31);
    if(jiema == 256) return uf;
    if(jiema == 1) return fuhao | (uf << 1);
    if(jiema == 255) return fuhao | (255 << 23);
    return (uf & ~(mask << 23)) | (jiema << 23);
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int fuhao = uf2 & (1 << 31); //yuanwei
    int jiema = (uf2 >> 20) & (((1 << 11) - 1)); //feiyuanwei
    if(jiema >= 1054) return 1 << 31;
    if(jiema < 1023) return 0;
    int pinjie = ((uf2 << 10) | (uf1 >> 22) | (1 << 30)) & ~(1 << 31);
    int result = pinjie >> (30 - (jiema - 1023));
    if(fuhao) return ~result + 1;
    return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x >= 128) return ((1 << 8) - 1) << 23;
    if(x <= -150) return 0;
    int jiema = 127 + x;
    if(jiema <= 0) return (1 << 23) >> (-jiema + 1);
    return jiema << 23;
}
