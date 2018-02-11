#ifndef LINQ_VECTORCONTAINSATINDEX_H
#define LINQ_VECTORCONTAINSATINDEX_H

#include <vector>
#include <algorithm>

namespace linq{
	namespace utils{
		/**
		 * A utilitary struct that is used to determine whether or not there's an element at a given index of vector
		 * @tparam T being the type of the elements of the given vector
		 */
		template <class T>
		struct VectorContainsAtIndex{
			const std::vector<T>& _sequence;
			inline VectorContainsAtIndex(const std::vector<T>& vec) : _sequence(vec) {}
			/**
			 * Determines whether or not there's an element at the given index
			 * @param i being the index
			 * @return TRUE if there's one, FALSE otherwise
			 */
			inline bool operator()(int i) const{
				return _sequence.end() != std::find(_sequence.begin(), _sequence.end(), i);
			}
		};
	};
};

#endif //LINQ_VECTORCONTAINSATINDEX_H
