
#include <stdlib.h>
#include <stdio.h>
struct testnode{
    int a;
    char* name;
};

struct testnode array11[10]={0};

struct testnode func(){
    return array11[0];
}
int main(){

    char* name="abcdefg";
    array11[0].a=10;
    array11[0].name=name;

    struct testnode test=func();

    printf("%d  %s\n",test.a, test.name);
}



class Solution {
public:
    bool IsBalanced_Solution(TreeNode* pRoot) {
        int Depth;
        return Subhelp(pRoot,Depth);
    }
    
    bool Subhelp(TreeNode* pRoot, int& Depth){
        if(pRoot == NULL){
            Depth=0;
            return true;
        }
        int leftDepth, rightDepth;
        bool leftRes, rightRes;
        leftRes = Subhelp(pRoot->left, leftDepth);
        rightRes = Subhelp(pRoot->right, rightDepth);
        if(leftRes && rightRes){
            int dif=leftDepth-rightDepth;
            if(dif>1 || dif<-1)return false;
            else return true;
        }
        return false;
    }
};