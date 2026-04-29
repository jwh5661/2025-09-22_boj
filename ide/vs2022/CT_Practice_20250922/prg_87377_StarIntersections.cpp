/*
 * [프로그래머스 87377] 교점에 별 만들기 (Lv.2)
 * - 훈련 날짜: 2026-04-29 (수)
 * - 알고리즘: 게임 수학 (좌표 기하학) & 좌표계 변환
 * - 목적: 직선의 교점 공식을 통해 정수 좌표를 추출하고, 이를 2D 배열(화면 좌표계)로 변환하여 렌더링
 * - 엔진 실무 최적화:
 * 1. 교점 공식 연산 중 발생할 수 있는 자료형 오버플로우를 선제적으로 방지하기 위해 64비트 정수형 캐스팅 적용.
 * 2. 수학적 월드 좌표계( Y축 상단 증가 )를 스크린 버퍼 좌표계( Y축 하단 증가 )로 변환하는 
 Y축 반전( maxY - y ) 및 오프셋( x - minX ) 로직을 통해 
 그래픽스 렌더링 파이프라인의 Viewport Transform 원리 구현.
 */

#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    vector<string> solution(vector<vector<int>> line) {
        vector<pair<long long, long long>> stars;
        long long minX = LLONG_MAX, minY = LLONG_MAX, maxX = LLONG_MIN, maxY = LLONG_MIN;
        
        for (int i = 0; i < line.size(); i++)
        {
            long long curA = line[i][0];
            long long curB = line[i][1];
            long long curE = line[i][2];

            for (int j = i + 1; j < line.size(); j++)
            {
                long long curC = line[j][0];
                long long curD = line[j][1];
                long long curF = line[j][2];

                if (curA * curD - curB * curC == 0) continue;
                if ((curB * curF - curE * curD) % (curA * curD - curB * curC) != 0) continue;
                if ((curE * curC - curA * curF) % (curA * curD - curB * curC) != 0) continue;

                long long valX = (curB * curF - curE * curD) / (curA * curD - curB * curC);
                long long valY = (curE * curC - curA * curF) / (curA * curD - curB * curC);
                minX = min(minX, valX);
                minY = min(minY, valY);
                maxX = max(maxX, valX);
                maxY = max(maxY, valY);

                stars.emplace_back(valY, valX);
            }
        }

        vector<string> answer(maxY - minY + 1, string(maxX - minX + 1, '.'));

        for (const auto coord : stars)
            answer[maxY - coord.first][coord.second - minX] = '*';
            
        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;
    vector<vector<int>> line1 = { {2, -1, 4}, {-2, -1, 4}, {0, -1, 1}, {5, -8, -12}, {5, 8, 12} };
    // 기대 결과:
    // "....*...."
    // "........."
    // "........."
    // "*.......*"
    // "........."
    // "........."
    // "........."
    // "........."
    // "*.......*"

    vector<string> res1 = sol.solution(line1);
    cout << "[테스트 1] 실행 결과:" << endl;
    for (const string& s : res1) cout << s << endl;

    return 0;
}