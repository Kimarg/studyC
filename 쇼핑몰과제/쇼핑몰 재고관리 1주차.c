#include <stdio.h>
#define SIZE 100
int main()
{
    int i = 0;
    int item_type = 0;
    int item_ID = 0;
    int put_item[SIZE] = {0};
    int sell_item[SIZE] = {0};
    
    scanf("%d",&item_type);
    for(i = 0;i<item_type;i++){
        scanf("%d",&put_item[i]);
    }
    for(i = 0;i<item_type;i++){
        scanf("%d",&sell_item[i]);
    }
    scanf("%d",&item_ID);
    printf("\n%d\n",put_item[item_ID]-sell_item[item_ID]);
    for(i = 0;i<item_type;i++){
        printf("%d ",put_item[i]-sell_item[i]);
    }
    
return 0;
}
