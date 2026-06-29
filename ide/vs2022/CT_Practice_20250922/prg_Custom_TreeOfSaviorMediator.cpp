/*
 * [PRG_Mock_16] 트리 오브 세이비어 중재자 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-29 (월)
 * - 알고리즘: Lowest Common Ancestor (LCA), Binary Lifting (이진 점프), BFS
 * - 목적: N=100,000 규모의 트리 계층 구조에서 M=100,000번의 최소 공통 조상 탐색 쿼리를 고속 처리
 * - 엔진 실무 최적화:
 * 1. `parent[i][j] = parent[i - 1][parent[i - 1][j]]` 점화식을 통한 O(N log N) 희소 배열 전처리.
 * 2. `answer.reserve(queries.size())`를 통한 벡터 재할당 오버헤드 제거 및 BFS 기반의 Non-recursive 트리 세팅.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

const int MAX_NODE = 100005;
const int LOG = 18;

int depth[MAX_NODE];
int parent[LOG][MAX_NODE];
vector<int> adj[MAX_NODE];
bool visited[MAX_NODE];

int get_lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int diff = depth[u] - depth[v];
    for (int i = LOG - 1; i >= 0; i--)
    {
        if (diff & (1 << i))
            u = parent[i][u];
    }

    if (u == v)
        return u;

    for (int i = LOG - 1; i >= 0; i--)
    {
        if (parent[i][u] != parent[i][v])
        {
            u = parent[i][u];
            v = parent[i][v];
        }
    }

    return parent[0][u];
}

vector<int> solution(int n, vector<vector<int>> edges, vector<vector<int>> queries) {
    vector<int> answer;
    answer.reserve(queries.size());

    // 1. 초기화 (전역 배열 리셋)
    for (int i = 0; i < MAX_NODE; i++)
        adj[i].clear();

    memset(depth, 0, sizeof(depth));
    memset(parent, 0, sizeof(parent));
    memset(visited, false, sizeof(visited));

    // 2. 트리 구축 (양방향)
    for (const auto& e : edges)
    {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }

    // 3. BFS를 이용한 depth 및 parent[0] 세팅 (루트는 1번)
    queue<int> q;
    visited[1] = true;
    q.emplace(1);
    
    while (!q.empty())
    {
        int cur = q.front(); q.pop();

        for (int next : adj[cur])
        {
            if (visited[next]) continue;
            visited[next] = true;
            parent[0][next] = cur;
            q.emplace(next);
            depth[next] = depth[cur] + 1;
        }
    }

    // 4. DP 장부(parent[k][v]) 갱신
    for (int i = 1; i < LOG; i++)
    {
        for (int j = 1; j <= n; j++)
            parent[i][j] = parent[i - 1][parent[i - 1][j]];
    }

    // 5. 쿼리 처리
    for (const auto& q : queries)
        answer.emplace_back(get_lca(q[0], q[1]));

    return answer;
}
// =========================================================================

int main() {
    int n = 11;

    // 트리의 양방향 간선 (1번이 루트)
    vector<vector<int>> edges = {
        {1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {3, 7},
        {4, 8}, {4, 9}, {5, 10}, {5, 11}
    };

    // 분쟁 중재 쿼리 {유저A, 유저B}
    vector<vector<int>> queries = {
        {8, 11}, // 8과 11의 중재자 -> 2
        {6, 7},  // 6과 7의 중재자 -> 3
        {9, 10}, // 9와 10의 중재자 -> 2
        {8, 6},  // 8과 6의 중재자 -> 1
        {2, 11}  // 2와 11의 중재자 -> 2 (2가 11의 상관이므로)
    };

    vector<int> result = solution(n, edges, queries);

    cout << "========================================" << endl;
    cout << "[결과 확인]" << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << "Query " << i + 1 << " 중재자: " << result[i] << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "[로컬 디버깅용 검증 기대값]" << endl;
    cout << "2, 3, 2, 1, 2" << endl;
    cout << "========================================" << endl;

    return 0;
}