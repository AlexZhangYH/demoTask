// ee754.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

float HexToFloatConverter(unsigned char ptr[]);

int main()
{
    //{ 0x01, 0x03, 0x04, 0x27, 0x52, 0x3F, 0xC0, 0x40, 0xF6 };
    //CDAB
    unsigned char array[] = { 0x3F, 0xC0, 0x27, 0x52 };//{ 0x01, 0x03, 0x04, 0x27, 0x52, 0x3F, 0xC0, 0x40, 0xF6 };
    float res = HexToFloatConverter(array);
    cout << "Hello World: "<< res << endl;
    do
    {
        cout << '\n' << "Press a key to continue...";
    } while (cin.get() != '\n');
    return 0;
}

#define BIAS 150

float HexToFloatConverter(unsigned char ptr[])
{
    //unsigned char ptr[4] = { 0x42,0x4c,0xe0,0x27 };
    // take care of endianness, which may vary between native float and native int
    uint32_t tmp = (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];
    uint32_t sign = tmp >> 31;
    uint32_t exp = (tmp >> 23) & 0xff;
    uint32_t mantissa = tmp & ((1 << 23) - 1);
    float result;
    if (exp > 0)
        mantissa |= (1 << 23);                        // Handle denormals && Inf

     // all integers < 16777216 can be represented exactly as a float
     // multiply that by a power of two

    result = ldexpf((float)mantissa, exp - BIAS);    // in <math.h>

    if (exp == 255 && mantissa != 0)  // Produce NaN from Inf-Inf
        result = (result - result);

    if (sign) 
        result = - result;       // Flip sign (also handles -0.0f)
    return result;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
