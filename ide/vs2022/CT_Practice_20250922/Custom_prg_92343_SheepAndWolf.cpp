/*
 * [프로그래머스 92343] 양과 늑대 (Lv.3 심화)
 * - 훈련 날짜: 2026-06-05 (금)
 * - 알고리즘: DFS, State Space Search (상태 공간 탐색), Bitmasking (비트마스킹)
 * - 목적: 트리 구조에서 물리적 재방문 경로를 추적하는 대신, '다음에 이동 가능한 후보군' 상태를 제어하여 최대 획득량 도출
 * - 엔진 실무 최적화:
 * 1. O(1) State Transition : next_nodes 배열을 들고 다니며 erase/push_back을 수행할 때 발생하는 O(N)의 메모리 복사 오버헤드를 막기 위해,
 32비트 int 변수 하나를 스위치 보드로 사용하는 비트마스킹을 적용함.
 * 2. Global State Initialization : 다중 테스트 케이스가 연속으로 실행되는 채점 서버( 런타임 ) 환경을 고려하여,
 solution 진입 시 전역 배열( adj )과 글로벌 상태 변수( max_sheep )를 명시적으로 clear() 하여 메모리 오염을 방어함.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역] 
// =========================================================================
int max_sheep = 0;
int n = 0;
vector<int> adj[17];

void dfs(int current_node, int sheep, int wolf, int state, const vector<int>& info) {
    if (info[current_node] == 0)
        sheep++;
    else
        wolf++;

    if (wolf >= sheep) return;

    max_sheep = max(max_sheep, sheep);

    int next_state = state & ~(1 << current_node);

    for (int child : adj[current_node])
        next_state |= (1 << child);

    for (int i = 0; i < n; i++)
    {
        if (next_state & (1 << i))
            dfs(i, sheep, wolf, next_state, info);
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    n = (int)info.size();

    for (int i = 0; i < 17; i++)
        adj[i].clear();

    for (const auto& e : edges)
        adj[e[0]].push_back(e[1]);

    dfs(0, 0, 0, (1 << 0), info);

    return max_sheep;
}
// =========================================================================

int main() {
    // 테스트 케이스 1
    vector<int> info1 = { 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1 };
    vector<vector<int>> edges1 = { {0, 1}, {1, 2}, {1, 4}, {0, 8}, {8, 7}, {9, 10}, {9, 11}, {4, 3}, {6, 5}, {4, 6}, {8, 9} };
    int expected1 = 5;

    // 테스트 케이스 2
    vector<int> info2 = { 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0 };
    vector<vector<int>> edges2 = { {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {3, 7}, {4, 8}, {6, 9}, {9, 10} };
    int expected2 = 5;

    cout << "========================================" << endl;

    max_sheep = 0; // 글로벌 변수 초기화
    int result1 = solution(info1, edges1);
    cout << "[테스트 1] " << (result1 == expected1 ? "PASS" : "FAIL") << " | 기대값: " << expected1 << ", 실행값: " << result1 << endl;

    max_sheep = 0; // 글로벌 변수 초기화
    int result2 = solution(info2, edges2);
    cout << "[테스트 2] " << (result2 == expected2 ? "PASS" : "FAIL") << " | 기대값: " << expected2 << ", 실행값: " << result2 << endl;

    cout << "========================================" << endl;

    return 0;
}