#include<iostream>
#include<string>

using namespace std;

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == NULL)
        return;

    showTrunks(p->prev);

    cout << p->str;
}

class node
{
    public:
        int info;
        node *left;
        node *right;
        
    node(int val)
    {
        info = val;
        left = NULL;
        right = NULL;
    }
};

node* parent(node* curr, node* p, node* par)
{
    if(curr == NULL)
        return NULL;

    if (curr == p)
    {
        return par;
    }
    else
    {
        node *t = NULL;
        t = parent(curr->left, p, curr);
        if(t!= NULL)
            return t;
        else
        {
            t = parent(curr->right, p, curr);
            return t;
        }

    }
}

node* sibling(node* root, node* p)
{
    node* par = parent(root, p, root);

    if (par->left == p)
        return par->right;
    else 
        return par->left;
}

void deleteTree(node* leaf)
{
    if (leaf != NULL)
    {
        deleteTree(leaf->left);
        deleteTree(leaf->right);
        delete leaf;
    }
}

int getLevel(node *ptr,int val,int level) 
{
   if (ptr == NULL)
      return 0;
   if (ptr->info == val)
      return level;
   return getLevel(ptr->left, val, level+1) | 
            getLevel(ptr->right, val, level+1);
}

int maxDepth(node* node)  
{  
    if (node == NULL)  
        return -1;  
    else
    {  
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->left);  
        int rDepth = maxDepth(node->right);  
      
        /* use the larger one */
        if (lDepth > rDepth)  
            return(lDepth + 1);  
        else return(rDepth + 1);  
    }  
}

void preOrder(node *n)
{
    if(n == NULL)
        return;
    
    cout<<n->info<<"\t";
    preOrder(n->left);
    preOrder(n->right);
}

void inOrder(node *n)
{
    if(n == NULL)
        return;

    inOrder(n->left);
    cout<<n->info<<"\t";
    inOrder(n->right);
}

void postOrder(node *n)
{
    if(n == NULL)
        return;
    
    postOrder(n->left);
    postOrder(n->right);
    cout<<n->info<<"\t";
}

// Recursive function to print binary tree
// It uses inorder traversal
void printTree(node *root, Trunk *prev, bool isRight)
{
    if (root == NULL)
        return;
    
    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isRight)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->info << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}

int main(int argc, const char** argv) {
    node *root = new node(5);
    root->left = new node(2);
    root->right = new node(7);
    root->right->left = new node(3);
    root->right->right = new node(9);
    root->left->left = new node(6);
    root->left->left->right = new node(1);

    printTree(root, NULL, false);
    
    // Find Parent
    node *n = parent(root, root->right, root);
    cout<<"Parent is: "<<n->info<<endl;

    // Find sibling
    node *sib = sibling(root, root->right->left); //sibling of 3 (which is 9)
    cout<<"Sibling of 3 is: "<<sib->info<<endl;

    // Level of a node
    cout<<"Level of 1: "<<getLevel(root, 1, 0)<<endl;

    // Depth of the tree
    cout<<"Depth of the tree: "<<maxDepth(root)<<endl;
    deleteTree(root);

    // Tree Traversals (PreOrder, InOrder, PostOrder) [Start]
    node *order = NULL;
    order = new node(1);
    order->left = new node(2);
    order->right = new node(3);
    order->left->left = new node(4);
    //printTree(root, NULL, false);
    preOrder(order);
    cout<<endl;
    inOrder(order);
    cout<<endl;
    postOrder(order);
    // Tree Traversals (PreOrder, InOrder, PostOrder) [End]
    return 0;
}