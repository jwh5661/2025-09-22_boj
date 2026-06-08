/*
 * [프로그래머스 60057] 문자열 압축 (Lv.2)
 * - 훈련 날짜: 2026-06-08 (월)
 * - 알고리즘: String Parsing (문자열 파싱), Brute-Force (완전 탐색)
 * - 목적: 특정 단위 가중치에 따른 문자열 청크 분할 및 압축률 최적화
 * - 엔진 실무 최적화:
 * 1. Half-Length Pruning : 압축이 성립할 수 있는 최대 단위 길이를 전체 문자열의 절반( N/2 )로 제한하여
 불필요한 고길이 탐색 연산을 50% 제거함.
 * 2. Mathmatical Tail Alignment : 정수 나눗셈의 특성을 활용한 'n / i * i' 수식을 통해,
 덩어리로 나누어떨어지지 않고 남은 잔여 문자열의 시작 주소를 완전 무결하게 찾아내어 바인딩함.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역] 
// =========================================================================
int solution(string s) {
    int answer = s.length();
    int n = answer;

    for (int i = 1; i <= n / 2; i++)
    {
        string unit = s.substr(0, i);
        string answerStr = "";
        int cnt = 1;

        for (int j = i; j <= n - i; j += i)
        {
            if (unit == s.substr(j, i))
            {
                cnt++;
                continue;
            }
            else if (cnt > 1)
            {
                answerStr += to_string(cnt) + unit;
                cnt = 1;
            }
            else
                answerStr += unit;

            unit = s.substr(j, i);
        }

        if(cnt > 1)
            answerStr += to_string(cnt) + unit;
        else
            answerStr += unit;

        for (int j = n / i * i; j < n; j++)
            answerStr += s[j];

        answer = min(answer, (int)answerStr.size());
    }

    return answer;
}
// =========================================================================

int main() {
    // 테스트 케이스
    string s1 = "aabbaccc";
    int expected1 = 7;

    string s2 = "ababcdcdababcdcd";
    int expected2 = 9;

    string s3 = "abcabcdede";
    int expected3 = 8;

    string s4 = "abcabcabcabcdededededede";
    int expected4 = 14;

    cout << "========================================" << endl;

    int result1 = solution(s1);
    cout << "[테스트 1] " << (result1 == expected1 ? "PASS" : "FAIL") << " | 기대값: " << expected1 << ", 실행값: " << result1 << endl;

    int result2 = solution(s2);
    cout << "[테스트 2] " << (result2 == expected2 ? "PASS" : "FAIL") << " | 기대값: " << expected2 << ", 실행값: " << result2 << endl;

    int result3 = solution(s3);
    cout << "[테스트 3] " << (result3 == expected3 ? "PASS" : "FAIL") << " | 기대값: " << expected3 << ", 실행값: " << result3 << endl;

    int result4 = solution(s4);
    cout << "[테스트 4] " << (result4 == expected4 ? "PASS" : "FAIL") << " | 기대값: " << expected4 << ", 실행값: " << result4 << endl;

    cout << "========================================" << endl;

    return 0;
}