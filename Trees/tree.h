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
        bool contains(const Comparable& x, BinaryNode* t) const;
        void makeEmpty(BinaryNode*& t);
        void printTree(BinaryNode* t, ostream& out) const;
        BinaryNode* clone(BinaryNode* t) const;
};

/**
 * contains - checks if a node x is in the tree 
 * x: Node to be searched for
 * Returns: True if x if found
*/
template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable& x) const
{
    return contains(x, root);
}

/**
 * insert - inserts a node x to the tree, Duplicates are ignored
 * x: node to be inserted
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x)
{
    insert(x, root);
}

/**
 * remove - removes a node from the tree
 * x: node to be removed
 * Nothing is done if x is not found in the tree
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x)
{
    remove(x, root);
}

/**
* contains - private method to search for node x in binary search tree t
* x: node to be searched for
* t: root of the tree to be searched
* Return: true if found, false otherwise
*/
template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable& x, BinaryNode* t) const
{
    if (t == nullptr)
        return false;
    else if (t->element == x)
    {
        return true;
    }
    else if (t->element > x)
    {
        return contains(x, t->left);
    }
    else
    {
        return contains(x, t->right);
    }
}

/**
* findMin - privated method that searches for the minimum node in a tree
* t: rooth of the tree to be searched
* Return: Minimum Node in the Tree, nullptr is Tree is empty
*/
template<typename Comparable>
BinarySearchTree<Comparable>::BinaryNode* BinarySearchTree<Comparable>::findMin(BinaryNode* t) const
{
    if (t != nullptr)
    {
        while (t->left != nullptr)
            t = t->left;
    }
    return t;
}

/**
* findMax - private method that searches for the maximum node in a tree recursively
* t: root of the tree to be searched
* Return: Maximum Node in the Tree, nullptr is Tree is empty
*/
template<typename Comparable>
BinarySearchTree<Comparable>::BinaryNode* BinarySearchTree<Comparable>::findMax(BinaryNode* t) const
{
    if (t == nullptr)
        return nullptr;
    else if (t->right == nullptr)
        return t;
    else
        return findMax(t->right);
}

/**
 * insert - private method which inserts a node x into the tree t
 * x: node to be inserted
 * t: root of the Tree
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x, BinaryNode*& t)
{
    if (t == nullptr)
        t = new BinaryNode(x, nullptr, nullptr);
    else if (t->element > x)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ; // incase t->element == x (duplicate) do nothing
}

/**
 * insert - private method which inserts a node x into the tree t
 * x: node to be inserted by moving
 * t: root of the Tree
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable&& x, BinaryNode*& t)
{
    if (t == nullptr)
        t = new BinaryNode(move(x), nullptr, nullptr);
    else if (t->element > x)
        insert(move(x), t->left);
    else if (t->element < x)
        insert(move(x), t->right);
    else
        ; // incase t->element == x (duplicate) do nothing
}

/**
 * 
 */
template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x, BinaryNode*& t)
{
    if (t == nullptr)
        return;
    else if (t->element > x)
    {
        remove(x, t->left);
    }
    else if (t->element < x)
    {
        remove(x, t->right);
    }
    else if (t->right != nullptr && t->left != nullptr) // has two children
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else
    {
        BinaryNode* currNode = t;
        t = (t->right != nullptr) ? t->right : t->left;
        delete currNode;
    }
}