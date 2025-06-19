// Basic test program for AVL Tree
// Author: John Edgar
// Date: July 2022

// #include <vector>
// #include <iostream>
// #include "AVLTree.h"
// using std::cout;
// using std::endl;
// using std::vector;

// void a4marking();
// template <class K, class V>
// bool checkAVLTree(const AVLTree<K, V>& tree);

// int main()
// {
//     a4marking();

//     cout << endl;
// }

// void a4marking()
// {
//     AVLTree<int, int> aspen;

//     // Method return values
//     bool success = aspen.insert(1, 2);
//     int result = aspen.search(1);
//     checkAVLTree<int, int>(aspen);
//     success = aspen.remove(1);
//     vector<int> v2 = aspen.values();
//     vector<int> k1 = aspen.keys();
//     AVLTree<int, int> larch(aspen);
//     aspen = larch;|

//     cout << endl << "end a4 test" << endl;
// }

// template <class K, class V>
// bool checkAVLTree(const AVLTree<K, V>& tree)
// {
//     AVLTreeNode<K, V>* nd = (AVLTreeNode<K, V>*)tree.getRoot();
//     cout << "height = " << nd->height << endl;

//     return false;
// }


// Basic test program for AVL Tree
// Author: John Edgar
// Date: July 2022
// Modified to include comprehensive tests

#include <vector>
#include <iostream>
#include "AVLTree.h"
using std::cout;
using std::endl;
using std::vector;

void a4marking();
template <class K, class V>
bool checkAVLTree(const AVLTree<K, V>& tree);

// Helper function to print a vector
template <typename T>
void printVector(const std::vector<T>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

int main()
{
    a4marking();
    cout << endl;
    return 0;
}

void a4marking()
{
    cout << "=== Starting AVL Tree Tests ===\n" << endl;

    AVLTree<int, int> aspen;

    // Test 1: Insert and Search
    cout << "Test 1: Insert and Search" << endl;
    cout << "Inserting (1, 10), (2, 20), (3, 30), (4, 40), (5, 50)" << endl;
    bool success = aspen.insert(1, 10);
    cout << "Insert (1, 10): " << (success ? "Success" : "Failed") << endl;
    success = aspen.insert(2, 20);
    cout << "Insert (2, 20): " << (success ? "Success" : "Failed") << endl;
    success = aspen.insert(3, 30);
    cout << "Insert (3, 30): " << (success ? "Success" : "Failed") << endl;
    success = aspen.insert(4, 40);
    cout << "Insert (4, 40): " << (success ? "Success" : "Failed") << endl;
    success = aspen.insert(5, 50);
    cout << "Insert (5, 50): " << (success ? "Success" : "Failed") << endl;

    // Test duplicate insert
    success = aspen.insert(1, 100);
    cout << "Insert duplicate (1, 100): " << (success ? "Failed (should not insert)" : "Success (duplicate not inserted)") << endl;

    // Check tree height
    checkAVLTree(aspen);

    // Test search
    try {
        int value = aspen.search(3);
        cout << "Search (3): Found value " << value << endl;
    } catch (const std::runtime_error& e) {
        cout << "Search (3): " << e.what() << endl;
    }

    try {
        int value = aspen.search(6);
        cout << "Search (6): Found value " << value << endl;
    } catch (const std::runtime_error& e) {
        cout << "Search (6): " << e.what() << endl;
    }

    // Test size
    cout << "Size: " << aspen.size() << endl;

    // Test keys and values
    cout << "Keys: ";
    printVector(aspen.keys());
    cout << "Values: ";
    printVector(aspen.values());
    cout << endl;

    // Test 2: Remove
    cout << "Test 2: Remove" << endl;
    success = aspen.remove(3); // Remove a node with two children
    cout << "Remove (3): " << (success ? "Success" : "Failed") << endl;
    checkAVLTree(aspen);
    cout << "Size after remove: " << aspen.size() << endl;
    cout << "Keys after remove: ";
    printVector(aspen.keys());
    cout << "Values after remove: ";
    printVector(aspen.values());

    success = aspen.remove(1); // Remove a leaf node
    cout << "Remove (1): " << (success ? "Success" : "Failed") << endl;
    checkAVLTree(aspen);
    cout << "Size after remove: " << aspen.size() << endl;

    success = aspen.remove(6); // Remove a non-existent node
    cout << "Remove (6): " << (success ? "Failed (should not remove)" : "Success (key not found)") << endl;
    cout << endl;

    // Test 3: Copy Constructor
    cout << "Test 3: Copy Constructor" << endl;
    AVLTree<int, int> larch(aspen);
    cout << "Copied tree size: " << larch.size() << endl;
    cout << "Copied tree keys: ";
    printVector(larch.keys());
    cout << "Copied tree values: ";
    printVector(larch.values());
    // Modify original tree to ensure deep copy
    aspen.insert(6, 60);
    cout << "Original tree keys after adding (6, 60): ";
    printVector(aspen.keys());
    cout << "Copied tree keys (should be unchanged): ";
    printVector(larch.keys());
    cout << endl;

    // Test 4: Assignment Operator
    cout << "Test 4: Assignment Operator" << endl;
    AVLTree<int, int> pine;
    pine.insert(7, 70);
    pine = aspen;
    cout << "Assigned tree size: " << pine.size() << endl;
    cout << "Assigned tree keys: ";
    printVector(pine.keys());
    cout << "Assigned tree values: ";
    printVector(pine.values());
    // Modify original tree to ensure deep copy
    aspen.remove(2);
    cout << "Original tree keys after removing (2): ";
    printVector(aspen.keys());
    cout << "Assigned tree keys (should be unchanged): ";
    printVector(pine.keys());
    cout << endl;

    // Test 5: Empty Tree
    cout << "Test 5: Empty Tree" << endl;
    while (aspen.size() > 0) {
        aspen.remove(aspen.keys()[0]);
    }
    checkAVLTree(aspen);
    cout << "Size of empty tree: " << aspen.size() << endl;
    cout << "Keys of empty tree: ";
    printVector(aspen.keys());
    cout << "Values of empty tree: ";
    printVector(aspen.values());

    cout << "\n=== End of AVL Tree Tests ===" << endl;
}

template <class K, class V>
 bool checkAVLTree(const AVLTree<K, V>& tree)
 {
     AVLTreeNode<K, V>* nd = (AVLTreeNode<K, V>*)tree.getRoot();
    cout << "height = " << nd->height << endl;

     return false;
}