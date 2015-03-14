#include <iostream>
using namespace std;


template<class T>
class SList
{
public:
    SList();
    SList(const SList<T> &cObj);
    SList<T>& operator=(const SList<T> &cObj);
    ~SList();
    
private:
    struct Node {
        T data;
        Node *next;
        Node() { next = 0; }
        Node(const T& a, Node *p = 0) { data = a; next = p; }
    };
    
    Node *head;
    
    
public:
    friend class Iterator;
    
    class Iterator {
        friend class SList < T >;
    private:
        Node *current;
    public:
        Iterator(Node *node = NULL){
            current = node;
        }
        Iterator& operator ++(){
            current = current->next;
            return *this;
        }
        Iterator& operator ++(int){
            current = current->next;
            return Iterator();
        }
        T& operator *(){
            return current->data;
        }
        
        bool operator ==(const Iterator &right) {
            return current == right.current;
        }
        bool operator !=(const Iterator &right) {
            return current != right.current;
        }
    };
    
    Iterator Begin();
    Iterator End();
    bool IsEmpty() const;
    const T& ShowFirst() const;
    
    void AddFirst(const T &newItem);
    void AddLast(const T &newItem);
    void AddAfter(Iterator i, const T &newItem);
    void RemoveFirst();
    void RemoveAfter(Iterator i);
    void SetToEmpty();
};

//constructors
template<class T>
SList<T> ::SList(){
    
    head = NULL;
    
    
}

template <class T>
SList<T>::~SList()
{
    
    this->SetToEmpty(); //The list object is empty after this operation.
    delete head;
    
    
}

//The List copy constructor, which constructs a list andinitializes it with copies of the items of list cObj.
template <class T>
SList<T>::SList(const SList<T> &cObj){
    Node *newHead = NULL;
    if (cObj.head != NULL) {
        newHead = new Node(cObj.head->data);
        auto obj_it = cObj.head->next;
        auto newHead_it = newHead;
        while (obj_it) {
            Node *newNode = new Node(obj_it->data);
            newHead_it->next = newNode;
            newHead_it = newNode;
            obj_it = obj_it->next;
        }
    }
    this->head = newHead;
}

//The List assignment operator, which replace current list with a copy of list cObj.
template <class T>
SList<T>& SList<T>::operator=(const SList<T> &cObj){
    Node *newHead = NULL;
    if (cObj.head != NULL) {
        newHead = new Node(cObj.head->data);
        auto obj_it = cObj.head->next;
        auto newHead_it = newHead;
        while (obj_it) {
            Node *newNode = new Node(obj_it->data);
            newHead_it->next = newNode;
            newHead_it = newNode;
            obj_it = obj_it->next;
        }
    }
    this->head = newHead;
    return *this;
}

//Adds a copy of newItem at the beginning of the list.
template <class T>
void SList<T>:: AddFirst(const T &newItem){
    
    this->head = new Node(newItem, head);
    
    
}

template <class T>
void SList<T>::AddLast(const T &newItem){
    
    Node *temp = head;
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = new Node(newItem);
    
}

//Returns an Iterator set to the first item of the list.
template <class T>
typename SList<T>::Iterator SList<T>::Begin(){
    
    return Iterator(this->head);
    
}

//Returns an Iterator set to the End position of the list.
template <class T>
typename SList<T>::Iterator SList<T>::End(){
    
    return Iterator();
    
}

//Returns true if the list is empty, false otherwise.
template <class T>
bool SList<T> :: IsEmpty()const{
    
    return head == NULL;
    
}

//
template <class T>
const T& SList<T>::ShowFirst() const
{
    
    return head->data;
    
}


template <class T>
void SList<T>::AddAfter(Iterator it, const T& newItem)
{
    
    if (it.current != NULL){
        it.current->next = new Node(newItem, it.current->next);
    }
    
}

template <class T>
void SList<T>::RemoveFirst()
{
    
    head = head->next;
    
}

template <class T>
void SList<T>::RemoveAfter(Iterator it)
{
    Node *temp = (it.current)->next;
    if (it != this->End()) {
        (it.current)->next = temp->next;
    }
    delete temp;
}

template <class T>
void SList<T>::SetToEmpty()
{
    Node *temp;
    
    while (head != NULL)
    {
        
        temp = head;
        head = head->next;
        delete temp;
        
    }
    
}


int main()
{
    
    SList<int> List1;
    List1.AddFirst(5);
    List1.AddFirst(4);
    List1.AddFirst(3);
    List1.AddFirst(2);
    List1.AddFirst(1);
    List1.AddLast(3);
    List1.RemoveFirst();
    
    cout << List1.ShowFirst() << endl;
    
   
    
    
    
    
    List1.AddLast(6);
    
    cout << List1.ShowFirst() << endl;
    
    
    
    cout << "" <<List1.IsEmpty() << endl;
    
    for (auto it = List1.Begin(); it != List1.End(); ++it)
    {
        cout << *it << endl;
    }
    cout << "....." << endl;
    SList<int> List2;
    List2.AddFirst(5);
    List2.AddFirst(4);
    List2.AddFirst(3);
    List2.AddFirst(2);
    List2.AddFirst(1);
    List2.AddLast(3);
    List2.RemoveFirst();
    
    //List1 = List2;
    SList<int> List3 = List2;
    for (auto it = List3.Begin(); it != List3.End(); ++it)
    {
        cout << *it << endl;
    }
    
    return 0;
}