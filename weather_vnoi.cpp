// link: https://oj.vnoi.info/problem/weather
#include <bits/stdc++.h>

using namespace std;

#define sz(x) (int)((x).size())
#define all(x) (x).begin(), (x).end()
template<typename T> bool chmin(T &x, T y) { return (y < x ? x = y, 1 : 0); }
template<typename T> bool chmax(T &x, T y) { return (y > x ? x = y, 1 : 0); }

const int maxN = 105;
vector<int> g[maxN];
int num[maxN], low[maxN], child[maxN];
vector<int> bridge;
int timeDfs;

void dfs(int u, int pre){
  num[u] = low[u] = ++timeDfs;
  for(int v : g[u]){
    if(v == pre) continue;
    if(!num[v]){
      dfs(v, u);
      child[u] += 1 + child[v];
      chmin(low[u], low[v]);
      if(low[v] == num[v]){
        bridge.push_back(v);
      }
    } else {
      chmin(low[u], num[v]);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  for(int i = 0; i < m; i++){
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(0, 0);
  int ans = 0;
  for(auto v : bridge){
    ans += (child[v] + 1) * (n - child[v] - 1);
  }
  cout << ans;
  return 0;  
}
