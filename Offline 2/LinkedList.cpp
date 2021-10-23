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

class LinkedList
{

    ListNode * list;
    int length;

public:
    LinkedList()
    {
        list=0; //initially set to NULL
        length=0;
    }

    int getLength()
    {
        return length;
    }

    int insertItem(int item) //insert at the beginning
    {
        ListNode * newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ; //point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node
        length++;
        return SUCCESS_VALUE ;
    }

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
        printf("\n");
        printf("Length: %d\n",length);
    }

    //------------write code for the functions below-----------

    int insertLast(int item)
    {
        ListNode *temp=new ListNode;
        temp->item=item;
        temp->next=NULL;
        ListNode *cur=new ListNode;
        cur=list;
        while(cur->next!=NULL)
        {
            cur=cur->next;
        }
        cur->next=temp;
        length++;

        return SUCCESS_VALUE;

    }

    int insertAfter(int oldItem, int newItem)//only after first instance
    {

        ListNode *temp=new ListNode;
        temp->item=newItem;
        ListNode *cur1=new ListNode;
        cur1=list;
        ListNode *cur2=new ListNode;
        while(cur1)
        {
            if(cur1->item==oldItem)
            {
                cur2=cur1->next;
                cur1->next=temp;
                temp->next=cur2;

                length++;

                return SUCCESS_VALUE;
            }
            else
            {
                cur1=cur1->next;
            }

        }

        return NULL_VALUE;

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

    int deleteFirst()
    {
        ListNode *temp=new ListNode;
        temp=list;
        list=list->next;
        length--;
        delete temp;

        return SUCCESS_VALUE;
    }


    ~LinkedList()
    {

        while(list)
        {
            deleteFirst();
        }
    }

};

int main(void)
{
    LinkedList ll;

    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert Last. 5. Insert After. 6. Get Item At.\n");
        cout << "7. Delete First 8. Print 9. Exit" << endl;

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
            int oi,ni;
            cin >> oi >> ni;
            ll.insertAfter(oi,ni);
        }
        else if(ch==6)
        {
            int pos;
            cin >> pos;
            ListNode * res = ll.getItemAt(pos);
            cout << res->item << endl;
        }
        else if(ch==7)
        {
            ll.deleteFirst();
        }
        else if(ch==8)
        {
            ll.printList();
        }
        else if(ch==9)
        {
            break;
        }
    }

}
