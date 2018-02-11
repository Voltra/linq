<img src="resources/logo.png" alt="LINQ++ logo" width="300" style="display: block; margin: auto;">

## Presentation

LINQ++ is a C++11 library that aims to emulate the behavior from LINQ in other languages such as C#.



## Features

These are the features that are currently supported :

* from<br/><br/>


* where

* orWhere

* andWhere

* andComplexWhere

* orderAscBy

* orderAsc

* orderDescBy

* orderDesc

* select<br/>

  <br/>

* packToPointer

* packToVector

* packToList

* packToSet

* packToDeque

* packToForwardList



## General use cases

As we already know, collection manipulation in C++ is not exactly as smooth as it can be in other languages.

LINQ++ tends to simplify collection manipulation operation by offering various ways to operate on a [container](http://www.cplusplus.com/reference/stl/).



The way you would usually process is to pass the `begin` and `end` iterator of your C++ Container as the parameters of `linq::from` (do not forget to specify the type of elements, eg. `linq::from<int>(arr.begin(), arr.end())`) and then chain operations until you are willing to `pack ` them back to a C++ Container.



Let's have an example, shall we (cf. `playground.cpp`) ?

```c++
#include "linq/linq.hpp"

vector<int> arr = {0,1,2,3,4,5,6,7,8,9};
forward_list<int> linqed = linq::from<int>(arr.begin(), arr.end())
->where([](const int& elem)->bool{ return elem % 2 == 0; }) //I want even numbers only
->orWhere([](const int& elem)->bool{ return elem == 1; }) //But if there are any 1s, keep them
->andWhere([](const int& elem)->bool{ return true; }) //Then keep everything from that
->orderDesc() //Order them in descending order
->select() //usually optional
->packToForwardList(); //Pack them

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

