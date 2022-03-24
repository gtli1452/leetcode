/* Refer to https://ppt.cc/fnvSAx */

#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *mergeTwoLists(struct ListNode *L1, struct ListNode *L2)
{
    struct ListNode *head;
    struct ListNode **ptr = &head, **node;

    for (node = NULL; L1 && L2; *node = (*node)->next) {
        node = (L1->val < L2->val) ? &L1 : &L2;
        *ptr = *node;
        ptr = &(*ptr)->next;
    }
    *ptr = (struct ListNode *) ((uintptr_t) L1 | (uintptr_t) L2);
    return head;
}


/*
 * Brute Force (naive)
 * Time complexity : O(N)
 * Space complexity: O(1)
 */
struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{
    if (listsSize == 0)
        return NULL;
    for (int i = 1; i < listsSize; i++)
        lists[0] = mergeTwoLists(lists[0], lists[i]);
    return lists[0];
}

/*
 * Merge the head and the tail
 * Time complexity : O(NlogN)
 * Space complexity: O(1)
 */
struct ListNode *mergeKLists_v2(struct ListNode **lists, int listsSize)
{
    if (listsSize == 0)
        return NULL;

    while (listsSize > 1) {
        for (int i = 0, j = listsSize - 1; i < j; i++, j--)
            lists[i] = mergeTwoLists(lists[i], lists[j]);
        listsSize = (listsSize + 1) / 2;
    }

    return lists[0];
}

/*
 * Merge segments
 * Time complexity : O(NlogN)
 * Space complexity: O(1)
 *
 * To avoid repeating merging in inner loop, update index i = i + interval*2.
 * After merging in the inner loop, the results will be put in lists[0],
 * lists[interval*2], lists[interval*4], lists[interval*6], etc.
 *
 * Double the interval in the outer loop for accessing the correct
 * position of lists in the inner loop.
 */
struct ListNode *mergeKLists_v3(struct ListNode **lists, int listsSize)
{
    if (listsSize == 0)
        return NULL;

    for (int interval = 1; interval < listsSize; interval *= 2)
        for (int i = 0; i + interval < listsSize; i += interval * 2)
            lists[i] = mergeTwoLists(lists[i], lists[i + interval]);

    return lists[0];
}

/*
 * Divide and Conquer
 * Time complexity : O(NlogN)
 * Space complexity: O(1)
 *
 * Reference
 * https://hackmd.io/@lambert-wu/modified-merge-sort
 * https://reurl.cc/Npe695
 * https://www.cnblogs.com/tuyang1129/p/12857821.html
 */
struct ListNode *mergeKLists_v4(struct ListNode **lists, int listsSize)
{
    if (!listsSize)
        return NULL;
    if (listsSize <= 1)
        return *lists;

    int m = listsSize >> 1;
    struct ListNode *left = mergeKLists(lists, m);
    struct ListNode *right = mergeKLists(lists + m, listsSize - m);

    return mergeTwoLists(left, right);
}