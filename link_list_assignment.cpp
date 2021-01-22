#include<iostream>
#include <string>
class node{
public:
    node *next;
    std::string student_id;
	std::string student_name;
    node(std::string student_id , std::string student_name);
};
node::node(std::string student_id , std::string student_name)
{
    this->student_id = student_id;
	this->student_name = student_name;
	next = NULL;
}
class List{
    node *current, *head;
    int length;
public:
    void append(std::string student_id , std::string student_name);
    List();
    void print();
    void del(std::string student_id);
    void free(node* &f);
	void search_student_by_id(std::string student_id);
    void search_student_by_name(std::string student_name);
	bool id_found(std::string student_id);

};
List::List()
{
    head = current = NULL;
    length = 0;
}
void List::free(node* &f)
{
   
    f->next  = NULL;
    delete f;
    f = NULL;
}
bool List::id_found(std::string student_id)
{
	current  = head;
	while(current != NULL)
	{
		if(current->student_id == student_id)return true;

		current = current->next;
	}
	return false;
}
void List::search_student_by_id(std::string student_id)
{
	current = head;
	bool not_found = true;
	if(current == NULL)
	{
		std::cout <<  "There is no student in the List\n";
		
		return;
	}
	while(current != NULL)
	{
		if(current->student_id == student_id)
		{
			not_found = false;
			std::cout << current->student_id  << "\t" << current->student_name << std::endl;

			return;
		}

		current = current->next;
	}

	if(not_found)std::cout << "This student is not present in the list " << std::endl;
}

void List::search_student_by_name(std::string student_name)
{
	node* current;
	bool not_found = true;
	current = head;
	if(current == NULL)
	{	
		std::cout << "There is no student in the List\n";
		
		return;

	}
	
	while(current != NULL)
	{
		if(current->student_name == student_name)
		{
			not_found = false;
			std::cout << "Yes the student is present \n";

			std::cout << current->student_id  << "\t" << current->student_name << std::endl;

			return;
		}

		current = current->next;
	}
	if(not_found)std::cout << "This student is not present in the list " << std::endl;
}
void List::del(std::string student_id)
{
	node* current;
	current = head;

   if(current == NULL )
   {	
		std::cout << "There is no student in the List\n";
		return;

	} 
	if(student_id == current->student_id  &&  current->next == NULL)
    {
        // for one node 
        free(head);
        length--;
		std::cout << "The student with student Id " <<  student_id << " is removed Successfully" << std::endl; 

        return;
    }
	if(student_id == current->student_id  &&  current->next != NULL)
    {
        // for one node 
        current = current->next;
		free(head);
        length--;
		head = current;
		std::cout << "The student with student Id " <<  student_id << " is removed Successfully" << std::endl; 

        return;
    }
	
    
    node* del;
	do{
		if( current->next != NULL && current->student_id == student_id)	// it means this is not a last node
		{
			del->next = current->next;
			free(current);
			length--;
			std::cout << "The student with student Id " <<  student_id << " is removed Successfully" << std::endl; 
     
			return;
		}
		if(current->next == NULL && current->student_id == student_id)	// it means this is a last node
		{
			del->next = current->next;
			free(current);
			length--;
			std::cout << "The student with student Id " <<  student_id << " is removed Successfully" << std::endl; 

			return;
		}
		del = current;
		current = current->next;
	}while(current != NULL);

  
	std::cout << "The student id is incorrect\n";	// if student not found 

}

void List::print()
{
	node* current;
    current = head;
	if(current == NULL)
	{	
		std::cout << "No student to show\n";
		return;

	};	// if list is empty
    while(current != NULL)
    {
		std::cout << current->student_id  << "\t" << current->student_name << std::endl;
        current = current->next;
    }
   std::cout << std::endl;
}
void List::append(std::string student_id, std::string student_name)
{
	if(id_found(student_id))
	{
		std::cout << "This Student is Already in the List\n";
		return;
	}

    if(head == NULL)
    {
         head = new node(student_id, student_name);
         length++;
         current = head;
         return;
    }
	current  = head;
	while(current->next != NULL)current = current->next;
    node* n = new node(student_id, student_name);
    length++;
    current->next = n;
    current = current->next;

}
void Run()
{
	List l;
	int choice;
	bool flag = true;

	
		std::string student_id;
		std::string student_name;
		
	int count = 0;
	bool ist_time = true;
	while(flag)
	{
		std::cout << "Press Enter to Continue" << std::endl;
		std::cin.get();

		std::cout << "1- Enter Student Information" << std::endl;
		std::cout << "2- Search Student by ID" << std::endl;
		std::cout << "3- Search Student by Name" << std::endl;
		std::cout << "4- Delete Student Information" << std::endl;
		std::cout << "5- Print All Students" << std::endl;
		std::cout << "6- Quit" << std::endl;
		std::cin>> choice;


		if (choice == 1)
		{
			std::cout << "Enter Student Id" << std::endl;
			std::cin >> student_id;
			std::cout << "Enter Student Name" << std::endl;
			std::cin >> student_name;
			l.append(student_id, student_name);
			std::cin.get();
		}
		else if(choice == 2)
		{
			std::cout << "Enter Student Id" << std::endl;
			std::cin >> student_id;
			l.search_student_by_id(student_id);
			std::cin.get();
		}
		else if (choice == 3)
		{
			std::cout << "Enter Student Name" << std::endl;
			std::cin >> student_name;
			l.search_student_by_name(student_name);
std::cin.get();
		}
		else if(choice == 4)
		{
			std::cout << "Enter Student Id" << std::endl;
			std::cin >> student_id;
			l.del(student_id);
		std::cin.get();
		}
		else if(choice == 5)
		{
			l.print();
			std::cin.get();
		}
		else if(choice == 6)
		{
			flag = false;
		}
		else 
		{
				std::cout << "Wrong Input. Please Input corrent Input\n" ;	
				std::cin.get();
		}
		
	}
	

}
int main(){
		Run();
	
    return 0;
    
}