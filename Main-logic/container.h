#ifndef CONTAINER_H
#define CONTAINER_H

#include "icontainer.h"

#include <cstddef>
#include <vector>

template <class ContainerType, class T>
class Container : public IContainer<T>
{
public:
    void push(const T &item) override
    {
        container.push_back(item);
    }

    T pop() override
    {
        T lastItem = container.back();
        container.pop_back();
        return lastItem;
    }

    std::size_t size() const override
    {
        return container.size();
    }

    bool empty() const override
    {
        return container.empty();
    }

    std::vector<T> getContents() const override
    {
        std::vector<T> result;
        for (const T &item : container)
        {
            result.push_back(item);
        }
        return result;
    }

private:
    ContainerType container;
};

#endif // CONTAINER_H
