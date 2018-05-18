#include <bits/stdc++.h>

using namespace std;

typedef vector<long long> vi;

#define MAX (1+(1<<6)) // Why? :D
#define inf 0x7fffffff //9223372036854775807 max llong

//st para max queries
class SegmentTree 
{
private:
	int N;
	vi arr;
	long long tree[MAX];
	long long lazy[MAX];

	/**
	 * Build and init tree
	 */
	void build_tree(long long node, long long a, long long b) {
	  	if(a > b) return; // Out of range
	  	
	  	if(a == b) { // Leaf node
	    		tree[node] = arr[a]; // Init value
			return;
		}
		
		build_tree(node*2, a, (a+b)/2); // Init left child
		build_tree(node*2+1, 1+(a+b)/2, b); // Init right child
		
		tree[node] = max(tree[node*2], tree[node*2+1]); // Init root value
	}

	/**
	 * Increment elements within range [i, j] with value value
	 */
	void update_tree(long long node, long long a, long long b, long long i, long long j, long long value) {
	  
	  	if(lazy[node] != 0) { // This node needs to be updated
	   		tree[node] += lazy[node]; // Update it

			if(a != b) {
				lazy[node*2] += lazy[node]; // Mark child as lazy
	    			lazy[node*2+1] += lazy[node]; // Mark child as lazy
			}

	   		lazy[node] = 0; // Reset it
	  	}
	  
		if(a > b || a > j || b < i) // Current segment is not within range [i, j]
			return;
	    
	  	if(a >= i && b <= j) { // Segment is fully within range
	    		tree[node] += value;

			if(a != b) { // Not leaf node
				lazy[node*2] += value;
				lazy[node*2+1] += value;
			}

	    		return;
		}

		update_tree(node*2, a, (a+b)/2, i, j, value); // Updating left child
		update_tree(1+node*2, 1+(a+b)/2, b, i, j, value); // Updating right child

		tree[node] = max(tree[node*2], tree[node*2+1]); // Updating root with max value
	}

	/**
	 * Query tree to get max element value within range [i, j]
	 */
	long long query_tree(long long node, long long a, long long b, long long i, long long j) {
		
		if(a > b || a > j || b < i) return -inf; // Out of range

		if(lazy[node] != 0) { // This node needs to be updated
			tree[node] += lazy[node]; // Update it

			if(a != b) {
				lazy[node*2] += lazy[node]; // Mark child as lazy
				lazy[node*2+1] += lazy[node]; // Mark child as lazy
			}

			lazy[node] = 0; // Reset it
		}

		if(a >= i && b <= j) // Current segment is totally within range [i, j]
			return tree[node];

		long long q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
		long long q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child

		long long res = max(q1, q2); // Return final result
		
		return res;
	}
public:

	SegmentTree(long long N):N(N)
	{
		arr.assign(N,0);
		build_tree(1, 0, N-1);
		memset(lazy, 0, sizeof lazy);
	}
	
	void update(long long i,long long j, long long v)
	{
		update_tree(1, 0, N-1, i, j, v);
	}

	long long rmq(long long i,long long j)
	{
		query_tree(1, 0, N-1, i, j);
	}
};

//st para sum queries
class SegmentTreeSum
{
private:
	int N;
	vi arr;
	long long tree[MAX];
	long long lazy[MAX];

	/**
	 * Build and init tree
	 */
	void build_tree(long long node, long long a, long long b) {
	  	if(a > b) return; // Out of range
	  	
	  	if(a == b) { // Leaf node
	    		tree[node] = arr[a]; // Init value
			return;
		}
		
		build_tree(node*2, a, (a+b)/2); // Init left child
		build_tree(node*2+1, 1+(a+b)/2, b); // Init right child
		
		tree[node] = tree[node*2] + tree[node*2+1]; // Init root value
	}

	/**
	 * Increment elements within range [i, j] with value value
	 */
	void update_tree(long long node, long long a, long long b, long long i, long long j, long long value) {
	  
	  	if(lazy[node] != 0) { // This node needs to be updated
	   		tree[node] += (b-a+1)*lazy[node]; // Update it

			if(a != b) {
				lazy[node*2] += lazy[node]; // Mark child as lazy
	    			lazy[node*2+1] += lazy[node]; // Mark child as lazy
			}

	   		lazy[node] = 0; // Reset it
	  	}
	  
		if(a > b || a > j || b < i) // Current segment is not within range [i, j]
			return;
	    
	  	if(a >= i && b <= j) { // Segment is fully within range
	    		tree[node] += (b-a+1)*value;

			if(a != b) { // Not leaf node
				lazy[node*2] += value;
				lazy[node*2+1] += value;
			}

	    		return;
		}

		update_tree(node*2, a, (a+b)/2, i, j, value); // Updating left child
		update_tree(1+node*2, 1+(a+b)/2, b, i, j, value); // Updating right child

		tree[node] = (tree[node*2] + tree[node*2+1]); // Updating root with max value
	}

	/**
	 * Query tree to get max element value within range [i, j]
	 */
	long long query_tree(long long node, long long a, long long b, long long i, long long j) {
		
		if(a > b || a > j || b < i) return 0; // Out of range

		if(lazy[node] != 0) { // This node needs to be updated
			tree[node] += (b-a+1)*lazy[node]; // Update it

			if(a != b) {
				lazy[node*2] += lazy[node]; // Mark child as lazy
				lazy[node*2+1] += lazy[node]; // Mark child as lazy
			}

			lazy[node] = 0; // Reset it
		}

		if(a >= i && b <= j) // Current segment is totally within range [i, j]
			return tree[node];

		long long q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
		long long q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child

		long long res = (q1 + q2); // Return final result
		
		return res;
	}
public:

	SegmentTreeSum(long long N):N(N)
	{
		arr.assign(N,0);
		build_tree(1, 0, N-1);
		memset(lazy, 0, sizeof lazy);
	}
	
	void update(long long i,long long j, long long v)
	{
		update_tree(1, 0, N-1, i, j, v);
	}

	long long rsq(long long i,long long j)
	{
		return query_tree(1, 0, N-1, i, j);
	}
};

int main()
{
	int N = 20;
	SegmentTree st(N);
	st.update(0, 6, 5); // Increment range [0, 6] by 5. here 0, N-1 represent the current range.
	st.update(7, 10, 12); // Incremenet range [7, 10] by 12. here 0, N-1 represent the current range.
	st.update(11, N-1, 100); // Increment range [10, N-1] by 100. here 0, N-1 represent the current range.

	cout << st.rmq(0, N-1) << endl; // Get max element in range [0, N-1]
	return 0;
}