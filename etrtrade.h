#ifndef ETR_TRADE_H
#define ETR_TRADE_H

#define MAX_USER_NAME_LENGTH 20

#include "etrstock.h"
#include "etr_report.h"

struct trade_request{
  char user_name[MAX_USER_NAME_LENGTH];
  char request;
  char stock_name[MAX_STOCK_NAME_LENGTH];
  int num_shares;
  double user_price;
};

struct trade_request load_request(char str[]);
void process_trade(struct executed_trade BUYS[MAX_BUYS_RECORDED], struct executed_trade SELLS[MAX_SELLS_RECORDED], struct trade_request t,double stock_price);
#endif
