#include <stdio.h>
int main()
{
    int item[99];
    int count = 0;
    int i = 0;
    int a = 0;
    printf("상품종류를 입력하세요 : ");
    scanf("%d",&count);
    printf("상품 별 입고수량을 입력해주세요 : ");
    for (i = 0; i < count; i++)
    {
        scanf("%d",&item[i]);
    }
    //printf("%d %d %d %d %d",item[0],item[1],item[2],item[3],item[4]); <===== cheak code
    printf("상품 별 판매수량을 입력해주세요 : ");
    for (i = 0; i < count; i++)
    {
        scanf("%d",&a);
        item[i] -= a;
    }
    printf("ID 입력하세요 : ");
    scanf("%d",&a);
    a -= 1;
    //printf("%d",a); <===== cheak code
    printf("아이디 재고 수량입니다.\n%d\n",item[a]);
    
    for (i = 0; i < count; i++)
    {
        printf("%d ",item[i]);
    }
    printf("모든 제품의 재고 수량입니다.");
    
    return 0;
}