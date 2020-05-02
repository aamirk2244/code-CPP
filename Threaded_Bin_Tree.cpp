#include<iostream>
class TreeNode{
public:
	TreeNode *left , *right, *parent;
	bool r_thread, l_thread;
	int val;
	TreeNode(int val, TreeNode* parent);
};
TreeNode::TreeNode(int val, TreeNode* parent)
{
	left  = right = NULL;
	this->parent = parent;
	r_thread = l_thread = false;
	this->val = val;
	
}	// TBT threaded binary tree
class TBT{
public:
	TreeNode *root, *temp;
public:
	TBT(){ root = NULL;}
	void show_del(int p){std::cout << "\n" << p << " is deleted successfully"<< std::endl;};
	TreeNode* successor(TreeNode* t);
	TreeNode* predecessor(TreeNode* t);
	void insert(int val, TreeNode* t = NULL, bool flag = true);
	void print(TreeNode* t = NULL);
	TreeNode* find_next_traversal_node(TreeNode* t);
	TreeNode* get_root(){return root;};
	void del(int val, bool ist_time = true, TreeNode* d = NULL, int* msg = NULL);
	TreeNode* Search(int val);
	TreeNode* Min(TreeNode* t = NULL);
};
TreeNode* TBT::Min(TreeNode* t)
{
	if(t == NULL)
		 t = root;
	while(!(t->l_thread ))
		t = t->left;
	return t;
}
TreeNode* TBT::Search(int val)
{
	temp = root;
	while(temp->left != NULL )
		 temp  = temp->left;
	while(temp != NULL)
	{
		if(val == temp->val)
			return temp;
		temp = find_next_traversal_node(temp);
	}
	return NULL;
	
}
void TBT::print(TreeNode* t)
{
	if(root == NULL)
	{
		std::cout << "\nTree is Empty \n[]\n";
		return;
	}
	if(t == NULL)
		t = root;
	while(!(t->l_thread))
	{
		if(t->left == NULL)
			break;
		t  = t->left;
	}
	std::cout << "[ ";
	while(t != NULL)
	{
		std::cout << t->val << " ";
		t = find_next_traversal_node(t);
	}
	std::cout << "]\n";
}
TreeNode* TBT::find_next_traversal_node(TreeNode* t)
{
	if(t == NULL)
		return NULL;
	if(t->r_thread == true)
		return t->right;
	t = t->right;
	if(t == NULL)
		return NULL;
	while (t->l_thread != true) {
		t = t->left;
	}
	return t;	

}

