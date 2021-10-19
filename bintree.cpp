#include "bintree.h"
#include <stack>
using namespace std;
//----------------------------Overloaded<<Operator----------------
// runs the recursive function inorderPrint
ostream& operator<<(ostream& output, const BinTree& nd) {
    nd.inorderPrint(output, nd.root);
    return output;
}
//-----------------------retrieve---------------------------------
// Gets the NodaData* of a particular item in the tree
bool BinTree::retrieve(const NodeData & node, NodeData *& p) const
{
    if (root)
    {
        NodeData* pfind = root;
        while (pfind)
        {
            if (pfind->data == node.data)
            {
                p = pfind;
                return true;
            }
            else if (node.data < pfind->data)
            {
                pfind = pfind->left;
            }
            else
                pfind = pfind->right;
        }
    }
    return false;
}
// ----------------Sibling function----------------------------
//returns all sibling elements of the selected element
bool BinTree::getSibling(const NodeData & node, NodeData & nd)
{
    NodeData* p = nullptr;
    bool found = retrieve(node, p);
    if (found)
    {
        NodeData* parent = p->parent;
        if (parent)
        {
            if (parent->left && parent->left != p)
            {
                nd = *(parent->left);
                return true;
            }
            if (parent->right && parent->right != p)
            {
                nd = *(parent->right);
                return true;
            }
        }
    }
    return false;
}
//---------------
bool BinTree::getParent(const NodeData & node, NodeData & parentNode)
{
    NodeData* p = nullptr;
    bool found = retrieve(node, p);
    if (found)
    {
        NodeData* parent = p->parent;
        if (parent)
        {
            parentNode = *parent;
            return true;
        }
    }
    return false;
}
//------bstreeToArray----------------------------------------------------------
// using an inorder traverse of the tree to fills an array of Nodedata*
void BinTree::bstreeToArray(NodeData *(&ndArray)[100])
{
    int n = 0;
    inorderHelper(root, ndArray, n);
    clear();
}
//-----------arrayToBSTree-----------------------------------------------------
//From a sorted array of NodeData* constructs a balanced BinTree, leaving the
//array empty.The root is (low+high)/2
void BinTree::arrayToBSTree(NodeData *(&ndArray)[100])
{
    int total = 0;
    for (int i = 0; i < 100; i++)
    {
        if (ndArray[i] == nullptr)
        {
            break;
        }
        total++;
    }
    int low = 0;
    int high = total - 1;
    int mid = (low + high) / 2;

    insert(ndArray[mid]);
    arrayToBSTree(ndArray, low, mid - 1);
    arrayToBSTree(ndArray, mid + 1, high);

    for (int i = 0; i < total; i++)
    {
        delete ndArray[i];
    }
}
//-----------------------------------------------------------------------------
// inserts each NodeData into the tree
void BinTree::arrayToBSTree(NodeData ** ndArray, int low, int high)
{
    if (low > high)
    {
        return;
    }
    // find the middle of array
    int mid = (low + high) / 2;
    insert(ndArray[mid]);
    //recursively split the array
    arrayToBSTree(ndArray, low, mid - 1);
    arrayToBSTree(ndArray, mid + 1, high);
}
void BinTree::makeEmpty(void)
{
    clear();
}
//-------------------insert----------------------------------------------------
bool BinTree::insert(NodeData * p)
{
    auto data = p->data;

    if (0 != root)
    {
        NodeData *fast, *slow, *ptemp;
        fast = slow = ptemp = root;

        while (fast != 0)
        {
            slow = fast;
            if (data < slow->data)
            {
                fast = slow->left;
            }
            else if (data > slow->data)
            {
                fast = slow->right;
            }
            else
            {
                fast = 0;
                return false;
            }
            //else equal do nothing
        }
        if (data < slow->data)
        {
            slow->left = new NodeData(data);
            slow->left->parent = slow;
        }
        else if (data > slow->data)
        {
            slow->right = new NodeData(data);
            slow->right->parent = slow;
        }
        //else equal do nothing
    }
    else
    {
        root = new NodeData(data);
    }
    return true;
}
bool BinTree::operator==(const BinTree & other) const
{
    return this->equal(other);
}
//------------displaySideways--------------------------------------------------
//display a binary tree
void BinTree::displaySideways() const {
    sidewaysHelper(root, 0);
}
//------------sidewaysHelper--------------------------------------------------
void BinTree::sidewaysHelper(NodeData* current, int level) const {
    if (current != nullptr) {
        level++;
        sidewaysHelper(current->right, level);

        // indent for readability, same number of spaces per depth level 
        for (int i = level; i >= 0; i--) {
            cout << "      ";
        }
        // display information of object
        cout << current->data << endl;        
        sidewaysHelper(current->left, level);
    }
}
BinTree& BinTree::operator=(const BinTree& treeFrom)
{
    if (this == &treeFrom)
    {
        return *this;
    }
    clear();
    copy(treeFrom);
    return *this;
}
BinTree::BinTree(const BinTree& treeFrom)
{
    copy(treeFrom);
}
BinTree::BinTree()
{
    root = 0;
}
//----------------copy---------------------------------------------------------
void BinTree::copy(const BinTree& other)
{
    return copy2(root, other.root);   
}
//----------------copy2--------------------------------------------------------
void BinTree::copy2(NodeData*& dest, const NodeData* source)
{
    if (source == nullptr)
    {
        dest = nullptr;
        return;
    }
    dest = new NodeData(source->data);
    copy2(dest->left, source->left);
    copy2(dest->right, source->right);
}
//-----------------------equal-------------------------------------------------
bool BinTree::equal(const BinTree & other) const
{
    return equal2(root, other.root);
}


