//This file test the behaviour of all the functions and structs involved in 
// an electric trading reporting program (ETR). 
//ETR allows users to trade stocks from their own computers without human 
//intervention.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etrstock.h"
#include "etrtrade.h"
#include "etr_report.h"

int main(void){

//Read stock file and load the data
  FILE * fstocks;
  fstocks = fopen("stocks.tex","r");
  struct Node_stock * head_stock_list = NULL;

  head_stock_list = createStockList(fstocks,head_stock_list);
  head_stock_list = listSort(head_stock_list);
  
  struct Node_stock * list_ptr = head_stock_list;
  while(list_ptr != NULL){
   printf("%s \t %f \n",list_ptr->data.stock_name, list_ptr->data.stock_price);
   list_ptr = list_ptr->next;
  }

  fclose(fstocks);
  
//Read each trade and process the trade
  FILE * ftrades;
  ftrades = fopen("trades.tex","r");


  struct executed_trade BUYS[MAX_BUYS_RECORDED];
  struct executed_trade SELLS[MAX_SELLS_RECORDED]; 
  int NBuys,NSells;
//-------------------------------------------------------------
  //Load data into trade_request struct 

 char str[MAX_TRADE_REQUEST_LENGTH];//Maybe use another define?
while(  fscanf(ftrades,"%s", str) != EOF){
  struct trade_request t = load_request(str);

  double stock_price;
  stock_price = look_up_stock_price(t.stock_name,head_stock_list);



    process_trade(BUYS,SELLS,t,stock_price, &NBuys, &NSells);

 }

 printf("%i \n", NBuys);
 
 mergeSort(BUYS,0, NBuys-1);
 for(int i = 0; i < NBuys; i++){
   printf("Stock: %s User: %s Num share: %i Price: %f \n", BUYS[i].stock_name, BUYS[i].user_name,BUYS[i].num_shares,BUYS[i].traded_price);
 }

 printf("\n");
 printf("Trade Type: SELL\n");

 mergeSort(SELLS,0, NSells-1);
 for(int i = 0; i < NSells; i++){
   printf("Stock: %s User: %s \n", SELLS[i].stock_name,SELLS[i].user_name);
 }

 
 fclose(ftrades);
 /*
 printf("\n");
 printf("Trade Type: BUY \n");
 printf("------------------------------------------ \n");
 printf("Stock: %s\n", BUYS[0].stock_name);
 printf("Stock: %s\n", BUYS[1].stock_name);
 
 printf("\n");
 printf("Trade Type: SELL\n");
 printf("------------------------------------------\n");
 printf("Stock: %s\n", SELLS[0].stock_name);

 */
    return 0;

}

