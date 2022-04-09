

| Operations                 | Binary Heap | Binomial Heap |
| :------------------------- | :---------- | :------------ |
| Make-Heap                  | O(1)        | O(1)          |
| Insert                     | Θ(logn)     | O(logn)       |
| Maximum (or Minimum)       | Θ(1)        | O(logn)       |
| Delete Max (or Delete Min) | Θ(logn)     | Θ(logn)       |
| Merge (Union)              | Θ(n)        | O(logn)       |



## Description

项目架构介绍 陆天

## Introduction

fabonacci堆的实现， 支持操作的介绍  lt

## Theoretical Comparison

各个堆的性能对比。 画个表， 简介。 写自己堆的简介。 

## Theoretical Analysis

分析运行速度。    lt

## experiment and  result

state：  DC xxx ljy 

## Discussion and Conclusion.

奇怪的是，  Fibonacci 很慢， 因为 我们dji 的实现， 堆的深度很浅， fibo nacci 有大量链表的操作， 如果我们用另一种实现， 可以有更优秀的表现。



### Implementition

#### merge

1. merge two heap into an linkedlist,  with asec order.
2. process each same degree tree, until all tree has different degree.

How to merge same degree trees?

```python
if cur.degree == cur.next.degree :
	if cur.key <= cur.next.key:
		combine(cur, cur.next)
	else:
		combine(cur.next,cur)
else:
    cur = cur.next
```

#### pop

1. find smallest node from the heap
2. remove the node, the children of the node can also turn into a new binomial Heap.
3. reverse the new heap link list. In this way, the degree of roots will have a ascend order.
4. merge new heap and old heap.

Problem

1. insert7 , head = 4 instead of 0 . head don't point root.

2.  I want swap key and value, but it would cause keyToNodeMap fail.
