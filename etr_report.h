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

void printReport(FILE * freport, 
		 struct executed_trade * buyTrades,
		 size_t buySize,
		 struct executed_trade * sellTrades,
		 size_t sellSize);
#endif
