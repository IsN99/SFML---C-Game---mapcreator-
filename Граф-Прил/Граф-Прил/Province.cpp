#include "Province.h"

int Province::CityId = 0;
int Province::TownId = 0;

Province::Province(sf::ConvexShape& P, buldings B, trees Tr, relief R, wet W, bool RB) {
	P.setOutlineColor(sf::Color::Black);
	P.setOutlineThickness(-0.25);
	Polygon = P;
	Buildings = B;
	Trees = Tr;
	Relief = R;
	Wet = W;
	
	srand(time(NULL));

	riverBank = RB;
	Owner = Neutral;

	switch (B) {
	case City:
		Industry = 6;
		break;
	case Town:
		Industry = 3;
		break;
	case Country:
		Industry = 1;
		break;
	}

	switch (B) {
	case City:
		Infr = rand() % 3 + 5;
		break;
	case Town:
		Infr = rand() % 3 + 3;
		break;
	case Country:
		Infr = rand() % 3;
		break;
	}

	switch (B) {
	case City:
		Supply = 4000 + rand() % 1000;
		break;
	case Town:
		Supply = 1500 + rand() % 1000;
		break;
	case Country:
		Supply = rand() % 1000;
		break;
	}
	
	switch (B) {
	case City:
		Mob_Pop = 1000000;
		break;
	case Town:
		Mob_Pop = 250000;
		break;
	case Country:
		Mob_Pop = 25000;
		break;
	}
	switch (B) {
	case City:
		WinMarks = 9;
		break;
	case Town:
		WinMarks = 3;
		break;
	case Country:
		WinMarks = 1;
		break;
	}
	
	switch (B) {
	case City:
		CityName = "City"+CityId;
		break;
	case Town:
		CityName = "Town" + CityId;;
		break;
	case Country:
		CityName = "";
		break;
	}

	Coloring(Owner);
	
};

//геттеры


owner Province::getOwner() {
	return this->Owner;
}

sf::ConvexShape& Province:: getPolygon() {
	return this->Polygon;
}



buldings Province::getBuildings() {
	return Buildings;
}
trees Province::getTrees() {
	return Trees;
}
relief Province::getRelief() {
	return Relief;
}
wet Province:: getWet() {
	return Wet;
}

int Province::getIndustry() {
	return Industry;
}
int Province:: getInfr() {
	return Infr;
}
int Province:: getSupply() {
	return Supply;
}
int Province:: getMob_Pop() {
	return Mob_Pop;
}
int Province:: getWinMarks() {
	return WinMarks;
}
bool Province:: getRiverBank() {
	return riverBank;
}

//сеттеры
void Province::setOwner(owner X) {
	Owner = X;
	void Coloring(owner X);
}


void Province:: setIndustry(int X) {
	Industry = X;
}

void Province:: setInfr(int X) {
	Infr = X;
}
	
void Province:: setSupply(int X) {
	Supply = X;
}

sf::Vector2f Province::getInsidePoint() {
	float X = 0;
	float Y = 0;
	for (int i = 0; i < Polygon.getPointCount(); i++) {
		X += Polygon.getPoint(i).x;
		Y += Polygon.getPoint(i).y;
	}
	 sf::Vector2f Temp(X, Y);
	 return Temp;
}

void Province::Coloring(owner O)
{
	switch (O) {
	case FirstPlayer:
		this->Polygon.setFillColor(sf::Color::Color(255, 255, 255, 100));
		break;
	case SecondPlayer:
		this->Polygon.setFillColor(sf::Color::Color(255, 0, 0, 100));
		break;
	case Neutral:
		this->Polygon.setFillColor(sf::Color::Transparent);
		break;
	}
}