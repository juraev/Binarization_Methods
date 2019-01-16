/*
 * main.cpp
 *
 *  Created on: Jan 3, 2019
 *      Author: jack
 */

#include <iostream>
#include "Image.h"

using namespace std;

int main(){
	string s = "image.jpg";
	//cin >> s;
	Image<> img(s);
	CImg<unsigned char>* bernsen = img.bernsenTech(31);
	CImg<unsigned char>* sauvola = img.SauvolaTech();
	CImg<unsigned char>* niblack = img.NiblackTech();
	bernsen->save_jpeg("bernsen.jpg");
	sauvola->save_jpeg("sauvola.jpg");
	niblack->save_jpeg("niblack.jpg");

	char name[] = "Bersen";
	CImgDisplay disp(*bernsen, name, 3, false, false);
	CImgDisplay disp1(*sauvola);
	CImgDisplay disp2(*niblack);
	while(!disp.is_closed()&&!disp1.is_closed()&&!disp2.is_closed()){

	}

	return 0;
}


