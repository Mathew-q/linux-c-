#include<iostream>
#include<vector>

using namespace std;

/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param a ListNode类
     * @param b ListNode类
     * @return ListNode类
     */
    ListNode* xorList(ListNode* a, ListNode* b) {
        // write code here
        stack<int> s1;
        queue<int> s2;
        queue<int> res;

        ListNode* head1 = a;
        ListNode* head2 = b;
        while (head1)
        {
            s1.push(head1->val);
            head1 = head1->next;
        }
        while (head2)
        {
            s2.push(head2->val);
            head2 = head2->next;
        }

        int n1 = s1.size();
        int n2 = s2.size();
        int N = n1 > n2 ? n2 : n1;
        ListNode* head_new = nullptr;
        ListNode* pre = nullptr;
        for (int i = 0; i < N; i++)
        {
            int a1 = s1.top(); s1.pop();
            int b1 = s2.front(); s2.pop();
            int temp = a == b ? 0 : 1;
            ListNode* cur = new ListNode(temp);
            cur->next = pre;
            pre = cur;
        }

        while (!s1.empty())
        {
            int t = s1.top(); s1.pop();
            ListNode* cur = new ListNode(t);
            cur->next = pre;
            pre = cur;
        }

        while (!s1.empty())
        {
            int t = s2.front(); s1.pop();
            ListNode* cur = new ListNode(t);
            cur->next = pre;
            pre = cur;
        }



        head_new->next = pre;

        while (pre)
        {
            if (pre->val != 0)
            {
                pre = pre->next;
            }
            else
            {
                pre = pre->next;
                break;
            }
        }

        return pre;

    }
};


int t3()
{
    long n, x;
    cin >> n >> x;
    vector<long> x1(n, 0);
    vector<long> w1(n, 0);
    vector<long> x2(n, 0);
    vector<long> w2(n, 0);

    vector<long> v(x + 1, -1e9);
    v[0] = 0;
    for (long i = 0; i < n; i++)
    {
        cin >> x1[i] >> w1[i] >> x2[i] >> w2[i];
    }
    for (long i = 1; i <= n; i++)
    {
        for (long j = x; j >= x2[i - 1]; j--)
        {
            if (j < x1[i - 1])
                v[j] = max(v[j], v[j - x2[i - 1]] + w2[i - 1]);
            else
            {
                v[j] = max(v[j], v[j - x2[i - 1]] + w2[i - 1]);
                v[j] = max(v[j], v[j - x1[i - 1]] + w1[i - 1]);
            }

            if (v[j] < 0)
                v[j] = -1e9;
        }
    }

    if (v[x] > 0)
    {
        cout << v[x] << endl;
    }
    else
        cout << -1 << endl;
    return 0;

}
