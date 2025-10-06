/*
BOJ 10809 — 알파벳 찾기 (Find Alphabet)
Topic: String | Implementation
Folder: string/impl

⏱ 시간복잡도: O(|s| + 26)
💾 공간복잡도: O(26)

📌 핵심 아이디어
- 알파벳 소문자 26개 배열을 -1로 초기화.
- 문자열을 처음부터 순회하며 해당 문자가 처음 나오면 인덱스를 기록.
- 마지막에 26개 인덱스를 공백으로 구분해 출력.

⚠️ 주의할 점
- fill로 -1 초기화(현재 구현 OK).
- 배열 크기/인덱스 범위가 26으로 고정됨 → 소문자 전제 문제.

✔️ 지문 힌트
- "알파벳 소문자 a–z" → 배열 크기 26 필요
- "처음 등장하는 위치" → 값이 -1일 때만 갱신

💡 개선 포인트
- ✅ [추가] range-based for + 별도 인덱스 관리로 코드 단순화 가능.
- ✅ [추가] 출력 형식을 `ostringstream`/조건부 콤마로 다듬으면 마지막 공백 처리 불필요.
- 🔄 [수정] `(int)s.size()` 캐스팅 제거 → `size_t` 사용 권장.
*/

// 2025-10-06 REVIEW D+14

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int arr[26];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string str;
	cin >> str;

	fill(arr, arr + 26, -1);

	for (int i = 0; i < str.size(); i++)
	{
		if (arr[str[i] - 'a'] == -1)
			arr[str[i] - 'a'] = i;
	}

	for (int i : arr)
		cout << i << ' ';
	cout << '\n';
}

// 2025-09-25 D+3 REVIEW
// 
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//int arr[26];
//
//int main()
//{
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr);
//
//	string s;
//	cin >> s;
//
//	fill(arr, arr + 26, -1);
//
//	for (int i = 0; i < (int)s.size(); i++)
//	{
//		int idx = s[i] - 'a';
//		if (arr[idx] == -1)
//			arr[idx] = i;
//	}
//
//	for (int i = 0; i < 26; i++)
//		cout << arr[i] << (i == 25 ? "" : " ");
//}

// 2025-09-22 D+0 REVIEW
// #include <iostream>
// #include <string>
// 
// using namespace std;
// 
// int arr[26];
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string s;
// 	cin >> s;
// 
// 	int n = (int)s.size();
// 
// 	fill(arr, arr + 26, -1);
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		int idx = s[i] - 'a';
// 		if (arr[idx] != -1) continue;
// 		arr[idx] = i;
// 	}
// 
// 	for (int i = 0; i < 26; i++)
// 		cout << arr[i] << (i == 25 ? "" : " ");
// }

// 2025-09-22 ORIGINAL
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//int arr[26];
//
//int main()
//{
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr);
//
//	string s;
//	cin >> s;
//
//	fill(arr, arr + 26, -1);
//
//	for (int i = 0; i < (int)s.size(); i++)
//	{
//		int idx = s[i] - 'a';
//		if (arr[idx] != -1) continue;
//		arr[idx] = i;
//	}
//
//	for (int i : arr)
//		cout << i << " ";
//}