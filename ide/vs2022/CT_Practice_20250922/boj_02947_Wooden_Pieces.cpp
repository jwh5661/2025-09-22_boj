/*
BOJ 2947 — 나무 조각 (Wooden Pieces)
Topic: Implementation | Simulation | Bubble Sort (adjacent swaps)
Folder: impl/simulation/

⏱ 시간복잡도: O(5^2) ≈ O(1)   // ( 입력은 항상 5개, 최악 스왑·출력 횟수도 상수 )
💾 공간복잡도: O(1)

📌 핵심 아이디어
- 길이 5의 배열에 대해 인접한 두 수를 비교하여 앞이 더 크면 스왑.
- 스왑이 발생할 때마다 배열 상태를 즉시 출력.
- 전체가 오름차순이 될 때까지(= is_sorted가 참이 될 때까지) 바깥 루프 반복.

⚠️ 주의할 점
- while 조건에 정답 배열을 하드코딩하기보다 `is_sorted`를 쓰면 의도가 명확.
- 사용하지 않는 변수 제거(`is_answer`는 미사용).
- 출력 형식: 공백/개행만 맞추면 트레일링 스페이스도 통과되지만, 깔끔하게 처리 가능.
- "스왑이 발생한 순간"마다 출력해야 함(스왑이 없을 땐 출력 X).
- 출력 포맷: 각 숫자 사이에 공백 1개, 줄바꿈은 스왑마다 1회.

✔️ 지문 힌트
- “swap이 일어날 때마다 출력” → 내부 `if (arr[i] > arr[i+1])` 블록 안에서 즉시 출력.
- 입력 크기 5 -> 단순 시뮬레이션으로 충분.
*/

// 2025-10-13 D+14 REVIEW

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<int> wood;
	for (int i = 0; i < 5; i++)
	{
		int num;
		cin >> num;
		wood.push_back(num);
	}

	while (!is_sorted(wood.begin(), wood.end()))
	{
		for (int i = 0; i < 4; i++)
		{
			if (wood[i] > wood[i + 1])
			{
				swap(wood[i], wood[i + 1]);
				for (int n : wood)
					cout << n << ' ';
				cout << '\n';
			}
		}
	}
}

// 2025-09-28 D+3 REVIEW

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
// 	vector<int> num(5);
// 	for (int i = 0; i < 5; i++)
// 		cin >> num[i];
// 
// 	while (!is_sorted(num.begin(), num.end()))
// 	{
// 		for (int i = 0; i < 4; i++)
// 		{
// 			if (num[i] > num[i + 1])
// 			{
// 				swap(num[i], num[i + 1]);
// 
// 				for (int x : num)
// 					cout << x << " ";
// 				cout << "\n";
// 			}
// 		}
// 	}
// }

// 2025-09-25 D+0 REVIEW

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
// 	vector<int> v(5, 0);
// 
// 	for (int i = 0; i < 5; i++)
// 		cin >> v[i];
// 
// 	while (!is_sorted(v.begin(), v.end()))
// 	{
// 		for (int i = 0; i < 4; i++)
// 		{
// 			if (v[i] > v[i + 1])
// 			{
// 				swap(v[i], v[i + 1]);
// 
// 				for (int x : v)
// 					cout << x << " ";
// 				cout << "\n";
// 			}
// 		}
// 	}
// }

// 2025-09-25 ORIGINAL

// #include <iostream>
// #include <array>
// #include <algorithm>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	array<int, 5> arr;
// 
// 	for (int i = 0; i < 5; i++)
// 		cin >> arr[i];
// 
// 	while (!is_sorted(arr.begin(), arr.end()))// arr[0] != 1 || arr[1] != 2 || arr[2] != 3 || arr[3] != 4 || arr[4] != 5
// 	{
// 		for (int i = 0; i < 4; i++)
// 		{
// 			if (arr[i] > arr[i + 1])
// 			{
// 				swap(arr[i], arr[i + 1]);
// 
// 				for (int j : arr)
// 					cout << j << " ";
// 				cout << "\n";
// 			}
// 		}
// 	}
// }