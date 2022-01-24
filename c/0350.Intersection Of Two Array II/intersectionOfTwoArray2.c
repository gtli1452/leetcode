#include "stdio.h"
#include "stdlib.h"

struct node {
    int key;
    int cnt;
    struct node *next;
};

typedef struct node node_t;

int hash(int key, int n)
{
    int idx = key % n;
    return idx < 0 ? idx + n : idx;
}

node_t *creat_node(int key)
{
    node_t *q = (node_t *) malloc(sizeof(node_t));
    q->key = key;
    q->cnt = 1;
    q->next = NULL;
    return q;
}

int *intersect(int *nums1,
               int nums1Size,
               int *nums2,
               int nums2Size,
               int *returnSize)
{
    *returnSize = 0;
    int *ans;
    if (nums1Size < nums2Size)
        ans = (int *) calloc(nums1Size, sizeof(int));
    else
        ans = (int *) calloc(nums2Size, sizeof(int));

    node_t **tb = (node_t **) calloc(nums1Size, sizeof(node_t *));

    for (int i = 0; i < nums1Size; i++) {
        int idx = hash(nums1[i], nums1Size);
        node_t *p = tb[idx];
        if (p == NULL)
            tb[idx] = creat_node(nums1[i]);
        else {
            while (p != NULL) {
                if (p->key == nums1[i]) {
                    p->cnt++;
                    break;
                } else if (p->next == NULL) {
                    p->next = creat_node(nums1[i]);
                    break;
                }
                p = p->next;
            }
        }
    }

    for (int i = 0; i < nums2Size; i++) {
        node_t *p = tb[hash(nums2[i], nums1Size)];
        if (p != NULL) {
            while (p != NULL) {
                if (p->key == nums2[i] && p->cnt > 0) {
                    ans[(*returnSize)++] = nums2[i];
                    p->cnt--;
                }
                p = p->next;
            }
        }
    }

    return ans;
}

int main()
{
    int nums1[] = {1, 2, 2, 1};
    int nums2[] = {2, 2};
    int *returnSize;

    int *ans = intersect(nums1, sizeof(nums1) / sizeof(nums1[0]), nums2,
                         sizeof(nums2) / sizeof(nums2[0]), returnSize);

    for (int i = 0; i < *returnSize; i++)
        printf("%d, ", ans[i]);

    return 0;
}
