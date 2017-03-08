#include <stdio.h>
#include <stdlib.h>
#include "ita3e.h"
#include "ita3e_list.h"
#include "ita3e_errors.h"

int ita3e_list_test() {
	ita3e_item_list_t list;
	ita3e_item_list_init(&list);
	int num_elem = 4, i = 0, ret;
	while(i++ < num_elem) {
		ita3e_item_t tmp = ita3e_item_init(rand()/112034,rand()/882034);
		ret = ita3e_item_list_cons(&list,tmp);
		if(ret != E_ITA3E_OK) {
            printf(" Unable to push(err-%d)\n",ret);
            exit(ret);
        }
		printf(" Item to be pushed(%d) : ",i);
        ita3e_item_print(tmp);
		printf("\n");
	}
	ita3e_item_list_traverse(list,true);
	return E_ITA3E_OK;
}
