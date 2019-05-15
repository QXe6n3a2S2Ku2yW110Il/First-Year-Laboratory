#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
 
struct int_list {
    int val = 0;
    int_list *next = nullptr;
 
    int_list() = default;
};
 
int_list *stack = nullptr;
 
void insert_element(int x) {
    int_list *curr_element = new int_list();
    curr_element->val = x;
    curr_element->next = stack;
    stack = curr_element;
}
 
int extract_element() {
    int_list *tmp = stack;
    stack = stack->next;
    int res = tmp->val;
    delete tmp;
    return res;
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
 
    return 0;
}
