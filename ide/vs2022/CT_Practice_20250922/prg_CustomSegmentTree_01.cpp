/*
 * [PRG_Mock_01] 실시간 구간 합 갱신 시스템 (Lv.3~4 수준)
 * - 훈련 날짜: 2026-06-10 (수)
 * - 알고리즘: Segment Tree (세그먼트 트리)
 * - 목적: 동적으로 빈번하게 데이터가 갱신되는 환경에서, 특정 구간의 데이터 총합을 O(log N)의 속도로 조회하고 갱신하는 트랜잭션 시스템 구축
 * - 엔진 실무 최적화:
 * 1. Delta Update ( Diff ) : 값을 통째로 덮어쓰기 위해 O(N)으로 트리를 재구축하는 대신,
 기존 값과의 차이만 계산하여 O(log N) 깊이만큼만 더해주는 델타 갱신 기법 적용.
 * 2. 1-Based Indexing : 쿼리로 들어오는 유저 ID( 1번부터 시작 )와 배열 인덱스를 직관적으로 1:1 매칭하기 위해
 배열 크기를 N+1로 Padding하여 인덱스 연산의 오버헤드와 휴먼 에러를 원천 차단함.
 */

#include <iostream>
#include <vector>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================
vector<long long> arr;
vector<long long> tree;

long long init(int node, int start, int end)
{
    if (start == end) return tree[node] = arr[start];
    int mid = (start + end) / 2;
    return tree[node] = init(2 * node, start, mid) + init(2 * node + 1, mid + 1, end);
}

long long query(int node, int start, int end, int left, int right)
{
    int mid = (start + end) / 2;
    if (start > right || end < left) return 0;
    else if (left <= start && right >= end) return tree[node];
    else return query(2 * node, start, mid, left, right) + query(2 * node + 1, mid + 1, end, left, right);
}

void update(int node, int start, int end, int index, long long diff)
{
    if (start > index || end < index) return;
    tree[node] += diff;

    if (start != end)
    {
        int mid = (start + end) / 2;
        update(2 * node, start, mid, index, diff);
        update(2 * node + 1, mid + 1, end, index, diff);
    }
}

vector<long long> solution(int n, vector<long long> initial_scores, vector<vector<int>> queries) {
    vector<long long> answer;
    answer.reserve((int)queries.size());

    arr.clear();
    tree.clear();
    arr.resize(n + 1);

    for (int i = 0; i < n; i++)
        arr[i + 1] = initial_scores[i];
    tree.resize(n * 4);
    init(1, 1, n);

    for (const auto& q : queries)
    {
        if (q[0] == 1)
        {
            long long diff = q[2] - arr[q[1]];
            arr[q[1]] = q[2];
            update(1, 1, n, q[1], diff);
        }
        else
            answer.push_back(query(1, 1, n, q[1], q[2]));
    }


    return answer;
}
// =========================================================================

int main() {
    int n = 5;
    vector<long long> initial_scores = { 10, 20, 30, 40, 50 };

    // 쿼리 형식: {type, a, b} 
    // type 1: a번 유저의 점수를 b로 변경
    // type 2: a번부터 b번 유저까지의 점수 합 조회
    vector<vector<int>> queries = {
        {2, 1, 5},    // 1~5번 합: 10+20+30+40+50 = 150
        {1, 3, 100},  // 3번 유저 점수(30)를 100으로 변경
        {2, 2, 4},    // 2~4번 합: 20+100+40 = 160
        {1, 5, 0},    // 5번 유저 점수(50)를 0으로 변경
        {2, 1, 5}     // 1~5번 합: 10+20+100+40+0 = 170
    };

    vector<long long> result = solution(n, initial_scores, queries);

    cout << "========================================" << endl;
    for (long long ans : result) {
        cout << ans << "\n";
    }
    cout << "========================================" << endl;

    return 0;
}