//This file test the behaviour of all the functions and structs involved in 
// an electric trading reporting program (ETR). 
//ETR allows users to trade stocks from their own computers without human 
//intervention.
#include<stdio.h>
#include <stdlib.h>

#define MAX_STOCK_NAME_LENGTH 15
#define MAX_USER_NAME_LENGTH 20

struct stock{
  double stock_price;
  char stock_name[MAX_STOCK_NAME_LENGTH];
};

struct Node_stock{
  struct stock data;
  struct Node_stock * next;
};

struct Node_stock* Insert(struct Node_stock* head, struct stock data)
{  
    struct Node_stock* newNode = (struct Node_stock*) malloc(sizeof(struct Node_stock));
    newNode->data = data;
    newNode->next = NULL;
    struct Node_stock* last = head;
    //Empty list
    if(head == NULL){
        head = newNode;
        return head;
    }else{
        while(last->next != NULL){
            last = last->next;
        }
        last->next = newNode;
        return head;        
    }    

}

struct Node_stock * createStockList(FILE * file, struct Node_stock * head ){
  
  char str[80];
 
  do{ 
    
    struct stock s;
    fscanf(file,"%s", str); 

    int i;
    for (i = 0; str[i] != '|'; i++){
      s.stock_name[i]=str[i];
    }
    s.stock_name[i]='\0';

    char temp[20];
    i++;
    int j;
    for (j = 0 ; str[i] != 0 ;j++, i++){
      temp[j]=str[i];
    }
    
    temp[j] = '\0';
    s.stock_price = atof(temp);

    head = Insert(head, s); 
    
   }while(fgetc(file) != EOF);
  
  return head;

} 

char cmp(struct Node_stock *a, struct Node_stock *b) {
    return (a->data.stock_name[0] - b->data.stock_name[0]);
}

struct Node_stock *listSort(struct Node_stock *list) {
    struct Node_stock *p, *q, *e, *tail;
    int insize, nmerges, psize, qsize, i;
    /*
     * Silly special case: if `list' was passed in as NULL, return
     * NULL immediately.
     */
    if (!list){
	return NULL;
    }
    
    insize = 1;

    while (1) {
        p = list;
        list = NULL;
        tail = NULL;

        nmerges = 0;  /* count number of merges we do in this pass */

        while (p) {
            nmerges++;  /* there exists a merge to be done */
            /* step `insize' places along from p */
            q = p;
            psize = 0;
            for (i = 0; i < insize; i++) {
                psize++;
		q = q->next;
                if (!q) break;
            }

            /* if q hasn't fallen off end, we have two lists to merge */
            qsize = insize;

            /* now we have two lists; merge them */
            while (psize > 0 || (qsize > 0 && q)) {

                /* decide whether next element of merge comes from p or q */
                if (psize == 0) {
		    /* p is empty; e must come from q. */
		    e = q; q = q->next; qsize--;
		} else if (qsize == 0 || !q) {
		    /* q is empty; e must come from p. */
		    e = p; p = p->next; psize--;
		} else if (cmp(p,q) <= 0) {
		    /* First element of p is lower (or same);
		     * e must come from p. */
		    e = p; p = p->next; psize--;
		} else {
		    /* First element of q is lower; e must come from q. */
		    e = q; q = q->next; qsize--;
		}

                /* add the next element to the merged list */
		if (tail) {
		    tail->next = e;
		} else {
		    list = e;
		}
		tail = e;
            }

            /* now p has stepped `insize' places along, and q has too */
            p = q;
        }
	 
	tail->next = NULL;

        /* If we have done only one merge, we're finished. */
        if (nmerges <= 1)   /* allow for nmerges==0, the empty list case */
            return list;

        /* Otherwise repeat, merging lists twice the size */
        insize *= 2;
    }
}




struct trade_request{
  char user_name[MAX_USER_NAME_LENGTH];
  char request;
  char stock_name[MAX_STOCK_NAME_LENGTH];
  int num_shares;
  int user_price;
};


int main(void){

//Read stock file and load the data
  FILE * fstocks;
  fstocks = fopen("stocks.tex","r");
  struct Node_stock * head_stock_list = NULL;

  head_stock_list = createStockList(fstocks,head_stock_list);
  head_stock_list = listSort(head_stock_list);
  
  while(head_stock_list != NULL){
   printf("%s \t %f \n",head_stock_list->data.stock_name, head_stock_list->data.stock_price);
   head_stock_list = head_stock_list->next;
  }

//Sort list alphabetically. 


  fclose(fstocks);

 
//Read each trade and process the trade
//Print report on executed trades

  return 0;
}

