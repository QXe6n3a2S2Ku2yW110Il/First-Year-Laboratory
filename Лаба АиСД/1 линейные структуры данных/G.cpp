#include <stdio.h>
#include <algorithm>
#include <cstring>
 
using namespace std;
 
struct mins {
    int val, min;
};
 
int capacity_l = 1, capacity_r = 1, size_l = 0, size_r = 0;
mins* stack_l = new mins[capacity_l];
mins* stack_r = new mins[capacity_r];
 
void increase_capacity_l() {
    mins *tmp = new mins[capacity_l * 2 + 1];
    memcpy(tmp, stack_l, capacity_l * sizeof(mins));
    capacity_l = capacity_l * 2 + 1;
    delete[] stack_l;
    stack_l = tmp;
}
 
void increase_capacity_r() {
    mins *tmp = new mins[capacity_r * 2 + 1];
    memcpy(tmp, stack_r, capacity_r * sizeof(mins));
    capacity_r = capacity_r * 2 + 1;
    delete[] stack_r;
    stack_r = tmp;
}
 
void decrease_capacity_l() {
    capacity_l /= 2;
    mins *tmp = new mins[capacity_l];
    memcpy(tmp, stack_l, capacity_l * sizeof(mins));
    delete[] stack_l;
    stack_l = tmp;
}
 
void decrease_capacity_r() {
    capacity_r /= 2;
    mins *tmp = new mins[capacity_r];
    memcpy(tmp, stack_r, capacity_r * sizeof(mins));
    delete[] stack_r;
    stack_r = tmp;
}
 
void push_l(int x) {
    if (capacity_l <= size_l)
        increase_capacity_l();
 
    if (size_l == 0)
        stack_l[size_l] = {x, x};
    else
        stack_l[size_l] = {x, min(stack_l[size_l - 1].min, x)};
    ++size_l;
}
 
void push_r(int x) {
    if (capacity_r <= size_r)
        increase_capacity_r();
 
    if (size_r == 0)
        stack_r[size_r] = {x, x};
    else
        stack_r[size_r] = {x, min(stack_r[size_r - 1].min, x)};
    ++size_r;
}
 
mins pop_l() {
    if (capacity_l >= 2 * size_l)
        decrease_capacity_l();
 
    return stack_l[--size_l];
}
 
mins pop_r() {
    if (capacity_r >= 2 * size_r)
        decrease_capacity_r();
 
    return stack_r[--size_r];
}
 
void update_queue(int x, int &queue_size, int m,
                  long long &ans, int &prev, int &prev2) {
    push_l(x);
    ++queue_size;
 
    if (queue_size == m) {
        if (size_r == 0) {
            while (size_l > 0)
                push_r(pop_l().val);
        }
  
        if (size_l == 0)
            ans += pop_r().min;
        else
            ans += min(pop_r().min, stack_l[size_l - 1].min);
 
        --queue_size;
    }
 
    prev2 = prev;
    prev = x;
}
 
int main() {
    int n, m, k, a, b, c;
    scanf("%d%d%d%d%d%d", &n, &m, &k, &a, &b, &c);
 
    int queue_size = 0, prev = 0, prev2 = 0;
    long long ans = 0;
    for (int i = 0; i < k; i++) {
        int x;
        scanf("%d", &x);
        update_queue(x, queue_size, m, ans, prev, prev2);
    }
    for (int i = k; i < n; i++) {
        int x = a * prev2 + b * prev + c;
        update_queue(x, queue_size, m, ans, prev, prev2);
    }
 
    printf("%I64d", ans);
 
    return 0;
}
