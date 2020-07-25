#ifndef LINQ_LINQCONTAINER_H
#define LINQ_LINQCONTAINER_H

#include <type_traits>
#include <memory>
#include <limits>

#define self LinqContainer<T, Allocator>

namespace linq{
	namespace types{

		/**
		 * An abstract class that can be inherited from to guarantee its use with Linqable
		 * @tparam T being the type of the items stored
		 * @tparam Allocator being the allocator type (that could be used)
		 */
		template <class T, class Allocator = std::allocator<T>>
		class LinqContainer{
			public:
				//Basic types
				using value_type = T;
				using allocator_type = Allocator;
				using allocator_traits = std::allocator_traits<allocator_type>;
				using size_type = std::size_t;
				using linq_container_type = LinqContainer<T, Allocator>;

				//Pointer types
				using pointer_type = typename allocator_traits::pointer;
				using const_pointer_type = typename allocator_traits::const_pointer;

				//Reference types
				using reference_type = typename std::add_lvalue_reference<value_type>::type;
				using const_reference_type = const value_type&;
				using rvalue_reference_type = typename std::add_rvalue_reference<value_type>::type;

				//Iterator types
				using iterator = self::pointer_type;//RandomAccessIterator<typename self::value_type>;//typename self::pointer_type;//std::iterator<std::random_access_iterator_tag, typename self::value_type>;
				using const_iterator = RandomAccessIterator<typename std::add_const<typename self::value_type>::type>;//typename self::const_pointer_type; //std::iterator<std::random_access_iterator_tag, typename std::add_const<typename self::value_type>::type>;

				//Member functions
				//////////////////////////////////////////////////////////////////
				//	Allocation and size
				//////////////////////////////////////////////////////////////////
				/**
				 * Retrieve the allocator used by this instance
				 * @return a copy of the allocator used by this instance
				 */
				virtual typename self::allocator_type get_allocator() const = 0;

				/**
				 * Retrieve the current amount of items stored in this LinqContainer
				 * @return the amount of items stored
				 */
				virtual typename self::size_type size() const = 0;

				/**
				 * Retrieve the maximum amount of items that can be stored in this LinqContainer
				 * @return the maximum amount of items that can be stored
				 */
				virtual typename self::size_type max_size() const{ return std::numeric_limits<size_type>::max(); }

				/**
				 * Determines whether or not this LinqContainer contains items
				 * @return TRUE if it does not, FALSE if it does
				 */
				virtual bool empty() const{ return this->size() == 0; }



				//////////////////////////////////////////////////////////////////
				//	Iterators
				//////////////////////////////////////////////////////////////////
				/**
				 * Get an iterator to the beginning of this LinqContainer
				 * @return an iterator to the first element
				 */
				virtual typename self::iterator begin() = 0;

				/**
				 * Get a const_iterator to the beginning of this LinqContainer
				 * @return a const_iterator to the first element
				 */
				virtual typename self::const_iterator begin() const = 0;

				/**
				 * Get a const_iterator to the beginning of this LinqContainer
				 * @return a const_iterator to the first element
				 */
				virtual typename self::const_iterator cbegin() const = 0;

				/**
				 * Get an iterator to the end of this LinqContainer
				 * @return an iterator to the first pointer unit after the last element
				 */
				virtual typename self::iterator end() = 0;

				/**
				 * Get a const_iterator to the end of this LinqContainer
				 * @return a const_iterator to the first pointer unit after the last element
				 */
				virtual typename self::const_iterator end() const = 0;

				/**
				 * Get a const_iterator to the end of this LinqContainer
				 * @return a const_iterator to the first pointer unit after the last element
				 */
				virtual typename self::const_iterator cend() const = 0;



				//////////////////////////////////////////////////////////////////
				//	Access
				//////////////////////////////////////////////////////////////////
				/**
				 * Get a read-only reference to the value at the given index
				 * @param index being the index of the desired value in this LinqContainer
				 * @return a read-only reference to the desired value
				 */
				virtual typename self::value_type operator[](const typename self::size_type& index) const = 0;

				/**
				 * Get a copy of the value at the given index
				 * @param index being the index of the desired value in this LinqContainer
				 * @return a copy the desired value
				 */
				virtual typename self::reference_type operator[](const size_type& index) = 0;

				/**
				 * Get a read-only reference to the value at the given index
				 * @param index being the index of the desired value in this LinqContainer
				 * @return a read-only reference to the desired value
				 */
				virtual typename self::value_type at(const typename self::size_type& index) const = 0;

				/**
				 * Get a copy of the value at the given index
				 * @param index being the index of the desired value in this LinqContainer
				 * @return a copy of the desired value
				 */
				virtual typename self::reference_type at(const typename self::size_type& index) = 0;



				//////////////////////////////////////////////////////////////////
				//	Insertion
				//////////////////////////////////////////////////////////////////
				/**
				 * Add a value to this LinqContainer
				 * @param value being the value to add
				 */
				virtual void push_back(typename self::const_reference_type value) = 0;

				/**
				 * Move a value into this LinqContainer
				 * @param value being the value to move
				 */
				virtual void push_back(typename self::rvalue_reference_type value) = 0;
		};
	};
};

#undef self

#endif //LINQ_LINQCONTAINER_H
