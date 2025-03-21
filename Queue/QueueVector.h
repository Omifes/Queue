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
        int newSize = size * 2;
        T* newQueue = new T[newSize];
        for (int i = 0; i < size; i++)
        {
            newQueue[i] = queue[(head + i) % size];
        }
        delete[] queue;
        queue = newQueue;
        head = 0;
        tail = quantity;
        size = newSize;
    }
        
public:
    int getQuantity() const {
        return quantity;
    }

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
        if (isFull()) {
            resize();
        }
        queue[tail] = e;
        tail = (tail + 1) % size;
        quantity++;
    }
    
    T deQueue() override {
        if (isEmpty()) {
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
    QueueVector<char> reversed(maxDeep);
    
    bool foundClosing = false;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '(' || text[i] == '[' || text[i] == '{') {
            if(foundClosing) {
                return false;
            }
            queue1.enQueue(text[i]);
            if (queue1.getQuantity() > maxDeep) {
                return false;
            }
        }
    
        if (text[i] == ')' || text[i] == ']' || text[i] == '}') {
            foundClosing = true;
            if (queue1.isEmpty()) {
                return false;
            }
            reversed.enQueue(text[i]);
            if (reversed.getQuantity() > maxDeep) {
                return false;
            }
        }   
    }   
    char* temp = new char[maxDeep];
    int rQuantity = reversed.getQuantity();
    for (int i = 0; i < rQuantity; i++) {
        temp[i] = reversed.deQueue();
    }
    for (int i = rQuantity - 1; i >= 0; i--) {
        queue2.enQueue(temp[i]);
    }
    delete[] temp;

    while (!queue1.isEmpty() && !queue2.isEmpty()) {
        char c1 = queue1.deQueue();
        char c2 = queue2.deQueue();
        if ((c1 == '(' && c2 != ')') || 
            (c1 == '[' && c2 != ']') || 
            (c1 == '{' && c2 != '}')) {
            return false;
        }
    }
    return queue1.isEmpty() && queue2.isEmpty();
}
#endif