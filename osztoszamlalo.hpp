#pragma once

#include "gtlib/enumerator.hpp"
#include "gtlib/linsearch.hpp"
#include "gtlib/summation.hpp"

class SeqEnum : public Enumerator<int> {
public:
	class InvalidRangeException {};

	SeqEnum(int f, int t) : from(f), to(t), curr(f) {
		if (f > t) {
			throw InvalidRangeException();
		}
	} 
	
	virtual void first() override {
	}
	
	virtual void next() override {
		curr += 1;
	}
	
	virtual bool end() const override {
		return curr > to;
	}
	
	virtual int current() const override {
		return curr;
	}
private:
	int from;
	int to;
	int curr;
};

class OsztoKereso : public LinSearch<int> {
public:
	OsztoKereso(int n) : number(n) {}
protected:
    virtual bool cond(const int& e) const override {
		//std::cout << "CondCheck: " << number << " % " << e << std::endl;
		return number % e == 0;
	}
private:
	int number;
};

class OsztoEnumerator : public Enumerator<int> {
public:
	OsztoEnumerator(int num) : number(num), curr(1) {} 
	
	virtual void first() override {
		if (curr < number) {
			next();
		} else {
			vege = true;
		}
	}
	
	virtual void next() override {
		curr++;
		
		SeqEnum se(curr, number);
		OsztoKereso ok(number);
		ok.addEnumerator(&se);
		
		ok.run();
		
		vege = !ok.found();
		if (!vege) {
			curr = ok.elem();
			vege = curr >= number;
		}
	}
	
	virtual bool end() const override {
		return vege;
	}
	
	virtual int current() const override {
		return curr;
	}
private:
	int number;
	int curr;
	bool vege = false;
};

class OsztoSzamlalo : public Summation<int> {
protected:
	virtual void init() override {
		*_result = 0;
	}
	
	virtual void add(const int& e)  override {
		*_result = *_result + 1;
	}
};