// MyListNode.h
#ifndef MY_LISTNODE_H
#define MY_LISTNODE_H
#include <initializer_list>
#include <iostream>
#include <vector>

/**
 * 链表节点定义
 * @param val 节点值
 * @param next 指向下一个节点的指针
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) { }
	ListNode(int x) : val(x), next(nullptr) { }
	ListNode(int x, ListNode *next) : val(x), next(next) { }
};

/**
 * 创建值为1到n的链表
 * @param n 链表长度
 * @return 链表头节点
 */
ListNode *createList(int n);

/**
 * 根据整数数组创建链表
 * @param values 整数数组
 * @return 链表头节点
 */
ListNode *createList(const std::initializer_list<int> &values);

/**
* 输出链表
* @param head 链表头节点
*/
std::ostream &operator<<(std::ostream &os, ListNode *head);

/**
 * 释放链表内存
 * @param head 链表头节点
 */
void deleteList(ListNode *head);

#endif // MY_LISTNODE_H