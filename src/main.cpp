/*
 * main.cpp
 *
 *  Created on: Jan 3, 2019
 *      Author: jack
 */

#include <iostream>
#include "Image.h"
#include <fstream>
#include <sys/time.h>

using namespace std;

long long getTime(){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return ms;
}

int main(int argc, char** args){
	//ofstream file("/home/jack/eclipse-workspace/Binarization-Methods/stats.csv", std::ios::app);
	string s, s1;

	s = args[1];
	s1 = args[2];
	s += s1;

	//	s = "image1.jpg";
//	cin >> s;
	Image<> img(s);
	int b, sa, n, ot;
	long long result, result1;

//	result = getTime();
//	CImg<unsigned char>* bernsen = img.bernsenTech(25);
//	result1 = getTime();
//	b = result1 - result;

	result = getTime();
	CImg<unsigned char>* sauvola = img.SauvolaTech();
	result1 = getTime();
	sa = result1 - result;

//	result = getTime();
//	CImg<unsigned char>* niblack = img.NiblackTech();
//	result1 = getTime();
//	n = result1 - result;

	result = getTime();
	CImg<unsigned char>* otsu = img.OtsuTech();
	result1 = getTime();
	ot = result1 - result;
	string sss = "";
	int i = 0;
	while(true){
		if(args[2][i] == '.') break;
		sss += args[2][i];
		i ++;
	}
	s = "/home/khurshid/Downloads/output/"+sss;
	s1 = "mkdir -p " + s;
	//system(s1.c_str());
//
//	s1 = s + "/bernsen.jpg";
//	bernsen->save_jpeg(s1.c_str());

	s1 = s + "/sauvola.jpg";
	sauvola->save_jpeg("/home/khurshid/Downloads/sauvola.jpg");

//	s1 = s + "/niblack.jpg";
//	niblack->save_jpeg(s1.c_str());

	s1 = s + "/otsu.jpg";
	otsu->save_jpeg(s1.c_str());


//	CImgDisplay disp(*bernsen, "Bernsen");
//	CImgDisplay disp1(*sauvola, "Sauvola");
//	CImgDisplay disp2(*niblack, "Niblack");
//	CImgDisplay disp3(*otsu, "Otsu");

	//file << otsu->_width << "," << otsu->_height << "," << b << "," << n << "," << sa << "," << ot <<endl;
	//file.close();

	//	while(!disp1.is_closed()){
//	while(!disp.is_closed()&&!disp1.is_closed()&&!disp2.is_closed()&&!disp3.is_closed()){
//
//	}
	return 0;
}


