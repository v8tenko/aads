#pragma once
#include <vector>

struct Heap {
   public:
    std::vector<int> values;
    void push(int value);
    int pop();
    void debug(int start);

   private:
    void bubble(int index);
    void sink(int index);
};
