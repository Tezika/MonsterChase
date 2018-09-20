#pragma once

namespace Engine
{
	template<class T>
	class TList
	{
		template<class T>
		class Node
		{
		public:
			T* data;
			Node<T>* next;
			Node<T>(const T& d) : data(d), next(nullptr) {}
			Node<T>(const Node<T>& copyNode) : data(copyNode.data), next(copyNode.next) {}
			~Node<T>() { delete data; }
		private:
			Node<T>& operator=(const Node<T>&);
		};

	public:
		TList(const TList&);
		//TList& operator=(TList);
		TList() : head(NULL), tail(NULL) {}
		TList(Node<T> * newNode) : head(newNode), tail(newNode) {}
		~TList();

		bool Remove(Node<T>* node);
		Node<T>* InsertToTail(T* val);

		Node<T>* head;
		Node<T>* tail;
	};
}
