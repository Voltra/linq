<p align="center"><img src="resources/logo.png" alt="LINQ++ logo" width="300"></p>

## Quick introduction

LINQ++ is a (headers only) C++11 library that aims to emulate the behavior from LINQ in other languages such as C#.

Collection manipulation in C++ is often painful, LINQ++ makes it way easier.



## Features

These are the features that are currently supported :

### Construction (FROM operations)

- `linq::Linqable<T> linq::Linqable<T>::from(It begin, It end)`  : A static method of the class `Linqable` that uses two iterators in order to build the `Linqable` object
- `linq::Linqable<T> linq::from<T>(It begin, It end)` : A utilitary function that calls the above, it is basically syntactic sugar



### Selection/Filtering (WHERE operations)

* `linq::Linqable<T> linq::Linqable<T>::where(Predicate p)` : The method usually used to start the selection sequence (chaining WHERE operations), only the elements that match the predicate `p` (`T => bool`) will be kept
* `linq::Linqable<T> linq::Linqable<T>::orWhere(Predicate p)` : Adds elements from the previous selection that match the given predicate
* `linq::Linqable<T> linq::Linqable<T>::andWhere(Predicate p)` : An alias to `where` usually used after the first (and supposedly only) `where` in order to add an additionnal filter to the current selection
* `linq::Linqable<T> linq::Linqable<T>::andComplexWhere(WhereBuilder wb)` : Used to make selection sub-operations (for instance, in `WHERE a AND (b OR C)`, `(b OR C)` would usually require a sub-operation). `wb` is a function that is `Linqable<T> => Linqable<T>`



### "Special" operations

* `linq::Linqable<T> linq::Linqable<T>::limit(unsigned int n)` : Restricts the current selection to a maximal amount of `n` elements (selects them in their order)
* `linq::Linqable<T> linq::Linqable<T>::unique()` : Removes duplicates from the current selection (packs to set and goes back to `Linqable`)



### Ordering (ORDER BY operations)

* `linq::Linqable<T> linq::Linqable<T>::orderDesc()` : Sorts the currently selected elements in descending order using the `operator>`
* `linq::Linqable<T> linq::Linqable<T>::orderAsc()` : Sorts the currently selected elements in ascending order using the `operator<`
* `linq::Linqable<T> linq::Linqable<T>::orderDescBy(Transformer f)` : Sorts the currently selected elements in ascending order using the transformed elements's (via `f`, `T => E`) `operator>`
* `linq::Linqable<T> linq::Linqable<T>::orderAscBy(Transformer f)` : Sorts the currently selected elements in ascending order using the transformed elements's (via `f`, `T => E`) `operator<`

### Projection (SELECT operations)

* `linq::Linqable<T> linq::Linqable<T>::select()` : Returns `*this`, only used for semantic coherence purposes
* `linq::Linqable<ReturnType> linq::Linqable<T>::select(Mapper mapper)` : Maps the currently selected elements using the given mapper function `mapper` (`T => ReturnType`) and render them available as the current selection
* `linq::Linqable<T> linq::Linqable<T>::selet(Mapper mapper)` : Maps the currently selected elements to elements of the same type and render them available as the current selection
* `ReturnType linq::Linqable<T>::selectReduced(Reducer red, ReturnType acc)` : Reduces the currently selected elements to a single value of the type `ReturnType` based upon the reducer function `red` (`(ReturnType, T) => ReturnType`) and the inital value of the accumulator `acc`

### Packing

I would describe the *packing* operation as the operation of getting to a usual C++ Container (or pointer) from a `Linqable` object : `Linqable` serving only as a way to manipulate your base Container easily.

* `T* linq::Linqable<T>::packToPointer()` : Allocates a pointer of `T` elements from a `Linqable<T>`
* `std::vector<T> linq::Linqable<T>::packToVector()` : Creates a `std::vector<T>` from the currently selected elements of the `Linqable<T>` object
* `std::list<T> linq::Linqable<T>::packToList()` : Creates a `std::list<T>` from the currently selected elements of the `Linqable<T>` object
* `std::set<T> linq::Linqable<T>::packToSet()` : Creates a `std::set<T>` from the currently selected elements of the `Linqable<T>` object
* `std::deque<T> linq::Linqable<T>::packToDeque()` : Creates a `std::deque<T>` from the currently selected elements of the `Linqable<T>` object
* `std::forward_list<T> linq::Linqable<T>::packToForwardList()` : Creates a `std::forward_list<T>` from the currently selected elements of the `Linqable<T>` object. Note that this operation has a bit more overhead than the others due to the fact that insertion in `std::forward_list` is done to the front, so we have to reverse the list to keep the original order



