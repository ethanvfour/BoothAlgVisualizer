#ifndef BOOTH_ALG
#define BOOTH_ALG

#include <iostream>
#include <queue>
#include <limits>
#include <ncurses.h>

class BoothAlg
{
    /*
    "Booth's algorithm is a method for multiplying binary numbers, particularly useful for signed integersusing two's complement. It examines pairs of bits from the multiplier and performs specific actions:adding or subtracting the multiplicand based on the bit pattern. After each operation, it performs an arithmetic right shift on the result and multiplier. This process is repeated for a number of cyclesequal to the number of bits in the multiplier, ultimately yielding the product."
    */

    //^^all these are just print strings

    std::string multiplierString;
    // the string version of the multiploer

    std::string multiplicandString;
    // the string version of the multiplicand



    /*
    Helper function that will wait how ever long ms
    */
    void waitThisLong(int ms);

    /*
    Helper function that returns true if this is a valid int to convert
    */
    bool validInt(std::string input);

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

    /*
    Shifts the bits to the right with sign extend
    Also return the boothBit
    */
    char shiftRightWithBoothBitReturn(std::string &bits);

public:
    /*
    The default constructor
    */
    BoothAlg();

    /*
    The function to call to do booth alg to 2 32-bit integers
    */
    void run();
};

#endif