void TBT::insert(int val, TreeNode* t, bool flag)
{
	if(root == NULL)
	{
		root = new TreeNode(val, NULL);
		return;
	}
	if(flag)
	{
		t = root;
		flag = false;
	}
	if(val < t->val)
	{
		if(t->l_thread == true || t->left == NULL)
		{
			t->l_thread = false;
			t->left = new TreeNode(val, t);
			temp = t->left;
			temp->right = successor(temp);
			temp->left = predecessor(temp);
				//std::cin.get();
		
			if(temp->right != NULL)
				temp->r_thread = true;
			else 
				temp->r_thread = false;
			if(temp->left != NULL)
				temp->l_thread = true;
			else 
				temp->l_thread = false;
				
			return;
		}
		insert(val, t->left, flag);
	}
	if(val > t->val)
	{
		if(t->r_thread == true || t->right == NULL)
		{
			t->r_thread = false;
			t->right = new TreeNode(val, t);
			temp = t->right;
			temp->right = successor(temp);
			temp->left = predecessor(temp);
			if(temp->right != NULL)
				temp->r_thread = true;
			else 
				temp->r_thread = false;
			if(temp->left != NULL)
				temp->l_thread = true;
			else 
				temp->l_thread = false;
				
			return;
		}
		insert(val, t->right,flag);
	}
	
}
TreeNode* TBT::successor(TreeNode* t)
{
	TreeNode* mov = t;
	if(t->parent == NULL)
		return NULL;
	// t->rthread means there is no right child
	if(t->right == NULL || t->r_thread)
	{
		mov = t->parent;
		while(t->val > mov->val)
		{
			mov = mov->parent;
			if(mov == NULL)
				break;
		}
		if( mov != NULL && mov->val < t->val)
			return NULL;
		return mov;
	}
	if(t->right != NULL)
	{
		t = t->right ;
		while(t->left != NULL)
			t = t->left;
		return t;
	}
}
TreeNode* TBT::predecessor(TreeNode* t)
{
	TreeNode* mov = t;
	if(t->parent == NULL && t->left == NULL)
		return NULL;
	if(t->left == NULL || t->l_thread)
	{
		mov = t->parent;
		while(t->val < mov->val)
		{
			mov = mov->parent;
			if(mov == NULL)
				break;
		}
		if( mov != NULL && mov->val > t->val)
			return NULL;
		return mov;
	}
	if(t->left != NULL)
	{
		t = t->left ;
		while(t->right != NULL)
			t = t->right;
		return t;
	}
}
void TBT::del(int val, bool ist_time, TreeNode* d, int* msg)
{
	if(ist_time)
	{
		// for one node
		if(val == root->val && (root->left == NULL || root->l_thread)  && (root->right == NULL || root->r_thread) )
		{
			delete root;
			root = NULL;
			return;
		}
		d = Search(val);
		if(d == NULL)
		{
			std::cout << "\nSorry " << val << " is not present in the tree  " << std::endl;
			return;
		}

	}
	// case 1	// for no child
	if( (d->l_thread && d->r_thread) ||  (d->l_thread && d->right == NULL) || (d->r_thread && d->left == NULL))
	{
		// above if statement means if left and right are both NULL or have a thread (meaning having no childs)
		
		if(d  ==  d->parent->left)
		{
			d->parent->left = NULL;
			d->parent->left = predecessor(d->parent);
			if(d->parent->left == NULL)
				d->parent->l_thread = false;
			else
				d->parent->l_thread = true;
		}
		if(d  ==  d->parent->right)
		{
			
			d->parent->right = NULL;
			d->parent->right = successor(d->parent);
			if(d->parent->right == NULL)
				d->parent->r_thread = false;
			else
				d->parent->r_thread = true;
		}
	
		delete d;
		d = NULL;
		if(msg == NULL)
			show_del(val);
		else
			 show_del(*msg);
		return;
	}
	// case 2	if one child is present. in this case r_thread is true if there is no right child and is false if its right is nULL or have child
	// same logic for left one
	if((!d->l_thread && d->left != NULL && (d->r_thread || d->right == NULL)))
	{
		// if left have child and right is NULL or have a thread(means successor)
		TreeNode* yes_pointing_from_left = NULL;
		TreeNode* yes_pointing_from_right = NULL;
		
		
		temp = root;
		while(temp->left != NULL)
			temp = temp->left;
		// thread should always from bottom to top. not from top to bottom
		while(temp != NULL)
		{
			if((temp != d) && (temp->l_thread && temp->left == d))
			{
				yes_pointing_from_left = temp;
			}
			if((temp != d) && (temp->r_thread && temp->right == d))
			{
				yes_pointing_from_right= temp;
			}
			
			
			temp = find_next_traversal_node(temp);
		}
		// if deleting root
		if((d == root) && (d->left != NULL))
			root = root->left;
		else if((d== root ) && (d->right != NULL))
			root = root->right;
		else
		{
			if(d == d->parent->right)
			{
				d->parent->right = d->left;
				d->left->parent = d->parent;
			}
			if(d == d->parent->left)
			{
				d->parent->left = d->left;
				d->left->parent = d->parent;
			}
	
		}
				
		delete d;
		d = NULL;
		if(msg == NULL)
			show_del(val);
		else
			show_del(*msg);
		if(yes_pointing_from_left != NULL)
		{
			yes_pointing_from_left->left = predecessor(yes_pointing_from_left);
			if(yes_pointing_from_left->left == NULL)
				yes_pointing_from_left->l_thread = false;
			else
				yes_pointing_from_left->l_thread = true;
			
		}
		if(yes_pointing_from_right != NULL)
		{
			std::cout << yes_pointing_from_right->val << std::endl;
			yes_pointing_from_right->right = successor(yes_pointing_from_right);
			if(yes_pointing_from_right->right == NULL)
				yes_pointing_from_right->r_thread = false;
			else
				yes_pointing_from_right->r_thread = true;
			
		}
		return;
	}
	if((d->left == NULL || d->l_thread) && (d->right != NULL && !d->r_thread))
	{
		
		// if right have child and left is NULL or have a thread(means successor)
		TreeNode* yes_pointing_from_left = NULL;
		TreeNode* yes_pointing_from_right = NULL;
		temp = root;
		while(temp->left != NULL)
			temp = temp->left;
		while(temp != NULL)
		{
			if((temp != d) && (temp->l_thread && temp->left == d))
			{
				yes_pointing_from_left = temp;
				yes_pointing_from_left->left = NULL;
			}
			if((temp != d) && (temp->r_thread && temp->right == d))
			{
				yes_pointing_from_right= temp;
				yes_pointing_from_right->right = NULL;
			}
			
			
			temp = find_next_traversal_node(temp);
			
		}
		// if deleting root
		if((d == root) && (d->left != NULL))
			root = root->left;
		else if((d== root ) && (d->right != NULL))
			root = root->right;
		else
		{
			if(d == d->parent->right)
			{
				d->parent->right = d->right;
				d->right->parent = d->parent;
			}
			if(d == d->parent->left)
			{
				d->parent->left = d->right;
				d->right->parent = d->parent;
			}
		
		}
		delete d;
		d = NULL;
		if(msg == NULL)
			show_del(val);
		else
			show_del(*msg);
		if(yes_pointing_from_left != NULL)
		{
			yes_pointing_from_left->left = predecessor(yes_pointing_from_left);
			if(yes_pointing_from_left->left == NULL)
				yes_pointing_from_left->l_thread = false;
			else
				yes_pointing_from_left->l_thread = true;
			
		}
		if(yes_pointing_from_right != NULL)
		{
			yes_pointing_from_left->right = successor(yes_pointing_from_right);
			if(yes_pointing_from_right->right == NULL)
				yes_pointing_from_right->r_thread = false;
			else
				yes_pointing_from_right->r_thread = true;
			
		}
		return;
	}
	// case 3 if right and left child both are present
	temp = Min(d->right); 
	d->val = temp->val;
	msg = new int;
	*msg = val;
	del(d->val, 0, temp, msg);
}
int main()
{
	TBT t;
	t.insert(8);
	t.insert(3);
	t.insert(1);
	t.insert(6);
	t.insert(4);
	t.insert(7);
	t.insert(10);
	t.insert(14);
	t.insert(13);
	t.print();
	t.del(100);
	t.del(8);
	t.print();
	t.del(3);
	t.print();
	t.del(6);
	t.print();
	t.del(7);
	t.print();
	t.del(13);
	t.print();
	t.del(1);
	t.print();
	t.del(10);
	t.print();
	t.del(4);
	t.print();
	t.del(14);
	t.print();
	return 0;	
	
}
