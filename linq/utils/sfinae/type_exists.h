#ifndef LINQ_TYPE_EXISTS_H
#define LINQ_TYPE_EXISTS_H

#include <type_traits>

namespace linq{
	namespace utils{
		namespace sfinae{
			template <class, class = void>
			struct type_exists : std::false_type{};

			template <class T>
			struct type_exists<T, sfinae::void_t<std::enable_if<
				std::is_same<T, T>::value
			>>> : std::true_type{};
		};
	};
};

#endif //LINQ_TYPE_EXISTS_H
