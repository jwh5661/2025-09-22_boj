/*
BOJ 11003 — 최솟값 찾기 (Sliding Window Minimum)
주제: Deque | Monotonic Queue | Sliding Window
폴더: deque/monoqueue

⏱ 시간복잡도: O(N)
💾 공간복잡도: O(N)

📌 핵심 아이디어
- 인덱스를 저장하는 **단조 증가 데크** 유지:
	- 앞쪽: 윈도우 밖(`dq.front() <= i - l`)이면 pop_front().
	- 뒤쪽: 현재 값 이상은 앞으로 최소가 될 수 없으니 pop_back().
	- 매 단계의 최소는 `num[dq.front()]`.

⚠️ 주의할 점
- 인덱스 기준으로 윈도우 경계 관리: `i-l+1 ~ i` -> 체크는 `dq.front() <= i - l`.
- 매우 큰 입력임므로 I/O 최적화(이미 적용) 유지.
- 출력은 끝에 개행(`'\n'`)을 넣어 마무리.

💡 문제 힌트 (Problem Hint)
- 슬라이딩 최소/최대는 **모노토닉 데크**가 정석.
- "뒤에서 더 큰(또는 같은) 값 제거"로 각 원소는 최대 1회 push/1회 pop -> **선형시간**.

🛠 개선 사항 (Improvement)
- 지금은 즉시 출력으로 메모리 절약 OK. 필요시 버퍼링하여 한 번에 출력 가능.
- `ans` 벡터가 필요 없다면 현재 방식 유지가 가장 메모리 친화적.

*/

// 2025-10-21 ORIGINAL

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, l;
	cin >> n >> l;

	vector<int> num(n);
	for (int i = 0; i < n; i++)
		cin >> num[i];

	deque<int> dq;
	
	for (int i = 0; i < n; i++)
	{
		while (!dq.empty() && dq.front() <= i - l) dq.pop_front();
		while (!dq.empty() && num[dq.back()] > num[i]) dq.pop_back();
		dq.push_back(i);
		cout << num[dq.front()] << " ";
	}
}