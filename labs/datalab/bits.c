/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /* De Morgan's Laws */
  return ~((~x) & (~y)) & ~(x & y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /* Tmin: 10000...0 (32 bits) -> -2,147,483,648 */
  return 1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* Tmax: 0111...1 (32 bits) -> 2,147,483,647 
   *   Tmax + 1 = 1000...0
   *   ~(Tmax + 1) = 0111...1
   *   Tmax ^ (~(Tmax + 1)) == 0 ? 1 : 0
   *
   * Exception: 
   *   x = 1111...1
   *   x + 1 = 0000...0 
   *   
   * !!(non-zero number) = 1
   * !!0 = 0
   */
  return (!(x ^ (~(x + 1)))) & (!!(x + 1));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /* 1010 -> A
   * 0 can be considered as a mask
   * (num & A) ^ A == 0
   */
  int A = 0xA;
  int AA = A | (A << 4);
  int AAAA = AA | (AA << 8);
  int mask = AAAA | (AAAA << 16);
  return !((x & mask) ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /* 0x30 -> 110000
   * 0x39 -> 111001
   * 
   * cond1 -> 000... before last 6 bits
   *   x >>= 6
   *   !x
   * 
   * cond2 -> 11xxxx
   *   x >>= 4
   *   (x ^ 0b11) == 0 ? 1 : 0
   *   !(x ^ 0b11)
   *  
   *  cond3 -> 
   *  c = x & 0xF -> truncate last 4 bits
   *  d = c - A < 0 -> need to check the sign bit
   *  !!(d >>= 31)
   */

  // 1. leading 26 zeros
  int a = x >> 6;
  int cond1 = !a; // 1

  // 2. 11xxxx
  int b = x >> 4;
  int cond2 = !(b ^ 0x3);

  //3. xxxx - A < 0
  int c = x & 0xF;
  int negate_A = ~0xA + 1;
  int res = c + negate_A;
  int cond3 = !!(res >> 31);

  return cond1 & cond2 & cond3;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /* a = !!x
   * b = a << 31 >> 31
   * x = 0 -> a = 0 -> b = 0
   * x = 1 -> a = 1 -> b = 1111...1
   */
  int mask = ((!!x) << 31) >> 31;
  return ((~mask) & z) | (mask & y);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /* cond1 -> x == y ? 1 : 0
   *   !(x ^ y);
   * 
   * signX = x >> 31 & 1
   * signY = y >> 31 & 1
   * 
   * cond2 -> forbid x > 0 and y < 0  
   *   !signX & signY -> 1
   * 
   * cond3 -> x < 0 and y > 0
   *   signX & !signY -> 1
   * 
   * cond4 -> same sign
   *   (x - y) >> 31 & 1
   *   
   * return cond1 | (!cond2 && (cond3 | cond4))
   */
  // x == y
  int cond1 = !(x ^ y);

  int signX = (x >> 31) & 0x1;
  int signY = (y >> 31) & 0x1;

  // x+ y- 
  int cond2 = !((!signX) & signY);

  // x- y+
  int cond3 = signX & !signY;

  // same sign
  int cond4 = ((x + (~y) + 1) >> 31) & 0x1;

  return cond1 | (cond2 & (cond3 | cond4));
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /* if x != 0 return 0 else 1 */
  int negX = ~x + 1;
  int sign = (negX | x) >> 31;
  return sign + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  /* 1111 -> -1, 111 -> -1, 11 -> -1, 1 -> -1 
   * if (x == 0)
   *   return 1;
   * else {
   *   x > 0 -> 1 + highBit //e.g. 0100 highBit = 3
   *   x < 0 -> e.g. 1 1111 0001 // replace the four digits before highBit
   * } 
   */
  int bit_16, bit_8, bit_4, bit_2, bit_1, bit_0, res;

  int isZero = !x;

  int sign = x >> 31;
  int mask = ((!!x) << 31) >> 31;
  x = ((~sign) & x) | (sign & (~x)); // get the highest bits

  // e.g.1  0000 0000 0000 0000 | 0000 0000 0000 0000
  //        1. a = x >> 16 -> truncate
  //        2. b = !(!!(a) ^ 0x1) -> !(0 ^ 1) = 0
  //        3. b << 4 -> 0
  // e.g.2  0000 0100 0000 0000 | 0000 0000 0000 0000
  //        1. a = x >> 16
  //        2. b = !(!!(a) ^ 0x1) -> !(1 ^ 1) = 1
  //        3. b << 4 -> 16
  // This condition ensures the necessity of lowest 16 bits
  bit_16 = (!((!!(x >> 16)) ^ (0x1))) << 4; // 0
  // bit_16 == 16 -> ignore lowest 16 bits and check highest 16 bits
  // bit_16 == 0 -> ignore highest 16 bits and check lowest 16 bits
  x >>= bit_16;

  bit_8 = (!((!!(x >> 8)) ^ (0x1))) << 3; 
  x >>= bit_8;

  bit_4 = (!((!!(x >> 4)) ^ (0x1))) << 2; 
  x >>= bit_4;

  bit_2 = (!((!!(x >> 2)) ^ (0x1))) << 1; 
  x >>= bit_2;

  bit_1 = (!((!!(x >> 1)) ^ (0x1))); 
  x >>= bit_1;

  bit_0 = x;

  // 1 stands for the sign digit
  res = 1 + bit_16 + bit_8 + bit_4 + bit_2 + bit_1 + bit_0;

  return isZero | (mask & res);
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  // get expr, s, frac
  unsigned s = (uf >> 31) & (0x1);
  unsigned expr = (uf >> 23) & (0xFF);
  unsigned frac = uf & 0x7FFFFF;

  // 0
  if (expr == 0 && frac == 0) {
    return uf;
  }
  // inifity or nan
  if (expr == 0xFF) {
    return uf;
  }  
  // denormalised
  if (expr == 0) {
    // E = expr - 127 = -127 
    // frac * 2
    frac <<= 1;
    return (s << 31) | frac; 
  }
  // normalised
  // V = (-1)^S * M * 2^E
  // expr++ , E = expr - 127 -> E += 1 -> V *= 2
  expr++;
  return (s << 31) | (expr << 23) | frac;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  // get expr, s, frac
  int E;
  unsigned s = (uf >> 31) & (0x1);
  unsigned expr = (uf >> 23) & (0xFF);
  unsigned frac = uf & 0x7FFFFF;

  // 0
  if (expr == 0 && frac == 0) {
    return 0;
  }
  // inifity or nan
  if (expr == 0xFF) {
    return 0x80000000u;
  }
  // denormalised
  if (expr == 0) {
    // M 0.xxxxx(2) < 1
    // E = 1 - 127 = -126
    // too small
    return 0;
  }
  // normalised
  // M 1.xxxxx(2) -> 1 stands for 2^0
  E = expr - 127;
  frac = frac | (1 << 23);
  // e.g. 111 0000 0000 0000 0000 0000 -> a 23-bit fraction
  //    1 (leading one) | 111 0000 0000 0000 0000 0000
  //    if E < 0, M = 1.xxxx -> M / 2 < 1
  //    if E >= 23, the decimal point can be moved to the end, even further
  //    else, the 23-bit fraction needs to be truncated
  if (E > 31) {
    return 1 << 31;
  } else if (E < 0) {
    return 0;
  } else if (E >= 23) {
    frac <<= (E - 23);
  } else {
    frac >>= (23 - E);
  }

  if (s) {
    return ~frac + 1;
  } 
  return frac;
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
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  // 2.0^x > 0 -> V = M * 2^E 
  // ------------------------------------------------------------------------------------
  // denormalised  | 2^(-23) * 2^(-126)  | 2^(-23) + 2^(-22) + ... + 2^(-1) < 2^(-126)
  // ------------------------------------------------------------------------------------
  //  normalised   |       2^(-126)      | E = 11111110 254 - 127 = 127 -> 2^127 ~ 2^128
  // ------------------------------------------------------------------------------------
  //               |     lowerbound      |   upperbound

  if (x < -149) {
    return 0;
  } else if (x < -126) {
    // E = x
    // E = 1 - 127 = -126
    // M * 2^(-126) = 2^x
    // M = x + 126
    int shift = 23 + (x + 126);
    return 1 << shift;
  } else if (x <= 127) {
    // x = expr - bias
    int expr = x + 127;
    return expr << 23;
  } else {
    return (0xFF) << 23; //+INF
  }
}
