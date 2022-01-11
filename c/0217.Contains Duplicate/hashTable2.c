/*
 * Author: nuclear-30
 * https://leetcode-cn.com/problems/contains-duplicate/solution/cyu-yan-ha-xi-biao-shi-xian-by-nuclear-30/
 */

#include "stdbool.h"
#include "stdlib.h"

struct node {
    int data;
    struct node *next;
};

typedef struct {
    int size;
    struct node **tb;
} map_t;

typedef struct node node_t;

int next_prime(int n)
{
    if (n % 2 == 0)
        n++;
    for (;; n += 2) {
        for (int i = 3; i <= sqrt(n); i++)
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

map_t *init_hash_tb(int size)
{
    map_t *m = malloc(sizeof(map_t));
    m->size = next_prime(size);
    m->tb = (node_t **) malloc(sizeof(node_t *) * m->size);
    for (int i = 0; i < m->size; i++) {
        m->tb[i] = malloc(sizeof(node_t));
        m->tb[i]->next = NULL;
    }
    return m;
}

node_t *find_node(map_t *m, int key)
{
    node_t *p = m->tb[hash(key, m->size)]->next;

    while (p != NULL && p->data != key)
        p = p->next;
    return p;
}

void add_node(map_t *m, int key)
{
    node_t *pos, *l;

    pos = find_node(m, key);

    if (pos == NULL) {
        node_t *new_node = (node_t *) malloc(sizeof(node_t));
        l = m->tb[hash(key, m->size)];
        new_node->next = l->next;
        l->next = new_node;
        new_node->data = key;
    }
}

void free_hash_tb(map_t *m, int size)
{
    node_t *tmp = NULL, *del_node = NULL;

    for (int i = 0; i < size; i++) {
        tmp = m->tb[i];
        while (tmp) {
            del_node = tmp;
            tmp = tmp->next;
            free(del_node);
        }
    }
    free(m);
}

bool containsDuplicate(int *nums, int numsSize)
{
    if (numsSize < 2)
        return false;

    map_t *m = init_hash_tb(numsSize + 1);

    for (int i = 0; i < numsSize; i++) {
        node_t *node = find_node(m, nums[i]);
        if (node != NULL)
            return true;
        else
            add_node(m, nums[i]);
    }
    return false;
}