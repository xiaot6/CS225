/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1

    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // if ()
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
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
  ListNode* tmp = NULL;
  ListNode* cur = head_;
  for(int i = 0; i < length_; i++) {
    tmp = cur->next;
    delete cur;
    cur = tmp;
  }
  head_ = NULL;
  tail_ = NULL;

  /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  // @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (length_ != 0) {
    head_->prev = newNode;
    newNode->next = head_;
    head_ = newNode;
    newNode->prev = NULL;
  }
  else {
    head_ = newNode;
    tail_ = newNode;
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
  // @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (length_ != 0) {
    tail_->next = newNode;
    newNode->prev = tail_;
    newNode -> next = NULL;
    tail_ = newNode;
  }
  else {
    head_ = newNode;
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
  if (splitPoint == 0) {
    return start;
  }
  if (splitPoint >length_) {
    return start;
  }
  for (int i = 0; i < splitPoint && curr!=NULL ; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
    curr->prev->next = NULL;
    curr->prev = NULL;

  }

  return curr;

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  if (head_ == NULL) {
    return;
  }
  /// @todo Graded in MP3.1
  ListNode * totail = NULL;
  ListNode * current = head_;
  while(current != tail_ && current != NULL && current->next != tail_  ) {
    totail = current->next;
    totail->next->prev = totail->prev;
    totail->prev->next = totail ->next;
    tail_->next = totail;
    totail->prev = tail_;
    totail->next = NULL;
    tail_ = totail;
    current = current->next;
  }
  return;

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
  if (startPoint== NULL || endPoint == NULL || startPoint== endPoint) {
    return;
  }
   ListNode *  after = endPoint ->next;
   ListNode * before = startPoint->prev;
   ListNode * tmp = startPoint->next;
   startPoint->next = endPoint->next;
   startPoint->prev = tmp;
   ListNode * current = startPoint;
   current = tmp;


   while (current != endPoint) {
     tmp = current->next;
     current->next = current->prev;
     current->prev = tmp;
     current = tmp;
   }

   endPoint->next = endPoint->prev;
   endPoint->prev = before;
   if(startPoint == head_ && endPoint ==tail_) {
     endPoint->prev = NULL;
     startPoint->next = NULL;
     head_ = endPoint;
     tail_ = startPoint;
   }
   else if(startPoint != head_ && endPoint ==tail_) {
     before->next = endPoint;
     startPoint->next = NULL;
     tail_ = startPoint;
   }
   else if(startPoint == head_ && endPoint !=tail_) {
     endPoint->prev = NULL;
     after->prev = startPoint;
     head_ = endPoint;
   }
   else if(startPoint != head_ && endPoint !=tail_) {
     after->prev = startPoint;
     before->next = endPoint;
   }





  /// @todo Graded in MP3.2
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
  int count = 0;
  ListNode * tmpend = head_;
  ListNode * tmpstart = head_;
  while(tmpstart != NULL) {
    while (count < n -1 &&tmpend != tail_) {
      tmpend = tmpend->next;
      count++;
    }
    count = 0;
    reverse(tmpstart,tmpend);
    tmpend = tmpstart->next;
    tmpstart = tmpend;

  }




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
  if (second == NULL) {
    return first;
  }
  if (first== NULL) {
    return second;
  }
  ListNode * firsttmp = first;
  ListNode * secondtmp = second;
  ListNode * toreturn;
  ListNode * tmp;
  if (second->data < first->data) {
    toreturn = second;
    tmp = secondtmp;
    secondtmp = secondtmp->next;
  } else {
  		toreturn = first;
      tmp = firsttmp;
  		firsttmp = firsttmp->next;
  }
  while(firsttmp != NULL && secondtmp!= NULL) {
     if (firsttmp->data  < secondtmp->data ) {
       tmp->next = firsttmp;
       firsttmp->prev = tmp;
       tmp = tmp->next;
       firsttmp = firsttmp->next;
     }
      else {
        tmp->next = secondtmp;
        secondtmp->prev = tmp;
        tmp = tmp->next;
        secondtmp = secondtmp->next;
     }
   }
  if (firsttmp != NULL && secondtmp == NULL) {
    tmp->next = firsttmp;
    firsttmp->prev = tmp;
    return toreturn;

  }
  if(firsttmp== NULL && secondtmp != NULL) {
    tmp->next = secondtmp;
    secondtmp->prev = tmp;
    return toreturn;
  }

    return toreturn;

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
  if (chainLength == 1 || chainLength == 0) {
    return start;
  }
  ListNode *secondhalf = split(start, chainLength /2);
  return merge(mergesort(start,chainLength /2), mergesort(secondhalf, chainLength-(chainLength /2)));

}
