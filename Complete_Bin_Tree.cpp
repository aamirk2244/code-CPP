#include<iostream>
#include<queue>
class TreeNode{
public:
	int val;
	TreeNode *left, *right, *parent;
	TreeNode(int val, TreeNode* parent);
	
};
TreeNode::TreeNode(int val, TreeNode* parent)
{
	this->val = val;
	this->parent = parent;
	left = right = NULL;
}
class CBT{
				// CBT Complete binary tree
	
	TreeNode *current , *root;
public:
	CBT();
	void insert(int val , std::queue<TreeNode*> que, bool flag = true);		
	void BFS(TreeNode* curr, std::queue<TreeNode*> print, bool flag = true);
	TreeNode* get_root(){return root;}
	void del(int val, TreeNode* del = NULL);
	TreeNode* Search(int val, TreeNode* t = NULL);
	TreeNode* get_last_leaf();
	bool check(int val, TreeNode* t = NULL);
	void pre_order(TreeNode* t = NULL, bool flag = true);
};
CBT::CBT()
{
	current = root =  NULL;
}

void CBT::insert(int val, std::queue<TreeNode* > que, bool flag)
{
	if(flag)
	{
		while(!que.empty())
		{	
			que.pop();
		}
		que.push(root);
	}
	if(root == NULL)
	{
		root = new TreeNode(val, NULL);
		return;
	}
	if(!que.empty())
	{
		current = que.front();
		if(current->left == NULL)
		{
			current->left = new TreeNode(val, current);
			return;
		}
		if(current->right == NULL)
		{
			current->right = new TreeNode(val, current);
			return;
		}
		if(current->left != NULL)
			que.push(current->left);
		if(current->right != NULL)
			que.push(current->right);
		que.pop();
	}
	insert(val, que, 0);
	if(flag)
	{
		while(!que.empty())
			que.pop();
	}
	
}
void CBT::BFS(TreeNode* curr, std::queue<TreeNode*> print, bool flag)
{
	if(root == NULL)
		throw "Tree is empty ]\n";
	if(flag)
	{
		print.push(root);
	}
	if(print.empty())
		return;
	curr = print.front();
	std::cout << curr->val <<  " ";
	print.pop();
	if(curr->left != NULL)
	{
		print.push(curr->left);
	}
	if(curr->right != NULL)
	{
		print.push(curr->right);
	}
	
	BFS(curr, print, false);
	
}

void CBT::del(int val,  TreeNode* del)
{

	del = Search(val);
	TreeNode* last = get_last_leaf();

	if(del == root && del->left == NULL && del->right == NULL)
	{
		int val = root->val;
		delete root;
		root = NULL;
		std::cout << val << " is deleted Successfully " << std::endl;
		return;
	}
	if(last->parent->left == last)
		last->parent->left = NULL;
	else if(last->parent->right == last)
		last->parent->right = NULL;

	int save = del->val;
	del->val = last->val;
	delete last;
	last = NULL;
	std::cout << save << " is deleted Successfully " << std::endl;
	return;
}
TreeNode* CBT::Search(int val, TreeNode* t)
{
	if(!check(val))
		throw "Given value is not Present in the Tree \n";
	std::queue<TreeNode*> q;
	q.push(root);
	t = q.front();
	while(!q.empty())
	{
		
		if(t->val == val)
		{
			while(!q.empty())
				q.pop();
			
			return t;
		}
		if(t->left != NULL)
		{
			q.push(t->left);
			
		}
		if(t->right != NULL)
		{
			q.push(t->right);
		}
		q.pop();
		t = q.front();
	}
	
}
TreeNode* CBT::get_last_leaf()
{
	std::queue<TreeNode*> q;
	q.push(root);
	while(!q.empty())
	{
		current = q.front();
		if(current->left != NULL)
			q.push(current->left);
		if(current->right != NULL)
			q.push(current->right);
		
		if(q.front() ==  q.back())
			return q.front();
		q.pop();	
	}
}
bool CBT::check(int val, TreeNode* t)
{
	if(t == NULL)
		t = root;
	if(t->val == val)
		return true;
	if(t->left != NULL)
	{
		if(check(val, t->left))
			return true;
	}
	if(t->right != NULL)
	{
		if(check(val, t->right))
			return true;
	}
	return false;
}
void CBT::pre_order(TreeNode* t, bool flag)
{
	if(root == NULL)
		throw "Tree is empty ] \n";
	if(flag)
		t = root;
	std::cout << t->val << " ";
	if(t->left != NULL)
		pre_order(t->left, 0);
	if(t->right != NULL)
		pre_order(t->right, 0);
}

int main()
{
	CBT c;
	std::queue<TreeNode*> q;

	try{
		for(int i=  1; i <= 16; i++)
			c.insert(i,q);

	std::cout << "[ "; c.BFS(NULL, q);std::cout<<  "]\n";
	std::cout << "[ ";c.pre_order();std::cout << "]\n";
	std::cout << "_______________________________________\n";
	for(int i = 1; i<= 17; i++)
	{
		std::cout << "[ "; c.BFS(NULL, q);std::cout<<  "]\n";
		c.del(i);
	}
		
	
//	std::cout << "[ ";c.pre_order();std::cout << "]\n";
	}catch(const char* msg){
		std::cout << msg ;
	}
	return 0;
}
