#ifndef ETR_REPORT_H
#define ETR_REPORT_H

#include "etr_definitions.h"
#include "etrstock.h"

struct executed_trade{
  char user_name[MAX_USER_NAME_LENGTH];
  char stock_name[MAX_STOCK_NAME_LENGTH];
  int num_shares;
  double traded_price;
};

void mergeSort(struct executed_trade arr[], int l, int r);

#endif
