#include <iostream>
#include <vector>

using namespace std;

vector<int> get_result(vector<int>& s, int score, int start)
{
    if(start == s.size())
        return {};

    if(s[start] == score)
        return vector<int>{start};

    if(s[start] < score)
    {
        vector<int> result = {start};
        vector<int> left = get_result(s, score - s[start], start + 1);

        if(left.size() > 0)
        {
            for(auto x: left)
                result.push_back(x);

            return result;
        }
    }

    return get_result(s, score, start+1);
}

int main(void)
{
    int n, tmp;
    vector<int> s;

    cin >> n;
    while(n > 0)
    {
        cin >> tmp;
        s.push_back(tmp);
        n--;
    }

    vector<int> r = get_result(s, 100, 0);

    cout << r.size() << endl;
    for(auto x: r)
        cout << x+1 << endl;

    return 0;
}