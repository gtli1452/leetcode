/*
 * Author: ling-xie-9
 * https://leetcode-cn.com/problems/contains-duplicate/solution/ha-xi-biao-by-ling-xie-9-lman/
 */

#include "stdbool.h"
#include "stdlib.h"

//链地址法实现哈希表
typedef struct MyLinkNode {
    struct MyLinkNode *next;
    int value;  //存储的元素值
} MyLinkNode, *MyLinkNodePtr;

//存储hash链key值数组的结点
typedef struct HashNode {
    MyLinkNode *LinkListPtr;
    int key;    //关键字key
    int count;  //记录桶内元素的个数
} MyHashSet, *MyHashSetPtr;

/* 创建哈希表 */
MyHashSet *myHashSetCreate(int hashnum)
{
    int i = 0;
    MyHashSet *HashTable = (MyHashSet *) malloc((hashnum) * sizeof(MyHashSet));
    if (HashTable == NULL) {
        return NULL;
    }
    for (i = 0; i < hashnum; i++) {
        HashTable[i].key = i;
        HashTable[i].count = 0;
        HashTable[i].LinkListPtr = NULL;
    }
    return HashTable;
}

/* 向哈希表中添加元素 */
void myHashSetAdd(MyHashSet *HashTable, int key, int hashnum)
{
    if (HashTable == NULL) {
        return;
    }
    MyHashSet *p_HashTable = HashTable;
    /* 除留取余法构建哈希函数,需要对负数哈希函数特殊处理 */
    int MyKey = key >= 0 ? (key % hashnum) : ((key % hashnum) + hashnum);
    //对应key值元素个数为0，则说明此时桶为空
    if (p_HashTable[MyKey].count == 0) {
        MyLinkNode *node = (MyLinkNode *) malloc(sizeof(MyLinkNode));
        node->next = NULL;
        node->value = key;                      //键就是此时对应的值
        p_HashTable[MyKey].LinkListPtr = node;  //桶为空时保存的链表头地址
        p_HashTable[MyKey].count++;             //记录桶内元素的数量
    } else {  //该key对应的桶不为空，此时解决冲突，链地址法
        MyLinkNode *tmp = p_HashTable[MyKey].LinkListPtr;
        MyLinkNode *prev = tmp;
        while (tmp != NULL) {  //遍历该桶，查看是否已经保存该元素
            prev = tmp;
            if (tmp->value == key) {
                break;  //如果该元素key已经存储，则不作处理
            }
            tmp = tmp->next;
        }

        if (tmp == NULL) {  //如果没有保存当前的key值，则将该值放入桶中
            MyLinkNode *node =
                (MyLinkNode *) malloc(sizeof(MyLinkNode));  //为该结点分配空间
            node->next = NULL;  //将新的值插入链表末尾
            node->value = key;
            prev->next = node;
            p_HashTable[MyKey].count++;  //记录当前桶内的元素数量
        }
    }
}

/* 删除哈希表中指定元素 */
void myHashSetRemove(MyHashSet *HashTable, int key, int hashnum)
{
    if (HashTable == NULL) {
        return;
    }
    MyHashSet *p_HashTable = HashTable;
    /* 除留取余法构建哈希函数，对负数特殊处理 */
    int MyKey = key >= 0 ? (key % hashnum) : ((key % hashnum) + hashnum);

    if (p_HashTable[MyKey].count != 0) {
        MyLinkNode *tmp = p_HashTable[MyKey].LinkListPtr;  //保存第一个结点
        if (tmp->value == key) {  //如果第一个值就是要删除的值，则直接删除
            p_HashTable[MyKey].LinkListPtr = tmp->next;
            free(tmp);
            tmp = NULL;
            p_HashTable[MyKey].count--;
        } else {
            while (tmp->next != NULL) {
                if (tmp->next->value == key) {
                    MyLinkNode *sp = tmp->next;
                    tmp->next = tmp->next->next;
                    free(sp);
                    sp = NULL;
                    p_HashTable[MyKey].count--;
                    break;
                }
                tmp = tmp->next;
            }
        }
    }
}

/* 查找哈希表中指定元素 */
bool myHashSetContains(MyHashSet *HashTable, int key, int hashnum)
{
    if (HashTable == NULL) {
        return false;
    }
    MyHashSet *p_HashTable = HashTable;
    /* 除留取余法构建哈希函数，要对负数特殊处理 */
    int MyKey = key >= 0 ? (key % hashnum) : ((key % hashnum) + hashnum);
    if (p_HashTable[MyKey].count == 0) {
        return false;
    }
    MyLinkNode *tmp = p_HashTable[MyKey].LinkListPtr;
    while (tmp != NULL) {
        if (tmp->value == key) {
            return true;
            ;
        }
        tmp = tmp->next;
    }
    return false;
}

/* 删除哈希表 */
void myHashSetFree(MyHashSet *HashTable)
{
    if (HashTable == NULL) {
        return;
    }
    free(HashTable);
    HashTable = NULL;
}

bool containsDuplicate(int *nums, int numsSize)
{
    if (numsSize < 2) {
        return false;
    }
    int i = 0;
    MyHashSet *HashTable = myHashSetCreate(numsSize);
    for (i = 0; i < numsSize; i++) {
        if (myHashSetContains(HashTable, nums[i], numsSize) == true) {
            return true;
        }
        myHashSetAdd(HashTable, nums[i], numsSize);
    }
    return false;
}