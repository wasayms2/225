/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
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
    if (t == NULL || t->right == NULL) {
      return;
    }
    Node* t1 = t->right;
    Node* t2 = t->right->left;
    //reassing pointers for rotation
    t->right = t2;
    t1->left = t;
    t = t1;
    t->left->height = 1 + max(heightOrNeg1(t->left->right), heightOrNeg1(t->left->left));
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
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
    if (t == NULL || t->left == NULL) {
      //check if node is null
      return;
    }
    //reassign pointers for rotation
    Node* t1 = t->left;
    Node* t2 = t->left->right;
    t->left = t2;
    t1->right = t;
    t = t1;
    t->right->height = 1 + max(heightOrNeg1(t->right->right), heightOrNeg1(t->right->left));
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));


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
    if(subtree == NULL) {
      //check if null
      return;
    }
    int rBalance = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);
    // right heavy
    if(rBalance < -1){
        if(heightOrNeg1(subtree->right-> left) - heightOrNeg1(subtree->right->right) > 0){
            rotateRightLeft(subtree);
        }else{
            rotateLeft(subtree);
        }
    }
    // left heavy
    if(rBalance > 1){
        if(heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left-> right) < 0){
            rotateLeftRight(subtree);
        }else{
            rotateRight(subtree);
        }
    }
    //always balance the height
    subtree -> height = 1 + max(heightOrNeg1(subtree -> left), heightOrNeg1(subtree -> right));

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
    //helper function
    if(subtree == NULL) {
      subtree = new Node(key, value);
      // check ket relative to subtree key
    } else if(key < subtree->key) {
      //move left if smallet than subtree key
      insert(subtree->left, key, value);
    } else if (key > subtree->key) {
      //rright if larger than subtree key
      insert(subtree->right, key, value);
    } else {
      subtree->value = value;
    }
    //always rebalance
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
  //function to remove node from tree
    if (subtree == NULL){
        return;
      }

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
      //no children
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
          /* two-child remove */
          Node *t = subtree->left;
          while (t->right != NULL) {
            t = t->right;
          }
          swap(t, subtree);
          remove(subtree->left, key);
        } else {
          /* one-child remove */
          //if right is the only child
          if(subtree->left == NULL) {
            Node* t = subtree->right;
            swap(subtree, t);
            subtree->right = t->right;
            subtree->left = t->left;
            delete t;
            // no need to set left and right pointers to NULL
            t = NULL;
          } else {
            //if left is the only child
            Node *t = subtree->left;
            swap(t, subtree);
            subtree->right = t->right;
            subtree->left = t->left;
            delete t;

            t = NULL;
          }

        }
    }
    //rebalnce tree after removal
    if(subtree != NULL) {
      rebalance(subtree);
    }
}
