#include <iostream>
using namespace std;
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
class AVL {
    private:
        struct Node {
            Node *left;
            Node *right;
            int value;
            int bf;
            Node() {
                left = right = nullptr;
                value = bf = -1;
            }
        };
        Node *root;
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        Node *new_node(int value) {
            Node *new_node = new Node();
            new_node->value = value;
            new_node->bf = 0;
            return new_node;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        Node *Left_rotation(Node *x) {
            Node *y = x->right;
            Node *Beta = y->left;
            y->left = x;
            x->right = Beta;
            if (y->bf == 1) {
                x->bf = 0;
                y->bf = 0;
            }
            else {
                x->bf = 1;
                y->bf = -1;
            }
            return y;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        Node *Right_rotation(Node *y) {
            Node *x = y->left;
            Node *Beta = x->right;
            x->right = y;
            y->left = Beta;
            //
            if (x->bf == -1) {
                y->bf = 0;
                x->bf = 0;
            }
            else {
                y->bf = -1;
                x->bf = 1;
            }
            return x;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        std::pair<Node *, bool> delete_val(Node* node, int value) {
            if (node == nullptr) {
                return {nullptr, false};
            }
            bool shrunk;
            if (value < node->value) {
                auto res = delete_val(node->left, value);
                node->left = res.first;
                shrunk = res.second;
                if (!shrunk) {
                    return {node, false};
                }
                node->bf++;
            }
            else if (value > node->value) {
                auto res = delete_val(node->right, value);
                node->right = res.first;
                shrunk = res.second;
                if (!shrunk) {
                    return {node, false};
                }
                node->bf--;
            }
            else {
                if (node->right == nullptr && node->left == nullptr) {
                    delete node;
                    return {nullptr, true};
                }
                else if (node->right == nullptr) {
                    Node *temp = node->left;
                    delete node;
                    return {temp, true};
                }
                else if (node->left == nullptr) {
                    Node *temp = node->right;
                    delete node;
                    return {temp, true};
                }
                else {
                    // successor
                    Node *temp = node->right;
                    while (temp->left != nullptr) {
                        temp = temp->left;
                    }
                    node->value = temp->value;
                    auto res = delete_val(node->right, temp->value);
                    node->right = res.first;
                    shrunk = res.second;
                    if (!shrunk) {
                        return {node, false};
                    }
                    node->bf--;
                }
            }
            //
            if (node->bf == 1 || node->bf == -1) {
                return {node, false};
            }
            else if (node->bf == 0) {
                return {node, true};
            }
            else if (node->bf == 2) {
                if (node->right->bf == 0) {
                    return {Left_rotation(node), false};
                }
                else if (node->right->bf == -1)
                    node->right = Right_rotation(node->right);
                return {Left_rotation(node), true};
            }
            else if (node->bf == -2) {
                if (node->left->bf == 0) {
                    return {Right_rotation(node), false};
                }
                else if (node->left->bf == 1)
                    node->left = Left_rotation(node->left);
                return {Right_rotation(node), true};
            }
            return {node, false};
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        std::pair<Node *, bool> insert_val(Node* node, int value) {
            if (node == nullptr)
                return {new_node(value), true};
            //
            bool grew;
            //
            if (value < node->value) {
                auto res = insert_val(node->left, value);
                node->left = res.first;
                grew = res.second;
                if (!grew) {
                    return {node, false};
                }
                node->bf--;
            }
            else if (value > node->value) {
                auto res = insert_val(node->right, value);
                node->right = res.first;
                grew = res.second;
                if (!grew) {
                    return {node, false};
                }
                node->bf++;
            }
            else
                return {node, false};
            //
            if (node->bf == 0) {
                return {node, false};
            }
            if (node->bf == 2) {
                if (node->right->bf == -1)
                    node->right = Right_rotation(node->right);
                return {Left_rotation(node), false};
            }
            if (node->bf == -2) {
                if (node->left->bf == 1)
                    node->left = Left_rotation(node->left);
                return {Right_rotation(node), false};
            }
            return {node, true};
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void inorder(Node* node) {
            if (!node) return;
            inorder(node->left);
            cout << node->value << "(" << node->bf << ") ";
            inorder(node->right);
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        bool search_val(Node *node, int value) {
            if (node == nullptr) {
                return false;
            }
            if (node->value == value) {
                return true;
            }
            else if (value < node->value) {
                return search_val(node->left, value);
            }
            else {
                return search_val(node->right, value);
            }
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
    public:
        AVL() {
            root = nullptr;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void insert(int value) {
            auto res = insert_val(root, value);
            root = res.first;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void del(int value) {
            auto res = delete_val(root, value);
            root = res.first;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        bool search(int value) {
            return search_val(root, value);
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void print_inorder() {
            inorder(root);
            cout << '\n';
        }
};
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
int main() {
    AVL tree;
    tree.insert(10);
    tree.insert(4);
    tree.insert(16);
    tree.insert(2);
    tree.insert(8);
    tree.insert(14);
    tree.insert(24);
    tree.insert(6);
    tree.insert(12);
    tree.insert(20);
    tree.insert(26);
    tree.insert(18);
    tree.insert(22);
    cout << "Inorder traversal (value(bf)):" << '\n';
    tree.print_inorder();
    cout << "search for 4:" << '\n';
    if (tree.search(4)) {
        cout << "Number was found" << '\n';
    }
    else {
        cout << "Number was not found" << '\n';
    }
    tree.del(4);
    cout << "value 4 deleted!" << '\n' << "Inorder traversal (value(bf)):" << endl;
    tree.print_inorder();
    cout << "search for 4:" << '\n';
    if (tree.search(4)) {
        cout << "Number was found" << '\n';
    }
    else {
        cout << "Number was not found" << '\n';
    }
}
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