#include "LinkedIntList.h"

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
    Node* newnode = new Node;
    newnode->payload = payload;
    
    if (num_elements_ == 0) {
        // degenerated case: the list is now empty
        newnode->prev = nullptr;
        newnode->next = nullptr;
        head_ = newnode;
        tail_ = newnode;
        num_elements_ = 1;
    } else {
        // general case: the list is not empty
        newnode->prev = nullptr;
        head_->prev = newnode;
        newnode->next = head_;
        head_ = newnode;
        num_elements_ += 1;
    }
}

void LinkedIntList::Append(const int payload) {
    Node* newnode = new Node;
    newnode->payload = payload;

    if (num_elements_ == 0) {
        // degenerated case: the list is now empty
        newnode->prev = nullptr;
        newnode->next = nullptr;
        head_ = newnode;
        tail_ = newnode;
        num_elements_ = 1;
    } else {
        // general case: the list is not empty
        newnode->prev = tail_;
        tail_->next = newnode;
        newnode->next = nullptr;
        tail_ = newnode;
        num_elements_ += 1;
    }
}

bool LinkedIntList::Pop(int* const payload_ptr) {
    if (num_elements_ == 0) {
        return false;
    }
    
    Node* node = head_;
    if (num_elements_ == 1) {
        head_ = nullptr;
        tail_ = nullptr;
        *payload_ptr = node->payload;
    } else {
        head_ = node->next;
        head_->prev = nullptr;
        *payload_ptr = node->payload;
    }
    num_elements_ -= 1;
    return true;
}

bool LinkedIntList::Slice(int* const payload_ptr) {
    if (num_elements_ == 0) {
        return false;
    }

    Node* node = tail_;
    if (num_elements_ == 1) {
        head_ = nullptr;
        tail_ = nullptr;
        *payload_ptr = node->payload;
    } else {
        tail_ = node->prev;
        tail_->next = nullptr;
        *payload_ptr = node->payload;
    }
    num_elements_ -= 1;
    return true;
}

}   // namespace intlist333
