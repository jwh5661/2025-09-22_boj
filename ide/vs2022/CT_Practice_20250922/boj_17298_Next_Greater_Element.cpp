/*
BOJ 17298 — 오큰수 (Next Greater Element)
Topic: Stack | Monotonic Stack
Folder: stack/monotonic

⏱ 시간복잡도: O(N)
💾 공간복잡도: O(N)

📌 핵심 아이디어
- 왼+오로 순회하며 "아직 오큰수를 못 찾은 인덱스"를 내림 단조 스택에 보관.
- 새 원소가 스택 top의 값보다 크면, 그 인덱스의 오큰수를 현재 값으로 확정하고 pop을 반복.
- 각 인덱스는 최대 1회 push + 1회 pop -> 전체 선형 보장.

⚠️ 주의할 점
- 비교는 '>'(엄격). 같은 값은 오큰수가 아님 -> pop 금지.
- 스택에는 **값이 아니라 인덱스**를 저장(중복·기록 위치 처리가 쉬움).
- 정답 배열은 **-1로 초기화**(끝까지 미해결인 원소 처리).

✔️ 지문 힌트
- 키워드: "오른쪽에서 **처음** 만나는 **더 큰** 수" -> Monotonic Stack 패턴.
- 내림차순/동일값/오름차순 케이스로 스택 동작을 손으로 점검하면 감이 빠르게 잡힘.
*/

// 2025-10-23 D+14 REVIEW

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	
	vector<int> num(n), ans(n, -1);
	for (int i = 0; i < n; i++)
		cin >> num[i];

	stack<int> stk;
	
	for (int i = 0; i < n; i++)
	{
		while (!stk.empty() && num[stk.top()] < num[i])
		{
			ans[stk.top()] = num[i];
			stk.pop();
		}
		stk.push(i);
	}

	for (int i : ans)
		cout << i << " ";
	cout << '\n';
}

// 2025-10-03 D+3 REVIEW

// #include <iostream>
// #include <vector>
// #include <stack>
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
// 	vector<int> num(n), nge(n, -1);
// 	for (int i = 0; i < n; i++)
// 		cin >> num[i];
// 
// 	stack<int> stk;
// 	for (int i = 0; i < n; i++)
// 	{
// 		while (!stk.empty() && num[stk.top()] < num[i])
// 		{
// 			nge[stk.top()] = num[i];
// 			stk.pop();
// 		}
// 		stk.push(i);
// 	}
// 
// 	for (int i = 0; i < n; i++)
// 		cout << nge[i] << (i == n - 1 ? "\n" : " ");
// }

// 2025-10-01 D+0 REVIEW

// #include <iostream>
// #include <vector>
// #include <stack>
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
// 	vector<int> num(n), nge(n, -1);
// 	for (int i = 0; i < n; i++)
// 		cin >> num[i];
// 
// 	stack<int> s;
// 	for (int i = 0; i < n; i++)
// 	{
// 		while (!s.empty() && num[i] > num[s.top()])
// 		{
// 			nge[s.top()] = num[i];
// 			s.pop();
// 		}
// 		s.push(i);
// 	}
// 
// 	for (int i : nge)
// 		cout << i << ' ';
// 	cout << '\n';
// }

// 2025-10-01 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <stack>
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
// 	vector<int> num(n), nge(n, -1);
// 	for (int i = 0; i < n; i++)
// 		cin >> num[i];
// 
// 	stack<int> s;
// 	for (int i = 0; i < n; i++)
// 	{
// 		while (!s.empty() && num[s.top()] < num[i])
// 		{
// 			nge[s.top()] = num[i];
// 			s.pop();
// 		}
// 		s.push(i);
// 	}
// 
// 	for (int i : nge)
// 		cout << i << " ";
// 	cout << "\n";
// }