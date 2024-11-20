#include <stdio.h>
#define SIZE 100
int main()
{
    int i = 0;
    int item_type = 0;
    int max = 0;
    int min = 0;
    float all_sell_item = 0.0;
    float all_put_item = 0.0;
    int put_item[SIZE] = {0};
    int sell_item[SIZE] = {0};
    scanf("%d",&item_type);
    for(i = 0;i<item_type;i++){
        scanf("%d",&put_item[i]);
        all_put_item += put_item[i];
    }
    for(i = 0;i<item_type;i++){
        scanf("%d",&sell_item[i]);
        all_sell_item += sell_item[i];
    }
    printf("재고 수량 : ");
    for(i = 0;i<item_type;i++){
        printf("%d ",put_item[i]-sell_item[i]);
    }
    printf("\n총 판매량 : %2.0f (판매율 : %2.2f%%)",all_sell_item,(all_sell_item/all_put_item)*100.0);
    for(i = 1;i<item_type;i++){
        if (sell_item[max] < sell_item[i]) max = i;
        if (sell_item[min] > sell_item[i]) min = i;
    }
    printf("\n가장 많이 판매된 상품 : ID %d , 판매량 %d",max+1,sell_item[max]);
    printf("\n가장 적게 판매된 상품 : ID %d , 판매량 %d",min+1,sell_item[min]);
    for(i= 0;i<item_type;i++){
        if(3 > put_item[i]-sell_item[i]) printf("\n상품 ID %d : 재고부족(%d)",i+1,put_item[i]-sell_item[i]);
    }
    return 0;
}