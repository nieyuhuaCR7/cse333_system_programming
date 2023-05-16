// Copyright [2023] <Yuhua Nie, Yanxiao Sun> [legal/copyright]
// nieyuhua@uw.edu, ysun01@uw.edu
#include "LinkedIntList.h"
#include <iostream>

namespace intlist333 {
// default constructor
LinkedIntList::LinkedIntList() {
    num_elements_ = 0;
    // head_ = nullptr;
    // tail_ = nullptr;
}

// intentionally not writing destructor

int LinkedIntList::num_elements() const {
    return num_elements_;
}

void LinkedIntList::Push(const int payload) {
    std::shared_ptr<Node> newnode = std::make_shared<Node>();
    newnode->payload = payload;

    if (num_elements_ == 0) {
        // degenerated case: the list is now empty
        newnode->prev.reset();
        newnode->next.reset();
        head_ = newnode;
        tail_ = head_;
        num_elements_ = 1;
    } else {
        // general case: the list is not empty
        newnode->prev.reset();
        newnode->next = head_;;
        newnode->next->prev = newnode;
        head_ = newnode;
        num_elements_ += 1;
    }
}

void LinkedIntList::Append(const int payload) {
    std::shared_ptr<Node> newnode = std::make_shared<Node>();
    newnode->payload = payload;

    if (num_elements_ == 0) {
        // degenerated case: the list is now empty
        newnode->prev.reset();
        newnode->next.reset();
        head_ = newnode;
        tail_ = head_;
        num_elements_ = 1;
    } else {
        // general case: the list is not empty
        newnode->prev = tail_.lock();
        tail_.lock()->next = newnode;
        newnode->next.reset();
        tail_ = newnode;
        num_elements_ += 1;
    }
}

bool LinkedIntList::Pop(int* const payload_ptr) {
    if (num_elements_ == 0) {
        return false;
    }
    int result = head_->payload;
    *payload_ptr = result;
    std::shared_ptr<Node> node = head_;
    if (num_elements_ == 1) {
        // std::cout << result << std::endl;
        head_.reset();
        tail_.reset();
        // std::cout << result << std::endl;
        // // int result = head_->payload;
        // *payload_ptr = node->payload;
    } else {
        head_ = node->next;
        head_->prev.reset();
    }
    num_elements_ -= 1;
    return true;
}

bool LinkedIntList::Slice(int* const payload_ptr) {
    if (num_elements_ == 0) {
        return false;
    }

    std::shared_ptr<Node> tailShared = tail_.lock();
    *payload_ptr = tailShared->payload;

    if (num_elements_ == 1) {
        head_.reset();
        tail_.reset();
    } else {
        tail_ = tailShared->prev;
        tailShared->prev.lock()->next.reset();
    }
    num_elements_ -= 1;
    return true;
}

}   // namespace intlist333
