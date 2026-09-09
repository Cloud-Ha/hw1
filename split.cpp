/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */

void append(Node*& head, Node* node);// Declare the function to append the list

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
// WRITE YOUR CODE HERE
  // Base case: empty list
  if(in == nullptr) {
      return;
  }

  Node* curr = in;
  in = in->next;     // detach first nodefrom input list
  curr->next = nullptr;

  // Place curr into odds or evens
  if(curr->value % 2 == 0) {
      append(evens, curr);
  }
  else {
      append(odds, curr);
  }

  // Iterate on the rest
  split(in, odds, evens);
}

/* If you needed a helper function, write it here */
void append(Node*& head, Node* node)
{
    if(head == nullptr) {
        head = node;
        return;
    }
    append(head->next, node);
}
