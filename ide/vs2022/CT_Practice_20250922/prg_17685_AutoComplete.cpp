/*
 * [프로그래머스 17685] [3차] 자동완성 (Lv.3)
 * - 훈련 날짜: 2026-05-27 (수)
 * - 알고리즘: Trie (트라이), String Search Optimization
 * - 목적: 다중 문자열 검색 시 중복 접두사(Prefix)를 압축하여, 단어 식별에 필요한 최소 타이핑 횟수 산출
 * - 엔진 실무 최적화:
 * 1. Prefix Frequency Caching : 각 노드에 `cnt` 변수를 두어 해당 경로를 통과한 문자열의 개수를 캐싱함.
 이를 통해 하위 트리를 전부 탐색하지 않고도 `cnt == 1`인 시점에서 O(1)로 탐색을 조기 종료함.
 * 2. Memory Offset Indexing : 노드 내부에 문자를 직접 저장하지 않고, 
 `w[i] - 'a'`라는 알파벳 오프셋 연산을 통해 자식 배열의 인덱스 자체를 문자로 활용하여 메모리를 절약함.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// =========================================================================
// [프로그래머스 제출 구역] 
// =========================================================================
class Solution {
public:
    struct Node {
        Node* child[26];
        int cnt = 1;
    };

    int solution(vector<string> words) {
        int answer = 0;

        Node* root = new Node();

        for (const auto& w : words)
        {
            Node* cur = root;
            for (int i = 0; i < w.size(); i++)
            {
                if (cur->child[w[i] - 'a'] == nullptr)
                    cur->child[w[i] - 'a'] = new Node();
                else
                    cur->child[w[i] - 'a']->cnt++;

                cur = cur->child[w[i] - 'a'];
            }
        }

        for (const auto& w : words)
        {
            Node* cur = root;
            for (int i = 0; i < w.size(); i++)
            {
                cur = cur->child[w[i] - 'a'];
                answer++;

                if (cur->cnt == 1)
                    break;
            }
        }

        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    vector<string> words = { "go", "gone", "guild" };
    // 기대 결과: 7 
    // ("go" -> 'g', 'o' 입력 (2) / "gone" -> 'g', 'o', 'n' 입력 (3) / "guild" -> 'g', 'u' 입력 (2))

    cout << "[테스트 1] 실행 결과: " << sol.solution(words) << " / 기대 결과: 7\n";

    return 0;
}