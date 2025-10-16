/*
BOJ 3015 — 오아시스 재결합 (Oasis Reunion)
Topic: Monotonic Stack | Stack | Counting
Folder: stack/monotonic

⏱ 시간복잡도: O(N)        // 각 원소가 스택에 들어갔다가 최대 한 번만 나온다
💾 공간복잡도: O(N)

📌 핵심 아이디어
- 스택에는 (키, 동일 키 연속 개수) 쌍을 보관하는 **단조 감소 스택**을 유지.
- 새 키 h 처리:
 1) 스택 top의 키 < h: 작은 키 그룹은 h와 모두 서로 보이므로 `ans += top.count` 후 pop 반복.
 2) 스택 top의 키 == h: 같은 키 그룹 `top.count` 만큼 `ans += top.count`, 그리고 그룹 병합(`group += top.count`) 후 pop.
 3) 위 처리 후 스택이 비어있지 않다면, 바로 왼쪽의 더 큰 키 하나와는 서로 보이므로 `ans += 1`.
 4) (h, group)을 push.

⚠️ 주의할 점
- 정답 범위가 커질 수 있으므로 `Long Long` 사용.
- **초기값을 0으로** 시작해야 함(`n-1`로 시작하면 과대/과소 가능).
- 같은 키 처리에서 반드시 "가산 후 병합(pop)" 순서를 지켜야 함.

✔️ 지문 힌트
- "서로 볼 수 있다"는 중간에 자신보다 큰 사람이 없다는 뜻 -> **단조 감소 스택**으로 좌측 시야를 선형 시간에 계산 가능.

*/

// 2025-10-16 ORIGINAL

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	long long n;
	cin >> n;
	long long cnt = 0;

	vector<long long> height(n, 0);

	for (int i = 0; i < n; i++)
		cin >> height[i];

	stack<pair<long long, long long>> stk;
	stk.emplace(height[0], 1);

	for (int i = 1; i < n; i++)
	{
		while (!stk.empty() && stk.top().first < height[i])
		{
			cnt += stk.top().second;
			stk.pop();
		}

		long long cur_cnt = 1;
		if (!stk.empty() && stk.top().first == height[i])
		{
			cnt += stk.top().second;
			cur_cnt += stk.top().second;
			stk.pop();
		}
		if (!stk.empty()) cnt++;
		stk.emplace(height[i], cur_cnt);
	}

	cout << cnt << '\n';
}