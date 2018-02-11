#ifndef LINQ_LINQABLE_H
#define LINQ_LINQABLE_H

#include <vector>
#include <list>
#include <set>
#include <deque>
#include <forward_list>
#include "utils/utils.hpp"

#define CONTAINER std::vector<T>
#define className linq::Linqable
#define self className<T>
#define constructor Linqable
#define destructor ~Linqable

namespace linq{
	/**
	 * A class that allows LINQ expressions/manipulations on a Container/Collection
	 * @tparam T being the type of element the Linqable object operates on
	 */
	template <class T>
	class Linqable {
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


			/****************************************************************************\
			 * Helpers
			\****************************************************************************/
			/**
			 * Construct a Linqable and initializes its members with the given content
			 * @param content being the base container that the Linqable will operate on
			 * @return a new Linqable
			 */
			static self fromContainer(const CONTAINER& content);

		public:
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
			constructor(const self* other);



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
			 * @tparam Predicate being a type for a predicate function -->  T=>bool
			 * @param predicate being the selection predicate
			 * @return a new filtered Linqable
			 */
			template <class Predicate>
			self where(Predicate predicate) const;

			/**
			 * Chain to adds the elements that satisfied the given predicate to this Linqable (no duplicates), uses the original elements
			 * @tparam Predicate being a type for a predicate function -->  T=>bool
			 * @param predicate being the selection predicate
			 * @return a new Linqable
			 */
			template <class Predicate>
			self orWhere(Predicate predicate) const;

			/**
			 * Chain a where selection operation
			 * @tparam Predicate being a type for a predicate function -->  T=>bool
			 * @param predicate being the selection predicate
			 * @return a new filtered Linqable
			 */
			template <class Predicate>
			self andWhere(Predicate predicate) const;

			/**
			 * Subquery to filter this Linqable
			 * @tparam WhereBuilder being a function --> Linqable<T> => Linqable<T>
			 * @param f being the WhereBuilder
			 * @return a new filtered Linqable
			 */
			template <class WhereBuilder>
			self andComplexWhere(WhereBuilder f) const;



				/****************************************************************************\
				 * SELECT operations
				\****************************************************************************/
			/**
			 * Maps the currently selected elements and retrieve them
			 * @tparam Mapper being a function --> T==>ReturnType
			 * @tparam ReturnType being the type of the mapped elements
			 * @param mapper being the mapper function used to map the currently selected elements
			 * @return a new Linqable of mapped elements
			 */
			template <class Mapper, class ReturnType>
			className<ReturnType> select(Mapper mapper) const;

			/**
			 * Maps the currently selected elements to the same type
			 * @tparam Mapper being a function --> T==>T
			 * @param mapper being the mapper function used to map the currently selected elements
			 * @return a new Linqable of mapped elements
			 */
			template <class Mapper>
			self select(Mapper mapper) const;

			/**
			 * Selects the currently selected elements
			 * @return a new Linqable of selected elements
			 */
			self select() const;



				/****************************************************************************\
				 * ORDER BY operations
				\****************************************************************************/
			/**
			 * Order the elements in ascending order by transforming them and comparing the transformed values (uses operator<)
			 * @tparam Transformer being a function --> T=>E
			 * @param f being a transformer function
			 * @return a new Linqable ordered using the given transformer function
			 */
			template <class Transformer>
			self orderAscBy(Transformer f) const;

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
			template <class Transformer>
			self orderDescBy(Transformer f) const;

			/**
			 * Order the elements in ascending order without transformation (uses operator>)
			 * @return a new Linqable ordered
			 */
			self orderDesc() const;



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

			typename CONTAINER::iterator begin();
			typename CONTAINER::const_iterator begin() const;
			typename CONTAINER::iterator end();
			typename CONTAINER::const_iterator end() const;

			typename CONTAINER::const_iterator cbegin() const;
			typename CONTAINER::const_iterator cend() const;
	};
};

#undef CONTAINER
#undef className
#undef self
#undef constructor
#undef destructor



/******************\
 * Implementation *
\******************/

#define thisNamespace linq
#define utilsNamespace thisNamespace::utils
#define className Linqable
#define thisClass thisNamespace::className
#define self thisClass<T>
#define constructor className

