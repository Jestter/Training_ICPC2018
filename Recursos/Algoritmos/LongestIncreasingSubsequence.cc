// Given a list of numbers of length n, this routine extracts a 
// longest increasing subsequence.
//
// Running time: O(n log n)
//
//   INPUT: a vector of integers
//   OUTPUT: a vector containing the longest increasing subsequence

using namespace std;

typedef vector<int> vi;

vi LIS(vi v)
{
   	vi p(v.size(),-1); //parents
   	vi m(v.size()+1,0); //increasing ordered list
   	int l = 0;

   	for (int i = 0; i < v.size(); ++i)
   	{
   		int lo=1,hi=l;

   		while(lo <= hi)
   		{
   			int mid = ceil((lo+hi)/2);
			if( v[m[mid]] < v[i]) lo = mid+1;
			else hi = mid-1;
   		}
   		int newL = lo;
   		p[i] = m[newL-1];
   		m[newL] = i;

   		l = max(newL,l);
   	}
   	vi s(l,0);
   	int k = m[l];
   	for (int i = l-1; i >=0; --i)
   	{
   		s[i] = v[k];
   		k = p[k];
   	}

    return s; //return longest increasing subsequence
}