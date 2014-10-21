// 
// pq_struct.h
// 
// Edit this to flesh out the pq structure as appropriate. You may
// also add the function prototypes for anything else, and implement
// them in pq.cpp.
//
// You will turn in this file and pq.cpp to retrograde.
//
// Your Name:Edward Zhu


using namespace std;

#ifndef pq_struct_h
#define pq_struct_h

#include <string>


struct pq{
	string text;
	float priority;
	pq* next;
	
//	int operator<(const pq& other){
//		return priority > other.priority;
//	}	
  // implement me
};

#endif
