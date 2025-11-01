#include "heap.h"

#include <cmath>
#include <iostream>
#include <optional>


template <typename Value, typename Compare>
Heap<Value, Compare>::Heap() : compare(Compare()) {}

template <typename Value, typename Compare>
void Heap<Value, Compare>::push(Value value) {
    _values.push_back(std::move(value));
    bubble(_values.size() - 1);
}

template <typename Value, typename Compare>
std::optional<Value> Heap<Value, Compare>::pop() {
    if (_values.empty()) {
        return std::nullopt;
    }

    Value min = _values[0];
    _values[0] = std::move(_values.back());
    _values.pop_back();

    sink(0);

    return min;
}

template <typename Value, typename Compare>
void Heap<Value, Compare>::bubble(int index) {
    Value value = _values[index];
    size_t nodeInProgressIndex = index;

    while (nodeInProgressIndex) {
        int parentIndex = (nodeInProgressIndex - 1) / 2;
        int parent = _values[parentIndex];

        if (compare(value, parent)) {
            std::swap(_values[parentIndex], _values[nodeInProgressIndex]);
            nodeInProgressIndex = parentIndex;
        } else {
            return;
        }
    }
}

template <typename Value, typename Compare>
void Heap<Value, Compare>::sink(int index) {
    size_t nodeInProgressIndex = index;
    size_t size = _values.size();

    while (nodeInProgressIndex < _values.size()) {
        size_t leftIndex = nodeInProgressIndex * 2 + 1;
        size_t rightIndex = nodeInProgressIndex * 2 + 2;

        size_t targetNode = nodeInProgressIndex;

        if (leftIndex < size && compare(_values[leftIndex], _values[targetNode])) {
            targetNode = leftIndex;
        }

        if (rightIndex < size && compare(_values[rightIndex], _values[targetNode])) {
            targetNode = rightIndex;
        }

        if (targetNode != nodeInProgressIndex) {
            std::swap(_values[targetNode], _values[nodeInProgressIndex]);
            nodeInProgressIndex = targetNode;
        } else {
            break;
        }
    }
}

template <typename Value, typename Compare>
const std::vector<Value>& Heap<Value, Compare>::values() {
    return _values;
}

template <typename Value, typename Compare>
void Heap<Value, Compare>::debug(int start) {
    int n = _values.size() - start;
    if (n <= 0) {
        return;
    };

    int h = log2(n) + 1;
    int index = start;

    for (int level = 0; level < h; level++) {
        int nodesAtLevel = 1 << level;
        int spacing = (1 << (h - level)) - 1;

        for (int s = 0; s < spacing; s++) {
            std::cout << " ";
        }

        for (int i = 0; i < nodesAtLevel && index < _values.size(); i++, index++) {
            std::cout << _values[index];

            for (int s = 0; s < spacing * 2 + 1; ++s) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}
