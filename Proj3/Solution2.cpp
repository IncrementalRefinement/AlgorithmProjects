#include<bits/stdc++.h>

using namespace std;
const int maxn = 1005;
int no[maxn], id[maxn];
int vertexNum, res = -1, cost;
int G[maxn][maxn], cnt[maxn], group[maxn], vis[maxn], p[maxn];

// vis 当前最大团是哪些点
// ans 当前团size
//group 保存了答案中最大团的点
// cnt  从这个点往后搜索, 最大答案的size
//
void dfs(int u, int ans, int t_cost) {
    for (int i = u + 1; i <= vertexNum; i++) {
        // 花费过大时返回. 
        if (cnt[i] + ans < res || (cnt[i] + ans == res && t_cost >= cost))
            return;
        if (G[u][i]) {
            for (int j = 0; j < ans; j++)
                if (!G[i][vis[j]])
                    goto skip;
            vis[ans] = i;
            dfs(i, ans + 1, t_cost + p[i]);
            skip:;
        }
    }
    if (ans > res || (ans == res && t_cost < cost)) {
        for (int i = 0; i < ans; i++)
            group[i] = vis[i];
        res = ans;
        cost = t_cost;
    }
}

void maxclique() {
    for (int i = vertexNum; i > 0; i--) {
        vis[0] = i;// 假设大小为1的最大团开始搜索, 这个团
        dfs(i, 1, p[i]);// 查询V,有一个顶点, 花费p[i]价格
        cnt[i] = res;// 从这个点往后答案就是res
    }
}

int main() {
#ifdef MyTest
    freopen("Sakura.txt", "r", stdin);
#endif
    int edgeNum;// 当前最大团大小为1
    scanf("%d %d", &edgeNum, &vertexNum);
    memset(G, -1, sizeof(G));
    vector<pair<int, int> > edges(edgeNum);
    int pos = 1;
    for (int i = 0; i < edgeNum; i++)
        scanf("%d %d", &edges[i].first, &edges[i].second);
    for (int i = 0; i < vertexNum; i++) {
        int x, price;
        scanf("%d %d", &x, &price);
        if (!no[x]) {
            no[x] = pos;
            id[pos++] = x;
        }
        p[no[x]] = price;
    }
    for (pair<int, int> &x: edges)
        G[no[x.first]][no[x.second]] = G[no[x.second]][no[x.first]] = 0;
    maxclique();
    vector<int> v;
    for (int i = 0; i < res; i++)
        v.push_back(id[group[i]]);
    sort(v.begin(), v.end());
    printf("%d\n%03d", res, v[0]);
    for (int i = 1; i < res; i++)
        printf(" %03d", v[i]);
    printf("\n%d", cost);
    return 0;
}
