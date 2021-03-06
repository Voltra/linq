#ifndef LINQ_CPP_TRANSFORMERGREATERTHANCOMPARATOR_H
#define LINQ_CPP_TRANSFORMERGREATERTHANCOMPARATOR_H

namespace linq{
	namespace utils{
		/**
		 * A general purpose comparator using a transformer function and operator>
		 * @tparam T being the type of the element to compare
		 * @tparam Transformer being the transformer function type
		 */
		template <class T, class Transformer>
		struct TransformerGreaterThanComparator{
			const Transformer f;
			TransformerGreaterThanComparator(Transformer f) : f(f){}
			/**
			 * Determines whether or not lhs > rhs
			 * @param lhs being the left hand side value of the comparison expression
			 * @param rhs being the right hand side value of the comparison expression
			 * @return TRUE if lhs > rhs, FALSE otherwise
			 */
			inline bool operator()(const T& lhs, const T& rhs){ return f(lhs) > f(rhs); }
		};
	};
};

#endif //LINQ_CPP_TRANSFORMERGREATERTHANCOMPARATOR_H
