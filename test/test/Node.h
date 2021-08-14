
#include <iostream>
#include <string>

using namespace std;

// TreeNode class
template <class T>
class TreeNode
{

public:
    T key;
    TreeNode<T> *left = nullptr;
    TreeNode<T> *right = nullptr;
    

    // Constructors
    TreeNode()
    {
        right = nullptr;
        left = nullptr;
    }

    TreeNode(T akey)
    {
        key = akey;
    }

};

