#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val)
{
  if(tail_ == nullptr) {
    tail_ = new Item();
    head_ = tail_;
    tail_->val[0] = val;
    tail_->first = 0;
    tail_->last = 1;
    size_++;
    return;
  }

  if(tail_->last < ARRSIZE) {
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
    return;
  }

  Item* newNode = new Item();
  newNode->val[0] = val;
  newNode->first = 0;
  newNode->last = 1;

  newNode->prev = tail_;
  tail_->next = newNode;
  tail_ = newNode;

  size_++;
}

void ULListStr::push_front(const std::string& val)
{
  if(head_ == nullptr) {
    head_ = new Item();
    tail_ = head_;
    head_->val[0] = val;
    head_->first = 0;
    head_->last = 1;
    size_++;
    return;
  }

  if(head_->first > 0) {
    head_->first--;
    head_->val[head_->first] = val;
    size_++;
    return;
  }

  Item* newNode = new Item();
  newNode->last = ARRSIZE;
  newNode->first = ARRSIZE - 1;
  newNode->val[newNode->first] = val;

  newNode->next = head_;
  head_->prev = newNode;
  head_ = newNode;

  size_++;
}

void ULListStr::pop_back()
{
  if(tail_ == NULL) return;

  tail_->last--;
  size_--;

  if(tail_->first == tail_->last) {
    Item* temp = tail_;
    tail_ = tail_->prev;
    if(tail_ != NULL) tail_->next = NULL;
    else head_ = NULL;
    delete temp;
  }
}

void ULListStr::pop_front()
{
  if(head_ == NULL) return;

  head_->first++;
  size_--;

  if(head_->first == head_->last) {
    Item* temp = head_;
    head_ = head_->next;
    if(head_ != NULL) head_->prev = NULL;
    else tail_ = NULL;
    delete temp;
  }
}

std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if(loc >= size_) return NULL;

  Item* curr = head_;
  size_t count = 0;

  while(curr != NULL) {
    size_t used = curr->last - curr->first;
    if(loc < count + used) {
      return &curr->val[curr->first + (loc - count)];
    }
    count += used;
    curr = curr->next;
  }

  return NULL;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
