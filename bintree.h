#pragma once
#include "nodedata.h"
class BinTree
{
public:
    friend ostream & operator<<(ostream &, const BinTree &);
    BinTree& operator=(const BinTree& treeFrom);
    BinTree(const BinTree& treeFrom);
    BinTree();
    ~BinTree()
    {
        clear();
    }
    bool operator==(const BinTree& other) const;
    bool operator!=(const BinTree& other) const { return !equal(other); }
    // dispaly a tree as a tree
    void displaySideways() const;
    // search node and return to p
    bool retrieve(const NodeData& node, NodeData*& p) const;
    // get the slibling of node
    bool getSibling(const NodeData& node, NodeData & nd);
    // get the parentNode of node
    bool getParent(const NodeData& node, NodeData & nd);
    void bstreeToArray(NodeData*(&ndArray)[100]);
    void arrayToBSTree(NodeData*(&ndArray)[100] );
    void makeEmpty(void);
    // insert node p into the tree
    bool insert(NodeData* p);
private:
    void sidewaysHelper(NodeData* current, int level) const;
    void copy(const BinTree& other) ;
    bool equal(const BinTree& other) const;
    void copy2(NodeData*& dest, const NodeData* source);
    bool equal2(const NodeData* lhs, const NodeData* rhs) const;
    bool isLeafNodeEqual(const NodeData* lhs, const NodeData* rhs) const;
    bool isNodeLeaf(const NodeData* node) const;
    void inorderPrint(std::ostream& os, const NodeData* node) const;
    void inorderHelper(NodeData* current, NodeData*(&ndArray)[100], int& count);
    void clear(void);
    void arrayToBSTree(NodeData** p, int low, int high);
private:
    NodeData* root = nullptr;
};

