#include<iostream>
using namespace std;
class node             
{
	public:
		int val;
		node *left;
		node *right;
};
node *root=NULL;

class avl_tree
{
	public:
		int height(node *);
		int differnce(node *);
		node *RR_rot(node *);
		node *LL_rot(node *);
		node *LR_rot(node *);
		node *RL_rot(node *);
		node *balance_factor(node *);
		node *insert(node *,int);
		int inorder(node *);
		int preorder(node *);
		int postorder(node *);
		void nonrec_inorder(node *);
		void nonrec_preorder(node *);
		void nonrec_postorder(node *);
		node *search(node *, int);
};

class stack                        //class stack for non recursive traversal
{
 int top;
 node *stack_nodes[20];
  public:
   stack()
   {
    top=-1;
   }
  void push(node *);
  node* pop();
  node* peek( stack stk);
  int empty()
  {
   if(top==-1)
      return(1);
   return(0);
  }
};

void stack::push(node *node)
{
 stack_nodes[++top]=node;
}

node *stack::pop()
{
 return(stack_nodes[top--]);
}

//main function
int main()
{
	int ch,n;
	avl_tree t;
	do
	{
		cout<<"\n\n*** Operation on AVL tree ***";
		cout<<"\n1. Insert";
		cout<<"\n2. Preorder traversal";
		cout<<"\n3. Inorder traversal";
		cout<<"\n4. Postorder traversal";
		cout<<"\n5. Search";
		cout<<"\n6. Non recurrsive traversal";
		cout<<"\n7. Exit";
		cout<<"\nEnter your choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				cout<<"\nEnter element to be inserted: ";
				cin>>n;
				root=t.insert(root,n);
				break;
				
			case 2:
				cout<<"\nThe preorder traversal of avl tree is: ";
				t.preorder(root);
				break;
				
			case 3:
				cout<<"\nThe inorder traversal of avl tree is: ";
				t.inorder(root);
				break;
				
			case 4:
				cout<<"\nThe postorder traversal of avl tree is: ";
				t.postorder(root);
				break;
				
			case 5:
				if(root!=NULL)
            {
            cout<<"\nEnter node to be Searched:";
            int a;
            cin>>a;
           if(t.search(root,a)!=NULL)
             cout<<"\n"<<a<<" is present in avl tree";
           else
             cout<<"\n"<<a<<" is not present in avl tree";
            }
                else
                    cout<<"\nAvl tree is empty";
			break;		
				
			case 6:
				cout<<"\nIn order Traversal: ";
				t.nonrec_inorder(root);
				cout<<"\nPre order Traversal: ";
				t.nonrec_preorder(root);
				cout<<"\nPost order Traversal: ";
				t.nonrec_postorder(root);
				break;
					
			case 7:
				cout<<"\nExiting ..";
				break;
				
			default:
				cout<<"Please enter proper choice";
				break;
		}
	}while(ch<=5);
	return 0;
}

//function for insertion of node in avl tree
node *avl_tree::insert(node *root, int n)
{
	if (root==NULL)           //tree is intially empty
	{
		root=new node;
		root->val=n;
		root->left=NULL;
		root->right=NULL;
		return root;
	}
	else                     //some nodes are intially present in tree
	{
		if(n<root->val)      //value to be inserted is less than root node value
		{
			root->left=insert(root->left,n);
			root=balance_factor(root);
		}
		else if(n>root->val)   //value to be inserted is greater than root node value
		{
			root->right=insert(root->right,n);
			root=balance_factor(root);
		}
		else                   //value to be inserted is already present in tree
			cout<<"\nNode already exist";
	return root;
	}
}

//function for calculating balance factor 
node *avl_tree::balance_factor(node *temp)
{
	int bf=differnce(temp);
	if(bf>1)                     
	{
		if(differnce(temp->left)>0)
			temp=LL_rot(temp);
		else
			temp=LR_rot(temp);
	}
	else if(bf<-1)
	{
		if(differnce(temp->right)>0)
			temp=RL_rot(temp);
		else
			temp=RR_rot(temp);
	}
	return temp;
}

int avl_tree::differnce(node *temp)
{
	int left_height=height(temp->left);
	int right_height=height(temp->right);
	int bf_1=left_height-right_height;
	return bf_1;
}

