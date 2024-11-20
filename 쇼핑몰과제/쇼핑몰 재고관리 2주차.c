#include <stdio.h>
#define SIZE 100

void calculate_inventory(int *put_item, int *sell_item, int item_type);
float calculate_total(int *arr, int item_type);
void find_max_min(int *sell_item, int item_type, int *max, int *min);
void check_stock_shortage(int *put_item, int *sell_item, int item_type);

int main() {
    int item_type = 0;
    int put_item[SIZE] = {0};
    int sell_item[SIZE] = {0};
    scanf("%d", &item_type);
    for (int i = 0; i < item_type; i++) {
        scanf("%d", &put_item[i]);
    }
    for (int i = 0; i < item_type; i++) {
        scanf("%d", &sell_item[i]);
    }
    calculate_inventory(put_item, sell_item, item_type);
    return 0;
}

void calculate_inventory(int *put_item, int *sell_item, int item_type) {
    int max = 0, min = 0;
    float all_put_item = calculate_total(put_item, item_type);
    float all_sell_item = calculate_total(sell_item, item_type);

    printf("재고 수량 : ");
    for (int i = 0; i < item_type; i++) {
        printf("%d ", *(put_item + i) - *(sell_item + i));
    }

    printf("\n총 판매량 : %2.0f (판매율 : %2.2f%%)", all_sell_item, (all_sell_item / all_put_item) * 100.0);

    find_max_min(sell_item, item_type, &max, &min);
    printf("\n가장 많이 판매된 상품 : ID %d , 판매량 %d", max + 1, *(sell_item + max));
    printf("\n가장 적게 판매된 상품 : ID %d , 판매량 %d", min + 1, *(sell_item + min));

    check_stock_shortage(put_item, sell_item, item_type);
}

float calculate_total(int *arr, int item_type) {
    float total = 0.0;
    for (int i = 0; i < item_type; i++) {
        total += *(arr + i);
    }
    return total;
}

void find_max_min(int *sell_item, int item_type, int *max, int *min) {
    for (int i = 1; i < item_type; i++) {
        if (*(sell_item + *max) < *(sell_item + i)) {
            *max = i;
        }
        if (*(sell_item + *min) > *(sell_item + i)) {
            *min = i;
        }
    }
}

void check_stock_shortage(int *put_item, int *sell_item, int item_type) {
    for (int i = 0; i < item_type; i++) {
        if (3 > (*(put_item + i) - *(sell_item + i))) {
            printf("\n상품 ID %d : 재고부족(%d)", i + 1, *(put_item + i) - *(sell_item + i));
        }
    }
}
