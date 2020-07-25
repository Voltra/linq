#ifndef LINQ_ADD_CONST_REF_H
#define LINQ_ADD_CONST_REF_H

#include <type_traits>

namespace linq{
	namespace utils{
		namespace sfinae{
			template <class T>
			struct add_const_ref : std::add_lvalue_reference<
				typename std::add_const<T>::type
			>{};
		};
	};
};

#endif //LINQ_ADD_CONST_REF_H
