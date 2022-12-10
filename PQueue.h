/*
Ben Fellows
002369768
bfellows@chapman.edu
CPSC-350-02
CPSC350 PA6
PQueue.h
A templated class containing the priority queue implementation from class. I have overloaded the < and > operators to compare the weights of the edges.
*/

#ifndef PQ_H
#define PQ_H

#include "WGraph.h"
#include "DblList.h"
#include <iostream>
using namespace std;

template <typename T>
class PQueue: private DblList<T>{
public:
  PQueue(bool isMin); //min queue or not
  virtual ~PQueue();
  void add(T data); //enforces min/max behavior
  T remove(); //always returns min/max
  int getSize();
  bool isEmpty();
  void print();
  T pop();
  void addEdge(T data);


private:
  bool m_isMinQ;
};

template <typename T>
PQueue<T>::PQueue(bool isMin){
  m_isMinQ = isMin;
}

template <typename T>
PQueue<T>::~PQueue(){
}

template <typename T>
int PQueue<T>::getSize(){
  return DblList<T>::getSize();
}

template <typename T>
bool PQueue<T>::isEmpty(){
  return DblList<T>::isEmpty();
}

template <typename T>
T PQueue<T>::remove(){
  if(m_isMinQ){
    return DblList<T>::removeFront(); //smallest always at front
  } else{
    return DblList<T>::removeBack(); //smallest always at front
  }
}

template <typename T>
void PQueue<T>::add(T data){
  if(isEmpty()){ //just add it
    DblList<T>::addFront(data);
    return;
  }
  //find the right place and then add it
  ListNode<T>* newNode = new ListNode<T>(data);
  int currIdx = 0;
  ListNode<T>* currNode = DblList<T>::m_front;
  while(currNode!=NULL && currNode->m_data < data){
    currNode = currNode->m_next;
    ++currIdx;
  }

  DblList<T>::add(currIdx,data); //lazy hack - do better


}

template <typename T>
void PQueue<T>::print(){
  DblList<T>::print();
}

//pop method to remove and return first element
template <typename T>
T PQueue<T>::pop(){
  if(m_isMinQ){
    return DblList<T>::removeFront();
  } else{
    return DblList<T>::removeBack();
  }
}

#endif
