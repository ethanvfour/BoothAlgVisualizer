#include "BoothAlg.h"

std::string BoothAlg::convertIntToBinaryString(int number)
{
    bool negative = false;
    if (number < 0)
    {
        negative = true;
        number = number * -1;
    }
    std::queue<int> binary; // a queue is needed with this method of turning into binary

    while (number != 0)
    {
        binary.push(number % 2);
        number = number / 2;
    }

    std::string outcome(32, '0');
    for (int i = 31; !binary.empty(); i--)
    {
        outcome[i] = binary.front() + 0x30;
        binary.pop();
    }
    if (negative)
    {
        onesComplement(outcome);
        twosComplement(outcome);
    }

    return outcome;
}

void BoothAlg::onesComplement(std::string &binaryNum)
{
    for (int i = 0; i < binaryNum.length(); i++)
    {
        if (binaryNum[i] == '0')
            binaryNum[i] = '1';
        else
            binaryNum[i] = '0';
    }
    // will do the opposite of what it is yk
}

void BoothAlg::twosComplement(std::string &binaryNum)
{
    std::string adder(32, '0');
    adder[adder.length() - 1] = '1';         // just adds one
    binaryNum = addBinary(binaryNum, adder); // calls the addBinary func
}

std::string BoothAlg::addBinary(std::string first, std::string second)
{
    std::string outcome(32, '0'); // makes outcome by default 0
    bool carry = false;           // this will be the carry flag
    for (int i = 31; i != -1; i--)
    {
        int ones = 0; // counts how many ones
        if (carry)
        {
            carry = false;
            ones++;
        }
        if (first[i] == '1')
            ones++;
        if (second[i] == '1')
            ones++;

        // from here, the amount of ones will determine the outcome
        if (ones == 1)
            outcome[i] = '1';
        else if (ones == 2)
            carry = true;
        else if (ones == 3)
        {
            outcome[i] = '1';
            carry = true;
        }
    }
    return outcome;
}

BoothAlg::BoothAlg()
{
    multiplierString = std::string(32, '0');
    multiplicandString = std::string(32, '0');
    // makes both string default to 0, will be changed later on
}


void BoothAlg::run()
{
    
}