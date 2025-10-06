/*
BOJ 11866 — 요세푸스 문제 0 (Josephus Problem 0)
Topic: Queue | Simulation
Folder: queue/josephus

⏱ 시간복잡도: O(N·K)   // N≤1000이라 충분
💾 공간복잡도: O(N)

📌 핵심 아이디어
- 1..N을 큐에 넣고, 원형 회전을 큐로 시뮬레이션한다.
- 앞에서 하나씩 꺼내 뒤로 보내며 카운트↑, K번째마다 pop하여 결과에 기록.
- 최종 출력은  "<a, b, c>" 형식.

⚠️ 주의할 점
- 출력 포맷 콤마/공백 위치: "a, b, c" (마지막엔 콤마 없음).
- 큐가 비워질 때까지 반복, 중간 상태를 잘 관리(카운터 초기화 등).
- (선택) vector 결과는 reserve(N)으로 미세 최적화 가능.

✔️ 지문 힌트
- "원형으로 K번째 제거"는 큐 회전으로 자연스럽게 구현 가능.
- 매 단계 1회 회전/판정으로 충분(N<=1000).

*/

// 2025-10-06 D+3 REVIEW

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

	queue<int> q;
	vector<int> num;
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

// 2025-10-03 D+0 REVIEW

// #include <iostream>
// #include <vector>
// #include <queue>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, k;
// 	cin >> n >> k;
// 
// 	vector<int> num;
// 	num.reserve(n);
// 	queue<int> q;
// 
// 	for (int i = 1; i <= n; i++)
// 		q.push(i);
// 
// 	while (!q.empty())
// 	{
// 		int i = k - 1;
// 		while (i--)
// 		{
// 			q.push(q.front());
// 			q.pop();
// 		}
// 		num.push_back(q.front());
// 		q.pop();
// 	}
// 
// 	cout << '<';
// 	for (int i = 0; i < n; i++)
// 		cout << num[i] << (i == n - 1 ? "" : ", ");
// 	cout << ">\n";
// }

// 2025-10-03 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <queue>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, k, cur = 0;
// 	cin >> n >> k;
// 	queue<int> q;
// 	vector<int> josephus;
// 	for (int i = 1; i <= n; i++)
// 		q.push(i);
// 
// 	while (!q.empty())
// 	{
// 		cur++;
// 		if (cur == k)
// 		{
// 			cur = 0;
// 			josephus.push_back(q.front());
// 			q.pop();
// 		}
// 		else
// 		{
// 			q.push(q.front());
// 			q.pop();
// 		}
// 	}
// 
// 	cout << '<';
// 	for (int i = 0; i < n; i++)
// 		cout << josephus[i] << (i == n-1 ? "" : ", ");
// 	cout << '>';
// }