#define TEMPLATE template <class T>
#define ITER_TPL TEMPLATE template <class It>
#define PREDICATE_TPL TEMPLATE template <class Predicate>
#define WHEREBUILDER_TPL TEMPLATE template <class WhereBuilder>
#define MAP_RET_TPL TEMPLATE template <class Mapper, class ReturnType>
#define MAPPER_TPL TEMPLATE template <class Mapper>
#define TRANSFORMER_TPL TEMPLATE template <class Transformer>

#define CONTAINER_OF std::vector
#define CONTAINER CONTAINER_OF<T>

/****************************************************************************\
 * Init members
\****************************************************************************/
TEMPLATE
self& self::emptyCurrents(){
	this->currentlySelected = {};
	return *this;
}

TEMPLATE
self& self::emptyOriginals(){
	this->originals = {};
	return *this;
}

TEMPLATE
self& self::emptyOldOriginals(){
	this->oldOriginals = {};
	return *this;
}

TEMPLATE
CONTAINER self::getCurrents() const{ return {this->currentlySelected}; }

TEMPLATE
CONTAINER self::getOriginals() const{ return {this->originals}; }

TEMPLATE
CONTAINER self::getOldOriginals() const{ return {this->oldOriginals}; }



/****************************************************************************\
 * Init empty
\****************************************************************************/
TEMPLATE
self::constructor(){
	this->emptyOldOriginals()
	.emptyOriginals()
	.emptyCurrents();
}



/****************************************************************************\
 * AND logic
\****************************************************************************/
TEMPLATE
self self::getNext(const self& previous){
	self tmp;

	tmp.oldOriginals = previous.originals;
	tmp.originals = previous.currentlySelected;
	tmp.currentlySelected = previous.currentlySelected;

	return tmp;
}

TEMPLATE
self self::getNext(self* previous){ return self::getNext(*previous); }




/****************************************************************************\
 * Helpers
\****************************************************************************/
TEMPLATE
self self::fromContainer(const CONTAINER& content){
	self tmp;
	tmp.oldOriginals = content;
	tmp.originals = content;
	tmp.currentlySelected = content;
	return tmp;
}


ITER_TPL
self self::from(It begin, It end){
	self tmp;

	for(It it = begin ; it != end ; ++it){
		T elem = static_cast<T>(*it);
		tmp.oldOriginals.push_back(elem);
		tmp.originals.push_back(elem);
		tmp.currentlySelected.push_back(elem);
	}

	return tmp;
}

TEMPLATE
int self::length() const{ return this->currentlySelected.size(); }

TEMPLATE
int self::size() const{ return this->length(); }



/****************************************************************************\
 * Constructors
\****************************************************************************/
TEMPLATE
self::constructor(const self& other) : constructor(){ (*this) = other; }

TEMPLATE
self::constructor(const self* other) : constructor(*other){}



/****************************************************************************\
 * Assignment
\****************************************************************************/
TEMPLATE
self& self::operator=(const self& rhs){
	if(this == &rhs)
		return *this;

	this->oldOriginals = rhs->getOldOriginals();
	this->originals = rhs->getOriginals();
	this->currentlySelected = rhs->getCurrents();

	return *this;
}



/****************************************************************************\
 * Operations
\****************************************************************************/
	/****************************************************************************\
	 * WHERE operations
	\****************************************************************************/
PREDICATE_TPL
self self::where(Predicate predicate) const{
	CONTAINER tmp = {};
	std::copy_if(
		this->begin(),
		this->end(),
		std::back_inserter(tmp),
		predicate
	);

	self thisCopy{this};
	thisCopy.currentlySelected = tmp;
	return self::getNext(thisCopy);
};

PREDICATE_TPL
self self::orWhere(Predicate predicate) const{
	CONTAINER tmp = {};
	std::copy_if(
		this->oldOriginals.begin(),
		this->oldOriginals.end(),
		std::back_inserter(tmp),
		predicate
	);

	self copy{this};

	std::remove_copy_if(
		tmp.begin(),
		tmp.end(),
		std::back_inserter(copy.currentlySelected),
		utilsNamespace::VectorContainsAtIndex<T>(copy.currentlySelected)
	);

	return self(copy);
};

PREDICATE_TPL
self self::andWhere(Predicate predicate) const{ return this->where(predicate); }

WHEREBUILDER_TPL
self self::andComplexWhere(WhereBuilder f) const{
	self built = f(*this);
	/*auto contained = [&](const T& elem){
		return std::find(built.begin(), built.end(), elem) != built.end();
	};*/
	return this->where(utilsNamespace::VectorContainsElem<T>(built.currentlySelected));
}

	/****************************************************************************\
	 * SELECT operations
	\****************************************************************************/
