
#pragma once

#include "CImg.h"
#include <iostream>
#include <queue>

using namespace cimg_library;
using namespace std;



class Pixel{
    /*
     utility class
     */
	public:
	int x;
	int y;
	int z;
	
	Pixel(int X, int Y, int Z)
	{
		x = X;
		y = Y;
		z = Z;
	}
};

void normalize(CImg<int> &img){
    /*
     normalize to 0-255
     */
	int max = img.max();
	int min = img.min();
	img = img - min;
	img = img*(255.0/(float)(max - min));
}

void medNormalize(CImg<int> &img){
    /*
     normalize to -2048 - 3071
     */
	int max = img.max();
	int min = img.min();
	img = img - min + 2048;
	img = img*(float(2048+3071)/(float)(max - min));
}

CImg<int> threshold(CImg<int>& tmp, int prog){
    /*
     threshold 3d image with "prog" threshold
     */
    CImg<int> img(tmp);
    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            for (int k = 0; k < img.depth(); k++) {
                if ((int) img(i, j, k) > prog)
                    img(i, j, k) = 3071;
                else
                    img(i, j, k) = -2048;
            }
        }
    }
    return img;
}

CImg<int> findComponents(CImg<int>& imgA) {
    /*
     find connected components of thresholded 3d image
     */
    int i, j;

    queue <Pixel> kolejka;

    CImg<int> tmp(imgA);
    tmp.fill(0);
    int N = 0;

    for (int k = 0; k < img.depth(); k++) {
        for (int i = 0; i < img.width(); i++) {
            for (int j = 0; j < img.height(); j++) {
                //main loop
                if (img(i, j, k) == 3071 && tmp(i, j, k) == 0) {
                    N++;
                    tmp(i, j, k) = N;
                    kolejka.push(Pixel(i, j, k));
                    while (!kolejka.empty()) {
                        Pixel Q = kolejka.front();
                        kolejka.pop();
                        for (int itmp = Q.x - 1; itmp <= Q.x + 1; itmp++) {
                            if (itmp > -1 && itmp < img.width())
                                for (int jtmp = Q.y - 1; jtmp <= Q.y + 1; jtmp++) {
                                    if (jtmp > -1 && jtmp < img.height()) {
                                        for (int ktmp = Q.z - 1; ktmp <= Q.z + 1; ktmp++)
                                            if (ktmp > -1 && ktmp < img.depth()) {
                                                if (img(itmp, jtmp, ktmp) == 3071 && tmp(itmp, jtmp, ktmp) == 0) {
                                                    kolejka.push(Pixel(itmp, jtmp, ktmp));
                                                    tmp(itmp, jtmp, ktmp) = N;
                                                }
                                            }
                                    }
                                }
                        }
                    }
                }
            }
        }
    }
    return tmp;
}


CImg<int> findFromPoint(CImg<int>& imgA, int i, int j, int k){
    /*
     find connected component starting from point given by i, j, k,
    of thresholded 3d image
     */
    queue <Pixel> kolejka;

    CImg<int> tmp(imgA);
    tmp.fill(0);
    int N = 1;
    tmp(i, j, k) = N;
    kolejka.push(Pixel(i, j, k));
    while (!kolejka.empty()) {
        Pixel Q = kolejka.front();
        kolejka.pop();
        for (int itmp = Q.x - 1; itmp <= Q.x + 1; itmp++) {
            if (itmp > -1 && itmp < img.width())
                for (int jtmp = Q.y - 1; jtmp <= Q.y + 1; jtmp++) {
                    if (jtmp > -1 && jtmp < img.height()) {
                        for (int ktmp = Q.z - 1; ktmp <= Q.z + 1; ktmp++)
                            if (ktmp > -1 && ktmp < img.depth()) {
                                if (img(itmp, jtmp, ktmp) == -2048 && tmp(itmp, jtmp, ktmp) == 0) {
                                    kolejka.push(Pixel(itmp, jtmp, ktmp));
                                    tmp(itmp, jtmp, ktmp) = N;
                                }
                            }
                    }
                }
        }
    }
    tmp = tmp*(-1)+1;
    return tmp;
}
