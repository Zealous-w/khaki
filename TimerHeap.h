#include <iostream>

namespace khaki {
template<class T>
class MinHeap {
public:
    enum {
        MINHEAP_DEFAULT_SIZE = 256,
    };

    struct Node {
        Node(){}
        ~Node(){if(node) delete node;}
        T*  node;
        uint32_t idx;
    };

    MinHeap() {
        capacity_ = MINHEAP_DEFAULT_SIZE;
        init();
    }
    ~MinHeap() {
        for (int idx = 0; idx < size_; idx++) {
            if (heap_[idx]) 
                delete heap_[idx];
        }
        delete[] heap_;
    }

    void init() {
        heap_ = new T*[capacity_];
        if (!heap_) {
            printf("alloc heap faild %d\n", capacity_);
            return;
        }
        for (int idx = 0; idx < capacity_; idx++) {
            heap_[idx] = NULL;
        }
    }

    int reserve() {
        if (size_ >= capacity_) {
            T** tmp = new T* [2*capacity_];
            if (!tmp) {
                return -1; 
            }  

            capacity_ *= 2;  
            for( int i = 0; i < capacity_; ++i ) {  
                tmp[i] = NULL;  
            }  

            for ( int i = 0; i < size_; ++i ) {  
                tmp[i] = heap_[i];  
            }  
            delete [] heap_;  
            heap_ = tmp;  
        }
        return 0;
    }

    T* front() {
        if (empty()) 
            return NULL;
        return heap_[0];
    }

    int push(T* node) {
        if (!node) {
            return -1;
        }

        if (reserve())
            return -1;
        uint32_t holeIndex = size_++;
        shiftUpUnconditional(node, holeIndex);
    }

    void pop() {
        if (size_) {
            T* t = heap_[0];
            if (t) {
                heap_[0] = NULL;
                heap_[0] = heap_[--size_];
                delete t;
                shiftDownUnconditional(0u);
            }
        }
        return;
    }

    bool empty() {
        return size_ == 0;
    }

    uint32_t size() {
        return size_;
    }

    void show() {
        for (int idx = 0; idx < size_; idx++) {
            std::cout << "NODE : " << heap_[idx] << std::endl;
        }
    }
private:
    void shiftUpUnconditional(T* node, uint32_t holeIndex) {
        int parent = 0;
        while (holeIndex != 0) {
            parent = (holeIndex - 1) / 2;
            if (*heap_[parent] < *node)
                break;
            heap_[holeIndex] = heap_[parent];
            holeIndex = parent;
        }
        heap_[holeIndex] = node;
    }

    void shiftDownUnconditional(uint32_t holeIndex) {
        T* tmp = heap_[holeIndex];
        uint32_t minChild = 2 * holeIndex + 1;
        while(size_ > 0 && minChild <= size_ - 1 ) {
            if ((minChild < (size_ - 1)) && (*heap_[minChild + 1] < *heap_[minChild])) {
                minChild++;
            }

            if (*tmp < *heap_[minChild])
                break;
            heap_[holeIndex] = heap_[minChild];
            holeIndex = minChild;
            minChild = 2 * holeIndex + 1;
        }
        heap_[holeIndex] = tmp;
    }

protected:
    T** heap_;
    uint32_t capacity_;
    uint32_t size_;
};
}