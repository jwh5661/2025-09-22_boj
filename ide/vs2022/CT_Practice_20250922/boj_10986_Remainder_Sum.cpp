/*
BOJ 10986 — 나머지 합 (Remainder Sum)
Topic: Prefix Sum | Counting | Combinatorics
Folder: prefix/counting

⏱ 시간복잡도: O(n + m)
💾 공간복잡도: O(m)

📌 핵심 아이디어
- prefix 누적합의 나머지를 매 원소마다 갱신하고, 같은 나머지의 개수를 누적 카운트.
- 같은 나머지를 가진 prefix 두 개의 차는 m의 배수.
- 초기값 num[0] = 1로 두어 [0..i] 형태의 구간도 자동으로 세어줌.
- 루프에서 즉시 누적: cnt += num[res]; num[res]++;

⚠️ 주의할 점
- cnt와 num은 long long 타입으로 유지 (조합 카운트 크기 때문에).
- prev는 누적 나머지 관리용 → 이름을 res로 통일하면 더 직관적일 수 있음.
- 변수 의미 주석(예: prev=이전 누적 나머지, res=현재 누적 나머지) 한 줄 덧붙이면 가독성↑
- 입력이 매우 큰 경우를 대비해 `res = (res + x) % m` 형태로 변수명 일관화(선호 차)
- 입력이 음수가 아닌 BOJ 조건에선 (res + x) % m만으로 충분.

✔️ 코너 케이스
- m=1이면 모든 구간이 배수 → cnt = n*(n+1)/2 자동으로 계산됨.
- 입력 크기가 최대일 때도 O(n)으로 안전히 동작.
*/

// 2025-10-15 D+14 REVIEW

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	long long n, m, sum = 0, cnt = 0;
	cin >> n >> m;

	vector<long long> num_res(m, 0);
	num_res[0]++;
	for (int i = 0; i < n; i++)
	{
		long long val;
		cin >> val;

		sum = (sum + val) % m;
		cnt += num_res[sum];
		num_res[sum]++;
	}
	cout << cnt << '\n';
}

// 2025-09-29 D+3 REVIEW

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
// 	int n, m;
// 	long long sum = 0, cnt = 0;
// 	cin >> n >> m;
// 
// 	vector<long long> num(m, 0);
// 	num[0] = 1;
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		int val;
// 		cin >> val;
// 
// 		val = (sum + val) % m;
// 		cnt += num[val];
// 		num[val]++;
// 		sum = val;
// 	}
// 	cout << cnt << "\n";
// }

// 2025-09-26 D+0 REVIEW

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
// 	int n, m;
// 	cin >> n >> m;
// 
// 	long long prev = 0, cnt = 0;
// 	vector<long long> num(m, 0);
// 	num[0] = 1;
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		long long res;
// 		cin >> res;
// 
// 		res = (prev + res) % m;
// 		cnt += num[res];
// 		num[res]++;
// 		prev = res;
// 	}
// 	cout << cnt << "\n";
// }

// 2025-09-26 ORIGINAL

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
// 	int n, m;
// 	long long cnt = 0, prev = 0;
// 	cin >> n >> m;
// 
// 	vector<long long> num(m, 0);
// 	num[0] = 1;
// 	for (int i = 0; i < n; i++)
// 	{
// 		long long res;
// 		cin >> res;
// 
// 		res = (prev + res) % m;
// 		cnt += num[res];
// 		num[res]++;
// 		prev = res;
// 	}
// 	
// 	cout << cnt << "\n";
// }