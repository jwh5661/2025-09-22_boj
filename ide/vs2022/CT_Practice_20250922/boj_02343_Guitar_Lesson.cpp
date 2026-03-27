// 2026-03-27 (금)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<int> course(n, 0);
	int start = -1, end = 0;

	// 강의 길이 입력 및 강의 최소 길이와 최대 길이 계산
	for (int i = 0; i < n; i++)
	{
		cin >> course[i];

		start = max(start, course[i]);
		end += course[i];
	}

	// 매개변수 탐색
	while (start < end)
	{
		int mid = (start + end) / 2;
		int sum = 0;
		int cnt = 0;

		for (int i = 0; i < n; i++)
		{
			// 합친 값이 mid보다 크면 현재 저장된 강의까지 저장하고 
			// 새 블루레이에 현재 강의 저장
			if (sum + course[i] > mid)
			{
				cnt++;
				sum = 0;
			}

			sum += course[i];
		}

		if (sum)
			cnt++;

		if (cnt <= m)
			end = mid;
		else
			start = mid + 1;
	}

	cout << start << '\n';
}