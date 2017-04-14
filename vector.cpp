#ifndef vector_cpp
#define vector_cpp
#include <iostream>
#include <stdexcept>
#include <memory>
#include <typeinfo>
#include "vector.hpp"
using namespace myspace;

template<typename T, typename U >
sorted_vector<T,U>::sorted_vector()
	: array_capacity(2)
	, current_size(0)
	, dynamic_array (new node<T,U>[array_capacity]){}

template<typename T, typename U>
sorted_vector<T,U>::sorted_vector(size_t new_capacity)
	: array_capacity(new_capacity)
	, current_size(0)
	, dynamic_array(new node<T,U>[array_capacity]){}

template<typename T, typename U>
sorted_vector<T,U>::sorted_vector(const sorted_vector& vec)
	: array_capacity(vec.array_capacity)
	, current_size(vec.current_size)
	, dynamic_array(new node<T,U>[array_capacity])
{
	for(size_t i = 0; i<current_size; ++i)
	{
		this->dynamic_array[i].key = vec.dynamic_array[i].key;
		this->dynamic_array[i].value = vec.dynamic_array[i].value;
	}
}

template<typename T, typename  U>
sorted_vector<T, U>::sorted_vector(const T& new_key, const U& new_value)
{
	array_capacity = 2;
	current_size = 1;
	dynamic_array(new node<T,U>[array_capacity]);
	dynamic_array.key = new_key;
	dynamic_array.value =new_value;
}

template<typename T, typename U>
sorted_vector<T, U>::~sorted_vector()
{
	delete []dynamic_array;
}

template<typename T, typename U>
void sorted_vector<T, U>::insert(const T new_key, const U new_value)
{
	if(current_size == array_capacity){
		array_capacity *=2;
		node<T,U>* temp;
		try{
			temp = new node<T,U>[array_capacity];
		}catch(std::bad_alloc &ba){
			throw ba;
		}
		for(size_t i = 0; i< current_size;++i){
			temp[i].key = dynamic_array[i].key;
			temp[i].value = dynamic_array[i].value;
		}
		delete [] dynamic_array;
		dynamic_array = temp;
	}
	if(current_size >0){
		for(size_t i= 0; i<current_size; ++i){
			if(dynamic_array[i].key > new_key){
				for(size_t j = current_size; j> i; j--){
					dynamic_array[j].key = dynamic_array[j-1].key;
					dynamic_array[j].value = dynamic_array[j-1].value;
				}
				dynamic_array[i].key=new_key;
				dynamic_array[i].value = new_value;
				current_size++;
				return;
			}
		}
	}
	dynamic_array[current_size].key = new_key;
	dynamic_array[current_size].value = new_value;
	current_size++;
}


template<typename T, typename U>
void sorted_vector<T, U>::display() const
{
	if(current_size == 0){
		std::cout<<"sorted_vector is empty"<<std::endl;
		return;
	}
	for(size_t i = 0; i < current_size; ++i)
	{
		std::cout<<dynamic_array[i].key<<" : "<<dynamic_array[i].value<<"; ";
	}
	std::cout<<std::endl;
}

template<typename T, typename U>
bool sorted_vector<T, U>::empty() const
{
	return current_size == 0;
}

template<typename T, typename U>
void sorted_vector<T, U>::insert_unique_key(const T& key, const U& value)
{
	if(find_key(key))
	{
		//std::cout<<"Element with key "<<key<<" already exists"<<std::endl;
		return;
	}
	insert(key, value);
}

template<typename T, typename U>
void sorted_vector<T, U>::insert_unique_value(const T& key, const U& value)
{
	if(find_value(value))
	{
		//std::cout<<"Element with value "<<value<<" already exists"<<std::endl;
		return;
	}
	insert(key, value);
}

template<typename T, typename U>
bool sorted_vector<T, U>::find_key(const T& new_key) const
{
	if(current_size == 0) return false;
	for(size_t i = 0; i<current_size; i++){
		if(dynamic_array[i].key == new_key)
			return true;
	}
	return false;
}

template<typename T, typename U>
bool sorted_vector<T, U>::find_value(const T&new_value) const
{
	if(current_size == 0) return false;
	for(size_t i = 0; i<current_size; i++){
		if(dynamic_array[i].value == new_value)
			return true;
	}
	return false;
}

template<typename T, typename U>
size_t sorted_vector<T,U>::size() const
{
	return current_size;
}

template<typename T, typename U>
size_t sorted_vector<T, U>::max_size() const
{
	return array_capacity;
}

template<typename T, typename U>
size_t sorted_vector<T, U>::count_key(const T& new_key) const
{
	if(current_size == 0){
		std::cout<<"sorted_vector is empty"<<std::endl;
		return 0;
	}
	size_t count = 0;
	for(size_t i = 0; i<current_size; i++){
		if(dynamic_array[i].key == new_key){
			count++;
		}
	}
	return count;
}

template<typename T,typename U>
size_t sorted_vector<T, U>::count_value(const T& new_value) const
{
	if(current_size == 0){
		std::cout<<"sorted_vector is empty"<<std::endl;
		return 0;
	}
	size_t count = 0;
	for(size_t i = 0; i<current_size; i++)
		if(dynamic_array[i].value == new_value)
			count++;
	return count;
}
template<typename T,typename U>
size_t sorted_vector<T,U>::count(const T& new_key,const U& new_value) const
{
	if(current_size == 0){
		std::cout<<"sorted_vector is empty"<<std::endl;
		return 0;
	}
	size_t count = 0;
	for(size_t i = 0; i<current_size; i++)
		if((dynamic_array[i].key == new_key) && (dynamic_array[i].value == new_value))
			count++;
	return count;
}


