#include  "stdafx.h"
#include  "TList.h"

using namespace Engine;

 template<class T>
 TList<T>::TList(const TList<T>& List) : head_(nullptr), tail_(nullptr)
 {

 }

 template<class T>
 TList<T>::Node<T> TList<T>::InsertToTail(T val)
 {
	 auto newNode = new Node<T>(val);
	 if (head_ == nullptr)
	 {
		 head_ = newNode;
		 tail_ = newNode;
	 }
	 else
	 {
		 tail_->next = node;
		 tail_ = node;
	 }
	 return newNode;
 }

 template<class T>
 bool TList<T>::Remove(Node<T> node)
 {
	 return true;
 }

 template<class T>
 TList<T>::~TList() 
 {
	 auto cur = head_;
	 while (head_)
	 {
		 head_ = head_->next;
		 delete cur;
		 cur = head_;
	 }
	 head_ = nullptr;
	 tail_ = nullptr;
 }

