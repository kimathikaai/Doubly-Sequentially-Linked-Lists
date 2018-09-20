/*
 * DoublyLinkedList.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: Kimathi
 */

#include "DoublyLinkedList.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
	value = data;
	next = NULL;
	prev = NULL;
}

DoublyLinkedList::DoublyLinkedList()
{
	head_ = NULL;
	tail_ = NULL;
	size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
	if(empty())
		return;

	Node* headtemp = NULL;
	while(head_->next != NULL){
		headtemp = (*head_).next;
		delete head_;
		head_ = headtemp;
	}

	delete head_;
	head_ = NULL;
	tail_ = NULL;
}

bool DoublyLinkedList::empty() const
{
	return size_ == 0;
	/*
	 * Previous Code:
	 * 	return head_ == NULL;
	 */
}

unsigned int DoublyLinkedList::size() const
{
	return size_;
	/*
	  Previous Code:
	  	if (head_ == NULL)
			return 0;

		int count = 1;
		Node* temp = head_;
		while(temp != tail_){
			temp = (*temp).next;
			count++;
		}
	return count;
	 */
}

void DoublyLinkedList::print() const
{
	if(head_ == NULL)
		cout << "Nothing to print, the list is empty" << endl;
	else
	{
		Node* temp = head_;
		do{
			cout << temp->value;
			temp = temp->next;
		}
		while(temp->next != NULL);
	}
}

bool DoublyLinkedList::insert_front(DataType value)
{
	if(full())
		return false;

	Node* NewNode = new Node(value);

	if(empty())
		head_ = tail_ = NewNode;
	else
	{
		NewNode->next = head_;
		head_->prev = NewNode;
		head_ = NewNode;
	}
	size_++;
	return true;
}

bool DoublyLinkedList::remove_front()
{
	if(empty())
		return false;

	if( size_ == 1)
	{
		delete head_;
		head_ = tail_ = NULL;
	}
	else
	{
		Node* temp = head_->next;
		delete head_;
		head_ = temp;
		temp->prev = NULL;
	}

	size_--;
	return true;

	//Previous Code did not check for the "size_==1" case
}

bool DoublyLinkedList::insert_back(DataType value)
{
	if(full())
		return false;

	Node* NewNode = new Node(value);

	if(empty())
		head_ = tail_ = NewNode;

	else{
		NewNode->prev = tail_;
		tail_->next = NewNode;
		tail_ = NewNode;
	}

	size_++;
	return true;
}

bool DoublyLinkedList::remove_back()
{
	if(empty())
		return false;

	if(size_ > 1){
		tail_ = tail_->prev;
		delete tail_->next;
		tail_->next = NULL;
	}
	else{
		delete head_;
		head_ = NULL;
		tail_ = NULL;
	}
	size_--;
	return true;
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
	if(full() || index > size_)
		return false;

	if( index == 0 )
	{
		insert_front(value);
		return true;
	}

	else if( index == size_)
	{
		insert_back(value);
		return true;
	}

	else
	{	Node* temp = head_;
		Node* NewNode = new Node(value);

		for(unsigned int i = 0; i < index; i++)
			temp = temp->next;

		NewNode->next = temp;
		NewNode->prev = temp->prev;
		temp->prev = NewNode;
		NewNode->prev->next = NewNode; // NewNode->prev->next
	}
	size_++;
	return true;

	//Previous code did not check for validity of index
}

bool DoublyLinkedList::remove(unsigned int index)
{
	if(empty()|| index >= size_)
		return false;

	if(size_ == 1)
	{
		delete head_;
		head_ = tail_ = NULL;
	}
	else if( index == size_ - 1)
	{
		remove_back();
		return true;
	}
	else if( index == 0 )
	{
		remove_front();
		return true;
	}
	else
	{
		Node* temp = head_;
		for(unsigned int i = 0; i < index; i++)
			temp = temp->next;

		temp->prev->next = temp->next; // (*((*temp).prev)).next = (*temp).next
		temp->next->prev = temp->prev;
		delete temp;
	}

	size_--;
	return true;
	//Previous code did not check for validity of index
}

unsigned int DoublyLinkedList::search(DataType value) const
{
	if(empty())
		return size_;

	Node* temp = head_;
	for(unsigned int i = 0; i < size_; i++){
		if(temp->value == value)
			return i;
		temp = temp->next;
		}
	return size_;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
	if(empty()||index >= size_)
		return tail_->value;

	Node* temp = head_;
	for(unsigned int i = 0; i < index; i++)
		temp = temp->next;

	return temp->value;
}
unsigned int DoublyLinkedList::capacity() const
{
	return CAPACITY;
}
bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
	if(empty()||index >= size_)
		return false;

	Node* temp = head_;
	for(unsigned int i = 0; i < index; i++)
		temp = temp->next;

	temp->value = value;
	return true;
}
DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
	if(empty()||index >= size_)
		return NULL;

	Node* temp = head_;
	for(unsigned int i = 0; i < index; i++){
		temp = temp->next;
	}
	return temp;
}
bool DoublyLinkedList::full() const
{
	return size_ >= CAPACITY;
}

