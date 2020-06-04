/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
 #include <stack>

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    this->length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(this->head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1

  while (head_ != NULL) {
    ListNode * temp = head_;
    head_ = head_->next;
    delete temp;
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1


  ListNode * newNode = new ListNode(ndata);


  if (head_ == NULL) {
    newNode -> prev = NULL;
    newNode -> next = NULL;
    head_ = newNode;
    tail_ = newNode;

  } else if (head_ != NULL) {
    newNode -> next = head_;
    newNode -> prev = NULL;
    head_ -> prev = newNode;
    head_ = newNode;
  }
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  if (tail_ == NULL) {
    newNode -> next = NULL;
    newNode -> prev = NULL;
    tail_ = newNode;
    head_ = newNode;
  } else if (tail_ != NULL) {
    newNode -> prev = tail_;
    newNode -> next = NULL;
    tail_ -> next = newNode;
    tail_ = newNode;
  }

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  // ListNode * head2 = NULL;

  // ListNode * toReturn;
  // if (splitPoint > this->length_) {
  //   return List<T>();
  // }
  // if (splitPoint == 0) {
  //   return NULL;
  // }

  for (int i = 0; i < splitPoint && curr; i++) {
    // if (curr == NULL) {
    //     break;
    // }
    curr = curr->next;
  }
  if (curr != NULL) {
    if (curr->prev != NULL){
      curr->prev->next = NULL;
      curr->prev = NULL;
    }
  }

  // head2 = curr;
  // head2->prev = NULL;
  //
  // if (curr != NULL) {
  //   curr->next = NULL;
  // }
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three
  * elements in the list starting for the first three elements. If the
  * end of the list has a set of 1 or 2 elements, no rotation all be done
  * on the last 1 or 2 elements.
  *
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1

  ListNode *curr = head_;
  int count = 0;
  while (curr && curr->next != NULL && curr->next->next != NULL) {

      ListNode * nextCurr = curr->next->next->next;
      ListNode * temp = curr; //1
      curr = curr->next;
      ListNode *temp2 = curr; // 2
      curr = curr->next; //3
      temp->next = curr-> next;
      curr->next = temp; // 3-1
      // temp2->next = curr; // 2-3
      temp2->prev = temp->prev; // 2 - prev(1)
      if (temp->prev) temp->prev->next = temp2;
      temp->prev = curr; // 3-1
      if (nextCurr) nextCurr->prev = temp;

      curr = nextCurr;
      // cout << temp2->data << " " << temp2->prev->data << " " << endl;
      if (count == 0) {
        head_ = temp2;
      }
      if (length_ % 3 == 0 && (length_ / 3 == count + 1)) {
        // std::cout << "tail" << std::endl;
        tail_ = temp;
      }
      count++;
  }


}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == endPoint) {
    return;
  }
  // if (startPoint == NULL || endPoint ==  NULL) {
  //   return;
  // }

  ListNode *temp = NULL; // temp holder pointer
  ListNode* current = startPoint;
  ListNode* beginning = current->prev;
  ListNode* end = endPoint->next;
  while (current != endPoint) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }
  // temp = current->prev;
  // current->prev = current->next;
  // current->next = temp;
  current->next = current->prev;
  current->prev = beginning;
  startPoint->next = end;
  if (beginning != NULL) {
    beginning->next = endPoint;
  } else {
    head_ = endPoint;
  }

  if (end != NULL) {
    end->prev = startPoint;
  } else {
    tail_ = startPoint;
  }
  temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;

  // endPoint = startPoint;
  // endPoint->next = beginning;
  // tail_ = endPoint;
  // startPoint = current;
  // startPoint->next = temp;
  // startPoint->prev = current->prev;
  // head_ = startPoint;


}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (head_ == NULL || n <= 1) {
    return;
  }
  if (n > length_) {
    reverse();
    return;
  }

  ListNode* revUntil = head_; //endpoint for reversal chunk
  ListNode* start = head_; // start of reversal chunk

  while (start != NULL) {
    revUntil = start;
    for(int i = 0; i < n - 1; i++) {
      if (revUntil->next != NULL) {
        revUntil = revUntil->next;
      } else {
        break;
      }
    }
    reverse(start, revUntil);
    if (revUntil->next != NULL) {
      start = revUntil->next;
    } else {
      break;
    }
  }

  // while (revUntil != NULL) {
  //   revUntil = start;
  //   int count = 1;
  //   while (count < n) {
  //     if (revUntil == NULL) {
  //       break;
  //     }
  //     revUntil = revUntil->next;
  //     count++;
  //   }
  //   if (revUntil ==  NULL) {
  //     break;
  //   }
  //   reverse(start, revUntil);
  //   cout << "reversed" << endl;
  //   if (revUntil->next != NULL) {
  //     start = revUntil->next;
  //   } else {
  //     break;
  //   }
  // }


}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }
  ListNode *c1 = first;
  ListNode *c2 = second;
  //ListNode *temp;
  ListNode *beginning;

  //determine which node will be the head
  if (c1->data < c2->data) {
    beginning = first;
    c1 = c1->next;
  } else if (c2->data < c1->data) {
    beginning = second;
    c2 = c2->next;
  } else {
    beginning = first;
    c1 = c1->next;
  }
  ListNode* current = beginning; //head of new list

  //create list starting with head
  while (c1 != NULL && c2!= NULL) {
    if (c2->data < c1->data) {
      current->next = c2;
      c2->prev = current;
      c2 = c2->next;
    } else {
      current->next = c1;
      c1->prev = current;
      c1 = c1->next;
    }
    current = current->next;
  }
  if (c2 != NULL && c1 == NULL) {
    current->next = c2;
    c2->prev = current;
  } else if (c1 != NULL && c2 == NULL) {
    current->next = c1;
    c1->prev = current;
  }


  // while (c1 != NULL) {
  //   while (c2 != NULL) {
  //     if (c2->data < c1->data) {
  //       temp = c1->prev;
  //       c1->prev = c2;
  //       temp->next = c2;
  //       c2->next = c1;
  //       c2->prev = temp;
  //     }
  //     c2 = c2->next;
  //   }
  //   c1 = c1->next;
  // }


  return beginning;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start->next == NULL) {
    return start;
  }
  // use split helper function to create second list
  ListNode* seq2 =  split(start, chainLength/2);
  //recursive call, merge two lists after splitting and sorting
  return merge(mergesort(start, chainLength/2), mergesort(seq2, (chainLength % 2) + (chainLength/2)));



}
