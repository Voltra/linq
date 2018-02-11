#ifndef LINQ_CPP_VECTORCONTAINSELEM_H
#define LINQ_CPP_VECTORCONTAINSELEM_H

#include <vector>
#include <algorithm>

namespace linq{
	namespace utils{
		/**
		 * A utilitary struct that is used to determine whether or not a vector contains a given element
		 * @tparam T being the type of the elements of the given vector
		 */
		template <class T>
		struct VectorContainsElem{
			const std::vector<T>& _sequence;
			VectorContainsElem(const std::vector<T>& vec) : _sequence(vec) {}
			/**
			 * Determines whether or not the given element is in the vector
			 * @param elem being the element to look for
			 * @return TRUE if the vector contains the given element, FALSE otherwise
			 */
			inline bool operator()(const T& elem) const{
				return _sequence.end() != std::find(_sequence.begin(), _sequence.end(), elem);
			}
		};
	};
};

#endif //LINQ_CPP_VECTORCONTAINSELEM_H
