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
    void insert(int val, int pos);
    node* get_last();
    void del(int pos);
    void free(node* &f);
    void print_reverse();
    

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
    if(pos < 1 || pos > length )
        throw "Position out of range. Select Valid position";

    std::cout << "total length is " << length << std::endl;
	if(pos == 1  &&  head->next == NULL)
    {
        // for one node 
        free(head);
        length--;
        return;
    }
    if(pos == 1)
    {
        current = head;
        node* del = current;
        head = head->next;
        head->priv = NULL;
        val = del->val;
        free(del);
        length--;
        std::cout << val << " at Position " << pos << " is deleted Successfully" << std::endl; 
        return;
    }
    // for last case
	if(pos == length)
	{
		node* del = get_last();
		node* back = del->priv;
		free(del);
		back->next = NULL; 
		length--;
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

    free(del);
    length--;
  std::cout << val << " at Position " << pos << " is deleted Successfully" << std::endl; 
}
void List::insert(int val, int pos)
{
	// 1,2,3,4
    if(pos < 1 || pos > length+1)
        throw "Position starts from 1. Select Valid position";
    current = head;

    if(head == NULL)
    {
        head = new node(val);
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
        length++;
        std::cout <<"The value " <<  val << " at Position " << pos << " is inserted Successfully" << std::endl; 
     
        return;
    }

    if(pos == 1)
    {
        // inserting at ist position
        node* ist = new node(val);
        ist->next = head;
        head->priv  = ist;
        head = ist;
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
    node* mid = new node(val);
    mid->next = current->next;
    mid->next->priv = current;
	current->next = mid;
    length++;
    std::cout <<"The value " <<  val << " at Position " << pos << " is inserted Successfully" << std::endl; 
     
    
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

    node* n = new node(val);
    length++;
    current->next = n;
    n->priv = current;
    
    current = current->next;

}
void List::print_reverse()
{
	std::cout << "_______printing in reverse order_____________ " << std::endl;
    node* last = get_last();
    std::cout << "[ ";
    while(last != NULL)
    {
        
        if(last->priv == NULL)   // it will look like python list
            std::cout <<last->val <<  " ]";
        else
            std::cout << last->val  << ", ";

        
        last = last->priv;        
        
    }
    
   std::cout << std::endl;
	std::cout << "____________________ " << std::endl;
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
   
    l.del(1);
   
    l.print();
   std::cout << std::endl;
   l.print_reverse();
   /*
    l.print();
   	*/
	   }catch(const char* msg){
        std::cout<<std::endl << msg << std::endl;
    }
    return 0;
    
}
