//
// pq.cpp
//
// Decide how you want to implement this: linked list? heap? array?
// magic pixie dust? The choice is yours.
//
// NOTE: You will need to edit pq_struct.h as appropriate, depending
// on your implementation strategy. You will turn in this file (your
// implementation of everything) and pq_struct.h (your definition of
// the pq structure and any helper functions you might create).

// Your Name: Edward Zhu


#include <string>
#include "pq.h"
#include <queue>

//priority_queue<pq> pQueue;

/**
 * Initialize an empty priority queue.
 *
 * This is needed for unit testing. I'll do something like this:
 *
 *   pq* queue = init_priority_queue();
 *   string text = "Speaker of the House";
 *   insert(queue,  text, 7.9);
 *   text = "President";
 *   insert(queue, text, 10.0);
 *   text = "Congressional Staffer";
 *   insert(queue, text, 2.0);
 *   cout << remove(queue) << endl; // President
 *   cout << remove(queue) << endl; // Speaker of the House
 *   cout << remove(queue) << endl; // Congressional Staffer
 *
 **/
pq* init_priority_queue() {
	return NULL;
  // implement me
}

/**
 * Insert the given text information into the queue with the specified
 * priority.
 *
 * Larger priority values have precedence. So if I add "foo" at
 * priority 5.0 and "bar" at priority 5.1, "bar" will be removed
 * before "foo".
 *
 * Priority values may be negative, zero, or positive.
 **/
void insert(pq* &queue, string &text, float priority) {
	pq* cur = queue;
	pq* put_in = new pq;
	put_in->text = text;
	put_in->priority = priority;
	put_in->next = NULL;
	pq* temp;
	if ( queue == NULL){
		queue = put_in;
	} else if (priority > queue->priority) {
		temp = queue;
		queue = put_in;
		put_in->next = temp;
	} else {
		while(cur->next != NULL && priority < cur->next->priority){
			cur = cur->next;
		}
		temp = cur->next;
		cur->next = put_in;
		put_in->next = temp;
	}
  // implement me
}

/**
 * Remove the highest priority element from the queue and return it.
 **/
string remove(pq* &queue) {
	string deleted = queue->text;
	delete queue;
	queue = queue->next;
	return deleted;
}

/**
 * Return the highest priority element in the queue but do not alter
 * the queue's membership.
 **/
string peek(pq* &queue) {
  return queue->text;
}
