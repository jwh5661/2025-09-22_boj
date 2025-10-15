/*
BOJ 2812 — 크게 만들기 (Make It Big)
Topic: Greedy | Monotonic Stack
Folder: stack/monotonic

⏱ 시간복잡도: O(N)
💾 공간복잡도: O(N)

📌 핵심 아이디어
- 숫자를 왼->오로 보며 **단조 감소 스택**을 유지.
- 새 자리 `val`이 스택 top보다 크면, 최종 자리수를 `n-k`로 맞출 수 있는 한에서 pop하여 더 큰 수를 앞쪽에 배치.
- 스택 크기를 `n-k` 이하로 유지하며 push. 최종 결과는 스택을 뒤집어 출력.

⚠️ 주의할 점
- 현재 구현은 "남은 자리수로 `n-k`를 채울 수 있는지"를 조건으로 판단해 pop 여부를 결정.
 - 등가이지만, 실전에선 `k_rem`(남은 삭제 횟수)을 두고
	`while (k_rem>0 && !stk.empty() && stk.top()<val) { stk.pop(); --k_rem; }`
	로 작성하면 더 직관적이고 실수 여지가 적음.
- 내림차순 입력(예: 4321)처럼 pop이 전혀 일어나지 않는 케이스도 **`size<n-k`일 때만 push** 조건으로 정확히 처리됨.

✔️ 지문 힌트
- "앞에서 더 작은 숫자를 지워 더 큰 숫자를 당겨온다" -> **greedy + 단조 스택**이 정석.

*/

// 2025-10-15 D+3 REVIEW

#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;
	string str;
	cin >> n >> k >> str;

	stack<int> stk, ans;

	for (char c : str)
	{
		int val = c - '0';

		while (!stk.empty() && stk.top() < val && k > 0)
		{
			k--;
			stk.pop();
		}
		stk.push(val);
	}

	while (k > 0)
	{
		k--;
		stk.pop();
	}

	while (!stk.empty())
	{
		ans.push(stk.top());
		stk.pop();
	}

	while (!ans.empty())
	{
		cout << ans.top();
		ans.pop();
	}
	cout << '\n';
}

// 2025-10-11 ORIGINAL

// #include <iostream>
// #include <string>
// #include <stack>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, k;
// 	string str;
// 	cin >> n >> k >> str;
// 
// 	stack<int> stk;
// 	for (int i = 0; i < str.size(); i++)
// 	{
// 		int val = str[i] - '0';
// 
// 		// 값이 top보다 큰데 top을 pop하고 값을 stack에 추가해도 아직 추가할 수가 더 남아 있다면 반복
// 		while (!stk.empty() && stk.top() < val && ((int)str.size() - (i + 1) >= n - k - (int)stk.size()))
// 			stk.pop();
// 		if(stk.size() < n - k)
// 			stk.push(val);
// 	}
// 
// 	stack<int> out;
// 	while (!stk.empty())
// 	{
// 		out.push(stk.top());
// 		stk.pop();
// 	}
// 
// 	while (!out.empty())
// 	{
// 		cout << out.top();
// 		out.pop();
// 	}
// 	cout << '\n';
// }