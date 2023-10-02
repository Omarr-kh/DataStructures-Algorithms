#pragma once
#include<iostream>
using namespace std;

template<typename Comparable>
class BinarySearchTree
{
    public:
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree& rhs);
        BinarySearchTree(BinarySearchTree&& rhs);
        ~BinarySearchTree();

        const Comparable& findMin() const;
        const Comparable& findMax() const;
        bool contains(const Comparable& x) const;
        bool isEmpty() const;
        void printTree(ostream & out = cout) const;

        void makeEmpty();
        void insert(const Comparable& x);
        void insert(const Comparable&& x);
        void remove(const Comparable& x);

        BinarySearchTree& operator=(const BinarySearchTree& rhs);
        BinarySearchTree& operator=(BinarySearchTree&& rhs);
    private:
        struct BinaryNode
        {
            Comparable element;
            BinaryNode* right;
            BinaryNode* left;

            BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt)
                : element{ theElement }, left{ lt }, right{ rt } {}
            BinaryNode(Comparable&& theElement, BinaryNode* lt, BinaryNode* rt)
                : element{ move(theElement) }, left{ lt }, right{ rt } {}
        };

        BinaryNode* root;

        void insert(const Comparable& x, BinaryNode*& t);
        void insert(Comparable&& x, BinaryNode*& t);
        void remove(const Comparable& x, BinaryNode*& t);
        BinaryNode* findMin(BinaryNode* t) const;
        BinaryNode* findMax(BinaryNode* t) const;
        void printTree(BinaryNode* t, ostream& out) const;
        BinaryNode* clone(BinaryNode* t) const;
};
