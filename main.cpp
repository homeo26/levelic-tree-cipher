#include <bits/stdc++.h>
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef string str;
#define FOR(i, a, b) for(int (i) = a; (i) < (b); (i)++)
#define ROF(i, a, b) for(int (i) = a; (i) > (b); (i)--) // reversed FOR
#define elif else if
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define print(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define print(x...)
#endif

template<typename T>
auto len(const T &x) { return x.size(); }
#define all(x) x.begin(), x.end()
#define sum(a) (accumulate (all(a), 0ll))
#define mini(a) (*min_element(all(a)))
#define maxi(a) (*max_element(all(a)))
#define minidx(a) (min_element(all(a)) - (a).begin())
#define maxidx(a) (max_element(all(a)) - (a).begin())
#define bisect_left(a, x) ( lower_bound(all(a), (x)) - (a).begin())
#define bisect_right(a, x) ( upper_bound(all(a), (x)) - (a).begin())
const int MOD = 1e9 + 7;

inline ll add(ll a, ll b) {
    return (a % MOD + b % MOD) % MOD;
}

inline ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

inline ll mul(ll a, ll b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}

ll power(ll x, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p % 2)
            ret = mul(ret, x);
        p /= 2;
        x = mul(x, x);
    }
    return ret;
}

ll inv(ll x) {
    return power(x, MOD - 2);
}

inline ll divide(ll a, ll b) {
    return mul(a, inv(b));
}

ll fact(ll x) {
    if (x <= 1) {
        return 1;
    }

    return mul(x, fact(x - 1));
}

ll nPr(ll n, ll r) {
    return divide(fact(n), fact(n - r));
}

ll nCr(ll n, ll r) {
    return divide(fact(n), mul(fact(n - r), fact(r)));
}
//-----------------------------------------------------------------------------------------------------------------------------------


int sumConsecutivePowers(int p, int n){
    return (1 - (int)pow(p,(n+1))) / (1 - p);
}
pair<int,int> ceilTreeNodesCount(int numOfNodeChildren, int ptLength){
    int res = 1;
    int itr = 0;
    while (ptLength > res){
        res = sumConsecutivePowers(numOfNodeChildren,itr);
        itr +=1;
    }
    return make_pair(res,itr);
}

string fitPlainText(int numOfNodeChildren, str pt){
    return pt + string(
            ceilTreeNodesCount(numOfNodeChildren, pt.size()).first - pt.size(),
            '$'
            );
}

vector<vector<int>> buildLevelicTreeLevels(int numOfNodeChildren, str pt){
    vector<vector<int>> levels;
    int idx(0);
    str fitPt = fitPlainText(numOfNodeChildren, pt);

    for(int i = 0; i < ceilTreeNodesCount(numOfNodeChildren, fitPt.size()).second; i++){
        vector<int> curLevel;
        for(int j = 0; j < pow(numOfNodeChildren,i); j++){

            curLevel.push_back(idx);
            idx +=1;
        }
        levels.push_back(curLevel);
    }
    return levels;

}

vector<vector<int>> buildAdjList(int numOfNodeChildren, vector<vector<int>> ptTreeLevels, str pt){

    vector<vector<int>> adjList(fitPlainText(numOfNodeChildren, pt).size());
    for(int i = 0; i < ptTreeLevels.size() - 1; i++){

        vector<int> nextLevel = ptTreeLevels[i+1];
        int idx = 0;

        for (auto node : ptTreeLevels[i]) {

            for(int j = 0; j < numOfNodeChildren; j++) {
                adjList[node].push_back(nextLevel[idx]);
                idx += 1;
            }

        }
    }
    return adjList;
}

bool vis[int(1e5)];
str fitPt;
str cipherText;

void DFS(vector<vector<int>> adj, int node=0){
    if (vis[node]) return;
    cipherText+= fitPt[node];
    vis[node] = true;
    for(auto child : adj[node]){
            DFS(adj, child);
    }

}

string levelicTreeEncoder(int numOfNodeChildren, const str& pt){

    fitPt = fitPlainText(numOfNodeChildren, pt);

    DFS(buildAdjList(numOfNodeChildren,buildLevelicTreeLevels(numOfNodeChildren,pt), pt));
    return cipherText;

}

vector<vector<int>> recoverDfsPreorder(int numOfNodeChildren, str ct){

    stack<tuple<int,int,int>> stk;
    vector<vector<int>> adj(len(ct));
    int i = 1;
    stk.emplace(0,0,0);

    int dpth = ceilTreeNodesCount(numOfNodeChildren, ct.size()).second -1;

    while( i < len(ct) ){

        while (get<1>(stk.top()) == numOfNodeChildren or get<2>(stk.top()) == dpth){
            stk.pop();
            if (get<2>(stk.top()) == dpth)
                break;
        }

        adj[get<0>(stk.top())].push_back(i);
        get<1>(stk.top()) +=1;

        stk.emplace(i, 0, get<2>(stk.top())+1);

        i+=1;
    }
//    print(adj);
    return adj;
}

string BFS(vector<vector<int>> adj, str ct){

    str pt;

    queue<int> q;
    bool visited[len(ct)];
    memset(visited, false, sizeof visited);
    int distance[len(ct)];
    visited[0] = true;
    distance[0] = 0;
    pt += ct[0];

    q.push(0);
    while (!q.empty()) {
        int s = q.front(); q.pop();
        for (auto u : adj[s]) {
            if (visited[u]) continue;
            visited[u] = true;
            distance[u] = distance[s]+1;
            pt += ct[u];
            q.push(u);
        }
    }
    return pt;
}

string levelicTreeDecoder(int numOfNodeChildren, str ct){

    return BFS(recoverDfsPreorder(numOfNodeChildren, ct), ct);
}


void voila(){

    string plainText = "this is levelic tree cipher";
//    vector<vector<int>> levels = buildLevelicTreeLevels(2,pt);
//    print(levels);
//    print(buildAdjList(2,levels, pt));
    print(plainText);
    string cipherText = levelicTreeEncoder(3,plainText);
    print(cipherText);
    string recoveredPt = levelicTreeDecoder(3, cipherText);
    print(recoveredPt);


}

void voila2(){
    str s = "abcdefghijklmno";
    stack<tuple<int,int,int>> stk;
    vector<vector<int>> adj(len(s));
    int i = 1;
    stk.emplace(0,0,0);

    int dpth = 3;

    while( i < len(s) ){

        while (get<1>(stk.top()) == 2 or get<2>(stk.top()) == dpth){
            stk.pop();
            if (get<2>(stk.top()) == dpth)
                break;
            }

        adj[get<0>(stk.top())].push_back(i);
        get<1>(stk.top()) +=1;

        stk.emplace(i, 0, get<2>(stk.top())+1);

        i+=1;
    }
    print(adj);

}
// must n < pt -1
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    voila();
//    voila2();
    return 0;
}