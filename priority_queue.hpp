#ifndef _PRIORITY_QUEUE_HPP_
#define  _PRIORITY_QUEUE_HPP_
/*
  Implementation of a maximum priority queue using a heap
*/

#include <ostream>

template <typename T>
class Priority_queue {
private:
  T* heap;
  size_t qty;
  size_t capacity;

  /* parent: get the index of the parent of the element at the given index
     of the heap */
  size_t parent(size_t index) {
    return index/2;
  }
  
  /* max_heapify: rearrange elements of the heap to 'float down' element at
     position i to the correct position. */
  void max_heapify(size_t i) {
    size_t left = i*2;
    size_t right = i*2+1;
    size_t largest = i;
    
    if (left <= qty && heap[left] > heap[largest])
      largest = left;
    if (right <= qty && heap[right] > heap[largest])
      largest = right;
    
    if (largest != i) {
      std::swap(heap[i], heap[largest]);
      max_heapify(largest);
    }
  }

  /*
    resize: change the capacity of the heap to the given new_capacity.
   */
  void resize(size_t new_capacity) {
    T* new_heap = new T[new_capacity];
    for (size_t i = 1; i <= qty; ++i)
      new_heap[i] = heap[i];

    delete[] heap;
    heap = new_heap;
    capacity = new_capacity;
  }
  
public:
  Priority_queue(size_t initial_size = 10) {
    qty = 0;
    capacity = initial_size;
    heap = new T[capacity+1]; // position zero isn't used
  }

  ~Priority_queue() {
    delete[] heap;
  }

  /* empty: check if the priority queue is empty. */
  bool empty() {
    return qty == 0;
  }

  /* size: get the number of items in the priority queue. */
  size_t size() {
    return qty;
  }

  /* front: get the maximum element in the priority queue without removing
     it from the priority queue. */
  T front() {
    return heap[1];
  }

  /* 
     push: add a new item to the priority queue.
  */
  void push(T item) {
    heap[++qty] = item;

    // reposition new item to the correct position
    for (size_t i = qty; i > 1 && heap[i] > heap[parent(i)]; i = parent(i))
      std::swap(heap[i], heap[parent(i)]);

    // if the heap is full double the capacity
    if (qty == capacity)
      resize(capacity*2);
  }

  /* pop: get the maximum element from the priority queue and remove it
     from the priority queue. */
  T pop() {
    T max = heap[1];

    // rearrange the remaining elements to maintain the heap property
    heap[1] = heap[qty--];
    max_heapify(1);
    
    return max;
  }  
};

#endif /*  _PRIORITY_QUEUE_HPP_ */
