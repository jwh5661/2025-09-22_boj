/*
BOJ 10828 — 스택 (Stack)
Topic: Stack | Implementation
Folder: stack/basic

⏱ 시간복잡도: O(Q)
💾 공간복잡도: O(Q)

📌 핵심 아이디어
- vector를 스택으로 사용: push_back / pop_back / back / empty / size로 매핑.
- 명령어에 따라 정확히 한 줄씩 출력(단, push는 출력 없음).

⚠️ 주의할 점
- 빈 스택에서 pop/top은 -1. empty는 1/0, size는 정수로 출력.
- 대량 I/O에서 endl 대신 '\n' 사용(불필요한 flush 방지).
- 입력 명령 수(Q)가 곧 최대 push 상한이므로 reserve(Q) 최적화 가능.

✔️ 지문 힌트
- 스택 연산을 그대로 시뮬레이션 하면 됨: push/pop/size/empty/top.
- 자료구조 상태 변화 후 곧바로 요구 결과를 출력하는 패턴을 유지.
*/

// 2025-10-04 D+3 REVIEW

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<int> v;
	v.reserve(n);

	while (n--)
	{
		string s;
		cin >> s;

		if (s == "push")
		{
			int val;
			cin >> val;

			v.push_back(val);
		}
		else if (s == "pop")
		{
			if (!v.empty())
			{
				cout << v.back() << '\n';
				v.pop_back();
			}
			else
				cout << -1 << '\n';
		}
		else if (s == "size")
			cout << v.size() << '\n';
		else if (s == "empty")
		{
			if (v.empty())
				cout << 1 << '\n';
			else
				cout << 0 << '\n';
		}
		else if (s == "top")
		{
			if (!v.empty())
				cout << v.back() << '\n';
			else
				cout << -1 << '\n';
		}
	}
}

// 2025-10-01 D+0 REVIEW

// #include <iostream>
// #include <vector>
// #include <string>
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
// 	vector<int> my_s;
// 	my_s.reserve(n);
// 
// 	while (n--)
// 	{
// 		string cmd;
// 		cin >> cmd;
// 
// 		if (cmd == "push")
// 		{
// 			int val;
// 			cin >> val;
// 			my_s.push_back(val);
// 		}
// 		else if (cmd == "pop")
// 		{
// 			if (my_s.empty())
// 				cout << -1 << '\n';
// 			else
// 			{
// 				cout << my_s.back() << '\n';
// 				my_s.pop_back();
// 			}
// 		}
// 		else if (cmd == "size")
// 			cout << (int)my_s.size() << '\n';
// 		else if (cmd == "empty")
// 			cout << (int)my_s.empty() << '\n';
// 		else if (cmd == "top")
// 		{
// 			if (my_s.empty())
// 				cout << -1 << '\n';
// 			else
// 				cout << my_s.back() << '\n';
// 		}
// 	}
// }

// 2025-10-01 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <string>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	vector<int> s;
// 	int n;
// 	cin >> n;
// 	s.reserve(n);
// 
// 	while (n--)
// 	{
// 		string cmd;
// 		cin >> cmd;
// 
// 		if (cmd == "push")
// 		{
// 			int val;
// 			cin >> val;
// 
// 			s.push_back(val);
// 		}
// 		else if (cmd == "pop")
// 		{
// 			if (s.empty())
// 				cout << -1 << "\n";
// 			else
// 			{
// 				cout << s.back() << "\n";
// 				s.pop_back();
// 			}
// 		}
// 		else if (cmd == "size")
// 			cout << static_cast<int>(s.size()) << "\n";
// 		else if (cmd == "empty")
// 			cout << static_cast<int>(s.empty()) << "\n";
// 		else if (cmd == "top")
// 		{
// 			if (s.empty())
// 				cout << -1 << "\n";
// 			else
// 				cout << s.back() << "\n";
// 		}
// 			
// 	}
// }