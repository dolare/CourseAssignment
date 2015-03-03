
#ifndef Single_Linked_List_H
#define	Single_Linked_List_H
#include <cassert>

	// DEFINITION OF TEMPLATE CLASS
	template <class T>
	class SList
	{
	public: 
		class Iterator;
		friend class Iterator;

		struct Node{
			T data;
			Node *next;
			Node(){ next = NULL };
			Node(const T& a, Node *p = NULL) { data = a; next = p; }
		};

	private:
		Node *head_ptr;
		Node *tail_ptr;

	public:
		SList();
		SList(const SList<T>&);
		SList<T>& operator =(const SList<T>&);
		~SList();

		Iterator begin();
		Iterator end();

		bool IsEmpty() const;
		const T& ShowFirst() const;

		void AddFirst(const T&);
		void AddLast(const T&);
		void AddAfter(Iterator, const T&);
		void RemoveFirst();
		void RemoveAfter(Iterator);
		void SetToEmpty();

		class Iterator
		{
			friend class SList<T>;
		private:
			Node *current;
		public:
			Iterator(Node* initial = NULL) { current = initial; }
			T& operator *() const { return current->data; }
			Iterator& operator ++()	{ current = current->next; return *this; }
			Iterator operator ++(int)	{ current = current->next; return Iterator(original); }
			bool operator ==(const Iterator other) const { return current == other.current; }
			bool operator !=(const Iterator other) const { return current != other.current; }
		};
	};

	// IMPLEMENTATION OF MEMBER FUNCTION OF THE TEMPLATE CLASS

	// default constructor
	template <class T>
	SList<T>::SList()
	{
		head_ptr = NULL;
		tail_ptr = NULL;
	}

	// default destructor
	template <class T>
	SList<T>::~SList()
	{
		SetToEmpty();	//remove all nodes in the single list

		// release memory
		delete head_ptr;
		delete tail_ptr;
	}

	// copy constructor
	template <class T>
	SList<T>::SList(const SList<T> &obj)
	{
		head_ptr = NULL;
		tail_ptr = NULL;
		*this = obj;
	}

	// overload operator =
	template <class T>
	SList<T>& SList<T>::operator=(const SList<T> &obj)
	{
		if (head_ptr == obj.head_ptr)	// the same list
			return *this;

		SetToEmpty();					// clear the list
		if (obj.head_ptr == NULL)		// return empty list if obj list is empty
			return *this;

		Node *pre_ptr = NULL;
		Node *insert_ptr;

		Node *cursor;
		cursor = obj.head_ptr;
		while (cursor != NULL)
		{
			if (cursor == obj.head_ptr)
			{
				this->AddFirst(cursor->data);
				pre_ptr = head_ptr;
			}
			else
			{
				insert_ptr = new Node(cursor->data);
				tail_ptr = insert_ptr;
				pre_ptr->next = insert_ptr;
				pre_ptr = insert_ptr;
			}

			cursor = cursor->next;
		}
		return *this;
	}

	template <class T>
	typename SList<T>::Iterator SList<T>::begin()
	{
		return Iterator(head_ptr);
	}

	template <class T>
	typename SList<T>::Iterator SList<T>::end()
	{
		return Iterator();
	}

	// check if the list is empty
	template <class T>
	bool SList<T>::IsEmpty() const
	{
		return head_ptr == NULL;
	}

	// show the data of the first node in the list
	template <class T>
	const T& SList<T>::ShowFirst() const
	{
		assert(head_ptr != NULL);
		return head_ptr->data;
	}

	// add a new node at the first of the list
	template <class T>
	void SList<T>::AddFirst(const T& newItem)
	{
		head_ptr = new Node(newItem, head_ptr);
		if (tail_ptr == NULL)
			tail_ptr = head_ptr;
	}

	// add a new node at last of the list
	template <class T>
	void SList<T>::AddLast(const T& newItem)
	{
		Node *insert_ptr;
		insert_ptr = new Node(newItem);	// create a new node

		if (tail_ptr == NULL)			// an empty list
		{
			tail_ptr = insert_ptr;
			head_ptr = tail_ptr;
		}
		else
		{
			tail_ptr->next = insert_ptr;	// link tail node next pointer to new node
			tail_ptr = insert_ptr;			// move tail pointer to new node
		}
	}

	// add a new node after current node
	template <class T>
	void SList<T>::AddAfter(Iterator it, const T& newItem)
	{
		assert(it.current != NULL);

		Node *insert_ptr;
		insert_ptr = new Node(newItem, it.current->next);
		it.current->next = insert_ptr;

		if (it.current == tail_ptr)			// add the item after tail, then move tail pointer to the new item
			tail_ptr = insert_ptr;
	}

	// remove the node at the head of the list
	template <class T>
	void SList<T>::RemoveFirst()
	{
		assert(head_ptr != NULL);

		Node *remove_ptr;
		remove_ptr = head_ptr;
		head_ptr = head_ptr->next;
		if (tail_ptr == remove_ptr)	// only one node in the list
			tail_ptr = NULL;

		delete remove_ptr;
	}

	// remove the node after current node
	template <class T>
	void SList<T>::RemoveAfter(Iterator it)
	{
		if (it.current != tail_ptr)
		{
			Node *remove_ptr;

			remove_ptr = (it.current)->next;			// link the current next pointer to the node after removed node
			(it.current)->next = remove_ptr->next;

			if (tail_ptr == remove_ptr)			// move tail pointer to current node if the removed node is the last of the list
				tail_ptr = it.current;

			delete remove_ptr;				// remove the node and temporary pointer
		}
		// do nothing if the current node is the last one
	}

	// remove all the nodes in the list
	template <class T>
	void SList<T>::SetToEmpty()
	{
		while (head_ptr != NULL)	// remove nodes if nodes exist
		{
			Node *remove_ptr;
			remove_ptr = head_ptr;
			if (head_ptr == tail_ptr)
				tail_ptr = tail_ptr->next;
			head_ptr = head_ptr->next;

			delete remove_ptr;
		}
	}

#endif