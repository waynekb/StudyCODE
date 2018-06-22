#include <vector>
#include <iostream>
using namespace std;


struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if(pHead == NULL)return NULL;
        ListNode* cur=pHead->next;
        ListNode* prenode=pHead;
        while(prenode){
            cur = prenode->next;
            int count = 0; 
            while(cur && cur->val ==  prenode->val){
                cur=cur->next;
                count++;
            }
            if(count==0)break;
            else{
                prenode=cur;
            }
        }
        ListNode* res=prenode;
        while(prenode && prenode->next!=NULL){
            cur=prenode->next;
            ListNode* nextnode=cur->next;
            int count=0;
            while(nextnode && nextnode->val == cur->val){
                nextnode=nextnode->next;
                count++;
            }
            if(count == 0){
                prenode=cur;
            }
            else{
                prenode->next=nextnode;
            }
        }
        return res;
    }
};

int main(){
    vector<int> valarray={1,2,2,3,3,4,5,5};
    ListNode* pHead = new ListNode(0);
    ListNode* cur=pHead;
    for(auto &w:valarray){
        cur->next=new ListNode(w);
        cur=cur->next;
    }
    Solution sol;
    cur=pHead;
    pHead=pHead->next;
    delete cur;
    cur=sol.deleteDuplication(pHead);
    while(cur != NULL){
        cout << cur->val << " ";
        cur=cur->next;
    }
    cout<<endl;
    return 0;
}