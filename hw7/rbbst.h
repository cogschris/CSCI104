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
  virtual void print () const
  { 
    printRoot (this->root);
    std::cout << "\n";
  }
  virtual void printRoot (Node<KeyType, ValueType> *r) const
  {
    if (r != NULL)
      {
        std::cout << "[";
         // std::cout<<"LEFT";
        printRoot (r->getLeft());
        std::cout << " (" << r->getKey() << ", " << r->getValue() << ", ";
          if(static_cast<RedBlackNode<KeyType,ValueType>*>(r)->getColor() == red) {
            std::cout << "red ";
          }
          else {
            std::cout << "black ";
          }
        std::cout << ") ";
 // std::cout<<"RIGHT";
        printRoot (r->getRight());
        std::cout << "]";
      }
  }
  void insert (const std::pair<const KeyType, ValueType>& new_item) {
  /* This one is yours to implement.
     It should insert the (key, value) pair to the tree, 
     making sure that it remains a valid Red-Black Tree.
     If the key is already in the tree
     (with a possibly different associated value),
     then it should overwrite the value with the new one.
     We strongly recommend defining suitable (private) helper functions. */

     //insertToTree(new_item);
     
     if (this->root == NULL) {
      Node<KeyType, ValueType>* temp = new Node<KeyType, ValueType>(new_item.first, new_item.second, NULL);
      this->root = insertInTree(NULL, this->root, new_item, temp);
      static_cast<RedBlackNode<KeyType,ValueType>*>(this->root)->setColor(black);
     }
     else {
       Node<KeyType, ValueType>* temp = new Node<KeyType, ValueType>(new_item.first, new_item.second, NULL);
      this->root = insertInTree(NULL, this->root, new_item, temp);
      fixTree(temp);
      static_cast<RedBlackNode<KeyType,ValueType>*>(this->root)->setColor(black);
     }
     
     

  }
  Node<KeyType, ValueType>* copy;
  Node<KeyType, ValueType>* insertInTree(Node<KeyType, ValueType>* parent, Node<KeyType, ValueType>* node, const std::pair<const KeyType, ValueType> new_item, Node<KeyType, ValueType>*& check) {
    
    if(node == NULL) {
      
      node = check;
      copy = node;
      node->setParent(parent);
        static_cast<RedBlackNode<KeyType,ValueType>*>(node)->setColor(red);
        node->setRight(NULL);
        node->setLeft(NULL);
        //fixTree(star);
      
      return node;
    }   
    // go left
    if(new_item.first < node->getKey()) {
        node->setLeft(insertInTree(node, node->getLeft(), new_item, check));

    }
    else {
        //std::cout << new_item.first <<"   " << node->getKey() << std::endl;
        node->setRight(insertInTree(node, node->getRight(), new_item, check));

    }
  
    return node;
  }
  void fixTree(Node<KeyType, ValueType>* cool) {
      
      /*Node<KeyType, ValueType>* temp = cool;
      
          
          
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
          std::cout << cool->getKey() << std::endl;
          if ((cool->getParent()->getLeft() == cool) && (cool->getParent()->getParent()->getLeft() == cool ->getParent())) {
            std::cout << "stuff" << std::endl;
            if ((cool->getParent()->getParent()->getRight() == NULL) || (static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getRight())->getColor() == black)) {
              
              rotateRight(cool);

            }
            else {
              reColor(cool->getParent());
            }
          }

          else if ((cool->getParent()->getRight() == cool) && (cool->getParent()->getParent()->getRight() == cool ->getParent())) {
            //std::cout << "stfstuff" << std::endl;
            if (cool->getParent()->getParent()->getLeft() == NULL || static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getLeft())->getColor() == black) {
              rotateLeft(cool->getParent());
            }
            else{
              reColor(cool->getParent());
            }
          }
          else if ((cool->getParent()->getLeft() == cool) && (cool->getParent()->getParent()->getRight() == cool ->getParent())) {
            std::cout << "sfefetuff" << std::endl;
            if (cool->getParent()->getParent()->getRight() == NULL || static_cast<RedBlackNode<KeyType,ValueType>*>(cool->getParent()->getParent()->getRight())->getColor() == black) {
              rotateLeft(cool);
            }
            else{
              reColor(cool->getParent());
            }
          }
          else if ((cool->getParent()->getRight() == cool) && (cool->getParent()->getParent()->getLeft() == cool ->getParent())) {
            std::cout << "stiiiiiiif" << std::endl;
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
     // fixTree(cool->getParent());
    }

    //if (cool->getParent() != NULL) {
      //    fixTree(cool->getParent());
        //}
  }

  void reColor(Node<KeyType, ValueType>* cool) {
    std::cout << "color "<<cool->getKey() << std::endl;

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
std::cout << "right" << std::endl;
     
   // Node<KeyType, ValueType>* total_parent = cool->getParent()->getParent()->getParent();
    Node<KeyType, ValueType>* righttemp = cool->getParent()->getParent();
    Node<KeyType, ValueType>* newleft = cool->getParent();


    /*if (righttemp->getKey() == total_parent->getLeft()->getKey()) {

     total_parent->setLeft(newconnect);
      newconnect->setParent(total_parent);
      
      


      righttemp->setParent(newconnect);
      newconnect->setRight(righttemp);
      newconnect->setLeft(cool);
      cool->setParent(newconnect);

      //newleft->setParent(cool);
      //cool->setLeft(newleft);
      static_cast<RedBlackNode<KeyType,ValueType>*> (newconnect)->setColor(black);
      std::cout << "black " << newconnect->getKey() << std::endl;
      static_cast<RedBlackNode<KeyType,ValueType>*> (righttemp)->setColor(red);
      std::cout << "red " << righttemp->getKey() << std::endl;
      
      
      }
    else if (righttemp->getKey() == total_parent->getRight()->getKey()) {
      total_parent->setRight(newconnect);
      newconnect->setParent(total_parent);
      righttemp->setLeft(newconnect->getRight());
      


      righttemp->setParent(newconnect);
      newconnect->setRight(righttemp);
      newconnect->setLeft(cool);
      cool->setParent(newconnect);


      //newleft->setParent(cool);
      //cool->setLeft(newleft);
      static_cast<RedBlackNode<KeyType,ValueType>*> (newconnect)->setColor(black);
      std::cout << "black " << newconnect->getKey() << std::endl;
      static_cast<RedBlackNode<KeyType,ValueType>*> (righttemp)->setColor(red);
      std::cout << "red " << righttemp->getKey() << std::endl;
    }*/
    /*righttemp->setLeft(NULL);
      righttemp->setRight(NULL);
      cool->setRight(NULL);
      cool->setLeft(NULL);*/
   


      
      //righttemp->setLeft(newleft->getRight());
      if (newleft->getRight() != NULL) {
        righttemp->setLeft(newleft->getRight());
        newleft->getRight()->setParent(righttemp);
      }
      else{
        righttemp->setLeft(NULL);
      }
      newleft->setParent(righttemp->getParent());
      if (newleft->getParent() == NULL) {
        this->root = newleft;

      }
      else if(newleft == newleft->getParent()->getRight()) {
        righttemp ->getParent()->setRight(newleft);
      }
      else {
        righttemp ->getParent()->setLeft(newleft);
      }


   
    //std::cout<<" halp" <<cool->getKey() << "   " << cool->getParent()->getKey() << std:: endl;
    fixTree(cool->getParent());
  }

