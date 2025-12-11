#include <iostream>
#include <cstring>
using namespace std;
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
class Trie {
    private:
        struct Node {
            Node *child[26];
            int child_number;
            Node *parent;
            int valid;
            char c;
            Node() {
                parent = NULL;
                valid = 0;
                c = 0;
                child_number = 0;
                for (int i = 0; i < 26; i++)
                    child[i] = NULL;
            }
        };
        Node *root;
    // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
    public:
        Trie() {
            root = new Node();
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        Node *insert_char(Node *root, char ch) {
            if (root->child[ch - 'a'] == NULL) {
                root->child_number++;
                Node *new_node = new Node();
                new_node->c = ch;
                new_node->parent = root;
                root->child[ch - 'a'] = new_node;
            }
            return root->child[ch - 'a'];
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void insert_word(char *word) {
            size_t word_len = strlen(word);
            Node *first = root;
            for (int i = 0; i < word_len; ++i) {
                first = insert_char(first, *(word + i));
            }
            first->valid = 1;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void search(char *word) {
            size_t word_len = strlen(word);
            Node *temp = root;
            for (int i = 0; i < word_len; i++) {
                if (temp->child[word[i] - 'a'] != NULL) {
                    temp = temp->child[word[i] - 'a'];
                } else {
                    printf("Word was not found.\n");
                    return;
                }
            }
            if (temp->valid == 1)
                printf("Word was found.\n");
            else
                printf("Word was not found.\n");
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void delete_word(char *word) {
            size_t word_len = strlen(word);
            Node *first = root;
            for (int i = 0; i < word_len; i++) {
                if (first->child[word[i] - 'a'] != NULL) {
                    first = first->child[word[i] - 'a'];
                }
                else {
                    printf("Word was not found.\n");
                }
            }
            if (first->valid == 0)
                printf("Word was not found.\n");
            else {
                first->valid = 0;
                while (first->child_number == 0) {
                    Node *temp = first;
                    first = first->parent;
                    first->child[temp->c - 'a'] = NULL;
                    first->child_number--;
                    delete temp;
                }
            }
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        /*In the preorder traversal function, the root node is passed as a parameter because traversal must always start
         from a specific point in the tree. Since the root represents the beginning of the Trie structure,
         giving it as input ensures that the function knows where to start processing the nodes. This makes the function
         more flexible, because if needed, we can later call it with any subtree root instead of always starting from
         the main root.*/
        void preorder(Node *root, char *word, int word_len) {
            if (!root) return;
            if (root->valid == 1 && root->c != 0) {
                *(word + word_len) = root->c;
                *(word + word_len + 1) = '\0';
                printf("%s\n", word);
            }
            if (root->c != 0) {
                *(word + word_len) = root->c;
                word_len++;
            }
            for (int i = 0; i < 26; i++) {
                if (root->child[i] != NULL) {
                    preorder(root->child[i], word, word_len);
                }
            }
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        Node* getRoot() {
            return root;
        }
};
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
int main() {
    Trie trie;
    //
    trie.insert_word("salam");
    trie.insert_word("hello");
    //
    char word[100];
    //
    trie.preorder(trie.getRoot(), word, 0);
    //
    trie.search("salam");
    trie.search("salama");
    trie.search("sal");
    trie.search("hello");
    trie.search("hell");
    //
    trie.delete_word("hello");
    //
    trie.preorder(trie.getRoot(), word, 0);
    //
    trie.search("hello");
    trie.search("hell");
    //
    return 0;
}
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