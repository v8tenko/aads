#pragma once

#include <functional>
#include <optional>
#include <vector>

template <typename Value, typename Compare = std::less<Value>>
struct Heap {
   public:
    Heap();
    void push(const Value& value);
    std::optional<Value> pop();

    void debug(int start = 0);
    const std::vector<Value>& values();

   private:
    Compare compare;
    void bubble(int index);
    void sink(int index);
    std::vector<Value> _values;
};
