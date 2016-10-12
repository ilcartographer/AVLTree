// AVLTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <list>
#include <set>
#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <limits>
#include "avltree.h"

using std::list;
using std::set;
using std::cin;
using std::getline;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

// Timer code. Thanks to StackExchange http://stackoverflow.com/a/21995693
template<typename TimeT = std::chrono::milliseconds>
struct measure
{
	template<typename F, typename ...Args>
	static typename TimeT::rep execution(F func, Args&&... args)
	{
		auto start = std::chrono::system_clock::now();

		// Now call the function with all the parameters you need.
		func(std::forward<Args>(args)...);

		auto duration = std::chrono::duration_cast< TimeT>
			(std::chrono::system_clock::now() - start);

		return duration.count();
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	string prompt;
	do
	{
		unsigned long int count;
		do
		{
			cout << "How many insertions (min 10)? ";
			cin >> count;
		} while (count <= 9);

		// Use the same list of numbers
		cout << "Populating random numbers... ";
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine generator(seed);
		std::uniform_int_distribution<int> distribution(0, 10000);
		list<int> values;
		for (int i = 0; i < count; ++i)
			values.push_back(distribution(generator));
		cout << "done." << endl;

		// Time student code: Insert
		avl_tree<int> avltree;
		cout << "Populating AVL Tree... ";
		// Using a lambda expression (anonymous function) do do the timing. For more
		// info on this capability in C++, see 
		// http://www.cprogramming.com/c++11/c++11-lambda-closures.html
		std::chrono::milliseconds::rep runtime = measure<>::execution([&]()
		{
			for (auto value : values)
				avltree.insert(value);
		});
		cout << "done; Took " << runtime << " ms ("
			<< runtime / static_cast<float>(count) << " per insert)." << endl;
		// Time student code: Search
		cout << "Searching AVL Tree... ";
		runtime = measure<>::execution([&]()
		{
			for (auto value : values)
				if (!avltree.find(value))
					cerr << "Error: Item " << value << " not found in tree." << endl;
		});
		cout << "done; Took " << runtime << " ms ("
			<< runtime / static_cast<float>(count) << " per search)." << endl;


		// Time C++ library code: Insert
		set<int> rbtree;
		cout << "Populating C++ Red-Black Tree... ";
		runtime = measure<>::execution([&]()
		{
			for (auto value : values)
				rbtree.insert(value);
		});
		cout << "done; Took " << runtime << " ms ("
			<< runtime / static_cast<float>(count) << " per insert)." << endl;
		// Time C++ library code: Search
		cout << "Searching C++ Red-Black Tree... ";
		auto end = rbtree.end();
		runtime = measure<>::execution([&]()
		{
			for (auto value : values)
				if (rbtree.find(value) == end)
					cerr << "Error: Item " << value << " not found in tree." << endl;
		});
		cout << "done; Took " << runtime << " ms ("
			<< runtime / static_cast<float>(count) << " per search)." << endl;

		cout << "Test again (Y/N)? " << endl;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flush newlines
		getline(cin, prompt);
	} while (prompt[0] == 'y' || prompt[0] == 'Y');
}