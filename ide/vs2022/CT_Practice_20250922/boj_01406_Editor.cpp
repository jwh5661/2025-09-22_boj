/*
BOJ 1406 — 에디터 (Editor)
Topic: Stack | Two-Stacks | Simulation
Folder: stack/editor

⏱ 시간복잡도: O(N + M)
💾 공간복잡도: O(N + M)

📌 핵심 아이디어
- 커서를 기준으로 문자열을 두 부분으로 나눠 관리: left(커서 왼쪽), right(커서 오른쪽).
- 명령 처리:
  - L: left.top()를 right로 이동
  - D: right.top()를 left로 이동
  - B: left.pop()
  - P x: left.push(x)
- 최종 출력: left의 내용을 순서 유지 위해 right로 모두 옮긴 뒤, right를 위에서부터 출력.

⚠️ 주의할 점
- L/D/B는 대상 스택이 비어 있을 때 동작하지 않도록 체크.
- 입력 문자열은 공백 없음 -> `cin >> str` 사용 가능.
- 출력은 마지막에 한 번에 생성(불필요한 flush 방지).

✔️ 지문 힌트
- 커서 이동/삽입/삭제를 O(1)로 처리하려면 두 스택 분할 모델이 적합.
- “왼->오 이동”, “오->왼 이동” 패턴만 정확히 구현하면 전체가 자연스럽게 동작한다.

*/

// 2025-10-04 MINI MOCKTEST

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	stack<char> stk1, stk2;
	string str;
	cin >> str;
	for (char c : str)
		stk1.push(c);

	int m;
	cin >> m;

	while (m--)
	{
		char cmd;
		cin >> cmd;

		if (cmd == 'L' && !stk1.empty())
		{
			stk2.push(stk1.top());
			stk1.pop();
		}
		else if (cmd == 'D' && !stk2.empty())
		{
			stk1.push(stk2.top());
			stk2.pop();
		}
		else if (cmd == 'B' && !stk1.empty())
			stk1.pop();
		else if (cmd == 'P')
		{
			char new_char;
			cin >> new_char;
			stk1.push(new_char);
		}
	}

	while (!stk1.empty())
	{
		stk2.push(stk1.top());
		stk1.pop();
	}

	while (!stk2.empty())
	{
		cout << stk2.top();
		stk2.pop();
	}
	cout << '\n';
}