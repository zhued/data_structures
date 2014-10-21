//
// binary_search_tree.cpp
//
// Please refer to binary_search_tree.h for documentation.
//
//
//
//Max
//Alex
//

#include <iostream>

#include "binary_search_tree.h"
 
bt_node* init_node(int data) {
	bt_node* new_node = new bt_node;
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}



void insert_recursive(bt_node* top, bt_node* new_node){
	if(top->data > new_node->data){
		if(top->left == NULL){
			top->left = new_node;
		} else {
			insert_recursive(top->left, new_node);
		}
		} else {
			if(top->right == NULL){
				top->right = new_node;
			} else {
				insert_recursive(top->right, new_node);
			}
		}
	}

void insert(bt_node** top_ref, bt_node* new_node) {
	if(*top_ref == NULL){
		*top_ref = new_node;
	} else{
		insert_recursive(*top_ref, new_node);
	}
}

void insert_data(bt_node** top_ref, int data) {
	bt_node* new_node = init_node(data);
	insert(top_ref, new_node);
}







bt_node* find_node(bt_node* top){
	bt_node* current = top;
	while (current->right){
		current = current->right;
	}
	return current;
}

void set_parent(bt_node* parent, bt_node* child, bt_node* set){
	if (parent){
		if (parent->left == child){
			parent->left = set;
		} else {
			parent->right = set;
		}
	}
}
void remove_recursive(bt_node* top, int data);

void remove_node(bt_node* death, bt_node* parent){
	if (death){
		if(death->left && death->right) {
			bt_node* pred = find_node(death->left);
			
			int temp = pred->data;
			pred->data = death->data;
			death->data = temp;
			
			if(death->left == pred){
				remove_node(pred, death);
			} else {
				remove_recursive(death->left, pred->data);
			}
		} else if (death->left || death->right){
			set_parent(parent, death, death->right == NULL ? death->left : death->right);
			delete death;
		} else {
			set_parent(parent, death, NULL);
			delete death;
		}
	}
}

void remove_recursive(bt_node* top, int data){
	if (top){
		if (data >= top->data){
			if(top->right && top->right->data == data){
				remove_node(top->right, top);
			} else {
				remove_recursive(top->right, data);
			}
		} else if(top->data > data) {
			if(top->left && top->left->data == data){
				remove_node(top->left, top);
			} else {
				remove_recursive(top->left, data);
			}
		}
	}
}

void remove(bt_node** top_ref, int data) {
	bt_node* top = *top_ref;
	if(top){
		if (top->data == data){
			bt_node parent;
			parent.left = NULL;
			parent.right = top;
			remove_node(top, &parent);
			*top_ref = parent.right;
		} else {
			remove_recursive(top, data);
		}
	}
		
}

bool contains(bt_node* top, int data) {
	if(top == NULL){
		return false;
	}
	else{
		if(data == top->data){
			return true;
			}
			else{
				if (data < top->data){ return (contains(top->left, data));}
					else{ return (contains(top->right, data));}
				}
		}
}

bt_node* get_node(bt_node* top, int data) {
	if(top == NULL){
		return NULL;
	}
	else{
		if(data == top->data){
			return top;
			}
			else{
				if (data < top->data){ return (get_node(top->left, data));}
					else{ return (get_node(top->right, data));}
				}
		}	

}

int size(bt_node* top) {
	if (top == NULL){
		return 0;
	}else{
		return (size(top->left) + 1 + size(top->right));
	}
}

void to_array(bt_node* top, int arr[]) {
	if (top == NULL){
		return;
	} else {
		to_array(top->left, arr);
		arr[size(top->left)] = top->data;
		to_array(top->right, arr + size(top->left) + 1);
	}	
}
