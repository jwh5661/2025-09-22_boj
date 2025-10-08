/*
BOJ 2346 — 풍선 터뜨리기 (Balloon Popping)
Topic: Deque | Simulation | Rotation
Folder: deque/rotation

⏱ 시간복잡도: O(N + K)      // N개 풍선, 회전 총합 K (모듈로 최적화 시 평균 감소)
💾 공간복잡도: O(N)

📌 핵심 아이디어
- 덱에 (풍선번호, 이동값)을 넣고, 매 단계:
  1) front를 꺼내 출력
  2) 이동값 k에 따라 덱을 회전
	 - k > 0 → 이미 하나 꺼냈으므로 **k-1칸** 왼쪽 회전(pop_front→push_back)
	 - k < 0 → **|k|칸** 오른쪽 회전(pop_back→push_front)
- 덱에 하나 남으면 마지막 번호 출력.

⚠️ 주의할 점
- 회전 횟수는 `steps = abs(k) % size`로 줄이면 비효율을 방지.
- `k > 0`일 때만 `k-1`인 이유: 현재 풍선을 이미 제거하며 한 칸 진행된 효과가 있기 때문.
- 덱이 비기 직전 `size()`를 기준으로 모듈러를 계산해야 함.

✔️ 지문 힌트
- 임의 지점 erase 필요 없음. **양끝 회전(pop/push)** 만으로 충분하고 더 효율적.
*/

// 2025-10-08 ORIGINAL

#include <iostream>
#include <deque>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	deque<pair<int, int>> dq;

	for (int i = 1; i <= n; i++)
	{
		int val;
		cin >> val;
		dq.push_back(make_pair(i, val));
	}

	while (dq.size() > 1)
	{
		auto cur = dq.front(); dq.pop_front();
		cout << cur.first << ' ';
		int cur_val = cur.second;
		if (cur_val < 0)
		{
			while (cur_val++)
			{
				dq.push_front(dq.back());
				dq.pop_back();
			}
		}
		else
		{
			cur_val -= 1;
			while (cur_val--)
			{
				dq.push_back(dq.front());
				dq.pop_front();
			}
		}
	}
	cout << dq.front().first << '\n';
}