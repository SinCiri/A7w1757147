#include "Queue.h"
//template <class T>
//Queue<T>::Queue(){
//  back=nullptr;
//}

template <class T>
//TODO
// add an element t to the end queue 
// this should be an O(1) operation
void Queue<T>::add(T  t){
  ListNode<T>* tempNode = new ListNode<T>(t);
  //if list is empty, the front is the new node
  if (this->front == nullptr) {
    this->front = tempNode;
    this->back = tempNode;
    return; 
  }
  else {
    //otherwise add it to the end.
    this->back->next = tempNode;
    this->back = tempNode;
  } 
}
//TODO
//remove an element from the front of the queue
// this should be an O(1) operation
template <class T>
void Queue<T>::remove(){
  
  // if queue is empty
  if(this->empty()) {
    throw new std::string("NULL POINTER EXCEPTION QUEUE IS EMPTY \n");
  }
  else {
    ListNode<T>* temp = this->front();
    this->front = this->front->next;
    delete temp;
  }
  
}
template <class T>
void Queue<T>::remove(std::string s) {
  if(this->empty()) {
    throw std::string("NULL POINTER EXCEPTION QUEUE IS EMPTY \n");
  }
  else {
    ListNode<T>* currNode = this->front();
    ListNode<T>* prev = nullptr;
    while(currNode) {
      //if data is matching remove the data
      if (currNode->data.getTitle() == s) {
        //if we are at the start
        if (prev == nullptr) {
          //remove the first element
          remove();
        }
        //if we are in the middle of the list
        else {
          //remove the current node we are on
          ListNode<T>* temp = currNode;
          prev->next = currNode->next;
          delete temp;
        }
        //move to next nodes
        prev = currNode;
        currNode = currNode->next;
      }
      else {
        //move to next nodes nothing matches
        prev = currNode;
        currNode = currNode->next;
      }
    }
  }
}
