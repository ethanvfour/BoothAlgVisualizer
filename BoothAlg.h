#ifndef BOOTH_ALG
#define BOOTH_ALG

#include <iostream>
#include <queue>

class BoothAlg
{
    std::string multiplierString;
    //the string version of the multiploer

    std::string multiplicandString;
    //the string version of the multiplicand

    /*
    Converts a number into a string.
    */
    std::string convertIntToBinaryString(int number);


    /*
    Does one's complement to the string given
    */
    void onesComplement(std::string &binaryNum);


    /*
    Does two's complement to the string given
    */
    void twosComplement(std::string &binaryNum);

    /*
    Adds two ints in binary, "very exciting"
    */
    std::string addBinary(std::string first, std::string second);

public:
    /*
    The default constructor
    Should NOT be called, if called, call the setter afterwards to set the values to the numbers
    */
    BoothAlg();

    /*
    The function to call to do booth alg to 2 32-bit integers
    */
    void run();
};


#endif