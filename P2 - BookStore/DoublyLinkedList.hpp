#ifndef MY_DOUBLY_LINKED_LIST_HPP
#define MY_DOUBLY_LINKED_LIST_HPP


/**
 * TODO: Implement DoublyLinkedList, its Node, and its Iterator!
 * 
 * I've left some methods filled out for you,
 * 	and stubbed out some structure, to reduce difficulty.
 * 
 * You may add or remove methods as you see fit,
 * 	as long as you can still pass all unit tests.
 * Although, it may be more difficult to do so. Your choice!
 * 
 * Notice we're inside a namespace here.
 * The DLL is inside a namespace called DoublyLinkedList,
 * 	which is itself inside a namespace called CPSC131
 * This means, if you'd like to play around with your class later,
 * 	you'll need to access it like so:
 * ::CPSC131::DoublyLinkedList::DoublyLinkedList<int> list;
 * 
 * Look into main.cpp and CPP_Tests.cpp for examples of using
 * 	the DLL and your BookStore. But don't worry too much, as you
 * 	only need to implement these classes
 * (main and tests are already done for you)
 */


//
#include <iostream>
#include <stdlib.h>
#include <stdexcept>


/**
 * Namespace for our classroom !
 */
namespace CPSC131
{
	/**
	 * Namespace to hold all things related to our DLL
	 */
	namespace DoublyLinkedList
	{
		/**
		 * Node class, which our DLL will use
		 * 
		 * The Professor realizes he could have made this an inline class (like the Iterator),
		 * but he is lazy.
		 */
		template <class T>
		class Node
		{
			public:
				
				/// CTORS
				Node() : prev_(nullptr), next_(nullptr) {}
				Node(T element) : element_(element), prev_(nullptr), next_(nullptr) {}
				Node(T element, Node* prev, Node* next) : element_(element), prev_(prev), next_(next) {}
				~Node() {}
				
				/// Set the pointer to the previous element
				void setPrevious(Node* prev) { this->prev_ = prev; }
				
				/// Set the pointer to the previous element
				void setPrev(Node* prev) {this->prev_ = prev;}
				
				/// Get a pointer to the previous element
				Node* getPrevious() { return prev_; }
				
				/// Get a pointer to the previous element
				Node* getPrev() { return prev_; }
				
				/// Set the pointer to the next node
				void setNext(Node* next) { this->next_ = next; }
				
				/// Get a pointer to the next node
				Node* getNext() { return next_; }
				
				/// Set the element this node holds
				void setElement(T element) { this->element_ = element; }
				
				/// Get the element this node holds
				T& getElement() { return element_;}
				
				/// Return a reference to the element
				T& operator*() { return element_; }
				
			private:
				T element_;
				Node* prev_;
				Node* next_;
		};
		
		/**
		 * Implement our DoublyLinkedList class !
		 */
		template <class T>
		class DoublyLinkedList
		{
			public:
				
				/**
				 * Nested Iterator class.
				 * This allows user code to refer to the Iterator's type as:
				 * 
				 * CPSC131::DoublyLinkedList::DoublyLinkedList<int>::Iterator
				 * 
				 * (as opposed to specifying the template argument two times)
				 */
				class Iterator
				{
					public:
						
						///	Constructor taking a head and tail pointer; YOUR WELCOME
						Iterator(Node<T>* head, Node<T>* tail) : head_(head), tail_(tail)
						{
							this->cursor_ = this->end();
						}
						
						///	Constructor taking a head, tail, and cursor pointer; YOUR WELCOME
						Iterator(Node<T>* head, Node<T>* tail, Node<T>* cursor) : head_(head), tail_(tail), cursor_(cursor) {}
						
						///	Get a pointer to the head node, or end() if this list is empty
						Node<T>* begin()
						{
							
							if (head_ == nullptr) {
								end();
							}

							return this->head_;
						}
						
						///	Get a node pointer representing "end" (aka "depleted"). Probably want to just use nullptr.
						Node<T>* end()
						{
							return nullptr;
						}
						
