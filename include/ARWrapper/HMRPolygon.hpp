#include <stdio.h>
#include <iostream>
#include <vector>
#include <opencv/cv.hpp>
#include <ARWrapper/HMRVertex.hpp>


using namespace std;
using namespace cv;

class HMRPolygon {
    
    private:
        vector<HMRVertex> vertices;
    
    public:
        HMRPolygon(vector<HMRVertex> vertices);
        vector<HMRVertex> getVertices();
        void setVertices(vector<HMRVertex> vertices);
    
};