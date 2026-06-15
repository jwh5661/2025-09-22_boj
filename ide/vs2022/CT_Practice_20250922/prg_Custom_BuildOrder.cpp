/*
 * [PRG_Mock_03] 기지 건설 순서 정렬 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-15 (월) (Week 1 금요일 커리큘럼 보충)
 * - 알고리즘: Topological Sort (위상 정렬)
 * - 목적: 단방향 인과율(Causality)이 존재하는 데이터들의 의존성을 분석하여, 데드락 없이 모든 작업을 수행할 수 있는 최적의 시퀀스 도출
 * - 엔진 실무 최적화:
 * 1. O(V + E) 스캔 : 크기 비교 기반의 O(N log N) 정렬 로직을 배제하고,
 진입차수 배열과 큐를 결합하여 노드와 간선을 단 한 번 씩만 스캔하는 극단적 최적화 달성.
 * 2. 안전한 메모리 생애주기 관리 : 전역 변수로 인한 다중 TC 오염을 방지하기 위해,
 그래프 인접 리스트( `adj` )와 `indegree` 배열을 함수 스택 내 지역 객체로 캡슐화함.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

vector<int> solution(int n, vector<vector<int>> build_order) {
    vector<int> answer;

    const int MAX = 32001;
    vector<vector<int>> adj(n + 1);
    queue<int> q;
    vector<int> indegree(n + 1, 0);

    for (const auto& order : build_order)
    {
        adj[order[0]].push_back(order[1]);
        indegree[order[1]]++;
    }

    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    while (!q.empty())
    {
        int cur = q.front(); q.pop();
        answer.push_back(cur);

        for (int next : adj[cur])
        {
            indegree[next]--;

            if (indegree[next] == 0)
                q.push(next);
        }
    }

    return answer;
}
// =========================================================================

int main() {
    int n = 5;
    // {A, B} : A를 지어야 B를 지을 수 있다. (A -> B)
    vector<vector<int>> build_order = {
        {1, 2}, // 1번 ➔ 2번
        {1, 3}, // 1번 ➔ 3번
        {2, 4}, // 2번 ➔ 4번
        {3, 4}, // 3번 ➔ 4번
        {4, 5}  // 4번 ➔ 5번
    };

    // 기대 정답 분석:
    // 진입차수 0인 건물은 1번뿐.
    // 1번 건설 후 2, 3번 해금.
    // 2, 3번 모두 건설되어야 4번 해금.
    // 결과적으로 {1, 2, 3, 4, 5} 또는 {1, 3, 2, 4, 5} 모두 정답 인정.
    vector<int> result = solution(n, build_order);

    cout << "========================================" << endl;
    cout << "[건설 시퀀스] ";
    for (int b : result) {
        cout << b << " ";
    }
    cout << "\n========================================" << endl;

    return 0;
}