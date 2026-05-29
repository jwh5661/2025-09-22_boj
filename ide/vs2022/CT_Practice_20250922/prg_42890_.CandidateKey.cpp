/*
 * [프로그래머스 42890] 후보키 (Lv.2)
 * - 훈련 날짜: 2026-05-29 (금)
 * - 알고리즘: Bitmasking (비트마스킹), Set (해시셋)
 * - 목적: 다중 컬럼의 선택 상태를 하나의 정수(Bit)로 압축하여, 조합의 유일성(Uniqueness)과 최소성(Minimality)을 검증함.
 * - 엔진 실무 최적화:
 * 1. State Compression : 최대 8개의 속성 선택 여부를 `bool array` 대신 `1` ~ `(1<<8)-1` 범위의
 단일 정수형 비트마스크로 압축하여 메모리 복사 부하를 원천 차단함.
 * 2. Bitwise Minimality Check : 새로운 부분집합이 기존 정답을 덮어쓰고 있는지 확인하기 위해,
 반복문이나 교집합 컨테이너를 쓰지 않고 `(기존키 & 새로운키) == 기존키`라는 단일 비트 연산 공식으로 
 CPU 사이클을 극단적으로 최적화함.
 */

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    int solution(vector<vector<string>> relation) {
        int answer = 0;

        int row = (int)relation.size();
        int col = (int)relation[0].size();
        vector<int> keys;
        keys.reserve(col);

        for (int i = 1; i < (1 << col); i++)
        {
            set<string> s;

            for (int j = 0; j < row; j++)
            {
                string str = "";

                for (int k = 0; k < col; k++)
                {
                    if ((i & (1 << k)))
                        str += relation[j][k];
                }

                s.insert(str);
            }

            if ((int)s.size() != row) continue;

            bool CanKey = true;

            for (int j = 0; j < keys.size(); j++)
            {

                if ((keys[j] & i) == keys[j])
                {
                    CanKey = false;
                    break;
                }
            }

            if (CanKey)
            {
                keys.push_back(i);
                answer++;
            }
        }

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    vector<vector<string>> relation = {
        {"100","ryan","music","2"},
        {"200","apeach","math","2"},
        {"300","tube","computer","3"},
        {"400","con","computer","4"},
        {"500","muzi","music","3"},
        {"600","apeach","music","2"}
    };
    // 기대 결과: 2 (이름+전공, 전공+학년)

    cout << "[테스트 1] 실행 결과: " << sol.solution(relation) << " / 기대 결과: 2\n";

    return 0;
}