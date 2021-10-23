#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include<cstring>

using namespace std;


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class ListNode
{
public:
    int item;
    ListNode * next;
};

class LinkedListWithTail
{

    ListNode * list;
    ListNode * tail;
    int length;

public:
    LinkedListWithTail()
    {
        list = 0;  //initially set to NULL
        tail = 0;
        length=0;
    }

    int getLength()
    {
        return length;
    }

    //add required codes to set up tail pointer
    int insertItem(int item) //insert at the beginning
    {
        ListNode * newNode ;
        newNode = new ListNode() ;
        newNode->item = item ;
        if(list==NULL)
        {
            list= newNode;
            tail= newNode;
        }
        else
        {
            newNode->next = list ; //point to previous first node
            list = newNode ;
        }//set list to point to newnode as this is now the first node
        length++;
        return SUCCESS_VALUE ;
    }

    //add required codes to set up tail pointer
    int deleteItem(int item)
    {
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item)
                break ;
            prev = temp;
            temp = temp->next ; //move to next node
        }
        if (temp == 0)
            return NULL_VALUE ; //item not found to delete
        if (temp == list) //delete the first node
        {
            list = list->next ;
            delete temp ;
            length--;
        }
        else if(temp == tail)
        {
            tail = prev;
            delete temp;
            length--;
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
            length--;
        }

        return SUCCESS_VALUE ;
    }

    //add required codes to set up tail pointer
    ListNode * searchItem(int item)
    {
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item)
                return temp ;
            temp = temp->next ; //move to next node
        }
        return 0 ; //0 means invalid pointer in C, also called NULL value in C
    }

    void printList()
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        /*cout << "Head is: " << list->item << endl;
        cout << "Tail is: " << tail->item << endl;*/
        printf("\n");
        printf("Length: %d\n",getLength());
    }

    //------------write code for the functions below-----------
    int insertLast(int item)
    {
        ListNode *temp=new ListNode;
        temp->item=item;
        tail->next=temp;
        tail=temp;
        length++;

        return SUCCESS_VALUE;

    }

    ListNode * getItemAt(int pos)
    {
        ListNode * temp ;
        temp = list ;
        if(pos>length)
            return 0;
        else
        {
            for(int i=1; i<pos; i++)
            {
                temp=temp->next;
            }
            return temp;
        }

    }

    int deleteLast()
    {
        ListNode *cur= new ListNode;
        cur=list;
        ListNode *prev=new ListNode;
        prev=list;
        while(cur->next!=NULL)
        {
            prev=cur;
            cur=cur->next;
        }

        tail=prev;
        tail->next=NULL;
        delete cur;
        length--;

        return SUCCESS_VALUE;
    }
};

/*int main(void)
{
    LinkedListWithTail ll;

    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert Last. 5. Get Item At. 6. Delete last.\n");
        cout << "7. Print 8. Exit" << endl;

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            ll.insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            ll.deleteItem(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            ListNode * res = ll.searchItem(item);
            if(res!=0)
                printf("Found.\n");
            else
                printf("Not found.\n");
        }
        else if(ch==4)
        {
            int x;
            cin >> x;
            ll.insertLast(x);

        }
        else if(ch==5)
        {
            int pos;
            cin >> pos;
            ListNode * res = ll.getItemAt(pos);
            cout << res->item << endl;
        }
        else if(ch==6)
        {
            ll.deleteLast();
        }
        else if(ch==7)
        {
            ll.printList();
        }
        else if(ch==8)
        {
            break;
        }
    }

}*/


class Queue
{
    LinkedListWithTail ll;
public:
    Queue()
    {

    }

    void enqueue(int item)
    {
        ll.insertItem(item);
    }

    int dequeue()
    {
       if(ll.getLength()==0)
            return NULL_VALUE;
        ListNode *x=new ListNode;
        x=ll.getItemAt(ll.getLength());
        ll.deleteLast();
        return x->item;
    }
};

int main(void)
{
    Queue qu;

    while(1)
    {
        printf("1. Enque. 2. Deque. 3. Exit. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            qu.enqueue(item);
        }
        else if(ch==2)
        {
            int item=qu.dequeue();
            printf("%d\n",item);
        }
        else if(ch==3)
        {
            break;
        }
    }

}

