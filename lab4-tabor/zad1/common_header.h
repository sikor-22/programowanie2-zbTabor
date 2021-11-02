#pragma once

#include <math.h>

template<typename t>
class Punkt{
    private:
        t x;
        t y;
        float r;
    public:
        Punkt(t Ax, t Ay){
            x = Ax;
            y = Ay;
            r = pow((pow((float)x, 2)+pow((float)y, 2)), 0.5);
        }
        t const getX(){return x;}
        t const getY(){return y;}
        float const getR(){return r;}
        void setX(t Ax){
            x = Ax;
            r = pow((pow((float)x, 2)+pow((float)y, 2)), 0.5);
        }
        void setY(t Ay){
            y = Ay;
            r = pow((pow((float)x, 2)+pow((float)y, 2)), 0.5);
        }
        bool operator <(Punkt& other){
            if(r<other.getR()){
                return true;
            }
            return false;
        }
        bool operator >(Punkt& other){
            if(r>other.getR()){
                return true;
            }
            return false;
        }
};


template<typename t>
t& Max(t& a, t& b){
    if(a>b){
        return a;
    }
    return b;
}