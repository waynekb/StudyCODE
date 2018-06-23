#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct d_t{
    int data[128];
};

 vector<d_t> counts;

bool compare(string& data, int s1, int s2, int len)
{
    if(len >= 128)
    {
        for(int i = '0'; i <= '9'; i++)
            if(counts[s2].data[i] - counts[s1].data[i] != counts[s2 + len].data[i] - counts[s2].data[i])
                return false;

        for(int i = 'A'; i <= 'z'; i++)
            if(counts[s2].data[i] - counts[s1].data[i] != counts[s2 + len].data[i] - counts[s2].data[i])
                return false;
    }

    for(int i = 0; i < len; i++)
    {
        if(data[s1 + i] != data[s2 + i])
            return false;
    }

    return true;
}

int max_len(string& data)
{
    int size = data.size();
    int maxlen = size/2;

    while(maxlen > 0)
    {
        const int limit = size - 2*maxlen;

        for(int i = 0; i <= limit; i++)
        {
            if(compare(data, i, i + maxlen, maxlen))
                return maxlen;
        }

        maxlen--;
    }

    return maxlen;
}

int main(void)
{
    string data;
    d_t dd = {.data = {0}};

    cin >> data;

    for(auto x: data)
    {
        counts.push_back(dd);
        dd.data[x]++;
    }
    counts.push_back(dd);
    
    cout << 2*max_len(data) << endl;

    return 0;
}