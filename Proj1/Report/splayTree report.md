#### Project Description

1. implement splay tree
2. to compare their performance under different sequences of operations

You should test these data structures in the following cases.

- insertion of *N* elements in increasing order.
- insertion of *N* elements in random order.
- random deletion of all the *N* elements from a tree that is built by random insertion.
- *N* random queries in a tree that is built by random insertion.
- *N* skewed queries in a tree that is built by random insertion. By skewed, we mean that only a small fraction of the elements are frequently quired. 通过随机插入构建的树中的倾斜查询。通过倾斜，我们的意思是只有一小部分元素经常被查询。

You should try different *N*, and plot the time cost againt *N*. For insertion, you should also compare the height of the resulting trees.

#### Submission Guidelines

The report should be written clearly and neatly in English. It should starts with a title page containing the title, the group id, the author names, and an abstract summarizing your work. Within the 10 pages following the title page, the report should present the following contents.

- A clear description of this project.
- A comparison of the theoretical performance of these data structures.
- Implementation details that, you think, may affect the performance of the data structures.
- Testing results and analysis of these results.
- Conclusion.

The report should be typeset using 12-point fonts, in a single-column, single-space format.

The source code should be in good style, and have sufficient comments.



### Implement

#### splay

we divide into 4 situation to process, gradually move node upward until it become the root.

#### delete

Firstly, we find the node. If it isn't exist, return directly.  If it is existed, then we use split function: we splay x to the root, and then split tree to two subtree. Next we use join function: splay the maximum node in left subtree, and then link right subtree to its right. 



### Problem

1 garbled print

I change the print method.

2 How to change pointer within a function

There are three methods. The first is to return the new pointer from the function. 

The second method is to declare the first parameter as pointer to pointer.

And the third method is declare reference to pointer

```cpp
void split(NodePtr x, NodePtr s, NodePtr t) 
//change to :
void split(NodePtr& x, NodePtr &s, NodePtr& t) 
```

