#ifndef CONTAINER_H
#define CONTAINER_H

#include "icontainer.h"

#include <cstddef>

template <class ContainerType>
class Container : public IContainer
{
public:
    void push(const PseudoPicture &item) override
    {
        storage.push_back(item);
    }

    PseudoPicture pop() override
    {
        PseudoPicture lastItem = storage.back();
        storage.pop_back();
        return lastItem;
    }

    std::size_t size() const override
    {
        return storage.size();
    }

    bool empty() const override
    {
        return storage.empty();
    }

private:
    ContainerType storage;
};

#endif // CONTAINER_H