void rotateLeft(Node<KeyType, ValueType>* cool) {
  
    //Node<KeyType, ValueType>* total_parent = cool->getParent()->getParent();
    Node<KeyType, ValueType>* newleft = cool->getParent();
    Node<KeyType, ValueType>* righttemp = cool->getParent()->getParent();
/*
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
    }*/
/*
    Node<KeyType, ValueType>* total_parent = cool->getParent()->getParent()->getParent();
    Node<KeyType, ValueType>* righttemp = cool->getParent()->getParent();
    Node<KeyType, ValueType>* newconnect = cool->getParent();


    if (righttemp->getKey() == total_parent->getLeft()->getKey()) {

     total_parent->setLeft(newconnect);
      newconnect->setParent(total_parent);
      
      


      righttemp->setParent(newconnect);
      newconnect->setLeft(righttemp);
      newconnect->setRight(cool);
      cool->setParent(newconnect);

      //newleft->setParent(cool);
      //cool->setLeft(newleft);
      static_cast<RedBlackNode<KeyType,ValueType>*> (newconnect)->setColor(black);
      
    else if (righttemp->getKey() == total_parent->getRight()->getKey()) {
      total_parent->setRight(newconnect);
      newconnect->setParent(total_parent);
      righttemp->setLeft(newconnect->getRight());
      


      righttemp->setParent(newconnect);
      newconnect->setLeft(righttemp);
      newconnect->setRight(cool);
      cool->setParent(newconnect);


      //newleft->setParent(cool);
      //cool->setLeft(newleft);
      static_cast<RedBlackNode<KeyType,ValueType>*> (newconnect)->setColor(black);
      std::cout << "black " << newconnect->getKey() << std::endl;
      static_cast<RedBlackNode<KeyType,ValueType>*> (righttemp)->setColor(red);
      std::cout << "red " << righttemp->getKey() << std::endl;
    }*/
    /*righttemp->setLeft(NULL);
      righttemp->setRight(NULL);
      cool->setRight(NULL);
      cool->setLeft(NULL);*/
    //if (righttemp->getLeft() == NULL && righttemp->getRight() == NULL) {
      //std::cout << "fucking shit" << std::endl;
    //}
   //std::cout << "command "<<righttemp->getRight()->getKey() << "  " ;
   //std::cout<<"command " << righttemp->getRight()->getKey()<< std::endl;
        //fixTree(cool->getParent());
    

      righttemp->setRight(newleft->getLeft());
      //righttemp->setLeft(newleft->getRight());
      if (newleft->getLeft() != NULL) {
        newleft->getLeft()->setParent(righttemp);
      }
      newleft->setParent(righttemp->getParent());
      if (newleft->getParent() == NULL) {
        this->root = newleft;

      }
      else if(newleft == newleft->getParent()->getLeft()) {
        righttemp ->getParent()->setLeft(newleft);
      }
      else {
        righttemp ->getParent()->setRight(newleft);
      }

      //newleft = righttemp->getLeft();
      //righttemp = newleft->getParent();




    fixTree(cool->getParent());

    
  }


  
};

#endif
