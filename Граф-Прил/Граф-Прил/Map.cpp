#include "Map.h"

Map::Map(std::vector <Province>& P) {
	Proves = P;
	FillRiver(P);
	FillRoads(P);
}



void Map:: FillRiver(std::vector <Province>& P){

	for (int i = 0; i < P.size(); i++) {
		std::vector <bool> t(0);
			
		for (int j = 0; j < P.size(); j++) {
			bool b = false;
			t.push_back(b);
		}
		River.push_back(t);
	}
	for (int i = 0; i < P.size(); i++) {
		if (P[i].getRiverBank()) {
			for (int j = 0; j < P.size(); j++) {
				if (P[j].getRiverBank() && i != j && (River[i][j] != true && River[j][i] != true)) {

					for (int pc1 = 0; pc1 < P[i].getPolygon().getPointCount(); pc1++) {

						for (int pc2 = 0; pc2 < P[j].getPolygon().getPointCount(); pc2++) {
							if (P[i].getPolygon().getPoint(pc1) == P[j].getPolygon().getPoint(pc2)) {
								River[j][i] = true;
								River[i][j] = true;
								break;
							}
						}

						if (River[j][i] == true && River[i][j] == true)
							break;
					}
				}
			}
		}

	}

}

void Map::FillRoads(std::vector <Province>& P) {
	for (int i = 0; i < P.size(); i++) {
		std::vector <int> t(0);

		for (int j = 0; j < P.size(); j++) {
			int b = 0;
			t.push_back(b);
		}
		Roads.push_back(t);
	}
	for (int i = 0; i < P.size(); i++) {
		for (int j = 0; j < P.size(); j++) {
			if (i != j && (Roads[i][j] == 0 && Roads[j][i] == 0)) {

				for (int pc1 = 0; pc1 < P[i].getPolygon().getPointCount(); pc1++) {

					for (int pc2 = 0; pc2 < P[j].getPolygon().getPointCount(); pc2++) {
						if (P[i].getPolygon().getPoint(pc1) == P[j].getPolygon().getPoint(pc2)) {
							int x2 = (P[i].getInsidePoint().x - P[j].getInsidePoint().x) * (P[i].getInsidePoint().x - P[j].getInsidePoint().x);
							int y2 = (P[i].getInsidePoint().y - P[j].getInsidePoint().y) * (P[i].getInsidePoint().y - P[j].getInsidePoint().y);
							River[j][i] = sqrt(x2 + y2);
							River[i][j] = sqrt(x2 + y2);
							break;
						}
					}

					if (River[j][i] != 0 && River[i][j] != 0)
						break;
				}
			}
		}
	}
}

void  Map::Draw(sf::RenderWindow& W) {
	for (int i = 0; i < Proves.size(); i++) {
		W.draw(Proves[i].getPolygon());		
	}
	for (int i = 0; i < Proves.size(); i++) {		
		if (Proves[i].getCityName() != "Country") {
			sf::Text CName;
			CName.setCharacterSize(8);
			CName.setFillColor(sf::Color::Black);
			sf::Font font;
			font.loadFromFile("arial.ttf");
			CName.setFont(font);
			CName.setString(Proves[i].getCityName());
			CName.setPosition(Proves[i].getInsidePoint());
			W.draw(CName);
		}		
	}	
}