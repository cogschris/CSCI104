#ifndef ALISTINT_H
#define ALISTINT_H

class AListInt
{
 public:
  /**
   * Default constructor - default to a list of capacity = 5
   */
  AListInt();

  /**
   * Another constructor - default to a list to the indicated capacity
   */
  AListInt(int cap);

  /**
   * Copy constructor 
   */
  AListInt(const AListInt& other);

  /**
   * Assignment operator
   */
  AListInt& operator=(const AListInt& other);

  /**
   * Destructor
   */
  ~AListInt();
  
  /**
   * Standard List interface
   */

  /**
   * Returns the current number of items in the list 
   */
  int size() const;
  
  /**
   * Returns true if the list is empty, false otherwise
   */
  bool empty() const;

  /**
   * Inserts val so it appears at index, pos
   */
  void insert (int pos, const int& val);

  /**
   * Removes the value at index, pos
   */
  void remove (int pos);

  /**
   * Overwrites the old value at index, pos, with val
   */
  void set (int position, const int& val);

  /**
   * Returns the value at index, pos
   */
  int& get (int position) ;

  /**
   * Returns the value at index, pos
   */
  int const & get (int position) const;

  /**
   * Produce a new list by concatenating this list and the input list
   *   If this list = [1, 2, 3] and other = [4, 5, 6] then return 
   *   a new list with contents [1, 2, 3, 4, 5, 6].  The capacity
   *   of the new list should be equal to its size (i.e. the new list
   *   would be full upon being returned)
   */
  AListInt operator+(const AListInt& other) const;
  
  /**
   * Operator[] to access the element at the given position
   */
  int const & operator[](int position) const;

  /**
   * Non-const version
   */
  int& operator[](int position);


 private:
  /**
   * Should double the size of the list maintaining its contents
   */
  void resize(); 
   
  /* Add necessary data members here */
  int* _data;
  unsigned int _size;
  unsigned int _cap;
  
};

#endif
