#include <vector>
#include <stdexcept>

using std::vector;

// AVL Node Class
template <typename K, typename V>
class AVLTreeNode {
public:
    K key;
    V value;
    AVLTreeNode* left;
    AVLTreeNode* right;
    AVLTreeNode* parent;
    unsigned int height;

    // Constructor
    AVLTreeNode(const K& k, const V& v)
        : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
};

// AVL Tree Class
template <typename K, typename V>
class AVLTree {
private:
    AVLTreeNode<K,V>* root;
    unsigned int treeSize;

    unsigned int getHeight(AVLTreeNode<K,V>* node) const;
    int getBalanceFactor(AVLTreeNode<K,V>* node) const;
    void updateHeight(AVLTreeNode<K,V>* node);
    AVLTreeNode<K,V>* copyTree(const AVLTreeNode<K,V>* node, AVLTreeNode<K,V>* parent);
    void destroyTree(AVLTreeNode<K,V>* node);
    void rotateLeft(AVLTreeNode<K,V>*& node);
    void rotateRight(AVLTreeNode<K,V>*& node);
    void balance(AVLTreeNode<K,V>*& node);
    AVLTreeNode<K,V>* findMin(AVLTreeNode<K,V>* node) const;
    void collectValues(AVLTreeNode<K,V>* node, vector<V>& result) const;
    void collectKeys(AVLTreeNode<K,V>* node, vector<K>& result) const;

public:
    AVLTree();
    AVLTree(AVLTree& t);
    AVLTree& operator=(AVLTree& t);
    ~AVLTree();

    bool insert(const K& k, const V& v);
    bool remove(const K& key);
    V search(const K& k);
    vector<V> values();
    vector<K> keys();
    unsigned int size();
    void* getRoot() const { return root; }; // DO NOT REMOVE
};

// AVL Tree Methods
template <typename K, typename V>
unsigned int AVLTree<K, V>::getHeight(AVLTreeNode<K, V>* node) const {
    return node ? node->height : 0;
}

