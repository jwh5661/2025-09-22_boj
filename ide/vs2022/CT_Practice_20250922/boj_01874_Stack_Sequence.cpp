/*
BOJ 1874 — 스택 수열 (Stack Sequence)
Topic: Stack | Simulation | Invariant-Driven
Folder: stack/sequence

⏱ 시간복잡도: O(N)
💾 공간복잡도: O(N)

📌 핵심 아이디어 (단조 변수/사후조건 기반 사고)
- 사후조건(Postcondition)을 먼저 고정: "루프 직후 stk.top() == val이면 pop, 아니면 NO"
- 이를 보장하기 위한 최소 행동: 현재 단조 증가 변수 j를 **val**까지 밀어넣기 -> while (j <= val) { push(j++); '+' }.
- 스택의 "비었냐/작냐" 같은 상태 분기 대신, **단조 변수 j 하나로 루프를 제어**하면 논리가 단순·명확해진다.
- push 후에는 반드시 `top == val`을 검사하여 pop('-') 또는 불가능("NO")을 결정.

⚠️ 주의할 점
- j는 1..N 범위에서 **단조 증가**하며, 한 숫자는 **딱 한 번만** push 가능.
- `top > val`인 시점은 이미 지나간 값이므로 **즉시 NO**
- 연산 로그는 push 때 '+' 기록, 성공적 pop 때 '-' 기록. 출력은 줄바꿈으로.

✔️ 지문 힌트
- 오름차순으로 1..N을 한 번씩만 사용할 수 있다는 제약 -> 단조 변수(j)로 전체 흐름을 설계.
- 상태(if/else)에 기대지 말고, "val까지 밀어넣는다"는 불변식을 루프 조건에 직접 박아라.

*/

// 2025-10-04 MINI MOCKTEST

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

	stack<int> stk;
	vector<char> v;
	int j = 1, val;
	for (int i = 0; i < n; i++)
	{
		cin >> val;
		while (j <= val)
		{
			stk.push(j++);
			v.push_back('+');
		}

		if (!stk.empty() && stk.top() == val)
		{
			v.push_back('-');
			stk.pop();
		}
		else
		{
			cout << "NO\n";
			return 0;
		}
	}

	for (char c : v)
		cout << c << '\n';
}