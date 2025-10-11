/*
BOJ 18258 — 큐 2 (Queue 2)
Topic: Queue | Implementation | I/O
Folder: queue/basic

⏱ 시간복잡도: O(M)            // 명령 개수 M
💾 공간복잡도: O(N)            // 큐에 들어간 최대 원소 수

📌 핵심 아이디어
- 표준 큐를 사용해 명령을 그대로 시뮬레이션:
 - push X: q.push(X)
 - pop: 비어있지 않으면 front 출력 후 pop, 아니면 -1
 - empty: q.empty() ? 1 : 0
 - front/back: 비어있지 않으면 해당 값, 아니면 -1
- 대량 입출력이므로 빠른 I/O 설정(ios::sync_with_stdio(false); cin.tie(nullptr);)을 적용.

⚠️ 주의할 점
- 빈 큐에서 pop/front/back일 때 반드시 -1.
- 출력은 개행 문자('\n') 사용 (endl 금지).
- size는 정수 출력 기대 -> 필요시 static_cast<int>(q.size())로 명시.

✔️ 지문 힌트
- 큐의 전형적 연산을 그대로 구현하는 입출력 시뮬레이션 문제.
- 표준 라이브러리 std::queue<int>로 충분히 해결 가능.

*/

// 2025-10-11 ORIGINAL

#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	queue<int> q;
	while (n--)
	{
		string str;
		cin >> str;

		if (str == "push")
		{
			int val;
			cin >> val;
			q.push(val);
		}
		else if (str == "pop")
		{
			if (q.empty())
				cout << -1 << '\n';
			else
			{
				cout << q.front() << '\n';
				q.pop();
			}
		}
		else if (str == "size")
			cout << q.size() << '\n';
		else if (str == "empty")
		{
			if (q.empty())
				cout << 1 << '\n';
			else
				cout << 0 << '\n';
		}
		else if (str == "front")
		{
			if (!q.empty())
				cout << q.front() << '\n';
			else
				cout << -1 << '\n';
		}
		else if (str == "back")
		{
			if (!q.empty())
				cout << q.back() << '\n';
			else
				cout << -1 << '\n';
		}
	}
}