//function for calculating height of any node in avl tree
int avl_tree::height(node *temp)
{
	int h=0;
	if(temp!=NULL)                           
	{
		int left_height=height(temp->left);
		int right_height=height(temp->right);
		int max_height=max(left_height,right_height);
		h=max_height+1;
	}
	return h;	
}

//function for single left rotation
node *avl_tree::LL_rot(node *parent)
{
	node *temp;
	temp=parent->left;
	parent->left=temp->right;
	temp->right=parent;
	return temp;
}

//function for single right rotation
node *avl_tree::RR_rot(node *parent)
{
	node *temp;
	temp=parent->right;
	parent->right=temp->left;
	temp->left=parent;
	return temp;
}

//function for left right rotation
node *avl_tree::LR_rot(node *parent)
{
	node *temp;
	temp=parent->left;
	parent->left=RR_rot(temp);
	return LL_rot(parent);
}

//function for right left rotation
node *avl_tree::RL_rot(node *parent)
{
	node *temp;
	temp=parent->right;
	parent->right=LL_rot(temp);
	return RR_rot(parent);
}

//recurisve preorder traversal	
int avl_tree::preorder(node *curr_root)
{
	if(curr_root == NULL)                 //if tree is empty
		return 0;
	else
	{
		cout<<curr_root->val<<" ";        //priting the root
		if(curr_root->left!=NULL)
			preorder(curr_root->left);
		if(curr_root->right!=NULL)
			preorder(curr_root->right);
	}
}			

//recurisve inorder traversal
int avl_tree::inorder(node *curr_root)
{
	if(curr_root == NULL)
		return 0;
	else
	{
		if(curr_root->left!=NULL)
			inorder(curr_root->left);
		cout<<curr_root->val<<" ";
		if(curr_root->right!=NULL)
			inorder(curr_root->right);
	}
}

//recurisve postorder traversal
int avl_tree::postorder(node *curr_root)
{
	if(curr_root == NULL)
        return 0;
    else
     {
        if(curr_root->left != NULL)
        	postorder(curr_root->left);
        if(curr_root->right != NULL)
            postorder(curr_root->right);
            cout<<curr_root->val<<" ";
     }
}

node *avl_tree::search(node* root, int k)
{
  if(root == NULL || root->val == k)
   return root;
  if(  k > root->val)
   return search(root->right,k);
  return search(root->left,k);
 }
 
 void avl_tree::nonrec_inorder(node *curr_root)
 {
 	stack stk;
 node *temp;
 if(curr_root!=NULL)
 {
  temp=curr_root;
  do
  {
   while(temp!=NULL)
   {
      stk.push(temp);
      temp=temp->left;
   }
   if(!stk.empty())
   {
      temp=stk.pop();
      cout<<temp->val<<"  ";
      temp=temp->right;
   }
   else
    break;
  }while(1);
 }
 else
  cout<<"The tree is empty ";
}

//nonrecurisve preorder traversal
void avl_tree::nonrec_preorder(node *curr_root)
{
 stack stk;
 node *temp=curr_root;
 stk.push(temp);
 while(!stk.empty())
 {
  temp=stk.pop();
  if(temp!=NULL)
  {
   cout<<temp->val<<"  ";
   stk.push(temp->right);
   stk.push(temp->left);
  }
 }
}

//nonrecurisve postorder traversal
void avl_tree::nonrec_postorder(node *ptr)
{     int flag[50];                 //to keep track weather we are visting right or left child 
      int top_prev;
      node * stk_array[50];
      int top =1;
      stk_array[++top]=NULL;
      do
      {
          while (ptr!=NULL)
          {
              stk_array[++top]=ptr;
              flag[top]=1;
              if (ptr->right !=NULL)
              {
                  stk_array[++top]=ptr->right;
                  flag[top]=-1;
              }
              ptr=ptr->left;
          }
          top_prev=top;
          ptr=stk_array[top--];

          while (flag[top_prev]==1)
          {
              cout<<ptr->val<<"  ";
              top_prev=top;
              ptr=stk_array[top--];
          }
      }while (ptr!=NULL);
      }
 