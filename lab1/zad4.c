#include<stdio.h>
#include<math.h>


int silnia(int liczba)
{
        if(liczba == 1)
        {
                return liczba;
        }
        return liczba * silnia(liczba-1);
}

int main()
{

    int liczba = -1, n = 1, x = 1;
}

double exponent()
{
    for(n; n < 20 ; n++)
    {
       liczba += pow(x,n)/silnia(n);
    }
    printf("%d",liczba);

    return 0;

}
