struct ListNode {
    int val;
    struct ListNode *next;
};

/*
 * Brute force
 * Time complexity : O(n)
 * Space complexity: O(1)
 */
struct ListNode *deleteMiddle(struct ListNode *head)
{
    struct ListNode **ptr = &head;
    int n = 0;

    // find the numbers of the list
    while (*ptr) {
        ptr = &(*ptr)->next;
        n++;
    }

    // find the middle node
    n >>= 1;
    ptr = &head;
    for (int i = 0; i < n; i++)
        ptr = &(*ptr)->next;

    /// delete the middle node
    *ptr = (*ptr)->next;

    return head;
}

/**
 * Two-pointers
 * Time complexity : O(logN)
 * Space complexity: O(1)
 */
struct ListNode *deleteMiddle_v2(struct ListNode *head)
{
    struct ListNode **indir = &head;

    for (struct ListNode *fast = head; fast && fast->next;
         fast = fast->next->next)
        indir = &(*indir)->next;
    *indir = (*indir)->next;

    return head;
}

#include <stdio.h>
#include <stdlib.h>
/**
 * Two-pointers
 * Time complexity : O(logN)
 * Space complexity: O(1)
 */
struct ListNode *deleteMiddle_v3(struct ListNode *head)
{
    struct ListNode **indir = &head, *prev;

    for (struct ListNode *fast = head; fast && fast->next;
         fast = fast->next->next) {
        prev = *indir;
        indir = &(*indir)->next;
    }
    prev->next = (*indir)->next;
    // free(*indir);
    return head;
}

void append(struct ListNode **head, int val)
{
    struct ListNode *new = (struct ListNode *) malloc(sizeof(struct ListNode));
    new->val = val, new->next = NULL;

    struct ListNode **indir = head;
    while (*indir)
        indir = &(*indir)->next;
    *indir = new;
}

void dump(struct ListNode *head)
{
    struct ListNode *ptr = head;
    while (ptr) {
        printf("%d", ptr->val);
        ptr = ptr->next;
        if (ptr)
            printf("->");
    }
    printf("\n");
}

void removeNode(struct ListNode *head, struct ListNode *target)
{
    struct ListNode **indir = &head;
    while (*indir != target)
        indir = &(*indir)->next;
    *indir = target->next;
}

int main()
{
    struct ListNode *head = NULL;
    for (int i = 0; i < 7; i++)
        append(&head, i);
    dump(head);

    // deleteMiddle_v3(head);
    removeNode(head, head->next->next);
    dump(head);

    return 0;
}
