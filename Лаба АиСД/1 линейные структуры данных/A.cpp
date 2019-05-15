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
    int n;
    scanf("%d", &n);
      
    ota_vector<int> stack;
    while (n--) {
        char c;
        scanf(" %c", &c);
  
        if (c == '+') {
            int x;
            scanf("%d", &x);
            stack.push_back(x);
        }
        else
            printf("%d\n", stack.pop_back());
    }
  
    return 0;
}
