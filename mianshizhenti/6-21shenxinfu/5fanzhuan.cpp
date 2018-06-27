#include<iostream>
#include<cmath>
#include <vector>
#include <memory>
using namespace std;

int findmorebignum(int value, int index, vector<int>& num)
{
    int count = 0;
    for (int i = 0; i < index; i++)
    {
        if (num[i] > value)
            count++;
    }
    return count;
}

int main()
{
    int n;
    cin >> n;
    int total = 0;
    vector<int> num;
    int tmp;

    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        num.push_back(tmp);
    }
    for (int i = 1; i < n; i++)
    {
        total += findmorebignum(num[i], i, num);
    }
    cout << total << endl;
    return 0;
}