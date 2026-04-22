/*
 * [프로그래머스 42576] 완주하지 못한 선수 (Lv.1)
 * - 훈련 날짜: 2026-04-21 (화)
 * - 알고리즘: 해시 (Hash)
 * - 목적: std::unordered_map을 활용한 O(1) 문자열 탐색
 * - 엔진 실무 최적화:
 * 1. range-based for loop에서 const string& 를 사용하여 불필요한 string 복사 방지
 * 2. map의 operator[ ] 기본 생성 특징을 활용하면 find( ) 없이 카운팅 가능
 * 3. 정답 발견 즉시 break를 통한 불필요한 순회 방지
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// 아래 클래스 전체와 필요한 #include 문만 프로그래머스에 복사하여 제출합니다.
// =========================================================================
class Solution {
public:
    string solution(vector<string> participant, vector<string> completion) {
        string answer = "";

        unordered_map<string, int> um;

        for (const string& com : completion)
        {
            um[com]++;
        }

        for (const string& par : participant)
        {
            if (um.find(par) != um.end() && um[par] > 0)
            {
                um[par]--;
                continue;
            }
            
            answer = par;
            break;
        }

        return answer;
    }
};
// =========================================================================


// =========================================================================
// [로컬 테스트 드라이버 구역]
// Visual Studio에서 로컬 테스트를 하기 위한 용도입니다. 
// 프로그래머스에는 제출하지 않습니다.
// =========================================================================
int main() {
    // 1. 테스트 케이스 데이터 세팅
    vector<string> participant = { "mislav", "stanko", "mislav", "ana" };
    vector<string> completion = { "stanko", "ana", "mislav" };

    // 2. Solution 객체 생성 및 함수 실행
    Solution sol;
    string result = sol.solution(participant, completion);

    // 3. 결과 출력 및 검증
    cout << "실행 결과: " << result << '\n';
    cout << "기대 결과: mislav\n";

    return 0;
}