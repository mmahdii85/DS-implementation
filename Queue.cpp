#include <iostream>
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
class Queue {
    private:
    typedef struct Node {
        int value;
        Node *next = NULL;
    }Node;
        Node *root;
        Node *last;
    // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
    public:
        Queue() {
            root = new Node;
            root->value = 0;
            last = root;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void push(int value) {
            Node *new_node = new Node();
            new_node->value = value;
            last->next = new_node;
            last = new_node;
            root->value++;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        int empty() {
            if (root->value != 0) {
                return 0;
            }
            return 1;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        int front() {
            if (!empty()) {
                return (root->next)->value;
            } else {
                printf("Queue is empty\n");
                return -1;
            }
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        int pop() {
            if (!empty()) {
                Node *temp = root->next;
                int value = temp->value;
                root->next = temp->next;
                temp->next = NULL;
                delete temp;
                root->value--;
                if (root->next == NULL) {
                    last = root;
                }
                return value;
            } else {
                printf("Queue is empty\n");
                return -1;
            }
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        int size() {
            return root->value;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void clear() {
            Node *temp = root->next;
            while (temp != NULL) {
                Node *nextNode = temp->next;
                temp->next = NULL;
                delete temp;
                temp = nextNode;
            }
            root->next = NULL;
            last = root;
            root->value = 0;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        ~Queue() {
            clear();
            delete root;
        }
};
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
int main() {
    Queue q;
    //
    printf("Queue is empty? %d\n", q.empty());
    //
    q.push(10);
    q.push(20);
    q.push(30);
    //
    printf("Queue size: %d\n", q.size());
    //
    printf("Front: %d\n", q.front());
    printf("Pop: %d\n", q.pop());
    //
    printf("Front after pop: %d\n", q.front());
    printf("Queue size: %d\n", q.size());
    //
    q.push(40);
    q.push(50);
    //
    printf("Queue size after push: %d\n", q.size());
    //
    printf("Pop: %d\n", q.pop());
    printf("Pop: %d\n", q.pop());
    //
    printf("Queue size: %d\n", q.size());
    //
    printf("Clear queue...\n");
    q.clear();
    //
    printf("Queue empty? %d\n", q.empty());
    printf("Queue size: %d\n", q.size());
    //
    printf("Trying pop after empty: %d\n", q.pop());
    //
    return 0;
}
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