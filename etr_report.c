#include "etr_report.h"
#include "etrstock.h"
#include <stdbool.h>
#include <string.h>

//Internal function declarations
//-------------------------------------------------------
bool alphcmp (struct executed_trade L, struct executed_trade R);
void merge(struct executed_trade arr[], int l, int m, int r);
//-------------------------------------------------------

bool alphcmp (struct executed_trade L, struct executed_trade R)
{
  if(L.stock_name[0] <= R.stock_name[0]){
    int i=0;
    while(L.stock_name[i] == R.stock_name[i]){
      i++;
    }
    if(L.stock_name[i] < R.stock_name[i]){
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
