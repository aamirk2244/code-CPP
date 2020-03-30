#include<iostream>
#define size 10

class Stack{
	int top;
	int s[size];
public:
	Stack();
	void push(int val);
	int pop();
	bool is_full();
	bool is_empty();
};
Stack::Stack()
{
	top = -1;
}
bool Stack::is_empty()
{
	if(top < 0)
		return true;
	
	return false;
}
bool Stack::is_full()
{
	if(size == top+1)
		return true;
		
	return false;
}
void Stack::push(int val)
{
	if(is_full())
		throw "Stack Overflow ";
		
	s[++top] = val;
	
}
int Stack::pop()
{
	if(is_empty())
		throw "Stack Underflow ";
		
	return s[top--];
}
int main()
{
	Stack s;
	try{
		s.push(1);
	s.push(2);
		
	s.push(3);
	s.push(4);
	s.push(5);
	
		s.push(6);
	s.push(7);
	s.push(8);
	s.push(9);
	s.push(10);
	std::cout   << s.pop() << " Popped " << std::endl;
	std::cout   << s.pop() << " Popped " << std::endl;
	std::cout   << s.pop() << " Popped " << std::endl;
	std::cout   << s.pop() << " Popped " << std::endl;
	std::cout   << s.pop() << " Popped " << std::endl;
	s.push(100);
	std::cout   << s.pop() << " Popped " << std::endl;
	std::cout   << s.pop() << " Popped " << std::endl;
	std::cout   << s.pop() << " Popped " << std::endl;
	std::cout   << s.pop() << " Popped " << std::endl;
	std::cout   << s.pop() << " Popped " << std::endl;
	
	}catch(const char* msg){
		std::cout << msg;
	}
	
	
}
