/*
BOJ 15828 — Router
Topic: Queue | Simulation
Folder: queue/simulation

⏱ 시간복잡도: O(M)    // 입력 개수 M
💾 공간복잡도: O(N)    // 버퍼 용량

📌 핵심 아이디어
- 고정 크기 버퍼 시뮬레이션: 양수 입력은 버퍼가 가득 차지 않았을 때만 push, 0이면 비어있지 않을 때 pop, -1이면 입력 종료.
- 종료 후 큐가 비었으면 "empty", 아니면 front->back 공백 구분 출력.

⚠️ 주의할 점
- size == N일 때의 양수 입력은 **드롭** (무시).
- 빈 큐에서 0이 들어오면 **무시**되어야 한다.
- 입력은 무한 길이일 수 있으므로 `while (cin >> x && x != -1)` 패턴이 안전.

✔️ 지문 힌트
- "고정 길이 큐 + 드롭 정책"을 그대로 큐로 시뮬레이션하면 된다.

🛠 Improvement
- 불필요한 캐스팅 제거: `q.size() < n`.
- 마지막 출력 뒤 개행 `'\n'` 추가(가독/채점기 안정).

*/

// 2025-10-06 D+3 REVIEW

#include <iostream>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, inf;
	cin >> n;
	queue<int> q;

	while (cin >> inf && inf != -1)
	{
		if (inf == 0)
		{
			if (!q.empty()) q.pop();
		}
		else if (q.size() < n) q.push(inf);
	}

	if (q.empty())
		cout << "empty";

	while (!q.empty())
	{
		cout << q.front() << ' ';
		q.pop();
	}
	cout << '\n';
}

// 2025-10-03 D+0 REVIEW

// #include <iostream>
// #include <queue>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n;
// 	cin >> n;
// 
// 	queue<int> q;
// 	int val;
// 	while (cin >> val && val != -1)
// 	{
// 		if (val == 0)
// 		{
// 			if (!q.empty()) q.pop();
// 		}
// 		else if (q.size() < n) q.push(val);
// 	}
// 
// 	if (q.empty())
// 	{
// 		cout << "empty\n";
// 		return 0;
// 	}
// 
// 	while (!q.empty())
// 	{
// 		cout << q.front();
// 		q.pop();
// 		cout << (q.empty() ? '\n' : ' ');
// 	}
// }

// 2025-10-03 ORIGINAL

// #include <iostream>
// #include <queue>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n;
// 	cin >> n;
// 
// 	int inf;
// 	queue<int> q;
// 	while (cin >> inf && inf != -1)
// 	{
// 		if (inf == 0)
// 		{
// 			if (!q.empty())
// 				q.pop();
// 		}
// 		else if ((int)q.size() < n) q.push(inf);
// 	}
// 
// 	if (q.empty())
// 	{
// 		cout << "empty\n";
// 		return 0;
// 	}
// 
// 	while (!q.empty())
// 	{
// 		cout << q.front();
// 		q.pop();
// 		cout << (q.empty() ? "" : " ");
// 	}
// }