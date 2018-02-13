#ifndef LINQ_COMPARISON_H
#define LINQ_COMPARISON_H

#include <functional>

#define TEMPLATE template <class T>
#define PREDICATE std::function<bool(T)>

namespace linq{
	namespace utils{
		namespace helperFunctions{
			TEMPLATE
			inline PREDICATE is(const T& ref){
				return [=](T elem){ return elem == ref; };
			}

			TEMPLATE
			inline PREDICATE isNot(const T& ref){
				return [=](T elem){ return elem != ref; };
			}

			TEMPLATE
			inline PREDICATE isGreaterThan(const T& ref){
				return [=](T elem){ return elem > ref; };
			}

			TEMPLATE
			inline PREDICATE isLessThan(const T& ref){
				return [=](T elem){ return elem < ref; };
			}

			TEMPLATE
			inline PREDICATE isGreaterThanOrEqualTo(const T& ref){
				return [=](T elem){ return elem >= ref; };
			}

			TEMPLATE
			inline PREDICATE isLessThanOrEqualTo(const T& ref){
				return [=](T elem){ return elem <= ref; };
			}


			//Compatibility  :  only requires == and <
			TEMPLATE
			inline PREDICATE e(const T& ref){ return is(ref); }

			TEMPLATE
			inline PREDICATE ne(const T& ref){
				return [=](T elem){ return !(elem == ref); };
			}

			TEMPLATE
			inline PREDICATE lt(const T& ref){ return isLessThan(ref); }

			TEMPLATE
			inline PREDICATE gt(const T& ref){
				return [=](T elem){ return ref < elem; };
			}

			TEMPLATE
			inline PREDICATE ge(const T& ref){
				return [=](T elem){ return !(elem < ref); };
			}

			TEMPLATE
			inline PREDICATE le(const T& ref){
				return [=](T elem){ return !(ref < elem); };
			}
		};
	};
};

#undef TEMPLATE
#undef PREDICATE

#endif //LINQ_COMPARISON_H
