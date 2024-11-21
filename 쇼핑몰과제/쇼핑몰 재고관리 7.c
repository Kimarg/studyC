#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item {
    int ID;
    char name[100];
    int price;
    int store;
    int out;
    int totalsale;
} ITEM;

ITEM *items = NULL; // 동적 배열 포인터
int item_count = 0;
const int MAX_ITEMS = 5; // 최대 상품 개수 고정

void add_item() {
    if (item_count == MAX_ITEMS) {
        printf("상품 갯수가 초과되었습니다. 더 이상 추가할 수 없습니다.\n");
        return;
    }

    int id, store_num, found = 0;
    printf("상품ID: ");
    scanf("%d", &id);

    // 기존 상품 확인 및 업데이트
    for (int i = 0; i < item_count; i++) {
        if (items[i].ID == id) {
            found = 1;
            printf("해당 ID의 상품이 존재합니다. 상품명: %s, 잔여 재고: %d\n", items[i].name, items[i].store);
            printf("상품명 업데이트: ");
            scanf("%s", items[i].name);
            printf("판매가격 업데이트: ");
            scanf("%d", &items[i].price);
            printf("추가 입고 수량: ");
            scanf("%d", &store_num);
            items[i].store += store_num;
            printf("업데이트가 완료되었습니다.\n");
            return;
        }
    }

    // 새 상품 추가
    if (!found) {
        items = realloc(items, (item_count + 1) * sizeof(ITEM));
        if (!items) {
            printf("메모리 할당에 실패했습니다.\n");
            exit(1);
        }

        items[item_count].ID = id;
        printf("상품명: ");
        scanf("%s", items[item_count].name);
        printf("입고량: ");
        scanf("%d", &items[item_count].store);
        printf("판매가격: ");
        scanf("%d", &items[item_count].price);
        items[item_count].out = 0;
        items[item_count].totalsale = 0;
        item_count++;
        printf("상품 추가가 완료되었습니다.\n");
    }
}

void sell_item() {
    int id, temp;
    printf("상품ID: ");
    scanf("%d", &id);

    for (int i = 0; i < item_count; i++) {
        if (items[i].ID == id) {
            printf("ID(%d) 상품명(%s)의 판매량: ", items[i].ID, items[i].name);
            scanf("%d", &temp);
            if (temp > items[i].store) {
                printf("재고가 부족합니다! 현재 재고: %d\n", items[i].store);
                return;
            }
            items[i].out += temp;
            items[i].store -= temp;
            items[i].totalsale += temp * items[i].price;
            printf("판매가 완료되었습니다.\n");
            return;
        }
    }
    printf("해당 ID가 존재하지 않습니다.\n");
}

void view_item() {
    int id;
    printf("상품ID: ");
    scanf("%d", &id);

    for (int i = 0; i < item_count; i++) {
        if (items[i].ID == id) {
            printf("상품명: %s\n", items[i].name);
            printf("가격: %d\n", items[i].price);
            printf("잔여재고: %d\n", items[i].store);
            printf("판매량: %d\n", items[i].out);
            printf("총 판매금액: %d\n", items[i].totalsale);
            return;
        }
    }
    printf("해당 ID가 존재하지 않습니다.\n");
}

void view_all_items() {
    if (item_count == 0) {
        printf("등록된 상품이 없습니다.\n");
        return;
    }

    printf("전체 상품 정보:\n");
    for (int i = 0; i < item_count; i++) {
        printf("ID: %d 상품명: %s 판매가격: %d 잔여재고: %d 판매량: %d 총 판매금액: %d\n",
               items[i].ID, items[i].name, items[i].price, items[i].store, items[i].out, items[i].totalsale);
    }
}

void save_items() {
    FILE *fp = fopen("items.bin", "wb");
    if (!fp) {
        printf("파일 저장에 실패했습니다.\n");
        return;
    }

    fwrite(&item_count, sizeof(int), 1, fp); // 상품 개수 저장
    fwrite(items, sizeof(ITEM), item_count, fp); // 상품 정보 저장
    fclose(fp);
    printf("상품 정보가 저장되었습니다.\n");
}

void load_items() {
    FILE *fp = fopen("items.bin", "rb");
    if (!fp) {
        printf("저장된 파일이 없습니다. 새로 시작합니다.\n");
        return;
    }

    fread(&item_count, sizeof(int), 1, fp); // 상품 개수 불러오기
    items = realloc(items, item_count * sizeof(ITEM)); // 동적 메모리 할당
    if (!items) {
        printf("메모리 할당에 실패했습니다.\n");
        fclose(fp);
        exit(1);
    }
    fread(items, sizeof(ITEM), item_count, fp); // 상품 정보 불러오기
    fclose(fp);
    printf("상품 정보가 로드되었습니다.\n");
}

int main() {
    items = malloc(0); // 초기 동적 배열 할당
    if (!items) {
        printf("메모리 할당에 실패했습니다.\n");
        return 1;
    }

    load_items();

    int choice;
    do {
        printf("\n1. 입고  2. 판매  3. 개별현황  4. 전체현황  5. 저장  6. 불러오기  7. 종료\n");
        printf("원하는 메뉴를 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_item();
                break;
            case 2:
                sell_item();
                break;
            case 3:
                view_item();
                break;
            case 4:
                view_all_items();
                break;
            case 5:
                save_items();
                break;
            case 6:
                load_items();
                break;
            case 7:
                printf("프로그램을 종료합니다.\n");
                break;
            default:
                printf("올바른 메뉴를 선택하세요.\n");
        }
    } while (choice != 7);

    free(items); // 동적 메모리 해제
    return 0;
}
