#include<iostream>
#include<algorithm>
#include <vector>
using namespace std;
vector<int> a{1, 7, 6, 3, 12, 6, 4, 12, 6, 56, 56, 23, 45, 45, 4, 5, 345, 345, 3, 364545, 57, 56};
int b[10005];

template<typename T, typename = void> struct is_iterable : false_type {};
template<typename T> struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};
template<typename T> typename enable_if<is_iterable<T>::value && !is_same<T, string>::value, ostream&>::type operator<<(ostream& cout, T const& v);
template<typename T> typename enable_if<is_iterable<T>::value && !is_same<T, string>::value, ostream&>::type operator<<(ostream& cout, T const& v) {
	cout << "[";
	for (auto it = v.begin(); it != v.end();) {
		cout << *it;
		if (++it != v.end()) cout << ", ";
	}
	return cout << "]";
}
template<typename A, typename B> ostream& operator<<(ostream& cout, pair<A, B> const& p) { return cout << "(" << p.first << ", " << p.second << ")"; }
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B>& p) {
	cin >> p.first;
	return cin >> p.second;
}

void merge(int low, int mid, int high) {
	int h = low, i = low, j = mid + 1;
	int k;
	while (h <= mid && j <= high) {
		if (a[h] <= a[j]) {
			b[i] = a[h];
			h++;
		}
		else {
			b[i] = a[j];
			j++;
		}
		i++;
	}
	if (h > mid) {
		for (k = j; k <= high;k++) {
			b[i] = a[k];
			i++;
		}
	}
	else {
		for (k = h; k <= mid; k++) {
			b[i] = a[k];
			i++;
		}
	}
	for (k = low; k <= high; k++) a[k] = b[k];
}

void mergesort(int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		mergesort(low, mid);
		mergesort(mid + 1, high);
		merge(low, mid, high);
	}
}

int main() {
	int n = a.size();
	mergesort(0, n-1);
	cout << a;

}