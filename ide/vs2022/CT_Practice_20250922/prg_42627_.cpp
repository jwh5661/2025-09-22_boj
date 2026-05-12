/*
 * [프로그래머스 42627] 디스크 컨트롤러 (Lv.3)
 * - 훈련 날짜: 2026-05-12 (화)
 * - 알고리즘: 우선순위 큐 (Priority Queue), 그리디 (SJF Scheduling)
 * - 목적: 구조체/클래스의 커스텀 비교 연산자(Comparator)를 작성하여 특정 조건에 최적화된 스케줄러를 설계
 * - 엔진 실무 최적화:
 * 1. C++ priority_queue의 기본 동작인 최대 힙을 최소 힙으로 변경하는 커스텀 `cmp` 구조체 구현.
 * 2. CPU 유휴 상태 발생 시, 
 불필요한 1초 단위의 루프 대기를 생략하고 다음 작업의 요청 시간으로 즉시 점프하는 분기 처리 적용.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    struct cmp {
        bool operator()(vector<int>& a, vector<int>& b) {
            return a[1] > b[1];
        }
    };

    int solution(vector<vector<int>> jobs) {
        int answer = 0;
        int current_time = 0;
        int job_index = 0;
        int completed_jobs = 0;
        int n = (int)jobs.size();

        sort(jobs.begin(), jobs.end());

        priority_queue<vector<int>, vector<vector<int>>, cmp> pq;

        while (completed_jobs < n)
        {
            while (job_index < n && jobs[job_index][0] <= current_time)
            {
                pq.emplace(jobs[job_index]);
                job_index++;
            }

            if (!pq.empty())
            {
                auto cur = pq.top(); pq.pop();
                current_time += cur[1];
                answer += current_time - cur[0];
                completed_jobs++;
            }
            else if(job_index < n)
                current_time = jobs[job_index][0];
        }


        return answer / completed_jobs;
    }
};
// =========================================================================

int main() {
    Solution sol;

    // [요청 시점, 소요 시간]
    vector<vector<int>> jobs = { {0, 3}, {1, 9}, {2, 6} };
    // 기대 결과: 9 
    // (A: 3, C: 6, B: 9 순으로 처리 -> A 대기 3, C 대기 7, B 대기 17 -> 총합 27 / 3 = 9)

    cout << "[테스트 1] 실행 결과: " << sol.solution(jobs) << " / 기대 결과: 9\n";

    return 0;
}