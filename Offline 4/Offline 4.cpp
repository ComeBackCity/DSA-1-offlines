#include<bits/stdc++.h>

using namespace std;

class hotel
{
    int x;
    int y;
public:
    hotel()
    {
        x=0;
        y=0;
    }

    hotel(int x, int y)
    {
        this->x=x;
        this->y=y;
    }

    void setx(int x)
    {
        this->x=x;
    }

    void sety(int y)
    {
        this->y=y;
    }

    int getx()
    {
        return x;
    }

    int gety()
    {
        return y;
    }

    bool operator< (const hotel& rhs)
    {
        if(x < rhs.x)
            return true;
        else if(x==rhs.x && y<rhs.y)
            return true;

        return false;
    }

};

vector<hotel> skyLine(vector<hotel> x)
{
    if(x.size()<2)
        return x;
    int half=x.size()/2;
    hotel s_item,temp_hotel;
    vector<hotel> left(x.begin(),x.begin()+half);
    vector<hotel> right(x.begin()+half,x.end());


    left=skyLine(left);
    s_item=left[0];

    for(int i=0; i<left.size(); i++)
    {
        if(s_item.gety()>left[i].gety())
        {
            s_item=left[i];
        }
    }

    vector<hotel> temp;

    for(int i =0 ; i < right.size() ; i++)
    {

        if( s_item.gety()>right[i].gety() )
        {
            temp_hotel=right[i];
            temp.push_back(temp_hotel);
        }
    }


    right=temp;
    right=skyLine(right);

    vector<hotel> newvc(left.size()+right.size());
    merge(left.begin(),left.end(),right.begin(), right.end(), newvc.begin());


    return newvc;

}





int main(void)
{
    freopen("test 3.txt","r",stdin);
    int x;
    cin >> x;
    int y,z;
    hotel h;
    vector<hotel> hotelVector;

    for(int i=0; i<x; i++)
    {
        cin >> y >> z;
        h.setx(y);
        h.sety(z);
        hotelVector.push_back(h);
    }

    sort(hotelVector.begin(),hotelVector.end());

    for(int i=0; i<hotelVector.size(); i++)
    {
        cout << hotelVector[i].getx() << "," << hotelVector[i].gety() << endl;
    }

    vector<hotel> hotelVector2;
    //hotelVector2=hotelVector;
    hotelVector2=skyLine(hotelVector);

    cout << "\nThe non-dominant points are: " << endl;

    for(int i=0; i<hotelVector2.size(); i++)
    {
        cout << hotelVector2[i].getx() << "," << hotelVector2[i].gety() << endl;
    }

}
