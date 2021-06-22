// using dictionry 
#include<iostream>
#include<string>
struct KEY_VALUE{
	int key;
	int value;
};
template <class T>

class node{
public:
	node* next;
	T val;
	node(T val);
};
template <class T>
node<T>::node(T val)
{
	this->val = val;
	this->next =NULL;
}
template <class T>
class List{
node<T>* head;
	node<T>* tail;
public:
	
	List();
	void append(T val);
	void insert(T val, int indx);
	void print();
	bool is_empty(int inc);
	T get_node_val(int indx);
	
};
template <class T>
bool List<T>::is_empty(int inc)
{
	node<T>* t = head;
	for(int i = 0 ;i  < inc; i++)
	{
		t = t->next;
	}
	if(t == NULL)
		return true;
	return false;
}
template <class T>
List<T>::List()
{
	head = tail = NULL;
}
template <class T>
void List<T>::append(T val)
{
	node<T>* n = new node<T>(val);
	if(head == NULL)
	{
		head = n;
		tail = head;
		return;
	}
	tail->next = n;
	tail = tail->next;
}
template <class T>
void List<T>::print()
{
	node<T>* temp = head;
	std::cout << "[ ";
	while(temp  != NULL)
	{
		
		std::cout << "Value is " <<  temp->val.value << " ";
		std::cout << "key is " <<  temp->val.key << " ";
		
		temp = temp->next;
	}
	std::cout << "]" << std::endl;
	
}
template <class T>
void List<T>::insert(T val, int indx)
{
	node<T>* tmp = new node<T>(val);
	if(indx == 0)
	{
		tmp->next = head;
		head = tmp;
		return;
	}
	node<T>* mov = head;
	for(int i = 1; i < indx; i++)
	{
		mov = mov->next;
	}
	tmp->next = mov->next;
	mov->next = tmp;
}

template <class T>
T List<T>::get_node_val(int indx){	// it will give the node value at given index
	node<T> *tmp = head;
	for(int i = 0; i < indx; i++)
		tmp = tmp->next;
	return tmp->val;
}
template <class T>
class Hash_Map{
	int size;
	//List key_value;
	List<KEY_VALUE> map[10];
public:
	Hash_Map();
	int get_Hash(int key){return key % size;}
	void add_key_value(int key, int val);
	int* get_values(int key);
		
};
template <class T>
Hash_Map<T>::Hash_Map()
{
	
	size = 10;
	
}
template <class T>
void Hash_Map<T>::add_key_value(int key, int val)
{
	int key_hash = get_Hash(key);
	KEY_VALUE key_value;
	key_value.key = key;
	key_value.value = val;
	map[key_hash].append(key_value);
	//map.insert()
}
template<class T>
int* Hash_Map<T>::get_values(int key)
{
	int key_hash = get_Hash(key);
	int* arr_val = new int[10];
	int i = 0;
		// returnig all value corresponds to keys saved in array
	for(i; i < 10 ; i++)arr_val[i] = 0;
	int inc = 0;	// inc will mov next pointer to next location to whether another value present or not
	// inc = 0 will point to head and 1 will head->next and son  
	i =0;
	if( map[key_hash].is_empty(inc) != true)
	{
		while(map[key_hash].is_empty(inc) != true)
		{
		KEY_VALUE obj;
		obj = map[key_hash].get_node_val(inc);
			if( obj.key == key)
			{
				arr_val[i] = obj.value;
				i++;
			}
				
		inc++;
		}
		return arr_val;
	}
	throw "Key Error";
	
}
int main()
{
	Hash_Map<int> h;
	h.add_key_value(10, 40);
	h.add_key_value(30, 100);
	h.add_key_value(20, 99);
	h.add_key_value(30, 23);
	h.add_key_value(30, 49);
	
	int key = 30;
	try{
		int* get = h.get_values(key);
		int i = 0;
		std::cout << "The values corresponds to key " << key << " are ";
		std::cout << "[ ";
		while(get[i] != 0)	// 0 means NULL or NONE in python
		{
			std::cout << get[i] << " ";
			i++;
		}
			std::cout << " ]";
		
	}catch(const char* msg){
		std::cout << msg << std::endl;
	}
		
}
