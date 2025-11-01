#pragma once
#include <vector>
#include <functional>

template <typename Value, typename Compare = std::less<Value>>
struct Heap {
   public:
    void push(const Value& value);
    Value* pop();

    void debug(int start = 0);
    const std::vector<Value>& values();

   private:
    void bubble(int index);
    void sink(int index);
    std::vector<Value> _values;
};
