#pragma once

#include "osztoszamlalo.hpp"

#include "gtlib/enumerator.hpp"
#include "gtlib/summation.hpp"

#include <iostream>
#include <fstream>
#include <string>

class SzamListazoOsztoSzamolo : public Enumerator<int> {
public:
	class InvalidFileException {};

	SzamListazoOsztoSzamolo(std::string filename) : file(filename) {
		if (!file.is_open()) {
			throw InvalidFileException();
		}
	}

	virtual void first() override {
		next();
	}
	
	virtual void next() override {
		int szam;
		file >> szam;
		
		OsztoEnumerator oe1(szam);
		OsztoSzamlalo osz1;
		osz1.addEnumerator(&oe1);
		osz1.run();
		
		curr = osz1.result();
	}
	
	virtual bool end() const override {
		return file.fail();
	}
	
	virtual int current() const override {
		return curr;
	}
private:
	std::ifstream file;
	int curr;
};

class SzamKiiro : public Summation<int> {
protected:
	virtual void init() override {
	}
	
	virtual void add(const int& e)  override {
		std::cout << e << std::endl;
	}
};