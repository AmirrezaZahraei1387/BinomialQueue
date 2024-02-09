//
// Created by mzahr on 2/8/2024.
//
#ifndef BIOQU_BIOQ_INL
#define BIOQU_BIOQ_INL
#include <algorithm>
#include "BioQ.hpp"

// the method combine two equal sized trees with each other
template<typename Comparable>
typename BioQ<Comparable>::BioNode *BioQ<Comparable>::combine2Nodes(BioQ::BioNode *t1, BioQ::BioNode *t2) {
    if(t1->item < t2->item){
        return combine2Nodes(t2, t1);
    }
    t2->nextSib = t1->leftChild;
    t1->leftChild = t2;
    return t1;
}


template<typename Comparable>
void BioQ<Comparable>::merge(BioQ &qu) {

    // avoid aliasing problems
    if(this == &qu)
        return;

    current_size += qu.current_size;

    if(current_size > bioT.size())
        resizeTree(std::max(bioT.size(), qu.bioT.size()) + 1);

    BioNode* temp = nullptr;

    for(int i = 0, j = 1; j<=current_size; ++i, j*=2){
        BioNode* t1Node = bioT[i];
        BioNode* t2Node = nullptr;

        if(qu.bioT.size() > i){
            t2Node = qu.bioT[i];
        }

        // determining the case that is occurring
        int whichCase = t1Node == nullptr? 0 : 1;
        whichCase += t2Node == nullptr? 0 : 2;
        whichCase += temp == nullptr? 0: 4;

        switch (whichCase) {
            case 0:
            case 1:
                break;

            // only the other tree exist. we just add it too ours
            case 2:
                bioT[i] = t2Node;
                qu.bioT[i] = nullptr;
                break;

            // only the carry exist.
            case 4:
                bioT[i] = temp;
                temp = nullptr;
                break;

            // both trees exist so we combine them
            case 3:
                temp = combine2Nodes(t1Node, t2Node);
                bioT[i] = nullptr;
                qu.bioT[i] = nullptr;
                break;

            case 5:
                temp = combine2Nodes(temp, t1Node);
                bioT[i] = nullptr;
                break;

            case 6:
                temp = combine2Nodes(temp, t2Node);
                bioT[i] = nullptr;
                break;

            // all of them are present
            case 7:
                bioT[i] = temp;
                temp = combine2Nodes(t1Node, t2Node);
                qu.bioT[i] = nullptr;
                break;
        }
    }

    // making sure qu is all set to nullptr
    for(auto& t: qu.bioT)
        t = nullptr;
    qu.current_size = 0;
}

template<typename Comparable>
void BioQ<Comparable>::resizeTree(size_t new_size) {

    if(new_size < bioT.size())
        return;

    int oldSize{bioT.size()};
    bioT.resize(new_size);
    for(int i{oldSize+1}; i<new_size; ++i)
        bioT[i] = nullptr;
}


template<typename Comparable>
std::size_t BioQ<Comparable>::findMinInd() const {

    size_t minIndex;
    int i;

    // finding a suitable position for the minItem
    for(i = 0; bioT[i] == nullptr; ++i);

    for(minIndex = i; i<current_size; ++i){
        if(bioT[i] != nullptr){
            if(bioT[i]->item < bioT[minIndex]->item){
                minIndex = i;
            }
        }
    }

    return minIndex;
}

template<typename Comparable>
bool BioQ<Comparable>::isEmpty() const {
    return current_size == 0;
}

template<typename Comparable>
const Comparable &BioQ<Comparable>::findMin() const {
    size_t minInd{findMin()};
    return bioT[minInd];
}

template<typename Comparable>
void BioQ<Comparable>::insert(const Comparable &item) {
    BioNode node{.item=item};

}

#endif //BIOQU_BIOQ_INL
