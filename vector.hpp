#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <memory>
#include <utility>


namespace myspace{


template<typename T, typename U>
struct node{
	T key;
	U value;
	bool operator == (node<T, U> const& src);
	bool operator == (node<T, U>& src);
	bool operator != (node<T, U> const& src);
	bool operator != (node<T, U> & src);
	node<T,U>& operator = (const node<T,U> & src);
};

template<typename T, typename U>
class sorted_vector {
private:
	size_t array_capacity;
	size_t current_size;
	node<T,U>* dynamic_array;
public:
	typedef node<T,U>* Node;
	typedef node<T,U>* iterator;
	typedef node<T,U> const* const_iterator;
	//constructors
	sorted_vector();
	sorted_vector(size_t new_capacity);
	sorted_vector(const sorted_vector& vec);
	sorted_vector(const T& new_key, const U& new_value);
	~sorted_vector();
	//methods
	void insert(const T new_key, const U new_value);
	void display() const;
	bool empty() const;
	void insert_unique_key(const T& key, const U& value);
	void insert_unique_value(const T& key, const U& value);
	bool find_key(const T& new_key) const;
	bool find_value(const T&new_value) const;
	size_t size() const;
	size_t max_size() const;
	size_t count_key(const T& new_key) const;
	size_t count_value(const T& new_value) const;
	size_t count(const T& new_key,const U& new_value) const;
	void reserve(size_t new_cap);
	void clear();
	void erase(const T& key);
	void remove(size_t index);
	node<T,U>& at(size_t index) const;
	node<T,U>& pop_back();
	//operators
	sorted_vector<T, U>& operator = (sorted_vector<T,U>const & src);
	bool operator == (const sorted_vector<T, U>& other_vector);
	bool operator != (const sorted_vector<T, U>& other_vector);
	iterator begin(){return &dynamic_array[0];}
	iterator end(){return &dynamic_array[current_size];}
	const_iterator begin() const{return &dynamic_array[0];}
	const_iterator end() const{return &dynamic_array[current_size];}
	node<T,U>& operator [](size_t i){return dynamic_array[i];}
	const node<T,U>& operator [](size_t i)const {return dynamic_array[i];}
	friend std::ostream& operator<<(std::ostream& os, const node<T,U>& src)
	{
		os<<src.key<<":"<<src.value<<"; ";
		return os;
	}

};
}
#include "vector.cpp"
#endif