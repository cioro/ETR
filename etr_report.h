#ifndef ETR_REPORT_H
#define ETR_REPORT_H

#define MAX_BUYS_RECORDED 100
#define MAX_SELLS_RECORDED 100

#include "etrstock.h"
#include "etrtrade.h"

#define MAX_TRADE_REQUEST_LENGTH 100
struct executed_trade{
  char user_name[MAX_USER_NAME_LENGTH];
  char stock_name[MAX_STOCK_NAME_LENGTH];
  int num_shares;
  double traded_price;
};

#endif
