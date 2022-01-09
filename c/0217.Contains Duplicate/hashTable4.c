/*
 * Author: 52coder
 * https://www.52coder.net/post/LeetCode217
 */

#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

struct Node {
    int val;
    struct Node *next;
};

struct Set {
    int bucketSize;
    struct Node **table;
};

void initSet(struct Set *set, int bucketSize)
{
    set->bucketSize = bucketSize;
    set->table = (struct Node **) malloc(sizeof(struct Node *) * bucketSize);
    memset(set->table, 0, sizeof(struct Node *) * bucketSize);
}

bool addValue(struct Set *s, int val)
{
    int idx = 0;
    /*-INT_MIN overflow in expression -val*/
    if (INT_MIN == val)
        idx = 0;
    else
        idx = val > 0 ? val : -val;
    /*find which list to add*/
    idx %= s->bucketSize;
    struct Node *ptr = s->table[idx];
    while (ptr != NULL) {
        if (ptr->val == val) {
            return false;
        }

        ptr = ptr->next;
    }
    /*add new value,malloc memory,assign val*/
    ptr = malloc(sizeof(struct Node));
    ptr->val = val;
    /*update the new added value ,as the first in list*/
    ptr->next = s->table[idx];
    s->table[idx] = ptr;
    return true;
}

void releaseSet(struct Set *s)
{
    struct Node *ptr, *tmp;
    for (int i = 0; i < s->bucketSize; ++i) {
        ptr = s->table[i];
        while (ptr != NULL) {
            tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }
    free(s->table);
    s->table = NULL;
    s->bucketSize = 0;
}

bool containsDuplicate(int *nums, int numsSize)
{
    if (numsSize < 2) {
        return false;
    }

    struct Set set;

    /*
     * here numsSize/2 && numsSize both ok,if divide > 2,
     * when array has less than divide,bucketSize is zero
     * idx %= s->bucketSize wrong : division by zero
     */
    initSet(&set, numsSize / 2);

    for (int i = 0; i < numsSize; ++i) {
        if (!addValue(&set, nums[i])) {
            /*free memory*/
            releaseSet(&set);
            return true;
        }
    }
    releaseSet(&set);
    return false;
}