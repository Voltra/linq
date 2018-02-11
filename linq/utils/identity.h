#ifndef LINQ_CPP_IDENTITY_H
#define LINQ_CPP_IDENTITY_H

namespace linq{
	namespace utils{
		/**
		 * A struct that serves as an identity function factory
		 * @tparam T being the type of elements that will be passed to the identity function
		 */
		template <class T>
		struct Identity{
			/**
			 *The identity function for the type T
			 * @param t being the element passed to the function (const T&)
			 * @return the same element that was passed to the function (T)
			 */
			inline T operator()(const T& t) const{ return t; }

			/**An helper member funciton that creates an identity function for the given type
			 * @return the identity function for T
			 */
			inline static Identity<T> get(){ return Identity<T>{}; }
		};

		/**
		 * A function that creates an identity function for the type given
		 * @tparam T being the type of element for this identity function
		 * @return the crafted identity function for the given type T
		 */
		template <class T>
		inline Identity<T> identityOf(){ return Identity<T>::get(); }
	};
};

#endif //LINQ_CPP_IDENTITY_H
