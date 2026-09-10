// 高精度非负整数模板：用低位在前的数组保存每一位数字。
namespace BigInteger {
	// 将十进制字符串转成低位在前的数字数组，例如 "123" -> {3,2,1}。
		vector<int> toVec(const string &s) {
			vector<int> A;
			for (int i = (int)s.size() - 1; i >= 0; i--)
				A.push_back(s[i] - '0');
			while (A.size() > 1 && A.back() == 0)
				A.pop_back();
			return A;
		}
		// 按正常的十进制顺序输出低位在前的数字数组。
		void printVec(const vector<int> &A) {
			for (int i = (int)A.size() - 1; i >= 0; i--)
				cout << A[i];
		}
		// 比较两个非负高精度整数，判断 A 是否大于等于 B。
		bool cmp(const vector<int> &A, const vector<int> &B) {
			if (A.size() != B.size()) return A.size() > B.size();
			for (int i = (int)A.size() - 1; i >= 0; i--)
				if (A[i] != B[i]) return A[i] > B[i];
			return true;
		}
		// 计算两个非负高精度整数 A + B。
		vector<int> add(const vector<int> &A, const vector<int> &B) {
			if (B.size() > A.size()) return add(B, A);
			vector<int> C;
			int t = 0;
			for (int i = 0; i < (int)A.size(); i++) {
				t += A[i];
				if (i < (int)B.size()) t += B[i];
				C.push_back(t % 10);
				t = t > 9 ? 1 : 0;
			}
			if (t) C.push_back(1);
			return C;
		}
		// 计算 A - B，要求 A >= B 且 A、B 均为非负数。
		vector<int> sub(const vector<int> &A, const vector<int> &B) {
			vector<int> C;
			int t = 0;
			for (int i = 0; i < (int)A.size(); i++) {
				t = A[i] - t;
				if (i < (int)B.size()) t -= B[i];
				C.push_back((t + 10) % 10);
				t = t < 0 ? 1 : 0;
			}
			while (C.size() > 1 && C.back() == 0)
				C.pop_back();
			return C;
		}
		// 计算非负高精度整数 A 与普通非负整数 b 的乘积。
		vector<int> mul(const vector<int> &A, int b) {
			vector<int> C;
			long long t = 0;
			for (int i = 0; i < (int)A.size() || t; i++) {
				if (i < (int)A.size()) t += 1LL * A[i] * b;
				C.push_back((int)(t % 10));
				t /= 10;
			}
			while (C.size() > 1 && C.back() == 0)
				C.pop_back();
			return C;
		}
		// 计算 A / b，要求 b > 0，并将余数写入 r。
		vector<int> div(const vector<int> &A, int b, int &r) {
			vector<int> C;
			r = 0;
			for (int i = (int)A.size() - 1; i >= 0; i--) {
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
