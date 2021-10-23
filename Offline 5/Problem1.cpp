#include<bits/stdc++.h>
#include <string>

using namespace std;

class treeNode
{

public:
    char c;
    int freq;
    treeNode *leftChild, *rightChild;
    /*bool operator< (const treeNode& rhs)
    {
        if(freq<rhs.freq)
            return true;

        return false;
    }*/

};

struct MyComparator{
    bool operator() (treeNode* const& lhs, treeNode* const& rhs)
    {
        return lhs->freq > rhs->freq;
    }
};

string toString(int num)
{
	string s;
	while(num)
	{
		s += '0' + (num % 10 ) ;
		num /= 10;
	}
	reverse(s.begin(),s.end());
	return s;
}

void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

treeNode* createNode(char ch, int frequency, treeNode*  left, treeNode* right)
{
    treeNode *temp=new treeNode;
    temp->leftChild=left;
    temp->rightChild=right;
    temp->c=ch;
    temp->freq=frequency;

    return temp;

}


treeNode* buildTree(vector<char> charvc, vector<int> freqvc, int n)
{
    priority_queue<treeNode*, vector<treeNode*>, MyComparator > pq;

    for(int i = 0; i < n; i++)
    {
        treeNode* node=createNode(charvc[i],freqvc[i],NULL,NULL);
        pq.push(node);
    }

    //cout<< pq.top()->c << endl;

    while(pq.size()>1)
    {
        treeNode* tn1=pq.top();
        pq.pop();
        treeNode* tn2=pq.top();
        pq.pop();
        int x=tn1->freq+tn2->freq;
        treeNode* newNode=createNode('&',x,tn1,tn2);
        pq.push(newNode);
    }

    return pq.top();
}



void printCodes(treeNode* root, int arr[], int top)
{
    if (root->leftChild) {

        arr[top] = 0;
        printCodes(root->leftChild, arr, top + 1);
    }

    if (root->rightChild) {

        arr[top] = 1;
        printCodes(root->rightChild, arr, top + 1);
    }

    if (!(root->leftChild) && !(root->rightChild)) {

        printf("%c ", root->c);
        printArray(arr,top);

    }
}

void huffmanCode(vector<char> charvc, vector<int> freqvc, int n)
{
    treeNode* root=buildTree(charvc,freqvc,n);

    /*cout << root->c << " " << root->freq << endl;
    cout << root->leftChild->c << " " << root->leftChild->freq << endl;
    cout << root->rightChild->c << " " << root->rightChild->freq << endl;*/

    int arr[200],top=0;

    /*for(int i=0; i<200; i++)
        arr[i]=0;*/

    printCodes(root,arr,top);
}

int main(void)
{
    int n,x;
    char c;
    vector<char> charvc;
    vector<int> freqvc;
    cin >> n;

    for(int i=0; i<n; i++)
    {
        cin >> c;
        charvc.push_back(c);
        cin >> x;
        freqvc.push_back(x);
    }

    /*for(int i=0; i<n; i++)
    {
        cout << charvc[i] << " " << freqvc[i] << endl;
    }*/

    huffmanCode(charvc,freqvc,n);

    /*treeNode* node= buildTree(charvc,freqvc,n);

    cout << node->c << " " << node->freq << endl;*/

    return 0;

}


