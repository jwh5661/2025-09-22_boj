/*
BOJ 10845 — 큐 (Queue)
Topic: Queue | Implementation
Folder: queue/basic

⏱ 시간복잡도: O(M)        // 명령 개수 M
💾 공간복잡도: O(N)        // 큐에 들어간 최대 원소 수

📌 핵심 아이디어
- 표준 큐로 명령어를 그대로 시뮬레이션:
  - push X: q.push(X)
  - pop: 비어있지 않으면 q.front() 출력 후 pop, 아니면 -1
  - size: q.size()
  - empty: q.empty() ? 1 : 0
  - front/back: 비어있지 않으면 해당 값, 아니면 -1

⚠️ 주의할 점
- 빈 큐에서 pop/front/back은 반드시 -1 출력.
- 출력은 개행 문자('\n')로 마무리.
- size는 정수 출력 기대 → 필요시 static_cast<int>(q.size()) 사용.

✔️ 지문 힌트
- 큐의 전형적 연산을 그대로 구현하면 되는 입출력 시뮬레이션 문제.
- 표준 라이브러리 `std::queue`로 충분히 해결 가능.

*/

// 2025-11-06 D+14 REVIEW

#include <iostream>
#include <string>
#include <queue>

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

		if (str[0] == 'p')
		{
			if (str[1] == 'u')
			{
				int val;
				cin >> val;

				q.push(val);
			}
			else if (str[1] == 'o')
			{
				if (!q.empty())
				{
					cout << q.front() << '\n';
					q.pop();
				}
				else
					cout << -1 << '\n';
			}
		}
		else if (str[0] == 's')
			cout << q.size() << '\n';
		else if (str[0] == 'e')
			cout << (q.empty() ? 1 : 0) << '\n';
		else if (str[0] == 'f')
			cout << (q.empty() ? -1 : q.front()) << '\n';
		else if (str[0] == 'b')
			cout << (q.empty() ? -1 : q.back()) << '\n';
	}
}

// 2025-10-13 D+3 REVIEW

// #include <iostream>
// #include <string>
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
// 
// 	while (n--)
// 	{
// 		string str;
// 		cin >> str;
// 
// 		if (str[0] == 'p')
// 		{
// 			if (str[1] == 'u')
// 			{
// 				int val;
// 				cin >> val;
// 				q.push(val);
// 			}
// 			else if (str[1] == 'o')
// 			{
// 				if (!q.empty())
// 				{
// 					cout << q.front() << '\n';
// 					q.pop();
// 				}
// 				else
// 					cout << -1 << '\n';
// 			}
// 		}
// 		else if (str[0] == 's')
// 			cout << q.size() << '\n';
// 		else if (str[0] == 'e')
// 			cout << (q.empty() ? 1 : 0) << '\n';
// 		else if (str[0] == 'f')
// 			cout << (q.empty() ? -1 : q.front()) << '\n';
// 		else if (str[0] == 'b')
// 			cout << (q.empty() ? -1 : q.back()) << '\n';
// 	}
// }

// 2025-10-06 ORIGINAL

// #include <iostream>
// #include <string>
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
// 	string str;
// 	cin >> n;
// 	queue<int> q;
// 
// 	while (n--)
// 	{
// 		cin >> str;
// 		if (str == "push")
// 		{
// 			int val;
// 			cin >> val;
// 			q.push(val);
// 		}
// 		else if (str == "pop")
// 		{
// 			if (!q.empty())
// 			{
// 				cout << q.front() << '\n';
// 				q.pop();
// 			}
// 			else
// 				cout << -1 << '\n';
// 		}
// 		else if (str == "size")
// 			cout << q.size() << '\n';
// 		else if (str == "empty")
// 		{
// 			if (q.empty())
// 				cout << 1 << '\n';
// 			else
// 				cout << 0 << '\n';
// 		}
// 		else if (str == "front")
// 		{
// 			if (!q.empty())
// 				cout << q.front() << '\n';
// 			else
// 				cout << -1 << '\n';
// 		}
// 		else if (str == "back")
// 		{
// 			if (!q.empty())
// 				cout << q.back() << '\n';
// 			else
// 				cout << -1 << '\n';
// 		}
// 	}
// }