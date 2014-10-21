#include "btree.h"
#include "dotfile.h"
#include <iostream>

using namespace std;

void insert_key(btree*&, int);

int main (int argc, char** argv){
	btree* b = init_btree();
	for(int i = 40; i >= 1; i--)
		insert(b, i);
	print_tree_named(b, "Before", "before.dot");
	//~ insert(b, 30);
	print_tree_named(b, "After", "after.dot");
	return 0;
}
