// Copyright [2023] <Yuhua Nie, Yanxiao Sun> [legal/copyright]
// nieyuhua@uw.edu, ysun01@uw.edu
#ifndef LINKEDINTLIST_H_
#define LINKEDINTLIST_H_

#include <memory>
#include "IntList.h"

namespace intlist333 {

// LinkedIntList is an implementation of
// the IntList abstract class. Implemented using
// a doubly linked list
class LinkedIntList : public IntList {
 public:
  // Destructor should be kept default
  // since smart pointers should clean
  // everything up for us

  // default constructor
  LinkedIntList();
  // destuctor
  virtual ~LinkedIntList() = default;

  int num_elements() const override;
  void Push(const int payload) override;
  void Append(const int payload) override;
  bool Pop(int* const payload_ptr) override;
  bool Slice(int* const payload_ptr) override;


 private:
  int num_elements_;
  // Note that these should be modified
  // to use smart pointers at some point
  struct Node {
    int payload;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
  };
  std::shared_ptr<Node> head_;
  std::weak_ptr<Node> tail_;
};

}  // namespace intlist333

#endif  // LINKEDINTLIST_H_
