#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "maybe_int.h"
#include "io.h"

/*
 Список нужных определений:

 struct list* node_create( int64_t value );
 void list_destroy( struct list* list );
 void list_add_front( struct list** old, int64_t value );
 struct list* list_last( struct list * list );
 void list_add_back( struct list** old, int64_t value );
 size_t list_length( struct list const* list );
 struct list* list_node_at( struct list* list, size_t idx );
 struct maybe_int64 list_at(struct list* list, size_t idx);
 struct list* list_reverse( const struct list* list );
 void list_print(const struct list* l);

*/
struct list* node_create( int64_t value){
	struct list* new_node = malloc(sizeof(struct list));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}

void list_destroy(struct list* list){
	if (!list) return;
	list_destroy(list->next);
	free(list);
}

void list_add_front( struct list** old, int64_t value){
	struct list* new_node = node_create(value);
	if (!(*old)) { *old = new_node; }
	else {
		new_node->next = *old;
		*old = new_node;
	}
}

struct list* list_last( struct list* list ){
	if (!list) return NULL;
	while (list->next){
		list = list->next;
	}
	return list;
}

void list_add_back(struct list** old, int64_t value){
	struct list* new_node = node_create(value);
	struct list* last_node = list_last(*old);
	if (!(*old)) *old = new_node;
	else last_node->next = new_node;
}


size_t list_length( const struct list* list ){
	size_t length = 0;
	while (list){
		length++;
		list = list->next;
	}
	return length;
}	

struct maybe_int64 list_at( struct list* list, size_t idx ) {
	size_t curIdx = 0;
	while (list){
	        if (idx == curIdx) break;
	        curIdx++;
	        list = list->next;
	}
	if (!list) return none_int64;
	return some_int64(list->value);
}

struct list* node_at( struct list* list, size_t idx) {
	size_t curIdx = 0;
	while (list){
		if (idx == curIdx) { break; }
		curIdx++;
		list = list->next;
	}
	if (!list) return NULL;
	return list;
}

void list_print( const struct list* list ){
	while (list) {
		printf("%" PRId64 " ", list->value);
		list = list->next;
	}
	printf("\n");
}
