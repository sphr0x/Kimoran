#include "Route.h"
#include <string>

Route::Route(Node & rSrc, Node & rDst, double distance):Edge(rSrc, rDst){
	this->m_distance = distance;
}

Route::Route(Node * Src, Node * Dst, double distance):Edge(*Src,*Dst){
	this->m_distance = distance;
}

Route::Route(std::string src, std::string dst, double distance):Edge(*new Node(src),*new Node(dst)){
	this->m_distance = distance;
}
std::string Route::toString2(){ // nur test
	std::string result;
	result = getSrcNode().getID() + " -> " + getDstNode().getID() + " | distance: " + std::to_string(m_distance);
	return result;
}

double Route::getWeight(){
	return m_distance;
}

Route::~Route()
{
}
