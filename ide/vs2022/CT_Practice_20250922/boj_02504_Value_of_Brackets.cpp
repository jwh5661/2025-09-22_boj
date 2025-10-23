/*
BOJ 2504 — 괄호의 값 (Value of Brackets)
Topic: Stack | Parsing | Evaluation
Folder: stack/evaluation

⏱ 시간복잡도: O(L)
💾 공간복잡도: O(L)

📌 핵심 아이디어
- 스택은 유혀성(짝)만 검증, 값 계산은 mul/val로 처리.
- 여는 괄호에서 mul을 곱한다: '('->x2, '['->x3.
- 닫는 괄호에서:
 - 스택 top이 같은 종류인지 확인(아니면 0).
 - 직전에 바로 열렸다면(바로 닫힘) val += mul.
 - 그 후 mul을 되돌린다. ')'->/2, ']'->/3.

⚠️ 주의할 점
- 진행 중 불일치/언더플로는 즉시 0 출력 후 종료.
- 처리 종료 후 스택이 비어 있어야 유효.
- 플래그(바로 닫힘 판정)는 여는 순간 true, 닫는 순간 사용 후 false로.

✔️ 지문 힌트
- "바로 닫힘일 때만 더하고, 항상 닫힌 뒤 되돌린다(/2,/3)"를 불변식으로 유지.
- 인접 합은 누적, 중첩은 mul이 반영되어 자연스럽게 곱으로 계산됨.

*/

// 2025-10-23 D+14 REVIEW

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string str;
	cin >> str;
	stack<char> stk;
	long long mul = 1, val = 0;
	bool just_open = false;

	for (char c : str)
	{
		if (c == '(')
		{
			just_open = true;
			stk.push(c);
			mul *= 2;
		}
		else if (c == '[')
		{
			just_open = true;
			stk.push(c);
			mul *= 3;
		}
		else if (c == ')')
		{
			if (stk.empty() || stk.top() != '(')
			{
				cout << 0 << '\n';
				return 0;
			}
			else
			{
				if (just_open)
				{
					val += mul;
					just_open = false;
				}
				mul /= 2;
				stk.pop();
			}
		}
		else if (c == ']')
		{
			if (stk.empty() || stk.top() != '[')
			{
				cout << 0 << '\n';
				return 0;
			}
			else
			{
				if (just_open)
				{
					val += mul;
					just_open = false;
				}
				mul /= 3;
				stk.pop();
			}
		}
	}

	if (stk.empty())
		cout << val << '\n';
	else
		cout << 0 << '\n';
}

// 2025-10-05 D+3 REVIEW

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
// 	string str;
// 	cin >> str;
// 	stack<char> stk;
// 	long long sum = 0, mul = 1;
// 	bool just_open = false;
// 	
// 	for (char c : str)
// 	{
// 		if (c == '(')
// 		{
// 			mul *= 2;
// 			stk.push(c);
// 			just_open = true;
// 		}
// 		else if (c == '[')
// 		{
// 			mul *= 3;
// 			stk.push(c);
// 			just_open = true;
// 		}
// 		else if (c == ')')
// 		{
// 			if (!stk.empty() && stk.top() == '(')
// 			{
// 				if (just_open)
// 				{
// 					sum += mul;
// 					just_open = false;
// 				}
// 				mul /= 2;
// 				stk.pop();
// 			}
// 			else
// 			{
// 				cout << 0 << '\n';
// 				return 0;
// 			}
// 		}
// 		else if (c == ']')
// 		{
// 			if (!stk.empty() && stk.top() == '[')
// 			{
// 				if (just_open)
// 				{
// 					sum += mul;
// 					just_open = false;
// 				}
// 				mul /= 3;
// 				stk.pop();
// 			}
// 			else
// 			{
// 				cout << 0 << '\n';
// 				return 0;
// 			}
// 		}
// 	}
// 	
// 	if (stk.empty())
// 		cout << sum << '\n';
// 	else
// 		cout << 0 << '\n';
// }

// 2025-10-02 D+0 REVIEW

// #include <iostream>
// #include <stack>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string str;
// 	cin >> str;
// 
// 	stack<char> stk;
// 	int val = 0, mul = 1;
// 	bool just_open = false;
// 	for (char c : str)
// 	{
// 		if (c == '(')
// 		{
// 			stk.push(c);
// 			mul *= 2;
// 			just_open = true;
// 		}
// 		else if (c == '[')
// 		{
// 			stk.push(c);
// 			mul *= 3;
// 			just_open = true;
// 		}
// 		else if (c == ')')
// 		{
// 			if (!stk.empty() && stk.top() == '(')
// 			{
// 				if(just_open)
// 				{
// 					val += mul;
// 					just_open = false;
// 				}
// 				mul /= 2;
// 				stk.pop();
// 			}
// 			else
// 			{
// 				cout << 0 << '\n';
// 				return 0;
// 			}
// 		}
// 		else if (c == ']')
// 		{
// 			if (!stk.empty() && stk.top() == '[')
// 			{
// 				if (just_open)
// 				{
// 					val += mul;
// 					just_open = false;
// 				}
// 				mul /= 3;
// 				stk.pop();
// 			}
// 			else
// 			{
// 				cout << 0 << '\n';
// 				return 0;
// 			}
// 		}
// 	}
// 
// 	if (stk.empty()) cout << val << '\n';
// 	else cout << 0 << '\n';
// }

// 2025-10-02 ORIGINAL

// #include <iostream>
// #include <stack>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string str;
// 	cin >> str;
// 
// 	stack<char> stk;
// 	int val = 0, mul = 1;
// 	bool just_open = false;
// 	for (char c : str)
// 	{
// 		if (c == '(')
// 		{
// 			mul *= 2;
// 			stk.push(c);
// 			just_open = true;
// 		}
// 		else if (c == '[')
// 		{
// 			mul *= 3;
// 			stk.push(c);
// 			just_open = true;
// 		}
// 		else if (c == ')')
// 		{
// 			if (!stk.empty() && stk.top() == '(')
// 			{
// 				if (just_open)
// 				{
// 					val += mul;
// 					mul /= 2;
// 					just_open = false;
// 				}
// 				else
// 					mul /= 2; 
// 				stk.pop();
// 			}
// 			else
// 			{
// 				cout << 0 << '\n';
// 				return 0;
// 			}
// 		}
// 		else if (c == ']')
// 		{
// 			if (!stk.empty() && stk.top() == '[')
// 			{
// 				if (just_open)
// 				{
// 					val += mul;
// 					mul /= 3;
// 					just_open = false;
// 				}
// 				else
// 					mul /= 3;
// 				stk.pop();
// 			}
// 			else
// 			{
// 				cout << 0 << '\n';
// 				return 0;
// 			}
// 		}
// 	}
// 
// 	if (stk.empty()) cout << val << '\n';
// 	else cout << 0 << '\n';
// }