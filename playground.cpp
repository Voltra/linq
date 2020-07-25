#include <iostream>
#include <functional>
#include <vector>
#include <set>
#include <forward_list>
#include "linq/linq.hpp"

using namespace std;
using namespace linq::utils;
using namespace helperFunctions; //linq::utils::helperFunctions
using namespace linq::types;

void testLinqable();
void testLinqable2();
void testLinqable3();
void testLinqable4();
void testLinqable5();

class Employe{
	protected:
		string name;
		bool lives;

	public:
		Employe(string name, bool lives = true) : name{name}, lives{lives}{}

		bool isAlive(){ return this->lives; }
		string getName(){ return this->name; }
};

int main() {
//	testLinqable();
//	testLinqable2();
//	testLinqable3();
//	testLinqable4();
//	testLinqable5();

	/*static_assert(
		isLinqCompatible<LinqVector<int>>::value,
		"Whoops, LinqVector<int> should be linq compatible"
	);*/
	return 0;
}


void testLinqable(){
	vector<int> arr = {0,1,2,3,4,5,6,7,8,9};
	forward_list<int> linqed = linq::from<int>(arr.begin(), arr.end())
	->where(isEven<int>)
	->orWhere(is(1))
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
	vector<int> linqed = linq::from<int>(arr.begin(), arr.end())
	->where(isEven<int>)
	->orWhere(is(1))
	->andWhere([](const int& elem)->bool{ return true; })
	->andComplexWhere([](const linq::Linqable<int>& builder){
		return builder->where(isGreaterThan(4))
		->orWhere(isLessThanOrEqualTo(2));
	})->orderDesc()
	->select()
	->packToVector();

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
	vector<int> linqed = linq::from<int>(arr.begin(), arr.end())
	->where(isEven<int>)
	->orWhere(is(1))
	->andWhere([](const int& elem)->bool{ return true; })
	->andWhere(isGreaterThan(4))
	->orWhere(isLessThanOrEqualTo(2))
	->orderDesc()
	->select()
	->packToVector();

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
	 * {0,1,2,3,4,5,6,7,8,9} => ? (this implementation -> {0,1,2,6,8} or (8,6,2,1,0))
	\********************/

	for(int i : linqed)
		cout << i << ' ';
	cout << '\n';
}

void testLinqable4(){
	vector<int> arr = {0,1,2,3,4,5,6,7,8,9};
//	int linqed = linq::from<int>(arr.begin(), arr.end())
	int linqed = linq::from<int>(arr.begin(), arr.end())
	->where(isEven<int>)
	->orWhere(is(1))
	->andWhere([](const int& elem)->bool{ return true; })
	->orderDesc()
	->selectReduced<int>(reducers::ints::sum, 0);

	/********************\
	 * Equivalent:
	 *
	 * //SQL-ish
	 * SELECT sum(elem)
	 * FROM arr
	 * WHERE (elem%2=0 OR elem=1) AND true
	 * ORDER BY elem DESC
	 *
	 * //C#
	 * from elem in arr
	 * where (elem%2==0 || elem==1) && true
	 * orderby elem descending
	 * select elem
	 *
	 * //Expected result
	 * {0,1,2,3,4,5,6,7,8,9} => 21
	\********************/

	cout << linqed;
}


void testLinqable5(){
	vector<Employe> vect = {};
	bool isAlive = true;
	for(char c='a' ; c <= 'z' ; c+=1) {
		vect.emplace_back(string{c}, isAlive);
		isAlive = !isAlive;
	}

	string names = linq::from<Employe>(vect.begin(), vect.end())
	->where(&Employe::isAlive)
	->select<string>(&Employe::getName)
	->select<string>([](string s){ return s + " "; })
	->selectReduced<string>(reducers::strings::concat, string{});

	std::cout << names;
}