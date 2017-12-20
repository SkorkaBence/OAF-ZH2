#include <iostream>

#include "osztoszamlalo.hpp"
#include "osztokiiro.hpp"
#include "osztosorrendbenkiiro.hpp"
#include "osztonelkul.hpp"

#include "gtlib/seqinfileenumerator.hpp"

int main () {
	/*  2 pontert  */
	std::cout << "--- 2 pontert ---" << std::endl;
	
	OsztoEnumerator oe1(18);
	OsztoSzamlalo osz1;
	osz1.addEnumerator(&oe1);
	osz1.run();
	std::cout << "18 osztoinak szama: " << osz1.result() << std::endl;
	
	/* 3 pontert */
	std::cout << "--- 3 pontert ---" << std::endl;
	
	SzamListazoOsztoSzamolo szamlista1("szamok_1.txt");
	SzamKiiro kiiras1;
	kiiras1.addEnumerator(&szamlista1);
	kiiras1.run();
	
	/* 4 pontert */
	std::cout << "--- 4 pontert ---" << std::endl;
	
	SzamokatSorrendbenSorolo szamsorrendbenlista("szamok_2.txt");
	SzambolOsztoenum osztoenor(&szamsorrendbenlista);
	SzamKiiro kiiras2;
	kiiras2.addEnumerator(&osztoenor);
	kiiras2.run();
	
	/* 5 pontert */
	std::cout << "--- 5 pontert ---" << std::endl;
	
	SzamokatSorrendbenSorolo szamsorrendbenlista2("szamok_2.txt");
	SzambolOsztoenum osztoenor2(&szamsorrendbenlista2);
	KiiroEsOsztoNelkuliKereso kiiras3;
	kiiras3.addEnumerator(&osztoenor2);
	kiiras3.run();
	
	std::cout << "Valodi oszto nelkuliek szama: " << kiiras3.result() << std::endl;
}