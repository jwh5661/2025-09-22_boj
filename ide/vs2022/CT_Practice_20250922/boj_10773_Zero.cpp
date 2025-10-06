/*
BOJ 10773 — 제로 (Zero)
Topic: Stack | Implementation
Folder: stack/basic

⏱ 시간복잡도: O(K)
💾 공간복잡도: O(K)

📌 핵심 아이디어
- 입력이 0이면 최근 수를 스택에서 pop, 0이 아니면 push.
- 모든 입력 처리 후 스택에 남은 수를 합산해 출력.

⚠️ 주의할 점
- 문제 스펙상 빈 스택에서 0이 오지 않지만, 방어적으로 empty 체크 후 pop해도 좋음.
- 합이 int 범위를 넘을 수 있으므로 합과 스택 원소는 long long 사용 권장.

✔️ 지문 힌트
- "직전 수를 취소"는 스택의 전형적 활용: push & pop 만으로 시뮬레이션 가능. 

🛠 Improvement
- 합산 루프 없이 실시간 합 관리 가능: push 시 sum += val, pop 전에 sum -= top.

*/

// 2025-10-06 D+3 REVIEW

#include <iostream>
#include <stack>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int k;
	long long sum = 0;
	cin >> k;

	stack<long long> stk;
	while (k--)
	{
		long long val;
		cin >> val;
		if (val != 0)
		{
			stk.push(val);
			sum += val;
		}
		else if (!stk.empty())
		{
			sum -= stk.top();
			stk.pop();
		}
	}

	cout << sum << '\n';
}

// 2025-10-03 D+0 REVIEW

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
// 	int k;
// 	cin >> k;
// 	long long sum = 0;
// 	stack<long long> stk;
// 	while (k--)
// 	{
// 		long long val;
// 		cin >> val;
// 
// 		if (val != 0)
// 			stk.push(val);
// 		else
// 			stk.pop();
// 	}
// 
// 	while (!stk.empty())
// 	{
// 		sum += stk.top();
// 		stk.pop();
// 	}
// 
// 	cout << sum << '\n';
// }

// 2025-10-03 ORIGINAL

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
// 	int k;
// 	cin >> k;
// 
// 	long long sum = 0;
// 	stack<long long> stk;
// 	while (k--)
// 	{
// 		long long val;
// 		cin >> val;
// 
// 		if (val == 0)
// 			stk.pop();
// 		else
// 			stk.push(val);
// 	}
// 
// 	while (!stk.empty())
// 	{
// 		sum += stk.top();
// 		stk.pop();
// 	}
// 
// 	cout << sum << '\n';
// }