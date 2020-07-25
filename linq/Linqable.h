#ifndef LINQ_LINQABLE_H
#define LINQ_LINQABLE_H

#include <vector>
#include <list>
#include <set>
#include <deque>
#include <forward_list>
#include <functional>
#include "utils/utils.hpp"
#include "types/types.hpp"

#define CONTAINER Container<T>
#define className linq::Linqable
#define self className<T, Container>
#define constructor Linqable
#define destructor ~Linqable

namespace linq{
	/**
	 * A class that allows LINQ expressions/manipulations on a Container/Collection
	 * @tparam T being the type of element the Linqable object operates on
	 */
	template <class T, template <class...> class Container = linq::types::LinqVector>
	class Linqable {
		static_assert(linq::types::isLinqCompatible<Container<T>>::value, "The given container is not linq-compatible");

		public:
			using value_type = T;
			using reference = T&;
			using ref = reference;
			using const_reference = const T&;
			using const_ref = const_reference;
			using pointer = T*;
			using ptr = pointer;
			using const_pointer = const T*;
			using const_ptr = const_pointer;

			using container = CONTAINER;
			using iterator = typename container::iterator;
			using const_iterator = typename container::const_iterator;


			using Predicate = std::function<bool(T)>;
			using WhereBuilder = std::function<self(self)>;
			using SelfMapper = std::function<T(T)>;

		protected:
			/****************************************************************************\
			 * Members
			\****************************************************************************/
			CONTAINER oldOriginals;///< Contains the original elements of the previous iteration/modification of the container
			CONTAINER originals;///< Contains the original elements of this iteration/modification of the container
			CONTAINER currentlySelected;///< Contains the elements currently selected for the next iteration/modification



			/****************************************************************************\
			 * Init members
			\****************************************************************************/
			/**
			 * Empties the container of currently selected elements
			 * @return this
			 */
			self& emptyCurrents();

			/**
			 * Empties the container of the original elements
			 * @return this
			 */
			self& emptyOriginals();

			/**
			 * Empties the container of the previous original elements
			 * @return this
			 */
			self& emptyOldOriginals();

			/**
			 * Retrieves the container of currently selected elements
			 * @return the container of currently selected elements
			 */
			CONTAINER getCurrents() const;

			/**
			 * Retrieves the container of the original elements
			 * @return the container of the original elements
			 */
			CONTAINER getOriginals() const;

			/**
			 * Retrieves the container of the previous original elements
			 * @return the container of the previous original elements
			 */
			CONTAINER getOldOriginals() const;



			/****************************************************************************\
			 * Init empty
			\****************************************************************************/
			/**
			 * Initializes all members to empty containers
			 */
			constructor();



			/****************************************************************************\
			 * AND logic
			\****************************************************************************/
			/**
			 * Swaps containers in order to get the next iteration/modification
			 * @param previous being the previous state (as a const&)
			 * @return a new Linqable that has set to the next iteration/modification
			 */
			static self getNext(const self& previous);

			/**
			 * Swaps containers in order to get the next iteration/modification
			 * @param previous being the previous state (as a pointer)
			 * @return a new Linqable that has set to the next iteration/modification
			 */
			static self getNext(self* previous);


		public:
			/****************************************************************************\
			 * Helpers
			\****************************************************************************/
			/**
			 * Construct a Linqable and initializes its members with the given content
			 * @param content being the base container that the Linqable will operate on
			 * @return a new Linqable
			 */
			static self fromContainer(const CONTAINER& content);

			/****************************************************************************\
			 * Destructor
			\****************************************************************************/
			/**
			 * Destroys the Linqable
			 */
			inline virtual destructor(){}



			/****************************************************************************\
			 * Helpers
			\****************************************************************************/
			/**
			 * Factory function that creates a Linqable from a container (its begin and end iterators)
			 * @tparam It being the type of the container's iterators
			 * @param begin being the iterator to the beginning of the container
			 * @param end being the iterator to the end of the container
			 * @return a Linqable made from the elements contained in the container
			 */
			template <class It>
			static self from(It begin, It end);

			/**
			 * Utilitary operator -> (for consistency in chaining operations)
			 * @return this (const pointer)
			 */
			inline const self* operator->() const{ return this; }

			/**
			 * Utilitary operator -> (for consistency in chaining operations)
			 * @return this (pointer)
			 */
			inline self* operator->(){ return static_cast<self*>(this); }

			/**
			 * Retrieve the amount of element contained in this Linqable
			 * @return the amount of element contained in this Linqable
			 */
			int length() const;

			/**
			 * Retrieve the amount of element contained in this Linqable
			 * @return the amount of element contained in this Linqable
			 */
			int size() const;

			/**
			 * Retrieve the amount of element contained in this Linqable
			 * @return the amount of element contained in this Linqable
			 */
			int count() const;



			/****************************************************************************\
			 * Constructors
			\****************************************************************************/
			/**
			 * Copy constructor (const&)
			 * @param other being the Linqable to copy from
			 */
			constructor(const self& other);

			/**
			 * Copy constructor (const*)
			 * @param other being the Linqable to copy from
			 */
			//constructor(const self* other);



			/****************************************************************************\
			 * Assignment
			\****************************************************************************/
			/**
			 * Copy assignment
			 * @param rhs being the Linqable to copy from
			 * @return this
			 */
			self& operator=(const self& rhs);



