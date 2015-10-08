//This file test the behaviour of all the functions and structs involved in 
// an electric trading reporting program (ETR). 
//ETR allows users to trade stocks from their own computers without human 
//intervention.
//SO CONFUSED ABOUT GIT and branching
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

  fclose(fstocks);
  
//Read each trade and process the trade
  FILE * ftrades;
  ftrades = fopen("trades.tex","r");

  struct executed_trade BUYS[MAX_BUYS_RECORDED];
  struct executed_trade SELLS[MAX_SELLS_RECORDED]; 
  int NBuys,NSells;

 char str[MAX_TRADE_REQUEST_LENGTH];//Maybe use another define?
while(  fscanf(ftrades,"%s", str) != EOF){
  struct trade_request t = load_request(str);
  double stock_price;
  stock_price = look_up_stock_price(t.stock_name,head_stock_list);
  process_trade(BUYS,SELLS,t,stock_price, &NBuys, &NSells);
 }

 fclose(ftrades);

 //Print report to file
 FILE * freport;
 freport = fopen ("report.tex", "w");

 printReport(freport,BUYS,SELLS,NBuys,NSells);

 fclose(freport); 
 return 0;
}

