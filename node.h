#include <iostream>
#ifndef NODE_H
#define NODE_H

//Class Definition for Node class

class Node{
 public:
  Node();
  ~Node();
  Node* getNext();
  void setNext(Node* newNext);
  void setValue(int newvalue);
  int getValue();
  Node* getParent();
  void setParent(Node* newParent);
 private:
  Node* next;
  Node* parent;
  int value;
};
#endif
