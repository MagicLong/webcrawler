#ifndef UTILS_H
#define UTILS_H

#define BUFF_MAX 1024


typedef struct NODE{
    void* key;
    void* value;
    struct NODE* next;
}HashList, HashListNode;

HashList* create_list();

bool add_node(HashListNode* pre, void* key,  void* value);

#endif
