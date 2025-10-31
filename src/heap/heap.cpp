#include "heap.h"

#include <iostream>
#include <cmath>

void Heap::push(int value) {
    values.push_back(value);
    bubble(values.size() - 1);
}

int Heap::pop() {
    int min = values[0];
    values[0] = values.back();
    values.pop_back();

    sink(0);

    return min;
}

void Heap::debug(int start = 0) {
    int n = values.size() - start;
    if (n <= 0) {
        return;
    };

    int h = log2(n) + 1;
    int index = start;

    for (int level = 0; level < h; level++) {
        int nodesAtLevel = pow(2, level);
        int spacing = pow(2, h - level) - 1;

        for (int s = 0; s < spacing; s++) {
            std::cout << " ";
        }

        for (int i = 0; i < nodesAtLevel && index < values.size(); i++, index++) {
            std::cout << values[index];

            for (int s = 0; s < spacing * 2 + 1; ++s) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Heap::bubble(int index) {
    int value = values[index];
    int nodeInProgressIndex = index;

    while (nodeInProgressIndex) {
        int parentIndex = (nodeInProgressIndex - 1) / 2;
        int parent = values[parentIndex];

        if (parent >= value) {
            std::swap(values[parentIndex], values[nodeInProgressIndex]);
            nodeInProgressIndex = parentIndex;
        } else {
            return;
        }
    }
}

void Heap::sink(int index) {
    int nodeInProgressIndex = index;
    int size = values.size();

    while (nodeInProgressIndex < values.size()) {
        int leftIndex = nodeInProgressIndex * 2 + 1;
        int rightIndex = nodeInProgressIndex * 2 + 2;

        int targetNode = nodeInProgressIndex;

        if (leftIndex < size && values[leftIndex] < values[targetNode]) {
            targetNode = leftIndex;
        }

        if (rightIndex < size && values[rightIndex] < values[targetNode]) {
            targetNode = rightIndex;
        }

        if (targetNode != nodeInProgressIndex) {
            std::swap(values[targetNode], values[nodeInProgressIndex]);
            nodeInProgressIndex = targetNode;
        } else {
            break;
        }
    }
}
