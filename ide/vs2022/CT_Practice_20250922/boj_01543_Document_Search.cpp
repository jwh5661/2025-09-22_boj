/*
BOJ 1543 — 문서 검색 (Document Search)
Topic: String | Scanning | Non-overlapping Match
Folder: string/

⏱ 시간복잡도: O(n·m)  (n=|t|, m=|p|; 최악 substr 비교)
💾 공간복잡도: O(1)

📌 핵심 아이디어
- 시작 인덱스 i에서 길이 m만큼 잘라 p와 비교.
- 일치하면 카운트++ 하고 i를 m만큼 건너뛰어(겹치지 않게) 다음 탐색.
- 불일치면 i를 1 증가.

⚠️ 주의할 점
- 이 문제는 **겹치지 않음**이 핵심 → 매치 후 `i += m`.
- `getline` 두 줄 입력: 이 파일이 단독 실행이면 개행 처리 이슈 없음.
- `substr(i, m)`은 매 호출마다 부분 문자열을 만든다 → 데이터가 극단적으로 길다면 비용이 커질 수 있음(아래 개선 참고).

✔️ 지문 힌트
- “겹치지 않게 세기” → 매치 발생 시 시작 인덱스를 m만큼 전진.
- 공백 포함 가능 → `getline`으로 전체 라인 입력.
*/

// 2025-10-20 D+14 REVIEW

#include <iostream>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string str1, str2;
	getline(cin, str1);
	getline(cin, str2);

	int n = (int)str2.size(), cnt = 0;

	for (size_t pos = 0; (pos = str1.find(str2, pos)) != string::npos; pos += n)
		cnt++;
	cout << cnt << '\n';
}

// 2025-10-02 D+3 REVIEW

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
// 	string t, p;
// 	getline(cin, t);
// 	getline(cin, p);
// 	int n = (int)p.size(), cnt = 0;
// 	 
// 	for (size_t pos = 0; (pos = t.find(p, pos)) != string::npos; pos += n)
// 		cnt++;
// 	cout << cnt << '\n';
// }

// 2025-09-29 D+0 REVIEW

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
// 	string t, p;
// 	getline(cin, t);
// 	getline(cin, p);
// 
// 	int i = 0, n = (int)t.size(), m = (int)p.size(), cnt = 0;
// 	for (size_t pos = 0; (pos = t.find(p, pos)) != string::npos; pos += m)
// 		cnt++;
// 	cout << cnt << "\n";
// }

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
// 	string t, p;
// 	getline(cin, t);
// 	getline(cin, p);
// 	 
// 	int n = (int)t.size(), m = (int)p.size(), cnt = 0;
// 
// 	int i = 0;
// 	while (i < n - m + 1)
// 	{
// 		if (t.substr(i, m) == p)
// 		{
// 			i += m;
// 			cnt++;
// 		}
// 		else
// 			i++;
// 	}
// 	cout << cnt << "\n";
// }