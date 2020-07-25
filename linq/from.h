#ifndef LINQ_FROM_H
#define LINQ_FROM_H

#include "Linqable.h"
#include "types/types.hpp"

namespace linq{
	/**
	 * Factory function that creates a Linqable from a container (its begin and end iterators)
	 * @tparam T being the type of the element of the container
	 * @tparam It being the type of the container's iterators
	 * @param begin being the iterator to the beginning of the container
	 * @param end being the iterator to the end of the container
	 * @return a Linqable made from the elements contained in the container
	 */
	template <class T, class It, template <class...> class Container = linq::types::LinqVector>
	inline Linqable<T, Container> from(It begin, It end){
		static_assert(linq::types::isLinqCompatible<Container<T>>::value, "The given container is not linq-compatible");
		return Linqable<T, Container>::from(begin, end);
	};
};

#endif //LINQ_FROM_H
