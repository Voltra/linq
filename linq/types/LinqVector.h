#ifndef LINQ_LINQVECTOR_H
#define LINQ_LINQVECTOR_H

#include "./LinqContainer.h"
#include <vector>
#include <initializer_list>

#define self LinqVector<T, Allocator>
#define className LinqVector
#define constructor className

namespace linq{
	namespace types{
		template <class T, class Allocator = std::allocator<T>>
		class LinqVector : public LinqContainer<T, Allocator>{
			public:
#define TYPE LinqContainer<T, Allocator>
				using TYPE::value_type;
				using TYPE::allocator_type;
				using TYPE::allocator_traits;
				using TYPE::size_type;
				using TYPE::linq_container_type;
				using TYPE::pointer_type;
				using TYPE::const_pointer_type;
				using TYPE::reference_type;
				using TYPE::const_reference_type;
				using TYPE::rvalue_reference_type;
				using TYPE::iterator;
				using TYPE::const_iterator;
#undef TYPE

				using vector_type = std::vector<T, Allocator>;
				using initializer_list_type = std::initializer_list<T>;

				/*//Pointer types
				using pointer_type = typename vector_type::pointer;
				using const_pointer_type = typename vector_type::const_pointer;

				//Iterator types
				using iterator = typename vector_type::iterator;
				using const_iterator = typename vector_type::const_iterator;*/

				//Member functions
				typename self::allocator_type get_allocator() const override;
				typename self::size_type size() const override;
				typename self::size_type max_size() const override;

				typename self::iterator begin() override;
				typename self::const_iterator begin() const override;
				typename self::const_iterator cbegin() const override;

				typename self::iterator end() override;
				typename self::const_iterator end() const override;
				typename self::const_iterator cend() const override;

				typename self::value_type operator[](const typename self::size_type&) const override;
				typename self::reference_type operator[](const typename self::size_type&) override;
				typename self::value_type at(const typename self::size_type&) const override;
				typename self::reference_type at(const typename self::size_type&) override;

				void push_back(typename self::const_reference_type) override;
				void push_back(typename self::rvalue_reference_type) override;


			public:
				vector_type data = {};

				explicit constructor(const typename self::allocator_type& allocator = typename self::allocator_type{});
				constructor(const initializer_list_type&, const typename self::allocator_type&  allocator = typename self::allocator_type{});
				constructor(const self&);
				self& operator=(const self&) noexcept;
				constructor(const self&, const typename self::allocator_type&);
		};
	};
};

#undef constructor
#undef className
#undef self

#endif //LINQ_LINQVECTOR_H