### Utilitaries

LINQ++ comes with a bit of utilitaries function that makes it easier to use (even though some may only be used for the development of this library, eg. `TransformerGreaterThanComparator`).

The base namespace for those is `linq::utils`.

#### Basics

* `Identity<T>` : A struct that is used as a functor for the identity function (`(T a) => a`)
* `identityOf<T>()` : A function that returns the identity function of the given type `T`



#### Helper Functions

Most of those functions are meant to ease the use of WHERE operations by giving support to recurrent operations (With x being the element : `x==n`,`x<n`, `n<x<m`, `x%2==0`, etc...).

The base namespace for those is `linq::utils::helperFunctions`.

Let's have `PREDICATE` designate a function `T => bool` and let's have `T` be the type of the elements in the `Linqable<T>` object.



##### Comparison

* `PREDICATE is(T ref)` : Returns a predicate that is true only when a given `T x` is equal to `ref` using `operator==`
* `PREDICATE isNot(T ref)` : Returns a predicate that is true only when a given `T x` is not equal to `ref` using `operator!=`
* `PREDICATE isGreaterThan(T ref)` : Returns a predicate that is true only when a given `T x` is greater than `ref` using `operator>`
* `PREDICATE isLessThan(T ref)` : Returns a predicate that is true only when a given `T x` is less than `ref` using `operator<`
* `PREDICATE isGreaterThanOrEqualTo(T ref)` : Returns a predicate that is true only when a given `T x` is greater than or equal to `ref` using `operator>=`
* `PREDICATE isLessThanOrEqualTo(T ref)` : Returns a predicate that is true only when a given `T x` is less than or equal to `ref` using `operator<=`



##### Comparison (for maximum compatibility, `operator==` and `operator<` only)

* `PREDICATE e(T ref)` : Alias of `is` (added solely for consistency)
* `PREDICATE ne(T ref)` : Equivalent to `isNot` but using `operator==`
* `PREDICATE lt(T ref)` : Alias of `isLessThan` (added solely for consistency)
* `PREDICATE gt(T ref)` : Equivalent to `isGreaterThan` but using `operator<`
* `PREDICATE le(T ref)` : Equivalent to `isLessThanOrEqualTo` but using `operator<`
* `PREDICATE ge(T ref)` : Equivalent to `isGreaterThanOrEqualTo` but using `operator<`



##### Ranges

* `PREDICATE isBetween(T lhs, T rhs)` : Equivalent to $elem \in [lhs ; rhs]$
* `PREDICATE isInRange(T lhs, T rhs)` : Equivalent to $elem \in [lhs ; rhs[ $
* `PREDICATE isWithin(T lhs, T rhs)` : Equivalent to $elem \in \space]lhs;rhs[ $
* `PREDICATE isInExclusiveRange(T lhs, T rhs)` : Equivalent to $elem \in \space]lhs ; rhs] $



##### Number specifics

* `bool isOdd(T elem)`
* `bool isEven(T elem)`





## General use cases

As we already know, collection manipulation in C++ is not exactly as smooth as it can be in other languages.

LINQ++ tends to simplify collection manipulation operation by offering various ways to operate on a [container](http://www.cplusplus.com/reference/stl/).



The way you would usually process is to pass the `begin` and `end` iterator of your C++ Container as the parameters of `linq::from` (do not forget to specify the type of elements, eg. `linq::from<int>(arr.begin(), arr.end())`) and then chain operations until you are willing to `pack ` them back to a C++ Container.



Let's have an example, shall we ?

```c++
#include "linq/linq.hpp"
#include <vector>
#include <forward_list>

using namespace std;
using namespace linq::utils::helperFunctions;

vector<int> arr = {0,1,2,3,4,5,6,7,8,9};
forward_list<int> linqed = linq::from<int>(arr.begin(), arr.end())
->where(isEven<int>) //I want even numbers only
->orWhere(is(1)) //But if there are any 1s, keep them
->andWhere([](const int& elem)->bool{ return true; }) //Then keep everything from that
->orderDesc() //Order them in descending order
->select() //Optional
->packToForwardList(); //Pack them into a forward_list

for(int elem : linqed)
    cout << elem << " ";
//prints: 8 6 4 2 1 0
```

In SQL, that would roughly be equivalent to (if we have a table `arr` that has `elem` as a column) :

```sql
SELECT elem
FROM arr
WHERE ((MOD(elem, 2)=0 OR elem=1) AND TRUE)
ORDER BY elem DESC
```

Or in C# :

```c#
from elem in arr
where (elem%2==0 || elem==1) && true
orderby elem descending
select elem
```

