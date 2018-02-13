#ifndef LINQ_NUMERICRANGE_H
#define LINQ_NUMERICRANGE_H

#include <functional>

#define TEMPLATE template <class T>
#define PREDICATE std::function<bool(T)>

namespace linq{
	namespace utils{
		namespace helperFunctions{
			TEMPLATE
			inline PREDICATE isBetween(const T& lhs, const T& rhs){
				return [=](T elem){ return lhs <= elem && elem <= rhs; };
			}

			TEMPLATE
			inline PREDICATE isInRange(const T& lhs, const T& rhs){
				return [=](T elem){ return lhs <= elem && elem < rhs; };
			}

			TEMPLATE
			inline PREDICATE isWithin(const T& lhs, const T& rhs){
				return [=](T elem){ return lhs < elem && elem < rhs; };
			}

			TEMPLATE
			inline PREDICATE isInExclusiveRange(const T& lhs, const T& rhs){
				return [=](T elem){ return lhs < elem && elem <= rhs; };
			}
		};
	};
};

#undef TEMPLATE
#undef PREDICATE

#endif //LINQ_NUMERICRANGE_H
