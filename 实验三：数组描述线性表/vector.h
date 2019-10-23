/*****************************************************************************
*  @brief    vector类的简单实现                                               *
*  @author   TriAlley                                                        *
*  @email    lg139@139.com                                                   *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*  2019/09/26 | 1.0       | TriAlley       | Create file                     *
*****************************************************************************/
#pragma once
#include<cstring>		//memset、memcpy
#include<cstdlib>		//malloc
/*常见错误的枚举*/
enum err { index_out_of_range }err;

/**
 * @brief vector类
 * private:
 *    T* head;           //内容数组头指针
 *    int maxindex;		 //指示index的最大值
 *    int frontindex;    //指向第一个空闲位置
 *    void __exlength()；//私有函数，提供将数组长度成两倍的功能
 *
 * public:
 *    vector();                                   //构造函数，参数为初始长度，默认为50
 *    ~vector();                                  //析构函数，释放构造函数申请的内存资源
 *    T& operator [] (int i);                     //重载方括号[]
 *    void push(T in);                            //push
 *    void del(int i);                            //根据下标删除元素
 *    void insert(int i, T in);                   //将元素插入到下标位置，其余元素后移
 *    int find(T target);                         //查找元素，返回下标，查找失败返回-1
 *    int getlength() { return frontindex; }      //返回数组元素数量
 *    int getmaxlength() { return maxindex + 1; } //返回数组最大长度
 */
template<typename T>
class vector {
protected:
	T* head;		//the array head pointer
	int maxindex;		//the length-1 of array
	int frontindex;
	void __exlength () {
		T* newhead = new T[( maxindex + 1 ) * 2];
		memcpy ( newhead, head, sizeof ( T ) * ( maxindex + 1 ) );

		maxindex = maxindex * 2 + 1;

		delete[] head;
		head = newhead;
	}
public:
	friend class vectoritreator;
	class vectoritreator {
	public:
		vectoritreator ( vector* ivec, int thePosition = 0 ) {
			index = thePosition;
			vec = ivec;
		}

		T& operator*() const {
			return ( vec->head )[index];
		}
		//T* operator->() const { return &*index; }

		/*加法操作*/
		vectoritreator& operator++() {
			++index;
			return *this;
		}
		vectoritreator operator++( int ) {
			vectoritreator old = *this;
			++index;
			return old;
		}
		vectoritreator operator+( int n ) {
			index += n;
			return *this;
		}

		/*减法操作*/
		vectoritreator& operator--() { --index; return *this; }
		vectoritreator operator--( int ) {
			vectoritreator old = *this;
			--index;
			return old;
		}
		vectoritreator operator-( int n ) {
			index -= n;
			return *this;
		}
		void clear () {
			frontindex = -1;
		}
		/*逻辑判断*/
		bool operator!=( const vectoritreator right ) const { return index != right.index; }
		bool operator==( const vectoritreator right ) const { return index == right.index; }
	protected:
		int index;
		vector* vec;
	};

	vector ( int n = 50 ) {
		maxindex = n - 1;
		frontindex = 0;

		head = new T[n];
		memset ( head, 0, sizeof ( T ) * n );
	}

	~vector () {
		delete[] head;
	}
	void clear ( int n = 50 ) {
		delete[] head;

		maxindex = n - 1;
		frontindex = 0;

		head = new T[n];
		memset ( head, 0, sizeof ( T ) * n );
	}

	T& operator [] ( int i ) {
		if ( i >= frontindex ) {
			throw index_out_of_range;
		}

		return head[i];
	}

	T get ( int i ) const {
		if ( i >= frontindex ) {
			throw index_out_of_range;
		}

		return head[i];
	}
	void push ( T in ) {
		if ( frontindex == maxindex ) {
			__exlength ();
		}

		head[frontindex++] = in;
	}
	void del ( int i ) {
		if ( i >= frontindex ) {
			//err= index_out_of_range
			throw index_out_of_range;
		}

		for ( int j = i; j < frontindex; j++ ) {
			head[j] = head[j + 1];
		}

		frontindex--;

	}
	void insert ( int i, T in ) {
		if ( i > frontindex ) {
			throw index_out_of_range;
		}

		//判断后移是否越界
		if ( frontindex + 1 > maxindex ) {
			__exlength ();
		}
		//向后复制时需要总尾开始，否则第一个元素将会覆盖全部
		for ( int j = frontindex; j >= i; j-- ) {
			head[j + 1] = head[j];
		}

		head[i] = in;
		frontindex++;
	}
	int find ( T target ) {
		for ( int i = 0; i <= frontindex; i++ ) {
			if ( head[i] == target ) {
				return i;
			}
		}
		return -1;
	}
	int getlength ()const { return frontindex; }
	int getmaxlength () const { return maxindex + 1; }

	vectoritreator begin () { return vectoritreator ( this, 0 ); }
	vectoritreator end () { return vectoritreator ( this, maxindex ); }
};