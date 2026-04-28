#ifndef PSEUDOPICTURE_H
#define PSEUDOPICTURE_H

class PseudoPicture
{
public:
    PseudoPicture();
    PseudoPicture(const PseudoPicture &other) = default;
    PseudoPicture& operator=(const PseudoPicture &other) = default;

    PseudoPicture& operator=(int value);
    operator int() const;

private:
    static const int SIZE = 10;
    unsigned char data[SIZE];
};

#endif // PSEUDOPICTURE_H
