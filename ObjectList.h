///
/// A list of Objects
///

#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

#define MAX_OBJECTS 5000

#include "Object.h"
#include "ObjectListIterator.h"

class Object;
class ObjectListIterator;

class ObjectList {

 private:
  int count;                  ///< Count of objects in list.
  int max_count;              ///< Maximum objects in list (variable).
  Object *list[MAX_OBJECTS];            ///< Array of pointers to objects.

 public:
  friend class ObjectListIterator;           ///< Iterators can access.
  ObjectListIterator createIterator() const; ///< Create an iterator.

  ObjectList();
  ~ObjectList();


  /// Insert object pointer in list.
  /// Return 0 if ok, else -1.
  int insert(Object *p_o);

  /// Remove  object pointer from list,
  /// Return 0 if found, else -1.
  int remove(Object *p_o);

  /// Clear the list (setting count to 0).
  void clear();

  /// Return count of number of objects in list.
  int getCount(void);

  /// Return true if list is empty, else false.
  bool isEmpty();

  /// Return true if list is full, else false.
  bool isFull();


};

#endif // __OBJECT_LIST_H__
