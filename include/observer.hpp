#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <iostream>
#include <list>


template<typename T>
class Observer {
public:
	virtual void update(T info) =0;
};

template<typename T>
class Observable {
private:
	std::list<Observer<T> *> list_observers_;
public:
	void notifyObservers(T info) {
		for(auto obs : list_observers_) obs->update(info);
	}
	void addObserver(Observer<T>* observer){
		list_observers_.push_back(observer);
	}
};

#endif