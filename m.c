//This file test the behaviour of all the functions and structs involved in 
// an electric trading reporting program (ETR). 
//ETR allows users to trade stocks from their own computers without human 
//intervention.
#include<stdio.h>
#include <stdlib.h>
#include "etrstock.h"

#define MAX_USER_NAME_LENGTH 20
#define MAX_TRADE_REQUEST_LENGTH 100

struct trade_request{
  char user_name[MAX_USER_NAME_LENGTH];
  char request;
  char stock_name[MAX_STOCK_NAME_LENGTH];
  int num_shares;
  double user_price;
};


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

  //-------------------------------------------------------------
  //Load data into trade_request struct 

 char str[MAX_TRADE_REQUEST_LENGTH];//Maybe use another define?
 while(  fscanf(ftrades,"%s", str) != EOF){
 
 
  struct trade_request t;

  
  //Load USER_NAME
  int i;
  for (i = 0; str[i] != '|'; i++){
    t.user_name[i]=str[i];
  }
  t.user_name[i]='\0';
  
  i++;// '|'
  //Load REQUEST_TYPE 
  t.request = str[i];
  i++;// request char
  
  //Load STOCK_NAME
  i++;//'|'
  int j;
  for (j = 0; str[i] != '|';j++, i++){
    t.stock_name[j]=str[i];
  }
  t.stock_name[j]='\0';
  
  //Load NUM_SHARES
  char tmp[20];
  i++;
  for (j = 0 ; str[i] != '|' ;j++, i++){
    tmp[j]=str[i];
   }
  tmp[j] = '\0';
  t.num_shares = atoi(tmp);
  
  //Load USER_PRICE
  char tmp2[20];
  i++;
  for (j = 0 ; str[i] != 0 ;j++, i++){
    tmp2[j]=str[i];
   }
  tmp2[j] = '\0';
  
  t.user_price = atof(tmp2);
  //--------------------------------------------------

  double stock_price;
  stock_price = look_up_stock_price(t.stock_name,head_stock_list);

  double traded_price;
  if(stock_price > 0 ){
    if(t.request == 'B'){
      if(t.user_price >= stock_price){
	traded_price = (t.user_price+stock_price)/2;
	//record transaction
	printf("BUY EXECUTED. Traded price: %f \n",traded_price);
      }else{
	//error transaction not processed. User buying price below stock price
	printf("NOT EXECUTED. user asking price %f below stock price \n", t.user_price);
      }
    }else if(t.request == 'S'){
      if(t.user_price <= stock_price){
	traded_price = (t.user_price+stock_price)/2;
	//record transaction
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
//Print report on executed trades
 }
    fclose(ftrades);
    return 0;
}

