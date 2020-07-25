#ifndef LINQ_VOID_T_H
#define LINQ_VOID_T_H

namespace linq{
	namespace utils{
		namespace sfinae{
			template <class...>
			using void_t = void;
		};
	};
};

#endif //LINQ_VOID_T_H
