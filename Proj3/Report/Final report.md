# Project 3 Safe Fruit

- Lin Juyi - 3180103721
- Lu Tian - 3180103740

## 1. Description of the problem.

There are a lot of tips telling us that some fruits must not be eaten with some other fruits, or we might get ourselves in serious trouble. For example, bananas can not be eaten with cantaloupe (哈密瓜), otherwise it will lead to kidney deficiency (肾虚).

Now you are given a long list of such tips, and a big basket of fruits. You are supposed to pick up those fruits so that it is safe to eat any of them.

要求所有两两不相连的最大水果集, 就是最大独立集,    我们要求最大独立集,  顶点集V中取 K个顶点，其两两间无连接。

图G的补图，通俗的来讲就是完全图Kn去除G的边集后得到的图Kn-G.  是一个图有着跟*G*相同的点，而且这些点之间有边相连[当且仅当](https://baike.baidu.com/item/当且仅当/7689242)在*G*里面他们没有边相连。

最大团：　顶点集V中取 K个顶点，其两两间有边连接。

最大团中顶点数量 = 补图的最大独立集中顶点数量

就可以通过求其补图中最大团中顶点数量,就可得出原图中最大独立集中顶点数量了.

### Input Specification:

Each input file contains one test case. For each case, the first line gives two positive integers: N, the number of tips, and M, the number of fruits in the basket. both numbers are no more than 100.

Then two blocks follow. The first block contains N pairs of fruits which must not be eaten together, each pair occupies a line and there is no duplicated tips; and the second one contains M fruits together with their prices, again each pair in a line. To make it simple, each fruit is represented by a 3-digit ID number. A price is a positive integer which is no more than 1000. All the numbers in a line are separated by spaces.

### Output Specification:

For each case, first print in a line the maximum number of safe fruits. Then in the next line list all the safe fruits, in increasing order of their ID's. The ID's must be separated by exactly one space, and there must be no extra space at the end of the line. Finally in the third line print the total price of the above fruits. Since there may be many different solutions, you are supposed to output the one with a maximum number of safe fruits. In case there is a tie, output the one with the lowest total price. It is guaranteed that such a solution is unique.

In our input file, we do not guarantee that such a solution is unique.



## 2. Algorithm





## 3. Theoretical Analysis

列出所有子集, 测试是否独立, 是 O( p(vertexNum) 2^vertexNum)  , where p(vertexNum) is some polynomial.

论文提出了O(2^ (vertexNum/3)) 复杂度. 





## 4. Experiment

Bounds of the running time of our algorithm on a graph with node can be expressed as a function of xxx

 the running time is[1]:
$$
\Theta(|E| * T_{\text{dk}} + |V| * T_{\text{pop}})
$$


## 5. Discussion and Conclusion



## 6. References

1.http://i.stanford.edu/pub/cstr/reports/cs/tr/76/550/CS-TR-76-550.pdf
