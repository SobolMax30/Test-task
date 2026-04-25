#ifndef PSEUDOPICTURE_H
#define PSEUDOPICTURE_H

class PseudoPicture
{
public:
    PseudoPicture();

    void fillRandom();

private:
    static const int SIZE = 100;
    unsigned char pictureData[SIZE];
};

#endif // PSEUDOPICTURE_H
