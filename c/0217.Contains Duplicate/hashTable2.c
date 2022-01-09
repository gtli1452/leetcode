/*
 * Author: nuclear-30
 * https://leetcode-cn.com/problems/contains-duplicate/solution/cyu-yan-ha-xi-biao-shi-xian-by-nuclear-30/
 */

#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

struct node {
    int data;
    struct node *next;
};

struct hash_tb {
    int size;
    struct node **tb;
};

typedef struct node node_t;
typedef struct hash_tb tb_t;

int next_prime(int n)
{
    if (n % 2 == 0)
        n++;
    int i;
    for (;; n += 2) {
        for (i = 3; i <= sqrt(n); i++)
            if (n % i == 0)
                goto out;
        return n;
    out:;
    }
}

int hash(int key, int table_size)
{
    return abs(key) % table_size;
}

tb_t *init_hash_tb(int size)
{
    tb_t *h;
    h = malloc(sizeof(tb_t));
    h->size = next_prime(size);
    h->tb = (node_t **) malloc(sizeof(node_t *) * h->size);
    for (int i = 0; i < h->size; i++) {
        h->tb[i] = malloc(sizeof(node_t));
        h->tb[i]->next = NULL;
    }
    return h;
}

node_t *find_node(int key, tb_t *h)
{
    node_t *p;
    p = h->tb[hash(key, h->size)]->next;

    while (p != NULL && p->data != key)
        p = p->next;
    return p;
}

void add_node(int key, tb_t *h)
{
    node_t *pos, *l;

    pos = find_node(key, h);

    if (pos == NULL) {
        node_t *new_node = (node_t *) malloc(sizeof(node_t));
        l = h->tb[hash(key, h->size)];
        new_node->next = l->next;
        l->next = new_node;
        new_node->data = key;
    }
}

void free_hash_tb(tb_t *h, int size)
{
    node_t *tmp = NULL, *del_node = NULL;

    for (int i = 0; i < size; i++) {
        tmp = h->tb[i];
        while (tmp) {
            del_node = tmp;
            tmp = tmp->next;
            free(del_node);
        }
    }
    free(h);
}

bool containsDuplicate(int *nums, int numsSize)
{
    if (numsSize < 2)
        return false;

    tb_t *h = init_hash_tb(numsSize + 1);

    for (int i = 0; i < numsSize; i++) {
        node_t *node = find_node(nums[i], h);
        if (node != NULL)
            return true;
        else
            add_node(nums[i], h);
    }
    return false;


    return false;
}