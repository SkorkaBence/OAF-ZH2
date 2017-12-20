#pragma once

#include "osztoszamlalo.hpp"
#include "osztokiiro.hpp"

#include "gtlib/enumerator.hpp"
#include "gtlib/summation.hpp"
#include "gtlib/linsearch.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <typeinfo>

template <typename Item>
class SeqInFileEnumerator2 : public Enumerator<Item>
{
    protected:
        std::ifstream _f;
        Item          _df;

    public:
        enum Exceptions { OPEN_ERROR };
        SeqInFileEnumerator2(const std::string& str){
            _f.open(str.c_str());
            if(_f.fail()) throw OPEN_ERROR;
            if(typeid(Item)==typeid(char)) _f.unsetf(std::ios::skipws);
        }

        void first()         final override { /*next();*/ }
        void next()          final override { _f >> _df;}
        bool end()     const final override { return _f.eof();}
        Item current() const final override { return _df; }
};


class KovetkezoSzamKereso : public LinSearch<int> {
public:
	KovetkezoSzamKereso(int ln) : lastnum(ln) {}
protected:
    virtual bool cond(const int& e) const override {
		//std::cout << "CHCK " << e << " > " << lastnum << std::endl;
		return e > lastnum;
	}
private:
	int lastnum;
};

class SzamokatSorrendbenSorolo : public Enumerator<int> {
public:
	SzamokatSorrendbenSorolo(std::string filename) : fileolvaso(filename) {
	}
	
	virtual void first() override {
		fileolvaso.next();
		next();
	}
	
	virtual void next() override {
		KovetkezoSzamKereso kovker(lastnum);
		kovker.addEnumerator(&fileolvaso);
		kovker.run();
		
		if (kovker.found()) {
			//std::cout << "NEXT " << kovker.elem() << std::endl;
			lastnum = kovker.elem();
		} else {
			//std::cout << "FAILED" << std::endl;
			vege = true;
		}
	}
	
	virtual bool end() const override {
		return vege;
	}
	
	virtual int current() const override {
		return lastnum;
	}
private:
	SeqInFileEnumerator2<int> fileolvaso;
	int lastnum = -1;
	bool vege = false;
};

class SzambolOsztoenum : public Enumerator<int> {
public:
	SzambolOsztoenum(Enumerator<int>* e) : enor(e) {}
	
	virtual void first() override {
		enor->first();
		calculate(enor->current());
	}
	
	virtual void next() override {
		enor->next();
		calculate(enor->current());
	}
	
	virtual bool end() const override {
		return enor->end();
	}
	
	virtual int current() const override {
		return curr;
	}
private:

	void calculate(int inp) {
		OsztoEnumerator oe1(inp);
		OsztoSzamlalo osz1;
		osz1.addEnumerator(&oe1);
		osz1.run();
		
		curr = osz1.result();
	}

	Enumerator<int>* enor;
	int curr;
};