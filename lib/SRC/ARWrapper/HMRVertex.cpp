#include <ARWrapper/HMRVertex.hpp>
#include <cstring>

HMRVertex::HMRVertex(double x, double y, ARMarkerInfo* t_markerInfo){
    this->x = x;
    this->y = y;
	if (t_markerInfo != NULL) {
		this->markerInfo = *t_markerInfo;
		isMarkerInit = true;
	}
	else {
		isMarkerInit = false;
	}

}

float HMRVertex::getX(){
    return this->x;
}

void HMRVertex::setX(double x){
    this->x = x;
}

float HMRVertex::getY(){
    return this->y;
}

void HMRVertex::setY(double y){
    this->y = y;
}

