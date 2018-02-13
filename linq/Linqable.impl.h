#ifdef LINQ_LINQABLE_H

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
#define REDUCER_TPL TEMPLATE template <class ReturnType, class Reducer>

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
//	return this->select(
//		utilsNamespace::identityOf<T>()
//	);
	return *this;
}

REDUCER_TPL
ReturnType self::selectReduced(Reducer reducer, const ReturnType& acc) const{
	ReturnType accumulator = acc;
	for(T elem : *this)
		accumulator = reducer(accumulator, elem);

	return accumulator;
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
	 * SPECIAL operations
	\****************************************************************************/
TEMPLATE
self self::limit(unsigned int limit) const{
	if(this->length() < limit)
		return *this;

	self copy{this};

	if(limit == 0){
		copy.currentlySelected = {};
		return self::getNext(copy);
	}

	CONTAINER newCurrent = {};
	for(unsigned int i = 0 ; i < limit ; i+=1)
		newCurrent.push_back(this->currentlySelected[i]);

	copy.currentlySelected = newCurrent;
	return self::getNext(copy);
}

TEMPLATE
self self::unique() const{
	self copy{this};

	std::set<T> asSet = this->packToSet();
	self unique = self::from(asSet.begin(), asSet.end());
	copy.currentlySelected = unique.currentlySelected;

	//return self::getNext(copy);
	return copy;
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

TEMPLATE
bool self::operator==(const self& other) const{
	return this->oldOriginals == other.getOldOriginals()
	&& this->originals == other.getOriginals()
	&& this->currentlySelected == other.getCurrents();
}

TEMPLATE
bool self::operator!=(const self& other) const{
	return !this->operator==(other);
}

TEMPLATE
std::size_t self::max_size() const{
	return this->currentlySelected.max_size();
}

TEMPLATE
bool self::empty() const{ return this->currentlySelected.empty(); }

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
#undef REDUCER_TPL

#undef CONTAINER_OF
#undef CONTAINER

#endif //LINQ_LINQABLE_IMPL_H
