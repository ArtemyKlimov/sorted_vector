#ifndef TESTS_CPP
#define TESTS_CPP
#include <iostream>
#include "vector.hpp"
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <ctime>
using std::cout;
using std::endl;
using namespace myspace;

void int_int_vector_test(){
	try{
	srand(time(NULL));
	int key_array[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int value_array[] = {15,25,35,45,55,65,75,85,95,105,115,125,135,145,155};
	myspace::sorted_vector<int, int> int_vec;
	size_t arr_len = (sizeof(key_array)/sizeof(int));
	for(size_t i = 0;i<arr_len; ++i){
		int_vec.insert(key_array[i], value_array[i]);
	}

	int_vec.display();

	assert(arr_len ==int_vec.size());
	assert(int_vec.max_size() > int_vec.size());
	int_vec.reserve(50);
		assert(int_vec.max_size()== 50);
	int_vec.pop_back();
		assert(int_vec.size() == arr_len - 1);
	int_vec.insert(150,340);
	int_vec.insert(150,340);
	int_vec.insert(150,340);
	int_vec.insert(152,340);
	int_vec.insert(152,340);
		size_t const_size = int_vec.size();
	int_vec.insert_unique_key(150,1000);
		assert(int_vec.size() == const_size);
	int_vec.insert_unique_value(120,340);
		assert(int_vec.size() == const_size);
	assert(int_vec.count_key(150)==3);
	assert(int_vec.count_value(340)==5);
	assert(int_vec.count(152,340) ==2);
	int_vec.erase(152);
	assert(int_vec.size() == const_size-2);
	assert(int_vec[4] ==int_vec.at(4));
	int_vec[5] = int_vec[6];
	assert(int_vec[5] == int_vec[6]);
	assert(int_vec[7] != int_vec[6]);
	assert(int_vec.find_value(85));
	//range-based loop:
	int j = 0;
	for(auto&& i: int_vec){
		assert(int_vec[j] == i);
		j++;
	}
	int_vec.clear();
		assert(int_vec.size() == 0);
	}catch(std::logic_error &e){
		throw e;
	}catch(std::bad_alloc const& ba){
		throw ba;
	}catch(...){
		throw;
	}
	
}
void double_char_vector_test(){

	try{
	double key_array[] = {1.8,2.9,3.1,4.2,5.3,6.4,7.5,8.6,9.7,10.8,11.9,12.1,13.2,14.3,15.4};
	char value_array[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','p'};
	myspace::sorted_vector<double, char> double_vec;
		assert(double_vec.max_size() > double_vec.size());
	size_t arr_len = (sizeof(key_array)/sizeof(double));
	for(size_t i = 0;i<arr_len; ++i){
		double_vec.insert(key_array[i], value_array[i]);
	}

		assert(arr_len ==double_vec.size());
	double_vec.reserve(50);
		assert(double_vec.max_size()== 50);
	double_vec.pop_back();
		assert(double_vec.size() == arr_len - 1);
	double_vec.insert(15.3,'s');
	double_vec.insert(15.3,'s');
	double_vec.insert(15.3,'s');
	double_vec.insert(15.4,'s');
	double_vec.insert(15.4,'s');
		size_t const_size = double_vec.size();
	double_vec.insert_unique_key(15.3,'m');
		assert(double_vec.size() == const_size);
	double_vec.insert_unique_value(15.4,'s');
		assert(double_vec.size() == const_size);
		assert(double_vec.count_key(15.3)==3);
	assert(double_vec.count_value('s')==5);
	assert(double_vec.count(15.3,'s') ==3);
	double_vec.erase(15.3);
	assert(double_vec.size() == const_size-3);
	assert(double_vec[4] ==double_vec.at(4));
	double_vec[5] = double_vec[6];
	assert(double_vec[5] == double_vec[6]);
	assert(double_vec[7] != double_vec[6]);
	assert(double_vec.find_value('s'));
	//range-based loop:
	int j = 0;
		for(auto&& i: double_vec){
		assert(double_vec[j] == i);
		j++;
	}
	double_vec.clear();
		assert(double_vec.size() == 0);
	}catch(std::logic_error &e){
		throw e;
	}catch(std::bad_alloc const& ba){
		throw ba;
	}catch(...){
		throw;
	}

}

#endif