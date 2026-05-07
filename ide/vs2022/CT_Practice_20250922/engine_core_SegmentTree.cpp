/*
 * [엔진 코어 훈련] 실시간 구간 합계 모니터링 (세그먼트 트리 기초)
 * - 훈련 날짜: 2026-05-07 (목)
 * - 알고리즘: 세그먼트 트리 (Segment Tree)
 * - 목적: 빈번한 데이터 갱신과 구간 질의가 발생하는 환경에서 O(log N)의 성능을 보장하는 트리 템플릿 구축
 * - 엔진 실무 최적화:
 * 1. 1차원 배열( vector )의 인덱싱( node * 2, node * 2 + 1 )을 활용하여,
 포인트 기반 트리의 메모리 파편화 및 오버헤드를 완벽히 제거한 완전 이진 트리 구성.
 * 2. Query( Sum ) 함수에서 탐색 구간이 목표 구간 내에 완전히 포함될 경우,
 하위 노드 탐색을 즉시 생략( Early Return )하는 분할 정복 최적화 적용.
 */

#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
private:
    vector<long long> tree;

public:
    // 트리의 크기는 넉넉하게 배열 크기(N)의 4배로 할당합니다.
    SegmentTree(int n) {
        tree.resize(n * 4);
    }

    // 1. 트리 초기화 (Build)
    // node: 현재 트리 노드 번호 (루트는 1) / start, end: 원본 배열의 구간
    long long Init(const vector<long long>& arr, int node, int start, int end) {
        if (start == end) return tree[node] = arr[start];
        int mid = (start + end) / 2;
        // 왼쪽 자식(node*2)과 오른쪽 자식(node*2 + 1)의 합을 저장
        return tree[node] = Init(arr, node * 2, start, mid) + Init(arr, node * 2 + 1, mid + 1, end);
    }

    // 2. 특정 인덱스 데이터 갱신 (Update)
    // index: 변경할 원본 배열의 인덱스 / diff: 기존 값과의 차이(변화량)
    void Update(int node, int start, int end, int index, long long diff) {
        // 구간을 벗어나면 무시
        if (index < start || index > end) return;

        // 구간에 포함되면 내 노드 값 갱신
        tree[node] += diff;

        // 리프 노드가 아니라면 자식들도 갱신
        if (start != end) {
            int mid = (start + end) / 2;
            Update(node * 2, start, mid, index, diff);
            Update(node * 2 + 1, mid + 1, end, index, diff);
        }
    }

    // 3. 특정 구간의 합 구하기 (Query)
    // left, right: 구하고자 하는 구간
    long long Sum(int node, int start, int end, int left, int right) {
        // 팁 1: 현재 구간(start~end)이 구하려는 구간(left~right)과 전혀 안 겹치면 0 반환
        if (end < left || start > right) return 0;
        // 팁 2: 현재 구간이 구하려는 구간 안에 완전히 쏙 들어가면 tree[node] 반환
        if (left <= start && right >= end) return tree[node];
        // 팁 3: 애매하게 걸쳐있으면 반으로 쪼개서 양쪽 자식에게 다시 물어보고 더함 (재귀)
        int mid = (start + end) / 2;
        return Sum(node * 2, start, mid, left, right) + Sum(node * 2 + 1, mid + 1, end, left, right);
    }
};

// =========================================================================
class Solution {
public:
    vector<long long> solution(vector<long long> arr, vector<vector<int>> queries) {
        vector<long long> answer;
        int n = arr.size();

        SegmentTree segTree(n);
        // 트리를 최초 1회 구축합니다. (배열 인덱스는 0부터 시작)
        segTree.Init(arr, 1, 0, n - 1);

        for (const auto& q : queries) {
            int type = q[0];
            if (type == 1) { // 1번 쿼리: Update (q[1] 인덱스의 값을 q[2]로 변경)
                int index = q[1];
                long long newValue = q[2];
                long long diff = newValue - arr[index]; // 변화량 계산
                arr[index] = newValue; // 원본 배열 갱신 필수!
                segTree.Update(1, 0, n - 1, index, diff);
            }
            else if (type == 2) { // 2번 쿼리: Query (q[1]부터 q[2]까지의 구간 합 반환)
                answer.push_back(segTree.Sum(1, 0, n - 1, q[1], q[2]));
            }
        }
        return answer;
    }
};
// =========================================================================

int main() {
    Solution sol;

    vector<long long> arr = { 1, 2, 3, 4, 5 };
    // 쿼리 형식: {타입, 인자1, 인자2}
    // 타입 1: [인덱스]를 [값]으로 변경
    // 타입 2: [시작 인덱스]부터 [끝 인덱스]까지의 합
    vector<vector<int>> queries = {
        {2, 0, 4}, // 0~4 구간 합 (1+2+3+4+5 = 15)
        {1, 2, 6}, // 2번 인덱스(3)를 6으로 변경 -> 배열: {1, 2, 6, 4, 5}
        {2, 1, 3}  // 1~3 구간 합 (2+6+4 = 12)
    };
    // 기대 결과: {15, 12}

    vector<long long> res = sol.solution(arr, queries);
    cout << "[실행 결과] ";
    for (auto val : res) cout << val << " ";
    cout << "\n[기대 결과] 15 12\n";

    return 0;
}