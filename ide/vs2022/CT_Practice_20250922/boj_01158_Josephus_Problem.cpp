/*
BOJ 1158 — 요세푸스 문제 (Josephus Problem)
Topic: Queue | Simulation
Folder: queue/simulation

⏱ 시간복잡도: O(N * K)         // 매 단계 회전 K-1번
💾 공간복잡도: O(N)

📌 핵심 아이디어
- 1..N을 큐에 넣고, 매 턴마다 K-1번 front를 뒤로 보내고(front->back), K번째를 pop하여 결과에 기록.
- 큐가 빌 때까지 반복, 출력은 "<a, b, c, ...>" 형식.

⚠️ 주의할 점
- 출력 포맷: 마지막 원소 뒤에 ", " 없음, 닫는 꺽쇠와 개행 ">\n" 필요
- N=K=1 같은 극단 입력에서도 잘 동작.

✔️ 개선 여지 (선택)
- 큰 K에서 약간 빠르게: 매 턴 회전 수 r = (K-1)% q.size() 만큼만 돌리기.
- 출력이 많을 때는 문자열 버퍼에 누적해 한 번에 출력하면 I/O가 살짝 빨라질 수 있음.

*/

// 2025-10-16 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;
	cin >> n >> k;

	vector<int> num;
	num.reserve(n);
	queue<int> q;
	for (int i = 1; i <= n; i++)
		q.push(i);

	while (!q.empty())
	{
		int i = k - 1;
		while (i--)
		{
			q.push(q.front());
			q.pop();
		}
		num.push_back(q.front());
		q.pop();
	}

	cout << '<';
	for (int i = 0; i < n; i++)
		cout << num[i] << (i == n - 1 ? ">\n" : ", ");
}