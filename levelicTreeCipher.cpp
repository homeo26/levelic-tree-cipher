#include <bits/stdc++.h>

using namespace std;

typedef string str;

// Debugging Methods
//-----------------------------------------------------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------------------------------------------------------


// Filler character used to pad the tree nodes to achieve a perfect tree.
// It can be any unique character chosen to identify the FILLER nodes.
const char FILLER = '$';

/**
 * Calculates the sum of consecutive powers of a number.
 * Reference: https://math.stackexchange.com/questions/971761/calculating-sum-of-consecutive-powers-of-a-number
 *
 * @param base The base number whose powers are summed consecutively.
 * @param exponent The number of powers to sum.
 * @return The sum of consecutive powers of the base number.
 */
int sumConsecutivePowers(int base, int exponent) {
    return (1 - (int) pow(base, (exponent + 1))) / (1 - base);
}

int ceilTreeNodesCount(int numOfNodeChildren, int ptLength) {
    int nodesSum = 1;
    int exponent = 0;
    while (ptLength > nodesSum) {
        nodesSum = sumConsecutivePowers(numOfNodeChildren, exponent);
        exponent += 1;
    }
    return nodesSum;
}

int treeDepth(int numOfNodeChildren, int ptLength){
    int nodesSum = 1;
    int exponent = 0;
    while (ptLength > nodesSum) {
        nodesSum = sumConsecutivePowers(numOfNodeChildren, exponent);
        exponent += 1;
    }
    return exponent;
}

/**
 * Appends filler characters to the end of a plaintext string to fit the required number
 * of tree nodes for a perfect tree with a given number of children per node.
 *
 * @param numOfNodeChildren The number of children each node has in the tree.
 * @param plainText The plaintext string to be padded.
 * @return The padded plaintext string to fit the required number of tree nodes.
 */
string fitPlainText(int numOfNodeChildren, const string& plainText) {
    int ceilNodesCount = ceilTreeNodesCount(numOfNodeChildren, plainText.size()) ;
    return plainText + string(ceilNodesCount - plainText.size(),FILLER);
}

/**
 * Builds a vector of vectors representing levels of a tree where each vector contains
 * all nodes of that level/depth.
 *
 * @param numOfNodeChildren The number of children each node has in the tree.
 * @param plainText The plaintext which will be encrypted.
 * @return A vector of vectors representing the levels of the tree, where each level contains its nodes.
 */
vector<vector<int>> buildLevelicTreeLevels(int numOfNodeChildren, str plainText) {
    vector<vector<int>> levels;
    int idx(0);
    str fitPt = fitPlainText(numOfNodeChildren, plainText);

    for (int i = 0; i < treeDepth(numOfNodeChildren, fitPt.size()); i++) {
        vector<int> curLevel;
        for (int j = 0; j < pow(numOfNodeChildren, i); j++) {

            curLevel.push_back(idx);
            idx += 1;
        }
        levels.push_back(curLevel);
    }
    return levels;

}

/**
 * Builds an adjacency list representation of a tree based on the levels components of the tree.
 *
 * @param numOfNodeChildren The number of children each node has in the tree.
 * @param ptTreeLevels A vector of vectors representing the levels of the tree.
 * @param plainText The plaintext which will be encrypted.
 * @return An adjacency list representation of the tree.
 */
vector<vector<int>> buildTreeAdjacencyList(int numOfNodeChildren, vector<vector<int>> ptTreeLevels, const str& plainText) {

    vector<vector<int>> adjList(fitPlainText(numOfNodeChildren, plainText).size());
    for (int i = 0; i < ptTreeLevels.size() - 1; i++) {

        vector<int> nextLevel = ptTreeLevels[i + 1];
        int idx = 0;

        for (auto node: ptTreeLevels[i]) {

            for (int j = 0; j < numOfNodeChildren; j++) {
                adjList[node].push_back(nextLevel[idx]);
                idx += 1;
            }

        }
    }
    return adjList;
}

bool vis[int(1e5)];
str fitPt;
str generatedCipherText;

void DFS(vector<vector<int>> adjList, int node = 0) {
    if (vis[node]) return;
    generatedCipherText += fitPt[node];
    vis[node] = true;
    for (auto child: adjList[node]) {
        DFS(adjList, child);
    }

}

string levelicTreeEncoder(int numOfNodeChildren, const str &pt) {

    fitPt = fitPlainText(numOfNodeChildren, pt);

    DFS(buildTreeAdjacencyList(numOfNodeChildren, buildLevelicTreeLevels(numOfNodeChildren, pt), pt));
    return generatedCipherText;

}

vector<vector<int>> recoverDfsPreorder(int numOfNodeChildren, str ct) {

    stack<tuple<int, int, int>> stk;
    vector<vector<int>> adj(len(ct));
    int i = 1;
    stk.emplace(0, 0, 0);

    int dpth = treeDepth(numOfNodeChildren, ct.size()) - 1;

    while (i < len(ct)) {

        while (get<1>(stk.top()) == numOfNodeChildren or get<2>(stk.top()) == dpth) {
            stk.pop();
            if (get<2>(stk.top()) == dpth)
                break;
        }

        adj[get<0>(stk.top())].push_back(i);
        get<1>(stk.top()) += 1;

        stk.emplace(i, 0, get<2>(stk.top()) + 1);

        i += 1;
    }
    return adj;
}

string BFS(vector<vector<int>> adj, str cipherText) {

    str plainText;

    queue<int> q;
    bool visited[len(cipherText)];
    memset(visited, false, sizeof visited);
    int distance[len(cipherText)];
    visited[0] = true;
    distance[0] = 0;
    plainText += cipherText[0];

    q.push(0);
    while (!q.empty()) {
        int s = q.front();
        q.pop();
        for (auto u: adj[s]) {
            if (visited[u]) continue;
            visited[u] = true;
            distance[u] = distance[s] + 1;
            plainText += cipherText[u];
            q.push(u);
        }
    }
    return plainText;
}

string levelicTreeDecoder(int numOfNodeChildren, str ct) {

    string recoveredPlainText = BFS(recoverDfsPreorder(numOfNodeChildren, ct), ct);

    // remove this string processing query if you want the output with padding
    recoveredPlainText.erase(
            remove_if(recoveredPlainText.begin(), recoveredPlainText.end(),[&](char c) { return c == FILLER; }),
            recoveredPlainText.end()
            );
    // --------------------

    return recoveredPlainText;
}



int main() {

    cout << endl;

    // number of children of each node
    // must be < len(plainText)-1
    int nodeChildrenCtr = 3; // Ternary Tree

    string plainText = "sample text for levelic tree cipher";
    string cipherText = levelicTreeEncoder(nodeChildrenCtr, plainText);
    string recoveredPt = levelicTreeDecoder(nodeChildrenCtr, cipherText);

    cout << "[Plain Text]: \t\t\t\t" << plainText << endl;
    cout << "[Cipher Text]: \t\t\t\t" << cipherText << endl;
    cout << endl;
    cout << "[Recovered Plain Text]: \t" << recoveredPt << endl;

    return 0;
}