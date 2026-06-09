/*
 * [프로그래머스 67257] 수식 최대화 (Lv.2)
 * - 훈련 날짜: 2026-06-08 ~ 06-09
 * - 알고리즘: String Parsing, Brute-Force, Permutation
 * - 목적: 문자열 수식을 숫자와 연산자로 토큰화(Tokenization)하고, 주어진 우선순위 조합에 따라 배열을 동적으로 축소(Reduction)하여 최댓값 도출
 * - 엔진 실무 최적화:
 * 1. Safe Index Control on Deletion : vector.erase() 발생 시 뒤의 원소가 앞으로 당겨지는 특성을 고려하여,
 연산이 발생한 턴에는 인덱스를 전지시키지 않는 능동적 포인터 제어 구현.
 * 2. Permutation with do-while : 백트래킹( DFS )으로 경우의 수를 직접 구현하지 않고, 
 C++ 표준 라이브러리인 std::next_permutation을 do-while 루프와 결합하여 O(1) 수준의 상태 전이 코드로 최적화함.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역] 
// =========================================================================
long long solution(string expression) {
    long long answer = 0;

    vector<long long> num;
    num.reserve((int)expression.size());

    vector<char> op;
    op.reserve((int)expression.size());

    vector<char> priority = { '*', '+', '-' };
    sort(priority.begin(), priority.end());

    string curNum = "";

    for (char c : expression)
    {
        if (isdigit(c))
            curNum += c;
        else
        {
            num.push_back(stoll(curNum));
            curNum = "";
            op.push_back(c);
        }
    }

    num.push_back(stoll(curNum));

    do {
        vector<long long> tempNum = num;
        vector<char> tempOp = op;

        for (char curOp : priority)
        {
            for (int i = 0; i < (int)tempOp.size();)
            {
                if (tempOp[i] == curOp)
                {
                    long long result = 0;
                    if (curOp == '*') result = tempNum[i] * tempNum[i + 1];
                    else if (curOp == '+') result = tempNum[i] + tempNum[i + 1];
                    else if (curOp == '-') result = tempNum[i] - tempNum[i + 1];

                    tempNum[i] = result;;
                    tempNum.erase(tempNum.begin() + i + 1);
                    tempOp.erase(tempOp.begin() + i);
                }
                else
                    i++;
            }
        }

        answer = max(answer, abs(tempNum[0]));

    } while (next_permutation(priority.begin(), priority.end()));

    return answer;
}
// =========================================================================

int main() {
    // 테스트 케이스
    string exp1 = "100-200*300-500+20";
    long long expected1 = 60420;

    string exp2 = "50*6-3*2";
    long long expected2 = 300;

    cout << "========================================" << endl;

    long long result1 = solution(exp1);
    cout << "[테스트 1] " << (result1 == expected1 ? "PASS" : "FAIL") << " | 기대값: " << expected1 << ", 실행값: " << result1 << endl;

    long long result2 = solution(exp2);
    cout << "[테스트 2] " << (result2 == expected2 ? "PASS" : "FAIL") << " | 기대값: " << expected2 << ", 실행값: " << result2 << endl;

    cout << "========================================" << endl;

    return 0;
}