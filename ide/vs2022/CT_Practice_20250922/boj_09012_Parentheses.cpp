/*
BOJ 9012 — 괄호 (Parentheses)
Topic: Stack | Parsing
Folder: stack/brackets

⏱ 시간복잡도: O(L) per test case
💾 공간복잡도: O(L) (스택 기반), O(1) (카운터 대안)

📌 핵심 아이디어
- 문자열을 순회하며 '('는 push, ')'는 top 확인 후 pop.
- 중간에 빈 스택에서 ')'가 나오면 즉시 NO, 끝나고 스택이 비어 있으면 YES.

⚠️ 주의할 점
- 테스트케이스마다 스택과 상태를 초기화.
- 조기 실패시 남은 문자 읽더라도 판정은 이미 NO.
- 입력은 공백 없는 토큰 단위(`cin >> s`)로 충분.

✔️ 지문 힌트
- VPS(Valid Parenthesis String): 부분 순회 중 음수 밸런스가 나오면 불가능.
- 스택 대신 정수 balance로도 가능: '('->+1, ')'->-1, 도중 음수면 NO, 최종 0이면 YES.

🛠 Improvement
- 상수항을 줄이려면 스택 대신 balance 카운터로 구현 가능(동일한 판정, 더 간결).

*/

// 2025-10-02 D+0 REVIEW

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--)
	{
		string str;
		cin >> str;

		stack<char> stk;
		bool is_vps = true;
		for (char c : str)
		{
			if (c == '(')
				stk.push(c);
			else if (c == ')')
			{
				if (!stk.empty() && stk.top() == '(')
					stk.pop();
				else
				{
					is_vps = false;
					break;
				}
			}
		}

		if (is_vps && stk.empty())
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}

// 2025-10-02 ORIGINAL

// #include <iostream>
// #include <stack>
// #include <string>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int t;
// 	cin >> t;
// 
// 	while (t--)
// 	{
// 		string s;
// 		cin >> s;
// 
// 		stack<char> my_s;
// 		bool is_vps = true;
// 		for (char c : s)
// 		{
// 			if (c == '(')
// 				my_s.push(c);
// 			else if (c == ')')
// 			{
// 				if (!my_s.empty() && my_s.top() == '(')
// 					my_s.pop();
// 				else
// 				{
// 					is_vps = false;
// 					break;
// 				}
// 			}
// 		}
// 
// 		if (is_vps && my_s.empty())
// 			cout << "YES\n";
// 		else
// 			cout << "NO\n";
// 	}
// }