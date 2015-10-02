//This file test the behaviour of all the functions and structs involved in 
// an electric trading reporting program (ETR). 
//ETR allows users to trade stocks from their own computers without human 
//intervention.
#include<stdio.h>
#include <stdlib.h>
#include "etrstock.h"

#define MAX_USER_NAME_LENGTH 20

struct trade_request{
  char user_name[MAX_USER_NAME_LENGTH];
  char request;
  char stock_name[MAX_STOCK_NAME_LENGTH];
  int num_shares;
  int user_price;
};


int main(void){

//Read stock file and load the data
  FILE * fstocks;
  fstocks = fopen("stocks.tex","r");
  struct Node_stock * head_stock_list = NULL;

  head_stock_list = createStockList(fstocks,head_stock_list);
  head_stock_list = listSort(head_stock_list);
  
  while(head_stock_list != NULL){
   printf("%s \t %f \n",head_stock_list->data.stock_name, head_stock_list->data.stock_price);
   head_stock_list = head_stock_list->next;
  }

  fclose(fstocks);

 
//Read each trade and process the trade
//Print report on executed trades

  return 0;
}

