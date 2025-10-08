/*
BOJ 2164 — 카드2 (Card 2)
Topic: Queue | Simulation
Folder: queue/basic

⏱ 시간복잡도: O(N)
💾 공간복잡도: O(N)

📌 핵심 아이디어
- 1..N을 큐에 넣고, "맨 위 버리기 -> 다음 카드 맨 아래로 보낵"를 큐 연산으로 시뮬레이션
- 큐에 카드가 하나만 남을 때 까지 반복, 마지막 원소를 출력.

⚠️ 주의할 점
- 루프 조건은 `q.size() > 1`, 순서: `pop()` -> `push(front)` -> `pop()`.
- I/O 최적화와 개행 출력 유지.

✔️ 지문 힌트
- 큐의 FIFO 특성이 동작을 그대로 모델링하므로 추가 자료구조가 필요 없다.
- 수학적 관찰(가장 큰 2의 거듭제곱)을 사용하면 O(1) 풀이도 가능하지만, 큐 시뮬레이션이 가장 직관적이다.

*/

// 2025-10-08 ORIGINAL

#include <iostream>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	queue<int> q;
	for (int i = 1; i <= n; i++) q.push(i);

	while (q.size() > 1)
	{
		q.pop();
		q.push(q.front());
		q.pop();
	}

	cout << q.front() << '\n';
}