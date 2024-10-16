#include<memory>
#include <string>
template <class T>

//template <class T>
class ListNode{
  public: T data;
  ListNode * next;

     // post: constructs a node with data 0 and null link
 public: ListNode();
 public: ListNode(T data); 
 public: ListNode(T idata, ListNode<T> * inext);
 public:std::string toString();
 public: T getData();
 

};
