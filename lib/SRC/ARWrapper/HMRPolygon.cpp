#include <ARWrapper/HMRPolygon.hpp>

HMRPolygon::HMRPolygon(vector<HMRVertex> vertices){
    this->vertices = vertices;
}

vector<HMRVertex> HMRPolygon::getVertices(){
    return this->vertices;
}

void HMRPolygon::setVertices(vector<HMRVertex> vertices){
    this->vertices = vertices;
}

