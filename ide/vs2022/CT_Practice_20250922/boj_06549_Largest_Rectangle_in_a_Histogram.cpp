/*
BOJ 6549 — 히스토그램에서 가장 큰 직사각형
주제: Stack | Monotonic Stack | Greedy
폴더: stack/monotonic

⏱ 시간복잡도: O(N)            // 각 막대는 최대 1회 push/pop
💾 공간복잡도: O(N)            // 인덱스 스택

📌 핵심 아이디어
- 막대 인덱스를 담는 **단조 증가 스택** 유지.
- 현재 높이가 스택 top의 높이보다 작아지는 순간, pop된 막대를 구간의 **최소 높이**로 하여 넓이 계산.
	- 오른쪽 경계 = 현재 인덱스 i(미포함)
	- 왼쪽 경계 = pop이후 스택의 새 top(없으면 -1)
	- 너비 = i - (왼쪽경계 + 1), 면적 = 높이 x 너비
- 끝에 센티널(높이 0) 추가로 잔여 스택 일괄 정산.

⚠️ 주의할 점
- 면적은 `long long`으로 계산(높이 <= 1e9, N <= 1e5 -> 면적 <= 1e14).
- 스택에는 **인덱스**만 저장하고 높이는 `h[idx]`로 참조.
- 스택이 비었을 때와 아닐 때의 **너비 계산 분기**를 정확히 구분.

🔧 개선 사항 (Improvement)
- 타입 일관성: 루프/스택 인덱스를 모두 `int`로 통일하고, `int N = (int)h.size();`처럼 한 번만 캐스팅하거나, 
전부 `size_t`로 통일하고 곱셈 직전 `width`만 `long long`으로 캐스팅.
- `h.reserve(n + 1)`로 센티널 포함 재할당 최소화.

✔️ 문제 힌트 (Problem Hint)
- "최대면적 = ( 구간의 최소 높이 ) x ( 구간 너비 )"이고, **최소 높이가 바뀌는 지점**이 곧 단조 스택이 깨지는 시점.
- 따라서 **감소 순간에만** 면적을 계산하면 전ㅊ체가 O(N)으로 해결된다.

*/

// 2025-10-21 ORIGINAL

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	while (cin >> n && n != 0)
	{
		vector<long long> h(n + 1);
		for (int i = 0; i < n; i++)
			cin >> h[i];
		h[n] = 0;
		
		long long mx_val = 0;
		stack<int> stk;
		for (int i = 0; i < static_cast<int>(h.size()); i++)
		{
			while (!stk.empty() && h[stk.top()] > h[i])
			{
				long long top_h = h[stk.top()];
				stk.pop();
				if(stk.empty())
					mx_val = max(mx_val, top_h * i);
				else
					mx_val = max(mx_val, top_h * (i - (stk.top() + 1)));
			}

			stk.push(i);
		}

		cout << mx_val << '\n';
	}
}