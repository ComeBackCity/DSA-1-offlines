#include<bits/stdc++.h>

using namespace std;

vector<double> bucket_sort(vector<double> a)
{
    vector<double> b[a.size()];
    double minimum=a[0],maximum;

    for(int i=0; i<a.size(); i++)
    {
        if(a[i]<minimum)
            minimum=a[i];
    }

    for(int i=0; i<a.size(); i++)
    {
        a[i]-=minimum;
    }

    maximum=a[0];

    for(int i=0; i<a.size(); i++)
    {
        if(a[i]>maximum)
            maximum=a[i];
    }

    maximum=maximum+0.0001;

    for(int i=0; i<a.size(); i++)
    {
        a[i]/=maximum;
    }

    for (int i=0; i<a.size(); i++)
    {
        int bi = a.size()*a[i];
        b[bi].push_back(a[i]);
    }

    for (int i=0; i<a.size(); i++)
    {
        sort(b[i].begin(), b[i].end());
    }

    int idx = 0;
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b[i].size(); j++)
        {
            a[idx++] = b[i][j];
        }
    }

    for(int i=0; i<a.size(); i++)
    {
        a[i]*=maximum;
    }

    for(int i=0; i<a.size(); i++)
    {
        a[i]+=minimum;
    }

    return a;
}

int main(void)
{
    int n;
    double temp;
    cin >> n;
    vector<double> a,out;

    if(n==0)
    {
        cout << "The vector is of size zero. Sorting ends" << endl;
        return 0;
    }

    for(int i=0; i<n; i++)
    {
        cin >> temp;
        a.push_back(temp);
    }

    out=bucket_sort(a);

    for(int i=0; i<out.size(); i++)
    {
        cout << out[i] << " " ;
    }
}
