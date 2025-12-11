#include <iostream>
#include <cstdlib>
using namespace std;
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
#define SIZE 100
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
class Stack {
    private:
        int *stack;
        int index;
        int capacity;
        int howManyTimesRealoc;
    // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
    public:
        Stack() {
            stack = (int *) malloc(sizeof(int) * SIZE);
            index = 0;
            capacity = SIZE;
            howManyTimesRealoc = 0;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        int *push(int value) {
            if (index == capacity) {
                capacity = (SIZE)*(howManyTimesRealoc+2);
                stack = (int *) realloc(stack, sizeof(int)*capacity);
                howManyTimesRealoc++;
            }
            *(stack + index) = value;
            index++;
            return stack;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        int pop() {
            if (index == 0) {
                printf("stack is empty\n");
                return -1;
            }
            int value = *(stack + index - 1);
            index--;
            return value;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        int top() {
            if (index == 0) {
                printf("stack is empty\n");
                return -1;
            }
            return *(stack + index - 1);
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        int empty() {
            if (index != 0) {
                return 0;
            }
            return 1;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void clear() {
            index = 0;
        }
};
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
int main() {
    //
    Stack s;
    //
    s.pop();
    s.top();
    //
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    //
    int top1 = s.top();
    int x = s.pop();
    int top2 = s.top();
    int emptyBefore = s.empty();
    //
    s.clear();
    //
    int emptyAfter = s.empty();
    //
    printf("top1: %d\nx: %d\ntop2: %d\nemptyBefore: %d\nemptyAfter: %d\n",
           top1, x, top2, emptyBefore, emptyAfter);
    //
    return 0;
}
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