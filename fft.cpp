using cnum = complex<double>;

const int LOGN = 10;
const int N = 1 << LOGN;
int bitrev(int x, int len)
{
	int res = 0;
	while(len--)
	{
		res <<= 1;
		if (x & 1)
			res ^= 1;
		x >>= 1;
	}
	return res;
}

int lb(int x)
{
	return x ^ (x & (x - 1));
}

struct FFT
{
	cnum w[N];
	cnum fa[N], fb[N];
	FFT()
	{
		for (int i = 2; i <= N; i *= 2)
			w[N / i] = { cos(2 * PI / i), sin(2 * PI / i) };
		w[0] = 1;
		for (int i = 1; i < N; ++i)
		{
			auto b = lb(i);
			if (b != i)
				w[i] = w[b] * w[i ^ b];
		}
	}
	void fft(cnum arr[], int lenp, bool rev = false)
	{
		auto len = 1 << lenp;
		for (int i = 0; i < len; ++i)
		{
			auto rev = bitrev(i, lenp);
			if (rev > i)
				swap(arr[rev], arr[i]);
		}
		for (int b = 1; b < len; b *= 2)
		{
			auto wstep = N / (2 * b);
			for (int i = 0; i < len; i += 2 * b)
				for (int j = 0; j < b; ++j)
				{
					auto f = arr[i + j];
					auto s = arr[i + b + j] * w[wstep * j];
					arr[i + j] = f + s;
					arr[i + b + j] = f - s;
				}
		}
		if (rev)
		{
			for (int i = 0; i < len; ++i)
				arr[i] /= len;
			reverse(arr + 1, arr + len);
		}
	}
	vector<double> multiply(vector<double> a, vector<double> b)
	{
		int len = max(a.size(), b.size());
		while (len & (len - 1))
			++len;
		len *= 2;
		int lenp = 0;
		for (; len > (1 << lenp); ++lenp);
		a.resize(len, 0);
		b.resize(len, 0);
		for (int i = 0; i < len; ++i)
			fa[i] = a[i];
		fft(fa, lenp);
		for (int i = 0; i < len; ++i)
			fb[i] = b[i];
		fft(fb, lenp);
		for (int i = 0; i < len; ++i)
			fa[i] *= fb[i];
		fft(fa, lenp, true);
		for (int i = 0; i < len; ++i)
			a[i] = fa[i].real();
		return a;
	}
} fft;
