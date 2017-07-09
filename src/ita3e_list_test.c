#include <stdio.h>
#include <stdlib.h>
#include "ita3e.h"
#include "ita3e_list.h"
#include "ita3e_errors.h"

int ita3e_list_test() {
	ita3e_item_list_t *list;
	ita3e_item_list_init(&list);
	int num_elem = 4;
	ita3e_item_t x = ita3e_item_init(0,0);
	/*while(i++ < num_elem) {
		ita3e_item_t tmp = ita3e_item_init(rand()/112034,rand()/882034);
		ret = ita3e_item_list_cons(&list,tmp);
		if(ret != E_ITA3E_OK) {
            printf(" Unable to push(err-%d)\n",ret);
            exit(ret);
        }
		printf(" Item to be pushed(%d) : ",i);
        ita3e_item_print(tmp);
		printf("\n");
	}*/
	ita3e_item_list_cons(&list,num_elem);
	ita3e_item_list_traverse(list,true);
	printf("-----Inserting elements------\n");
	ita3e_item_list_insert(&list,67,3);
	ita3e_item_list_traverse(list,true);
	ita3e_item_list_insert(&list,87,1);
	ita3e_item_list_traverse(list,true);
	ita3e_item_list_insert(&list,97,0);
	ita3e_item_list_traverse(list,true);
	printf("-----deleting elements------\n");
	ita3e_item_list_delete(&list,1);
	ita3e_item_list_traverse(list,true);
	ita3e_item_list_delete(&list,4);
	ita3e_item_list_traverse(list,true);
	printf("-----Searching elements------\n");
	ita3e_item_list_search(list,82,&x);
	ita3e_item_print(x);
	printf("\n");
	ita3e_item_list_search(list,87,&x);
	ita3e_item_print(x);
	printf("\n");
	ita3e_item_list_search(list,67,&x);
	ita3e_item_print(x);
	printf("\n");
	ita3e_item_list_clean_all(&list);
	return E_ITA3E_OK;
}