MAP_RET_TPL
thisClass<ReturnType> self::select(Mapper mapper) const{
	CONTAINER_OF<ReturnType> tmp = {};
	std::transform(
		this->begin(),
		this->end(),
		std::back_inserter(tmp),
		mapper
	);

	thisClass<ReturnType> ret;
	ret.currentlySelected = tmp;
	ret.originals = tmp;
	return ret;
}

MAPPER_TPL
self self::select(Mapper mapper) const{
	CONTAINER tmp = {};
	std::transform(
			this->begin(),
			this->end(),
			std::back_inserter(tmp),
			mapper
	);

	self clone{this};
	clone.currentlySelected = tmp;
	return self::getNext(clone);
}

TEMPLATE
self self::select() const{
	return this->select(
		utilsNamespace::identityOf<T>()
	);
}

	/****************************************************************************\
	 * ORDER BY operations
	\****************************************************************************/
TRANSFORMER_TPL
self self::orderAscBy(Transformer f) const{
	self copy{this};
	std::sort(
			copy->begin(),
			copy->end(),
			utilsNamespace::TransformerLessThanComparator<T, Transformer>(f)
	);

	return self(copy);
}

TEMPLATE
self self::orderAsc() const{
	return this->orderAscBy(utilsNamespace::identityOf<T>());
}

TRANSFORMER_TPL
self self::orderDescBy(Transformer f) const{
	self copy{this};

	std::sort(
			copy->begin(),
			copy->end(),
			utilsNamespace::TransformerGreaterThanComparator<T, Transformer>(f)
	);

	return self(copy);
}

TEMPLATE
self self::orderDesc() const{
	return this->orderDescBy(utilsNamespace::identityOf<T>());
}



/****************************************************************************\
 * Container Concept
\****************************************************************************/
TEMPLATE
T* self::packToPointer() const{
	const int size = this->size();
	T* ret = new T[size];

	for(int i = 0 ; i < size ; i+=1)
		ret[i] = this->operator[](i);

	return ret;
}

TEMPLATE
std::vector<T> self::packToVector() const{
	std::vector<T> ret;
	for(T elem : *this)
		ret.push_back(elem);
	return ret;
}

TEMPLATE
std::list<T> self::packToList() const{
	std::list<T> ret;
	for(T elem : *this)
		ret.push_back(elem);
	return ret;
}

TEMPLATE
std::set<T> self::packToSet() const{
	std::set<T> ret;
	for(T elem : *this)
		ret.insert(elem);
	return ret;
}

TEMPLATE
std::deque<T> self::packToDeque() const{
	std::deque<T> ret;
	for(T elem : *this)
		ret.push_back(elem);
	return ret;
}

TEMPLATE
std::forward_list<T> self::packToForwardList() const{
	std::forward_list<T> ret;
	for(T elem : *this)
		ret.push_front(elem);

	ret.reverse();//Keep the order from the Linqable<T>
	return ret;
}



/****************************************************************************\
 * Container Concept
\****************************************************************************/
TEMPLATE
typename CONTAINER::const_iterator self::begin() const{ return this->currentlySelected.begin(); }

TEMPLATE
typename CONTAINER::iterator self::begin(){ return this->currentlySelected.begin(); }

TEMPLATE
typename CONTAINER::const_iterator self::end() const{ return this->currentlySelected.end(); }

TEMPLATE
typename CONTAINER::iterator self::end(){ return this->currentlySelected.end(); }

TEMPLATE
typename CONTAINER::const_iterator self::cbegin() const{ return this->currentlySelected.cbegin(); }

TEMPLATE
typename CONTAINER::const_iterator self::cend() const{ return this->currentlySelected.cend(); }

TEMPLATE
T self::operator[](int index) const{ return this->currentlySelected[index]; }

#undef thisNamespace
#undef utilsNamespace
#undef className
#undef thisClass
#undef self
#undef constructor

#undef TEMPLATE
#undef PREDICATE_TPL
#undef ITER_TPL
#undef WHEREBUILDER_TPL
#undef MAPPER_TPL
#undef MAP_RET_TPL
#undef TRANSFORMER_TPL

#undef CONTAINER_OF
#undef CONTAINER

#endif //LINQ_LINQABLE_H
