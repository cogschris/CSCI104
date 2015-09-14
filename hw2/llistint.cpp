#include "llistint.h"
#include <cstdlib>
#include <stdexcept>

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& vals)
{
  // as long as the size is A okay
  if (loc >= 0 && loc <= size_) {
    
    //if this is the first of the list, set that value equal to head and tail
    if (size_ == 0) {
      Item *value = new Item;
      value -> val = vals;
      
      head_ = value;
      tail_ = value;
      size_++;
    }

    //adding to the beginning of the list changes just head
    else if (loc == 0) {
      Item *value = new Item;
      value -> val = vals;
      Item *temp = head_;
      value -> next = temp;
      head_ = value;
      size_++;
    }

    //adding to the end of the list changes just tail
    else if (loc == size_){
      Item *value = new Item;
      value -> val = vals;
      Item *temp = tail_;
      temp -> next = value;
      tail_ = value;
      size_++;
    }

    //everything else just changes the next and previous pointers
    else if (loc <= size_) {
      Item *ins = head_;
      //ins = head_;
      for (int i = 0; i < loc; i++) {
        ins = ins -> next;
      }

      if (ins-> next != NULL) {
        Item *temp = ins -> prev;
        Item *value = new Item;
        value -> val = vals;
        ins -> prev = value;
        value -> next = ins;
        temp -> next = value;
        value -> prev = temp;
        size_++;
      }

     
      }
    }

}

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{
  //is it a good size?
  if (loc < size_ ) {
    
    //deleting from front moves head forward
    if (loc == 0) {
      Item *temp = head_ -> next;
      delete head_;
      head_ = temp;
      size_--;
    }
    
    //deleting from back changes tail
    else if (loc == size_){
      Item *del = head_;
    for (int i = 0; i < loc; i++) {
      del = del -> next;
    }
      tail_ = del -> prev;
      delete del;
      size_--;
    }

    //everthing else just means changing next and prev
    else {
      Item *del = head_;
    for (int i = 0; i < loc; i++) {
      del = del -> next;
    }
      Item *tempa = del -> next;
      Item *tempb = del -> prev;
      delete del;
      tempa -> prev = tempb;
      tempb -> next = tempa;
      size_--;
    }
  }

}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


/**
 * Complete the following function
 */
LListInt::Item* LListInt::getNodeAt(int loc) const
{
  //follow good size
  if (loc >= 0 && loc <= size_) {
    Item *check = head_;
    //use for loop to search through to find the right one
    for (int i = 0; i < loc; i++) {
      check = check -> next;
    }
    //return the value
    return check;
  }

}
