#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"

typedef struct node {
    int key;
    int data;
    struct node *next;
} node_t;

typedef struct node **tb_t;

tb_t *create_tb(int n)
{
    return (tb_t *) calloc(n, sizeof(node_t *));
}

static inline int hash(int key, int n)
{
    int idx = key % n;
    return idx < 0 ? idx + n : idx;
}

bool search_node(tb_t *t, int key, int n)
{
    int idx = hash(key, n);
    node_t *p = t[idx];

    while (p != NULL) {
        if (p->key == key)
            return true;
        p = p->next;
    }
    return false;
}

void add_node(tb_t *t, int key, int data, int n)
{
    if (search_node(t, key, n))
        return;

    /* create a new node */
    node_t *q = (node_t *) malloc(sizeof(node_t));
    q->key = key;
    q->data = data;
    q->next = NULL;

    int idx = hash(key, n);
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

    while (p->key != key)
        p = p->next;
    node_t *q = p;
    p = p->next;
    free(q);
}

/*
 * Use hash_table
 * Time complexity:  O(N)
 * Space complexity: O(N)
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    *returnSize = 2;
    int *ans = (int *) malloc(sizeof(int) * 2);

    tb_t *t = create_tb(numsSize);

    for (int i = 0; i < numsSize; i++) {
        if (!search_node(t, nums[i], numsSize))
            add_node(t, target - nums[i], i, numsSize);
        else {
            ans[0] = i;
            // node_t *p = t[hash(nums[i], numsSize)];
            // ans[1] = p->data;
            ans[1] = ((node_t *) (t[hash(nums[i], numsSize)]))->data;
            return ans;
        }
    }

    *returnSize = 0;
    return NULL;
}

int main()
{
    int nums[] = {2, 7, 11, 13, 17};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize = 0;
    int *ansPtr = NULL;

    ansPtr = twoSum(nums, numsSize, 9, &returnSize);

    printf("[%d, %d]", *ansPtr, *(ansPtr + 1));
    return 0;
}