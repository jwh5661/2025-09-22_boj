/*
BOJ 1935 — 후위 표기식2 (Postfix Evaluation 2)
Topic: Stack | Postfix Evaluation
Folder: stack/postfix

⏱ 시간복잡도: O(L)
💾 공간복잡도: O(N)

📌 핵심 아이디어
- 후위식(exp)을 왼->오 순회하며, 피연산자(A..Z)는 값 테이블로 치환해 스택에 push.
- 연산자를 만나면 스택에서 두 수를 pop하여 (두 번째 pop이 좌항) 계산 후 결과를 push.
- 순회가 끝나면 스택의 단 하나 값이 정답 -> 소수점 둘째 자리까지 출력.

⚠️ 주의할 점
- 스택에서 꺼낼 때 순서: first pop = 우항, second pop = 좌항 -> tmp2 op tm1.
- 출력 형식: fixed + setprecision(2), 계행은 '\n'.
- (방어) 연산자 처리 시 스택 원소가 2개 미만이면 잘못된 입력으로 간주.

✔️ 지문 힌트
- 피연산자 개수 N은 A부터 순서대로 값이 주어진다 -> num[c-'A']로 인덱싱.
- 사칙연산만 등장하므로 double 스택 하나로 충분.

*/

// 2025-10-23 D+14 REVIEW

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	string str;
	cin >> n >> str;

	vector<double> val(n);
	for (int i = 0; i < n; i++)
		cin >> val[i];

	stack<double> stk;
	for (char c : str)
	{
		if ('A' <= c && c <= 'Z')
			stk.push(val[c - 'A']);
		else if (stk.size() > 1)
		{
			double val1 = stk.top(); stk.pop();
			double val2 = stk.top(); stk.pop();
			switch (c)
			{
			case '+':
				stk.push(val2 + val1);
				break;
			case '-':
				stk.push(val2 - val1);
				break;
			case '*':
				stk.push(val2 * val1);
				break;
			case '/':
				stk.push(val2 / val1);
				break;
			}
		}
		else
			return 0;
	}

	cout << fixed << setprecision(2) << stk.top() << '\n';
}

// 2025-10-05 D+3 REVIEW

// #include <iostream>
// #include <vector>
// #include <stack>
// #include <string>
// #include <iomanip>
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
// 	cin >> n >> str;
// 	vector<int> val(n);
// 	stack<double> stk;
// 
// 	for (int i = 0; i < n; i++)
// 		cin >> val[i];
// 
// 	for (char c : str)
// 	{
// 		if ('A' <= c && c <= 'Z')
// 			stk.push(val[c - 'A']);
// 		else if (stk.size() > 1)
// 		{
// 			double tmp1 = stk.top(); stk.pop();
// 			double tmp2 = stk.top(); stk.pop();
// 
// 			switch (c)
// 			{
// 			case '+':
// 				stk.push(tmp2 + tmp1);
// 				break;
// 			case '-':
// 				stk.push(tmp2 - tmp1);
// 				break;
// 			case '*':
// 				stk.push(tmp2 * tmp1);
// 				break;
// 			case '/':
// 				stk.push(tmp2 / tmp1);
// 				break;
// 			}
// 		}
// 		else
// 			return 0;
// 	}
// 
// 	cout << fixed << setprecision(2) << stk.top() << '\n';
// }

// 2025-10-02 D+0 REVIEW

// #include <iostream>
// #include <vector>
// #include <stack>
// #include <string>
// #include <iomanip>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n;
// 	string exp;
// 	cin >> n >> exp;
// 
// 	vector<int> num(n);
// 	stack<double> stk;
// 	for (int i = 0; i < n; i++)
// 		cin >> num[i];
// 
// 	for (char c : exp)
// 	{
// 		if ('A' <= c && c <= 'Z')
// 			stk.push(num[c - 'A']);
// 		else
// 		{
// 			if ((int)stk.size() > 1)
// 			{
// 				double tmp1 = stk.top();
// 				stk.pop();
// 				double tmp2 = stk.top();
// 				stk.pop();
// 
// 				switch (c)
// 				{
// 				case '+':
// 					stk.push(tmp2 + tmp1);
// 					break;
// 				case '-':
// 					stk.push(tmp2 - tmp1);
// 					break;
// 				case '/':
// 					stk.push(tmp2 / tmp1);
// 					break;
// 				case '*':
// 					stk.push(tmp2 * tmp1);
// 					break;
// 				}
// 			}
// 			else
// 				return 0;
// 		}
// 	}
// 	cout << fixed << setprecision(2) << stk.top() << '\n';
// }

// 2025-10-02 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <stack>
// #include <string>
// #include <iomanip>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n;
// 	string exp;
// 	cin >> n >> exp;
// 	vector<int> num(n);
// 
// 	for (int i = 0; i < n; i++)
// 		cin >> num[i];
// 
// 	stack<double> stk;
// 	for (char c : exp)
// 	{
// 		if ('A' <= c && c <= 'Z')
// 			stk.push(num[c - 'A']);
// 		else
// 		{
// 			if (!stk.empty())
// 			{
// 				double tmp1 = stk.top();
// 				stk.pop();
// 				if (stk.empty()) return 0;
// 				double tmp2 = stk.top();
// 				stk.pop();
// 
// 				switch (c)
// 				{
// 				case '+':
// 					stk.push(tmp2 + tmp1);
// 					break;
// 				case '-':
// 					stk.push(tmp2 - tmp1);
// 					break;
// 				case '/':
// 					stk.push((double)tmp2 / tmp1);
// 					break;
// 				case '*':
// 					stk.push(tmp2 * tmp1);
// 					break;
// 				}
// 			}
// 			else
// 				return 0;
// 		}
// 	}
// 	cout << fixed << setprecision(2) << stk.top() << '\n';
// }