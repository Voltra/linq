#ifndef LINQ_NUMBERS_H
#define LINQ_NUMBERS_H

#include <functional>
#include <type_traits>

#define TEMPLATE template <class T, typename = std::enable_if<std::is_integral<T>::value>>

namespace linq{
	namespace utils{
		namespace helperFunctions{
			TEMPLATE
			inline bool isOdd(T elem){ return elem % 2 != 0; }

			TEMPLATE
			inline bool isEven(T elem){ return !isOdd(elem); }
		};
	};
};

#undef TEMPLATE

#endif
