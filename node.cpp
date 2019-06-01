#include <iostream>
#include <string.h>
#include "Node.h"

using namespace std;

Node::Node(){
  next = NULL;
  parent = NULL;
}

Node::~Node(){

}
  

// get next

Node* Node::getNext(){
  return next;
}

// get value

int Node::getValue(){
  return value;
}

//set next

void Node::setNext(Node* newNext){
  next = newNext;
}

// set value to the operator being passed in
void Node::setValue(int newvalue){
  value = newvalue;
}

Node* Node::getParent(){
  return parent;
}
void Node::setParent(Node* newParent){
  parent = newParent;
}
