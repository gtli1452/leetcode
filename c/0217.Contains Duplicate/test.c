#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

struct node {
    int val;
    struct node *next;
};

typedef struct node node_t;
typedef struct node **tb_t;

tb_t *create_tb(int n)
{
    return (tb_t *) calloc(n, sizeof(node_t *));
}

int hash(int key, int n)
{
    int idx = key % n;
    return idx < 0 ? idx + n : idx;
}

bool search_node(tb_t *t, int key, int n)
{
    int idx = hash(key, n);
    node_t *p = t[idx];

    while (p != NULL) {
        if (p->val == key)
            return true;
        p = p->next;
    }
    return false;
}

void add_node(tb_t *t, int key, int n)
{
    if (search_node(t, key, n))
        return;

    int idx = hash(key, n);

    /* create a new node */
    node_t *q = (node_t *) malloc(sizeof(node_t));
    q->val = key;
    q->next = NULL;

    node_t *p = t[idx];
    if (p == NULL) {
        t[idx] = q;
    } else {
        while (p->next != NULL)  // add the node in the tail
            p = p->next;
        p->next = q;
    }
}

void del_node(tb_t *t, int key, int n)
{
    if (!search_node(t, key, n))
        return;

    int idx = hash(key, n);
    node_t *p = t[idx];

    while (p->val != key)
        p = p->next;

    node_t *q = p;
    p = p->next;
    free(q);
}

bool containsDuplicate(int *nums, int numsSize)
{
    if (numsSize < 2)
        return false;

    tb_t *tb = create_tb(numsSize);

    for (int i = 0; i < numsSize; i++) {
        if (search_node(tb, nums[i], numsSize))
            return true;
        else
            add_node(tb, nums[i], numsSize);
    }

    return false;
}