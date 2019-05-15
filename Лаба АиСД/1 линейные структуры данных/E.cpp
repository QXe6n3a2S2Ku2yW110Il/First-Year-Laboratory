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
 
int bracket_type(char c) {
    if (c == '(')
        return 1;
    if (c == '[')
        return 2;
    if (c == ')')
        return -1;
    if (c == ']')
        return -2;
    return 0;
}
  
bool correct_bracket_sequence(std::string &s) {
    ota_vector<int> stack;
    for (char curr_symbol : s) {
        int curr_type = bracket_type(curr_symbol);
        if (curr_type > 0)
            stack.push_back(curr_type);
  
        if (curr_type < 0) {
            if (stack.empty())
                return false;
  
            int back_type = stack.pop_back();
            if (!(curr_type == -back_type))
                return false;
        }
  
        if (curr_type == 0)
            return false;
    }
  
    return stack.empty();
}
  
int main() {
    string curr_brackets;
    while (getline(cin, curr_brackets)) {
        if (correct_bracket_sequence(curr_brackets))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
   
    return 0;
}
