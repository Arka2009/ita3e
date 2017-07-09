/*
 * Priority Queue Methods
 */
void ita3e_priority_queue_init			(ita3e_priority_queue_t *pq);
void ita3e_priority_queue_print			(ita3e_priority_queue_t *pq);
int  ita3e_priority_queue_add			(ita3e_priority_queue_t *pq, ita3e_item_t *elem);
int  ita3e_priority_queue_max			(ita3e_priority_queue_t *pq, ita3e_item_t *max);
int  ita3e_priority_queue_del			(ita3e_priority_queue_t *pq, ita3e_item_t *max);
int  ita3e_priority_queue_size			(ita3e_priority_queue_t *pq);


