#include <stdio.h>
#include <string.h>
#define PRODUCT_COUNT 5
#define NAME_LENGTH 50

void restock(int *stock, int *restocked) {
    int choice, id, qty;
    printf("입고수량 입력: 전체 상품 입고수량 입력 1, 개별 상품 입력 2를 선택\n> ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("전체 상품 입고수량 입력 (공백으로 구분하여 %d개 입력):\n> ", PRODUCT_COUNT);
        for (int i = 0; i < PRODUCT_COUNT; i++) {
            scanf("%d", &qty);
            stock[i] += qty;
            restocked[i] += qty;
        }
    } else if (choice == 2) {
        printf("상품 ID 입력 (0 ~ %d):\n> ", PRODUCT_COUNT - 1);
        scanf("%d", &id);
        if (id >= 0 && id < PRODUCT_COUNT) {
            printf("입고수량 입력:\n> ");
            scanf("%d", &qty);
            stock[id] += qty;
            restocked[id] += qty;
        } else {
            printf("잘못된 상품 ID입니다.\n");
        }
    }
}

void sell(int *stock, int *sold) {
    int choice, id, qty;
    printf("판매수량 입력: 전체 상품 판매수량 입력 1, 개별 상품 입력 2를 선택\n> ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("전체 상품 판매수량 입력 (공백으로 구분하여 %d개 입력):\n> ", PRODUCT_COUNT);
        for (int i = 0; i < PRODUCT_COUNT; i++) {
            scanf("%d", &qty);
            if (qty <= stock[i]) {
                stock[i] -= qty;
                sold[i] += qty;
            } else {
                printf("상품 ID %d의 재고가 부족합니다. (남은 재고: %d)\n", i, stock[i]);
            }
        }
    } else if (choice == 2) {
        printf("상품 ID 입력 (0 ~ %d):\n> ", PRODUCT_COUNT - 1);
        scanf("%d", &id);
        if (id >= 0 && id < PRODUCT_COUNT) {
            printf("판매수량 입력:\n> ");
            scanf("%d", &qty);
            if (qty <= stock[id]) {
                stock[id] -= qty;
                sold[id] += qty;
            } else {
                printf("상품 ID %d의 재고가 부족합니다. (남은 재고: %d)\n", id, stock[id]);
            }
        } else {
            printf("잘못된 상품 ID입니다.\n");
        }
    }
}

void enterProductNames(char names[PRODUCT_COUNT][NAME_LENGTH]) {
    for (int i = 0; i < PRODUCT_COUNT; i++) {
        printf("ID%d 상품명: ", i + 1);
        scanf("%s", names[i]);
    }
}

void displayStatus(int *stock, int *restocked, int *sold, char names[PRODUCT_COUNT][NAME_LENGTH]) {
    int totalSold = 0, totalRestocked = 0, maxSold = 0, minSold = 1e9;
    int maxSoldID = -1, minSoldID = -1;

    printf("재고수량: ");
    for (int i = 0; i < PRODUCT_COUNT; i++) {
        printf("%d ", stock[i]);
        totalSold += sold[i];
        totalRestocked += restocked[i];
        if (sold[i] > maxSold) {
            maxSold = sold[i];
            maxSoldID = i;
        }
        if (sold[i] < minSold) {
            minSold = sold[i];
            minSoldID = i;
        }
    }
    printf("\n총 판매량: %d (판매율 %.2f%%)\n", totalSold, totalRestocked > 0 ? (totalSold * 100.0 / totalRestocked) : 0);
    if (maxSoldID != -1) printf("가장 많이 판매된 상품: ID%d, 상품명: %s, 판매량 %d\n", maxSoldID + 1, names[maxSoldID], maxSold);
    if (minSoldID != -1) printf("가장 적게 판매된 상품: ID%d, 상품명: %s, 판매량 %d\n", minSoldID + 1, names[minSoldID], minSold);

    for (int i = 0; i < PRODUCT_COUNT; i++) {
        if (stock[i] == 0) printf("상품 ID%d: 상품명: %s 재고부족(0)\n", i + 1, names[i]);
    }
}

int main() {
    int stock[PRODUCT_COUNT] = {0};
    int restocked[PRODUCT_COUNT] = {0};
    int sold[PRODUCT_COUNT] = {0};
    char names[PRODUCT_COUNT][NAME_LENGTH] = {"미정", "미정", "미정", "미정", "미정"};
    int choice;

    while (1) {
        printf("\n[쇼핑몰 관리 프로그램]\n");
        printf("원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 상품현황, 4. 상품명 입력, 5. 종료)\n> ");
        scanf("%d", &choice);

        if (choice == 1) {
            restock(stock, restocked);
        } else if (choice == 2) {
            sell(stock, sold);
        } else if (choice == 3) {
            displayStatus(stock, restocked, sold, names);
        } else if (choice == 4) {
            enterProductNames(names);
        } else if (choice == 5) {
            printf("프로그램을 종료합니다.\n");
            break;
        } else {
            printf("잘못된 선택입니다. 다시 시도해주세요.\n");
        }
    }
    return 0;
}
