#ifndef LINQ_LINQVECTOR_IMPL_H
#define LINQ_LINQVECTOR_IMPL_H

#include "./LinqVector.h"
#include <utility>

#define TEMPLATE template<class T, class Allocator>
#define thisNamespace linq::types
#define className LinqVector<T, Allocator>
#define self thisNamespace::className
#define constructor LinqVector

//Constructors and copy assignment
TEMPLATE
self::constructor(const typename self::allocator_type& allocator) : data{allocator} {
}

TEMPLATE
self::constructor(const self::initializer_list_type& initializer_list, const typename self::allocator_type& allocator) : data{initializer_list, allocator} {
}

TEMPLATE
self::constructor(const self& rhs){
	(*this) = rhs;
}

TEMPLATE
self& self::operator=(const self& rhs) noexcept{
	this->data = rhs.data;
}

TEMPLATE
self::constructor(const self& other, const typename self::allocator_type& allocator){
	this->data = typename self::vector_type{other.data, allocator};
}


TEMPLATE
typename self::allocator_type self::get_allocator() const{
	return this->data.get_allocator();
}

//Size operations
TEMPLATE
typename self::size_type self::size() const{
	return this->data.size();
}

TEMPLATE
typename self::size_type self::max_size() const{
	return this->data.max_size();
}



//Iterators
TEMPLATE
typename self::iterator self::begin(){
	//return this->data.begin();
	typename self::vector_type::iterator it = this->data.begin();
	return &(*it);
}

TEMPLATE
typename self::const_iterator self::begin() const{
	//return this->data.begin();
	typename self::vector_type::const_iterator cit = this->data.begin();
	return &(*cit);
}

TEMPLATE
typename self::const_iterator self::cbegin() const{
	//return this->data.cbegin();
	typename self::vector_type::const_iterator cit = this->data.cbegin();
	return &(*cit);
}

TEMPLATE
typename self::iterator self::end(){
//	return this->data.end();
	typename self::vector_type::iterator it = this->data.end();
	return &(*it);
}

TEMPLATE
typename self::const_iterator self::end() const{
//	return this->data.end();
	typename self::vector_type::const_iterator cit = this->data.end();
	return &(*cit);
}

TEMPLATE
typename self::const_iterator self::cend() const{
//	return this->data.cend();
	typename self::vector_type::const_iterator cit = this->data.cend();
	return &(*cit);
}



//Data access
TEMPLATE
typename self::value_type self::operator[](const typename self::size_type& index) const{
	return this->data.at(index);
}

TEMPLATE
typename self::reference_type self::operator[](const typename self::size_type& index){
	return this->data.at(index);
}

TEMPLATE
typename self::value_type self::at(const typename self::size_type& index) const{
	return this->operator[](index);
}

TEMPLATE
typename self::reference_type self::at(const typename self::size_type& index){
	return this->operator[](index);
}


//Push data
TEMPLATE
void self::push_back(typename self::const_reference_type data) {
	this->data.push_back(data);
}

TEMPLATE
void self::push_back(typename self::rvalue_reference_type data){
	this->data.push_back(std::move(data));
}

#undef constructor
#undef self
#undef className
#undef thisNamespace
#undef TEMPLATE

#endif //LINQ_LINQVECTOR_IMPL_H
