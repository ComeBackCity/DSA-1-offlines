#include<bits/stdc++.h>

using namespace std;

void lcs( char *X, char *Y, int m, int n )
{
    int table[m+1][n+1];
    int i, j;


    for (i=0; i<=m; i++)
    {
        for (j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
            {
                table[i][j] = 0;
            }

            else if (X[i-1] == Y[j-1])
            {
                table[i][j] = table[i-1][j-1] + 1;
            }

            else
            {
                table[i][j] = max(table[i-1][j], table[i][j-1]);
            }
        }
    }


    int idx = table[m][n];

    char lcs[idx+1];
    lcs[idx] = '\0';


    i = m, j = n;
    while (i > 0 && j > 0)
    {

        if (X[i-1] == Y[j-1])
        {
            lcs[idx-1] = X[i-1];
            i--;
            j--;
            idx--;
        }


        else if (table[i-1][j] > table[i][j-1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }


    cout << "LCS of " << X << " and " << Y << " is " << lcs;
}



int max(int a, int b)
{
    return (a > b)? a : b;
}


int main()
{
    char X[100],Y[100];

    gets(X);
    gets(Y);

    int m = strlen(X);
    int n = strlen(Y);

    lcs(X, Y, m, n);

    return 0;
}
