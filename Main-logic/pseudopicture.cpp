#include "pseudopicture.h"

PseudoPicture::PseudoPicture()
{
    for (int i = 0; i < SIZE; ++i)
    {
        data[i] = 0;
    }
}

PseudoPicture& PseudoPicture::operator=(int value)
{
    for (int i = 0; i < SIZE; ++i)
    {
        data[i] = static_cast<unsigned char>(value);
    }
    return *this;
}

PseudoPicture::operator int() const
{
    return static_cast<int>(data[0]);
}
