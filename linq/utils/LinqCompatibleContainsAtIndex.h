#ifndef LINQ_LINQCOMPATIBLECONTAINSATINDEX_H
#define LINQ_LINQCOMPATIBLECONTAINSATINDEX_H

#include <algorithm>
#include "../types/types.hpp"

namespace linq{
	namespace utils{
		template <class Container>
		struct LinqCompatibleContainsAtIndex{
			static_assert(linq::types::isLinqCompatible<Container>::value, "The given container is not linq-compatible");

			const Container& _seq;

			inline LinqCompatibleContainsAtIndex(const Container& seq) : _seq{seq} {
			}

			inline bool operator()(int i) const{
				return _seq.end() != std::find(_seq.begin(), _seq.end(), i);
			}
		};
	}
}

#endif //LINQ_LINQCOMPATIBLECONTAINSATINDEX_H
