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
const unsigned char WHITE[] = {255, 255, 255};
const unsigned char BLACK[] = {0, 0, 0};

using namespace cimg_library;

template<class T = unsigned char>
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


    CImg<T> getWB(unsigned char threshold){

        CImg<T> binary(_width, _height);

        cimg_forXY(img, x, y){
            binary(x, y) = img(x, y, 0, 1) > threshold ? WHITE : BLACK;
        }
        return binary;
    }



    int width() { return _width; }

    int height() { return _height; }

//    double* getHusMoments(){
//        if(pfi == nullptr){
//            pfi = new double[10];
//            pfi[1] = getNyu(2, 0) + getNyu(0, 2);
//            pfi[2] = pfi[1] * pfi[1] - 4 * getNyu(2, 0) * getNyu(0, 2)
//                    + 4 * getNyu(1, 1) * getNyu(1, 1);
//            pfi[3] = _sqr(getNyu(3, 0) - 3 * getNyu(1, 2))
//                    + _sqr(3 * getNyu(2, 1) - getNyu(3, 0));
//            pfi[4] = _sqr(getNyu(3, 0) + getNyu(1, 2)) + _sqr(getNyu(2, 1) + getNyu(3, 0));
//            pfi[5] = (getNyu(3, 0) - 3 * getNyu(1, 2)) * (getNyu(3, 0 ) + getNyu(1, 2))
//                    * (_sqr(getNyu(3, 0) + getNyu(1, 2)) - 3 * _sqr(getNyu(2, 1) + getNyu(0, 3)))
//                    + (3 * getNyu(2, 1) - getNyu(0, 3)) * (getNyu(2, 1) + getNyu(0, 3))
//                    * (3 * _sqr(getNyu(3, 0) + getNyu(1, 2)) - _sqr(getNyu(2, 1) + getNyu(0, 3)));
//            pfi[6] = (getNyu(2, 0) - getNyu(0, 2))
//                    * (_sqr(getNyu(3, 0) + getNyu(1, 2)) - _sqr(getNyu(2, 1) + getNyu(0, 3)))
//                    + 4 * getNyu(1, 1) * (getNyu(3, 0 ) + getNyu(1, 2)) * (getNyu(2, 1) + getNyu(0, 3));
//            pfi[7] = (3 * getNyu(2, 1) - getNyu(0, 3)) * (getNyu(2, 1) + getNyu(0, 3))
//                    * (_sqr(getNyu(3, 0) + getNyu(1, 2)) - 3 * _sqr(getNyu(2, 1) + getNyu(0, 3)))
//                    - (getNyu(3, 0) - 3 * getNyu(1, 2)) * (getNyu(3, 0 ) + getNyu(1, 2))
//                    * (3 * _sqr(getNyu(3, 0) + getNyu(1, 2)) - _sqr(getNyu(2, 1) + getNyu(0, 3)));
//        }
//        return pfi;
//    }
//
//    double getNyu(short i, short j){
//        if(myu[i][j] == inf){
//            myu[i][j] = 0;
//            cimg_forXY(img, x, y){
//                myu[i][j] += pow(x - cent_x, i) * pow(y - cent_y, j)*getPix(x, y);
//            }
//            nyu[i][j] = (myu[i][j] * 1.0) / (pow(myu[0][0], (i + j) / 2 + 1) * 1.0);
//        }
//        return nyu[i][j];
//    }

    unsigned char getPix(int x, int y){
        return img(x, y, 0, 1);
    }

    void inline computeMeanAndVar(int x, int y, int& r, int& x1,
    			int& x2, int& y1, int& y2, double& mean, double& var){
    	mean = 0;
    	var = 0;
    	int pixnum = 0;
		x1 = std::max(0, x - r / 2);
		x2 = std::min(_width - 1, x + r / 2);
		y1 = std::max(0, y - r / 2);
		y2 = std::min(_height - 1, y + r / 2);
		int z;
		for (int i = x1; i <= x2; i ++){
			for (int j = y1; j <= y2; j ++){
				z = img(i, j, 0, 1);
				var += z * z;
				mean += z;
			}
		}
		pixnum = (x2 - x1 + 1) * (y2 - y1 + 1);
		mean /= pixnum;
		var /= pixnum;
		var -= mean * mean;
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
				if(mx < img(i, j, 0, 1)) mx = img(i, j, 0, 1);
				if(mn > img(i, j, 0, 1)) mn = img(i, j, 0, 1);
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
				if(mn > img(i, j, 0, 1)) mn = img(i, j, 0, 1);
			}
		}
	}

    CImg<unsigned char>* bernsenTech(int r){
    	CImg<unsigned char>* bw = new CImg<unsigned char>(_width, _height);
    	int x1, x2, y1, y2;
    	double mx, mn;
    	unsigned char t;
    	cimg_forXY(*bw, x, y){
    		computeMaxMin(x, y, r, x1, x2, y1, y2, mx, mn);
    		t = (mx - mn) / 2;
    		bw->draw_point(x, y, img(x, y, 0, 1) > t ? WHITE : BLACK);
    	}
    	return bw;
    }

    CImg<unsigned char>* NiblackTech(int r = 15, float k = -0.2){
    	CImg<unsigned char>* bw = new CImg<unsigned char>(_width, _height);
		int x1, x2, y1, y2;
		double mean, var;
		unsigned char t;
		cimg_forXY(*bw, x, y){
			computeMeanAndVar(x, y, r, x1, x2, y1, y2, mean, var);
			t = mean + k * var;
			bw->draw_point(x, y, img(x, y, 0, 1) > t ? WHITE : BLACK);
		}
		return bw;
	}

    CImg<unsigned char>* SauvolaTech(int r = 15, float k = 0.5, int R = 128){
    	CImg<unsigned char>* bw = new CImg<unsigned char>(_width, _height);
		int x1, x2, y1, y2;
		double mean, var;
		unsigned char t;
		cimg_forXY(*bw, x, y){
			computeMeanAndVar(x, y, r, x1, x2, y1, y2, mean, var);
			t = mean * (1 + k * (var / R - 1));
			bw->draw_point(x, y, img(x, y, 0, 1) > t ? WHITE : BLACK);
		}
		return bw;
	}

};


#endif /* IMAGE_H_ */
