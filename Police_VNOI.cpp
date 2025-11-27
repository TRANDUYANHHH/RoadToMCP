// link: https://oj.vnoi.info/problem/nkpolice
#include <bits/stdc++.h>

using namespace std;

#define sz(x) (int)((x).size())
#define all(x) (x).begin(), (x).end()
template<typename T> bool chmin(T &x, T y) { return (y < x ? x = y, 1 : 0); }
template<typename T> bool chmax(T &x, T y) { return (y > x ? x = y, 1 : 0); }

const int maxN = 100010;
int n, m, q;
int p[maxN][20];
vector<int> g[maxN];
int num[maxN], tail[maxN], low[maxN], depth[maxN], joint[maxN];
int timeDfs;
void calP() {
  p[1][0] = 1;
  for(int j = 1; j <= 19; j++){
    for(int i = 1; i <= n; i++){
      p[i][j] = p[p[i][j - 1]][j - 1];
    }
  }
}

int findPar(int u, int par){
  for(int i = 19; i >= 0; i--){
    if(depth[p[u][i]] > depth[par]) u = p[u][i];
  }
  return u;
}

bool isChild(int u, int par){
  return num[u] >= num[par] && tail[u] <= tail[par];
}

void dfs(int u, int pre){
  low[u] = num[u] = ++timeDfs;
  int child = 0;
  for(int v : g[u]){
    if(v == pre) continue;
    if(!num[v]){
      depth[v] = depth[u] + 1;
      p[v][0] = u;
      child++;
      dfs(v, u);
      chmin(low[u], low[v]);
      if(u == pre){
        if(child > 1){
          joint[u] = 1;
        }
      } else
      if(low[v] >= num[u]){
        joint[u] = 1;
      }
    } else {
      chmin(low[u], num[v]);
    }
  }
  tail[u] = timeDfs;
}

bool f1(int a, int b, int u, int v){
  if(num[v] < num[u]) swap(u, v);
  if(low[v] != num[v]) {
    return true;
  } 
  if(isChild(a, v) && !isChild(b, v)) return false;
  if(!isChild(a, v) && isChild(b, v)) return false;
  return true;
}
bool f2(int a, int b, int c){
  if(!joint[c]) return true;
  int pa = 0, pb = 0;
  if(isChild(a, c)) pa = findPar(a, c);
  if(isChild(b, c)) pb = findPar(b, c);
  if(!pa && !pb) return true;
  if(pa == pb) return true;
  if(!pa && low[pb] < num[c]) return true;
  if(!pb && low[pa] < num[c]) return true;
  if(pa && pb && low[pa] < num[c] && low[pb] < num[c]) return true;
  return false;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  for(int i = 0; i < m; i++){
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, 1);
  calP();
  int q;
  cin >> q;
  while(q--){
    int op;
    cin >> op;
    if(op == 1){
      int a, b, u, v;
      cin >> a >> b >> u >> v;
      cout << (f1(a, b, u, v) ? "yes" : "no");
    } else {
      int a, b, c;
      cin >> a >> b >> c;
      cout << (f2(a, b, c) ? "yes" : "no");
    }
    cout << '\n';
  }
  return 0;  
}
