#include <iostream>    
#include <stack> 

int main()
{
	std::stack<int> mystack;

	mystack.push(1);
	mystack.push(2);
	std::cout << ' ' << mystack.top() << " ";
	mystack.pop();

	mystack.push(3);
	mystack.push(4);
	std::cout << ' ' << mystack.top() << " ";
	mystack.pop();
	std::cout << ' ' << mystack.top() << " ";
	mystack.pop();

	mystack.push(5);
	mystack.push(6);
	std::cout << ' ' << mystack.top() << " ";
	mystack.pop();
	std::cout << ' ' << mystack.top() << " ";
	mystack.pop();
	std::cout << ' ' << mystack.top() << " ";
	mystack.pop();
	
	return 0;
}