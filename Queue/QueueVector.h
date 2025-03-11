#ifndef QUEUEVECTOR_H
#define QUEUEVECTOR_H

#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;

class QueueOverflow : public exception
{
public:
    const char* what() const noexcept override 
    {
        return "Queue Overflow";
    }
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
    int quantity = 0;
    int size;
    T* queue;

    void resize(){
        int newCapacity = capacity * 2;
        T* newQueue = new T[newCapacity];
        for (int i = 0; i < size; i++)
        {
            newQueue[i] = queue[(head + i) % capacity];
        }
        delete[] queue;
        queue = newQueue;
        head = 0;
        tail = size;
        capacity = newCapacity;
    }
        
public:
    QueueVector(int size) : quantity(0), head(0), tail(0), size(size) {
        if (size <= 0) {
            throw WrongQueueSize();
        }
        queue = new T[size];
    }

    ~QueueVector() {
        delete[] queue;
    }

    void enQueue(const T& e) override {
        if (quantity == size) {
            resize();
        }
        queue[tail] = e;
        tail = (tail + 1) % size;
        quantity++;
    }
    
    T deQueue() override {
        if (quantity == 0) {
            throw QueueUnderflow();
        }
        T e = queue[head];
        head = (head + 1) % size;
        quantity--;
        return e;
    }

    bool isEmpty() override {
        return quantity == 0;
    }

    bool isFull() override {
        return quantity == size;
    }   

};

bool checkBalanceBrackets(const char* text, const int maxDeep) {
    QueueVector<char> queue1(maxDeep);
    QueueVector<char> queue2(maxDeep);
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '(' || text[i] == '[' || text[i] == '{') {
            queue1.enQueue(text[i]);
        }
    }
    QueueVector<char> reversed(maxDeep);
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == ')' || text[i] == ']' || text[i] == '}') {
            if (queue1.isEmpty()) {
                return false;
            }
            reversed.enQueue(text[i]);          
        }   
    }   

    while (!reversed.isEmpty()) {
        queue2.enQueue(reversed.deQueue());
    }

    while (!queue1.isEmpty() && !queue2.isEmpty()) {
        if (queue1.deQueue() != queue2.deQueue()) {
            return false;
        }
    }
    return queue1.isEmpty() && queue2.isEmpty();
}
#endif