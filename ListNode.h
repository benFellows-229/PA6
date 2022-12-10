/*
Ben Fellows
002369768
bfellows@chapman.edu
CPSC-350-02
CPSC350 PA6
Listnode.h
A templated class containing the listnode implementation from class. I have overloaded the < and > operators to compare the weights of the edges.
*/

#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <cstdlib>
#include <iostream>
using namespace std;


template <typename T>
class ListNode{
public:
  ListNode(T data);
  virtual ~ListNode();
  template <typename S>
  friend class DblList;
  template <typename S>
  friend class PQueue;
  friend bool operator < (const ListNode<T>& lhs, const ListNode<T>& rhs){
    return lhs.m_data < rhs.m_data;
  }
  friend bool operator > (const ListNode<T>& lhs, const ListNode<T>& rhs){
    return lhs.m_data > rhs.m_data;
  }
private:
  T m_data;
  ListNode<T>* m_next;
  ListNode<T>* m_prev;
};

template <typename T>
ListNode<T>::ListNode(T data){
  m_data = data;
  m_next = NULL;
  m_prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode(){
  m_next = NULL;
  m_prev = NULL;
}

#endif
