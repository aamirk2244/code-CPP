// here is the link of theory video to understand insertion in AVL and Rotation Expalanation
//https://www.youtube.com/watch?v=jDM6_TnYIqE
#include<iostream>
class TreeNode{
public:
	int balance_factor;
	int val;
	
	TreeNode *left , *right, *parent;
	TreeNode(int val, TreeNode* parent);
};
TreeNode::TreeNode(int val, TreeNode* parent)
{
	this->val = val;
	this->parent = parent;
	left = right = NULL;
	balance_factor = 0;
}
class AVL{
	TreeNode* root;
	bool LL, RR, LR, RL;
	int left_depth, right_depth;
	int temp_left, temp_right;
	int set_left_depth( TreeNode* temp);
	int set_right_depth( TreeNode* temp);

public:
	AVL(){	root = NULL;temp_left = temp_right = 0;}
	void set_bool(){LL = RR  = LR = RL = false;}
	void insert(int val, bool flag = true, TreeNode* temp  = NULL);
	void Inorder(TreeNode* temp = NULL);
	void Pre_order(TreeNode* temp = NULL);
	TreeNode* Check_depth();
	int get_left_depth(TreeNode* temp){return (set_left_depth(temp->left) + 1);}
	int get_right_depth(TreeNode* temp){return (set_right_depth(temp->right) + 1);}
	TreeNode* get_root(){return root;}
	void LL_rotation(TreeNode* temp);
	void RR_rotation(TreeNode* temp);
	void RL_rotation(TreeNode* temp);
	void LR_rotation(TreeNode* temp);
	void update_balance_factor(TreeNode* temp);

};
void AVL::insert(int val, bool flag, TreeNode* temp)
{
	if(root == NULL)
	{
		root = new TreeNode(val, NULL);
		root->balance_factor = 0;
		
		return;
	}
	if(flag)
	{
		set_bool();
		temp = root;
	}
	if(val  < temp->val)
	{
		if(temp->left == NULL)
		{
			temp->left = new TreeNode(val, temp);
		
			if(temp->parent == NULL)
				return;
		
			
			TreeNode* dep = temp->left;
			TreeNode* mov;
			dep = dep->parent->parent;
			while(dep != NULL)
			{
				update_balance_factor(dep);
				dep = dep->parent;
			}
			dep = temp->left;
			dep = dep->parent->parent;
			while(dep != NULL)
			{
				if(dep->balance_factor < -1 || dep->balance_factor > 1 )
				{
					while(true)
					{
						mov = dep;
						if(val < mov->val)
						{
							mov = mov->left;
							if(val < mov->val)
							{
								mov = mov->left;
								LL = true;
								break;
							}
							if(val > mov->val)
							{
								mov = mov->right;
								LR = true;
								break;
							}
						}
						else if(val > mov->val)
						{
							mov = mov->right;
							if(val > mov->val)
							{
								mov = mov->right;
								RR = true;
								break;
							}
							if(val < mov->val)
							{
								mov = mov->left;
								RL = true;
								break;
							}
						}
						
					}
						
					if(RR)
						RR_rotation(dep);
					else if(RL)
						RL_rotation(dep);
					else if(LL)
						LL_rotation(dep);
					else if(LR)
						LR_rotation(dep);
					
					return;
				}
				dep = dep->parent;
			}
			return;
		}
		insert(val, 0, temp->left);
		return;
	}
	if(val > temp->val)
	{
		if(temp->right == NULL)
		{
			temp->right = new TreeNode(val, temp);
			TreeNode* dep = temp->right;
			TreeNode* mov;
			dep = dep->parent->parent;
			
			while(dep != NULL)
			{
				update_balance_factor(dep);
				dep = dep->parent;
			}
			dep = temp->right;
			dep = dep->parent->parent;
			while(dep != NULL)
			{
				if(dep->balance_factor < -1 || dep->balance_factor > 1 )
				{
					while(true)
					{
						mov = dep;
						if(val < mov->val)
						{
							mov = mov->left;
							if(val < mov->val)
							{
								mov = mov->left;
								LL = true;
								break;
							}
							if(val > mov->val)
							{
								mov = mov->right;
								LR = true;
								break;
							}
						}
						else if(val > mov->val)
						{
							mov = mov->right;
							if(val > mov->val)
							{
								mov = mov->right;
								RR = true;
								break;
							}
							if(val < mov->val)
							{
								mov = mov->left;
								RL = true;
								break;
							}
						}
						
					}
						
					if(RR)
						RR_rotation(dep);
					else if(RL)
						RL_rotation(dep);
					else if(LL)
						LL_rotation(dep);
					else if(LR)
						LR_rotation(dep);
					
					return;
					// unbalance
				}
				dep = dep->parent;
			}
			
			return;
		}
		insert(val, 0, temp->right);
		
	}
}
void AVL::LL_rotation(TreeNode* temp)
{
	// LL Imbalance
	bool flag = false;
	bool connect_left = false;
	bool connect_right = false;
	std::cout << "(LL Rotation in Active) Rotating Towards Right \n";
	temp->balance_factor = 0;
	TreeNode* parent = temp->parent;
	if(parent != NULL)
		flag = true;
	
	if(flag)
	{
		if(parent->right == temp)
		{
			parent->right = NULL;
			connect_right = true;
		}
		else if(parent->left == temp)
		{
			parent->left = NULL;
			connect_left = true;
		}
	}
	TreeNode* mid = temp->left;
	TreeNode* end = temp->left->left;
	TreeNode* right = mid->right;
	temp->left =  NULL;
	mid->right = temp;
	temp->parent = mid;
	mid->left = end;
	end->parent = mid;
	temp = mid;
	temp->parent = NULL;
	mid  = mid->right;
	while(mid->left != NULL)
		mid = mid->left;
	mid->left = right;
	//// 
	if(connect_right)
	{
		parent->right = temp;
		temp->parent = parent;
	}
	else if(connect_left)
	{
		parent->left = temp;
		temp->parent = parent;
	}

	while(temp->parent != NULL)
		temp=  temp->parent;
	root = temp;
}
void AVL::RR_rotation(TreeNode* temp)
{
	// RR Imbalance
	bool flag = false;
	bool connect_left = false;
	bool connect_right = false;
	std::cout << "(RR Rotation in Active) Rotating Towards Left \n";
	temp->balance_factor = 0;
	TreeNode* p = temp->parent;
	TreeNode* parent = temp->parent;
	if(parent != NULL)
		flag = true;
	
	if(flag)
	{
		if(parent->left == temp)
		{
			parent->left = NULL;
			connect_left = true;
		}
		else if(parent->right == temp)
		{
			parent->right = NULL;
			connect_right = true;
		}
	}
	TreeNode* mid = temp->right;
	TreeNode* end = temp->right->right;
	TreeNode* left = mid->left;
	temp->right =  NULL;
	mid->left = temp;
	temp->parent = mid;
	mid->right = end;
	end->parent = mid;
	temp = mid;
	temp->parent = NULL;
	mid  = mid->left;
	while(mid->right != NULL)
		mid = mid->right;
	mid->right = left;
	if(connect_right)
	{
		parent->right = temp;
		temp->parent = parent;
	}
	else if(connect_left)
	{
		parent->left = temp;
		temp->parent = parent;
	}
	while(temp->parent != NULL)
		temp=  temp->parent;
	root = temp;
}
void AVL::RL_rotation(TreeNode* temp)
{
	// (Right subtree will remain same) ist replace the head node with the last and the head node would go towards left , and manage all subtrees
	
	bool flag = false;
	bool connect_left  = false;
	bool connect_right = false;
	std::cout << "(RL Rotation in Active) \n";
	temp->balance_factor = 0;
	// LR(Left Right) Imbalane
	TreeNode* p = temp->parent;
	if(p != NULL)
		flag = true;

	TreeNode* parent = temp->parent;
	if(flag)
	{
	
		if(parent->left == temp)
		{
	
			parent->left = NULL;
			connect_left = true;
		}
		else if(parent->right == temp)
		{
	
			parent->right = NULL;
			connect_right = true;
		}
		
	}
	TreeNode* mov = temp->right->left;
	TreeNode* right = mov->right;
	TreeNode* left = mov->left;
	TreeNode* temp_right = temp->right;
	temp->right = temp_right->left = NULL;
	mov->left = temp;
	temp->parent = mov;
	if(flag)
	{
		if(connect_left)
		{
			mov->parent = parent;
			parent->left = mov;
		}
		else if(connect_right)
		{
			mov->parent = parent;
			parent->right = mov;
		}
	}
	else
		mov->parent = NULL;
	
	mov->right = temp_right;
	temp_right->parent = mov;
	temp = mov;
	
	mov = mov->right;
	
	while(mov->left != NULL)
		mov = mov->left;
	mov->left = right;
	if(right != NULL)
		right->parent = mov;
	
	mov = temp->left;
	while(mov->right != NULL)
		mov = mov->right;
	mov->right = left;
	if(left != NULL)
		left->parent = mov;
	while(temp->parent != NULL)
		temp = temp->parent;
	root = temp;
}
void AVL::LR_rotation(TreeNode* temp)
{
	// (left subtree will remain same) ist replace the head node with the last and the head node would go towards right, and manage all subtrees
	bool flag = false;
	bool connect_left  = false;
	bool connect_right = false;
	temp->balance_factor = 0;
	// LR(Left Right) Imbalane
	std::cout << "(LR Rotation in Active) \n";
	TreeNode* p = temp->parent;
	
	if(p != NULL)
		flag = true;

	TreeNode* mov = temp->left->right;
	TreeNode* parent = temp->parent;
	if(flag)
	{
		if(parent->right == temp)
		{
			parent->right = NULL;
			connect_right = true;
		}
		else if(parent->left == temp)
		{
			parent->left = NULL;
			connect_left = true;
		}
			
	}
	TreeNode* right = mov->right;
	TreeNode* left = mov->left;
	TreeNode* temp_left = temp->left;
	temp->left = temp_left->right = NULL;
	
	mov->right = temp;
	temp->parent = mov;
	if(flag)
	{
		mov->parent = parent;
		if(connect_right)
			parent->right = mov;
		else if(connect_left)
			parent->left = mov;
	}
	else
		mov->parent = NULL;	
	mov->left = temp_left ;
	temp_left->parent = mov;
	temp = mov;
	mov = mov->right;
	while(mov->left != NULL)
		mov = mov->left;
	
	mov->left = right;
	if(right != NULL)
		right->parent = mov;
	mov = temp->left;
	while(mov->right != NULL)
		mov = mov->right;
	mov->right = left;
	if(left != NULL)
		left->parent = mov;
	while(temp->parent != NULL)
	{
		temp = temp->parent;
	}
	root = temp;

}
void AVL::Inorder(TreeNode* temp)
{
	if(root == NULL)
		return;
	if(temp == NULL)
		temp = root;
	if(temp->left != NULL)
		Inorder(temp->left);
	
	std::cout << temp->val << " ";
	if(temp->right != NULL)
		Inorder(temp->right);
}
int AVL::set_left_depth(TreeNode* temp)
{
	if(temp == NULL)
		return -1;

	int ldepth = set_right_depth(temp->left);
	int rdepth = set_right_depth(temp->right);
	if(ldepth > rdepth)
		return (ldepth + 1);
	return (rdepth + 1);
}
int AVL::set_right_depth(TreeNode* temp)
{
	if(temp == NULL)
		return -1;
	
	int ldepth = set_right_depth(temp->left);
	int rdepth = set_right_depth( temp->right);
	if(ldepth > rdepth)
		return (ldepth + 1);
	return (rdepth + 1);
}
void AVL::Pre_order(TreeNode* temp)
{
	if(temp == NULL)
		temp = root;
		
	std::cout << temp->val << " ";
	if(temp->left != NULL)
		Pre_order(temp->left);
	if(temp->right != NULL)
		Pre_order(temp->right);
	
}
void AVL::update_balance_factor(TreeNode* temp)
{
	temp->balance_factor = get_left_depth(temp) - get_right_depth(temp);
	
}
int main()
{
	
	AVL v;
	v.insert(40);
	v.insert(20);
	v.insert(10);
	v.insert(25);
	v.insert(30);
	v.insert(22);
	v.insert(50);
	v.insert(60);
std::cout << "\nPre Order\n[ ";v.Pre_order();std::cout << "]\n";
}
