#include "mine_generator.h"
#include <iostream>

#define RATIO_GOLD      2
#define RATIO_FREEWAY   2
#define RATIO_FENCE     2

/*  Generates a n x n matrix, with n/2 positions with gold, n/4 freeway and n/4 barriers,
    being the first one freeway.
*/
std::fstream MineGenerator::generate(std::string filename, int size)
{
    std::fstream file;
    int lines = size;
    int columns = size;
    int value;

    srand(time(NULL));
    
    file.open(filename, std::fstream::out);
    file << size << std::endl;
    while (lines--)
    {
        while (columns--)
        {
            if (lines == size-1 && columns == size-1) 
            {
                --columns;
                file << 0 << " ";
            }
                
            value = rand() % (RATIO_FENCE + RATIO_FREEWAY + RATIO_GOLD);
            if (value < RATIO_GOLD)
                file << "*" << " ";
            else if (value >= RATIO_GOLD && value <= (RATIO_GOLD + RATIO_FREEWAY))
                file << "0" << " ";
            else
                file << "1" << " ";
        }
        file << std::endl;
        columns = size;
    }
    file.close();

    return file;
}