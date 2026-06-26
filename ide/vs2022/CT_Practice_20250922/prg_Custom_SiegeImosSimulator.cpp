/*
 * [PRG_Mock_12] 공성전 마법 폭격 시뮬레이터 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-25 (목)
 * - 알고리즘: 2D Imos Method (2차원 이모스법 / 차분 배열), 누적 합(Prefix Sum)
 * - 목적: K번의 직사각형 범위 데이터 갱신을 O(1)에 처리하고, 최종 결과를 O(N*M)에 도출
 * - 엔진 실무 최적화:
 * 1. O(1) 마킹 : 매 폭격마다 N*M 격자를 순회하지 않고, 영역의 4개 꼭짓점에만 차분 값을 기록하여 O(K)의 시간 복잡도로 로그 압축.
 * 2. 2-Way Sweep : 모든 이벤트 종료 후 가로 방향으로 1회, 세로 방향으로 1회 누적 합을 전개하여 마킹된 델타 값을 전체 맵에 퍼뜨림.
 */

#include <iostream>
#include <vector>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

const int MAX = 1005;
int diff_map[MAX][MAX];

int solution(int n, int m, vector<vector<int>> events) {
    int cnt = 0;

    // 1. diff_map 초기화 (전역 배열 재사용 대비)
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
            diff_map[i][j] = 0;
    }

    // 2. K번의 이벤트 스캔 (O(K) 마킹)
        // e[0]=r1, e[1]=c1, e[2]=r2, e[3]=c2, e[4]=degree
    for (const auto& e : events)
    {
        diff_map[e[0]][e[1]] += e[4];
        diff_map[e[0]][e[3] + 1] += -e[4];
        diff_map[e[2] + 1][e[1]] += -e[4];
        diff_map[e[2] + 1][e[3] + 1] += e[4];
    }

    // 3. 가로/세로 Sweep 점화 (O(N*M) 누적 합)
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < m; j++)
            diff_map[i][j] += diff_map[i][j - 1];
    }

    for (int j = 0; j < m; j++)
    {
        for (int i = 1; i < n; i++)
            diff_map[i][j] += diff_map[i - 1][j];
    }

    // 4. 생존 격자(내구도 1 이상) 카운트 및 반환
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (diff_map[i][j] > 0) cnt++;
        }
    }

    return cnt;
}
// =========================================================================

int main() {
    int n = 4; // 세로 4
    int m = 5; // 가로 5

    // {r1, c1, r2, c2, degree} (1-based index 기준이라 가정, 0-based라면 그에 맞게 처리)
    vector<vector<int>> events = {
        {0, 0, 2, 2, 2},   // (0,0)~(2,2)에 내구도 +2 결계
        {1, 1, 3, 3, -1},  // (1,1)~(3,3)에 내구도 -1 폭격
        {2, 2, 3, 4, 1}    // (2,2)~(3,4)에 내구도 +1 결계
    };

    int result = solution(n, m, events);

    cout << "========================================" << endl;
    cout << "[파괴되지 않은 안전한 격자의 수] : " << result << endl;
    cout << "========================================" << endl;

    return 0;
}