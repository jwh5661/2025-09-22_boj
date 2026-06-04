/*
 * [자체 제작] 대규모 트래픽 라우팅 분산 (Lv.4)
 * - 훈련 날짜: 2026-06-04 (목)
 * - 알고리즘: Network Flow (네트워크 유량), Edmonds-Karp (에드몬드-카프), BFS
 * - 목적: 단방향 가중치 그래프에서 자원의 동시 다발적 흐름을 제어하고, 역방향 간선을 이용해 누적 유량을 극대화함.
 * - 엔진 실무 최적화:
 * 1. Residual Graph Pre-allocation : 인접 리스트 초기화 시 정방향 간선 뿐만 아니라 용량이 0인 역방향 간선을 사전에 강제 개통해여,
 런타임 중 추가적인 동적 메모리 할당 없이 BFS 오버헤드를 최소화함.
 * 2. Shortest Augmenting Path : DFS 기반으 포드-폴커슨( O(E * f )) 대신 BFS 기반의 에드몬드-카프( O(V * E^2) )를 선택하여,
 유량의 크기( f )와 무관하게 일정한 다항 시간 내에 알고리즘이 반드시 종결되도록 안정성을 확보함.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역] 
// =========================================================================
int solution(int N, vector<vector<int>> cables) {
    int answer = 0;

    vector<vector<int>> adj(N + 1);
    vector<vector<int>> capacity(N + 1, vector<int>(N + 1, 0));
    vector<vector<int>> flow(N + 1, vector<int>(N + 1, 0));

    for (int i = 0; i < cables.size(); i++)
    {
        adj[cables[i][0]].push_back(cables[i][1]);
        adj[cables[i][1]].push_back(cables[i][0]);
        capacity[cables[i][0]][cables[i][1]] += cables[i][2];
    }

    while (true)
    {
        vector<int> parent(N + 1, -1);
        queue<int> q;

        q.push(1);

        while (!q.empty())
        {
            int cur = q.front(); q.pop();

            for (int next : adj[cur])
            {
                if (parent[next] != -1) continue;
                if (capacity[cur][next] - flow[cur][next] <= 0) continue;

                parent[next] = cur;
                q.push(next);
            }
        }

        if (parent[N] == -1) break;

        int i = N, BottleNeck = 1e9;

        while (i != 1)
        {
            BottleNeck = min(BottleNeck, capacity[parent[i]][i] - flow[parent[i]][i]);
            i = parent[i];
        }

        i = N;

        while (i != 1)
        {
            flow[parent[i]][i] += BottleNeck;
            flow[i][parent[i]] -= BottleNeck;
            i = parent[i];
        }

        answer += BottleNeck;
    }

    return answer;
}
// =========================================================================

int main() {
    int N = 6;
    // [u, v, capacity]
    vector<vector<int>> cables = {
        {1, 2, 10}, {1, 3, 10},
        {2, 3, 2},  {2, 4, 4}, {2, 5, 8},
        {3, 5, 9},
        {4, 6, 10},
        {5, 4, 6},  {5, 6, 10}
    };
    // 기대 결과: 19

    cout << "[테스트 1] 실행 결과: " << solution(N, cables) << " / 기대 결과: 19\n";

    return 0;
}