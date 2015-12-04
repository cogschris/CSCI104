#ifndef HASH_H
#define HASH_H
#include <vector>
#include <string>


class HashTable {
     public:
       HashTable ();
       /* Constructor that builds a hash table with 31 indices. */

       ~HashTable ();

       void add (std::pair<std::string, int> new_item);
         /* adds new_item to the hashtable.  
            Conflicts should be resolved via chaining.
            You may use the STL list to accomplish this. 
            Throws an exception if the key is already 
            in the hashtable.*/

       const int& find(std::string key) const;
         /* returns the value with the associated key. 
            Throws an exception if the key is not in the
            hashtable. */

       void remove (std::string key);
         /* removes the element with the associated key. 
            Throws an exception if the key is not in the
            hashtable. */

       void update (std::pair<std::string, int> new_value);
         /* finds the item with the associated key, 
            and updates its value accordingly. 
            Throws an exception if the key is not in the
            hashtable. */
        void resize();

   private:
      // whatever you need to naturally store things.
      // You may also add helper functions here, 
      // including your hash function and resize function.
    std::vector< std::pair<std::string, int> >  **table;
    int size;
    int count;
    int orig;
  };

#endif