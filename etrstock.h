#ifndef ETR_STOCK_H
#define ETR_STOCK_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_STOCK_NAME_LENGTH 15

struct stock{
  double stock_price;
  char stock_name[MAX_STOCK_NAME_LENGTH];
};

struct Node_stock{
  struct stock data;
  struct Node_stock * next;
};

struct Node_stock * createStockList(FILE * file, struct Node_stock * head );
struct Node_stock *listSort(struct Node_stock *list);
double look_up_stock_price(char search_name[MAX_STOCK_NAME_LENGTH],struct Node_stock* head); 
#endif
