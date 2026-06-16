/*
 * [PRG_Mock_05] 물류망 최적화 엔진 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-16 (화)
 * - 알고리즘: Floyd-Warshall (플로이드-워셜 다대다 최단 경로)
 * - 목적: 모든 노드 쌍 간의 최단 거리를 O(N^3) 매트릭스 연산으로 일괄 도출 및 동적 갱신
 * - 엔진 실무 최적화:
 * 1. 안전한 인덱스 시프팅 : 내부 연산은 가독성과 누락 방지를 위해 1-Based로 수행하되,
 결과물 반환 시 `answer[i - 1][j - 1]` 구조로 0-Based 시프팅 최적화.
 * 2. 오버플로우 언더컷 락 : 무한대 상수를 `1e9`로 락을 걸어, 
 `dist[i][k] + dist[k][j]` 연산 시의 최댓값을 20억으로 억제함으로써 C++ int 오버플로우 크래시를 원천 방지.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

vector<vector<int>> solution(int n, vector<vector<int>> edges) {
    const int INF = 1e9;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> answer(n, vector<int>(n, INF));

    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;

    for (const auto& e : edges)
        dist[e[0]][e[1]] = min(dist[e[0]][e[1]], e[2]);

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
    }
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dist[i][j] == INF) answer[i - 1][j - 1] = 0;
            else answer[i - 1][j - 1] = dist[i][j];
        }
    }

    return answer;
}
// =========================================================================

int main() {
    int n = 4;
    // {출발지, 도착지, 비용}
    vector<vector<int>> edges = {
        {1, 2, 4},
        {1, 4, 6},
        {2, 1, 3},
        {2, 3, 7},
        {3, 1, 5},
        {3, 4, 4},
        {4, 3, 2},
        // [주의] 중복 노선 함정 (동일한 경로이나 비용이 다름)
        {1, 2, 2}
    };

    // 기대 정답 분석:
    // [0, 2, 8, 6] (1번 ➔ 1/2/3/4번) - 1->2는 비용 2가 적용됨
    // [3, 0, 7, 9] (2번 ➔ 1/2/3/4번)
    // [5, 7, 0, 4] (3번 ➔ 1/2/3/4번)
    // [7, 9, 2, 0] (4번 ➔ 1/2/3/4번)
    vector<vector<int>> result = solution(n, edges);

    cout << "========================================" << endl;
    cout << "[모든 도시 간 최소 운송 비용 매트릭스]" << endl;
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    cout << "========================================" << endl;

    return 0;
}