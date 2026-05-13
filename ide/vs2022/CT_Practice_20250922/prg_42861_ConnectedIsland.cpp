/*
 * [프로그래머스 42861] 섬 연결하기 (Lv.3)
 * - 훈련 날짜: 2026-04-28 (화)
 * - 알고리즘: 그래프 (MST - Kruskal & Union-Find)
 * - 목적: N개의 섬을 무방향 그래프로 연결할 때, 모든 섬이 통행 가능하도록 만드는 최소 비용 산출
 * - 엔진 실무 최적화:
 * 1. 간선 비용 기준으로 오름차순 정렬 후, 
 Union-Find 알고리즘을 통해 사이클 발생을 완벽하게 차단하며 최소 신장 트리( MST ) 구성.
 * 2. C++ 클래스 멤버 함수를 std::sort의 비교 함수( cmp )로 사용할 때 발생하는 
 숨겨진 'this' 포인터 타입 충돌 문제를 인지하고, 람다 캡처를 활용하여 모던 C++ 스타일로 안전하게 해결.
 * 3. Union-Find의 Find 함수에 경로 압축( Path Compression ) 기법을 적용하여 
 탐색 시간 복잡도를 O(1)에 가깜게 최적화.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    int parent[101];

    int findParent(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findParent(parent[node]);
    }

    bool unionParent(int node1, int node2) {
        node1 = findParent(node1);
        node2 = findParent(node2);
        if (node1 == node2) return false;
        parent[node2] = node1;
        return true;
    }

    int solution(int n, vector<vector<int>> costs) {
        int answer = 0;

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        sort(costs.begin(), costs.end(), [](const vector<int>& a, const vector<int>& b)
            {
                return a[2] < b[2];
            }
        );

        int picked = 0;
        for (int i = 0; i < costs.size(); i++)
        {
            if (unionParent(costs[i][0], costs[i][1]))
            {
                answer += costs[i][2];
                picked++;
                if (picked == n - 1) break;
            }
        }

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    int n1 = 4;
    vector<vector<int>> c1 = { {0, 1, 1}, {0, 2, 2}, {1, 2, 5}, {1, 3, 1}, {2, 3, 8} };
    // 기대 결과: 4

    cout << "[테스트 1] 실행 결과: " << sol.solution(n1, c1) << " / 기대 결과: 4\n";

    return 0;
}