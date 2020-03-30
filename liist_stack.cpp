#include<iostream>
class node{
	public:
		node* priv;
		int val;
		node(int val);
		
};
node::node(int val)
{
	priv = NULL;
	this->val = val;
}
class Stack{
	node *head , *current, *del;
public:
	Stack();
	void push(int val);
	node** pop();
	bool is_empty();
	void free(node** n){
		(*n)->priv = NULL;
		delete (*n);
		*n = NULL;
		n = NULL;
	}
	
};

Stack::Stack()
{
	head = current =del =  NULL;
	
}
bool Stack::is_empty()
{
	if(head == NULL){
		return true;
		
	}
		
	
	return false;
}
void Stack::push(int val)
{
	
	if(is_empty())
	{
		head = new node(val);
		current = head;
		return;
	}
	node* n= new node(val);
	
	n->priv = current;
	current  = n;
}
node** Stack::pop()
{
	
	if(is_empty())
		throw "Stack Underflow";
		
	if(current == head)
	{
		return &head;
	}
	del = current;
	current = current->priv;
	return &del;
}
int main()
{
	node** get;
	Stack s;
	try{
		s.push(1);
		s.push(2);
		s.push(3);
		
		get = s.pop();
		std::cout << (*get)->val << " Has been popped " << std::endl;
		s.free(get);
		get = s.pop();
		std::cout << (*get)->val << " Has been popped " << std::endl;
		s.free(get);
		get = s.pop();
		std::cout << (*get)->val << " Has been popped " << std::endl;
		s.free(get);
		s.pop();
	
	}catch (const char* msg){
		std::cout << std::endl;std::cout << msg;
	}
	
}
