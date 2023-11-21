/********************************************************************************* 
* Roman Luo, yluo111
* 2023 Winter CSE101 PA# 7
* Dictionary.cpp 
* implementation file for Dictionary ADT
*********************************************************************************/ 
#include<iostream>
#include<string>
#include"Dictionary.h"

// Class Constructors & Destructors ----------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v) {
   key = k;
   val = v;
   parent = nullptr;
   left = nullptr;
   right = nullptr;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
   nil = new Node("", 0);
   nil->left = nil;
   nil->right = nil;
   nil->parent = nil;
   
   root = nil;
   current = nil;
   num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
   nil = new Node("", 0);
   nil->left = nil;
   nil->right = nil;
   nil->parent = nil;

   root = nil;
   current = nil;
   
   num_pairs = 0;
   if (D.root != D.nil) {
      // root = new Node(D.root->key, D.root->val);
      // root->parent = nil;
      preOrderCopy(D.root, D.nil); // preOrderCopy is called with D's root and nil
   }
}

// Destructor
Dictionary::~Dictionary() {
   if(root != nil) {
      postOrderDelete(root); // Assume postOrderDelete is correctly implemented
   }
   delete nil;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
//-----------------------------------------------------------------------------
// InOrderTreeWalk(x)
//    if x != NIL
//       InOrderTreeWalk(x.left)
//       print(x.key)
//       InOrderTreeWalk(x.right)
//-----------------------------------------------------------------------------
void Dictionary::inOrderString(std::string& s, Node* R) const {
   if (R != nil) {
      inOrderString(s, R->left);
      s += R->key + " : " + std::to_string(R->val) + "\n";
      inOrderString(s, R->right);
   }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
//-----------------------------------------------------------------------------
// PreOrderTreeWalk(x)
//    if x != NIL
//       print(x.key)
//       PreOrderTreeWalk(x.left)
//       PreOrderTreeWalk(x.right)
//-----------------------------------------------------------------------------
void Dictionary::preOrderString(std::string& s, Node* R) const {
   if (R != nil) {
      s += R->key + "\n";
      preOrderString(s, R->left);
      preOrderString(s, R->right);
   }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
   if (R != N) {
      // std::cout << "Copying key: " << R->key << " with value: " << R->val << std::endl;
      setValue(R->key, R->val);
      preOrderCopy(R->left, N);
      // std::cout << "L======" << std::endl;
      preOrderCopy(R->right, N);
      // std::cout << "R======" << std::endl;
   }
}


// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
//-----------------------------------------------------------------------------
// PostOrderTreeWalk(x)
//    if x != NIL
//       PostOrderTreeWalk(x.left)
//       PostOrderTreeWalk(x.right)
//       print(x.key)
//-----------------------------------------------------------------------------
void Dictionary::postOrderDelete(Node* R) {
   if (R != nil) {
      postOrderDelete(R->left);
      postOrderDelete(R->right);
      delete R;
   }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
   if (R == nil || k == R->key) {
      // If the subtree is empty or the current Node's key is equal to k
      return R;
   } else if (k < R->key) {
      // If the key is less than the current Node's key, search left subtree
      return search(R->left, k);
   } else {
      // If the key is greater than the current Node's key, search right subtree
      return search(R->right, k);
   }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
//-----------------------------------------------------------------------------
// TreeMinimum(x) Pre: x != NIL
//    while x.left != NIL
//       x = x.left
//    return x
//-----------------------------------------------------------------------------
Dictionary::Node* Dictionary::findMin(Node* R) {
   Node* x = R;
   while (x->left != nil) {
      x = x->left;
   }
   return x;
}


// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
//-----------------------------------------------------------------------------
// TreeMaximum(x) Pre: x != NIL
//    while x.right != NIL
//       x = x.right
//    return x
//-----------------------------------------------------------------------------
Dictionary::Node* Dictionary::findMax(Node* R) {
   Node* x = R;
   while (x->right != nil) {
      x = x->right;
   }
      return x;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil.
//-----------------------------------------------------------------------------
// TreeSuccessor(x)
//    if x.right != NIL                 // case 1
//       return TreeMinimum(x.right)
//    y = x.parent                      // case 2
//    while y != NIL and x == y.right
//       x = y
//       y = y.parent
//    return y
//-----------------------------------------------------------------------------
Dictionary::Node* Dictionary::findNext(Node* N) {
   if (N->right != nil) {
      return findMin(N->right);
   }

   Node* y = N->parent;
   while (y != nil && N == y->right) {
      N = y;
      y = y->parent;
   }
   return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
   if (N->left != nil) {
      return findMax(N->left);
   }

   Node* y = N->parent;
   while (y != nil && N == y->left) {
      N = y;
      y = y->parent;
   }
   return y;
}

//-----------------------------------------------------------------------------
// Transplant(T, u, v)
//    if u.parent == NIL
//       T.root = v
//    else if u == u.parent.left
//       u.parent.left = v
//    else 
//       u.parent.right = v
//    if v != NIL
//       v.parent = u.parent
//-----------------------------------------------------------------------------
void Dictionary::transplant(Node* u, Node* v) {
   if (u->parent == nil) { // u is the root
      root = v;
   }
   else if (u == u->parent->left) { // u is the left child of its parent
      u->parent->left = v;
   }
   else { // u is the right child of its parent
      u->parent->right = v;
   }
   if (v != nil) {
      v->parent = u->parent;
   }
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
   return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
   return (search(root, k) != nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
   // Node* node = search(root, k);
   // if(node == nil) {
   //    throw std::logic_error("Key not found in dictionary");
   // }
   // return node->val;


   // TA
   if(!contains(k)) {
      throw std::logic_error("Dictionary: getValue(): key " + k + " does not exist");
   }
   Node* node = search(root, k);
   return node->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
   return current != nil;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
   if (!hasCurrent()) {
      throw std::logic_error("Dictionary: currentKey(): current undefined");
   }
   return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
   if (!hasCurrent()) {
      throw std::logic_error("Dictionary: currentVal(): current undefined");
   }
   return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
   postOrderDelete(root);
   root = nil;
   current = nil;
   num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
//-----------------------------------------------------------------------------
// TreeInsert(T, z)
//    y = NIL
//    x = T.root
//    while x != NIL
//       y = x
//       if z.key < x.key
//          x = x.left
//       else 
//          x = x.right
//    z.parent = y
//    if y == NIL
//       T.root = z    // tree T was empty
//    else if z.key < y.key
//       y.left = z
//    else 
//       y.right = z
//-----------------------------------------------------------------------------
void Dictionary::setValue(keyType k, valType v) {
   Node* y = nil;
   Node* x = root;

   // First, search for a node with the key `k`
   while (x != nil) {
      y = x;
      if (k < x->key) {
         x = x->left;
      } else if (k > x->key) {
         x = x->right;
      } else {
         // Key `k` already exists in the dictionary
         // so update its value and return
         x->val = v;
         return;
      }
   }

   // Create a new node z with key `k` and value `v`
   Node* z = new Node(k, v);

   if (y == nil) {
      // The tree was empty
      // z->parent = nil;
      z->parent = y;
      root = z;
   } else if (k < y->key) {
      z->parent = y;
      y->left = z;
   } else {
      z->parent = y;
      y->right = z;
   }

   z->left = nil;
   z->right = nil;

   num_pairs++;
}



// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
//-----------------------------------------------------------------------------
// Delete(T, z)
//    if z.left == NIL               // case 1  or case 2.1 (right only)
//       Transplant(T, z, z.right)
//    else if z.right == NIL         // case 2.2 (left only)
//       Transplant(T, z, z.left)
//    else                           // case 3
//       y = TreeMinimum(z.right)
//       if y.parent != z
//          Transplant(T, y, y.right)
//          y.right = z.right
//          y.right.parent = y
//       Transplant(T, z, y)
//       y.left = z.left
//       y.left.parent = y
//-----------------------------------------------------------------------------
void Dictionary::remove(keyType k) {
   // find the node with the given key
   Node* z = search(root, k);
   if (z == nil) { // no node with the given key found
      throw std::logic_error("Dictionary: remove(): key " + k + " does not exist");
   }

   // check if node to be removed is the current node
   if (current == z) {
      current = nil;
   }

   // Case 1: z has no left child (so its right child replaces it)
   if (z->left == nil) {
      transplant(z, z->right);
   }
   // Case 2: z has only one child and it's on the left (so its left child replaces it)
   else if (z->right == nil) {
      transplant(z, z->left);
   }
   // Case 3: z has two children
   else {
      Node* y = findMin(z->right); // find the minimum node from the right subtree
      // Case 3.1: if the minimum node isn't direct right child of z
      if (y->parent != z) {
         transplant(y, y->right); // replace y by its own right child
         y->right = z->right; // set right child of y to right child of z
         y->right->parent = y;
      }
      transplant(z, y); // replace z by y
      y->left = z->left; // set left child of y to left child of z
      y->left->parent = y;
   }
   delete z;
   num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
   if (root != nil) {
      current = findMin(root);
      // std::cout << "cur is " << current->key << std::endl;
   }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
   if (root != nil) {
      current = findMax(root);
   }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
   std::string s;
   inOrderString(s, root);
   return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
   std::string s;
   preOrderString(s, root);
   return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
   // Generating the in-order traversal string for the current object.
   std::string s1;
   inOrderString(s1, root);

   // Generating the in-order traversal string for the dictionary object D.
   std::string s2;
   D.inOrderString(s2, D.root);

   // Returning true if both strings are the same.
   return s1 == s2;
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
   return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==(const Dictionary& A, const Dictionary& B) {
   return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=(const Dictionary& D) {
   if(this != &D) { // not self assignment
      // make a copy of D
      Dictionary temp = D;

      // then swap the copy's fields with fields of this
      std::swap(root, temp.root);
      std::swap(nil, temp.nil);
      std::swap(current, temp.current);
      std::swap(num_pairs, temp.num_pairs);
      // continue for any other fields in your Dictionary class
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}