						///	Get the node to which this iterator is currently pointing
						Node<T>* getCursor()
						{
							return cursor_;
						}
						
						/**
						 * Assignment operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator=(const Iterator& other)
						{
							if (this != &other) {
								this = other;
							}
							return *this;
						}
						
						///	Comparison operator
						bool operator==(const Iterator& other)
						{
							return cursor_ == other.cursor_;
						}
						///	Inequality comparison operator
						bool operator!=(const Iterator& other)
						{
							return cursor_ != other.cursor_;
						}
						
						/**
						 * Prefix increment operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator++()
						{
							if (cursor_ != nullptr) {
								cursor_ = cursor_->getNext();
							}
							return *this;
						}
						
						/**
						 * Postfix increment
						 * Return a copy of this Iterator, BEFORE it was modified
						 */
						Iterator operator++(int)
						{
							Iterator old = *this;
							operator++();
							cursor_= old.cursor_->getNext();
							return old;
						}
						
						/**
						 * Prefix decrement operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator--()
						{
							if (cursor_ != nullptr) {
								cursor_ = cursor_->getPrev();
							}
							return *this;
						}
						
						/**
						 * Postfix decrement operator
						 * Return a copy of this Iterator BEFORE it was modified
						 */
						Iterator operator--(int)
						{
							if (this->cursor_ != nullptr) {
								Iterator copied(this->head_, this->tail_, this->cursor_);
								this->cursor_ = this->cursor_->getPrev();
								return copied;
							}
							else {
								return *this;
							}
						}
						
						/**
						 * Addition Assignment operator
						 * Return a copy of the current iterator, after modification
						*/
						Iterator operator +=(size_t add)
						{
							cursor_ += add;
							return *this;
						}
						/**
						 * Subtraction Assignment operator
						 * Return a copy of the current iterator, after modification
						 */
						Iterator operator -=(size_t add)
						{
							cursor_ -= add;
							return *this;
						}
						
						/**
						 * AdditionAssignment operator, supporting positive or negative ints
						 */
						Iterator operator +=(int add)
						{
							if (add > 0) {
								for (int i = 0; i < add; i++) {
									++(*this);
								}
							} else if (add < 0) {
        						for (int i = 0; i < -add; i++) {
									--(*this);
								}
							}

							return *this;
						}
						
						/**
						 * SubtractionAssignment operator, supporting positive or negative ints
						 */
						Iterator operator -=(int subtract)
						{
							if (subtract > 0) {
       							for (int i = 0; i < subtract; i++) {
            						--(*this);  //call prev() method "subtract" times
        						}
							} else if (subtract < 0) {
        						for (int i = 0; i < -subtract; i++) {
        						++(*this);  //call next() method "-subtract" times
        						}
    						}
    						return *this;
						}
						
						/**
						 * Dereference operator returns a reference to the ELEMENT contained with the current node
						 */
						T& operator*()
						{
							return cursor_->getElement();
						}
					
					private:
						
						/// Pointer to the head node
						Node<T>* head_ = nullptr;
						
						/// Pointer to the tail node
						Node<T>* tail_ = nullptr;
						
						/**
						 * Pointer to the cursor node.
						 * This is only one way of letting the iterator traverse the linked list.
						 * You can change to a different method if you wish (and can still pass unit tests)
						 */
						Node<T>* cursor_ = nullptr;
						

					friend class DoublyLinkedList;
				};
				
				/// Your welcome
				DoublyLinkedList()
				{
					this->head_ = nullptr;
					this->tail_ = nullptr;
					this->size_ = 0;
				}
				
				///	Copy Constructor
				DoublyLinkedList(DoublyLinkedList& other)
				{
					this->head_ = nullptr;
					this->tail_ = nullptr;
					this->size_ = 0;
					
					for (auto it = other.begin(); it != other.end(); ++it) {
						this->push_back(*it);
					}
				}
				
				/// DTOR: Your welcome
				~DoublyLinkedList()
				{
					this->clear();
				}
				
