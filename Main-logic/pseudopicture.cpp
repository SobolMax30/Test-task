#include "pseudopicture.h"

#include <cstdlib>

PseudoPicture::PseudoPicture()
{
    for (int index = 0; index < SIZE; index++)
    {
        pictureData[index] = 0;
    }
}

void PseudoPicture::fillRandom()
{
    for (int index = 0; index < SIZE; index++)
    {
        pictureData[index] = static_cast<unsigned char>(rand() % 256);
    }
}
