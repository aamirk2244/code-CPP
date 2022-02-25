#include<iostream>
#define size 10
using namespace std;
class List{
	int *list;                          // will get the list array 
	int *t;                                // temporary pointer we will use this later.                                 
	int length;                         // will count the total length
public:
	
	void insertElement(int val);
	bool deleteElement(int x, int* p);
	// List(int length){this->length = length; list = new list(this->length); };
	List();
	bool is_empty();
	bool is_full();
	void printList();
	int searchElement(int x);
	void insertElementAT(int x, int pos);
	void emptyList();
	int totalLength(){return length;}
	void copyList( List &fromThis );
	int* getList(){return list;};
	~List(){cout << "Distructor is called " << endl;}                       // checking our distructor 
	void sort();
	void reverseList();
};
// 1,2,3
void List::printList()
{
	int *p = list;
		t =  list + this->length;

	cout << "[ ";
	while (p != t)
	{
		
		cout << *p << "  ";
		p++;
	}
	cout << "]" << endl;

}
int List::searchElement(int x)
{
	int *p = list;
		t =  list + this->length;
	while (p!= t)
	{
		if(x == *p)return *p;

		p++;
	}
	cout << "Value not found" << endl;
	return -1;           // means value not found
}
void List::insertElementAT(int x, int pos)        // position will starts from zero
{
	if (pos >= length+1 || pos < 0 || pos == size)      //i.e  if three length then should be max pos contain 3, 4 is not valid
	{
		cout << "Invalid position, maybe the list is full or your input is incorrect" << endl;
		return;
	}
	if (pos+1 == length ){*(this->list + pos) = x;return; }                     // no arrangement needed
	// 1 2 3 4 5 , if pos = 1, and x = 23,  the list should be    1, 23, 2, 3, 4, 5 
	int swap;
	for(int i = this->length ; i > pos; i--)
	{
		swap  =  *(this->list + (i-1));
		*(this->list + (i-1)) = *(this->list + i);                  // sending this deleted value to last position
		*(this->list + i) = swap;

	}
	*(this->list + pos) = x;
	cout << "Value inserted successfully " << endl;
	this->length++;

}

bool List::is_empty()
{
	
	if(this->length == size)
	{
		return false;
	}
	return true;
}
bool List::is_full()
{
	if (this->length == size)
	{
		return true;
	}
	return false;
}
List::List()
{
	cout << "constructor called " << endl;
	this->list= new int[size];
	t = NULL;
	length = 0;
}
//1,2,3
void List::insertElement(int val)
{
	if(is_full())
	{
		cout << "list is full" << endl;
		return;
	}
		
	t =  list + this->length;

	*t = val;
	length++;
	
}

bool List::deleteElement(int x, int* p = NULL)
{
	
	if (p == NULL)
	{
		t =  list + this->length;                         // t will be present at garbage value, i.e after the last

		p = list;
	}
	
	if (p == t)return false;                // means value not found
	if(x == *p)
	{
		length--;
		*p = -1;
		return true;
	}
	if(deleteElement(x, p+1) == true)            // recursive call to find the element
	{
		cout << "element " << x << " is deleted succesfully" << endl;
		if (p+1 == t) return true;                       // it is last element no need to arrange list 
		else
		{
			p += 1;
			while(p != t)
			{
				*p = *(p + 1);                  // sending this deleted value to last position
				p++;
			}
		}
		
	}
	
	return false;

}
void List::emptyList()
{
	length = 0;
	t = list = NULL;
	cout<<"The list is now empty" << endl;
}
void List::copyList(List &fromThis )
{
	int *cp = fromThis.getList(); // returning whole list 
	for (int i = 0 ; i < fromThis.totalLength(); i++)
	{
		this->insertElement(*(cp + i)); 
	}
	this->length = fromThis.totalLength();
	cout << "\nList copies successfully" << endl;
}
bool compare(List &l1, List &l2)
{
	if (l1.totalLength() != l2.totalLength())return false;                       // if list are not   same 
	int *a1 = l1.getList();                     // getting list array 
	int *a2 = l1.getList();
	
	for (int i = 0 ; i < l1.totalLength(); i++)
	{
		if (*(a1 + i) != *(a2 + i))return false;

	}
	return true;                          // it means lists are same 


}
void List::sort()
{
	int *l = this->getList();
	int swap;
	for (int i = 0 ; i < this->totalLength(); i++)
	{
		for (int j = i; j < this->totalLength(); j++)
		{
			if (*(l + i) > *(l + j))
			{
				swap = *(l + j);
				*(l + j) = *(l + i);
				*(l + i) = swap;
			}
		}
	}
	cout << "List sorted successfully" << endl;
}
void List::reverseList()
{
	int left=  -1;
	int swap;
	for (int right = this->length-1; right > int(this->length/2)-1; right--)            // i dit /2 to handle even and odd length list , swapping last with first and so on
	{
		left++;
		if (this->list + left == this->list + right)                 // moving right to right side and left to left side 
		{
			break;

		}
		
		swap = *(this->list + right);
		*(this->list + right) = *(this->list + left);
		*(this->list + left) = swap;


	}
	cout << "list reversed successfully" << endl;
}
// isinstance
int main()
{
		List s;
		List s2;
	
	
	
	s.insertElement(23);
	
	s.insertElement(4);
	
	s.insertElement(7);
	s.insertElement(8);
	
	s.printList();


	s2.copyList(s);                // copy s to s2
	s2.printList();
	cout << compare(s, s2) << endl;               // compare takes 2 list objects
	s2.sort();
	s2.printList();
	s2.insertElementAT(100, 1);                 // inserting 100 at index 1, index starts from 0
	s2.printList();
	s2.reverseList();
	s2.printList();
	s2.deleteElement(7);
	s2.printList();
	s2.reverseList();
	s2.printList();
	cout << s.searchElement(7) << endl;
}
