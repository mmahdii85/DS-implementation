#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
class MaxHeap {
    private:
        vector<int> heap;
    // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
    public:
        void UpHeapify(int index) {
            while (index > 0) {
                int parent_index = (index - 1) / 2;
                if (heap[parent_index] < heap[index]) {
                    int temp = heap[parent_index];
                    heap[parent_index] = heap[index];
                    heap[index] = temp;
                    index = parent_index;
                }
                else {
                    break;
                }
            }
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void DownHeapify(int index, int size) {
            while (true) {
                int left = index * 2 + 1;
                int right = index * 2 + 2;
                int largest = index;
                //
                if (left < size && heap[left] > heap[largest]) {
                    largest = left;
                }
                //
                if (right < size && heap[right] > heap[largest]) {
                    largest = right;
                }
                //
                if (largest != index) {
                    int temp = heap[largest];
                    heap[largest] = heap[index];
                    heap[index] = temp;
                    index = largest;
                }
                else {
                    break;
                }
            }
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void insert(int value) {
            heap.push_back(value);
            UpHeapify(heap.size() - 1);
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void del(int index) {
            if (index < 0 || index >= heap.size()) {
                return;
            }
            heap[index] = heap.back();
            heap.pop_back();
            //
            if (index > 0 && heap[index] > heap[(index - 1) / 2])
                UpHeapify(index);
            else
                DownHeapify(index, heap.size());
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void buildHeap(vector<int>& arr) {
            heap = arr;
            int size = (int)heap.size();
            for (int i = (size-2)/2; i >= 0; i--) {
                DownHeapify(i, size);
            }
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void heapsort(vector<int>& arr) {
            buildHeap(arr);
            int size = heap.size();
            while (size != 1) {
                int temp = heap.back();
                heap[size - 1] = heap[0];
                heap[0] = temp;
                size--;
                DownHeapify(0, size);
            }
            arr = heap;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        int extractMax() {
            if (heap.empty()) {
                return -1;
            }
            int maxVal = heap[0];
            heap[0] = heap.back();
            heap.pop_back();
            DownHeapify(0, heap.size());
            return maxVal;
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        int getMax() {
            return heap.empty() ? -1 : heap[0];
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        bool isEmpty() {
            return heap.empty();
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        int size() {
            return heap.size();
        }
        // ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
        void printHeap() {
            int size = heap.size();
            for (int i = 0; i < size; ++i) {
                printf("%d ", heap[i]);
            }
        }
};
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖
// main is written by gpt
int main() {
    MaxHeap h;
    //
    printf("=== Test insert ===\n");
    h.insert(10);
    h.insert(40);
    h.insert(20);
    h.insert(30);
    h.insert(50);
    printf("Heap after inserts: \n");
    h.printHeap();
    //
    printf("\ngetMax(): %d\n", h.getMax());
    //
    printf("\n=== Test del(index) ===\n");
    //
    printf("Delete index 2\n");
    h.del(2);
    printf("Heap now: ");
    h.printHeap();
    //
    printf("\n=== Test extractMax ===\n");
    int ex = h.extractMax();
    printf("extractMax returned: %d\n", ex);
    printf("Heap now: ");
    h.printHeap();
    //
    printf("\n=== Test buildHeap from external array ===\n");
    vector<int> arr = {3, 1, 6, 5, 2, 4};
    printf("Array before buildHeap: ");
    for (int i = 0; i < arr.size(); ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    //
    h.buildHeap(arr);
    printf("Heap after buildHeap(arr): ");
    h.printHeap();
    //
    printf("\n=== Test heapsort on array ===\n");
    vector<int> arr2 = {12, 3, 17, 8, 34, 1, 9};
    printf("arr2 before heapsort: ");
    for (int i : arr2) {
        printf("%d ", i);
    }
    printf("\n");
    //
    h.heapsort(arr2);
    printf("arr2 after heapsort: ");
    for (int i : arr) {
        printf("%d ", i);
    }
    printf("\n");
    //
    printf("\n=== Final status of internal heap (after heapsort call) ===\n");
    printf("Internal heap: ");
    h.printHeap();
    //
    printf("\nsize(): %d\n", h.size());
    printf("isEmpty(): %d\n", h.isEmpty() ? 1 : 0);
    //
    return 0;
}
// ➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