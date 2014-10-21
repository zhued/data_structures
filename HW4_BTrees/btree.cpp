/*
 * query = 5 points
 * 
 * remove 
 * easy - mostly full leaf
 * medium - movely full index node
 * medium - starving leas, borrow from fat sibling
 * hard - starving node& siblings, must combine nodes
 * hardest - combine bodes & shrink tree height
 * 
 * insert
 * easy - empty(ish) root
 * easy 2 - leaf w/ room
 * medium - split node, parent not full


*/
#include "btree.h"

using namespace std;

// -------------------------------------------- I N S E R T ------------------------
//
// Insert the given key into a b-tree rooted at 'root'.  If the key is
// already contained in the btree this should do nothing.  
// 
// On exit: 
// -- the 'root' pointer should refer to the root of the
//    tree. (the root may change when we insert or delete)
// -- the btree pointed to by 'root' is valid.
void insert_into(btree* root, btree* parent, btree* node, int key);
btree* find_subtree (btree* node, int key);
void split_root (btree* root);
void insert_leaf(btree* root, btree* parent, btree* node, int key);
void split_node (btree* root, btree* parent, btree* node);

int t = (BTREE_ORDER+1)/2;

btree* init_btree(){
	btree *b = new btree;
	b->is_leaf = true;
	b->num_keys = 0;
	return b; 
}

void insert_key(btree *&node, int key){
	if (node == NULL){
		node = init_btree();
	}
	if (node->num_keys == BTREE_ORDER){
		return;
	}
	if (node->num_keys == 0){
		node->keys[0] = key;
	} else if (key > node->keys[node->num_keys-1]) {
		node->keys[node->num_keys] = key;
	} else {
		for (int i = 0; i < node->num_keys; i++){
			if (node->keys[i] == key){
				return;
			} else if (node->keys[i] > key){
				int temp = key;
				for (int j = i; j <= node->num_keys; j++){
					swap (temp, node->keys[j]);
				}
				break;
			}
		}
	}
	node->num_keys++;
}

btree* find_subtree (btree* node, int key){
	for (int i = 0; i< node->num_keys; i++){
		if(node->keys[i] == key){
			return node;
		} else if (node->keys[i] > key){
			return node->children[i];
		}
	}
	return node->children[node->num_keys];
}

void insert_leaf(btree* root, btree* parent, btree* node, int key){
	insert_key(node, key);
	if (node->num_keys >= BTREE_ORDER){
		split_node(root, parent, node);
	}
}

int find_index (btree* parent, btree* node){
	for (int i = 0; i <= node->num_keys; i++){
		if (parent->children[i] == node){
			return i;
		}
	}
	return -1;
}

void insert_child (btree* parent, btree* node, int index){
	btree* temp = parent->children[index];
	parent->children[index] = node;
	for (int i = index + 1; i <= parent->num_keys; i++){
		swap(temp, parent->children[i]);
	}
}

btree* find_parent(btree* root, btree* node){
	if (node != NULL){
		if (root == node){
			return root;
		} else if (find_subtree(root, node->keys[0]) == node){
			return root;
		} else {
			return find_parent(find_subtree(root, node->keys[0]), node);
		}
	}
}

void split_node (btree* root, btree* parent, btree* node){
	if(node == root){
		split_root(node);
		return;
	}
	int mid = BTREE_ORDER/2;
	int key = node->keys[mid];
	int index = find_index(parent, node);
	
	insert_key(parent, key);
	btree* clone = init_btree();
	for (int i = 0; i < mid; i++){
		clone->keys[i] = node->keys[i + mid + 1];
		clone->children[i] = node->children[i + mid + 1];
	}
	clone->children[mid] = node->children[BTREE_ORDER];
	node->num_keys = mid;
	clone->num_keys = mid;
	if (!node->is_leaf){
		clone->is_leaf = false;
	}
	insert_child(parent, clone, index + 1);
	if(parent->num_keys >= BTREE_ORDER){
		split_node(root, find_parent(root, parent), parent);
	}
	
}

void split_root (btree* root){
	btree* right = init_btree();
	btree* left = init_btree();
	int mid = BTREE_ORDER/2;
	
	for (int i = 0; i < mid; i++){
		left->keys[i] = root->keys[i];
		left->children[i] = root->children[i];
		root->children[i] = NULL;
		left->num_keys = mid;
	}
	
	for (int i = 0; i < mid; i++){
		right->keys[i] = root->keys[i + mid + 1];
		right->children[i] = root->children[i + mid + 1];
		root->children[i + mid + 1] = NULL;
		right->num_keys = mid;
	}
	
	left->children[mid] = root->children[mid];
	right->children[mid] = root->children[BTREE_ORDER];
	
	if (!root->is_leaf){
		left->is_leaf = false;
		right->is_leaf = false;
	}
	
	root->is_leaf = false;
	root->keys[0] = root->keys[mid];
	
	root->children[0] = left;
	root->children[1] = right;
	root->num_keys = 1;

}

void insert_into(btree* root, btree* parent, btree* node, int key){
	if (node){
		if (node->is_leaf){
			insert_leaf(root, parent, node, key);
		} else {
			btree* next = find_subtree(node, key);
			if (next != node){
				insert_into(root, node, next, key);
			}
		}
	}
}

