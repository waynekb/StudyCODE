#include <iostream>
#include <stack>
using namespace std;

class BTnode
{
public:
    BTnode(int a):value(a),left(NULL),right(NULL){};
    int value;
    BTnode* left;
    BTnode* right;
};


/*
*   先序遍历 循环
*/
void Preorder(BTnode* root)
{
    stack<BTnode*> stack;
    if(root==NULL)return;
    BTnode* cur=root;
    while(cur!=NULL)
    {
        cout<<cur->value<<" ";
        if(cur->left != NULL)
        {
            stack.push(cur);
            cur=cur->left;
        }
        else if(cur->right != NULL)
        {
            cur=cur->right;
        }
        else 
        {
            cur=NULL;
            while(!stack.empty())
            {
                BTnode* tmp=stack.top();
                if(tmp->right!=NULL)
                {
                    cur=tmp->right;
                    stack.pop();
                    break;
                }
                stack.pop();
            }
        }
    }
    cout<<endl;
}


/*
*   中序遍历 循环
*/

void midorder( BTnode*const root)
{
    if(root==NULL)return;
    stack<BTnode*> stack;
    BTnode* cur=root;
    while(cur!=NULL)
    {
        if(cur->left!=NULL)
        {
            stack.push(cur);
            cur=cur->left;
        }
        else
        {
            cout<< cur->value<<" ";
            if(cur->right!=NULL)
            {
                cur=cur->right;
            }
            else
            {
                cur=NULL;
                BTnode* tmp=NULL;
                while(!stack.empty())
                {
                    tmp=stack.top();
                    cout<<tmp->value<<" ";
                    if(tmp->right!=NULL)
                    {
                        cur=tmp->right;
                        stack.pop();
                        break;
                    }
                    stack.pop();
                }
            }
        }
    }
    cout<<endl;
}

/*
*   后序遍历 循环
*/
void aftorder(BTnode* root)
{
    if(root==NULL)return;
    BTnode* cur=root;
    stack<BTnode*> stack;
    int flag=0;
    while(cur!=NULL)
    {
        if(cur->left!=NULL)
        {
            stack.push(cur);
            cur=cur->left;
        }
        else if(cur->right!=NULL)
        {
            stack.push(cur);
            cur=cur->right;
        }
        else 
        {
            cout<<cur->value<<" ";
            BTnode* tmp;
            BTnode* pre=cur;
            cur=NULL;
            while(!stack.empty())
            {
                tmp=stack.top();                              //判断出栈时，当前的节点是top节点的左儿子还是右儿子，
                if(tmp->right==pre||tmp->right==NULL)         //从而判断当前top节点的左右儿子是否已经被访问.如果当前节点是左儿子，
                {                                             //则说明右儿子还未被访问，如果是右儿子则说明两个儿子都被访问了，
                    cout<<tmp->value<<" ";                    //可以访问父节点了
                    pre=tmp;
                    stack.pop();
                }
                else if(tmp->left==pre)
                {
                    cur=tmp->right;
                    break;
                }    
            }
        }
    }
    cout << endl;
}



void test1()
{
    cout<<"---------test1-----------"<<endl;
    BTnode* node1=new BTnode(6);
    BTnode* node2=new BTnode(9);
    BTnode* node3=new BTnode(10);
    BTnode* node4=new BTnode(3);
    BTnode* node5=new BTnode(45);
    BTnode* node6=new BTnode(67);
    BTnode* node7=new BTnode(23);
    BTnode* node8=new BTnode(87);
    BTnode* node9=new BTnode(11);
    BTnode* node10=new BTnode(4);
    BTnode* node11=new BTnode(18);

    node1->left=node2;
    node1->right=node3;
    node2->left=node4;
    node3->right=node7;
    node4->left=node5;
    node4->right=node6;
    node5->right=node10;
    node7->left=node8;
    node8->left=node9;
    node10->right=node11;

    cout<<"precious order"<<endl;
    Preorder(node1);
    cout<<"mid order"<<endl;
    midorder(node1);
    cout<<"after order"<<endl;
    aftorder(node1);
    cout<<endl;
}

void test2()
{
    cout<<"---------test2-----------"<<endl;
    BTnode* node1=new BTnode(6);
    BTnode* node2=new BTnode(9);
    BTnode* node3=new BTnode(10);
    BTnode* node4=new BTnode(3);
    BTnode* node5=new BTnode(45);
    BTnode* node6=new BTnode(67);
    BTnode* node7=new BTnode(23);

    node1->left=node2;
    node2->left=node3;
    node3->left=node4;
    node4->left=node5;
    node5->left=node6;
    node6->left=node7;
    cout<<"precious order"<<endl;
    Preorder(node1);
    cout<<"mid order"<<endl;
    midorder(node1);
    cout<<"after order"<<endl;
    aftorder(node1);
    cout<<endl;
}




void test3()
{
cout<<"---------test3-----------"<<endl;
    BTnode* node1=new BTnode(6);
    BTnode* node2=new BTnode(9);
    BTnode* node3=new BTnode(10);
    BTnode* node4=new BTnode(3);
    BTnode* node5=new BTnode(45);
    BTnode* node6=new BTnode(67);
    BTnode* node7=new BTnode(23);

    node1->right=node2;
    node2->right=node3;
    node3->right=node4;
    node4->right=node5;
    node5->right=node6;
    node6->right=node7;
    cout<<"precious order"<<endl;
    Preorder(node1);
    cout<<"mid order"<<endl;
    midorder(node1);
    cout<<"after order"<<endl;
    aftorder(node1);
    cout<<endl;
}
// int main()
// {
//     test1();
//     test2();
//     test3();

    
// }