/*
BOJ 10866 — 덱 (Deque)
Topic: Deque | Implementation | I/O
Folder: deque/basic

⏱ 시간복잡도: O(M)        // 명령 수 M
💾 공간복잡도: O(N)        // 덱에 들어간 최대 원소 수

📌 핵심 아이디어
- 표준 deque로 명령을 그대로 시뮬레이션:
 - push_front/back: 값 입력 후 양끝 삽입
 - pop_front/back: 비어있지 않으면 출력+삭제, 아니면 -1
 - size/empty/front/back: 스펙대로 출력

⚠️ 주의할 점
- pop/front/back에서 빈 덱이면 -1을 출력.

*/

// 2025-10-12 ORIGINAL

#include <iostream>
#include <deque>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	deque<int> dq;

	while (n--)
	{
		string str;
		cin >> str;

		if (str == "push_front")
		{
			int val;
			cin >> val;
			dq.push_front(val);
		}
		else if (str == "push_back")
		{
			int val;
			cin >> val;
			dq.push_back(val);
		}
		else if (str == "pop_front")
		{
			if (!dq.empty())
			{
				cout << dq.front() << '\n';
				dq.pop_front();
			}
			else
				cout << -1 << '\n';
		}
		else if (str == "pop_back")
		{
			if (!dq.empty())
			{
				cout << dq.back() << '\n';
				dq.pop_back();
			}
			else
				cout << -1 << '\n';
		}
		else if (str == "size")
			cout << dq.size() << '\n';
		else if (str == "empty")
			cout << (dq.empty() ? 1 : 0) << '\n';
		else if (str == "front")
			cout << (dq.empty() ? -1 : dq.front()) << '\n';
		else if(str=="back")
			cout << (dq.empty() ? -1 : dq.back()) << '\n';
	}
}