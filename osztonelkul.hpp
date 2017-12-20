#pragma once

#include "gtlib/summation.hpp"

#include <iostream>

class KiiroEsOsztoNelkuliKereso : public Summation<int> {
protected:
	virtual void init() override {
		*_result = 0;
	}
	
	virtual void add(const int& e) override {
		if (e == 0) {
			*_result = *_result + 1;
		}
		std::cout << e << std::endl;
	}
};