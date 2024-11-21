#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5

typedef struct {
    int id;
    char name[50];
    int price;
    int stock;
    int sold;
    int totalSales;
} Product;

void addOrUpdateProduct(Product products[], int *productCount) {
    int id, quantity, price, index = -1;
    char name[50];

    if (*productCount >= MAX_PRODUCTS) {
        printf("상품 갯수 초과! 더 이상 추가할 수 없습니다.\n");
        return;
    }

    printf("상품 ID : ");
    scanf("%d", &id);

    for (int i = 0; i < *productCount; i++) {
        if (products[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) { // 신규 상품 추가
        index = *productCount;
        products[index].id = id;
        (*productCount)++;
    }

    printf("상품명 : ");
    scanf("%s", name);
    printf("입고량 : ");
    scanf("%d", &quantity);
    printf("판매가격 : ");
    scanf("%d", &price);

    strcpy(products[index].name, name);
    products[index].stock += quantity;
    products[index].price = price;

    printf("상품이 추가/업데이트 되었습니다.\n");
}

void sellProduct(Product products[], int productCount) {
    int id, quantity, index = -1;

    printf("상품 ID : ");
    scanf("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("존재하지 않는 상품 ID입니다.\n");
        return;
    }

    printf("판매량 : ");
    scanf("%d", &quantity);

    if (quantity > products[index].stock) {
        printf("재고 부족! (현재 재고: %d)\n", products[index].stock);
    } else {
        products[index].stock -= quantity;
        products[index].sold += quantity;
        products[index].totalSales += quantity * products[index].price;
        printf("판매가 완료되었습니다.\n");
    }
}

void viewIndividualProduct(Product products[], int productCount) {
    int id, index = -1;

    printf("상품 ID : ");
    scanf("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("존재하지 않는 상품 ID입니다.\n");
        return;
    }

    printf("상품 정보\n");
    printf("ID : %d\n", products[index].id);
    printf("이름 : %s\n", products[index].name);
    printf("가격 : %d\n", products[index].price);
    printf("재고 : %d\n", products[index].stock);
    printf("판매량 : %d\n", products[index].sold);
    printf("총 판매금액 : %d\n", products[index].totalSales);
}

void viewAllProducts(Product products[], int productCount) {
    int totalSold = 0, totalSales = 0, totalStock = 0;
    int maxSold = 0, minSold = 1e9;
    int maxSoldID = -1, minSoldID = -1;

    printf("전체 상품 현황\n");

    for (int i = 0; i < productCount; i++) {
        totalSold += products[i].sold;
        totalSales += products[i].totalSales;
        totalStock += products[i].stock;

        if (products[i].sold > maxSold) {
            maxSold = products[i].sold;
            maxSoldID = i;
        }
        if (products[i].sold < minSold) {
            minSold = products[i].sold;
            minSoldID = i;
        }

        printf("ID: %d, 이름: %s, 가격: %d, 재고: %d, 판매량: %d, 총 판매금액: %d\n",
               products[i].id, products[i].name, products[i].price,
               products[i].stock, products[i].sold, products[i].totalSales);
    }

    printf("\n총 판매량: %d, 총 판매 금액: %d\n", totalSold, totalSales);

    if (maxSoldID != -1) {
        printf("가장 많이 판매된 상품: ID%d, 이름: %s, 판매량: %d\n",
               products[maxSoldID].id, products[maxSoldID].name, maxSold);
    }
    if (minSoldID != -1) {
        printf("가장 적게 판매된 상품: ID%d, 이름: %s, 판매량: %d\n",
               products[minSoldID].id, products[minSoldID].name, minSold);
    }
}

int main() {
    Product products[MAX_PRODUCTS] = {0};
    int productCount = 0;
    int choice;

    while (1) {
        printf("\n[쇼핑몰 관리 프로그램]\n");
        printf("원하는 메뉴를 선택하세요.(1. 입고, 2. 판매, 3. 개별현황, 4. 전체현황, 5. 종료)\n> ");
        scanf("%d", &choice);

        if (choice == 1) {
            addOrUpdateProduct(products, &productCount);
        } else if (choice == 2) {
            sellProduct(products, productCount);
        } else if (choice == 3) {
            viewIndividualProduct(products, productCount);
        } else if (choice == 4) {
            viewAllProducts(products, productCount);
        } else if (choice == 5) {
            printf("프로그램을 종료합니다.\n");
            break;
        } else {
            printf("잘못된 입력입니다. 다시 시도해주세요.\n");
        }
    }

    return 0;
}
