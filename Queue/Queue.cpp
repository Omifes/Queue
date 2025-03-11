#include "QueueVector.h"
#include <iostream>
#include <string>

using namespace std;

void testBasicQueueOperations();
void testQueueUnderflow();
void testWrongQueueSize();
void testBracketBalancing();

int main() {
    testBasicQueueOperations();
    testQueueUnderflow();
    testWrongQueueSize();
    testBracketBalancing();
    return 0;
}

void testBasicQueueOperations() {
    QueueVector<int> queue(5);
    queue.enQueue(10);
    queue.enQueue(20);
    queue.enQueue(30);
    if (queue.isEmpty()) {
        cout << "Error: Queue should not be empty after enQueue" << endl;
    }
    if (queue.deQueue() != 10 || queue.deQueue() != 20 || queue.deQueue() != 30) {
        cout << "Error: Incorrect order of element extraction" << endl;
    }
    if (!queue.isEmpty()) {
        cout << "Error: Queue should be empty after extracting all elements" << endl;
    }
}

void testQueueUnderflow() {
    try {
        QueueVector<int> queue(3);
        queue.enQueue(1);
        queue.deQueue();
        cout << "Attempting to deQueue from an empty queue" << endl;
        queue.deQueue();
    } catch (const QueueUnderflow& e) {
        cerr << e.what() << endl;
    }
}

void testWrongQueueSize() {
    cout << "Attempting to create queue with wrong size" << endl;
    try {
        QueueVector<string> wrongSize(-1);
    } catch (const WrongQueueSize& e) {
        cerr << e.what() << endl;
    }
}

void testBracketBalancing() {
    string testCases[] = {"", "[", "{[{}]}", "([)]", "((())))", "{[()]}", "{[({[()]})}"}; 
    for (int i = 0; i < 7; ++i) {
        bool result = checkBalanceBrackets(testCases[i].c_str(), 5);
        cout << "Tested: " << testCases[i] << " Result: " << (result ? "True" : "False") << endl;
    }
}
