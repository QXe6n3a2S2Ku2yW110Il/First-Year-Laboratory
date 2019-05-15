#include <iostream>
#include <stdlib.h>
#include <algorithm>
 
struct int_list {
    int val = 0;
    int_list *next = nullptr;
  
    int_list() = default;
    int_list(int_list *x): val(0), next(x) {}
    int_list(int x): val(x), next(nullptr) {}
    int_list(int x, int_list *y): val(x), next(y) {}
};
  
int_list *tail = new int_list();
int_list *head = new int_list(tail);
 
void insert_element(int x) {
    int_list *curr_element = tail;
    tail = new int_list();
    curr_element->val = x;
    curr_element->next = tail;
}
int extract_element() {
    int res = head->next->val;
    auto tmp = head->next;
    head->next = head->next->next;
    delete tmp;
    return res;
}
 
void clean() {
    auto curr_element = head;
    while (curr_element != nullptr) {
        auto tmp = curr_element;
        curr_element = curr_element->next;
        delete tmp;
    }
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    while (n--) {
        char c;
        scanf(" %c", &c);
 
        if (c == '+') {
            int x;
            scanf("%d", &x);
            insert_element(x);
        }
        else
            printf("%d\n", extract_element());
    }
 
    clean();
   
    return 0;
}