				/**
				 * Clear the list and assign the same value, count times.
				 * If count was 5, T was int, and value was 3,
				 * 	we'd end up with a list like {3, 3, 3, 3, 3}
				 */
				void assign(size_t count, const T& value)
				{
					this->clear();
					
					for(size_t i = 0; i < count; ++i) {
						this->push_back(value);
					}
				}
				
				/**
				 * Clear the list and assign values from another list.
				 * The 'first' iterator points to the first item copied from the other list.
				 * The 'last' iterator points to the last item copied from the other list.
				 * 
				 * Example:
				 * 	Suppose we have a source list like {8, 4, 3, 2, 7, 1}
				 * 	Suppose first points to the 4
				 *	Suppose last points to the 7
				 * 	We should end up with our list becoming: {4, 3, 2, 7}
				 *
				 * If the user code sends out-of-order iterators,
				 * 	just copy from 'first' to the end of the source list
				 * Example: first=7, last=4 from the list above would give us:
				 * 	{7, 1}
				 */
				void assign(Iterator first, Iterator last)
				{
					clear();
					size_ = 0;
					if (first > last) {
						last = last();
					}
					
					for (auto it = first; it != last; ++it) {
						push_back(*it);
					}

					head_ = first.getCursor();
					tail_ = last.getCursor();
				}
				
				/// Return a pointer to the head node, if any
				Node<T>* head() { return head_; }
				
				/// Return a pointer to the tail node, if any
				Node<T>* tail() { return tail_; }
				
				/**
				 * Return an iterator that points to the head of our list
				 */
				Iterator begin()
				{
					return Iterator(head_, tail_, head_);
				}
				
				/**
				 * Return an iterator that points to the last element (tail) of our list
				 */
				Iterator last()
				{
					return Iterator(head_, tail_, tail_);
				}
				
				/**
				 * Should return an iterator that represents being past the end of our nodes,
				 * or just that we are finished.
				 * You can make this a nullptr or use some other scheme of your choosing,
				 * 	as long as it works with the logic of the rest of your implementations.
				 */
				Iterator end()
				{
					 return Iterator(nullptr, nullptr, nullptr);
				}
				
				/**
				 * Returns true if our list is empty
				 */
				bool empty() const
				{
					return head_ == nullptr;
				}
				
				/**
				 * Returns the current size of the list
				 * Should finish in constant time!
				 * (keep track of the size elsewhere)
				 */
				size_t size() const
				{
					return size_;
				}
				
				/**
				 * Clears our entire list, making it empty
				 * Remember: All removal operations should be memory-leak free.
				 */
				void clear()
				{
					for (Node<T> *i = head_; i != nullptr; ) {
						Node<T> *n = i->getNext();
						delete i;
						i = n;
						size_--;
					}

					head_ = nullptr;
					tail_ = nullptr;
				}
				
				/**
				 * Insert an element after the node pointed to by the pos Iterator
				 * 
				 * If the list is currently empty,
				 * 	ignore the iterator and just make the new node at the head/tail (list of length 1).
				 * 
				 * If the incoming iterator is this->end(), insert the element at the tail
				 * 
				 * Should return an iterator that points to the newly added node
				 * 
				 * To avoid repeated code, it might be a good idea to have other methods
				 * 	rely on this one.
				 */
				Iterator insert_after(Iterator pos, const T& value)
				{
					Node<T> *cursor_ = pos.cursor_;

					if (empty()) {
						head_ = new Node<T>(value);
						tail_ = head_;
						size_++;
						return Iterator(head_, tail_, head_);
					} else if (cursor_ == nullptr) {
						tail_->setNext(new Node<T>(value));
						tail_->getNext()->setPrev(tail_);
						tail_ = tail_->getNext();
						size_++;
						return Iterator(tail_, tail_, tail_);
					} else {
						Node<T>* newNode = new Node<T>(value);
						newNode->setNext(cursor_->getNext());
						newNode->setPrev(cursor_);
						cursor_->setNext(newNode);
						if (newNode->getNext() != nullptr) {
							newNode->getNext()->setPrev(newNode);
						} else {
							tail_ = newNode;
						}
						size_++;
						return Iterator(newNode, tail_, newNode->getNext());
					}
				}
				
