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
/*
#define MAX_BUYS_RECORDED 100
#define MAX_SELLS_RECORDED 100

#define MAX_TRADE_REQUEST_LENGTH 100
struct executed_trade{
  char user_name[MAX_USER_NAME_LENGTH];
  char stock_name[MAX_STOCK_NAME_LENGTH];
  int num_shares;
  double traded_price;
  };*/

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

//-------------------------------------------------------------
  //Load data into trade_request struct 

 char str[MAX_TRADE_REQUEST_LENGTH];//Maybe use another define?
while(  fscanf(ftrades,"%s", str) != EOF){
  struct trade_request t = load_request(str);

  double stock_price;
  stock_price = look_up_stock_price(t.stock_name,head_stock_list);

  //---------------------------------------------------------------------------  
  void process_trade(BUYS,SELLS,t,stoc_price);
    /*  
double traded_price;
  if(stock_price > 0 ){
    if(t.request == 'B'){
      if(t.user_price >= stock_price){
	traded_price = (t.user_price+stock_price)/2;
	//record transactio
        strcpy(BUYS[Nbuys].user_name, t.user_name);
        strcpy(BUYS[Nbuys].stock_name, t.stock_name);
        BUYS[Nbuys].num_shares = t.num_shares;
        BUYS[Nbuys].traded_price = traded_price; 
        Nbuys++;
        printf("BUY EXECUTED. Traded price: %f \n",traded_price);
      }else{
	//error transaction not processed. User buying price below stock price
	printf("NOT EXECUTED. user asking price %f below stock price \n", t.user_price);
      }
    }else if(t.request == 'S'){
      if(t.user_price <= stock_price){
	traded_price = (t.user_price+stock_price)/2;
	//record transaction
        strcpy(SELLS[Nsells].user_name, t.user_name);
        strcpy(SELLS[Nsells].stock_name, t.stock_name);
        SELLS[Nsells].num_shares = t.num_shares;
        SELLS[Nsells].traded_price = traded_price; 
        Nsells++;
	printf("SELL EXECUTED. Traded price: %f \n",traded_price);
      }else{
	//error transaction not processed. Stockprice higher than user selling price.
	printf("NOT EXECUTED. user selling price %f above stock price \n", t.user_price);
      }
    }else{
      //Error transaction not processed. stock not in stock list. 
      printf("NOT EXECUTED. Stock %s not in stock list \n", t.stock_name);
    }

  }else{
    printf("error: %s is not in the stock file \n", t.stock_name);
  }
*/
  //-------------------------------------------------------------------------------------
 }



 //---------------------------------------------------------------------------------------
    fclose(ftrades);

printf("\n");
printf("Trade Type: BUY \n");
printf("------------------------------------------ \n");
printf("Stock: %s\n", BUYS[0].stock_name);
printf("Stock: %s\n", BUYS[1].stock_name);

printf("\n");
printf("Trade Type: SELL\n");
printf("------------------------------------------\n");
printf("Stock: %s\n", SELLS[0].stock_name);


    return 0;

}

