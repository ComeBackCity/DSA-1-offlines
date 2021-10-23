#include<bits/stdc++.h>
#define UNSUCCESSFUL -9999999

using namespace std;

vector<int> counting_sort(vector<int> a)
{

    vector<int> c(a.size());
    int minimum=a[0],maximum,temp;

    for(int i=0; i<a.size(); i++)
    {
        if(a[i]<minimum)
            minimum=a[i];
    }

    for(int i=0; i<a.size(); i++)
    {
        a[i]-=minimum;
    }

    int minimum1=minimum;
    minimum=0;
    maximum=a[0];

    for(int i=0; i<a.size(); i++)
    {
        if(a[i]>maximum)
            maximum=a[i];
    }

    vector<int> b(maximum+1,0);

    for(int i=0; i<a.size(); i++)
    {
        b[a[i]]++;
    }

    for(int i=1; i<=maximum; i++)
    {
        b[i]=b[i-1]+b[i];
    }

    for(int i=a.size()-1; i>=0; i--)
    {
        c[b[a[i]]-1]=a[i];
        b[a[i]]--;
    }


    for(int i=0; i<c.size(); i++)
    {
        c[i]+=minimum1;
    }

    return c;

}

int main(void)
{
    int k,in;
    cin >> k;
    vector<int> a,out;

    if(k==0)
    {
        cout << "The vector is of size zero. Sorting ends." << endl;
        return 0;
    }

    for(int i=0; i<k; i++)
    {
        cin >> in;
        a.push_back(in);
    }

    out=counting_sort(a);


    for(int i=0; i<out.size(); i++)
    {
        cout << out[i] << " " ;
    }

    cout << "\nSorting ends." << endl;

    return 0;
}
