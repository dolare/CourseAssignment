#include <vector>
#include <string>
#include <iostream>
using namespace std;

template <typename T>
class MaxHeap {
private:
    vector<T> items;
    
public:
    int size();
    void softDown();
    void softUp();
    void enqueue(const T& item);
    T peekMax();
    void dequeue();
    void toString();
    bool isEmpty();
	friend ostream& operator<<(ostream& out, const T &ob){
		out << ob;
		return out;
	}
};

template <typename T>
bool MaxHeap<T>::isEmpty() {
    return items.empty();
}

template <typename T>
void MaxHeap<T>::toString(){
    for (int i = 0; i < items.size(); i++){
        cout << items[i] << " ";
    }
    cout << endl;
}

template <typename T>
int MaxHeap<T>::size(){
    return items.size();
}

template <typename T>
void MaxHeap<T>::softUp(){
    size_t k = items.size() - 1;
    while (k > 0){
        size_t p = (k - 1) / 2;
        T child = items[k];
        T parent = items[p];
        if (child > parent){
            items[k] = parent;
            items[p] = child;
            k = p;
        }else break;
    }
}

template <typename T>
void MaxHeap<T>::softDown(){
    int parent = 0;
    int child1 = parent * 2 + 1;
    
    while (child1 < items.size()){
        int max = child1;
        int child2 = child1 + 1;
        if (child2 < items.size()){
            if (items[child2] > items[child1]){
                max = child2;
            }
        }
        
        if (items[parent] < items[max]){
            T temp = items[parent];
            items[parent] = items[max];
            items[max] = temp;
            parent = max;
            child1 = 2 * parent + 1;
        }else break;
    }
}

template <typename T>
void MaxHeap<T>::enqueue(const T& item) {
    items.push_back(item);
    softUp();
}


template <typename T>
T MaxHeap<T>::peekMax(){
    return items[0];
}


template <typename T>
void MaxHeap<T>::dequeue(){
    if (items.size() == 0){
        throw new exception();
    }
    items[0] = items.back();
    items.pop_back();
    softDown();
}


int main(){
    
    MaxHeap<string> maxHeap;
   
	maxHeap.enqueue("a");
	maxHeap.enqueue("ab");
	maxHeap.enqueue("abc");
	maxHeap.enqueue("d");
	maxHeap.enqueue("bvds");
	
   
	

	cout << " For string type: " << endl;
	cout << " Size is : " << maxHeap.size() << endl;
	cout << "is empty :" << maxHeap.isEmpty() << endl;
    while (!maxHeap.isEmpty()){
        cout << maxHeap.peekMax() << endl;
        maxHeap.dequeue();
    }
	cout << "After dequeue : is empty :" << maxHeap.isEmpty() << endl;
	cout << endl;
	cout << " For integer type: " << endl;
	MaxHeap<int> maxHeap1;
	for (int i = 0; i <= 10; i++){
		maxHeap1.enqueue(i);
	}
	cout << " Size is : " << maxHeap1.size() << endl << endl;
	cout << "is empty :" << maxHeap1.isEmpty() << endl;
	while (!maxHeap1.isEmpty()){
		cout << maxHeap1.peekMax() << endl;
		maxHeap1.dequeue();
	}
	cout << "After dequeue : is empty :" << maxHeap1.isEmpty() << endl;
	
    
}