//-----------------equal2------------------------------------------------------
bool BinTree::equal2(const NodeData * lhs, const NodeData * rhs) const
{
    if (lhs == nullptr && rhs == nullptr)
    {
        return true;
    }
    if (isLeafNodeEqual(lhs, rhs))
    {
        return true;
    }
    if (lhs && rhs && lhs->data == rhs->data)
    {
        return equal2(lhs->left, rhs->left) && equal2(lhs->right, rhs->right);
    }
    return false;
}
//-----------------------isLeafNodeEqual---------------------------------------
bool BinTree::isLeafNodeEqual(const NodeData * lhs, const NodeData * rhs) const
{
    if (isNodeLeaf(lhs) && isNodeLeaf(rhs))
    {
        return lhs->data == rhs->data;
    }
    return false;
}
//----------------isNodeLeaf---------------------------------------------------
bool BinTree::isNodeLeaf(const NodeData * node) const
{
    return node != nullptr && node->left == nullptr && node->right == nullptr;
}
//------------------inorderPrint
void BinTree::inorderPrint(std::ostream& os, const NodeData * node) const
{
    if (node == nullptr)
    {
        return;
    }
    inorderPrint(os, node->left);
    os << node->data << " ";
    inorderPrint(os, node->right);
}
//-----------inorderHelper-----------------------------------------------------
void BinTree::inorderHelper(NodeData* current, NodeData*(&ndArray)[100], int& count)
{
    if (current)
    {
        if (current->left)
        {
            inorderHelper(current->left, ndArray, count);
        }
        ndArray[count] = new NodeData(current->data);
        ++count;
        if (current->right)
        {
            inorderHelper(current->right, ndArray, count);
        }
    }
}
//------------------clear------------------------------------------------------
void BinTree::clear(void)
{
    if (root)
    {
        stack<NodeData*> node_stack;
        node_stack.push(root);
        NodeData* t;
        while (!node_stack.empty())
        {
            t = node_stack.top();
            node_stack.pop();
            if (t->right != 0)
            {
                node_stack.push(t->right);
            }
            if (t->left != 0)
            {
                node_stack.push(t->left);
            }
            delete t;
        }
        root = nullptr;
    }
}
