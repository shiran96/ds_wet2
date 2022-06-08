#if !defined(TREE_NODE_H)
#define TREE_NODE_H

#include <iostream>
#include <memory>
#include <assert.h>

template <typename T>
class tree_node
{
private:
    T *data_t;
    int height;
    int size_of_sub_tree;
    struct Node *father;
    struct Node *left;
    struct Node *right;

public:
    explicit tree_node(T *data) : data_t(data), father(nullptr), left(nullptr),
                                  right(nullptr), height(0) {}
    ~tree_node();
    tree_node *getFather() { return father; }
    tree_node *getLeft() { return left; }
    tree_node *getRight() { return right; }
    data_t *getData() { return data; }
    bool isLeaf();
    bool onlyHaveLeftSon();
    bool onlyHaveRightSon();
    bool haveTwoSons();
    bool isALeftSon();
    bool isARightSon();
    void updateHeight();
    void updateRank();
    void resetRank();
    int getBalanceFactor();
    static void recursiveNodeDeletion(RankTreeNode<data_t, rank_t>* node);
};

template <typename data_t>
tree_node<data_t>::~tree_node()
{
    father = nullptr;
    left = nullptr;
    right = nullptr;
    data = nullptr;
}

template <typename data_t>
bool tree_node<data_t>::isLeaf()
{
    if (!right && !left)
    {
        return true;
    }
    return false;
}

template <typename data_t>
bool tree_node<data_t>::onlyHaveLeftSon()
{
    if (!right && left)
    {
        return true;
    }
    return false;
}

template <typename data_t>
bool tree_node<data_t>::onlyHaveRightSon()
{
    if (right && !left)
    {
        return true;
    }
    return false;
}

template <typename data_t>
bool tree_node<data_t>::haveTwoSons()
{
    if (right && left)
    {
        return true;
    }
    return false;
}

template <typename data_t>
bool tree_node<data_t>::isALeftSon()
{
    if (father == nullptr)
    {
        return false;
    }
    if (!father->left)
    {
        return false;
    }
    if (father->left->getData() == this->getData())
    {
        return true;
    }
    return false;
}

template <typename data_t>
bool tree_node<data_t>::isARightSon()
{
    if (father == nullptr)
    {
        return false;
    }
    if (!father->right)
    {
        return false;
    }
    if (father->right->getData() == data)
    {
        return true;
    }
    return false;
}

template <typename data_t>
void tree_node<data_t>::updateHeight()
{
    int left_height = (left == nullptr) ? -1 : left->height;
    int right_height = (right == nullptr) ? -1 : right->height;

    height = 1 + max(left_height, right_height);
}

template <typename data_t>
void tree_node<data_t>::updateRank()
{
    resetRank();
    if (isLeaf())
    {
        return;
    }
    if (onlyHaveLeftSon())
    {
        rank += left->rank;
        return;
    }
    if (onlyHaveRightSon())
    {
        rank += right->rank;
        return;
    }
    if (haveTwoSons())
    {
        rank += left->rank;
        rank += right->rank;
        return;
    }
}

template <typename data_t>
void tree_node<data_t>::resetRank()
{
    rank.initializeRank(*data);
}

template <typename data_t>
void tree_node<data_t>::getBF()
{
    int left_height = (left == nullptr) ? -1 : left->height;
    int right_height = (right == nullptr) ? -1 : right->height;
    return (left_height - right_height);
}

template <typename data_t>
void tree_node<data_t>::recursiveNodeDeletion(RankTreeNode<data_t> *node)
{
    if (node == nullptr)
    {
        return;
    }
    recursiveNodeDeletion(node->left);
    recursiveNodeDeletion(node->right);

    if (node->isALeftSon())
    {
        node->father->left = nullptr;
    }
    else
    {
        if (node->isARightSon())
        {
            node->father->right = nullptr;
        }
    }
    delete node;
}

#endif // TREE_NODE_H
