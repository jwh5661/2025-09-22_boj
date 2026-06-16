/*
 * [PRG_Mock_06] 초고속 통신망 구축 엔진 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-16 (화) (Week 1 토요일 커리큘럼 보충)
 * - 알고리즘: Kruskal (크루스칼 최소 신장 트리) & Union-Find
 * - 목적: N개의 고립된 노드를 사이클 없이 모두 연결하는 최소 비용 네트워크(MST) 구축
 * - 엔진 실무 최적화:
 * 1. 람다 커스텀 정렬 : `sort` 내부 람다 함수를 통해 2차원 벡터의 3번째 원소( 비용 )만을 기준으로 O( M log M ) 고속 정렬 수행.
 * 2. 경로 압축 ( Path Compression ) : `Find` 재귀 호출 시 반환값을 `parent`에 즉시 덮어씌워,
 트리가 편향되는 최악의 O(N) 병목을 O(1) 수준으로 압축.
 * 3. 조기 종료 ( Early Exit ) : 연결된 간선이 `N - 1`개가 되는 순간 MST가 완성되었음을 수학적으로 확정하고
 루프를 즉시 파괴( `break` )하여 잉여 연산 제거.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================
const int MAX = 1001;
int parent[MAX];

int Find(int x)
{
    if (x == parent[x]) return x;
    return parent[x] = Find(parent[x]);
}

bool Union(int a, int b)
{
    a = Find(a);
    b = Find(b);

    if (a == b) return false;

    parent[b] = a;
    return true;
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;

    sort(costs.begin(), costs.end(), [](vector<int>& a, vector<int>& b) { return a[2] < b[2]; });

    for (int i = 1; i <= n; i++)
        parent[i] = i;

    int edge_cnt = 0;

    for (const auto& e : costs)
    {
        if (Union(e[0], e[1]))
        {
            answer += e[2];
            edge_cnt++;
        }

        if (edge_cnt == n - 1) break;
    }

    return answer;
}
// =========================================================================

int main() {
    int n = 6;
    // {기지 A, 기지 B, 건설 비용}
    vector<vector<int>> costs = {
        {1, 2, 5},
        {1, 3, 4},
        {2, 3, 2},
        {2, 4, 7},
        {3, 4, 6},
        {3, 5, 11},
        {4, 5, 3},
        {4, 6, 8},
        {5, 6, 8}
    };

    // 기대 정답 분석:
    // 1. 비용 2: (2, 3) 연결 (edge=1)
    // 2. 비용 3: (4, 5) 연결 (edge=2)
    // 3. 비용 4: (1, 3) 연결 (edge=3)
    // 4. 비용 5: (1, 2)는 이미 같은 네트워크(1-3-2)이므로 스킵 (Cycle 방지)
    // 5. 비용 6: (3, 4) 연결 (edge=4)
    // 6. 비용 7: (2, 4)는 스킵
    // 7. 비용 8: (4, 6) 연결 (edge=5) -> 간선 5개 달성. Early Exit!
    // 최소 건설 비용 합: 2 + 3 + 4 + 6 + 8 = 23

    int result = solution(n, costs);

    cout << "========================================" << endl;
    cout << "[최소 네트워크 구축 비용] : " << result << " (기대값: 23)" << endl;
    cout << "========================================" << endl;

    return 0;
}