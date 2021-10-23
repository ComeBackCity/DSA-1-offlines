#include<iostream>
#include<stdio.h>
#include<stdlib.h>


using namespace std;

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;


void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem)
{
	if(listMaxSize==0)
    {
        initializeList();
    }

	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
	return SUCCESS_VALUE ;
}

// InsertItemAt function where the order of the items are maintained. However it does not satisfy the condition of the instruction
/*int insertItemAt(int value, int pos)
{

    if(pos<length)
    {
        int * tempList ;
        if (length == listMaxSize)
        {

            listMaxSize = 2 * listMaxSize ;

        }

        tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
        int i;
        for( i = 0; i < pos ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        tempList[pos]=value;
        for( i = pos; i < length ; i++ )
        {
            tempList[i+1] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory


        length++ ;
        return SUCCESS_VALUE ;
    }
}*/

int getLength()
{
    return length;
}

int insertItemAt(int value, int pos) // Order is not maintained but condition is fulfilled
{
    if(pos>=length)
    {
        return NULL_VALUE;
    }

    int *tempList;
    if(length==listMaxSize)
    {
        listMaxSize = 2 * listMaxSize ;

        tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
        for(int i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ;
        }
        free(list) ;
        list = tempList ;
    }

    list[length]=list[pos];
    length++;
    list[pos]=value;
    return SUCCESS_VALUE;


}

void shrink()
{
    if(listMaxSize>LIST_INIT_SIZE)
    {
        while(length<=listMaxSize/2)
        {
            listMaxSize/=2;
            int *tempList;
            tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
            for(int i = 0; i < length ; i++ )
            {
                tempList[i] = list[i] ; //copy all items from list to tempList
            }
            free(list) ; //free the memory allocated before
            list = tempList ;
        }
    }

}



int deleteItemAt(int position) //version 2, do not preserve order of items
{

    if ( position >= length )
        return NULL_VALUE;
    list[position] = list[length-1] ;
    length-- ;
    shrink();

    return SUCCESS_VALUE ;
}



int deleteItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE )
        return NULL_VALUE;
    deleteItemAt(position) ;
    shrink();
    return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    //printf("Current size: %d, current length: %d\n", listMaxSize, length);
}


int deleteLast()
{

    deleteItemAt(length);
    length--;
    shrink();


    return SUCCESS_VALUE;
}

void deleteall()
{
    while(length>0)
        deleteLast();


}

void Clear()
{
    deleteall();
    free(list);
    listMaxSize=0;

}


/*int main(void)
{
    initializeList();

    while(1)
    {
        cout << "1. Insert new item. 2. Delete item at. 3. Delete item." << endl;
        cout << "4.Find Length  5. Insert Item at 6.Delete Last Item" << endl;
        cout << "7.Delete All  8. Clear 9.Print  10. Exit " << endl;


        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
            cout << "\n" << endl;
        }
        else if(ch==2)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
            cout << "\n" << endl;
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
            cout << "\n" << endl;
        }
        else if(ch==4)
        {
            cout << "Length of the List is " << getLength() << endl;
            cout << "\n" << endl;
        }
        else if(ch==5)
        {
            int pos,item;
            cin >> pos >> item;
            insertItemAt(item,pos);
            cout << "\n" << endl;
        }
        else if(ch==6)
        {
            deleteLast();
            cout << "\n" << endl;
        }
        else if(ch==7)
        {
            deleteall();
            cout << "\n" << endl;
        }
        else if(ch==8)
        {
            Clear();
            cout << "\n" << endl;
        }
        else if(ch==9)
        {
            printList();
            cout << "\n" << endl;
        }
        else if(ch==10)
        {
            break;
        }
    }


}*/

//Main function for Task 7(postfix evaluation)

int main(void)
{
    initializeList();
    string s;
    int num1,num2,int_count=0,op_count=0;

    cout << "Enter the expression to be evaluated" << endl;
    cin >> s;

    //cout << s << endl;

    for(int i=0; i<s.length(); i++)
    {
        if(s[i]>='0' && s[i]<='9')
            int_count++;
        else if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/')
            op_count++;
    }

    if(s[0]=='+' || s[0]=='-' || s[0]=='*' || s[0]=='/')
    {
        cout << "Invalid statement. Operator at the start" << endl;
        return NULL_VALUE;

    }
    else if(s[1]=='+' || s[1]=='-' || s[1]=='*' || s[1]=='/')
    {
        cout << "Invalid statement. Operator follows only one operand. At least 2 required." << endl;
        return NULL_VALUE;

    }
    else if(int_count-1!=op_count)
    {
        cout << "Invalid statement. Not enough operators " << endl;
        return NULL_VALUE;


    }
    else
    {
        for(int i=0; i<s.length(); i++)
        {
            if(s[i]>='0' && s[i]<='9')
            {
                insertItem(s[i]-48);
            }
            else if(s[i]=='+')
            {
                num1=list[length-1];
                num2=list[length-2];
                deleteLast();
                deleteLast();
                num1=num1+num2;
                insertItem(num1);
            }
            else if(s[i]=='-')
            {
                num1=list[length-1];
                num2=list[length-2];
                deleteLast();
                deleteLast();
                num2=num2-num1;
                insertItem(num2);
            }
            else if(s[i]=='*')
            {
                num1=list[length-1];
                num2=list[length-2];
                deleteLast();
                deleteLast();
                num1=num1*num2;
                insertItem(num1);
            }
            else if(s[i]=='/')
            {
                num1=list[length-1];
                num2=list[length-2];
                deleteLast();
                deleteLast();
                if(num1==0)
                {
                    cout << "Invalid" << endl;
                    return NULL_VALUE;
                }
                num2=num2/num1;
                insertItem(num2);
            }

        }
    }

    int result=list[length-1];
    cout << result << endl;


    Clear();

}
