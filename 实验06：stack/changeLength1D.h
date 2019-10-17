#pragma once
#include<cstring>//memcpy
#include<cstdlib>//min
typedef enum{ pointer_is_null, newLength_less_than_zero } changeLength_err;
template<class T>
void changeLength1D ( T*& p, int oldLength, int newLength ) {
	/*错误检查*/
	//新长度小于0则报错
	if ( newLength < 0 ) {
		throw newLength_less_than_zero;
	}
	//指针为空则报错
	if ( p == NULL || p == nullptr ) {
		throw pointer_is_null;
	}

	T* temp = new T[newLength];
	memcpy ( temp, p, min ( oldLength, newLength ) * sizeof(T) );
	delete[] p;
	p = temp;
}