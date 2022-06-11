#ifndef RANK_TREE_H
#define RANK_TREE_H

#include <iostream>
#include <memory>
#include <assert.h>

class AvlRankTree
{         
    private:
    struct Node{
        friend class AvlRankTree;
        struct Node*  father;
        struct Node*  left;
        struct Node*  right;
        int height;

        int id;
        int salary;
        int grade;

        int numEmploiesAtSubTree;
        int sumOfGradeInSubTree;
        int sumBumpGradeinSubTree;
    };

    int size_of_tree; //amount of nodes in sub tree
    Node* root;
    Node* max;
    Node* min; 

    /*operation for Node*/
    int calculateBalanceFactor(Node* node) const;
    Node* getMinNode(Node* node) const;
    Node* getMaxNode(Node* node) const;
    int getNodeSalary(Node* node) const;
    int getNodeSize(const Node* node) const;
    int getNodeHeight(const Node* node) const;
    //int getNodeNumPeopleAtLevel(const Node* node) const;
    int getNodenumEmploiesAtSubTree(const Node* node) const;
    int getNodesumOfGradeInSubTree(const Node* node) const;
    int getNodesumBumpGradeinSubTree(const Node* node) const;
    Node* createNode(int id, int salary, int grade);
    Node* duplicateNode(Node* node);
    Node* insertNode(Node* new_node,Node* target,Node* parent);
    Node* findNode(Node* node,int id) const;
    Node* deleteNode(Node* target, Node* to_remove);
    Node* selectNodeOperation(Node* node, int index) const;
    void printTreeAux(Node* root) const;
    void sumUntilReachHighLevel(Node* start,int highLevel, int* with_score,int* in_range,int score) const;
    void sumUntilReachLowLevel(Node* start,int lowLevel, int* with_score,int* in_range,int score) const;

    /*roll function*/
    Node* rollLeftLeft(Node* node);
    Node* rollRightRight(Node* node);
    Node* rollRightLeft(Node* node);
    Node* rollLeftRight(Node* node);

    // helper func for Constructor && Destructor of AVL
    void emptyTreeAux(Node* node);
    Node* convertSortedArrayToTreeAux(Node* sorted_array[],int start,int end,Node* father);

    //avl rank tree's constructor, destructor, interface functions
    public:
    bool isTreeEmpty() const;
    void empty();
    AvlRankTree();
    AvlRankTree(const AvlRankTree& other);
    ~AvlRankTree();
    AvlRankTree(const AvlRankTree& firstTree, const AvlRankTree& secondTree); //merge
    AvlRankTree& operator=(const AvlRankTree &other);
    // void convertSortedArrayToTree(Node* dataArr[],int arrSize);
    void insert(int salary, int id);
    Node* find(int id);
    void remove(int salary, int id);
    Node* select(int salary) const;
    int getHeight() const;
    int getMaxlevel() const;
    void printTree() const; //for debug
    void fillFromTree(const AvlRankTree& src); //O(n) //fill a tree from data of other tree
    Node* getCommonFather(Node* first,Node* second,Node* origin);
    double getPrecentOfPlayersWithScoreBetweenBounds(int score,int lowLevel,int highLevel,int* error,
                                             int numPeopleAtZero, int numPeopleAtZeroWithScore);
    int getTotalNumPeopleAtTree() const;
    int getSumOfHighestMPlayerLevel(int sum,int m,Node* node);
    Node* getRoot() const;

    //iterator-in order to sort the elements into an array
    class Iterator
    {
        private:
        friend class AvlRankTree;
        Node* node;
        Node* last;
        public:
        Iterator(Node* node, Node* last);
        ~Iterator()=default;
        Iterator& operator=(const Iterator& other_iter);
        Iterator(const Iterator& other_iter);
        Node* operator*();
        bool operator==(const Iterator& iter) const;
        bool operator!=(const Iterator& iter) const;
        Iterator& operator++();
    };
    Iterator begin() const;
    Iterator end() const;

};


#endif