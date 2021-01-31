class fraction
{
#define myabs(x)  ((x<0)?-(x):(x))
	llint a, b;
	void simplify()
	{
		while(b == 0);
		assert(b);
		llint g = __gcd(myabs(a), myabs(b));
		a /= g;
		b /= g;
		if(b < 0)b = -b, a = -a;
	};
public:
	fraction(llint aa = 0, llint bb = 1): a(aa), b(bb)
	{
		assert(b);
		simplify();
	};
	void setValue(llint aa, llint bb)
	{
		a = aa, b = bb;
		assert(b);
		simplify();
	};
	void getValue(llint &aa, llint &bb)
	{
		aa = a, bb = b;
	};
	fraction operator+(const fraction &fb);
	fraction operator+=(const fraction &ff);

	fraction operator-(const fraction &ff);
	fraction operator-=(const fraction &ff);

	fraction operator*(const fraction &ff);
	fraction operator*=(const fraction &ff);

	fraction operator/(const fraction &ff);
	fraction operator/=(const fraction &ff);
	friend bool operator==(const fraction &fa, const fraction &fb)
	{
		return fa.a == fb.a && fa.b == fb.b;
	};
	friend bool operator<(const fraction &fa, const fraction &fb)
	{
		fraction d = fraction(fa) - (fb);
		return d.a < 0;
	};
	friend bool operator>(const fraction &fa, const fraction &fb)
	{
		fraction d = fraction(fa) - fb;
		return d.a > 0;
	};
	friend ostream &operator<<(ostream &out, const fraction &); //{out<<a<<"/"<<b;return out;};
};

ostream &operator<<(ostream &out, const fraction &ff)
{
	out << ff.a << "/" << ff.b;
	return out;
}
fraction fraction::operator+(const fraction &fb)
{
	llint g = __gcd(myabs(b), myabs(fb.b));
	fraction res;
	res.b = b / g * fb.b;
	res.a = a * (fb.b / g) + fb.a * (b / g);
	res.simplify();
	return res;
}
fraction fraction::operator+=(const fraction &fb)
{
	fraction res = (*this) + fb;
	*this = res;
	return *this;
}
fraction fraction::operator-(const fraction &fb)
{
	llint g = __gcd(myabs(b), myabs(fb.b));
	fraction res;
	res.b = b / g * fb.b;
	res.a = a * (fb.b / g) - fb.a * (b / g);
	res.simplify();
	return res;
}
fraction fraction::operator-=(const fraction &fb)
{
	fraction res = (*this) - fb;
	*this = res;
	return *this;
}
fraction fraction::operator*(const fraction &fb)
{
	llint g1 = __gcd(myabs(a), myabs(fb.b));
	llint g2 = __gcd(myabs(fb.a), myabs(b));
	fraction res(a / g1*(fb.a / g2), b / g2*(fb.b / g1));
	res.simplify();
	return res;
}
fraction fraction::operator*=(const fraction &fb)
{
	fraction res = (*this) * fb;
	*this = res;
	return *this;
}
fraction fraction::operator/(const fraction &fb)
{
	while(fb.a == 0);
	llint g1 = __gcd(myabs(a), myabs(fb.a));
	llint g2 = __gcd(myabs(fb.b), myabs(b));
	fraction res(a / g1*(fb.b / g2), b / g2*(fb.a / g1));
	res.simplify();
	return res;
}
fraction fraction::operator/=(const fraction &fb)
{
	fraction res = (*this) / fb;
	*this = res;
	return *this;
}
//******************************************
//  BigInteger
struct BigN
{
	vector<int> dig;
	int sig;
	static const int B = 10000;
	BigN(): sig(0) {};
	void setValue(int a)
	{
		sig = 0;
		if(a < 0)sig = 1, a = -a;
		dig.clear();
		while(a)dig.push_back(a % B), a /= B;
	};
	BigN(int v): sig(0)
	{
		setValue(v);
	};
	void shrink()
	{
		while(dig.size() && dig.back() == 0)dig.pop_back();
		if(dig.empty())sig = 0;
	};
	void operator+=(const BigN &b);
	void operator-=(const BigN &b)
	{
		BigN c = b;
		c.sig ^= 1;
		(*this) += c;
	};
	void operator*=(const BigN &b);
	void operator*=(int v);
	void print(FILE *f = stderr, const char *tail = "")const
	{
		if(sig)fprintf(f, "-");
		if(dig.empty())
		{
			fprintf(f, "0");
			return;
		}
		fprintf(f, "%d", dig.back());
		for(int i = (int)dig.size() - 2; i >= 0; i--)fprintf(f, "%04d", dig[i]);
		fprintf(f, "%s", tail);
	};
};

void add(vector<int>& a, const vector<int>& b, int s = 0)
{
	while(a.size() < b.size() + s)a.push_back(0);
	int c = 0;
	for(int i = 0; i < b.size(); i++)
	{
		a[i+s] += b[i] + c;
		c = a[i+s] / BigN::B;
		a[i+s] %= BigN::B;
	}
	if(c)
	{
		for(int i = b.size() + s; i < a.size(); i++)
		{
			if(a[i] + c < BigN::B)
			{
				a[i] += c, c = 0;
				break;
			}
		}
		if(c)a.push_back(c);
	}
}
void sub(vector<int>& a, const vector<int>& b)
{
	assert(a.size() >= b.size());
	int c = 0;
	for(int i = 0; i < b.size(); i++)
	{
		a[i] -= b[i] + c;
		c = 0;
		if(a[i] < 0)a[i] += BigN::B, c = 1;
	}
	for(int i = b.size(); i < a.size() && c; i++)if(a[i])a[i]--, c = 0;
	assert(c == 0);
	while(a.size() && a.back() == 0)a.pop_back();
}

int cmp(const vector<int>& a, const vector<int>& b)
{
	if(a.size() != b.size())return a.size() - b.size();
	for(int i = (int)a.size() - 1; i >= 0; i--)
		if(a[i] != b[i])return a[i] - b[i];
	return 0;
}
void BigN::operator+=(const BigN &b)
{
	if(sig == b.sig)add(dig, b.dig);
	else if(cmp(dig, b.dig) >= 0)sub(dig, b.dig);
	else
	{
		vector<int> c = b.dig;
		sub(c, dig);
		sig = b.sig;
		dig = c;
	}
	shrink();
}
void BigN::operator*=(int v)
{
	if(v == 0)
	{
		setValue(0);
		return ;
	}
	if(v < 0)v = -v, sig ^= 1;
	assert(v < BigN::B);
	int c = 0;
	for(int i = 0; i < dig.size(); i++)
	{
		dig[i] *= v, dig[i] += c;
		c = dig[i] / B;
		dig[i] %= B;
	}
	if(c)dig.push_back(c);
}
void BigN::operator*=(const BigN &b)
{
	sig ^= b.sig;
	vector<int> all;
	all.swap(dig);
	assert(dig.empty());
	for(int i = 0; i < all.size(); i++)
	{
		BigN tmp = b;
		tmp *= (all[i]);
		add(dig, tmp.dig, i);
	}
	shrink();
}

//*******************************************


