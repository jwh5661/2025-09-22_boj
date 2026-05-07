/*
 * [프로그래머스 64064] 불량 사용자 (Lv.3)
 * - 훈련 날짜: 2026-05-04 (월)
 * - 알고리즘: DFS & 비트마스킹 (Bitmasking)
 * - 목적: 불리언(bool) 배열 대신 정수형 비트마스크를 활용하여 객체의 조합 상태를 최적화하고 관리
 * - 엔진 실무 최적화:
 * 1. 최대 8명의 유저 상태를 8-bit 정수 하나로 압축하여 캐시 지역성 및 연산 속도 극대화.
 * 2, 재귀 함수의 Pass-by-Value 특성을 활용하여, 
 `visited | ( 1 << i )` 형태로 상태를 전달함으로써 불필요한 롤백( Rollback ) 연산을 제거함.
 */

#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    set<int> s;

    bool IsMatch(const string& uid, const string& bid)
    {
        if (uid.size() != bid.size()) return false;

        for (int i = 0; i < uid.size(); i++)
        {
            if (bid[i] == '*') continue;
            if (uid[i] != bid[i]) return false;
        }

        return true;
    }

    void Backtrack(vector<string>& user_id, vector<string>& banned_id, int depth, int n, int visited)
    {
        if (depth == n)
        {
            s.insert(visited);
            return;
        }

        for (int i = 0; i < user_id.size(); i++)
        {
            if (visited & (1 << i)) continue;

            if (IsMatch(user_id[i], banned_id[depth]))
                Backtrack(user_id, banned_id, depth + 1, n, visited | (1<<i));
        }
    }

    int solution(vector<string> user_id, vector<string> banned_id) {
        Backtrack(user_id, banned_id, 0, (int)banned_id.size(), 0);
 
        return (int)s.size();
    }
};
// =========================================================================

int main() {
    Solution sol;
    vector<string> user = { "frodo", "crodo", "def", "dangi", "apeach" };
    vector<string> banned = { "fr*do", "c*odo" };
    // 기대 결과: 1

    cout << "[테스트 1] 실행 결과: " << sol.solution(user, banned) << "\n";

    return 0;
}