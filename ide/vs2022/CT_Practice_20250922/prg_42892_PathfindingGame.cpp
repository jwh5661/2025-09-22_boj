/*
 * [PRG 42892] 길 찾기 게임 (Lv.3)
 * - 훈련 날짜: 2026-06-09 (화)
 * - 알고리즘: 이진 탐색 트리(BST), DFS (Tree Traversal)
 * - 목적: 2차원 좌표 데이터를 파싱하여 BST 아키텍처를 구축하고, 전위/후위 순회 결과를 반환
 * - 엔진 실무 최적화:
 * 1. Cache-Friendly Memory Allocation : `new` 키워드를 통한 동적 할당을 전면 배제.
 `vector.reserve()`를 통해 메모리를 연속된 공간에 사전 할당한 뒤 해당 원소들의 메모리 주소(&)를 직접 바인딩하여 오버헤드를 극단적으로 줄임.
 * 2. Encapsulated Operator Overloading : 구조체 내부에 `operator>`를 오버로딩하여 
 `std::greater<Node>()`와 연동, 정렬 기준을 캡슐화된 형태로 깔끔하게 제어함.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

struct Node {
    int num = 0, x = 0, y = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int nnum, int nx, int ny)
        :num(nnum), x(nx), y(ny) {
    }

    const bool operator>(const Node& other) const
    {
        if (this->y > other.y)
            return true;
        else if (this->y == other.y)
        {
            if (this->x < other.x)
                return true;
        }

        return false;
    }
};

void insertNode(Node* parent, Node* child)
{
    if (parent->x < child->x)
    {
        if (parent->right == nullptr)
            parent->right = child;
        else
            insertNode(parent->right, child);
    }
    else
    {
        if (parent->left == nullptr)
            parent->left = child;
        else
            insertNode(parent->left, child);
    }
}

void preorder(vector<int>& result, Node* curr)
{
    if (curr == nullptr) return;

    result.push_back(curr->num);
    preorder(result, curr->left);
    preorder(result, curr->right);
}

void postorder(vector<int>& result, Node* curr)
{
    if (curr == nullptr) return;

    postorder(result, curr->left);
    postorder(result, curr->right);
    result.push_back(curr->num);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer(2);
    vector<Node> nodev;
    nodev.reserve(nodeinfo.size());

    for (int i = 0; i < nodeinfo.size(); i++)
        nodev.push_back(Node(i + 1, nodeinfo[i][0], nodeinfo[i][1]));
    
    sort(nodev.begin(), nodev.end(), greater<Node>());

    Node root = nodev[0];

    for (int i = 1; i < nodeinfo.size(); i++)
        insertNode(&root, &nodev[i]);

    preorder(answer[0], &root);
    postorder(answer[1], &root);
    

    return answer;
}
// =========================================================================

int main() {
    // 테스트 케이스
    vector<vector<int>> nodeinfo = { {5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2} };

    // 기대되는 정답
    // 전위 순회: {7,4,6,9,1,8,5,2,3}
    // 후위 순회: {9,6,5,8,1,4,3,2,7}

    vector<vector<int>> result = solution(nodeinfo);

    cout << "========================================" << endl;
    cout << "[전위 순회 결과] ";
    for (int n : result[0]) cout << n << " ";
    cout << "\n[후위 순회 결과] ";
    for (int n : result[1]) cout << n << " ";
    cout << "\n========================================" << endl;

    return 0;
}