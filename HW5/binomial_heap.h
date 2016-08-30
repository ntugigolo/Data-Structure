#include <utility>
#include <list>
#include <iostream>
#include <math.h>

struct EmptyHeap: public std::exception {};

template<class T>
class BinomialHeap {
    private:
        /* inner class: binomial tree */
        struct BinomialTree {
            int _size;
            T element;
            std::list<BinomialTree*> children;

            BinomialTree(T _ele): _size(1), element(_ele) {
                children.clear();
            }

            /* return the size of BinomialTree
             * #note that nullptr->size() == 0
             * (nullptr is a null pointer (like NULL in C))
             */
            int size() {
                return (this!=nullptr)?this->_size:0;
            }
        };
        /* some definition for convinience
         */
        typedef BinomialTree BT;
        typedef BinomialHeap<T> BH;
        typedef std::pair<BT*, BT*> CarrySum;
        typedef std::pair<T, BH> MaxRemainder;

        /* Merge two binomial trees which have the same sizes
         *
         * INPUT:   a: operand a, b: operand b
         *
         * OUTPUT:  a pair of two variables.
         *          first: carry out
         *          second: sum
         *
         * (half adder)
         */
        CarrySum sub_merge(BT *a, BT *b) {
            if (a->size() == 0)
                return std::make_pair(nullptr, b);
            else if (b->size() == 0)
                return std::make_pair(nullptr, a);
            else {
                BT *bigger = (a->element > b->element)?a:b;
                BT *smaller = (a->element > b->element)?b:a;
                bigger->_size *= 2;
                (bigger->children).push_back(smaller);
                return std::make_pair(bigger, nullptr);
            }
        }

        /* Merge three binomial trees which have the same sizes
         *
         * INPUT:   a: operand a, b: operand b, c: carry in
         *          (each of them are either nullptr or a pointer of BinomialTree with size 2^n)
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: carry out (nullptr or a pointer of BinomialTree with size 2^(n+1))
         *          second: sum (nullptr or a pointer of BinomialTree with size 2^n)
         *
         * (just as a full adder: http://en.wikipedia.org/wiki/Adder_%28electronics%29#Full_adder )
         */
        CarrySum merge_tree(BT *a, BT *b, BT *c) {
            // write your code here.
            CarrySum _first = sub_merge(a, b);
            if (_first.first->size() > 0)
                return std::make_pair(_first.first, c);
            else {
                CarrySum _second = sub_merge(_first.second, c);
                return _second;
            }
        };

        /* Pop the maximum element of a binomial tree and make other elements a binomial heap.
         *
         * INPUT:   a: a pointer of BinomialTree
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: the maximum element
         *          second: a binomial heap consists of other elements
         */
        MaxRemainder pop_max(BT *a) {
            // write your code here.
            BH _second;
            int loop = (a->children).size();
            for (int i=0; i < loop; ++i) {
                _second.trees[i] = (a->children).front();
                (a->children).pop_front();
            }
            _second._size = (a->size()) - 1;
            return std::make_pair(a->element, _second);
        }

        int _size;
        BT* trees[32]; //binomial trees of the binomial heap, where trees[i] is a tree with size 2^i.

    public:
        BinomialHeap(): _size(0) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
        }
        BinomialHeap(T element): _size(1) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
            trees[0] = new BT(element);
        }

        /* merge all elements in the binomial heap b into *this, and clear the binomial heap b.
         *
         * INPUT:   b: a reference of BinomialHeap
         */
        void merge(BH &b) {
            // write your code here.
            BT *carry = nullptr;
            int maxsize = (_size > b.size())?_size:b.size();
            int iter = log2(maxsize) + 1;
            for (int i=0; i <= iter; ++i) {
                CarrySum tmp = merge_tree(trees[i], b.trees[i], carry);
                carry = tmp.first;
                trees[i] = tmp.second;
            }

            _size += b._size;

            // clean binomial heap b
            for (int i=0; i<32; ++i) b.trees[i] = nullptr;
            b._size = 0;
        }

        void insert(const T &element) {
            BH tmp = BH(element);
            merge(tmp);
        }

        T& max() const {
            if(_size==0) throw EmptyHeap();
            else {
                //find the tree contains maximum element
                int max_tree = -1;
                int iter = log2(_size);
                for(int i=0; i<=iter; ++i)
                    if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
                        max_tree = i;

                return trees[max_tree]->element;
            }
        }

        T pop() {
            if(_size==0) throw EmptyHeap();
            else {
                //find the tree contains maximum element
                int max_tree = -1;
                int iter = log2(_size);
                for(int i=0; i<=iter; ++i)
                    if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
                        max_tree = i;

                MaxRemainder m_r = pop_max(trees[max_tree]);
                T &max_element = m_r.first;
                BH &remainder = m_r.second;

                _size -= trees[max_tree]->size();
                delete trees[max_tree];
                trees[max_tree] = nullptr;
                merge(remainder);
                return max_element;
            }
        }

        int size() {
            return _size;
        }
};
