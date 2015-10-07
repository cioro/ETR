#include "etr_report.h"
#include "etrstock.h"
#include <stdbool.h>
#include <string.h>

//Internal function declarations
//-------------------------------------------------------
bool alphcmp (struct executed_trade L, struct executed_trade R);
void merge(struct executed_trade arr[], int l, int m, int r);
void mergeSort(struct executed_trade arr[], int l, int r);
//-------------------------------------------------------


void printReport(FILE * freport, struct executed_trade BUYS[], struct executed_trade SELLS[],int NBuys,int NSells)
{
  mergeSort(BUYS,0, NBuys-1);
   
  fprintf(freport,"\n");
  fprintf(freport,"Trade Type: BUY \n");
  fprintf(freport,"------------------------------------------ \n");
  for(int i = 0; i < NBuys; ++i){
   
   
    if(i!=0 && strcmp(BUYS[i-1].stock_name,BUYS[i].stock_name)){
      fprintf(freport,"\n");
      fprintf(freport,"Stock: %s \n", BUYS[i].stock_name);
      char name[]="User";
      char price[]="Price";
      char shares[]="Shares";
      fprintf(freport,"%-8s \t %-8s \t %-8s \n",name,price,shares);
    }else if(i == 0){
      fprintf(freport,"Stock: %s \n", BUYS[i].stock_name);
      char name[]="User";
      char price[]="Price";
      char shares[]="Shares";
      fprintf(freport,"%-8s \t %-8s \t %-8s \n",name,price,shares);
    }
    fprintf(freport,"%-8s \t %-.2f \t %-2i\n",BUYS[i].user_name,BUYS[i].traded_price,BUYS[i].num_shares);
  }
 
  mergeSort(SELLS,0, NSells-1);
  fprintf(freport,"\n");
  fprintf(freport,"Trade Type: SELL \n");
  fprintf(freport,"------------------------------------------ \n");
  for(int i = 0; i < NSells; ++i){
   
   
    if(i!=0 && strcmp(SELLS[i-1].stock_name,SELLS[i].stock_name)){
      fprintf(freport,"\n");
      fprintf(freport,"Stock: %s \n", SELLS[i].stock_name);
      char name[]="User";
      char price[]="Price";
      char shares[]="Shares";
      fprintf(freport,"%-8s \t %-8s \t %-8s \n",name,price,shares);
    }else if(i == 0){
      fprintf(freport,"Stock: %s \n", SELLS[i].stock_name);
      char name[]="User";
      char price[]="Price";
      char shares[]="Shares";
      fprintf(freport,"%-8s \t %-8s \t %-8s \n",name,price,shares);
    }
    fprintf(freport,"%-8s \t %-.2f \t %-2i\n",SELLS[i].user_name,SELLS[i].traded_price,SELLS[i].num_shares);
  }
}

bool alphcmp (struct executed_trade L, struct executed_trade R)
{
  if(L.stock_name[0] <= R.stock_name[0]){
    int i=0;
    while(L.stock_name[i] == R.stock_name[i] && L.stock_name[i] != '\0' && R.stock_name[i] !='\0'){
      i++;
    }
    if(L.stock_name[i]== '\0' && R.stock_name[i]=='\0'){
      int j=0;
      while(L.user_name[j] == R.user_name[j] && L.user_name[j] != '\0' && R.user_name[j] !='\0'){
	j++;
      }
      if(L.user_name[j] <= R.user_name[j]){
	return true;
      }else{
	return false;
      }
    }else if(L.stock_name[i] < R.stock_name[i]){
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
      if (alphcmp(L[i],R[j]))
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
