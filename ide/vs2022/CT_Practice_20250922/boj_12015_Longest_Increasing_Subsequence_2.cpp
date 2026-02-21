/*
BOJ 12015 — 가장 긴 증가하는 부분 수열 2 (Longest Increasing Subsequence 2)
Topic: Dynamic Programming | Binary Search | LIS
Folder: dp/lis/

⏱ 시간복잡도: O(N log N) ( 각 원소마다 Lower_bound )
💾 공간복잡도: O(N) ( LIS 후보 벡터 )

📌 핵심 아이디어
- LIS 길이만 구하는 문제 -> O(N log N) 방식 사용.
- 길이별 최소 '꼬리값' 배열 유지.
- 새 값 x가 마지막 값보다 크면 push_back,
  아니면 lower_bound로 x 이상 첫 위치를 찾아 그 자리를 x로 교체.
- 최종 배열 크기 = LIS 길이.

⚠️ 주의할 점
- '엄격 증가'이므로 같은 값은 길이를 늘리면 안 됨 → lower_bound(교체).
- LIS의 실제 수열을 구하는 게 아니라 길이만 출력.
- N ≤ 1e6 → O(N^2) 불가 → 이분 탐색 (N log N) 유도.
- 스트리밍 입력으로 전체 배열 저장 없이 처리 가능.

✔️ 지문 힌트
- "가장 긴 증가하는 부분 수열의 길이"만 출력.
- n 최대 1,000,000 -> 최적화 필요.
*/

// 2026-02-21 D+3 REVIEW

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	vector<int> lis;
	lis.reserve(n);

	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;

		if (lis.empty() || lis.back() < x) lis.push_back(x);
		else *lower_bound(lis.begin(), lis.end(), x) = x;
	}

	cout << lis.size() << '\n';
}

// 2026-02-09 Reboot

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
// 	int n;
// 	cin >> n;
// 	vector<int> lis;
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		int x;
// 		cin >> x;
// 
// 		if (lis.empty() || lis.back() < x) lis.push_back(x);
// 		else *lower_bound(lis.begin(), lis.end(), x) = x;
// 	}
// 
// 	cout << lis.size() << '\n';
// }

// 2025-09-27 D+3 REVIEW

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
// 	int n;
// 	vector<int> lis;
// 	cin >> n;
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		int x;
// 		cin >> x;
// 
// 		if (lis.empty() || lis.back() < x) lis.push_back(x);
// 		else *lower_bound(lis.begin(), lis.end(), x) = x;
// 	}
// 	
// 	cout << (int)lis.size() << "\n";
// }

// 2025-09-24 D+0 REVIEW

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
// 	int n; cin >> n;
// 
// 	vector<int> LIS;
// 	for (int i = 0; i < n; i++)
// 	{
// 		int x; cin >> x;
// 		if (i == 0 || LIS.back() < x) LIS.push_back(x);
// 		else *lower_bound(LIS.begin(), LIS.end(), x) = x;
// 	}
// 
// 	cout << (int)LIS.size();
// }

// 2025-09-24 ORIGINAL

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
// 	int n;
// 	cin >> n;
// 
// 	vector<int> LIS;
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		int x; cin >> x;
// 		if (i == 0 || LIS.back() < x) LIS.push_back(x);
// 		else *lower_bound(LIS.begin(), LIS.end(), x) = x;
// 	}
// 
// 	cout << (int)LIS.size();
// }

// 첫 시도. 이걸로 안풀림

// #include <iostream>
// #include <vector>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n;
// 	cin >> n;
// 
// 	vector<int> a(n);
// 
// 	for (int i = 0; i < n; i++)
// 		cin >> a[i];
// 
// 	int mx_cnt = 0;
// 
// 	for (int i = 0; i < n - mx_cnt; i++)
// 	{
// 		int prev = a[i], cur_cnt = 1;
// 		for (int j = i + 1; j < n; j++)
// 		{
// 			if (prev < a[j])
// 			{
// 				prev = a[j];
// 				cur_cnt++;
// 			}
// 		}
// 		if (cur_cnt > mx_cnt) mx_cnt = cur_cnt;
// 	}
// 
// 	cout << mx_cnt;
// }