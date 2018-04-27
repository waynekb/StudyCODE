#include <iostream>
#include <stack>
using namespace std;

struct ListNode
{
    int Key;
    ListNode* next;
};

struct ListHead
{
    ListNode* head;
    ListNode* tail;
};

void Addnode(ListHead* List,int value)
{
    ListNode* tmp=new ListNode{value,NULL};
    if(List->head==NULL && List->tail ==NULL)
    {
        List->head=tmp;
        List->tail=tmp;
    }
    List->tail->next=tmp;
    List->tail=tmp;
}


void printList(ListHead* List)
{
    ListNode* curr=List->head;
    while(curr!=NULL)
    {
        cout<<curr->Key<<" ";
        curr=curr->next;
    }
    cout<<endl;
}

/*基于栈*/

void convert(ListHead* List)
{
    stack<ListNode*> nodes;
    ListNode* curr=List->head;
    while(curr != NULL)
    {
        nodes.push(curr);
        curr=curr->next;
    }
    while(!nodes.empty())
    {
        curr=nodes.top();
        cout << curr->Key << " ";
        nodes.pop();
    }
    cout << endl;
}



/*基于递归*/
void help(ListNode* node)
{
    if(node->next != NULL)
        help(node->next);
    cout << node->Key << " ";
    return;
}
void convert1(ListHead* List)
{
    help(List->head);
    cout<<endl;
    return;
}

int main()
{
    int num;
    // int values[100];
    cin>>num;
    int values;
    ListHead* List=new ListHead{NULL,NULL};
    for(int i=0;i<num;i++)
    {   
        cin>>values;
        Addnode(List,values);
    }
    printList(List);
    convert(List);
    convert1(List);

    return 0;
}