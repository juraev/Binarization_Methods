/*
 * Image.h
 *
 *  Created on: Jan 4, 2019
 *      Author: jack
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "CImg.h"
#include <iostream>

#define uchar unsigned char

const uchar WHITE[] = {255, 255, 255};
const uchar BLACK[] = {0, 0, 0};

using namespace cimg_library;

template<class T = uchar>
class Image {

private:

    int _width;
    int _height;
    CImg<T> img;

public:

    Image(std::string path){
        img = CImg<T>(path.c_str());
        _width = img._width;
        _height = img._height;
    }

    ~Image(){
        ~img;
    }

    void save(std::string path) {
    	img.save_png(path, 3);
    }


    CImg<T> getWB(uchar threshold){

        CImg<T> binary(_width, _height);

        cimg_forXY(img, x, y){
            binary(x, y) = img(x, y, 1) > threshold ? WHITE : BLACK;
        }
        return binary;
    }



    int width() { return _width; }

    int height() { return _height; }

    uchar getPix(int x, int y){
        return img(x, y, 0, 1);
    }

    void inline computeMeanAndDev(int x, int y, int& r, int& x1,
    			int& x2, int& y1, int& y2, double& mean, double& var){
    	mean = 0;
    	var = 0;
    	int pixnum = 0;
		x1 = std::max(0, x - r / 2);
		x2 = std::min(_width - 1, x + r / 2);
		y1 = std::max(0, y - r / 2);
		y2 = std::min(_height - 1, y + r / 2);
		for (int i = x1; i <= x2; i ++){
			for (int j = y1; j <= y2; j ++){
				uchar z = img(i, j, 0);
				var += z * z;
				mean += z;
			}
		}
		pixnum = (x2 - x1 + 1) * (y2 - y1 + 1);
		mean /= pixnum;
		var /= pixnum;
		var -= mean * mean;
		var = sqrt(var);
    }

    void inline computeMaxMin(int x, int y, int& r, int& x1,
    			int& x2, int& y1, int& y2, double& mx, double& mn){
		mx = 0;
		mn = 255;
		x1 = std::max(0, x - r / 2);
		x2 = std::min(_width - 1, x + r / 2);
		y1 = std::max(0, y - r / 2);
		y2 = std::min(_height - 1, y + r / 2);
		for (int i = x1; i <= x2; i ++){
			for (int j = y1; j <= y2; j ++){
				if(mx < img(i, j, 0)) mx = img(i, j, 0);
				if(mn > img(i, j, 0)) mn = img(i, j, 0);
			}
		}
    }

    void inline computeMin(int x, int y, int& r, int& x1,
    			int& x2, int& y1, int& y2, double& mn){
		mn = 255;
		x1 = std::max(0, x - r / 2);
		x2 = std::min(_width - 1, x + r / 2);
		y1 = std::max(0, y - r / 2);
		y2 = std::min(_height - 1, y + r / 2);
		for (int i = x1; i <= x2; i ++){
			for (int j = y1; j <= y2; j ++){
				if(mn > img(i, j, 1)) mn = img(i, j, 1);
			}
		}
	}

    CImg<uchar>* bernsenTech(int r){
    	std::clog << "bernsen...\n";
    	CImg<uchar>* bw = new CImg<uchar>(_width, _height, 1, 3, 0);
    	int x1, x2, y1, y2;
    	double mx, mn;
    	uchar t;

    	cimg_forXY(*bw, x, y){
    		computeMaxMin(x, y, r, x1, x2, y1, y2, mx, mn);
    		t = (mx - mn) / 2;
    		uchar g;
    		g = img(x, y, 0);
			bw->draw_point(x, y, g > t ? WHITE : BLACK);
    	}
    	return bw;
    }

    CImg<uchar>* NiblackTech(int r = 15, float k = -0.2){
    	std::clog << "niblack...\n";
    	CImg<uchar>* bw = new CImg<uchar>(_width, _height);
		int x1, x2, y1, y2;
		double mean, var;
		uchar t;
		cimg_forXY(*bw, x, y){
			computeMeanAndDev(x, y, r, x1, x2, y1, y2, mean, var);
			t = mean + k * var;
			uchar z = img(x, y, 0);
			bw->draw_point(x, y, z > t ? WHITE : BLACK);
		}
		return bw;
	}

    CImg<uchar>* SauvolaTech(int r = 15, float k = 0.34, int R = 128){
    	std::clog << "sauvola...\n";
    	CImg<uchar>* bw = new CImg<uchar>(_width, _height);
		int x1, x2, y1, y2;
		double mean, var;
		uchar t;
		cimg_forXY(*bw, x, y){
			computeMeanAndDev(x, y, r, x1, x2, y1, y2, mean, var);
			t = mean * (1 + k * (var / R - 1));
			uchar z = img(x, y, 0);
			bw->draw_point(x, y, z > t ? WHITE : BLACK);
		}
		return bw;
	}

    CImg<uchar>* OtsuTech(){
    	std::clog<<"otsu...\n";
    	CImg<uchar>* bw = new CImg<uchar>(_width, _height);
    	int hist[256];
    	for(int i = 0; i < 256; i ++) hist[i] = 0;
    	int pixnum = img._width * img._height;
    	double sum = 0;
    	cimg_forXY(*bw, x, y){
    		uchar z = img(x, y, 0);
    		hist[z] ++;
    		sum += z;
    	}

    	sum /= pixnum;
    	double w1 = 0, w2 = 1, m1 = 0, m2 = sum;
    	double mn = 0, tmp = 0;
    	uchar th = 0;
    	for (int t = 0; t < 256; t ++){
    		w1 += hist[t] * 1.0 / pixnum;
    		w2 -= hist[t] * 1.0 / pixnum;
    		m1 += t * hist[t] * 1.0 / pixnum;
    		m2 -= t * hist[t] * 1.0 / pixnum;
    		tmp = w1 * w2 * (m1 / w1 - m2 / w2) * (m1 / w1 - m2 / w2);
    		if(mn < tmp) mn = tmp, th = t;
    	}
    	cimg_forXY(*bw, x, y){
    		uchar z = img(x, y, 0);
    		bw->draw_point(x, y, z > th ? WHITE : BLACK);
    	}

    	return bw;
    }
};


#endif /* IMAGE_H_ */
