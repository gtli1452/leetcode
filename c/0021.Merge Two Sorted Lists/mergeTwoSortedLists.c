/* Refer to https://ppt.cc/fnvSAx */

#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} node_t;

/*
 * Ues a tmp node
 * Time complexity : O(n)
 * Space complexity: O(1)
 */
struct ListNode *mergeTwoLists(struct ListNode *L1, struct ListNode *L2)
{
    node_t *head = (node_t *) malloc(sizeof(node_t));
    node_t *ptr = head;

    while (L1 && L2) {
        if (L1->val < L2->val) {
            ptr->next = L1;
            L1 = L1->next;
        } else {
            ptr->next = L2;
            L2 = L2->next;
        }
        ptr = ptr->next;
    }

    ptr->next = L1 ? L1 : L2;

    return head->next;
}

/*
 * Ues a indirect pointer
 * Time complexity : O(n)
 * Space complexity: O(1)
 */
struct ListNode *mergeTwoLists_v2(struct ListNode *L1, struct ListNode *L2)
{
    struct ListNode *head;
    struct ListNode **ptr = &head;

    for (; L1 && L2; ptr = &(*ptr)->next) {
        if (L1->val < L2->val) {
            *ptr = L1;
            L1 = L1->next;
        } else {
            *ptr = L2;
            L2 = L2->next;
        }
    }

    *ptr = (struct ListNode *) ((uintptr_t) L1 | (uintptr_t) L2);

    return head;
}

/*
 * Simplify the solution_v2
 * Time complexity : O(n)
 * Space complexity: O(1)
 */
struct ListNode *mergeTwoLists_v3(struct ListNode *L1, struct ListNode *L2)
{
    struct ListNode *head = NULL;
    struct ListNode **ptr = &head, **node;

    for (node = NULL; L1 && L2; *node = (*node)->next) {
        node = (L1->val < L2->val) ? &L1 : &L2;
        *ptr = *node;
        ptr = &(*ptr)->next;
    }
    *ptr = (struct ListNode *) ((uintptr_t) L1 | (uintptr_t) L2);
    return head;
}