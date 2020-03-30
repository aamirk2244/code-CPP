#include<iostream>
class TreeNode{
public:
	TreeNode *left, *right, *parent;
	int val;
	TreeNode(int val);	
};
TreeNode::TreeNode(int val)
{
	this->val = val;
	left = right = parent = NULL;
}
class BST{
	int hold;
public:
	TreeNode *root, *temp;
	BST();
	void set_temp();
	void insert(int val, TreeNode* &t);
	void Pre_order(TreeNode* &t);	
	void Inorder(TreeNode* &t);
	void Post_order(TreeNode* &t);
	void del(int val,TreeNode* &t,  bool check = 1);
	TreeNode* min(TreeNode* &t);
	TreeNode* max(TreeNode* &t);
	bool Search(int val);
	int Predecessor(int val, TreeNode* &t, int BREAK = 0, bool check = 1, int count  = 1);
	int Successor(int val, TreeNode* &t, int BREAK = 0, bool check = 1, int count  = 1);
	
};
BST::BST()
{
	root = temp =  NULL;
}
void BST::insert(int val, TreeNode* &r)
{
	if(r == NULL)
	{
		r = new TreeNode(val);
		temp = r;
		return;
	}
	if(val < r->val)
	{
		if(r->left == NULL)
		{
			r->left = new TreeNode(val);
			r->left->parent = r;
		}
		else	
			insert(val, r->left);	
	}
	else{
		if(r->right == NULL)
		{
			r->right  = new TreeNode(val);
			r->right->parent = r;
		}
		else
			insert(val, r->right);
	}
}
void BST::set_temp()
{
	temp = root;
}                           
int BST::Predecessor(int  val , TreeNode* &t,int BREAK , bool check, int count)
{
	if(check)
	{
		if(!Search(val))
			throw "Predecessor doesn't exists. Because the Given value is not Present in the Tree";
		set_temp();
	}
	// I used break for Returning the Saved Predecessor value in Hold at the time of ist stack called 
	if(root->val < val && check)
	{ 
		Predecessor(val, t->right, BREAK+1, 0, 0);
		if(BREAK == 0)
			return hold;
	}
	//std::cout << "This is value of T " << t << std::endl;
	if(t->val == val && t->left == NULL)
		throw "Predecessor Doesn't Exists Because The Given value Has NO LEFT Child ";
	
	if(t->val == val)
		hold = max(t->left)->val;
	else
	{
		if(t->left != NULL)
		{
			Predecessor(val, t->left,BREAK+1 , 0,0);
			if(BREAK == 0)
				return hold;
		}
		if(t->right != NULL)
		{
			Predecessor(val, t->right,BREAK+1, 0,0);
			if(BREAK == 0)
				return hold;
		}	
	
	}
	if(BREAK == 0)
		return hold;
}
int BST::Successor(int  val , TreeNode* &t,int BREAK , bool check, int count)
{
	if(check)
	{
		if(!Search(val))
			throw "Successor doesn't exists. Because the Given value is not Present in the Tree";
		set_temp();
	}
	// I used break for Returning the Saved Successor value in Hold at the time of ist stack called 
	if(root->val < val && check)
	{
		Successor(val, t->right, BREAK+1, 0, 0);
		if(BREAK == 0)
			return hold;
	}
		
	if(t->val == val && t->right == NULL)
		throw "Successor Doesn't Exists Because The Given value Has NO Right Child ";
	
	if(t->val == val)
		hold = min(t->right)->val;
	else
	{
		if(t->left != NULL)
		{
			Successor(val, t->left,BREAK+1 , 0,0);
			if(BREAK == 0)
				return hold;
		}
		if(t->right != NULL)
		{
			Successor(val, t->right,BREAK+1, 0,0);
			if(BREAK == 0)
				return hold;
		}	
	
	}
	if(BREAK == 0)
		return hold;
}
bool BST::Search(int val)
{
	if(val == temp->val)
		return true;
	
	if(val < temp->val)
	{
		temp = temp->left;
		if(temp == NULL)
			return false;
	}
	if(val > temp->val)
	{
		temp = temp->right;
		if(temp == NULL)
			return false;
	}
	
	Search(val);
	
}
TreeNode* BST::min(TreeNode* &t)
{
	if(t->left == NULL)
		return t;
	min(t->left);
	
}
TreeNode* BST::max(TreeNode* &t)
{
	if(t->right == NULL)
		return t;
	else
		max(t->right);
}
void BST::del(int val, TreeNode* &t, bool check)
{
	if(check)
	{
		if(!(Search(val)))
		{
			std::cout << val <<  " is not Present in the Tree " << std::endl;
			return;
		}
	}
	if(t->val == val)
	{
		if(t->left == NULL && t->right == NULL)
		{
			if(t->parent->right == t)
			{
			
				t->parent->right = NULL;
				std::cout << t->val << " is deleted Successfully " << std::endl;
				delete t;
				t = NULL;
				return;
			}
			else if(t->parent->left == t)
			{
				t->parent->left = NULL;
				std::cout << t->val << " is deleted Successfully " << std::endl;
				delete t;
				t = NULL;
				return;
			}
		}
		else if(t->left == NULL )
		{
			TreeNode* d = t;
			if(t->parent->left == t)
			{
				t->parent->left = t->right;
				t->right->parent = t->parent;
				std::cout << d->val << " is deleted Successfully " << std::endl;
				delete d;
				d = NULL;
			}
			return;
		}
		else if(t->right == NULL)
		{
			
			std::cout << "This is my parent " << t->parent->val << std::endl;
			TreeNode* d = t;
			if(t->parent->right == t)
			{
				t->parent->right = t->left;
				t->left->parent = t->parent;
				std::cout << d->val << " is deleted Successfully " << std::endl;
			
				delete d;
				d = NULL;
				return;
			}
		}
		else if(t->right != NULL & t->left != NULL)
		{
			if(t == root)
				root = t;
			TreeNode* mini = t;
			int save = t->val;
			mini = min(mini->right);
			if(mini->right == NULL)
			{
				mini->parent->left = NULL;
				t->val = mini->val;
				delete mini;
				mini = NULL;
				std::cout << save << " is deleted Successfully " << std::endl;
				return;
			}
			else if(mini->right != NULL)
			{
				t->val = mini->val;
				TreeNode* d = mini;
				mini->parent->left = mini->right;
				mini->right->parent = mini->parent;
				delete d;
				d = NULL;
				std::cout << save << " is deleted Successfully " << std::endl;
				return;
			}
		
		}
	}
	if(t->left != NULL)
		del(val, t->left, 0);
	if(t->right != NULL)
		del(val, t->right, 0);
}
void BST::Pre_order(TreeNode* &t)
{
	std::cout << t->val << std::endl;
	if(t->left != NULL)
		Pre_order(t->left);
	
	if(t->right != NULL)
		Pre_order(t->right);
	
}
void BST::Inorder(TreeNode* &t)
{
	if(t->left != NULL)
		Inorder(t->left);
	std::cout << t->val << std::endl;

	if(t->right != NULL)
		Inorder(t->right);
}
void BST::Post_order(TreeNode* &t)
{
	if(t->left != NULL)
		Post_order(t->left);
	
	if(t->right != NULL)
		Post_order(t->right);
	std::cout << t->val << std::endl;

}
int main()
{
	BST t;
	t.insert(23,t.root);
	t.insert(12,t.root);
	t.insert(31,t.root);
	t.insert(3,t.root);
	t.insert(15,t.root);
	t.insert(29,t.root);
	t.insert(88,t.root);
	t.insert(7,t.root);
	t.insert(53,t.root);
	std::cout << "pre order ????????????????????? " << std::endl;
	t.set_temp();
	t.Pre_order(t.temp);
	std::cout << "in order :::::::::: " << std::endl;
	t.set_temp();
	t.Inorder(t.temp);
	std::cout << "Post _order ____________________________ " << std::endl;
	t.set_temp();
	t.Post_order(t.temp);
	t.set_temp();
	std::cout << "This is the minimum value in the TREE -->  " << (t.min(t.temp))->val << std::endl;
	t.set_temp();
	std::cout << "This is the MAXIMUM value in the TREE -->  " << (t.max(t.temp))->val << std::endl;
	int search = 0;
	if(t.Search(search))
	std::cout << "Yes. " << search << "  is Present in the TREE " << std::endl;
	else
	 std::cout << "No. "  << search << " is not Present in The TREE " << std::endl; 
	t.set_temp();	
	std::cout<< t.Search(88) << std::endl;
	t.set_temp();
	int predeccessor = 23;
	try{
		std::cout << "Predecessor of " << predeccessor << " is -->  " << t.Predecessor(predeccessor, t.temp) << std::endl;
	
	}catch(const char* msg ){
		std::cout << msg << std::endl;
	}
	t.set_temp();
	int successor = 31;
	try{
		std::cout << "Successor of " << successor << " is -->  " << t.Successor(successor, t.temp) << std::endl;
	
	}catch(const char* msg2 ){
		std::cout << msg2 << std::endl;
	}
	t.set_temp();
	t.del(23, t.temp);
	t.set_temp();
	t.Inorder(t.temp);
	t.set_temp();
	
	return 0;	
}
