/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
int AVLTree<K, V>::findheight(Node* subtree) {
  if(subtree == NULL){
      return -1;
    }
    if(findheight(subtree->left) > findheight(subtree->right)){
      return 1 + findheight(subtree->left);
    }
    else{
      return 1 + findheight(subtree->right);
    }
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->right;
    t->right = y->left;
    y->left = t;
    t->height = findheight(t);
    y->height = findheight(y);
    t = y;

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)

    Node* y = t->left;
    t->left = y->right;
    y->right = t;
    t->height = findheight(t);
    y->height = findheight(y);
    t = y;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{

    if (subtree == NULL) {
      return;
    }
    int RootBF = findheight(subtree->right) - findheight(subtree->left);
    if (RootBF == 2) {
      int childBF = findheight(subtree->right->right) - findheight(subtree->right->left);
      if (childBF == 1) {//stick
          rotateLeft(subtree);
      } else if (childBF == -1) {
        rotateRightLeft(subtree);
      }

    } else if (RootBF == -2) {
      int childBF = findheight(subtree->left->right) - findheight(subtree->left->left);
      if (childBF == -1) {//stick
        rotateRight(subtree);
      } else if (childBF == 1) {
        rotateLeftRight(subtree);
      }
    }


}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) subtree = new Node(key,value);
    if (key > subtree->key) insert(subtree->right, key, value);
    if (key < subtree->key) insert(subtree->left, key, value);
    rebalance(subtree);
}


template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
            // your code here
        }
        else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node* tmp = subtree->left;
            while (tmp->right != NULL) {
              tmp = tmp->right;
            }
            swap(subtree,tmp);
            remove(subtree->left, key);
        } else {
                /* one-child remove */
          if (subtree->left != NULL) {
            Node* temp = subtree->left;
            delete subtree;
            subtree = temp;
          } else {
            Node* temp = subtree->right;
            delete subtree;
            subtree = temp;

          }
        }
      }
    rebalance(subtree);
}
