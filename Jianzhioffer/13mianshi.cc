#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

// class Solution {
// public:
//     void reOrderArray(vector<int> &array) {
//         int low=0;
//         int high=array.size();
//         high--;
//         while(low!=high){
//             while(low!=high && (array[high] & 0x1) != 1){ 
//                 cout<< "aaaa"<<endl;
//                 high--;}               
//             while(low!=high && (array[low] & 0x1) ==1){ 
//                 low++;}
//             if(low != high){
//                 int temp=array[low];
//                 array[low]=array[high];
//                 array[high]=temp;
                
//             }
//         }
//     }
// };


class Solution {
public:
    void reOrderArray(vector<int> &array) {
        vector<int>::iterator low=array.begin();
        vector<int>::iterator high=array.end();
        high--;
        while(low!=high){
            while(low!=high && ((*low) & 0x1 )==1)
                low++;
            while(low!=high && ((*high) & 0x1) == 0)
                high--;
            if(low != high){
                int temp=*low;
                *low=*high;
                *high=temp;
            }
        }
    }
};



    // ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
    //     if(pListHead == NULL || k == 0)
    //         return NULL;
    //     ListNode* after=pListHead;
    //     ListNode* pre=pListHead;
    //     for(int i=0;i <k;i++){
    //         if(pre == NULL )return NULL;
    //         pre=pre->next;
    //     }
    //     while(pre!=NULL){
    //         pre=pre->next;
    //         after=after->next;
    //     }
    //     return after;
    // }



int main(int argc, char** argv){
    vector<int> array={12,33,43,56,4,7,8,3,97};
    Solution sol;
    // int num=atoi(argv[1]);
    // for(int i=0;i<num;i++){
    //     int tmp;
    //     cin>> tmp;
    //     array.push_back(tmp);
    // }
    sol.reOrderArray(array);
    for(auto &w:array){
        cout<< w <<" ";
    }
    cout<<endl;
    return 0;
}
