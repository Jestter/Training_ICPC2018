#include <bits/stdc++.h>
using namespace std;

struct RollingHash
{
	string s;
	const long L;
	long long hashValue;
	long ini;
	long end;
	long long base;

	RollingHash(const string &s,long hlength):L(hlength),s(s),ini(0),end(L-1),hashValue(0)
	{
		base = 1;
		for (long i = L-1; i >= 0; --i)
		{
			//hashValue += (s[i])<<((L-1) - i);
			hashValue += s[i] * base;
			if(i!=0)base*=127;
		}
	}

	long long getHashValue(){return hashValue;}

	//returns the next hash value. If the last value is reached, next calls will return the last value.
	long long nextHashValue()
	{
		if(end == s.length()) return hashValue;
		hashValue -= (s[ini]) * base;//<< (L-1);
		hashValue*=127;
		hashValue+= (s[end+1]);
		ini++;
		end++;
		return hashValue;
	}

	void reset()
	{
		hashValue = 0;
		for (long i = 0; i < L; ++i)
		{
			hashValue += (s[i])<<((L-1) - i);
		}
		end = end - ini;
		ini = 0;
	}

	bool finished()
	{
		return end==s.length();
	}
};

int main()
{
	string s1 = "aggg";
	string s2 = "aggtmreaggaggtmreagg";

	RollingHash RH(s1,s1.length());
	long long h1 = RH.getHashValue();

	RollingHash RH2(s2,s1.length());

	long long count = RH2.getHashValue()==h1?1:0;
	while(!RH2.finished())
	{
		if(RH2.nextHashValue()==h1)count++;
	}

	//ocurrences of "agg" in "aggtmreaggaggtmreagg" are 4
	cout << "ocurrences of \""<< s1 << "\" in \""<< s2<< "\" are "<< count << endl;

}