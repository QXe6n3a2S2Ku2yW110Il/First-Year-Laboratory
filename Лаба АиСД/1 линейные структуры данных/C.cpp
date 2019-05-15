#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
 
using namespace std;
 
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
    int get_capacity() {
        return (int)capacity;
    }
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
        if (capacity >= 4 * size)
            decrease_capacity();
        --size;
        return a[size];
    }
    ~ota_vector() {
        free(a);
        capacity = size = 0;
    }
};
 
template <typename T>
class ota_queue {
private:
    ota_vector<T> left_stack;
    ota_vector<T> right_stack;
 
public:
    void push_back(T x) {
        left_stack.push_back(x);
    }
 
    T pop_front() {
        if (right_stack.empty()) {
            while (!left_stack.empty())
                right_stack.push_back(left_stack.pop_back());
        }
        return right_stack.pop_back();
    }
};
 
int main() {
    int n;
    scanf("%d", &n);
 
    ota_queue<int> curr_queue;
    while (n--) {
        char c;
        scanf(" %c", &c);
 
        if (c == '+') {
            int x;
            scanf("%d", &x);
            curr_queue.push_back(x);
        }
        else
            printf("%d\n", curr_queue.pop_front());
    }
   
    return 0;
}
