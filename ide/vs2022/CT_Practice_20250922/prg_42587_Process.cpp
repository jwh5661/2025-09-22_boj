/*
 * [프로그래머스 42587] 프로세스 (Lv.2)
 * - 훈련 날짜: 2026-04-22 (수)
 * - 알고리즘: 스택/큐 (Queue, Priority Queue)
 * - 목적: 우선순위에 따른 프로세스 스케줄링(순환) 구현
 * - 엔진 실무 최적화 :
 * 1. queue와 priority_queue의 투 트랙( Two-track ) 운용을 통해 우선순위 검증 시간을 단축함.
 * 2. std::pair 삽입 시 push 대신 emplace를 활용하여 임시 객체 생성 및 복사 오버헤드 방지.
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
    int solution(vector<int> priorities, int location) {
        int answer = 0;

        queue<pair<int, int>> q;
        priority_queue<int> pq;

        for (int i = 0; i < priorities.size(); i++)
        {
            q.emplace(priorities[i], i);
            pq.push(priorities[i]);
        }

        while (!q.empty())
        {
            auto cur = q.front(); q.pop();

            if (cur.first == pq.top())
            {
                answer++;
                pq.pop();
                if (cur.second == location)
                    break;
            }
            else
                q.emplace(cur);
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

    vector<int> p1 = { 2, 1, 3, 2 };
    int l1 = 2;

    vector<int> p2 = { 1, 1, 9, 1, 1, 1 };
    int l2 = 0;

    cout << "[테스트 1] 실행 결과: " << sol.solution(p1, l1) << " / 기대 결과: 1\n";
    cout << "[테스트 2] 실행 결과: " << sol.solution(p2, l2) << " / 기대 결과: 5\n";

    return 0;
}