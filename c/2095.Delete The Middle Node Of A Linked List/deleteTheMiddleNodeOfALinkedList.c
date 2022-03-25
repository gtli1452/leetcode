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
