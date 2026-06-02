/*
 * [프로그래머스 60059] 자물쇠와 열쇠 (Lv.3)
 * - 훈련 날짜: 2026-06-02 (화)
 * - 알고리즘: Brute-Force (완전 탐색), 2D Matrix Rotation (행렬 회전), Simulation
 * - 목적: 제한 조건 스케일이 매우 작음을 파악하고, 격자 확장 및 트랜잭션 패턴을 통해 예외 없는 완벽한 완전 탐색 구현
 * - 엔진 실무 최적화:
 * 1. Transactional State Pattern : 자물쇠 격자에 열쇠 값을 우선 더하고( `+=` ),
 정중앙 영역만 독립 검증한 뒤, 다시 빼주는( `-=` ) 구조를 취해 복잡한 경계선 분기 조건을 단 한 줄의 수식으로 압착함.
 * 2. Multi-Level Loop Break : 검증 실패 시 불필요한 연산이 지속되지 않도록 플래그 변수( `can_open` )를 활용해
 중첩된 내장 루프를 즉시 조기 탈출( `break` )하도록 설계함.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    vector<vector<int>> rotate(vector<vector<int>>& key)
    {
        int m = (int)key.size();
        vector<vector<int>> k(m, vector<int>(m, 0));

        for (int i = 0; i < key.size(); i++)
        {
            for (int j = 0; j < key.size(); j++)
                k[j][m - 1 - i] = key[i][j];
        }

        return k;
    }

    bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
        int n = (int)lock.size();
        int m = (int)key.size();
        vector<vector<int>> lock3x(3 * n, vector<int>(3 * n, 0));

        for (int i = n; i < 2 * n; i++)
        {
            for (int j = n; j < 2 * n; j++)
                lock3x[i][j] = lock[i - n][j - n];
        }

        for (int i = 0; i < 4; i++)
        {
            if (i != 0) key = rotate(key);

            for (int j = 0; j < 2 * n; j++)
            {
                for (int k = 0; k < 2 * n; k++)
                {
                    bool can_open = true;

                    for (int x = 0; x < m; x++)
                    {
                        for (int y = 0; y < m; y++)
                            lock3x[j + x][k + y] += key[x][y];
                    }

                    for (int x = n; x < 2 * n; x++)
                    {
                        for (int y = n; y < 2 * n; y++)
                        {
                            if (lock3x[x][y] == 0 || lock3x[x][y] == 2)
                            {
                                can_open = false;
                                break;
                            }
                        }

                        if (!can_open) break;
                    }

                    if (can_open) return true;

                    for (int x = 0; x < m; x++)
                    {
                        for (int y = 0; y < m; y++)
                            lock3x[j + x][k + y] -= key[x][y];
                    }
                }
            }
        }

        return false;
    }
};
// =========================================================================

int main() {
    Solution sol;

    vector<vector<int>> key = {
        {0, 0, 0},
        {1, 0, 0},
        {0, 1, 1}
    };
    vector<vector<int>> lock = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}
    };
    // 기대 결과: true (또는 1)

    cout << "[테스트 1] 실행 결과: " << sol.solution(key, lock) << " / 기대 결과: 1\n";

    return 0;
}