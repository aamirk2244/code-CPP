#include<iostream>
class TreeNode{
public:
	int val;
	TreeNode *left , *right, *parent;
	TreeNode(int val, TreeNode* parent);
};
TreeNode::TreeNode(int val, TreeNode* parent)
{
	this->val = val;
	this->parent = parent;
	right  = left = NULL;
}
class BST{
	TreeNode *root, *current;
public:
	TreeNode* get_root(){return root;}
	BST(){root = current = NULL;}
	void insert(int val,bool flag = true,  TreeNode* root = NULL, TreeNode* parent = NULL);
	void In_order(TreeNode* temp = NULL);
	void del(int val,bool flag = true, TreeNode* curr= NULL, int* third_print = NULL);	
	void show_del(int val);
	bool search(int val, bool flag = true);
	TreeNode* MIN(TreeNode* min);
};
void BST::show_del(int val)
{
	std::cout << val << " is deleted Successfully " << std::endl;
}
void BST::insert(int val, bool flag, TreeNode* root, TreeNode* parent)
{
	if(this->root == NULL)
	{
		this->root = new TreeNode(val, parent);
		return;
	}
	if(flag)
		root = this->root;
	
	if(val == root->val)
	{
		std::cout << val << " is Duplicate. Which is  not Allowed " << std::endl;
		return;
	}
	if(val  < root->val )
	{
		if(root->left == NULL)
		{
			root->left = new TreeNode(val, root);
			return;
		}
		insert(val,0, root->left, root->left);
	}
	
	if(val > root->val)
	{
		if(root->right == NULL)
		{
			root->right = new TreeNode(val, root);
			return;
		}
		insert(val,0, root->right, root->right);
	}
}

void BST::del(int val,bool flag, TreeNode* curr, int* third_print)
{
	if(flag)
	{
		if(!search(val))
			throw "Sorry this value is not present in the list " ;
		
		curr = root;
	}
	// ist case
	if(root->left == NULL && root->right == NULL)
	{
		std::cout << root->val << " is deleted Successfully " << std::endl;
		delete root;
		root = curr = NULL;
		return;
	}
	if(val == curr->val && curr->left == NULL && curr->right == NULL)
	{
		if(curr->parent->right == curr)
			curr->parent->right = NULL;
		else if(curr->parent->left == curr)
			curr->parent->left = NULL;
		int dd = curr->val;
		delete curr;	
		curr = NULL;
		if(third_print != NULL)
		{
			show_del(*third_print);
			delete third_print;
			third_print = NULL;
			return;
		}
		show_del(dd);
		return;
	}
	// 2nd case
	if(val == curr->val && (curr->left == NULL || curr->right == NULL))
	{
		if(curr->right != NULL)
		{
			if(curr->parent == NULL)
			{
				curr->right->parent = curr->parent;
				root = curr->right;
			}
			else if(curr->parent->left == curr)
			{
				curr->right->parent = curr->parent;
				curr->parent->left = curr->right;
			}
			else if(curr->parent->right == curr)
			{
				
				curr->right->parent = curr->parent;
				curr->parent->right = curr->right;
			}
		}
		else if(curr->left != NULL)
		{
			if(curr->parent == NULL)
			{
				curr->left->parent = curr->parent;
				root = curr->left;
			}
			else if(curr->parent->right == curr)
			{
				curr->left->parent = curr->parent;
				curr->parent->right = curr->left;
			}
			else if(curr->parent->left == curr)
			{
				curr->left->parent = curr->parent;
				curr->parent->left = curr->left;
			}
		}
		int vall = curr->val;
		delete curr;
		curr = NULL;
		if(third_print != NULL)
		{
			show_del(*third_print);
			delete third_print;
			third_print = NULL;
			return;
		}

		show_del(vall);
		return;
	}
	// 3rd case
	if(val == curr->val && curr->right != NULL && curr->left != NULL)
	{
		third_print = new int;
		*third_print = curr->val;
		TreeNode* dell;
		dell = MIN(curr->right);
		curr->val = dell->val;
		del(dell->val,0,dell,third_print );
		return;
	}
	if(val < curr->val)
		del(val, 0,curr->left);
	else if(val > curr->val)
		del(val, 0,curr->right);
}
void BST::In_order(TreeNode* temp)
{
	if(root == NULL)
	{
		throw "Tree is Emtpy ] ";	
	}
	if(temp == NULL)
		temp = root;
	if(temp->left != NULL)
		In_order(temp->left);
	std::cout << temp->val << " ";
	if(temp->right != NULL)
		In_order(temp->right);
	
}
bool BST::search(int val, bool flag)
{
	if(flag)
	{
		if(root == NULL)
			throw "BST is empty";
		current = root;
	}
	if(val == current->val)
		return true;
	if(val < current->val)
	{
		current = current->left;
		if(current == NULL)
			return false;
	}
	if(val > current->val)
	{
		current = current->right;
		if(current == NULL)
			return false;
	}
	search(val, 0);
}
TreeNode* BST::MIN(TreeNode* min)
{
	if(root == NULL)
		throw "List is Empty ";
	if(min == NULL)
	{
		min = root;
	}	
	while(min->left != NULL)
		min = min->left;
	return min;
}
int main()
{
	BST t;
	int arr[11] = {7,3,2,0,4,5,10,8,56,12,44};
	try{
	for(int i  = 0 ; i < 11; i++)
		t.insert(arr[i]);	
	
	std::cout << "[ ";t.In_order();std::cout << "]\n";

	for(int i = 0; i < 11; i++)
	{
		t.del(arr[i]);
		std::cout << "[ ";t.In_order();std::cout << "]\n";
	
	}
	
	std::cout << "[ ";t.In_order();std::cout << "]\n";
	
	}catch(const char* msg){
		std::cout << msg << std::endl;
	}
	
}