template <typename K, typename V>
int AVLTree<K, V>::getBalanceFactor(AVLTreeNode<K,V>* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

template <typename K, typename V>
void AVLTree<K, V>::updateHeight(AVLTreeNode<K,V>* node) {
    if (node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }
}

template <typename K, typename V>
AVLTreeNode<K,V>* AVLTree<K,V>::copyTree(const AVLTreeNode<K,V>* node, AVLTreeNode<K,V>* parent) {
    if (!node) return nullptr;
    AVLTreeNode<K,V>* newNode = new AVLTreeNode<K,V>(node->key, node->value);
    newNode->height = node->height;
    newNode->parent = parent;
    newNode->left = copyTree(node->left, newNode);
    newNode->right = copyTree(node->right, newNode);
    return newNode;
}

template <typename K, typename V>
void AVLTree<K,V>::destroyTree(AVLTreeNode<K,V>* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

template <typename K, typename V>
void AVLTree<K, V>::rotateLeft(AVLTreeNode<K,V>*& node) {
    AVLTreeNode<K,V>* newRoot = node->right;
    node->right = newRoot->left;
    if (node->right) node->right->parent = node;
    newRoot->left = node;
    newRoot->parent = node->parent;
    node->parent = newRoot;
    if (newRoot->parent) {
        if (newRoot->parent->left == node) {
            newRoot->parent->left = newRoot;
        } else {
            newRoot->parent->right = newRoot;
        }
    }
    updateHeight(node);
    updateHeight(newRoot);
    node = newRoot;
}

template <typename K, typename V>
void AVLTree<K, V>::rotateRight(AVLTreeNode<K,V>*& node) {
    AVLTreeNode<K,V>* newRoot = node->left;
    node->left = newRoot->right;
    if (node->left) node->left->parent = node;
    newRoot->right = node;
    newRoot->parent = node->parent;
    node->parent = newRoot;
    if (newRoot->parent) {
        if (newRoot->parent->left == node) {
            newRoot->parent->left = newRoot;
        } else {
            newRoot->parent->right = newRoot;
        }
    }
    updateHeight(node);
    updateHeight(newRoot);
    node = newRoot;
}

template <typename K, typename V>
void AVLTree<K, V>::balance(AVLTreeNode<K,V>*& node) {
    if (!node) return;

    int bf = getBalanceFactor(node);
    if (bf > 1) {
        if (getBalanceFactor(node->left) < 0) {
            rotateLeft(node->left);
        }
        rotateRight(node);
    } else if (bf < -1) {
        if (getBalanceFactor(node->right) > 0) {
            rotateRight(node->right);
        }
        rotateLeft(node);
    }
}

template <typename K, typename V>
AVLTreeNode<K,V>* AVLTree<K, V>::findMin(AVLTreeNode<K,V>* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

template <typename K, typename V>
void AVLTree<K, V>::collectValues(AVLTreeNode<K,V>* node, vector<V>& result) const {
    if (node) {
        collectValues(node->left, result);
        result.push_back(node->value);
        collectValues(node->right, result);
    }
}

template <typename K, typename V>
void AVLTree<K, V>::collectKeys(AVLTreeNode<K,V>* node, vector<K>& result) const {
    if (node) {
        collectKeys(node->left, result);
        result.push_back(node->key);
        collectKeys(node->right, result);
    }
}

template <typename K, typename V>
AVLTree<K, V>::AVLTree() : root(nullptr), treeSize(0) {}

template <typename K, typename V>
AVLTree<K, V>::AVLTree(AVLTree& t) {
    root = copyTree(t.root, nullptr);
    treeSize = t.treeSize;
}

template <typename K, typename V>
AVLTree<K,V>& AVLTree<K, V>::operator=(AVLTree& other) {
    if (this != &other) {
        destroyTree(root);
        root = copyTree(other.root, nullptr);
        treeSize = other.treeSize;
    }
    return *this;
}

template <typename K, typename V>
AVLTree<K, V>::~AVLTree() {
    destroyTree(root);
}

template <typename K, typename V>
bool AVLTree<K, V>::insert(const K& k, const V& v) {
    AVLTreeNode<K,V>* newNode = new AVLTreeNode<K,V>(k, v);
    if (!root) {
        root = newNode;
        treeSize++;
        return true;
    }

    AVLTreeNode<K,V>* current = root;
    while (true) {
        if (k < current->key) {
            if (!current->left) {
                current->left = newNode;
                newNode->parent = current;
                treeSize++;
                break;
            }
            current = current->left;
        } else if (k > current->key) {
            if (!current->right) {
                current->right = newNode;
                newNode->parent = current;
                treeSize++;
                break;
            }
            current = current->right;
        } else {
            delete newNode;
            return false; // Duplicate key
        }
    }

    current = newNode;
    while (current) {
        updateHeight(current);
        balance(current);
        if (!current->parent) {
            root = current;
            break;
        }
        current = current->parent;
    }
    return true;
}

template <typename K, typename V>
bool AVLTree<K, V>::remove(const K& key) {
    AVLTreeNode<K,V>* current = root;
    while (current && current->key != key) {
        current = (key < current->key) ? current->left : current->right;
    }
    if (!current) return false;

    AVLTreeNode<K,V>* toBalance = nullptr;
    if (!current->left || !current->right) {
        toBalance = current->parent;
        AVLTreeNode<K,V>* child = current->left ? current->left : current->right;
        if (!toBalance) {
            root = child;
        } else if (current == toBalance->left) {
            toBalance->left = child;
        } else {
            toBalance->right = child;
        }
        if (child) child->parent = toBalance;
        delete current;
    } else {
        AVLTreeNode<K,V>* successor = findMin(current->right);
        if (successor->parent != current) {
            successor->parent->left = successor->right;
            if (successor->right) successor->right->parent = successor->parent;
            successor->right = current->right;
            current->right->parent = successor;
        }
        successor->left = current->left;
        current->left->parent = successor;
        successor->parent = current->parent;
        if (!current->parent) {
            root = successor;
        } else if (current == current->parent->left) {
            current->parent->left = successor;
        } else {
            current->parent->right = successor;
        }
        toBalance = successor->parent;
        delete current;
    }

    while (toBalance) {
        updateHeight(toBalance);
        balance(toBalance);
        if (toBalance == root) 
		break;
        toBalance = toBalance->parent;
    }
    treeSize--;
    return true;
}

template <typename K, typename V>
V AVLTree<K, V>::search(const K& key) {
    AVLTreeNode<K,V>* current = root;
    while (current) {
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            return current->value;
        }
    }
    throw std::runtime_error("Key not found");
}

template <typename K, typename V>
vector<V> AVLTree<K, V>::values() {
    vector<V> result;
    collectValues(root, result);
    return result;
}

template <typename K, typename V>
vector<K> AVLTree<K, V>::keys() {
    vector<K> result;
    collectKeys(root, result);
    return result;
}

template <typename K, typename V>
unsigned int AVLTree<K, V>::size() {
    return treeSize;
}
