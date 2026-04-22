/*
 * [프로그래머스 42586] 기능개발 (Lv.2)
 * - 훈련 날짜: 2026-04-22 (수)
 * - 알고리즘: 스택/큐 (Queue)
 * - 목적: 작업 완료 일수 계산 및 순차적 배포 로직 구현
 * - 엔진 실무 최적화
 * 1. 부동소수점( double ) 연산을 피하교 모듈로( % ) 연산을 통한 정수형 기반 올림처리로 CPU 오버헤드 방지
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    vector<int> solution(vector<int> progresses, vector<int> speeds) {
        vector<int> answer;

        queue<int> q;

        for (int i = 0; i < progresses.size(); i++)
        {
            int days = 
                ((100 - progresses[i]) % speeds[i] == 0 ? 
                    (100 - progresses[i]) / speeds[i] : (100 - progresses[i]) / speeds[i] + 1);
            q.push(days);
        }

        while (!q.empty())
        {
            int day = q.front(); q.pop();
            int cnt = 1;

            while (!q.empty() && day >= q.front())
            {
                q.pop();
                cnt++;
            }

            answer.push_back(cnt);
        }

        return answer;
    }
};
// =========================================================================


// =========================================================================
// [로컬 테스트 드라이버 구역]
// =========================================================================
int main() {
    Solution sol;

    vector<int> p1 = { 93, 30, 55 };
    vector<int> s1 = { 1, 30, 5 };
    vector<int> p2 = { 95, 90, 99, 99, 80, 99 };
    vector<int> s2 = { 1, 1, 1, 1, 1, 1 };

    vector<int> res1 = sol.solution(p1, s1);
    vector<int> res2 = sol.solution(p2, s2);

    cout << "[테스트 1] 실행 결과: ";
    for (int n : res1) cout << n << " ";
    cout << " / 기대 결과: 2 1\n";

    cout << "[테스트 2] 실행 결과: ";
    for (int n : res2) cout << n << " ";
    cout << " / 기대 결과: 1 3 2\n";

    return 0;
}