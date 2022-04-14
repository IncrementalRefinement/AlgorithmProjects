#include<chrono>
#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
const int SIZE = 1005;
int Graph[SIZE][SIZE] = {0}; // 图矩阵
int dp[SIZE];// dp[i]表示从i到n-1中的最大团的节点数。
int Stack[SIZE][SIZE];
vector<int> idToIndex(SIZE, 105), indexToId(SIZE);
vector<int> tips_id[SIZE];
vector<int> temppath, path;
int price[SIZE];
int vertexNum;
int tempans = 0, ans, best =0;

void dfs(int num, int step) {
    if (num == 0) {
        //  当此团中最后一个点 没有 比起序号大 的顶点相连时
        if (step > best || (step == best && tempans < ans)) {
            ans = tempans;
            best = step;// mx为最大团中顶点的数量
            path = temppath;
        }
        return;
    }
    //枚举每一个与 u 相连的顶点 adj[i]
    for (int i = 0; i < num; ++i) {
        int k = Stack[step][i];
        // prune
        // 剪枝1， 若当前 顶点数量cnt 加上还能够增加的最大数量 仍小于 best则 退出并返回false
        if (step + vertexNum - k < best)
            return;
        //剪枝2， 若当前 顶点数量cnt 加上 包含adj[i]的最大团顶点数 仍小于 best则 退出并返回false
        if (step + dp[k] < best)
            return;
        int cnt = 0;
        // 扫描与u相连的顶点中与 adj[u]相连的顶点 并存储到数组Stack中，数量为cnt
        for (int j = i + 1; j < num; ++j)
            if (!Graph[k][Stack[step][j]])
                Stack[step + 1][cnt++] = Stack[step][j];
        temppath.push_back(k);
        tempans += price[k];
        dfs(cnt, step + 1);
        tempans -= price[k];
        temppath.pop_back();
    }
}

void run() {
    for (int i = vertexNum - 1; i >= 0; --i) {
        int sz = 0;
        for (int j = i + 1; j < vertexNum; ++j) // 遍历所有下面的顶点
            if (!Graph[i][j]) // 不存在边
                Stack[1][sz++] = j;
        temppath.push_back(i);
        tempans += price[i];
        dfs(sz, 1);
        tempans -= price[i];
        temppath.pop_back();
        dp[i] = best;
    }
}

int main() {
    auto pt = freopen(R"(..\dataset\Data\100sparse.txt)", "r", stdin);
    assert(pt != NULL);
    int edgeNum, a, b;
    // edgeNum is edge num, m is vertex num
    scanf("%d %d", &edgeNum, &vertexNum);
    for (int i = 0; i < edgeNum; ++i) {
        scanf("%d %d", &a, &b);
        tips_id[a].push_back(b);
    }
    for (int i = 0; i < vertexNum; ++i) {
        scanf("%d %d", &a, &price[i]);
        indexToId[i] = a;
        idToIndex[a] = i;
    }
    for (int i = 0; i < vertexNum; ++i) {
        Graph[i][i] = 1;
        for (int j: tips_id[indexToId[i]])
            if (idToIndex[j] < vertexNum)
                Graph[i][idToIndex[j]] = Graph[idToIndex[j]][i] = 1;
    }
    auto start = system_clock::now();
    run();
    auto end   = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << double(duration.count()) * microseconds::period::num
         << " microseconds" << endl;
    for (int i = 0; i < path.size(); ++i)
        path[i] = indexToId[path[i]];
    sort(path.begin(), path.end());
    printf("%d\n%03d", best, path[0]);
    for (int i = 1; i < path.size(); ++i)
        printf(" %03d", path[i]);
    printf("\n%d", ans);
}