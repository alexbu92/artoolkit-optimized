#include <AR/ar.h>
class HMRVertex {
    
    private:
        double x;
        double y;
		

    public:
		ARMarkerInfo markerInfo;
		bool isMarkerInit;
		HMRVertex(double x, double y, ARMarkerInfo* t_markerInfo);
        float getX();
        void setX(double x);
        float getY();
        void setY(double y);
};