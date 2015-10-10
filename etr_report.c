#include "etr_report.h"
#include "etrstock.h"
#include <stdbool.h>
#include <string.h>

//Internal function declarations
//-------------------------------------------------------
bool alphcmp (const struct executed_trade* L, const struct executed_trade* R);
void merge(struct executed_trade arr[], int l, int m, int r);
void mergeSort(struct executed_trade arr[], int l, int r);
//-------------------------------------------------------


void printReport(FILE * freport,
		 struct executed_trade * buyTrades,
		 size_t buySize,
		 struct executed_trade * sellTrades,
		 size_t sellSize)
{
  mergeSort(buyTrades,0, buySize-1);
   
  fprintf(freport,"\n");
  fprintf(freport,"Trade Type: BUY \n");
  fprintf(freport,"------------------------------------------ \n");
  for(size_t i = 0; i < buySize; ++i){
   
   
    if(i !=0 && strcmp(buyTrades[i-1].stock_name, buyTrades[i].stock_name)){
      fprintf(freport,"\n");
      fprintf(freport,"Stock: %s \n", buyTrades[i].stock_name);
      char name[]="User";
      char price[]="Price";
      char shares[]="Shares";
      fprintf(freport,"%-8s \t %-8s \t %-8s \n",name,price,shares);
    }else if(i == 0){
      fprintf(freport,"Stock: %s \n", buyTrades[i].stock_name);
      char name[]="User";
      char price[]="Price";
      char shares[]="Shares";
      fprintf(freport,"%-8s \t %-8s \t %-8s \n",name,price,shares);
    }
    fprintf(freport,"%-8s \t %-.2f \t %-2i\n",buyTrades[i].user_name,buyTrades[i].traded_price,buyTrades[i].num_shares);
  }
 
  mergeSort(sellTrades,0, sellSize-1);
  fprintf(freport,"\n");
  fprintf(freport,"Trade Type: SELL \n");
  fprintf(freport,"------------------------------------------ \n");
  for(size_t i = 0; i < sellSize; ++i){
   
   
    if(i!=0 && strcmp(sellTrades[i-1].stock_name,sellTrades[i].stock_name)){
      fprintf(freport,"\n");
      fprintf(freport,"Stock: %s \n", sellTrades[i].stock_name);
      char name[]="User";
      char price[]="Price";
      char shares[]="Shares";
      fprintf(freport,"%-8s \t %-8s \t %-8s \n",name,price,shares);
    }else if(i == 0){
      fprintf(freport,"Stock: %s \n", sellTrades[i].stock_name);
      char name[]="User";
      char price[]="Price";
      char shares[]="Shares";
      fprintf(freport,"%-8s \t %-8s \t %-8s \n",name,price,shares);
    }
    fprintf(freport,"%-8s \t %-.2f \t %-2i\n",sellTrades[i].user_name,sellTrades[i].traded_price,sellTrades[i].num_shares);
  }
}

bool alphcmp (const struct executed_trade* left_elem, const struct executed_trade* right_elem)
{
  if(left_elem->stock_name[0] <= right_elem->stock_name[0]){
    int i=0;
    while(left_elem->stock_name[i] == right_elem->stock_name[i] && left_elem->stock_name[i] != '\0' && right_elem->stock_name[i] !='\0'){
      i++;
    }
    if(left_elem->stock_name[i]== '\0' && right_elem->stock_name[i]=='\0'){
      int j=0;
      while(left_elem->user_name[j] == right_elem->user_name[j] && left_elem->user_name[j] != '\0' && right_elem->user_name[j] !='\0'){
	j++;
      }
      if(left_elem->user_name[j] <= right_elem->user_name[j]){
	return true;
      }else{
	return false;
      }
    }else if(left_elem->stock_name[i] < right_elem->stock_name[i]){
      return true;
    }else{
      return false;
    }
 }else{
    return false;
  }

}
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(struct executed_trade arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    struct executed_trade L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
      if (alphcmp(&L[i],&R[j]))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the sub-array
  of arr to be sorted */
void mergeSort(struct executed_trade arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2; //Same as (l+r)/2, but avoids overflow for large l and h
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
