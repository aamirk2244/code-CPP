#include <iostream>
using namespace std;
class node{
public:
    node *next;
    node *priv;
    int val;
    node(int val);
};
node::node(int val)
{
    this->val = val;
    next = priv = NULL;
}
class List{
    node *current, *head;
    int length;
public:
    void append(int val);
    List();
    void print();
    node* get_last();
	void reverse();
};
List::List()
{
    head = current = NULL;
    length = 0;
}
node* List::get_last()
{
    current = head;
    node* last = head;
    for(int i = 1 ; i < length; i++)
    {
        last = last->next;
    }
    return last;
}
void List::reverse()
{
	if (length <= 1)return;
	
	current = get_last();
	head = current;           // last node will be our head 

	node* temp = current->priv;
	while(true)              
	{
		current->next = temp;
		if(temp->priv == NULL)             
		{
			temp->priv = current;
			temp->next = NULL;
			head->priv = NULL;
			return;            // done return
		}
		temp = temp->priv;
		temp->next->priv = current;
		current = temp->next;
	}

	
}

void List::print()
{
    current = head;
    std::cout << "[ ";
    while(current != NULL)
    {
        
        if(current->next == NULL)   // it will look like python list
            std::cout <<current->val <<  " ]";
        else
            std::cout << current->val  << ", ";

        
        current = current->next;        
        
    }
   std::cout << std::endl;
}
void List::append(int val)
{
    if(head == NULL)
    {
         head = new node(val);
         length++;
         current = head;
         return;
    }
	current = get_last();
    node* n = new node(val);
    length++;
    current->next = n;
    n->priv = current;
    
    current = current->next;

}
int main(){
    List l;
	for(int i = 1;  i <= 10; i++)
	{
		if(i == 5)
			continue;
		
		l.append(i);
	}
	
	l.append(20);
   l.append(21);

l.append(22);
   
   l.print();
   l.reverse();
   l.print();
   l.reverse();               // again reversing to get the ist list 
   l.print();
	
   std::cout << std::endl;
   
    return 0;
    
}