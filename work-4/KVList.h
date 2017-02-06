#pragma once
namespace w4 {
	template<typename K, typename V, int N>
	class KVList {
		size_t count;
		K k[N];
		V v[N];
		public:
			KVList() : count(0) {}

			//returns the number of entires in the key - value list
			size_t size() const {
				return count;
			}

			//returns an unmodifiable reference to the key of element i in the list
			const K& key(int i) const {
				if (i >= 0 && i < count) {
					return k[i];
				}
				return k[count];
			};

			//returns an unmodifiable reference to the value of element i in the list
			const V& value(int i) const {
				if (i >= 0 && i < count) {
					return v[i];
				}
				return v[count];
			};

			// 1 - adds a new element to the list if room exists and returns a reference to the current object;
			// 2 - does nothing if no room exists;
			KVList& add(const K& kk, const V& vv) {
				if (count >= 0 && count < N) {
					k[count] = kk;
					v[count] = vv;
					count++;
					return *this;
				}
			};

			// 1 - returns the index of the first element in the list with a key equal to k - defaults to 0
			// 2 - returns -1 if nothing was found;
			int find(const K& kk) const {
				for (size_t i = 0; i < count; i++) {
					if (k[i] == kk) {
						return i;
					}
				}
				return -1;
			};

			// 1 - replaces element i in the list with the key and value received; 
			// 2 - returns a reference to the current object;
			KVList& replace(int i, const K& kk, const V& vv) {
				if (i >= 0 && i < count) {
					k[i] = kk;
					v[i] = vv;
				}
				return *this;
			};
	};
}