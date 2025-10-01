/*
BOJ 9086 — 문자열 (String)
Topic: String | Implementation
Folder: string/impl/

⏱ 시간복잡도: O(|s|) (문자열 입력 길이에 비례)
💾 공간복잡도: O(1)

📌 핵심 아이디어
- 문자열의 첫 번째 문자와 마지막 문자를 출력.
- 문자열 길이가 1일 때도 정상 동작 (`s.front()`와 `s.back()` 동일 문자).

⚠️ 주의할 점
- s.front(), s.back()은 C++11 이상에서 사용 가능.
- 입력 문자열 길이가 최소 1 이상임이 보장됨(BOJ 조건).
- 출력은 반드시 첫 문자 + 마지막 문자 순서, 그 뒤에 개행.

✔️ 지문 힌트
- “첫 번째와 마지막 글자를 출력한다” → 문자열 길이와 관계없이 동일 처리.
*/

// 2025-09-29 D+0 REVIEW

#include <iostream>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--)
	{
		string s;
		cin >> s;

		cout << s.front() << s.back() << "\n";
	}
}

// 2025-09-29 ORIGINAL

// #include <iostream>
// #include <string>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int t;
// 	cin >> t;
// 
// 	while (t--)
// 	{
// 		string s;
// 		cin >> s;
// 
// 		cout << s.front() << s.back() << "\n";
// 	}
// }