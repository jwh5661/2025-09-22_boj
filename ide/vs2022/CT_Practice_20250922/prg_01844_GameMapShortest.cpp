/*
 * [프로그래머스 1844] 게임 맵 최단거리 (Lv.2)
 * - 훈련 날짜: 2026-04-23 (목)
 * - 알고리즘: 그래프 탐색 (BFS)
 * - 목적: 격자 지도에서 장애물을 피해 목적지까지 가는 최단 경로 산출
 * - 엔진 실무 최적화:
 * 1. memset을 이용한 O(1)에 가까운 메모리 초기화.
 * 2. visited 배열 하나로 '방문 여부'와 '최단 거리'를 동시에 관리하여 메모리 절약.
 * 3. 정적 코드 분석기( Static Analyzer )의 Bounds Check 경고를 방지하기 위한 예외 처리( Guard Clause ) 적용.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    typedef pair<int, int> Edge;

    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 1 };
    int visited[100][100];

    int solution(vector<vector<int>> maps) {
        queue<Edge> q;

        memset(visited, -1, sizeof(visited));

        int n = (int)maps.size();
        int m = n > 0 ? (int)maps[0].size() : 0;

        if (n < 1 || n > 100 || m < 1 || m > 100) return -1;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (maps[i][j] == 0)
                    visited[i][j] = 0;
            }
        }

        q.emplace(0, 0);
        visited[0][0] = 1;

        while (!q.empty())
        {
            auto cur = q.front(); q.pop();
            int cx = cur.first;
            int cy = cur.second;

            for (int d = 0; d < 4; d++)
            {
                int nx = cx + dx[d];
                int ny = cy + dy[d];

                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (visited[nx][ny] != -1) continue;

                q.emplace(nx, ny);
                visited[nx][ny] = visited[cx][cy] + 1;
            }
        }

        return visited[n - 1][m - 1];
    }
};
// =========================================================================

int main() {
    Solution sol;
    vector<vector<int>> m1 = {
        {1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1},
        {0, 0, 0, 0, 1}
    };
    // 기대 결과: 11

    cout << "[테스트 1] 실행 결과: " << sol.solution(m1) << " / 기대 결과: 11\n";
    return 0;
}