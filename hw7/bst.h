/**
 * bst.h
 *  Implements a(n unbalanced) BST storing Key,Value pairs
 */
#ifndef BST_H
#define BST_H
#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/* -----------------------------------------------------
 * Regular Binary Tree Nodes
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
  class Node {
 public:
  Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p)
    : _item(k, v)
   // the default is to create new nodes as leaves
    { _parent = p; _left = _right = NULL; }
  
  virtual ~Node()
  { }
  
  std::pair<const KeyType, ValueType> const & getItem () const
    { return _item; }
  
  std::pair<const KeyType, ValueType> & getItem ()
    { return _item; }
  
  const KeyType & getKey () const
  { return _item.first; }
  
  const ValueType & getValue () const
  { return _item.second; }
  
  /* the next three functions are virtual because for Red-Black-Trees,
     we'll want to use Red-Black nodes, and for those, the 
     getParent, getLeft, and getRight functions should return 
     Red-Black nodes, not just ordinary nodes.
     That's an advantage of using getters/setters rather than a struct. */
  
  virtual Node<KeyType, ValueType> *getParent () const
    { return _parent; }
  
  virtual Node<KeyType, ValueType> *getLeft () const
    { return _left; }
  
  virtual Node<KeyType, ValueType> *getRight () const
    { return _right; }
  
  
  void setParent (Node<KeyType, ValueType> *p)
  { _parent = p; }
  
  void setLeft (Node<KeyType, ValueType> *l)
  { _left = l; }
  
  void setRight (Node<KeyType, ValueType> *r)
  { _right = r; }
  
  void setValue (const ValueType &v)
  { _item.second = v; }
  
 protected:
  std::pair<const KeyType, ValueType> _item;
  Node <KeyType, ValueType> *_left, *_right, *_parent;
};

/* -----------------------------------------------------
 * Regular Binary Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class BinarySearchTree {
 protected:
  // Main data member of the class
  Node<KeyType, ValueType> *root;

 public:
  /**
   * Constructor
   */
  BinarySearchTree () { root = NULL; }
  /*void insert(const std::pair<const KeyType, ValueType> new_item) {
  this->root = insertInTree(NULL, this->root, new_item);
     
     
     

  }
  Node<KeyType, ValueType>* insertInTree(Node<KeyType, ValueType>* parent, Node<KeyType, ValueType>* node, const std::pair<const KeyType, ValueType> new_item) {
    if(node == NULL) {
      
      Node<KeyType, ValueType>* star = new Node<KeyType, ValueType>(new_item.first, new_item.second, parent);
      
     // if (this->root == NULL) {

       // static_cast<RedBlackNode<KeyType,ValueType>*>(star)->setColor(black);
      //}
      //else {

        //static_cast<RedBlackNode<KeyType,ValueType>*>(star)->setColor(red);
        
        //fixTree(star);
      
      return star;
    }   
    // go left
    if(new_item.first < node->getKey()) {
        node->setLeft(insertInTree(node, node->getLeft(), new_item));
    }
    else {
        node->setRight(insertInTree(node, node->getRight(), new_item));
    }
  
    return node;
  }*/
  /**
   * Destructor
   */
  ~BinarySearchTree () { deleteAll (root); }

  /**
   * Prints the entire tree structure in a nice format 
   *  
   * It will denote subtrees in [] brackets.
   *  This could be helpful if you want to debug your functions. 
   */  
  virtual void print () const
  { 
    printRoot (root);
    std::cout << "\n";
  }

  
  /**
   * An In-Order iterator
   *  !!! You must implement this !!!
   */
  class iterator {
  public:
    /**
     * Initialize the internal members of the iterator
     */
    iterator(Node<KeyType,ValueType>* ptr) {
    	curr = ptr;
    }
    
    std::pair<const KeyType,ValueType>& operator*()
      { return curr->getItem();  }
    
    std::pair<const KeyType,ValueType>* operator->() 
      { return &(curr->getItem()); }
    
    /**
     * Checks if 'this' iterator's internals have the same value
     *  as 'rhs'
     */
    bool operator==(const iterator& rhs) const {
    	return this->curr == rhs.curr;
    }
    
    /**
     * Checks if 'this' iterator's internals have a different value
     *  as 'rhs'
     */
    bool operator!=(const iterator& rhs) const {
    	return (this->curr != rhs.curr);
    }
    
    /**
     * Advances the iterator's location using an in-order sequencing
     */
    iterator& operator++() {
    	Node<KeyType, ValueType> *temp;
    	temp = curr;
    	
    	while (temp->getKey() >= curr->getKey()) {
    	
    		bool move = false;
    		while (((curr->getRight() != NULL) || (curr->getLeft() != NULL)) && ((temp->getKey() > curr->getRight()->getKey()) || temp->getKey() > curr->getLeft()->getKey())) {
    			while (curr->getLeft() != NULL && (temp->getKey() > curr->getLeft()->getKey())) {
    				curr = curr->getLeft();
    			}
    			move = true;
    			if (curr->getRight() != NULL) {
    				curr = curr->getRight();
    			}
    		}
    		if(move == false) {
    			curr = curr->getParent();
    		}
    	}
    	
    return *this;
    }
    

    Node<KeyType, ValueType>* curr;
    //you are welcome to add any necessary variables and helper functions here.

  };
  
  /**
   * Returns an iterator to the "smallest" item in the tree
   */
  iterator begin() {
  	Node<KeyType, ValueType> *cool;
  	
  	cool = root;
  	
  	while(cool->getLeft() != NULL) {
  		cool = cool->getLeft();
  		
  	}
  	
  	return iterator(cool);
  } 

  /**
   * Returns an iterator whose value means INVALID
   */
  iterator end() {
  	Node<KeyType, ValueType> *cool;
  	
  	cool = root;
  	
  	while(cool->getRight() != NULL) {
  		cool = cool->getRight();
  		
  	}
  	
  	return iterator(cool);
  }

  /**
   * Returns an iterator to the item with the given key, k
   * or the end iterator if k does not exist in the tree
   */
  iterator find (const KeyType & k) const 
  {
    Node<KeyType, ValueType> *curr = internalFind(k);
    iterator it(curr);
    return it;
  }
  
  
 protected:
  /**
   * Helper function to find a node with given key, k and 
   * return a pointer to it or NULL if no item with that key
   * exists
   */
  Node<KeyType, ValueType>* internalFind(const KeyType& k) const 
  {
    Node<KeyType, ValueType> *curr = root;
    while (curr) {
      if (curr->getKey() == k) {
	return curr;
      } else if (k < curr->getKey()) {
	curr = curr->getLeft();
      } else {
	curr = curr->getRight();
      }
    }
    return NULL;
  }
  
  /**
   * Helper function to print the tree's contents
   */
  virtual void printRoot (Node<KeyType, ValueType> *r) const
  {
    if (r != NULL)
      {
	std::cout << "[";
	printRoot (r->getLeft());
	std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
	printRoot (r->getRight());
	std::cout << "]";
      }
  }

  
  /**
   * Helper function to delete all the items
   */
  void deleteAll (Node<KeyType, ValueType> *r)
  {
    if (r != NULL)
      {
	deleteAll (r->getLeft());
	deleteAll (r->getRight());
	delete r;
      }
  }
};

/* Feel free to add member function definitions here if you need */

#endif
