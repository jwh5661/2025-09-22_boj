/*
 * [프로그래머스 49189] 가장 먼 노드 (Lv.3)
 * - 훈련 날짜: 2026-05-18 (월)
 * - 알고리즘: Graph (그래프), BFS (너비 우선 탐색)
 * - 목적: 가중치가 1로 동일한 무방향 그래프에서 인접 리스트와 큐를 활용하여 최단 거리를 산출
 * - 엔진 실무 최적화:
 * 1. 2차원 배열( 인접 행렬 ) 대신 인접 리스트를 사용하여 메모리 파편화 및 낭비를 방지함.
 * 2. BFS의 레벨 순서 탐색 특성을 활용하여, 큐 삽입 과정에서 별도의 대소 비교 없이
 즉시 최대 거리를 갱신하는 최적화 달성.
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    int solution(int n, vector<vector<int>> edge) {
        vector<vector<int>> adj(n + 1);
        vector<int> visited(n + 1, -1);
        queue<int> q;
        int answer = 0;
        int mxVal = -1;

        for (const auto& e : edge)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        
        visited[1] = 0;
        q.emplace(1);
         
        while (!q.empty())
        {
            int cur = q.front(); q.pop();

            for (const int next : adj[cur])
            {
                if (visited[next] != -1) continue;

                visited[next] = visited[cur] + 1;
                mxVal = visited[next];
                q.emplace(next);
            }
        }

        for (int i = 1; i <= n; i++)
        {
            if (mxVal == visited[i])
                answer++;
        }

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    int n = 6;
    vector<vector<int>> edge = {
        {3, 6}, {4, 3}, {3, 2}, {1, 3}, {1, 2}, {2, 4}, {5, 2}
    };
    // 기대 결과: 3

    cout << "[테스트 1] 실행 결과: " << sol.solution(n, edge) << " / 기대 결과: 3\n";

    return 0;
}