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

/*
 * Use the hash table to store the value and numbers of the value.
 * Suppose lengths of two arrays are N (nums1) and M (nums2).
 * Time complexity : O(N + M)
 * Space complexity: O(N)
 */
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

/*
 * Use an additional array.
 * Suppose lengths of two arrays are N (nums1) and M (nums2).
 * Time complexity : O(1001)
 * Space complexity: O(N)
 */
int *intersect_v2(int *nums1,
                  int nums1Size,
                  int *nums2,
                  int nums2Size,
                  int *returnSize)
{
    *returnSize = 0;
    int size = nums1Size < nums2Size ? nums1Size : nums2Size;
    int *ans = (int *) calloc(size, sizeof(int));

    /*
     * There are some constraints to the arrays:
     * 1 <= nums1.length, nums2.length <= 1000
     * 0 <= nums1[i], nums2[i] <= 1000
     *
     * We can use the value as an index to record the numbers of the same value.
     */
    int tmp[1001] = {0};
    for (int i = 0; i < nums1Size; i++) {
        tmp[nums1[i]]++;
    }

    for (int i = 0; i < nums2Size; i++) {
        if (tmp[nums2[i]]) {
            tmp[nums2[i]]--;
            ans[(*returnSize)++] = nums2[i];
        }
    }

    return ans;
}

static int cmp(const void *lhs, const void *rhs)
{
    if (*(int *) lhs == *(int *) rhs)
        return 0;

    return *(int *) lhs < *(int *) rhs ? -1 : 1;
}

/*
 * Sorting the arrays then using the Two-Pointers.
 * Suppose lengths of two arrays are N (nums1) and M (nums2).
 * Time complexity : O(N logN) + O(M logM); worst is O(N^2) + O(M^2)
 * Space complexity: O(min(N, M))
 */
int *intersect_v3(int *nums1,
                  int nums1Size,
                  int *nums2,
                  int nums2Size,
                  int *returnSize)
{
    *returnSize = 0;
    int size = nums1Size < nums2Size ? nums1Size : nums2Size;
    int *ans = (int *) calloc(size, sizeof(int));

    qsort(nums1, nums1Size, sizeof(nums1[0]), cmp);
    qsort(nums2, nums2Size, sizeof(nums2[0]), cmp);

    int i = 0, j = 0;

    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] == nums2[j]) {
            ans[(*returnSize)++] = nums1[i];
            i++;
            j++;
        } else if (nums1[i] < nums2[j]) {
            i++;
        } else {
            j++;
        }
    }

    return ans;
}

int main()
{
    int nums1[] = {1, 2, 2, 1};
    int nums2[] = {2, 2};
    int *returnSize;

    int *ans = intersect_v3(nums1, sizeof(nums1) / sizeof(nums1[0]), nums2,
                            sizeof(nums2) / sizeof(nums2[0]), returnSize);

    for (int i = 0; i < *returnSize; i++)
        printf("%d, ", ans[i]);

    return 0;
}
