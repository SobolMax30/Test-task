#ifndef ICONTAINER_H
#define ICONTAINER_H

#include <cstddef>
#include <vector>

template <class T>
class IContainer
{
public:
    virtual ~IContainer() = default;
    virtual void push(const T &item) = 0;
    virtual T pop() = 0;
    virtual std::size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual std::vector<T> getContents() const = 0;
};

#endif // ICONTAINER_H
