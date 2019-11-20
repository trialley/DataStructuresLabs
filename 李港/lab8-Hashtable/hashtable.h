
#include <windows.h>
enum hashtable_err{ hashtable_full };
template<typename K, typename D>
class hashtable {
private:
	typedef struct pair {
		K first;
		D secend;
	}pair;
	pair** table;
	int size;
	int divisor;
	/*MYSQL哈希函数*/
	unsigned int MYSQLhash(K* inkey, int length) const {
		char* key = (char*)inkey;
		register unsigned int nr = 1, nr2 = 4;
		while (length--) {
			nr ^= (((nr & 63) + nr2) * ((unsigned int)(unsigned char)* key++)) + (nr << 8);
			nr2 += 3;
		}
		return((unsigned int)nr);
	}
	/*Daniel J.Bernstein 教授的哈希函数*/
	long DJBHash(K* keyaddr, int length)const {
		long hash = 5381;
		keyaddr = (char*)keyaddr;
		for (int i = 0; i < length; i++) {
			hash = ((hash << 5) + hash) + keyaddr[i];
		}
		return hash;
	}
public:
	hashtable(int indivisor = 960) {
		divisor = indivisor;
		size = 0;
		table = new pair * [divisor];
		for (int i = 0; i < divisor; i++) {
			table[i] = NULL;
		}
	}

	~hashtable() {

	}
	void insert(pair thepair) {
		/*查找关键词*/
		int index = search(thepair.first);

		if (table[index] == NULL) {
			table[index] = new pair(thepair);
			size++;
		}
		else {
			if (table[index]->first == thepair.first) {
				table[index]->secend = thepair.secend;
			}else {
				throw hashtable_full;
			}
		}

	}
	/*根据键值查找下标*/
	int search(K& key) const {
		int i = (int)MYSQLhash(&key, sizeof(key))% divisor;
		int j = i;
		do {
			if (table[j] == NULL || table[j]->first == key) {
				return j;
			}
			else {

			}
			j = (j + 1) % divisor;
		} while (j != i);
		return j;
	}

	D find(K& thekey)const {
		int index = search(thekey);
		if (table[index] == NULL || table[index]->first != thekey) {
			return NULL;
		}
		return table[index]->secend;
	}
	static pair makepair( K k, D d)  {
		pair p;
		p.first = k;
		p.secend = d;
		return p;
	}
	int getlength()const { return size; }
};