#include <cstdlib>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
       TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };


TreeNode* createBT(vector<int>::iterator prebeg,vector<int>::iterator preend,vector<int>::iterator vinbeg,vector<int>::iterator vinend){
        int tmp=*prebeg;
        int count=0;
        if(prebeg==preend)return NULL;
        auto cur=vinbeg;
        while(tmp!=*cur){
            count++;
        }
        TreeNode* ret=new TreeNode(tmp);
        ret->left=createBT(prebeg+1,prebeg+count,vinbeg,vinbeg+count-1);
        ret->right=createBT(prebeg+count+1,preend,vinbeg+count+1,vinend);
        return ret;
    }
class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        auto prebeg=pre.begin();
        auto preend=pre.end();
        auto vinbeg=vin.begin();
        auto vinend=vin.end();
        return createBT(prebeg,--preend,vinbeg,--vinend);
    }
    
};


void Preorder(TreeNode* root)
{
    stack<TreeNode*> stack;
    if(root==NULL)return;
    TreeNode* cur=root;
    while(cur!=NULL)
    {
        cout<<cur->val<<" ";
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
                TreeNode* tmp=stack.top();
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
int main()
{
    vector<int> pre={1,2,4,7,3,5,6,8};
    vector<int> vin={4,7,2,1,5,3,8,6};
    Solution sol;
    TreeNode* tree=sol.reConstructBinaryTree(pre,vin);
    Preorder(tree);
    return 0;
}

