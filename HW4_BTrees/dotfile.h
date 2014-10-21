/* Dot file api */

#ifndef __DOTFILE__
#define __DOTFILE__

#include "btree.h"
#include <string>

void print_tree(btree* &root);

void print_tree_named(btree* &root, std::string title, std::string to);

#endif	/* __DOTFILE__ */
