
#ifndef BIOQ_BIO_QU
#define BIOQ_BIO_QU
#include <vector>
#include <cstddef>
#include <initializer_list>


template<typename Comparable>
class BioQ{
public:
    BioQ();
    BioQ(const BioQ& qu);
    BioQ(std::initializer_list<Comparable> ls);
    BioQ(BioQ&& qu);

    ~BioQ() noexcept;

    BioQ& operator=(const BioQ& qu);
    BioQ& operator=(BioQ&& qu);

    bool isEmpty() const;
    const Comparable& findMin() const;

    void insert(const Comparable& item);
    void insert(Comparable&& item);
    void deleteMin();
    void deleteMin(Comparable& minItemEW);

    void makeEmpty();
    void merge(BioQ& qu);
private:
    struct BioNode{
        Comparable item;
        BioNode*   nextSib{nullptr};
        BioNode*   leftChild{nullptr};
    };

    static constexpr int DEFAULT_TREE_COUNT{1};
    std::vector<BioNode*> bioT;
    std::size_t current_size;

    std::size_t findMinInd() const;
    BioNode* combine2Nodes(BioNode* t1, BioNode* t2);
    void makeEmpty(BioNode*& node);
    void resizeTree(size_t new_size);
};


#include "BioQ.inl"
#endif // BIOQ_BIO_QU