				/**
				 * Insert a new element after the index pos.
				 * Should work with an empty list.
				 * 
				 * Should return an iterator pointing to the newly created node
				 * 
				 * To reduce repeated code, you may want to simply find
				 * 	an iterator to the node at the pos index, then
				 * 	send it to the other overload of this method.
				*/
				Iterator insert_after(size_t pos, const T& value)
				{
					if (pos > size_) {
						throw std::range_error("Index out of range");
					}
					Iterator itr = begin();
					for (size_t i = 0; i < pos; i++) {
						itr++;
					}
					return insert_after(itr, value);

				}
				
				/**
				 * Erase the node pointed to by the Iterator's cursor.
				 * 
				 * If the 'pos' iterator does not point to a valid node,
				 * 	throw an std::range_error
				 * 
				 * Return an iterator to the node AFTER the one we erased,
				 * 	or this->end() if we just erased the tail
				 */
				Iterator erase(Iterator pos)
				{
					Node<T>* cursor_ = pos.cursor_;
					if (cursor_ == nullptr) {
						throw std::range_error("Iterator does not point to a valid node");
					}
					Node<T>* next_ = cursor_->getNext();
					if (cursor_ == head_) {
						head_ = next_;
					} else {
						cursor_->getPrev()->setNext(next_);
					}

					if (next_ != nullptr) {
						next_->setPrev(cursor_->getPrev());
					} else {
						tail_ = cursor_->getPrev();
					}
					delete cursor_;
					size_--;
					return Iterator(next_, tail_, next_ != nullptr ? next_->getNext() : nullptr);
				}
				
				/**
				 * Add an element just after the one pointed to by the 'pos' iterator
				 * 
				 * Should return an iterator pointing to the newly created node
				 */
				Iterator push_after(Iterator pos, const T& value)
				{
					Node<T>* posNode = pos.cursor_;
					Node<T>* newNode = new Node<T>(value);
					if (posNode == nullptr) {
						if (tail_ == nullptr) {
							head_ = newNode;
							tail_ = newNode;
						} 
						else {
							tail_->setNext(newNode);
							newNode->setPrev(tail_);
							tail_ = newNode;
						}
					} else {
						newNode->setNext(posNode->getNext());
						newNode->setPrev(posNode);
						if (posNode->getNext() != nullptr) {
							posNode->getNext()->setPrev(newNode);
						} else {
							tail_ = newNode;
						}
						posNode->setNext(newNode);
					}
					
					size_++;
					return Iterator(head_, tail_, newNode);
					delete newNode;
				}
				
				/**
				 * Add a new element to the front of our list.
				 */
				void push_front(const T& value)
				{
					Node<T>* newNode = new Node<T>(value);
					if (empty()) {
						tail_ = newNode;
					} 
					
					else {
						newNode->setNext(head_);
						head_->setPrev(newNode);
					}
					
					head_ = newNode;
					size_++;
				}
				
				/**
				 * Add an element to the end of this list.
				 * 
				 * Should return an iterator pointing to the newly created node.
				 */
				Iterator push_back(const T& value)
				{
					if (this->empty()) {
						Node<T>* newNode = new Node<T>(value);
						head_ = newNode;
						this->tail_ = this->head_;
						this->size_ = 1;
						return this->begin();
						
					}
					this->tail_->setNext(new Node<T>(value));
					this->tail_->getNext()->setPrev(this->tail_);
					this->tail_ = this->tail_->getNext();
					this->size_++;
					return this->last();
				}
				
				/**
				 * Remove the node at the front of our list
				 * 
				 * Should throw an exception if our list is empty
				 */
				void pop_front()
				{
					if (empty()) {
						throw std::out_of_range("List is empty");
					}
					Node<T>* oldHead = head_;
					head_ = oldHead->getNext();

					if (head_ != nullptr) {
						head_->setPrev(nullptr);
					} 
					
					else { tail_ = nullptr; }

					delete oldHead;
					size_--;
				}
				
