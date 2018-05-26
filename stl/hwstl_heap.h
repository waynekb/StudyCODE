#ifndef _HWSTL_HEAP_H
#define _HWSTL_HEAP_H

namespace hwstl{

template <class RandomAccessIterator>
inline void push_heap(RandonAccessIterator first, RandomAccessIterator last){
    hw_push_heap_aux(first, last, distance_type(first), value_type(first));
}

template <class RandomAccessIterator, class Distance, class T>
inline void hw_push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance*,  T*){
    hw_push_heap(first, Distance((last-first)-1), Distance(0), T(*(last-1)))
}

template <class RandomAccessIterator, class Distance, class T>
void hw_push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value){
    Distance parent = (holeIndex-1)/2;
    while(holeIndex > topIndex && *(first +parent ) < value){
        *(first + holeIndex) = *(first + parent);
        holeIndex = parent;
        parent =(holeIndex - 1 )/2;
    }
    *(first + holeIndex)=value; 
}



template<class RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last){
    hw_pop_heap_aux(first, last, value_type(first));
}

template<class RandomAccessIterator, class Distance, class T>
inline void hw_pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*){
    hw_pop_heap(first, )
}

template<class RandomAccessIterator, class Distance, class T>
inline hw_pop_heap(RandomAccessIterator first, RandomAccessIterator last, Distance )

}

#endif