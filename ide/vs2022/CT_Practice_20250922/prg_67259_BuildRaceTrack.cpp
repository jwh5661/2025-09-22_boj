/*
 * [프로그래머스 67259] 경주로 건설 (Lv.3)
 * - 훈련 날짜: 2026-05-02 (토)
 * - 알고리즘: 그래프 탐색 (BFS / Dijkstra 응용) & 2차원 좌표계
 * - 목적: 방향(Direction) 상태를 포함한 3차원 방문 배열을 활용하여, 코너링 비용이 존재하는 2D 그리드 환경에서의 최소 비용 산출
 * - 엔진 실무 최적화:
 * 1. 3차원 상태 공간( dir, y, x )을 1차원 배열( vector )로 평탄화하는 수학적 인덱스 매핑을 적용하여
 캐시 메모리 지역성 극대화
 * 2. 큐에서 꺼낸 상태의 비용이 이미 기록된 최소 비용보다 클 경우 즉시 폐기하는 조기 차단으로 큐 오버헤드 최소화.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    int dy[4] = { -1, 1, 0, 0 };
    int dx[4] = { 0, 0, -1, 1 };

    struct Edge {
        int y, x, cost, dir;

        Edge(int ny, int nx, int ncost, int ndir)
            :y(ny), x(nx), cost(ncost), dir(ndir) {
        }
    };

    int Flatten(int n, int mx_dir, int y, int x, int dir)
    {
        return y * n * mx_dir + x * mx_dir + dir; 
    }

    int solution(vector<vector<int>> board) {
        int answer = INT_MAX;
        int n = board.size();
        const int mx_dir = 4;

        vector<int> visited(n * n * mx_dir, INT_MAX);
        queue<Edge> q;
        q.emplace(1, 0, 100, 1);
        q.emplace(0, 1, 100, 3);
        for (int i = 0; i < mx_dir; i++)
            visited[Flatten(n, mx_dir, 0, 0, i)] = 0;
        visited[Flatten(n, mx_dir, 1, 0, 1)] = 100;
        visited[Flatten(n, mx_dir, 0, 1, 3)] = 100;

        while (!q.empty())
        {
            const auto& cur = q.front(); q.pop();
            
            if (cur.cost > visited[Flatten(n, mx_dir, cur.y, cur.x, cur.dir)]) continue;

            for (int d = 0; d < mx_dir; d++)
            {
                int ny = cur.y + dy[d];
                int nx = cur.x + dx[d];
                int ncost = cur.cost;
                if (cur.dir == d)
                    ncost += 100;
                else
                    ncost += 600;
   
                if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
                if (board[ny][nx] != 0) continue;
                if (ncost >= visited[Flatten(n, mx_dir, ny, nx, d)]) continue;

                q.emplace(ny, nx, ncost, d);
                visited[Flatten(n, mx_dir, ny, nx, d)] = ncost;
            }
        }

        for (int i = 0; i < mx_dir; i++)
        {
            if (answer > visited[Flatten(n, mx_dir, n - 1, n - 1, i)])
                answer = visited[Flatten(n, mx_dir, n - 1, n - 1, i)];
        }

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    // 테스트 1
    vector<vector<int>> b1 = {
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };
    // 기대 결과: 900

    // 테스트 2
    vector<vector<int>> b2 = {
        {0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0},
        {0,0,0,0,1,0,0,0},
        {0,0,0,1,0,0,0,1},
        {0,0,1,0,0,0,1,0},
        {0,1,0,0,0,1,0,0},
        {1,0,0,0,0,0,0,0}
    };
    // 기대 결과: 3800

    cout << "[테스트 1] 실행 결과: " << sol.solution(b1) << " / 기대 결과: 900\n";
    cout << "[테스트 2] 실행 결과: " << sol.solution(b2) << " / 기대 결과: 3800\n";

    return 0;
}