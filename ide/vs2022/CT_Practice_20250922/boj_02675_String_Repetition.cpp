/*
BOJ 2675 — 문자열 반복 (String Repetition)
Topic: String | Implementation
Folder: string/impl

⏱ 시간복잡도: O(n * |s|)
💾 공간복잡도: O(|s| * n)   // 출력 문자열 길이에 비례

📌 핵심 아이디어
- 각 테스트 케이스마다 문자열 s의 모든 문자를 n번 반복 출력.
- C++ string의 string(count, char) 생성자를 활용하면 반복 출력이 간결해짐.

⚠️ 주의할 점
- string(n, c)는 n이 클 때 메모리를 많이 쓸 수 있음 → 문제 조건에서 허용됨.
- 출력 뒤 반드시 개행 필요.
- 테스트 케이스마다 초기화 필요 없으므로 구현 단순.

✔️ 지문 힌트
- "문자열의 각 문자를 반복해 출력" → 각 문자별 반복 처리 필요.
- "테스트 케이스 T" → 여러 번 반복 수행, 각 줄마다 출력.

💡 개선 포인트
- ✅ [추가] 성능을 더 아끼려면 `ostringstream`로 누적 후 출력 가능.
- 🔄 [수정] 출력 시 string(n, c) 대신 for 루프로도 가능 → 성능은 유사, 디버깅 가독성은 루프가 나을 수도 있음.
*/

// 2025-10-06 D+14 REVIEW

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
		int rep;
		string str;
		cin >> rep >> str;

		for (char c : str)
			cout << string(rep, c);
		cout << '\n';
	}
}

// 2025-09-25 D+3 REVIEW

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
// 		int n;
// 		string s;
// 		cin >> n >> s;
// 		for (char c : s)
// 			cout << string(n, c);
// 		cout << "\n";
// 	}
// }

// 2025-09-22 D+0 REVIEW

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
// 	int t; cin >> t;
// 
// 	while (t--)
// 	{
// 		int r; cin >> r;
// 
// 		string s; cin >> s;
// 
// 		string out = "";
// 		out.reserve(s.size() * r);
// 		for (char c : s)
// 			out.append(r, c);
// 		cout << out << (t == 0 ? "" : "\n");
// 	}
// }

// 2025-09-22 ORIGINAL
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//int main()
//{
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr);
//
//	int t;
//	cin >> t;
//
//	while (t--)
//	{
//		int a;
//		cin >> a;
//
//		string s;
//		cin >> s;
//
//		for (int i = 0; i < (int)s.size(); i++)
//		{
//			for (int j = 0; j < a; j++)
//				cout << s[i];
//		}
//		cout << "\n";
//	}
//}