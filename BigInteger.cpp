// High Precision (Big Integer) - Competitive Programming Simple Template

namespace BigInteger
{
	// Read string to reversed digit array. Example: "123" -> {3,2,1}
	vector<int> toVec(const string &s)
	{
		vector<int> A;
		for (int i = (int)s.size() - 1; i >= 0; i--)
			A.push_back(s[i] - '0');
		while (A.size() > 1 && A.back() == 0)
			A.pop_back();
		return A;
	}

	// Print reversed digit array.
	void printVec(const vector<int> &A)
	{
		for (int i = (int)A.size() - 1; i >= 0; i--)
			cout << A[i];
	}

	// Compare absolute value: A >= B ?
	bool cmp(const vector<int> &A, const vector<int> &B)
	{
		if (A.size() != B.size())
			return A.size() > B.size();
		for (int i = (int)A.size() - 1; i >= 0; i--)
			if (A[i] != B[i])
				return A[i] > B[i];
		return true;
	}

	// A + B (A,B >= 0)
	vector<int> add(const vector<int> &A, const vector<int> &B)
	{
		if (B.size() > A.size())
			return add(B, A);
		vector<int> C;
		int t = 0;
		for (int i = 0; i < (int)A.size(); i++)
		{
			t += A[i];
			if (i < (int)B.size())
				t += B[i];
			C.push_back(t % 10);
			t = t > 9 ? 1 : 0;
		}
		if (t)
			C.push_back(1);
		return C;
	}

	// A - B (require A >= B, A,B >= 0)
	vector<int> sub(const vector<int> &A, const vector<int> &B)
	{
		vector<int> C;
		int t = 0;
		for (int i = 0; i < (int)A.size(); i++)
		{
			t = A[i] - t;
			if (i < (int)B.size())
				t -= B[i];
			C.push_back((t + 10) % 10);
			t = t < 0 ? 1 : 0;
		}
		while (C.size() > 1 && C.back() == 0)
			C.pop_back();
		return C;
	}

	// A * b (A >= 0, b >= 0)
	vector<int> mul(const vector<int> &A, int b)
	{
		vector<int> C;
		long long t = 0;
		for (int i = 0; i < (int)A.size() || t; i++)
		{
			if (i < (int)A.size())
				t += 1LL * A[i] * b;
			C.push_back((int)(t % 10));
			t /= 10;
		}
		while (C.size() > 1 && C.back() == 0)
			C.pop_back();
		return C;
	}

	// A / b (A >= 0, b > 0), r is remainder
	vector<int> div(const vector<int> &A, int b, int &r)
	{
		vector<int> C;
		r = 0;
		for (int i = (int)A.size() - 1; i >= 0; i--)
		{
			r = r * 10 + A[i];
			C.push_back(r / b);
			r %= b;
		}
		reverse(C.begin(), C.end());
		while (C.size() > 1 && C.back() == 0)
			C.pop_back();
		return C;
	}
}

