/*
 * [프로그래머스 43162] 네트워크 (Lv.3)
 * - 훈련 날짜: 2026-05-06 (수)
 * - 알고리즘: Union-Find (Disjoint Set, 분리 집합)
 * - 목적: 다수의 객체 간 연결 관계를 바탕으로 독립된 컴포넌트(네트워크 덩어리)의 총 개수를 산출
 * - 엔진 실무 최적화:
 * 1. FindParent 함수 내에서 `parent[x] =- FindParent(,,,)`을 통한 경로 압축으로 탐색 트리의 높이를 O(1)에 가깝게 평탄화.
 * 2. 양방향 간선의 특성을 활용하여 인접 행렬 탐색 시 `j = i + 1`부터 순회,
 불필요한 중복 Union 호출 및 자기 자신( i == j ) 검사를 제거함.
 */

#include <iostream>
#include <vector>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    vector<int> parent;

    int FindParent(int x) {
        if (x == parent[x]) return x;
        return parent[x] = FindParent(parent[x]);
    }

    void UnionParent(int a, int b) {
        a = FindParent(a);
        b = FindParent(b);
        if (a == b) return;
        parent[b] = a;
    }

    int solution(int n, vector<vector<int>> computers) {
        int answer = 0;

        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i;

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (computers[i][j] == 1)
                    UnionParent(i, j);
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (parent[i] == i)
                answer++;
        }

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    // 테스트 1
    int n1 = 3;
    vector<vector<int>> comp1 = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    // 기대 결과: 2

    // 테스트 2
    int n2 = 3;
    vector<vector<int>> comp2 = {
        {1, 1, 0},
        {1, 1, 1},
        {0, 1, 1}
    };
    // 기대 결과: 1

    cout << "[테스트 1] 실행 결과: " << sol.solution(n1, comp1) << " / 기대 결과: 2\n";
    cout << "[테스트 2] 실행 결과: " << sol.solution(n2, comp2) << " / 기대 결과: 1\n";

    return 0;
}