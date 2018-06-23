#include <iostream>
#include <vector>

using namespace std;

// bool check(int n, int r, vector<int>& holes, int d)
// {
//     if(d == holes.size())
//         return false;

//     if(r > 1 && holes[d] != r-1)
//         if(!check(n, r-1, holes, d+1))
//             return false;

//     if(r < n && holes[d] != r+1)
//         if(!check(n, r+1, holes, d+1))
//             return false;

//     return true;
// }

// bool rabbit(int n, vector<int>& holes)
// {
//     for(int i = 1; i <= n; i++)
//     {
//         if(i == holes[0])
//             continue;

//         if(!check(n, i, holes, 1))
//             return false;
//     }

//     return true;
// }


bool check(int n, vector<int>& holes, int r, int d){
    if( d > holes.size())return false;
    if(holes[d] == r)return true;
    if(r!=n && check(n, holes, r-1, )){

    }
}


bool rabbit(int n, vector<int>& holes){
    for(int i=1; i <= n; i++){
        if(!check(holes,int r, int d))return false;
    }
    return true;
}

int main(void)
{
    int n, k;
    vector<int> holes;
    int tmp;

    cin >> n >> k;

    while(k > 0)
    {
        cin >> tmp;
        holes.push_back(tmp);
        k--;
    }

    if(n > 0 && holes.size() > 0 && rabbit(n, holes))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}