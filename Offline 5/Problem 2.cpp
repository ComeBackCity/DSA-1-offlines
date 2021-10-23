#include<bits/stdc++.h>

using namespace std;

vector<int> minWastinTime(vector<int> x)
{
    //Greedy choice here lies in selecting the customer with minimum serving time
    vector<pair<int,int> > newvc;
    pair<int,int> y;
    int n=x.size();


    for(int i=0; i<n; i++)
    {
        y.first=x[i];
        y.second=i+1;
        newvc.push_back(y);
    }

    sort(newvc.begin(),newvc.end());

    vector<int> newvc2;

    for(int i=0; i<n; i++)
    {
        newvc2.push_back(newvc[i].second);
    }

    return newvc2;
}


int main(void)
{
    int n,x;
    cin >> n;
    vector<int> x1,x2;
    for(int i=0; i<n; i++)
    {
        cin >> x;
        x1.push_back(x);
    }

    x2=minWastinTime(x1);

    for(int i=0; i<n; i++)
    {
        cout << x2[i] << " " ;
    }

    return 0;
}
