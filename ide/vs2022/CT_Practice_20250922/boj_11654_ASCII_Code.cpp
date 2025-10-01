/*
BOJ 11654 — 아스키 코드 (ASCII Code)
Topic: Implementation | ASCII | Type Casting
Folder: impl/type-casting/

⏱ 시간복잡도: O(1)
💾 공간복잡도: O(1)

📌 핵심 아이디어
- 단일 문자를 입력받아 `static_cast<int>(c)`로 정수(ASCII 코드)로 변환해 출력한다.

⚠️ 주의할 점
- `int(c)`는 **문자의 아스키 코드 값**을 출력.
- 숫자 문자 '0'~'9'를 실제 정수 값으로 쓰고 싶다면 `c - '0'`을 사용해야 함.
  - 예: `'7' → int('7')=55, '7'-'0'=7`.
- 문제에서는 문자 하나를 입력받아 아스키 코드 출력 → `int(c)`가 정답.
- `cin >> c`는 공백/개행을 무시하므로 공백 문자를 입력받는 문제였다면 `cin.get(c)`를 써야 한다.
- 일부 환경에서 `char`가 signed라면 확장 아스키(>127)에서 음수가 될 수 있음. ( 이 문제는 표준 ASCII라 영향 없음 )


✔️ 지문 힌트
- "입력으로 주어진 문자의 아스키 코드 값을 출력한다" → 문자 그대로 `int(c)`.
*/

// 2025-09-30 D+0 REVIEW

#include <iostream>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	char c; cin >> c;
	cout << static_cast<int>(static_cast<unsigned char>(c)) << '\n';
}

// 2025-09-30 ORIGINAL

// #include <iostream>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	char c;
// 	cin >> c;
// 	cout << static_cast<int>(c) << "\n";
// }