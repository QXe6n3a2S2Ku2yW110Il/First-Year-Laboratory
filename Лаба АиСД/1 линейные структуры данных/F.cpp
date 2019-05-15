#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
 
template <typename T>
class ota_vector {
private:
    T *a = (T*)malloc(sizeof(T));
    size_t capacity = 1, size = 0;
  
    void increase_capacity() {
        T *tmp = (T*)malloc(2 * sizeof(T) * capacity);
        for (size_t i = 0; i < capacity; ++i)
            tmp[i] = a[i];
        capacity *= 2;
        std::swap(a, tmp);
        free(tmp);
    }
    void decrease_capacity() {
        capacity /= 2;
        T *tmp = (T*)malloc(sizeof(T) * capacity);
        for (size_t i = 0; i < capacity; ++i)
            tmp[i] = a[i];
        std::swap(a, tmp);
        free(tmp);
    }
  
public:
    bool empty() {
        return size <= 0;
    }
    void push_back(T x) {
        if (capacity <= size)
            increase_capacity();
        a[size] = x;
        ++size;
    }
    T pop_back() {
        if (capacity >= 4 * size && size > 0)
            decrease_capacity();
        --size;
        return a[size];
    }
    ~ota_vector() {
        free(a);
        capacity = size = 0;
    }
};
 
int main() {
    ota_vector<int> stack;
    char c;
    while (scanf(" %c", &c) == 1) {
        if ('0' <= c && c <= '9')
            stack.push_back(c - '0');
        else {
            int first_int = stack.pop_back(), second_int = stack.pop_back();
            int curr_result = 0;
            if (c == '+')
                curr_result = second_int + first_int;
            if (c == '-')
                curr_result = second_int - first_int;
            if (c == '*')
                curr_result = second_int * first_int;
            stack.push_back(curr_result);
        }
    }
 
    printf("%d", stack.pop_back());
  
    return 0;
}
