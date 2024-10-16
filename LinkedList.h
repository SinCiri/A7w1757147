#include "ListNodecpp.h"

template <class T>
class LinkedList{

protected: ListNode<T> * front;
protected: ListNode<T> * back;
int count;

public: LinkedList<T>();
public: bool empty();

public: int size();
public: void add( T  t);
public: void remove(T t);
public: void move(T t, int pos);
public: void insert(T t, int pos);
public: void insert(T t);
public : int get(T t);

public: std::string toString();
public: void  printList();
public: void print(int number);
public: bool operator==(T other);
public: void printSong(int number);
public :void adjustInsert(ListNode<T> *t, int increment);
public: struct Iterator{
  ListNode<T> * cur; //  a pointer to the current ListNode
  Iterator(); // constructs the Iterator object
  Iterator(ListNode<T> * t); // custom constructor
  ListNode<T> * next();// gets a pointer to the next ListNode in the q
  ListNode<T> * getCur(); // returns cur
  bool operator==(Iterator iter);// used to compare  the current object with the iterator, used to detect the end 
  void operator++();// increment iterator to move to next ListNode
  ListNode<T> *operator*();// dereference to get the value of the ListNode being pointed to by iterator object

};


Iterator begin();
Iterator end();

};