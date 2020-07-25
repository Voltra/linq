#ifndef LINQ_ISLINQCOMPATIBLE_H
#define LINQ_ISLINQCOMPATIBLE_H

#include <type_traits>
#include "../utils/sfinae/type_exists.h"

namespace linq{
	namespace types{
		using namespace linq::utils::sfinae;
		using std::enable_if;
		using std::is_default_constructible;
		using std::is_constructible;
		using std::is_copy_constructible;
		using std::is_copy_assignable;
		using std::is_integral;
		using std::is_const;
		using std::is_member_function_pointer;
		using std::is_convertible;
		using std::result_of;
		using std::add_rvalue_reference;
		using std::is_void;
		using std::declval;

		template <class, class = void>
		struct isLinqCompatible : std::false_type{}; //SFINAE

		template<class T>
		struct isLinqCompatible<T, typename enable_if<
				type_exists<typename T::value_type>::value
				&& type_exists<typename T::allocator_type>::value
				&& type_exists<typename T::allocator_traits>::value
				&& type_exists<typename T::size_type>::value
				&& type_exists<typename T::linq_container_type>::value
				&& type_exists<typename T::pointer_type>::value
				&& type_exists<typename T::const_pointer_type>::value
				&& type_exists<typename T::reference_type>::value
				&& type_exists<typename T::const_reference_type>::value
				&& type_exists<typename T::rvalue_reference_type>::value
				&& type_exists<typename T::iterator>::value
				&& type_exists<typename T::const_iterator>::value

				&& is_constructible<T>::value
				&& (is_default_constructible<T>::value
				|| is_constructible<T>::value
				|| is_constructible<T, add_const_ref<typename T::allocator_type>>::value)
				&& is_copy_constructible<T>::value
				&& is_copy_assignable<T>::value

				&& is_integral<typename T::size_type>::value
				&& is_default_constructible<typename T::allocator_type>::value

				&& is_member_function_pointer<decltype(&T::get_allocator)>::value
				&& is_convertible<
					decltype(declval<T>().get_allocator()),
					typename T::allocator_type
				>::value

				&& is_member_function_pointer<decltype(&T::size)>::value
				&& is_convertible<
					decltype(declval<T>().size()),
					typename T::size_type
				>::value

				&& is_member_function_pointer<decltype(&T::max_size)>::value
				&& is_convertible<
					decltype(declval<T>().max_size()),
					typename T::size_type
				>::value

				&& is_member_function_pointer<decltype(&T::empty)>::value
				&& is_convertible<
					decltype(declval<T>().empty()),
					bool
				>::value

				/*&& is_member_function_pointer<decltype(&T::begin)>::value*/
				&& is_convertible<
					decltype(declval<T>().begin()),
					typename T::iterator
				>::value
				&& is_convertible<
					decltype(declval<const T>().begin()),
					typename T::const_iterator
				>::value

				&& is_member_function_pointer<decltype(&T::cbegin)>::value
				&& is_convertible<
					decltype(declval<T>().cbegin()),
					typename T::const_iterator
				>::value

				/*&& is_member_function_pointer<decltype(&T::end)>::value*/
				&& is_convertible<
					decltype(declval<T>().end()),
					typename T::iterator
				>::value
				&& is_convertible<
					decltype(declval<const T>().end()),
					typename T::const_iterator
				>::value

				&& is_member_function_pointer<decltype(&T::cend)>::value
				&& is_convertible<
					decltype(declval<T>().cend()),
					typename T::const_iterator
				>::value

				/*&& is_member_function_pointer<decltype(&T::operator[])>::value*/
				&& is_convertible<
					decltype(declval<T>()[declval<typename add_const_ref<typename T::size_type>::type>()]),
					typename T::reference_type
				>::value
				&& is_convertible<
					decltype(declval<const T>()[declval<typename add_const_ref<typename T::size_type>::type>()]),
					typename T::value_type
				>::value

				/*&& is_member_function_pointer<decltype(&T::at)>::value*/
				&& is_convertible<
					decltype(declval<T>().at(declval<typename add_const_ref<typename T::size_type>::type>())),
					typename T::reference_type
				>::value
				&& is_convertible<
					decltype(declval<const T>().at(declval<typename add_const_ref<typename T::size_type>::type>())),
					typename T::value_type
				>::value

				/*&& is_member_function_pointer<decltype(&T::push_back)>::value*/
				/*&& (is_void<
					result_of<decltype(&T::push_back)(T, typename T::const_reference_type)>
				>::value || is_void<
					result_of<decltype(&T::push_back)(T, typename T::rvalue_reference_type)>
				>::value)*/
				&& is_void<
					decltype(declval<T>().push_back(declval<typename T::const_reference_type>()))
				>::value
				&& is_void<
					decltype(declval<T>().push_back(declval<typename T::rvalue_reference_type>()))
				>::value
		>::type> : std::true_type{};
	};
};

#endif //LINQ_ISLINQCOMPATIBLE_H
