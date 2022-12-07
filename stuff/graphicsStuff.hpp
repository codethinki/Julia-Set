#pragma once
#include <iostream>
#include <Windows.h>
#include <glm/glm.hpp>
#include <string>

inline float dist(float x1, float y1, float x2, float y2) { return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); }

double map(double input, double inputMin, double inputMax, double outputMin, double outputMax) {
	 return outputMin + (outputMax - outputMin) * ((input - inputMin) / (inputMax - inputMin));
}

bool inbetween1d(float movingPoint, float point1, float point2) {
	using namespace std;
	if (point1 == point2) {
		throw runtime_error("function inbetween1d point1 = point2 Point1 & Point2 = " + to_string(point1));
	} else if (point1 < point2 && point1 <= movingPoint && movingPoint <= point2) {
		return true;
	} else if (point1 > point2 && point1 >= movingPoint && movingPoint >= point2) {
		return true;
	}
	return false;
}
bool inbetween2d(float movingPointX, float point1X, float point2X, float movingPointY, float point1Y, float point2Y) {
	if (inbetween1d(movingPointX, point1X, point2X) && inbetween1d(movingPointY, point1Y, point2Y)) {
		return true;
	}
	return false;
}