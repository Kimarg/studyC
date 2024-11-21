#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 5

typedef struct item {
    int ID;
    char name[100];
    int price;
    int store;
    int out;
    int totalsale;
} ITEM;

int item_count = 0;

void item_in(ITEM *p) {
    int id, store_num;
    if (item_count == SIZE) {
        printf("새로운 상품 추가시 상품 갯수가 초과됩니다.\n");
        return;
    }
    printf("=====================================\n");
    printf("상품ID: ");
    scanf("%d", &id);

    for (int i = 0; i < item_count; i++) {
        if (p[i].ID == id) {
            printf("해당 ID의 상품이 존재합니다. 상품명: %s, 잔여 재고: %d\n", p[i].name, p[i].store);
            printf("상품명 업데이트: ");
            scanf("%s", p[i].name);
            printf("판매가격 업데이트: ");
            scanf("%d", &p[i].price);
            printf("추가 입고 수량: ");
            scanf("%d", &store_num);
            p[i].store += store_num;
            printf("업데이트가 완료되었습니다.\n");
            printf("=====================================\n");
            return;
        }
    }

    printf("새 상품을 추가합니다.\n");
    p[item_count].ID = id;
    printf("상품명: ");
    scanf("%s", p[item_count].name);
    printf("입고량: ");
    scanf("%d", &p[item_count].store);
    printf("판매가격: ");
    scanf("%d", &p[item_count].price);
    p[item_count].out = 0;
    p[item_count].totalsale = 0;
    item_count++;
    printf("상품 추가가 완료되었습니다.\n");
    printf("=====================================\n");
}

void item_sell(ITEM *p) {
    int id, temp;
    printf("=====================================\n");
    printf("상품ID: ");
    scanf("%d", &id);

    for (int i = 0; i < item_count; i++) {
        if (p[i].ID == id) {
            printf("ID(%d) 상품명(%s)의 판매량: ", p[i].ID, p[i].name);
            scanf("%d", &temp);
            if (temp > p[i].store) {
                printf("재고가 부족합니다! 현재 재고: %d\n", p[i].store);
                return;
            }
            p[i].out += temp;
            p[i].store -= temp;
            p[i].totalsale += temp * p[i].price;
            printf("판매가 완료되었습니다.\n");
            printf("=====================================\n");
            return;
        }
    }
    printf("해당 ID가 존재하지 않습니다.\n");
    printf("=====================================\n");
}

void item_select_info(ITEM *p) {
    int id;
    printf("=====================================\n");
    printf("상품ID: ");
    scanf("%d", &id);

    for (int i = 0; i < item_count; i++) {
        if (p[i].ID == id) {
            printf("상품명: %s\n", p[i].name);
            printf("가격: %d\n", p[i].price);
            printf("잔여재고: %d\n", p[i].store);
            printf("판매량: %d\n", p[i].out);
            printf("총 판매금액: %d\n", p[i].totalsale);
            printf("=====================================\n");
            return;
        }
    }
    printf("해당 ID가 존재하지 않습니다.\n");
    printf("=====================================\n");
}

void all_print(ITEM *p) {
    printf("=====================================\n");
    if (item_count == 0) {
        printf("등록된 상품이 없습니다.\n");
        printf("=====================================\n");
        return;
    }

    printf("전체 상품 정보:\n");
    for (int i = 0; i < item_count; i++) {
        printf("ID: %d 상품명: %s 판매가격: %d 잔여재고: %d 판매량: %d 총 판매금액: %d\n",
               p[i].ID, p[i].name, p[i].price, p[i].store, p[i].out, p[i].totalsale);
    }
    printf("=====================================\n");
}

void save_to_file(ITEM *p) {
    FILE *fp = fopen("item_data.txt", "w");
    if (fp == NULL) {
        printf("파일 저장에 실패했습니다.\n");
        return;
    }

    for (int i = 0; i < item_count; i++) {
        fprintf(fp, "%d %s %d %d %d %d\n", p[i].ID, p[i].name, p[i].price, p[i].store, p[i].out, p[i].totalsale);
    }

    fclose(fp);
    printf("데이터가 파일에 저장되었습니다.\n");
}

void load_from_file(ITEM *p) {
    FILE *fp = fopen("item_data.txt", "r");
    if (fp == NULL) {
        printf("파일이 존재하지 않습니다. 새로 시작합니다.\n");
        return;
    }

    item_count = 0;
    while (fscanf(fp, "%d %s %d %d %d %d", &p[item_count].ID, p[item_count].name, &p[item_count].price,
                  &p[item_count].store, &p[item_count].out, &p[item_count].totalsale) == 6) {
        item_count++;
    }

    fclose(fp);
    printf("파일에서 데이터를 불러왔습니다.\n");
}

int main() {
    ITEM items[SIZE] = {0};
    int choice;

    load_from_file(items);

    do {
        printf("\n1. 입고  2. 판매  3. 개별현황  4. 전체현황+저장  5. 종료\n");
        printf("원하는 메뉴를 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                item_in(items);
                break;
            case 2:
                item_sell(items);
                break;
            case 3:
                item_select_info(items);
                break;
            case 4:
                save_to_file(items);
                all_print(items);
                break;
            case 5:
                save_to_file(items);
                printf("프로그램을 종료합니다.\n");
                break;
            default:
                printf("올바른 메뉴를 선택하세요.\n");
        }
    } while (choice != 5);

    return 0;
}
