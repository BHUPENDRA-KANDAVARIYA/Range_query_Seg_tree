#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

// Segemnt Tree for range update
class Seg
{
private:
    vector<int> seg;
    vector<int> lazy;

public:
    Seg(int n)
    {
        seg.resize(4 * n);
        lazy.resize(4 * n);
    }
    void build(int low, int high, int idx, vector<int> &arr)
    {
        if (low == high)
        {
            seg[idx] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(low, mid, 2 * idx + 1, arr);
        build(mid + 1, high, 2 * idx + 2, arr);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }
    // update for range l to h
    void update(int l, int h, int val, int low, int high, int idx)
    {
        if (low > h || high < l)
            return;
        if (lazy[idx] != 0)
        {
            seg[idx] += (high - low + 1) * lazy[idx];
            if (low != high)
            {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
        if (low >= l && high <= h)
        {
            seg[idx] += (high - low + 1) * val;
            if (low != high)
            {
                lazy[2 * idx + 1] += val;
                lazy[2 * idx + 2] += val;
            }
            return;
        }
        int mid = (low + high) / 2;
        update(l, h, val, low, mid, 2 * idx + 1);
        update(l, h, val, mid + 1, high, 2 * idx + 2);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }
    int query(int idx, int low, int high, int l, int h)
    {
        if (low > h || high < l)
            return 0;
        if (lazy[idx] != 0)
        {
            seg[idx] += (high - low + 1) * lazy[idx];
            if (low != high)
            {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
        if (low >= l && high <= h)
            return seg[idx];
        int mid = (low + high) / 2;
        return query(2 * idx + 1, low, mid, l, h) + query(2 * idx + 2, mid + 1, high, l, h);
    }
};
int main()
{
}