/*
 * [프로그래머스 43162] 네트워크 (Lv.3)
 * - 훈련 날짜: 2026-04-23 (목)
 * - 알고리즘: 그래프 탐색 (DFS/BFS)
 * - 목적: 인접 행렬로 주어진 그래프에서 독립된 네트워크(연결 요소)의 개수 파악
 * - 엔진 실무 최적화:
 * 1. 콜 스택( Call Stack ) 오버플로우 위험이 있는 재귀 함수 대신, 
 std::stack을 활용한 반복문 기반( Iterative ) DFS 구현.
 * 2. memset을 이용한 O(1) 메모리 초기화.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    bool visited[201];

    int solution(int n, vector<vector<int>> computers) {
        stack<int> stk;
        int answer = 0;
       
        memset(visited, false, sizeof(visited));

        for (int i = 0; i < n; i++)
        {
            if (visited[i]) continue;

            answer++;
            stk.push(i);

            while (!stk.empty())
            {
                int cur = stk.top(); stk.pop();
                visited[cur] = true;

                for (int j = 0; j < n; j++)
                {
                    if (cur == j) continue;
                    if (visited[j]) continue;
                    if (computers[cur][j] == 0) continue;

                    stk.push(j);
                }
            }
        }

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;
    int n1 = 3;
    vector<vector<int>> c1 = { {1, 1, 0}, {1, 1, 0}, {0, 0, 1} };
    // 기대 결과: 2

    int n2 = 3;
    vector<vector<int>> c2 = { {1, 1, 0}, {1, 1, 1}, {0, 1, 1} };
    // 기대 결과: 1

    cout << "[테스트 1] 실행 결과: " << sol.solution(n1, c1) << " / 기대 결과: 2\n";
    cout << "[테스트 2] 실행 결과: " << sol.solution(n2, c2) << " / 기대 결과: 1\n";
    return 0;
}