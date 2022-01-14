/*
 * Author: ling-hu-yi
 * https://leetcode-cn.com/problems/contains-duplicate/solution/cyu-yan-shou-cuo-jian-dan-hashbiao-by-ling-hu-yi/
 */

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#define HashSize 20000

struct hash_node {
    int val;
    struct hash_node *next;
};

typedef struct hash_node node_t;

node_t **init_hash_tb(int n)
{
    node_t **a = (node_t **) malloc(sizeof(node_t *) * n);
    for (int i = 0; i < n; i++)
        a[i] = NULL;
    /*
     * We also can use `calloc` to create, this func will initialize the memory.
     * node_t **a = (node_t *) calloc(n, sizeof(node_t));
     */

    return a;
}

int hash(int x, int n)
{
    int idx = x % n;
    return x < 0 ? idx + n : idx;
}

bool search_node(node_t **table, int x, int n)
{
    int index = hash(x, n);
    node_t *p = table[index];

    while (p != NULL) {
        if (p->val == x)
            return true;
        p = p->next;
    }
    return false;
}

void add_node(node_t **table, int x, int n)
{
    if (search_node(table, x, n) == true)
        return;

    node_t *q = (node_t *) malloc(sizeof(node_t));
    q->val = x;
    q->next = NULL;

    int index = hash(x, n);
    node_t *p = table[index];

    if (p == NULL) {
        table[index] = q;
        return;
    }

    while (p->next != NULL)
        p = p->next;
    p->next = q;
}

void del_node(node_t **table, int x, int n)
{
    if (search_node(table, x, n) == false)
        return;

    int index = hash(x, n);
    node_t *p = table[index];

    while (p->val != x)
        p = p->next;

    node_t *q = p;
    p = p->next;
    free(q);
}

bool containsDuplicate(int *nums, int numsSize)
{
    if (numsSize < 2)
        return false;

    node_t **table = init_hash_tb(HashSize);

    for (int i = 0; i < numsSize; i++) {
        if (search_node(table, nums[i], HashSize) == true)
            return true;
        else
            add_node(table, nums[i], HashSize);
    }

    return false;
}