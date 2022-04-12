#include<bits/stdc++.h>

using namespace std;
const int maxn = 1005;
int idToIndex[maxn], indexToId[maxn];
int vertexNum, best = -1, Maxcost;
int G[maxn][maxn], cnt[maxn], group[maxn], vis[maxn], prices[maxn];
// vis 当前最大团是哪些点
// ans 当前团size
//group 保存了答案中最大团的点
// cnt  从这个点往后搜索, 最大答案的size
void dfs(int u, int ans, int t_cost) {
    for (int i = u + 1; i <= vertexNum; i++) {
        // 花费过大时返回. 这个, 加上之后的最大的都比best小就返回.
        if (cnt[i] + ans < best || (cnt[i] + ans == best && t_cost >= Maxcost))
            return;
        // 如果后面有连着的
        if (G[u][i]) {
            // 遍历当前团中的所有节点
            for (int j = 0; j < ans; j++)
                if (G[i][vis[j]] == 0)
                    goto skip;//跳出多重循环
            //说明都连着,就加1, dfs i这个节点
            vis[ans] = i;
            dfs(i, ans + 1, t_cost + prices[i]);
            skip:;
        }
    }
    //如果找到的答案更好, 就把答案保存到group中.
    if (ans > best || (ans == best && t_cost < Maxcost)) {
        for (int i = 0; i < ans; i++)
            group[i] = vis[i];
        best = ans;
        Maxcost = t_cost;
    }
}

void maxclique() {
    // 从后往前可以动态更新best, 不会覆盖.
    for (int i = vertexNum; i > 0; i--) {
        vis[0] = i;// 假设大小为1的最大团开始搜索, 这个团
        dfs(i, 1, prices[i]);// 查询V,有一个顶点, 花费p[i]价格
        cnt[i] = best;// 从这个点往后答案就是best
    }
}

int main() {
    auto pt = freopen(R"(..\dataset\Data\20.txt)", "r", stdin);
    assert(pt != NULL);
    int edgeNum;// 当前最大团大小为1
    scanf("%d %d", &edgeNum, &vertexNum);
    memset(G, 1, sizeof(G));
    vector<pair<int, int> > edges(edgeNum);
    int k = 1;
    for (int i = 0; i < edgeNum; i++)
        scanf("%d %d", &edges[i].first, &edges[i].second);
    // 在这个循环中记录tips.
    for (int i = 0; i < vertexNum; i++) {
        int x, price;
        scanf("%d %d", &x, &price);
        if (idToIndex[x] == 0) {
            // 如果是0
            idToIndex[x] = k;// 出现在第一个, 就给个k =1 , 记录在index to id
            indexToId[k++] = x;
        }
        prices[idToIndex[x]] = price;
    }
    // 记录反边.
    for (pair<int, int> &x: edges)
        G[idToIndex[x.first]][idToIndex[x.second]] = G[idToIndex[x.second]][idToIndex[x.first]] = 0;
    maxclique();
    vector<int> v;
    for (int i = 0; i < best; i++)
        v.push_back(indexToId[group[i]]);
    sort(v.begin(), v.end());
    printf("%d\n%03d", best, v[0]);
    for (int i = 1; i < best; i++)
        printf(" %03d", v[i]);
    printf("\n%d", Maxcost);
    return 0;
}
