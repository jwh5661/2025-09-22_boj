/*
 * [PRG_Mock_02] 실시간 접두사 필터링 시스템 (Lv.3~4 수준)
 * - 훈련 날짜: 2026-06-12 (금) (Week 1 목요일 커리큘럼 보충)
 * - 알고리즘: Trie (Prefix Tree, 접두사 트리)
 * - 목적: 다량의 문자열 사전을 구축하고, 실시간 질의에 대해 특정 접두사를 공유하는 단어의 개수를 O(L)의 속도로 즉각 반환하는 인프라 설계
 * - 엔진 실무 최적화:
 * 1. O(1) Indexing Branch : 문자열의 각 알파벳을 `c - 'a'` 연산을 통해 0~25의 고정된 배열 인덱스로 치환,
 해시 함수나 문자열 비교 없이 메모리 주소를 직접 참조하여 분기함.
 * 2. Caching on Path : 리프 노드까지 도달한 뒤 단어 개수를 세는 것이 아니라,
 `insert` 단계에서 경로를 지나갈 때마다 `cnt`를 미리 누적해 두어 탐색 시간을 극단적으로 단축시킴.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

struct TrieNode {
    TrieNode* child[26] = { nullptr };
    int cnt = 0;
};

TrieNode* root;

void insert(const string& word)
{
    TrieNode* cur = root;

    for (char c : word)
    {
        if (cur->child[c - 'a'] == nullptr)
            cur->child[c - 'a'] = new TrieNode();

        cur = cur->child[c - 'a'];
        cur->cnt++;
    }
}

int countPrefix(const string& prefix)
{
    TrieNode* cur = root;

    for (char c : prefix)
    {
        if (cur->child[c - 'a'] == nullptr)
            return 0;

        cur = cur->child[c - 'a'];
    }

    return cur->cnt;
}

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    answer.reserve(queries.size());

    root = new TrieNode();

    for (const auto& w : words)
        insert(w);

    for (const auto& q : queries)
        answer.push_back(countPrefix(q));

    return answer;
}
// =========================================================================

int main() {
    // 테스트 케이스: 서버에 등록된 단어 사전 (N)
    vector<string> words = { "frodo", "front", "frost", "frozen", "frame", "kakao" };

    // 테스트 케이스: 유저들의 실시간 검색 질의 (M)
    vector<string> queries = { "fro", "fra", "pro", "ka" };

    // 기대 정답 분석:
    // "fro" -> frodo, front, frost, frozen (4개)
    // "fra" -> frame (1개)
    // "pro" -> 일치하는 단어 없음 (0개)
    // "ka" -> kakao (1개)

    vector<int> result = solution(words, queries);

    cout << "========================================" << endl;
    cout << "[검색 결과] ";
    for (int ans : result) {
        cout << ans << " ";
    }
    cout << "\n========================================" << endl;

    return 0;
}

