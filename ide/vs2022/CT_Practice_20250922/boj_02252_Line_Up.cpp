// 2026-03-25 (수)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> con_list(n + 1);
	vector<int> frequency(n + 1, 0);
	queue<int> q;

	// 연결 리스트 만들기 + 큰 학생의 빈도 벡터 증가
	for (int i = 0; i < m; i++)
	{
		int small, tall;
		cin >> small >> tall;

		con_list[small].push_back(tall);
		frequency[tall]++;
	}
	
	// 빈도 벡터가 0인 학생 큐에 삽입
	for (int i = 1; i <= n; i++)
	{
		if (frequency[i] == 0)
			q.push(i);
	}

	// 큐에 있는 숫자 출력
	while (!q.empty())
	{
		int cur = q.front(); q.pop();

		cout << cur << ' ';
		for (int student : con_list[cur])
		{
			frequency[student]--;

			if (frequency[student] == 0)
				q.push(student);
		}
	}
}