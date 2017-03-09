#include <stdio.h>
#include <float.h>

int main()
{
    int n;
    scanf("%d", &n);

    float min = FLT_MAX;
    float max = -FLT_MAX;
    for(int i = 0; i < n; ++i)
    {
        int people, kms;
        scanf("%d %d", &people, &kms);

        int pricePerKm = kms < 500 ? 50 : 80;
        float price = kms * pricePerKm / (float)people;
        if(price > max)
        {
            max = price;
        }
        if(price < min)
        {
            min = price;
        }
    }

    printf("Custo minimo %.2f\n", min);
    printf("Custo maximo %.2f\n", max);

    return 0;
}
