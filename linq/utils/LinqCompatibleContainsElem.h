#ifndef LINQ_LINQCOMPATIBLECONTAINSELEM_H
#define LINQ_LINQCOMPATIBLECONTAINSELEM_H

#include <algorithm>
#include "../types/types.hpp"

namespace linq{
	namespace utils{
		template <class T, template <class...> class Container>
		struct LinqCompatibleContainsElem{

			static_assert(linq::types::isLinqCompatible<Container<T>>::value, "The given container is not linq-compatible");

			const Container<T>& _seq;

			LinqCompatibleContainsElem(const Container<T>& seq) : _seq(seq){}

			inline bool operator()(const T& elem){
				return _seq.end() != std::find(_seq.begin(), _seq.end(), elem);
			}
		};
	}
}

#endif //LINQ_LINQCOMPATIBLECONTAINSELEM_H
