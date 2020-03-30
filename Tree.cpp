#include<iostream>
int summ = 0;
class List;
class TreeNode;
class node;
class List{
	node *current, *head;
public:
	List();
	void add(TreeNode* val);
	void print();
};
class TreeNode{

	
public:
	TreeNode* left;
	TreeNode* right;
	int val;
	TreeNode(int val);	
	void pre_order(List &l);
	void post_order();
	void in_order();
	void dfs();
	void sum();
	int get_sum();
};

TreeNode::TreeNode(int val)
{
	this->val = val;
	left = right = NULL;
}
void TreeNode::pre_order(List &l)
{
	static int i = 0;
	if(!i)
	{
				std::cout << "Pre _order " << std::endl;
	i++;
	}
	std::cout << val <<std::endl;
	std::cout << "Sum is " << summ << std::endl;
	
	if(left != NULL)
	{
		std::cout << "This is left " ;
		l.add(left);
		left->pre_order(l);
	}
	if(right != NULL)
	{
		std::cout << "This is right " ;
		l.add(right);
		right->pre_order(l);
	}
	
	return;
	
}
/*
void TreeNode::dfs()
{
	TreeNode* temp;
	while(!is_empty)
	{
		temp = q.dequeue();
		std::cout << temp.val << std::endl;
		if(temp.left)
			q.enqueue(temp.left);
		if(temp.right)
			q.enqueue(temp.right);
	}
}
*/
void TreeNode::post_order()
{
	static int i = 0;
	if(!i)
	{
				std::cout << "Post _order " << std::endl;
	i++;
	}
	if(left != NULL)
		left->post_order();
	if(right != NULL)
		right->post_order();
	
	std::cout << val << std::endl;
	return;
}
void TreeNode::in_order()
{
	static int i = 0; 
	if(!i)
	{
		std::cout  << "In_order  " << std::endl;
		i++; 
	}
	if(left != NULL)
		left->in_order();
	
	std::cout << val << std::endl;
	
	if(right != NULL)
		right->in_order();
		
	return;
}
void TreeNode::sum()
{
	summ += val;
	std::cout << val <<std::endl;
	if(left != NULL)
	{
		left->sum();
	}
	if(right != NULL)
	{
		right->sum();
	}
	
	
}
int TreeNode::get_sum()
{
	return summ;
}
class node{
public:
	node* next;
	TreeNode* val;
	node(TreeNode* val);
};
node::node(TreeNode* val)
{
	this->val = val;
	next = NULL;
}
List::List()
{
	head = current = NULL;
}
void List::add(TreeNode* val)
{
	
	if(head == NULL)
	{
		head = new node(val);
		current = head;
		return;
	}
	node* n = new node(val);
	current->next = n;
	current = current->next;
}
void List::print()
{
	std::cout << "Let's Save whole tree into the List " << std::endl;
	current = head;
	std::cout << "[ ";
	while(current != NULL)
	{
		std::cout << current->val->val << " ";
		current = current->next; 
	}
	std::cout << "]" << std::endl;
	
}
int main()
{
	
	TreeNode* t = new TreeNode(1);
	List l;
	l.add(t);
	t->right = new TreeNode(2);
//	l.add(t->right);
	t->right->right = new TreeNode(55);
//	l.add(t->right->right);
	
	t->right->right->left = new TreeNode(87);
//	l.add(t->right->right->left);

	t->right->right->right = new TreeNode(101);
//	l.add(t->right->right->right);

	t->right->right->right->right = new TreeNode(1019);
//	l.add(t->right->right->right->right);
	
	t->right->right->right->left = new TreeNode(200);
//	l.add(t->right->right->right->left);

	t->left = new TreeNode(3);
//	l.add(t->left);
	
	t->left->left = new TreeNode(5);
//	l.add(t->left->left);

	t->left->right = new TreeNode(15);
//	l.add(t->left->right);
t->pre_order(l);
	std::cout << std::endl;	
	t->post_order();
	std::cout << std::endl;
	t->in_order();
	t->sum();
	std::cout << "Total sum of the Tree is --> " << t->get_sum() << std::endl;
	l.print();
	
	//t.left = new TreeNode(5);
	
	//t.left->left = new TreeNode(10);
	std::cin.get();
	return 0;
}
