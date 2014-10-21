//
// pq_driver.cpp
//
// This is an empty unit test file that you can implement (or not) to
// create unit tests for your code.
//
// You'll likely want one for insert, remove, and peek. Try to think
// about how your queue could break, and write tests that help you
// test your deepest priority-queue-related fears.
//
// The test code will appear on RetroGrade late in the game.

#include "UTFramework.h"
#include "pq.h"
#include <sstream>

using namespace Thilenius;

SUITE_BEGIN("Priority Queue")

TEST_BEGIN("Initialize Queue")
{
	pq* n = init_priority_queue();
	IsTrue("Sane?", !n, "OK I'm insane");
}TEST_END

TEST_BEGIN("Insert into Queue")
{
	pq* n = NULL;
	for (int i = 0; i < 3; i++) {
		string s = to_string(i);
		insert(n, s, (float)i);
		string fail = "Failed with ";
		fail += peek(n);
		IsTrue("Contains highest priority element?", peek(n) == to_string(i),
	       fail);
	}
	string foo = "Foo";
	insert(n, foo, -1);
	IsTrue("Contains middle value", n->priority == 2, "Failure");
}TEST_END

TEST_BEGIN("Remove from Queue")
{
	pq* n = NULL;
	for (int i = 0; i < 10; i++) {
		string s = to_string(i);
		insert(n, s, (float)i);
	}
	
	for (int i = 9; i >= 0; i--) {
		string s = remove(n);
		string fail = "Failed with ";
		fail += s;
		IsTrue(s, s == to_string(i), fail);
	}
}TEST_END
	

SUITE_END

int main (int argc, char* argv[])
{	
  UTFrameworkInit;
}
