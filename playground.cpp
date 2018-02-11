#include <iostream>
#include <vector>
#include <set>
#include <forward_list>
#include "linq/linq.hpp"

using namespace std;

void testLinqable();
void testLinqable2();
void testLinqable3();

int main() {
//	testLinqable();
//	testLinqable2();
//	testLinqable3();
	return 0;
}


void testLinqable(){
	vector<int> arr = {0,1,2,3,4,5,6,7,8,9};
	forward_list<int> linqed = linq::from<int>(arr.begin(), arr.end())
	->where([](const int& elem)->bool{ return elem % 2 == 0; })
	->orWhere([](const int& elem)->bool{ return elem == 1; })
	->andWhere([](const int& elem)->bool{ return true; })
	->orderDesc()
	->select()
	->packToForwardList();

	/********************\
	 * Equivalent:
	 *
	 * //SQL-ish
	 * SELECT elem
	 * FROM arr
	 * WHERE ((elem%2=0 OR elem=1) AND true)
	 * ORDER BY elem DESC
	 *
	 * //C#
	 * from elem in arr
	 * where (elem%2==0 || elem==1) && true
	 * orderby elem descending
	 * select elem
	 *
	 * //Expected result
	 * {0,1,2,3,4,5,6,7,8,9} => {0,1,2,4,6,8} or (8,6,4,2,1,0)
	\********************/

	for(int i : linqed)
		cout << i << ' ';
	cout << '\n';
}

void testLinqable2(){
	vector<int> arr = {0,1,2,3,4,5,6,7,8,9};
	set<int> linqed = linq::from<int>(arr.begin(), arr.end())
	->where([](const int& elem)->bool{ return elem % 2 == 0; })
	->orWhere([](const int& elem)->bool{ return elem == 1; })
	->andWhere([](const int& elem)->bool{ return true; })
	->andComplexWhere([](const linq::Linqable<int>& builder){
		return builder->where([](const int& elem){ return elem > 4; })
		->orWhere([](const int& elem){ return elem <= 2; });
	})->orderDesc()
	->select()
	->packToSet();

	/********************\
	 * Equivalent:
	 *
	 * //SQL-ish
	 * SELECT elem
	 * FROM arr
	 * WHERE ((elem%2=0 OR elem=1) AND true AND (elem > 4 OR elem <= 2))
	 * ORDER BY elem DESC
	 *
	 * //C#
	 * from elem in arr
	 * where (elem%2==0 || elem==1) && true && (elem>4 || elem <=2)
	 * orderby elem descending
	 * select elem
	 *
	 * //Expected result
	 * {0,1,2,3,4,5,6,7,8,9} => {0,1,2,6,8} or (8,6,2,1,0)
	\********************/

	for(int i : linqed)
		cout << i << ' ';
	cout << '\n';
}

void testLinqable3(){
	vector<int> arr = {0,1,2,3,4,5,6,7,8,9};
	set<int> linqed = linq::from<int>(arr.begin(), arr.end())
	->where([](const int& elem)->bool{ return elem % 2 == 0; })
	->orWhere([](const int& elem)->bool{ return elem == 1; })
	->andWhere([](const int& elem)->bool{ return true; })
	->andWhere([](const int& elem){ return elem > 4; })
	->orWhere([](const int& elem){ return elem <= 2; })
	->orderDesc()
	->select()
	->packToSet();

	/********************\
	 * Equivalent:
	 *
	 * //SQL-ish
	 * SELECT elem
	 * FROM arr
	 * WHERE (elem%2=0 OR elem=1) AND true AND elem > 4 OR elem <= 2
	 * ORDER BY elem DESC
	 *
	 * //C#
	 * from elem in arr
	 * where (elem%2==0 || elem==1) && true && elem>4 || elem <=2
	 * orderby elem descending
	 * select elem
	 *
	 * //Expected result
	 * {0,1,2,3,4,5,6,7,8,9} => ? (this implementation -> {0,1,2,6,8} or (8,6,4,2,1,0))
	\********************/

	for(int i : linqed)
		cout << i << ' ';
	cout << '\n';
}