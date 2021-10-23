#include<bits/stdc++.h>

using namespace std;

class MaxHeap{

    vector<int> vec;

public:
    //Creation
    MaxHeap();
    MaxHeap(int arr[], int length);
    void heapify();
    static MaxHeap merge(MaxHeap &lhs, MaxHeap &rhs);
    static MaxHeap meld(MaxHeap &lhs, MaxHeap &rhs);

    //Basic
    int findMax();
    void Insert(int val);
    int extract_max();
    void delete_max();
    void Replace(int val);

    //Inspection
    int size();
    bool is_empty();

    //Internal
    void increase_key(int i, int val);
    void decrease_key(int i, int val);
    void Delete(int i);
    void sift_up(int i);
    void sift_down(int i);

    //Utility functions
    int parent(int i);
    int left(int i);
    int right(int i);
    void printHeap();

};

MaxHeap::MaxHeap()
{

}

MaxHeap::MaxHeap(int arr[], int length)
{
    for(int i=0; i<length; i++)
    {
        this->vec.push_back(arr[i]);
    }

    heapify();
}

void MaxHeap::heapify()
{
    for(int i=vec.size()/2-1; i>=0; i--)
        sift_up(i);
}

MaxHeap MaxHeap::merge(MaxHeap &lhs, MaxHeap &rhs)
{
    MaxHeap nmh;
    int x,y,temp;
    x=lhs.size();
    y=rhs.size();
    for(int i=0; i<x; i++)
    {
        temp=lhs.vec[i];
        nmh.Insert(temp);
    }

    for(int i=0; i<y; i++)
    {
        temp=rhs.vec[i];
        nmh.Insert(temp);
    }

    nmh.heapify();

    return nmh;
}

MaxHeap MaxHeap::meld(MaxHeap &lhs, MaxHeap &rhs)
{
    MaxHeap nmh;
    int x,y,temp;
    x=lhs.size();
    y=rhs.size();
    for(int i=0; i<x; i++)
    {
        temp=lhs.extract_max();
        nmh.Insert(temp);
    }

    for(int i=0; i<y; i++)
    {
        temp=rhs.extract_max();
        nmh.Insert(temp);
    }

    nmh.heapify();

    return nmh;
}

int MaxHeap::findMax()
{
    heapify();
    return vec[0];
}

void MaxHeap::Insert(int val)
{

    vec.push_back(val);

    heapify();
}

int MaxHeap::extract_max()
{
    heapify();

    int x=vec[0];

    vec[0]=vec[vec.size()-1];
    vec.erase(vec.end()-1);

    heapify();

    return x;
}

void MaxHeap::delete_max()
{
    heapify();

    vec[0]=vec[vec.size()-1];
    vec.erase(vec.end()-1);

    heapify();
}

void MaxHeap::Replace(int val)
{
    delete_max();
    Insert(val);
}


int MaxHeap::size()
{
    return vec.size();
}

bool MaxHeap::is_empty()
{
    if(vec.size()==0)
        return true;
    else
        return false;
}

void MaxHeap::increase_key(int i, int val)
{
    vec[i]+=val;

    heapify();

}

void MaxHeap::decrease_key(int i, int val)
{
    vec[i]-=val;

    heapify();
}

void MaxHeap::Delete(int i)
{
    vec[i]=vec[vec.size()-1];
    vec.erase(vec.end()-1);
    heapify();
}

void MaxHeap::sift_up(int i)
{
    int l,r,largest;
    l=left(i);
    r=right(i);
    largest=i;
    if(l<vec.size() && vec[l]>vec[largest])
    {
        largest=l;
    }

    if(r<vec.size() && vec[r]>vec[largest])
    {

        largest=r;
    }

    if(largest!=i)
    {
        swap(vec[i],vec[largest]);
        sift_up(largest);
    }

}

void MaxHeap::sift_down(int i)
{
    if(i && vec[parent(i)] < vec[i])
    {
        swap(vec[parent(i)],vec[i]);
        sift_down(parent(i));
    }
}

int MaxHeap::parent(int i)
{
    return (i-1)/2;
}

int MaxHeap::left(int i)
{
    return (2*i + 1);
}

int MaxHeap::right(int i)
{
    return (2*i + 2);
}


void MaxHeap::printHeap()
{
    for(int i=0; i<vec.size(); i++)
    {
        cout << vec[i] << " " ;
    }
}





int main(void)
{
    int n;

    cin >> n;

    int a[n];
    for(int i=0; i<n; i++)
    {
        cin >> a[i];
    }

    int b[]={4,5,6,7};

    MaxHeap h(a,n);
    MaxHeap h1(b,sizeof(b)/sizeof(int));
    MaxHeap h2;
    //h.printHeap();

    //cout << h.size() << endl;
    h.printHeap();
    cout << "\n" << endl;
    /*cout << h.extract_max() << endl;
    h.printHeap();
    cout << "\n" << endl;
    h.Insert(8);
    //cout << h.extract_max() << endl;

    //h.Insert(9);
    h.printHeap();
    cout << "\n" << endl;*/

    //h.Delete(2);

    //h.printHeap();

    //h2=MaxHeap::merge(h,h1);

    h2=MaxHeap::merge(h,h1);
    h2.printHeap();

    cout << "\n" << endl;

    h.printHeap();
}


