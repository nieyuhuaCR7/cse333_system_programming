#include "LinkedIntList.h"
#include <iostream>

namespace intlist333 {
// default constructor
LinkedIntList::LinkedIntList() {
    num_elements_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
}

// intentionally not writing destructor

int LinkedIntList::num_elements() const {
    return num_elements_;
}

void LinkedIntList::Push(const int payload) {
    std::unique_ptr<Node> newnode = std::make_unique<Node>();
    newnode->payload = payload;
    
    if (num_elements_ == 0) {
        // degenerated case: the list is now empty
        newnode->prev = nullptr;
        newnode->next = nullptr;
        head_ = std::move(newnode);
        tail_ = head_.get();
        num_elements_ = 1;
    } else {
        // general case: the list is not empty
        newnode->prev = nullptr;
        newnode->next = std::move(head_);
        newnode->next->prev = newnode.get();
        head_ = std::move(newnode);
        num_elements_ += 1;
    }
}

void LinkedIntList::Append(const int payload) {
    std::unique_ptr<Node> newnode = std::make_unique<Node>();
    newnode->payload = payload;

    if (num_elements_ == 0) {
        // degenerated case: the list is now empty
        newnode->prev = nullptr;
        newnode->next = nullptr;
        head_ = std::move(newnode);
        tail_ = head_.get();
        num_elements_ = 1;
    } else {
        // general case: the list is not empty
        newnode->prev = tail_;
        tail_->next = std::move(newnode);
        newnode->next = nullptr;
        tail_ = tail_->next.get();
        num_elements_ += 1;
    }
}

bool LinkedIntList::Pop(int* const payload_ptr) {
    if (num_elements_ == 0) {
        return false;
    }
    
    int result = head_->payload;
    // *payload_ptr = result;
    
    Node* node = head_.get();
    
    std::cout << result << std::endl;
    // const int result1 = head_->payload; 
    // std::unique_ptr<Node> node = std::make_unique<Node>();
    // node = std::move(head_);
    if (num_elements_ == 1) {
        std::cout << result << std::endl;
        head_ = nullptr;
        tail_ = nullptr;
        std::cout << result << std::endl;
        // int result = head_->payload;
        *payload_ptr = node->payload;
    } else {
        head_ = std::move(node->next);
        head_->prev = nullptr;
        // int result = head_->payload;
        *payload_ptr = node->payload;        
    }
    
    num_elements_ -= 1;
    return true;
}

bool LinkedIntList::Slice(int* const payload_ptr) {
    if (num_elements_ == 0) {
        return false;
    }

    *payload_ptr = tail_->payload;
    if (num_elements_ == 1) {
        head_ = nullptr;
        tail_ = nullptr;
    } else {
        tail_ = tail_->prev;
        tail_->next = nullptr;
    }
    num_elements_ -= 1;
    return true;
}

}   // namespace intlist333
