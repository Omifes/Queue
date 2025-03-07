#ifndef QUEUEVECTOR_H
#define QUEUEVECTOR_H

#include "Queue.h"
#include <exception>

using namespace std;

class QueueOverflow : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Queue Overflow";
};


class QueueUnderflow : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Queue Underflow";
    }
};

class WrongQueueSize : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Wrong Queue Size";
    }
};

template <class T>
class QueueVector : public Queue<T>
{
private:
    int head = 0;
    int tail = 0;
    int size;
    T* queue;
};


#endif