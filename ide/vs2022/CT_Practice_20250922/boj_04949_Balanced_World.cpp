/*
BOJ 4949 — 균형잡힌 세상 (Balanced World)
Topic: Stack | Parsing
Folder: stack/brackets

⏱ 시간복잡도: O(L) per line
💾 공간복잡도: O(L)

📌 핵심 아이디어
- 각 줄에 대해 괄호만 대상으로 스택 검사를 수행한다.
- 여는 괄호 '(' '[' -> push, 닫는 괄호 ')' ']' -> 비어있지 않은지 확인 후 짝 확인·pop.
- 줄이 끝나면 is_balanced && stack.empty()일 때만 "yes"를 출력.

⚠️ 주의할 점
- 입력은 라인 단위이며, 한 줄이 정확히 "."이면 전체 입력 종료(그 줄은 판정/출력 대상 아님).
- 닫는 괄호에서 먼저 empty 체크 -> top 비교 순서로 언더플로 방지.
- 괄호 외 모든 문자는 무시(공백/문자/마침표 포함).

✔️ 지문 힌트
- 예제 출력 줄 수가 7인 이유: 마지막 줄 "."은 입력 종료 신호라 출력이 없다.
- 복잡한 괄호 라인도 규칙대로만 처리하면 yes/no가 명확히 결정된다.
*/

// 2025-10-01 ORIGINAL

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s;
	getline(cin, s);
	while (s != ".")
	{
		stack<int> my_s;
		bool is_balanced = true;
		for (char c : s)
		{
			if (c == '(' || c == '[')
				my_s.push(c);
			else if (c == ')')
			{
				if (!my_s.empty() && my_s.top() == '(')
					my_s.pop();
				else
				{
					is_balanced = false;
					break;
				}
					
			}
			else if (c == ']')
			{
				if (!my_s.empty() && my_s.top() == '[')
					my_s.pop();
				else
				{
					is_balanced = false;
					break;
				}
			}
		}

		if (is_balanced && my_s.empty())
			cout << "yes" << '\n';
		else
			cout << "no" << '\n';
		getline(cin, s);
	}
}

// 2025-10-01 ORIGINAL

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
// 	string s;
// 	getline(cin, s);
// 	while (s != ".")
// 	{
// 		stack<int> m_stack;
// 		bool is_balanced = true;
// 		for (char c : s)
// 		{
// 			if (c == '(' || c == '[')
// 				m_stack.push(c);
// 			else if (c == ')')
// 			{
// 				if (!m_stack.empty())
// 				{
// 					if (m_stack.top() != '(')
// 					{
// 						is_balanced = false;
// 						break;
// 					}
// 					else
// 						m_stack.pop();
// 				}
// 				else
// 				{
// 					is_balanced = false;
// 					break;
// 				}
// 				
// 			}
// 			else if (c == ']')
// 			{
// 				if (!m_stack.empty())
// 				{
// 					if (m_stack.top() != '[')
// 					{
// 						is_balanced = false;
// 						break;
// 					}
// 					else
// 						m_stack.pop();
// 				}
// 				else
// 				{
// 					is_balanced = false;
// 					break;
// 				}
// 			}
// 		}
// 
// 		if (is_balanced && m_stack.empty())
// 			cout << "yes" << "\n";
// 		else
// 			cout << "no" << "\n";
// 
// 		getline(cin, s);
// 	}
// }