template<typename T, typename U>
void sorted_vector<T, U>::reserve(size_t new_cap)
{
	if(new_cap <=current_size){
		throw std::out_of_range("reserve():new_cap is less then current size of given array");
	}
	array_capacity = new_cap;
	node<T,U>* new_array = dynamic_array;
	try{
		dynamic_array = new node<T,U>[array_capacity];
	}catch(std::bad_alloc &ba){
		throw ba;
	}
	for(size_t i = 0; i < current_size; ++i){
		dynamic_array[i].key = new_array[i].key;
		dynamic_array[i].value = new_array[i].value;
	}
	delete [] new_array;
}

template<typename T, typename U>
void sorted_vector<T, U>::clear()
{
	delete [] dynamic_array;
	current_size = 0;
	array_capacity = 2;
	try{
		dynamic_array = new node<T,U>[array_capacity];
	}catch(std::bad_alloc &ba){
		throw ba;
	}
}

template<typename T, typename U>
void sorted_vector<T, U>::erase(const T& key)
{
	if(current_size == 0){
		throw std::out_of_range("erase(): given array is empty");
	}
	for(size_t i = 0;i < current_size; ++i){
		if(dynamic_array[i].key == key){
			remove(i);
			i--;
		}
	}
}

template<typename T, typename U>
void sorted_vector<T, U>::remove(size_t index)
{
	if(index > current_size || index < 0){
		throw std::out_of_range("remove(): uncorrect index");
	}
	//node temp = dynamic_array[index];
	for(size_t i = index; i <current_size; ++i){
		dynamic_array[i] = dynamic_array[i+1];
	}
	current_size--;
}

template<typename T,typename U>
node<T,U>& sorted_vector<T, U>::at(size_t index) const
{
	if(index > current_size || index < 0){
		throw std::out_of_range("at(): uncorrect index");
	}
	else {
		return dynamic_array[index];
	}
}

template<typename T,typename U>
node<T,U>& sorted_vector<T,U>::pop_back()
{
	if(current_size == 0){
		throw std::out_of_range("pop_back():: given array is empty");
	}
	node<T,U>& temp = dynamic_array[current_size -1];
	--current_size;
	return temp;
}

template<typename T, typename U>
bool sorted_vector<T, U>::operator ==(const sorted_vector<T, U>& other){
	if(this->current_size != other.current_size){
		return false;
	}
	for(size_t i = 0; i < current_size; ++i){
		if(dynamic_array[i].key !=other.dynamic_array[i].key || dynamic_array[i].value !=other.dynamic_array[i].value)
			return false;
	}
	return true;
}

template<typename T, typename U>
bool sorted_vector<T, U>::operator != (const sorted_vector<T, U>& other){
	if(this->current_size != other.current_size){
		return true;
	}
	for(size_t i = 0; i < current_size; ++i){
		if(dynamic_array[i] !=other.dynamic_array[i] || dynamic_array[i].value !=other.dynamic_array[i].value)
			return true;
	}
	return false;
}

template<typename T, typename U>
sorted_vector<T,U>& sorted_vector<T, U>::operator = (sorted_vector<T, U> const& src){
	delete[] dynamic_array;
	current_size = src.current_size;
	array_capacity = src.array_capacity;
	try{
		dynamic_array = new node<T,U>[sizeof(node<T,U>) * array_capacity];
	}catch(std::bad_alloc& ba){
		throw ba;
	}
	for(size_t i = 0;i < current_size; ++i){
		dynamic_array[i].key = src.dynamic_array[i].key;
		dynamic_array[i].value = src.dynamic_array[i].value;
	}
	return *this;
}



template<typename T, typename U>
node<T,U>&node<T,U>::operator = (const node<T,U>& src){
	key = src.key;
	value = src.value;
	return *this;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const node<T,U>& src)
{
		os<<src.key<<":"<<src.value<<"; ";
		return os;
}
template<typename T, typename U>
bool node<T,U>::operator == (node<T, U> const& src){
	if(src.key != key || src.value != value) return false;
	return true;
}

template<typename T, typename U>
bool node<T,U>::operator == (node<T, U>& src){
	if(src.key != key || src.value != value) return false;
	return true;
}

template<typename T, typename U>
bool node<T,U>::operator != (node<T, U> & src){
	if(src.key == key && src.value == value) return false;
	return true;
}


template<typename T, typename U>
bool node<T,U>::operator != (node<T, U> const& src){
	if(src.key == key && src.value == value) return false;
	return true;
}

/*
template<typename T, typename U>
typename sorted_vector<T, U>::node<T,U>& operator +(const typename sorted_vector<T, U>::node<T,U>& lhs, const typename sorted_vector<T, U>::node& rhs)
{
	typename sorted_vector<T,U>::node<T,U> new_node;
	new_node.key = lhs.key + rhs.key;
	new_node.value = lhs.value + rhs.value;
	return new_node;
}
template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const typename sorted_vector::node<T,U>& src)
{
	os <<;
	return os;
}
*/


#endif
