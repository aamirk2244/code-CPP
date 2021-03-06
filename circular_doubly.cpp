
#include<iostream>
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
    void print_reverse();
	void insert(int val, int pos);
    node* get_last();
    void del(int pos);
    void free(node* &f);
    

};
List::List()
{
    head = current = NULL;
    length = 0;
}
void List::free(node* &f)
{
	
    f->next  = NULL;
    f->priv = NULL;
    delete f;
	f = NULL;
 
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
void List::del(int pos)
{
    int val;
    if(pos < 1 )
        throw "Position out of range. Select Valid position";

    if(head->next == head)
    {
        // for one node 
        free(head);
        return;
    }
    if(pos == 1)
    {
    	// 1,2,3,4
		node* last = get_last();
        current = head;
        node* del = current;
        head = head->next;
        val = del->val;
        last->next = head;
        head->priv = last;
        free(del);
        length--;
        std::cout << val << " at Position " << pos << " is deleted Successfully" << std::endl; 
        return;
    }			
    // 1,2,3,4
    // for middle cases
    current = head;
    node* del = current;
    for(int i  = 1 ; i < pos-1; i++)
    {
        current = current->next;
        del = del->next;

    }
    del = del->next;
    del->next->priv = current;
	current->next = current->next->next;
    
    val = del->val;
    if(del == head)
    {
    	head = head->next;	
	}
    free(del);
    length--;
 std::cout << val << " at Position " << pos << " is deleted Successfully" << std::endl; 
}
void List::insert(int val, int pos)
{

    if(pos < 1)
        throw "Position starts from 1. Select Valid position";
    current = head;

    if(head == NULL)
    {
        head = new node(val);
        head->next = head->priv = head;
        current = head;
        length++;
         std::cout <<"The value " <<  val << " at Position " << pos << " is inserted Successfully" << std::endl; 
       
        return;
    }
    if(pos == (length + 1))
    {  // this is the last position
        node* lst = get_last();
        node* last = new node(val);
        lst->next = last;
        last->priv = lst;
		last->next = head;
		head->priv = last;
        length++;
        std::cout <<"The value " <<  val << " at Position " << pos << " is inserted Successfully" << std::endl; 
     
        return;
    }

    if(pos == 1)
    {
        // inserting at ist position
        node* last = get_last();
        node* ist = new node(val);
        ist->next = head;
        head->priv  = ist;
        head = ist;
        last->next  = head;
        head->priv = last;
        length++;
        std::cout <<"The value " <<  val << " at Position " << pos << " is inserted Successfully" << std::endl; 
     
        return;
    }
    // for middle case
    current = head; 
    for(int i = 1; i < (pos - 1) ; i++)
    {
        current = current->next;
    }
    // 1,2,3,4
    
    node* mid = new node(val);
    mid->next = current->next;
    mid->next->priv = mid;
    current->next = mid;
	mid->priv = current; 
    
    length++;
    std::cout <<"The value " <<  val << " at Position " << pos << " is inserted Successfully" << std::endl; 
     
    
}
void List::print()
{
    if(head->next == head)
    { // for one node 
        std::cout << "[ " << head->val << " ]" << std::endl;
        return;
    }  
    current = head;
    std::cout << "[ ";
    std::cout << current->val << ", ";
    current = current->next;
    while(current != head)
    {
        std::cout << current->val ;
        
        if(current->next == head)   // it will look like python list
            std::cout << " ]";
        else
            std::cout << ", ";

        
        current = current->next;        
        
    }
   std::cout << std::endl;
}
void List::append(int val)
{
    if(head == NULL)
    {
         head = new node(val);
         head->next  = head;
         head->priv = head;
         length++;
         current = head;
         return;
    }

    node* n = new node(val);
    length++;
    current->next = n;
    n->priv = current;
    current = current->next;
    current->next = head;
    head->priv  = current;

}
void List::print_reverse()
{
	std::cout << "___________printing in reverse order___________ " << std::endl;
	if(head->priv == head)
    { // for one node 
        std::cout << "[ " << head->val << " ]" << std::endl;
        return;
    }
	node* last =  get_last();
	node* end = get_last();
	std::cout << "[ ";
    std::cout << last->val << ", ";
    last = last->priv;
    while(last != end)
    {
        std::cout << last->val ;
        
        if(last->priv == end)   // it will look like python list
            std::cout << " ]";
        else
            std::cout << ", ";

        
        last = last->priv;        
        
    }
   std::cout << std::endl;
   std::cout << "_____________________________";
   std::cout << std::endl;
	
}
int main(){
    List l;
    try{
		for(int i = 1;  i <= 10; i++)
        {
            if(i == 5)
                continue;
            
            l.append(i);
        }
   
    
	l.print();
    
	l.insert(5,5);
    
	l.print();
    
	l.del(4);
    
	l.print();
	l.print_reverse();
    
 }catch(const char* msg){
        std::cout<<std::endl << msg << std::endl;
    }
    return 0;
    
}
