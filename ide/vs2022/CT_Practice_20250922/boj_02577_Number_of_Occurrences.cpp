/*
BOJ 2577 — 숫자의 개수 (Count Digits)
Topic: Implementation | String Conversion | Frequency Counting
Folder: impl/

⏱ 시간복잡도: O(log(val)) (val의 자릿수 길이에 비례)
💾 공간복잡도: O(1) (고정 크기 배열 10개)

📌 핵심 아이디어
- 세 수의 곱을 문자열로 변환 → 각 자리 문자를 정수로 바꿔 카운트.
- 문자열 → char-'0' 변환으로 각 자리수를 벡터에 기록.
- 출력은 0~9까지 등장 횟수.

⚠️ 주의할 점
- 곱이 int 범위를 넘어갈 수 있음 → long long 사용 권장.
- to_string은 간단하지만, 직접 나눗셈으로 자리수를 구해도 됨.
- freq 배열 크기 = 10 (0~9), 반드시 0 초기화 필요.

✔️ 지문 힌트
- “A×B×C의 결과” → 세 수 곱을 문자열로 바꿔 자리수 세기.
- “0~9의 각 숫자가 몇 번씩 쓰였는가” → 등장 빈도 출력.
*/

// 2026-02-05 Reboot 간단 복습 완료

// 2025-09-27 D+3 REVIEW

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int val = 1;

	for (int i = 0; i < 3; i++)
	{
		int tmp;
		cin >> tmp;

		val *= tmp;
	}

	string num = to_string(val);
	vector<int> freq(10, 0);

	for (char c : num)
		freq[c - '0']++;

	for (int i : freq)
		cout << i << "\n";
}


// 2025-09-24 D+0 REVIEW

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
// 	int val = 1;
// 
// 	for (int i = 0; i < 3; i++)
// 	{
// 		int temp;
// 		cin >> temp;
// 		val *= temp;
// 	}
// 
// 	string s = to_string(val);
// 	int arr[10] = {};
// 
// 	for (char c : s)
// 		arr[c - '0']++;
// 
// 	for (int i : arr)
// 		cout << i << "\n";
// }

// 2025-09-24 ORIGINAL

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
// 	int temp, val;
// 	cin >> temp;
// 	val = temp;
// 	for (int i = 0; i < 2; i++)
// 	{
// 		cin >> temp;
// 		val *= temp;
// 	}
// 
// 	string s = to_string(val);
// 
// 	int arr[10] = {};
// 
// 	for (char c : s)
// 		arr[c - '0']++;
// 
// 	for (int i : arr)
// 		cout << i << "\n";
// }