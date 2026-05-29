/*
 * [프로그래머스 67258] 보석 쇼핑 (Lv.3)
 * - 훈련 날짜: 2026-05-29 (금)
 * - 알고리즘: Two Pointers (투 포인터), Sliding Window, Hash Map
 * - 목적: O(N)의 선형 시간 안에 조건을 만족하는 가장 짧은 구간(Window) 탐색
 * - 엔진 실무 최적화:
 * 1. State Machine Architecture : '수축( Shrink )', '확장( Expand )', '종료( Break )' 라는
 3가지 명확한 상태로 분기를 서계하여 포인터 연산의 데드락과 무한 루프를 원천 차단함.
 * 2. Optimal Update Timing : 조건을 만족한다고 매번 정답을 갱신하는 것이 아니라,
 'um[gems[left]] == 1'이 되어 '더 이상 윈도우를 줄일 수 없는 임계점'에 도달했을 때만 정답을 갱신하여
 Memory Write 부하를 최소화함.
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    vector<int> solution(vector<string> gems) {
        vector<int> answer = { 1, (int)gems.size() };

        unordered_map<string, int> um;
        set<string> s;
        for (const string& str : gems)
            s.insert(str);
        int left = 0, right = 0, cnt = 0, mx_cnt = (int)s.size(), min_size = 100001;

        while (true)
        {
            if (cnt == mx_cnt)
            {
                if (um[gems[left]] > 1)
                    um[gems[left]]--;
                else
                {
                    if (min_size > right - left)
                    {
                        answer[0] = left + 1;
                        answer[1] = right;
                        min_size = right - left;
                    }

                    um.erase(gems[left]);
                    cnt--;
                }

                left++;
            }
            else if (right < (int)gems.size())
            {
                if (um.find(gems[right]) == um.end())
                {
                    cnt++;
                    um.insert({ gems[right], 1 });
                }
                else
                    um[gems[right]]++;

                right++;
            }
            else
                break;
        }

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    vector<string> gems = { "DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA" };
    // 기대 결과: {3, 7}

    vector<int> result = sol.solution(gems);
    cout << "[테스트 1] 실행 결과: {" << result[0] << ", " << result[1] << "} / 기대 결과: {3, 7}\n";

    return 0;
}