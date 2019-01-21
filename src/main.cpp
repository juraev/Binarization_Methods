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
	string s;
	s = "image.png";
//	cin >> s;
	Image<> img(s);
	CImg<unsigned char>* bernsen = img.bernsenTech(25);
	CImg<unsigned char>* sauvola = img.SauvolaTech();
	CImg<unsigned char>* niblack = img.NiblackTech();
	CImg<unsigned char>* otsu = img.OtsuTech();
	bernsen->save_jpeg("bernsen.jpg");
	sauvola->save_jpeg("sauvola.jpg");
	niblack->save_jpeg("niblack.jpg");
	otsu->save_jpeg("otsu.jpg");

	CImgDisplay disp(*bernsen, "Bernsen");
	CImgDisplay disp1(*sauvola, "Sauvola");
	CImgDisplay disp2(*niblack, "Niblack");
	CImgDisplay disp3(*otsu, "Otsu");
//	while(!disp1.is_closed()){
	while(!disp.is_closed()&&!disp1.is_closed()&&!disp2.is_closed()){

	}

	return 0;
}


