/*
 * rbbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 */
#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

/* -----------------------------------------------------
 * Red-Black Nodes and Search Tree
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
  RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { color = red; }
  
  virtual ~RedBlackNode () {}
  
  Color getColor () const
    { return color; }
  
  void setColor (Color c)
    { color = c; }
  
  virtual RedBlackNode<KeyType, ValueType> *getParent () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_parent; }
  
  virtual RedBlackNode<KeyType, ValueType> *getLeft () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_left; }
  
  virtual RedBlackNode<KeyType, ValueType> *getRight () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_right; }
  
 protected:
  Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:
  void insert (const std::pair<const KeyType, ValueType>& new_item) {
  /* This one is yours to implement.
     It should insert the (key, value) pair to the tree, 
     making sure that it remains a valid Red-Black Tree.
     If the key is already in the tree
     (with a possibly different associated value),
     then it should overwrite the value with the new one.
     We strongly recommend defining suitable (private) helper functions. */

     //insertToTree(new_item);
     

     this->root = insertInTree(NULL, this->root, new_item);
     
     
     

  }
  Node<KeyType, ValueType>* insertInTree(Node<KeyType, ValueType>* parent, Node<KeyType, ValueType>* node, const std::pair<const KeyType, ValueType> new_item) {
    if(node == NULL) {
      
      Node<KeyType, ValueType>* star = new Node<KeyType, ValueType>(new_item.first, new_item.second, parent);
      
      if (this->root == NULL) {
        static_cast<RedBlackNode<KeyType,ValueType>*>(star)->setColor(black);
      }
      else {
        static_cast<RedBlackNode<KeyType,ValueType>*>(star)->setColor(red);
        
        fixTree(star);
      }
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
  }
  void fixTree(Node<KeyType, ValueType>* cool) {
      /*Node<KeyType, ValueType>* temp = cool;
      std::cout << "fuck" << std::endl;
      if (static_cast<RedBlackNode<KeyType,ValueType>*>(temp->getParent())->getColor() == red) {
        std::cout << "shit" << std::endl;
        if (temp->getParent()->getParent() != NULL) {
          
          if (static_cast<RedBlackNode<KeyType,ValueType>*>(temp->getParent()->getParent()->getLeft())->getColor() == red && static_cast<RedBlackNode<KeyType,ValueType>*>(temp->getParent()->getParent()->getRight())->getColor() == red) {
            std::cout << "shithead" << std::endl;
            reColor(cool); 

          }

          else {
            if (temp->getParent()->getParent()->getLeft() != temp->getParent()) {
              std::cout << "shithead" << std::endl;
              rotateLeft(cool);
            }
            else {
              std::cout << "shithead" << std::endl;
              rotateRight(cool);
            }
          }
        }
        else {
           if (temp->getParent()->getParent()->getLeft() != temp->getParent()) {
              rotateLeft(cool);
            }
            else {
              rotateRight(cool);
            }
        }
      }
*/
    if (cool->getParent() != NULL) {

      if (cool ->getParent() -> getParent() != NULL) {

        if (static_cast<RedBlackNode<KeyType,ValueType>*>(cool)->getColor() == red && static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent())->getColor() == red) {
          std::cout << "fucking motherfucking shit fuck" << std::endl;
          if (cool->getParent()->getLeft() == cool && cool->getParent()->getParent()->getRight() == cool ->getParent()) {
            if (cool->getParent()->getParent()->getLeft() == NULL || static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getLeft())->getColor() == black) {
              
              rotateRight(cool);

            }
            else {
              reColor(cool->getParent());
            }
          }

          else if (cool->getParent()->getRight() == cool && cool->getParent()->getParent()->getRight() == cool ->getParent()) {
            
            if (cool->getParent()->getParent()->getLeft() == NULL || static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getLeft())->getColor() == black) {
              rotateLeft(cool->getParent());
            }
            else{
              reColor(cool->getParent());
            }
          }
          else if (cool->getParent()->getLeft() == cool && cool->getParent()->getParent()->getLeft() == cool ->getParent()) {
            if (cool->getParent()->getParent()->getRight() == NULL || static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getRight())->getColor() == black) {
              rotateLeft(cool);
            }
            else{
              reColor(cool->getParent());
            }
          }
          else if (cool->getParent()->getRight() == cool && cool->getParent()->getParent()->getLeft() == cool ->getParent()) {
            if (cool->getParent()->getParent()->getRight() == NULL || static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getRight())->getColor() == black) {
              //std::cout << "wrodl" << std::endl;
              rotateRight(cool->getParent());
            }
            else{
              reColor(cool->getParent());
            }

          }
        }
      }
    }

    //if (cool->getParent() != NULL) {
      //    fixTree(cool->getParent());
        //}
  }

  void reColor(Node<KeyType, ValueType>* cool) {
    std::cout << cool->getKey() << std::endl;
   static_cast<RedBlackNode<KeyType,ValueType>*> (cool->getParent())->setColor(red);
    static_cast<RedBlackNode<KeyType,ValueType>*> (cool->getParent()->getLeft())->setColor(black);
    static_cast<RedBlackNode<KeyType,ValueType>*> (cool->getParent()->getRight())->setColor(black);

    /*cool = cool->getParent();
    if (static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent())->getColor() == red) {
        if (cool->getParent()->getParent()->getLeft() != NULL && cool->getParent()->getParent()->getRight() != NULL) {
          if (static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getLeft())->getColor() == red && static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getRight())->getColor() == red) {
            reColor(cool);   
          }

          else {
            if (cool->getParent()->getRight()->getKey() == cool->getKey()) {
              rotateLeft(cool);
            }
            else {
              rotateRight(cool);
            }
          }
        }
        else {
           if (cool->getParent()->getRight()->getKey() == cool->getKey()) {
              rotateLeft(cool);
            }
            else {
              rotateRight(cool);
            }
        }
      }*/
        if (cool->getParent() != NULL) {
          fixTree(cool->getParent());
        }
  }

  void rotateRight(Node<KeyType, ValueType>* cool) {
    std::cout << cool->getKey() << std::endl;
    Node<KeyType, ValueType>* total_parent = cool->getParent()->getParent();
    Node<KeyType, ValueType>* lefttemp = cool->getLeft();
    Node<KeyType, ValueType>* newleft = cool->getParent();

    if (newleft->getKey() == total_parent->getLeft()->getKey()) {

      total_parent->setLeft(cool);
      cool->setParent(total_parent);
      
      newleft->setRight(lefttemp);
      lefttemp->setParent(newleft);

      newleft->setParent(cool);
      cool->setLeft(newleft);
     
      static_cast<RedBlackNode<KeyType,ValueType>*> (cool)->setColor(black);
    }
    else {
      total_parent->setRight(cool);
      cool->setParent(total_parent);
      
      newleft->setRight(lefttemp);
      lefttemp->setParent(newleft);

      newleft->setParent(cool);
      cool->setLeft(newleft);
      static_cast<RedBlackNode<KeyType,ValueType>*> (cool)->setColor(black);
    }

   /* cool = cool->getParent(); 
    if (static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent())->getColor() == red) {
        if (cool->getParent()->getParent()->getLeft() != NULL && cool->getParent()->getParent()->getRight() != NULL) {
          if (static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getLeft())->getColor() == red && static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getRight())->getColor() == red) {
            reColor(cool);   
           
          }

          else {
            if (cool->getParent()->getRight()->getKey() == cool->getKey()) {
              rotateLeft(cool);
            }
            else {
              rotateRight(cool);
            }
          }
        }
        else {
           if (cool->getParent()->getRight()->getKey() == cool->getKey()) {
              rotateLeft(cool);
            }
            else {
              rotateRight(cool);
            }
        }
      }*/
        fixTree(cool->getParent());
  }