			/****************************************************************************\
			 * Operations
			\****************************************************************************/
				/****************************************************************************\
				 * WHERE operations
				\****************************************************************************/
			/**
			 * Filters the Linqable to keep the elements that satisfy the given predicate, uses the currently selected elements
			 * @param predicate being the selection predicate
			 * @return a new filtered Linqable
			 */
			self where(Predicate predicate) const;

			/**
			 * Chain to adds the elements that satisfied the given predicate to this Linqable (no duplicates), uses the original elements
			 * @param predicate being the selection predicate
			 * @return a new Linqable
			 */
			self orWhere(Predicate predicate) const;

			/**
			 * Chain a where selection operation
			 * @param predicate being the selection predicate
			 * @return a new filtered Linqable
			 */
			self andWhere(Predicate predicate) const;

			/**
			 * Subquery to filter this Linqable
			 * @param f being the WhereBuilder
			 * @return a new filtered Linqable
			 */
			self andComplexWhere(WhereBuilder f) const;



				/****************************************************************************\
				 * SELECT operations
				\****************************************************************************/
			/**
			 * Maps the currently selected elements and retrieve them
			 * @tparam Mapper being a function --> T=>ReturnType
			 * @tparam ReturnType being the type of the mapped elements
			 * @param mapper being the mapper function used to map the currently selected elements
			 * @return a new Linqable of mapped elements
			 */
			template <class ReturnType>
			className<ReturnType, Container> select(std::function<ReturnType(T)> mapper) const;

			/**
			 * Maps the currently selected elements to the same type
			 * @param mapper being the mapper function used to map the currently selected elements
			 * @return a new Linqable of mapped elements
			 */
			self select(SelfMapper mapper) const;

			/**
			 * Selects the currently selected elements
			 * @return a new Linqable of selected elements
			 */
			self select() const;

			/**
			 * Reduces the selection to a single value
			 * @tparam ReturnType being the type of the returned value (and accumulator)
			 * @tparam Reducer being a function --> (ReturnType, T)=>ReturnType
			 * @param reducer being the Reducer function to use in order to get the final result
			 * @param acc being the initial value of the accumulator
			 * @return the reduced value
			 */
			template <class ReturnType>
			ReturnType selectReduced(std::function<ReturnType(ReturnType, T)> reducer, const ReturnType& acc) const;



				/****************************************************************************\
				 * ORDER BY operations
				\****************************************************************************/
			/**
			 * Order the elements in ascending order by transforming them and comparing the transformed values (uses operator<)
			 * @tparam Transformer being a function --> T=>E
			 * @param f being a transformer function
			 * @return a new Linqable ordered using the given transformer function
			 */
			template <class Member>
			self orderAscBy(std::function<Member(T)> f) const;

			/**
			 * Order the elements in ascending order without transformation (uses operator<)
			 * @return a new Linqable ordered
			 */
			self orderAsc() const;

			/**
			 * Order the elements in descending order by transforming them and comparing the transformed values (uses operator>)
			 * @tparam Transformer being a function --> T=>E
			 * @param f being a transformer function
			 * @return a new Linqable ordered using the given transformer function
			 */
			template <class Member>
			self orderDescBy(std::function<Member(T)> f) const;

			/**
			 * Order the elements in ascending order without transformation (uses operator>)
			 * @return a new Linqable ordered
			 */
			self orderDesc() const;

				/****************************************************************************\
				 * SPECIAL operations
				\****************************************************************************/
			/**
			 * Limit the amount of elements
			 * @param limit being the maximum of elements
			 * @return a new Linqable that contains a maximum of limit elements
			 */
			self limit(unsigned int limit) const;

			self unique() const;



			/****************************************************************************\
			 * Packing
			\****************************************************************************/
			/**
			 * Packs the elements contained in this Linqable into a pointer
			 * @return the allocated pointer that contains the elements that are in this Linqable
			 */
			T* packToPointer() const;

			/**
			 * Packs the elements contained in this Linqable into a vector
			 * @return the vector that contains the elements that are in this Linqable
			 */
			std::vector<T> packToVector() const;

			/**
			 * Packs the elements contained in this Linqable into a list
			 * @return the list that contains the elements that are in this Linqable
			 */
			std::list<T> packToList() const;

			/**
			 * Packs the elements contained in this Linqable into a set
			 * @return the set that contains the elements that are in this Linqable
			 */
			std::set<T> packToSet() const;

			/**
			 * Packs the elements contained in this Linqable into a deque
			 * @return the deque that contains the elements that are in this Linqable
			 */
			std::deque<T> packToDeque() const;

			/**
			 * Packs the elements contained in this Linqable into a forward_list
			 * @return the forward_list that contains the elements that are in this Linqable
			 */
			std::forward_list<T> packToForwardList() const;



			/****************************************************************************\
			 * Container Concept
			\****************************************************************************/
			/**
			 * Access the element that is located at the given index in this Linqable
			 * @param index being the index of the desired element
			 * @return the desired element
			 */
			T operator[](int index) const;

			typename self::iterator begin();
			typename self::const_iterator begin() const;
			typename self::iterator end();
			typename self::const_iterator end() const;

			typename self::const_iterator cbegin() const;
			typename self::const_iterator cend() const;

			bool operator==(const self& other) const;
			bool operator!=(const self& other) const;

			std::size_t max_size() const;

			bool empty() const;
	};
};

#undef CONTAINER
#undef className
#undef self
#undef constructor
#undef destructor

#include "Linqable.impl.h"

#endif //LINQ_LINQABLE_H
