#include "point_belongs.h"

int point_belongs(float x, float y, std::vector<sf::ConvexShape>& Polygon) { //проверяет какому полигону пренадлежит точка
	
	for (int i = 0; i < Polygon.size(); i++) {
		
		bool belong = false;
		for (int j = 0; j < Polygon[i].getPointCount(); j++) {
			bool FCondition = (Polygon[i].getPoint(j).x <= x && Polygon[i].getPoint((j + 1) % Polygon[i].getPointCount()).x >= x);
			bool SCondition = (Polygon[i].getPoint(j).x >= x && Polygon[i].getPoint((j + 1) % Polygon[i].getPointCount()).x <= x);
			float h = (Polygon[i].getPoint(j).y - Polygon[i].getPoint((j + 1) % Polygon[i].getPointCount()).y);
			float b = ((Polygon[i].getPoint(j).x - Polygon[i].getPoint((j + 1) % Polygon[i].getPointCount()).x));
			float d = (x - Polygon[i].getPoint(j).x);
			bool TCondition = (Polygon[i].getPoint(j).y + (float)(h / b * d)) < y;

		

			if ((FCondition || SCondition) && TCondition)
			{
				belong = !belong;
				
			}
			//std::cout << belong << std::endl;
		}
		if (belong) return i;
	}

	return -1;
}