void rotateLeft(Node<KeyType, ValueType>* cool) {
    std::cout << cool->getKey() << std::endl;
    Node<KeyType, ValueType>* total_parent = cool->getParent()->getParent();
    Node<KeyType, ValueType>* lefttemp = cool->getLeft();
    Node<KeyType, ValueType>* newleft = cool->getParent();

    if (newleft->getKey() == total_parent->getLeft()->getKey()) {
      total_parent->setLeft(cool);
      cool->setParent(total_parent);
      
      newleft->setRight(lefttemp);
      lefttemp->setParent(newleft);

      newleft->setParent(cool);
      cool->setLeft(newleft);
      static_cast<RedBlackNode<KeyType,ValueType>*> (cool)->setColor(black);
    }
    else {
      total_parent->setRight(cool);
      cool->setParent(total_parent);
      
      newleft->setRight(lefttemp);
      lefttemp->setParent(newleft);

      newleft->setParent(cool);
      cool->setLeft(newleft);
      static_cast<RedBlackNode<KeyType,ValueType>*> (cool)->setColor(black);
    }

    /*cool = cool->getParent(); 
    if (static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent())->getColor() == red) {
        if (cool->getParent()->getParent()->getLeft() != NULL && cool->getParent()->getParent()->getRight() != NULL) {
          if (static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getLeft())->getColor() == red && static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getRight())->getColor() == red) {
            reColor(cool);   
          }

          else {
            if (cool->getParent()->getRight()->getKey() == cool->getKey()) {
              rotateLeft(cool);
            }
            else {
              rotateRight(cool);
            }
          }
        }
        else {
           if (cool->getParent()->getRight()->getKey() == cool->getKey()) {
              rotateLeft(cool);
            }
            else {
              rotateRight(cool);
            }
        }
      }*/
      fixTree(cool->getParent());
  }


  
};

#endif
