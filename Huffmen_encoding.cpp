// Huffmen encoding is used to compress the text file size 
#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<iostream>
#define SIZE 2
template <class T>
class Stack{
	T s[SIZE];
	int indx;
public:
	
	int read_ist;
	Stack();
	bool is_Full();
	bool is_Empty();
	void push(T val);
	T read_from_start();
	T pop();
	T top();
};
template <class T>
Stack<T>::Stack()
{
	indx = -1;
}
template <class T>
T Stack<T>::read_from_start()
{
	T store = s[read_ist];
	if(read_ist == indx)
		read_ist = 0;
	else
		read_ist++;
	return store;
}
template <class T>
T Stack<T>::top()
{
	return s[indx];
}
template <class T>
void Stack<T>::push(T val)
{
	if(is_Full())
	{
		std::cout << "Stack is full " << std::endl;
		exit(1);
	}
	
	s[++indx] = val;
}
template <class T>
T Stack<T>::pop()
{
	if(is_Empty())
	{
		std::cout << "Stack is Empty ";
		exit(1);
	}	
	return s[indx--];
}
template <class T>
bool Stack<T>::is_Full()
{
	if(indx >= SIZE-1)
		return true;
	return false;
}
template <class T>
bool Stack<T>::is_Empty()
{
	if(indx < 0)
		return true;
	return false;
}
struct find{
		int freq;
		char ch;
	};
struct char_nemonic{
	char c;
	std::string nemonic;
};
class TreeNode{
public:	
	int val;
	int freq;
	TreeNode *left ,*right, *parent;
	TreeNode(int val, int freq);
};
TreeNode::TreeNode(int val,  int freq)
{
	this->val  = val;
	this->freq = freq;
	
	left = right = NULL;
}
class Tree{
	TreeNode* root;
	TreeNode* tmp;
	std::string str;
	std::string code;
	std::string on, off;
	
	int brk;
	std::stack<char> chr;
	std::stack<char> nemonic;
	Stack<std::string> store;
	std::stack<std::string> temp;
	std::string rev;
	bool cond;
	char chh;
	
public:
	static int indx;
	Tree(std::string str = "");
	void Huffmen_Encode();
	void pre_order(char_nemonic* m,TreeNode* t = NULL);
	void Huffmen_Decod(std::string bin_code  = "", TreeNode* temp = NULL);
};
Tree::Tree(std::string str)
{
	this->str = str;
	root = NULL;
}
void Tree::Huffmen_Decod(std::string bin_code , TreeNode* temp)
{
	temp = root;
char on = '1';
char off = '0';
	for(int i = 0 ; i < bin_code.length(); i++)
	{
		if(bin_code[i] == off )
		{
			temp = temp->left;
		}
			
		else if(bin_code[i] == on)
		{
		
			temp = temp->right;
		}
		if(temp->right == NULL && temp->left == NULL)
		{
			std::cout << char(temp->val);
			temp = root;
		}		
	}
	
}
int Tree::indx = 0;
void Tree::pre_order(char_nemonic* m,  TreeNode* t)
{
	if(t == NULL)
	{
		code = "";
		t = root;
	}
	if(t->right == NULL && t->left == NULL)
	{
		code = "";
		
		tmp = t;
		on = "1";
		off = "0";
		while(tmp->parent != NULL)
		{
			if(tmp == tmp->parent->left)
				code += off;
			else if(tmp == tmp->parent->right)
				code+= on;
			
			tmp = tmp->parent;
		}
		rev = code;
		code  = "";
		int itr = 0;
		for(int i = rev.length()-1; i >= 0; i-- )
		{
			code += rev[i]; 
		}
		m[indx].c = t->val;
		m[indx].nemonic = code;
		
		temp.push(code);
		indx++;
	}
	if(t->left != NULL)
		pre_order(m , t->left);
	
	if(t->right != NULL)
		pre_order( m,  t->right);
	
	//std::cout << "Ret \n";
}
void Tree::Huffmen_Encode()
{
	
	std::string complete  = "";
	find f[str.length()];
	find swap;
	char c;
	int  count;
	 int indx = 0;
	 bool flag;
	for(int i = 0 ; i < str.length(); i++)
	{

		flag = false;
		
		count = 0;
		for(int k = 0; k < complete.length(); k++)
		{
			if(str[i] == complete[k])
			{
				flag = true;
				break;
			}
		}
		if(flag)
			continue;
		for(int j = i; j < str.length(); j++)
		{
			if(str[i] == str[j])
				count++;
		}
		complete += str[i];
		f[indx].ch = str[i];
		f[indx].freq = count;
		indx++;
	}
	brk = indx-1;
	for(int i = 0 ; i <= brk; i++)
	{
		for(int j = 0 ; j <= brk; j++)
		{
			if(f[i].freq < f[j].freq)
			{
				swap = f[i];
				f[i] = f[j];
				f[j] = swap;
			}
				
		}
	}
	for(int i = indx; i < str.length(); i++)
		f[i].freq = 0;
	
	for(int i  = 0; i < brk+1; i++)
	{
		std::cout << "char  is " << f[i].ch << " , and freq is " << f[i].freq << std::endl;
	}
	// Huffmen encoding starts here
	
	std::queue<TreeNode*> q;
	std::queue<TreeNode*> q2;
	
	for(int i = 0; i <= brk; i++)
	{
		TreeNode* t = new TreeNode(f[i].ch, f[i].freq);
		q.push(t);
	}
	TreeNode *child1, *child2, *hld;
	flag = false;
	while(!q.empty() || !q2.empty() )
	{
		flag = false;
		root =  child1 = q.front();
		q.pop();
		if(q.empty() && q2.empty())
		{
			break;
		}	
	
		child2 = q.front();
		q.pop();
		if(q.front() == q.back())
			flag = true;
		TreeNode* parent = new TreeNode(0, (child1->freq + child2->freq));
		parent->left = child1;
		parent->right = child2;
		child1->parent = child2->parent = parent;
		
		if(q.front() == q.back())
		{
			q2.push(q.front());
			q.pop();
		}		
		q2.push(parent);
		
		if(q.empty())
		{
			while(!q2.empty())
			{
				q.push(q2.front());
				q2.pop();
			}
		}
		 
	}
	root->parent = NULL;
	char_nemonic m[brk+1]; 
	pre_order(m);
	for(int i = 0; i <= brk; i++)
	{
		std::cout << "character " << m[i].c << " has binary value " << m[i].nemonic << std::endl;
	}
	code = "";
	for(int i = 0; i < str.length(); i++)
	{
		for(int j = 0; j <= brk; j++)
		{
			if(str[i] == m[j].c)
			{
				code += m[j].nemonic;
			}
		}
	}
	std::cout << "This is the list of binarycode of all string  \n" << code << std::endl;
	
	Huffmen_Decod(code);

}
int main()
{
	std::string encode = "My name is Muhammad Aamir KHan " ;
	Tree t(encode);
	t.Huffmen_Encode();
}