				/**
				 * Remove the node at the end of our list
				 * 
				 * Should throw an exception if our list is empty
				 */
				void pop_back()
				{
					if (empty()) {
						throw std::out_of_range("List is empty");
					}
					
					Node<T>* oldTail = tail_;
					tail_ = oldTail->getPrevious();
					
					if (tail_ != nullptr) {
						tail_->setNext(nullptr);
					}
					else { head_ = nullptr; }
					
					delete oldTail;
					size_--;
				}
				
				/**
				 * Return a reference to the element at the front.
				 * 
				 * Throw an exception if the list is empty
				 */
				T& front()
				{
					if (empty()) {
						throw std::out_of_range("List is empty");
					}
					
					return head_->getElement();
				}
				
				/**
				 * Return a reference to the element at the back.
				 * 
				 * Throw an exception if the list is empty
				 */
				T& back()
				{
					 if (empty()) {
						throw std::out_of_range("List is empty");
					}
					
					return tail_->getElement();
				}
				
				/**
				 * Return the element at an index
				 * 
				 * Should throw a range_error is out of bounds
				 */
				T& at(size_t index)
				{
					if (index >= size_ || index < 0) {
						throw std::range_error("Index out of bounds");
					}

					Node<T>* current = head_;
					size_t i = 0;
					
					while (i < index) {
						current = current->getNext();
						i++;
					}
					
					return current->getElement();

				}
				
				/**
				 * Reverse the current list
				 * 
				 * It might be easy to consider the following:
				 * - Create a temp empty list
				 * - Iterate through the current list
				 * - For each item in the current list, push to the FRONT (not back)
				 * - Assign the current list to the temp list
				 * - Discard the temp list
				 */
				void reverse()
				{
					if (head_ == nullptr || head_->getNext() == nullptr) {
						return;
					}

					Node<T>* current = head_;
					Node<T>* temp = nullptr;
					
					while (current != nullptr) {
						temp = current->getPrev();
						current->setPrev(current->getNext());
						current->setNext(temp);
						current = current->getPrev();
					}

					temp = head_;
					head_ = tail_;
					tail_ = temp;
				}
				
				/**
				 * I bet you're happy I'm not making you do this.
				 * No tests will be run against this function,
				 * 	but feel free to try it out, as a challenge!
				 * 
				 * If I were doing this and didn't care too much for efficiency,
				 * 	I would probably create an extra helper function to swap two
				 * 	positions in the current list.
				 * Then I would simply sweep through the list and perform
				 *  the bubble-sort algorithm. Perhaps selection sort.
				 * 
				 * If you want a huge challenge, try implementing quicksort.
				 * 
				 * (but again, don't worry about this method; it will not be tested)
				 */
				void sort()
				{
					
				}
				
				/**
				 * Assignment operator
				 * 
				 * Clear this list and fill it with the others' values
				 * (by value, not by reference)
				 * 
				 * Return a reference to this list
				 */
				DoublyLinkedList<T>& operator =(DoublyLinkedList<T>& other)
				{
					return *this;
				}
				
				/**
				 * Return true if the lists are "equal"
				 * 
				 * "Equal" here is defined as:
				 * - Same size
				 * - Elements at the same indexes would return true for their own comparison operators
				 * 
				 * In other words: "They contain all the same values"
				 * (no need to be references to each other)
				 */
				bool operator ==(DoublyLinkedList<T>& other)
				{
					if (size() != other.size()) {
						return false;
					}
					
					Iterator ti = begin();
					Iterator oi = other.begin();
					
					while (ti != end()) {
						if (*ti != *oi) {
							return false;
						}
						
						++ti;
						++oi;
					}



					return true;
				}
				
				/**
				 * Return true if the lists are "not equal"
				 * 
				 * See the operator== stub for definition of "equal"
				 * 
				 * Probably want to avoid repeated code by relying on the other operator
				 */
				bool operator !=(DoublyLinkedList<T>& other)
				{
					return !(*this == other);
				}
				
			private:
				
				Node<T>* head_ = nullptr;
				Node<T>* tail_ = nullptr;
				size_t size_ = 0;
		};
	}
}

#endif
