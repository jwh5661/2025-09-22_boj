/*
BOJ 6198 — 옥상 정원 꾸미기 (Rooftop Garden)
Topic: Monotonic Stack | Stack | Greedy
Folder: stack/monotonic

⏱ 시간복잡도: O(N)    // 각 빌딩은 최대 1번 push/pop
💾 공간복잡도: O(N)

📌 핵심 아이디어
- 왼->오 순회하면서 **단조 감소 스택**(높이 내림차순)을 유지.
- 현재 높이 h 처리:
 - while (!stk.empty() && stk.top() <= h) stk.pop();	// 자신보다 낮거나 같은 건물은 시야를 막으므로 제거
 - 정답 += stk.size();	// 스택에 남은 건물들은 모두 h보다 높아 h를 볼 수 없음
 - stk.push(h);

⚠️ 주의할 점
- **같은 높이도** 시야를 막음 -> 비교는 `<`가 아니라 `<=`.
- 정답은 최대 O(N^2)까지 커질 수 있어 **Long Long** 사용.
- 스택에는 **높이만** 저장해도 충분(인덱스 불필요).

✔️ 지문 힌트
- "왼쪽에 보이는 건물 수"를 각 빌딩마다 더하면 전체 쌍 수가 됨.
- 단조 스택으로 "나보다 낮거나 같은" 건물을 정리하고, 남은 스택 크기가 곧 보이는 개수.

*/

// 2025-10-16 ORIGINAL

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	long long cnt = 0;
	cin >> n;

	vector<int> build(n);

	for (int i = 0; i < n; i++)
		cin >> build[i];

	stack<int> stk;
	for (int i = 0; i < n; i++)
	{
		while (!stk.empty() && stk.top() <= build[i]) stk.pop();
		cnt += static_cast<long long>(stk.size());
		stk.push(build[i]);
	}

	cout << cnt << '\n';
}