/**
 * Author: Lukas Derner Grüdtner
 **/

#include "mine_generator.h"

#define RATIO_FREE 0.65

/*  Generates a n x n matrix, with n/2 positions with gold, n/4 freeway and n/4 barriers,
    being the first one freeway.
*/
std::fstream MineGenerator::generate(std::string filename, int size)
{
    std::vector<std::string> positions = shuffle(size);
    std::fstream file;
    int lines = size;
    int columns = size;
    
    file.open(filename, std::fstream::out);
    file << size << std::endl;
    unsigned int counter = 0;

    while (lines--)
    {
        while (columns--)
        {
            file << positions[counter++] << " ";
        }
        file << std::endl;
        columns = size;
    }
    file.close();

    return file;
}

int myrandom(int i)
{
    return std::rand()%i;
}

std::vector<std::string> MineGenerator::shuffle(int size)
{
    std::vector<std::string> v;
    unsigned int N_GOLD = size/2;
    unsigned int N_FREE = size*size*RATIO_FREE;
    unsigned int N_FENCE = size*size-N_FREE-N_GOLD;

    srand(time(NULL));

    unsigned int value;
    for (int i = 0; i < size*size; i++)
    {
        bool choosen = false;
        do
        {
            value = rand() % size*size;

            if (value >= size*size*0.4 && N_FREE)
            {
                v.push_back("0");
                --N_FREE;
                choosen = true;
            }
            else if (value >= size/2 && value < size*size*0.4 && N_FENCE)
            {
                v.push_back("1");
                --N_FENCE;
                choosen = true;
            }
            else if (value < size/2 == 0 && N_GOLD)
            {
                v.push_back("*");
                --N_GOLD;
                choosen = true;
            }
        } while (!choosen);
    }

    std::random_shuffle(v.begin(), v.end(), myrandom);
    while (v.front() != "0")
        std::random_shuffle(v.begin(), v.end(), myrandom);

    return v;
}

