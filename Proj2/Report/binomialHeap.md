

| Operations                 | Binary Heap | Binomial Heap |
| :------------------------- | :---------- | :------------ |
| Make-Heap                  | O(1)        | O(1)          |
| Insert                     | Θ(logn)     | O(logn)       |
| Maximum (or Minimum)       | Θ(1)        | O(logn)       |
| Delete Max (or Delete Min) | Θ(logn)     | Θ(logn)       |
| Merge (Union)              | Θ(n)        | O(logn)       |

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
2. 



2.  I want swap key and value, but it would cause keyToNodeMap fail.
