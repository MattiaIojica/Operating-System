#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    scanf("%d", &n);

    int *m = (int*)malloc((n * n) * sizeof(int));

    for(int i = 0; i < n * n; i++)
            scanf("%d", (m + i));

    printf("Elementele matricei: ");
    for(int i = 0; i < n * n; i++)
        printf("%d ", *(m + i));

    if(n % 2 == 1)
        printf("\n\nElementul din intersectie: %d\n\n", *(m + n * n / 2));

    printf("Diagonala principala: ");
    for(int i = 0; i < n; i++)
                printf("%d ", *(m + i * (n + 1)));


    printf("\n\nDiagonala secundara: ");

    for(int i = 0; i < n; i++)
                printf("%d ", *(m + (i + 1) * (n - 1)));

    printf("\n");

    return 0;
}