void insert (btree* &root, int key){
	insert_into(root, NULL, root, key);
}

/*
void split_child(btree* &root, int i, btree* &child){
	btree* z = new btree;
	z->is_leaf = child->is_leaf;
	z->num_keys = t-1;  // prob wrong
	for (int j = 1; j <= t-1; j++){
		z->keys[j] = child->keys[j+t];
	}
	if (!child->is_leaf){
		for (int j = 1; j <= t; j++){
			z->children[j] = child->children[j+t];
		}
	}
	child->num_keys = t-1;
	for (int j = root->num_keys+1; j >= i+1; j--){
		root->children[j+1] = root->children[j];
	}
	z = root->children[i+1];
	for (int j = root->num_keys; j >= i+1; j--){
		root->keys[j+1] = root->keys[j];
	}
	root->keys[i] = child->keys[i];
	root->num_keys++;
	
}

void insert_nonfull(btree* &root, int key){
	int i = root->num_keys;
	if (root->is_leaf){
		while (i >= 1 && key < root->keys[i]){
			root->keys[i+1] = root->keys[i];
			i--;
		}
		root->keys[i+1] = key;
		root->num_keys++;
	} else {
		while (i >= 1 && key < root->keys[i]){
			i--;
		}
		i++;
		btree* subtree = root->children[i];
		if (subtree->num_keys == BTREE_ORDER){
			split_child(root, i, subtree);
			if (key > root->keys[i]){
				i++;
			}
		}
		insert_nonfull(root->children[i], key);
	}
}

void insert(btree* &root, int key) {
	if (root->num_keys == BTREE_ORDER){
		btree* s = new btree;
		s->is_leaf = false;
		s->num_keys = 0;
		s->children[1] = root;
		split_child(s, 1, root);
		insert_nonfull(s, key);
	} else {
		insert_nonfull(root, key);
	}
}
*/






// -------------------------------------------- R E M O V E ------------------------
//
// Remove the given key from a b-tree rooted at 'root'. If the key is
// not in the btree this should do nothing.
//
// On exit:
// -- the 'root' pointer should refer to the root of the
//    tree. (the root may change when we insert or delete)
// -- the btree pointed to by 'root' is valid.
void remove(btree* &root, int key) {

}









// ----------------------------------------- C O N T A I N S ------------------------
//
// Return true if any node accessed from the given root node contains
// the provided key value.
bool find_key(btree* &root, int key);
btree* find_subtreee(btree* &root, int key);

bool contains(btree* &root, int key) {
	if (root == NULL){
		return NULL;
	}
	if (find_key(root, key)){
		return true;
	} else {
		btree* subtree = find_subtreee(root, key);
		return contains(subtree, key);
	}
	return false;
}

bool find_key(btree* &root, int key){
	for (int k = 0; k < root->num_keys; k++){
		if (root->keys[k] == key){
			return true;
		} 
	}
	return false;
}

btree* find_subtreee(btree* &root, int key){
	if (root->is_leaf == true){
		return NULL;
	}
	int cur = 0;
	for (int k = 0; k < root->num_keys; k++){
		if (root->keys[k] < key){
			cur = cur + 1;
		} else {
			break;
		}
	}
	return root->children[cur];
}





/*	
fillnode

split

search node

int setval ( int val, btree *n, int *p, btree **c )
{
	int k ;
	if ( n == NULL )
	{
		*p = val ;
		*c = NULL ;
		return 1 ;
	}
	else
	{
		if ( searchnode ( val, n, &k ) )
//			cout << endl << "Key value already exists." << endl ;
		if ( setval ( val, n -> child[k], p, c ) )
		{
			if ( n -> num_keys < BTREE_ORDER )
			{
				fillnode ( *p, *c, n, k ) ;
				return 0 ;
			}
			else
			{
				split ( *p, *c, n, k, p, c ) ;
				return 1 ;
			}
		}
		return 0 ;
	}
}

void insert(btree* &node, int &val){
	int i ;
	btree *c, *n ;
	int flag ;
	flag = setval ( val, root, &i, &c ) ;
	if ( flag )
	{
		n = new btree ;
		n -> count = 1 ;
		n -> value[1] = i ;
		n -> child[0] = root ;
		n -> child[1] = c ;
		root = n ;
	}	
}

void find_node



//---------------------------------------------------
void node_contains_key(btree* node, int val){
	for(i = 0, i <= num_keys, i++){
		if (i == val){
			return true;
		}
		else {
			return false;
		}
	}
}

void findsub(btree* node, int val){
	if (is_leaf == true){
		return;
	}
	else {
		int cur = 0;
		for (i = 0, i <= num_keys, i++){
			if (val > key){
				cur++;
			}
			else{
				break;
			}
		}
		return btree* children[cur];
	}
}

bool contains(btree* &root, int key) {
	if node_contains_key(root, key){
		return true;
	}
	else{
		subtree = findsub(root, key)
		return contains(subtree, key)
	}
  return false;
}
//---------------------------------------------------




void remove(btree* &root, int key) {
}
*/
