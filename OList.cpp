#include <iostream>
#include <utility>
#include "Node.h"
#include "OList.h"

OList::OList() {
  head = nullptr;
}

// insert at the "front" (head)
void OList::insert(std::string data) {
  Node *tmp = new Node(std::move(data));
  tmp->setNext(head);
  head = tmp;
}

/*
  insert at loc
  We need a pointer to the node BEFORE
  the location where we want to insert 

  Piggybacking 
 */
void OList::insert(int loc, std::string data) {
  Node *walker, *trailer;
  walker = this->head; // start of the list
  trailer = nullptr; // one behind

  while (loc > 0 && walker != nullptr) {
    loc = loc - 1;

    /* trailer will always be one node
       behind walker */
    trailer = walker;
    walker = walker->getNext();

  }

  // At this point, trailer points to the Node
  // BEFORE where we want to insert


  // test to see if we're trying to
  // insert past the end 
  if (loc > 0) {
    // do something to indicate this is invalid
    throw std::out_of_range("Our insert is out of range");
  }

  Node *newNode = new Node(std::move(data));
  // Inserting at true location 0
  // will have trailer == nullptr
  // - we have to treat that as a special case
  if (trailer == nullptr) {
    newNode->setNext(head);
    head = newNode;
  } else {
    // do the regular case 
    newNode->setNext(walker);
    trailer->setNext(newNode);
  }
}

/*
  Alternate solution:
    make a private variable to store the length
    and just return it here.

    Change all the insert/delete/remove type
    routines to upate that variable 
 */
int OList::length() {
  int count = 0;
  Node *walker = head;
  while (walker != nullptr) {
    count++;
    walker = walker->getNext();
  }
  return count;
}

std::string OList::toString() {
  Node *tmp = this->head;
  std::string result;
  while (tmp != nullptr) {
    result += tmp->getData();
    result += "-->";
    tmp = tmp->getNext();
  }
  result = result + "nullptr";
  return result;
}

bool OList::contains(const std::string &item) {
  Node *tmp = this->head;
  while (tmp != nullptr) {
    if (tmp->getData() == item) {
      return true;
    }
    tmp = tmp->getNext();
  }
  return false;
}

void OList::remove(int loc) {
  if (loc >= this->length()) {
    throw std::out_of_range("Our remove is out of range");
  }
  if (loc == 0) {
    Node *newFirst = this->head->getNext();
    delete this->head;
    this->head = newFirst;
  }
  Node *tmp = this->head;
  int i = 0;
  while (tmp != nullptr) {
    if (i + 1 == loc) {
      Node *nodeAfterRemoved = tmp->getNext()->getNext();
      delete tmp->getNext();
      tmp->setNext(nodeAfterRemoved);
      return;
    }
    tmp = tmp->getNext();
    i++;
  }
}

OList::~OList() {
  Node *walker, *trailer;
  walker = this->head; // start of the list
  trailer = nullptr; // one behind
  while (walker != nullptr) {
    delete trailer;
    trailer = walker;
    walker = walker->getNext();
  }
}

std::string OList::get(int loc) {
  if (loc >= this->length()) {
    throw std::invalid_argument("Out of bounds");
  }
  Node *tmp = this->head;
  for (int i = 0; i < loc; i++) {
    tmp = tmp->getNext();
  }
  return tmp->getData();
}

Node *OList::getPointer(int loc) {
  // cannot check length() because results in infinite loop in reverse due to next pointers not updated
//  if (loc >= this->length()) {
//    throw std::invalid_argument("Out of bounds");
//  }
  Node *tmp = this->head;
//  if (loc == 0) {
//    return tmp;
//  }

  for (int i = 0; i < loc; i++) {
    tmp = tmp->getNext();
  }
  return tmp;
}

void OList::reverse() {
  // handle empty list
  if (head == nullptr) {
    return;
  }
  int len = length();
  Node *end = getPointer(len - 1);

  for (int i = len - 1; i > 0; i--) {
//    std::cout << "started " << i << "\n";
    auto curr = getPointer(i);
    auto next = getPointer(i - 1);
    curr->setNext(next);
//    std::cout << "curr: '" << curr->getData() << "' next set to: '" << curr->getNext()->getData() << "'\n";
//    std::cout << "finished " << i << "\n";
  }

  head->setNext(nullptr);
  head = end;
}
