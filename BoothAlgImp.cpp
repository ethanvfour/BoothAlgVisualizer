#include "BoothAlg.h"

void BoothAlg::waitThisLong(int ms)
{
    napms(2000);
    timeout(1);
    while (getch() != ERR)
    {
    }
    timeout(-1);
}

bool BoothAlg::validInt(std::string input)
{
    if (input.length() > 12)
        return false;
    for (int i = 0; i < input.length(); i++)
    {
        if (!((0x30 <= input[i] && input[i] <= 0x39) || input[i] == '-'))
        {
            return false;
        }
    }
    long temp = std::stol(input);
    if (temp > std::numeric_limits<int>::max() || temp < std::numeric_limits<int>::min())
        return false;

    return true;
}

std::string BoothAlg::convertIntToBinaryString(int number)
{
    bool negative = false; // assumes its not false
    if (number < 0)
    {
        negative = true; // if it is, we make the flag true
        number = number * -1;
    }
    std::queue<int> binary; // a queue is needed with this method of turning into binary

    while (number != 0)
    {
        binary.push(number % 2); // pushes the remainder onto queue
        number = number / 2;     // then actually divides the number by 2
    }

    std::string outcome(32, '0');
    /*
    Until the queue is empty, it will keep putting the things from queue into it
    */
    for (int i = 31; !binary.empty(); i--)
    {
        outcome[i] = binary.front() + 0x30;
        // reason for the 0x30, is to get the actual character of the decimal
        binary.pop();
    }

    // if flag is true, we have to call the ones complement and twos complement
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

char BoothAlg::shiftRightWithBoothBitReturn(std::string &bits)
{
    std::string changer(bits.length(), '0');
    if (bits[0] == '1')
        changer[0] = '1';

    for (int i = 1; i < changer.length(); i++)
        changer[i] = bits[i - 1];

    char boothBit = bits[bits.length() - 1];
    bits = changer;
    return boothBit;
}

void BoothAlg::run()
{
    // assuming initscr and everything else was called
    char buffer[500]; // 200 bytes cuz why not

    bool userDone = false;

    while (!userDone)
    {
        clear();
        /* move(0, 0);
        printw("%s", boundary.c_str()); */

        move(2, 2);
        printw("Welcome to the Booth Algorithm Visualizer!");
        move(3, 2);
        printw("1) About Booth's Algorithm");
        move(4, 2);
        printw("2) Start Booth's Algoithm");
        move(5, 2);
        printw("3) Quit Booth Algorithm");
        refresh();
        timeout(-1);
        int choice = getch();

        if ((char)choice == '1')
        {
            clear();
            /* move(0,0);
            printw("%s", boundary.c_str()); */
            move(2 + 1, 2);
            printw("Booth's algorithm is a method for multiplying binary numbers, particularly useful for ");
            move(3 + 1, 2);
            printw("signed integers using two's complement. It examines pairs of bits from the multiplier");
            move(4 + 1, 2);
            printw("and performs specific actions:adding or subtracting the multiplicand based on the bit pattern.");
            move(5 + 1, 2);
            printw("After each operation, it performs an arithmetic right shift on the result and multiplier.");
            move(6 + 1, 2);
            printw("This process is repeated for a number of cycles equal to the number of bits");
            move(7 + 1, 2);
            printw("in the multiplier, ultimately yielding the product.");
            refresh();
            napms(5000);
            timeout(1);
            while (getch() != ERR)
            {
            }

            move(15, 25);
            timeout(-1);
            printw("Press any button to continue");
            refresh();
            getch();
        }
        else if ((char)choice == '2')
        {
            clear();
            /* move(0,0);
            printw("%s", boundary.c_str()); */
            echo();
            bool goodMultiplier = false, goodMultiplicand = false;
            while (!goodMultiplier)
            {

                move(2, 2);
                printw("Give the multiplier, let it be in the range of a signed 32-bit");
                refresh();
                move(3, 2);
                getstr(buffer);
                std::string temp = buffer;
                if (validInt(temp))
                {
                    multiplierString = convertIntToBinaryString(std::stoi(temp));
                    goodMultiplier = true;
                }
                else
                {
                    noecho();
                    clear();
                    move(1, 2);
                    printw("Not a valid number");
                    refresh();
                    napms(2000);
                    timeout(1);
                    while (getch() != ERR)
                    {
                    }
                    timeout(-1);
                    echo();
                    continue;
                }
            }
            clear();
            while (!goodMultiplicand)
            {
                move(2, 2);
                printw("Now give the multiplicand, let it be in the range of a signed 32-bit");
                refresh();
                move(3, 2);
                getstr(buffer);
                std::string temp = buffer;
                if (validInt(temp))
                {
                    multiplicandString = convertIntToBinaryString(std::stoi(temp));
                    goodMultiplicand = true;
                }
                else
                {
                    noecho();
                    clear();
                    move(1, 2);
                    printw("Not a valid number");
                    refresh();
                    napms(2000);
                    timeout(1);
                    while (getch() != ERR)
                    {
                    }
                    timeout(-1);
                    echo();
                    continue;
                }
            }

            noecho();
            // first is intialization
            clear();
            move(2, 2);
            printw("First, we have to initalize");

            std::string product(32, '0');
            char boothBit = '0';
            product = product + multiplierString;
            move(3, 2);
            printw("Multiplier:   %s", multiplierString.c_str());
            move(4, 2);
            printw("Multiplicand: %s", multiplicandString.c_str());
            move(5, 2);
            printw("Product:      %s", product.c_str());
            move(6, 2);
            printw("Booth Bit:    %c", boothBit);
            refresh();
            waitThisLong(2000);
            move(8, 2);
            printw("Press any button to go to next step");
            refresh();
            getch();

            for (int i = 1; i <= 32; i++)
            {
                clear();
                move(3, 2);
                printw("Step %d", i);
                move(4, 2);
                printw("Multiplier:   %s", multiplierString.c_str());
                move(5, 2);
                printw("Multiplicand: %s", multiplicandString.c_str());
                move(6, 2);
                printw("Product:      %s", product.c_str());
                move(7, 2);
                printw("Booth Bit:    %c", boothBit);
                move(10, 2);

                std::string whichOfThe4Options = "", boothCombination = "";

                boothCombination.push_back(product[product.length() - 1]);
                boothCombination.push_back(boothBit);

                bool additionOperation = false, subtractionOperation = false, noOp = false;

                if (boothCombination == "00" || boothCombination == "11")
                {
                    whichOfThe4Options = "The least significant bit and booth bit was " + boothCombination + ". Therefore no operation";
                    noOp = true;
                }
                else if (boothCombination == "01")
                {
                    whichOfThe4Options = "The least significatn bit and booth bit was " + boothCombination + ". Therefore an addition operation needs to be done.";
                    additionOperation = true;
                }
                else if (boothCombination == "10")
                {
                    whichOfThe4Options = "The least significatn bit and booth bit was " + boothCombination + ". Therefore a subtraction operation needs to be done";
                    subtractionOperation = true;
                }
                else
                {
                    throw std::out_of_range("I dont even know how this would happen");
                }

                printw("%s", whichOfThe4Options.c_str());
                refresh();
                waitThisLong(2000);

                move(12,2);
                printw("Press any button to go to next step...");
                refresh();
                getch();
            }
        }
        else if ((char)choice == '3')
        {
            userDone = true;
        }
        // else do nothing until good input?
    }
}