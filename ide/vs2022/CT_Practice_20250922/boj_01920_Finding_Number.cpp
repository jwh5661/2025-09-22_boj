/*
BOJ 1920 — 수 찾기 (Finding Number)
Topic: search | binary_search | stl
Folder: search/binary

⏱ 시간복잡도: O(N log N + M log N)
💾 공간복잡도: O(N)

📌 핵심 아이디어
- 입력 수열을 정렬한 뒤, 각 질의에 대해 이분 탐색(std::binary_search)로 존재 여부를 판단한다.

⚠️ 주의할 점
- 출력은 보통 각 줄마다 개행해도 무방하므로, 마지막 줄 처리 분기 없이 매번 '\n'을 출력해도 된다.
- 값 범위가 크다면(잠재적으로 ±2^31), int로도 충분하지만 확실히 하려면 long long 입력으로 통일하는 방법도 있다.

✔️ 지문 힌트
- 정렬 후 이분 탐색이 정석. 해시(unordered_set)로도 평균 O(1) 가능하지만, 최악/메모리 관점에서 정렬+이분 탐색이 안정적이다.
*/

// 2026-02-26 D+14 REVIEW 간단 복습
// 숫자 벡터를 정렬해서 찾는 숫자를 순서대로 이진 탐색하여 결과 출력

// 2026-02-02 D+3 REVIEW

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n;

	vector<int> num(n);
	
	for (int i = 0; i < n; i++)
		cin >> num[i];

	sort(num.begin(), num.end());

	cin >> m;

	while (m--)
	{
		int target;
		cin >> target;

		if (binary_search(num.begin(), num.end(), target))
			cout << 1 << '\n';
		else
			cout << 0 << '\n';
	}
}

// 2026-01-28 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <algorithm>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, m;
// 
// 	cin >> n;
// 	vector<int> num = vector<int>(n);
// 
// 	for (int i = 0; i < n; i++)
// 		cin >> num[i];
// 
// 	sort(num.begin(), num.end());
// 
// 	cin >> m;
// 	while (m--)
// 	{
// 		int target;
// 		cin >> target;
// 		if (binary_search(num.begin(), num.end(), target))
// 			cout << 1;
// 		else
// 			cout << 0;
// 		if (m != 0)
// 			cout << '\n';
// 	}
// }