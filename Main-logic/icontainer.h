#ifndef ICONTAINER_H
#define ICONTAINER_H

#include "pseudopicture.h"

#include <cstddef>

class IContainer
{
public:
    virtual ~IContainer() = default;
    virtual void push(const PseudoPicture &item) = 0;
    virtual PseudoPicture pop() = 0;
    virtual std::size_t size() const = 0;
    virtual bool empty() const = 0;
};

#endif // ICONTAINER_H
