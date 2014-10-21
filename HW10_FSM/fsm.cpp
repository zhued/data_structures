/*

  fsm.cpp - Finite State Machine

  Read the header file 'fsm.hpp' for all documentation on individual
  functions. I suggest you start by getting the unit test cases to
  pass in order. E.g. start with the Defaults one, then do Add States,
  and so on.

  Your Name: Edward Zhu

  Your Collaborators: Max Russek

 */

#include "fsm.hpp"

using namespace std;

FSM::FSM() {
	state = -1;
	default_state = -1;
}

int FSM::addState(string label, bool is_accept_state) {
	State* st = new State;
	st->label = label;
	st->accept = is_accept_state;
	st->failure_trans = -1;
	int id = states.size();
	states.push_back(st);
	if (id == 0){
		default_state = id;
		state = id;
	}
	return id;
}

int FSM::addState(string label) {
	return addState(label, false);
}

int FSM::addTransition(int stateA, int stateB, 
		       int signal, string transLabel) {
	State* stA = getState(stateA);
	State* stB = getState(stateB);
	int id = -1;
	if (stA && stB){
		for(vector<int>:: iterator it = stA->trans.begin(); it != stA->trans.end(); it ++){
			Transition* cur = getTransition(*it);
			if (cur->signal == signal){
				return -1;
			}
		}
		Transition* tr = new Transition;
		tr->label = transLabel;
		tr->signal = signal;
		id = transitions.size();
		tr->next_state = stateB;
		if (signal == FAILURE_SIGNAL)
			stA->failure_trans = id;
		transitions.push_back(tr);
		stA->trans.push_back(id);		
	}
	return id;
}

int FSM::countStates() {
	return states.size();
}

int FSM::countTransitions() {
	return transitions.size();
}

int FSM::getCurrentState() {
	return state;
}

bool FSM::isAcceptState() {
	State* s = getState(state);
	if (s){
		return s->accept;
	} else {
		return false;
	}
}

State* FSM::getState(int id) {
	if(id >= 0 && id < states.size()){
		return states[id];
	}
	return NULL;
}

Transition* FSM::getTransition(int id) {
	if(id >= 0 && id < transitions.size()){
		return transitions[id];
	}
	return NULL;
}

int FSM::getDefaultState() {
	return default_state;
}

void FSM::setState(int id) {
	if (id >= 0 && id < states.size()){
		state = id;
	}
}

bool FSM::handleSignal(int signal) {
	State* wat = getState(state);
	if (wat){
		for(vector<int>::iterator it = wat->trans.begin(); it != wat->trans.end(); it++){
			if (transitions[*it]->signal ==  signal){
				state = getTransition(*it)->next_state;
				return true;
			}
		}
		if(wat->failure_trans >= 0){
			state = getTransition(wat->failure_trans)->next_state;
			return true;
		}
	}
	return false;
}

ostream &operator << (ostream& out, State* st) {
  if (st == NULL) {
    out << "State: NULL";
  } else {
    out << "State: " << st->label;
    if (st->accept) {
      out << " +";
    }
  }
  return out;
}
