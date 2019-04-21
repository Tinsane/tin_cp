const int N = 1e5 + 10;
inline int sum(int a, int b, int p)
{
    a += b;
    return a >= p ? a - p : a;
}
inline int sub(int a, int b, int p)
{
    return sum(a, p - b, p);
}

struct SuffixArray
{
    int lcp[N];
    int cl[N], pos[N];
    int cl_n[N], pos_n[N];
    int cnt[N];
    int n;
    string s;
    void eprint()
    {
        for(int i = 0; i < n; ++i)
        {
            auto p = pos[i];
            eprintf("%s\n", s.c_str() + p);
        }
        eprintf("\n");
    }
    int calc_cl(int step)
    {
        cl_n[pos[0]] = 0;
        int cl_cnt = 1;
        for(int i = 1; i < n; ++i)
        {
            if (cl[pos[i]] != cl[pos[i - 1]] || cl[sum(pos[i], step, n)] != cl[sum(pos[i - 1], step, n)])
                ++cl_cnt;
            cl_n[pos[i]] = cl_cnt - 1;
        }
        copy(cl_n, cl_n + n, cl);
        return cl_cnt;
    }
    void sort_pos(int cl_cnt, int offset)
    {
        for (int i = 0; i < n; ++i)
            pos_n[i] = sub(pos[i], offset, n);
        fill(cnt, cnt + cl_cnt, 0);
        for (int i = 0; i < n; ++i)
            ++cnt[cl[i]];
        for (int i = 1; i < cl_cnt; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i)
            pos[--cnt[cl[pos_n[i]]]] = pos_n[i];
    }
    void build(string s)
    {
        this->s = s;
        n = s.size();
        for (int i = 0; i < n; ++i)
        {
            pos[i] = i;
            cl[i] = s[i];
        }
        for(int h = 1, cl_cnt = N; h == 1 || cl_cnt < n; h *= 2)
        {
            auto step = h / 2;
            sort_pos(cl_cnt, step);
            cl_cnt = calc_cl(step);
        }
        calc_lcp();
    }
    void calc_lcp()
    {
        int len = 0;
        for(int i = 0; i < n; ++i)
        {
            if (len > 0)
                --len;
            if (cl[i] == n - 1)
                continue;
            auto j = pos[cl[i] + 1];
            while (max(i, j) + len < n && s[i + len] == s[j + len])
                ++len;
            lcp[cl[i]] = len;
        }
    }
} sa;
