/*
 * [PRG_Mock_10] 청백전 시너지 밸런서 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-22 (월)
 * - 알고리즘: Backtracking (백트래킹) / Combination (조합 탐색)
 * - 목적: N명의 선수를 절반으로 나누는 모든 조합을 탐색하여 양 팀 간의 시너지 차이를 최소화
 * - 엔진 실무 최적화:
 * 1. 대칭성 제거( Symmetry Breaking ) : `visited[0] = true; DFS(1, 1);`을 통해 0번 선수를 강제로 스타트 팀에 고정.
 A팀 vs B팀과 B팀 vs A팀이라는 논리적 중복 매치업을 원천 차단하여 상태 공간을 50% 절단함.
 * 2. 시너지 O(N^2) 중복 연산 방지 : 계산 루프를 `for (j = i + 1; j < N)`으로 좁히고,
 그 안에서 `map[i][j]`와 `map[j][i]`를 한 번에 더하여 캐시 히트율을 높이고 연산량을 압축함.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

int min_diff = 1e9;
bool visited[20];
int N;

// 시너지 맵을 전역에서 쉽게 접근하기 위한 포인터나 복사본 (원하는 방식으로 구현)
vector<vector<int>> synergy_map;

void DFS(int idx, int count) {
    // 1. 기저 사례: N/2 명을 모두 뽑았을 때
    if (count == N / 2) {
        int start_team = 0;
        int link_team = 0;
        // 스타트 팀과 링크 팀의 시너지 계산 로직
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                if (visited[i] && visited[j])
                {
                    start_team += synergy_map[i][j];
                    start_team += synergy_map[j][i];
                }
                else if(!visited[i] && !visited[j])
                {
                    link_team += synergy_map[i][j];
                    link_team += synergy_map[j][i];
                }
            }
        }

        // min_diff 갱신
        min_diff = min(min_diff, abs(start_team - link_team));
        
        return;
    }

    // 2. 재귀 호출: 백트래킹 뼈대 이식
    for (int i = idx; i < N; i++)
    {
        visited[i] = true;
        DFS(i + 1, count + 1);
        visited[i] = false;
    }
}

int solution(vector<vector<int>> synergy) {
    N = synergy.size();
    synergy_map = synergy;
    min_diff = 1e9;
    fill(visited, visited + 20, false);

    // 3. 엔진 점화 (0번 선수를 고정하는 극한의 가지치기 적용 권장)
    visited[0] = true;
    DFS(1, 1);

    return min_diff;
}
// =========================================================================

int main() {
    // 4명의 선수 시너지 데이터
    vector<vector<int>> synergy = {
        {0, 1, 2, 3},
        {4, 0, 5, 6},
        {7, 1, 0, 2},
        {3, 4, 5, 0}
    };

    // 기대 정답 분석:
    // (0, 3) 팀 vs (1, 2) 팀 구성 시:
    // 스타트(0, 3): S[0][3] + S[3][0] = 3 + 3 = 6
    // 링크(1, 2): S[1][2] + S[2][1] = 5 + 1 = 6
    // 차이 = |6 - 6| = 0 (최적!)

    int result = solution(synergy);

    cout << "========================================" << endl;
    cout << "[두 팀의 최소 전투력 차이] : " << result << " (기대값: 0)" << endl;
    cout << "========================================" << endl;

    return 0;
}