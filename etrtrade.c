#include "etrtrade.h"
#include "etrstock.h"
#include "etr_report.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trade_request load_request(char str[])
{ 
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
  
  return t;
}


void process_trade(struct executed_trade BUYS[], struct executed_trade SELLS[], struct trade_request t,double stock_price){

  double traded_price;
  static int Nbuys = 0;
  static int Nsells = 0;
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
}
