#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <ctime>

enum buldings {City=2, Town=1, Country = 0};
enum trees { Forest = 2, Grove = 1, Field = 0 };
enum relief { Mountains = 2, Hills = 1, Plain = 0 };
enum wet { Swamp = 1, Normal = 0, Dust = -1 };
enum owner { FirstPlayer = 1, Neutral = 0, SecondPlayer = -1 };

class Province
{	
private:
	
	static int CityId, TownId;

	bool riverBank;
	owner Owner;

	sf::ConvexShape Polygon;
	std::string CityName;

	buldings Buildings;
	trees Trees;
	relief Relief;
	wet Wet;

	int Industry;

	int Infr;

	int Supply;

	int Mob_Pop;

	int WinMarks;

	void Coloring(owner O);
public:
	
	//конструктор обычной провинции
	Province(sf::ConvexShape& P, buldings B, trees Tr, relief R, wet W, bool RB);

	//геттеры
	owner getOwner();

	std::string getCityName() {
		return CityName;		
	};

	sf::ConvexShape &getPolygon();



	buldings getBuildings();

	trees getTrees();

	relief getRelief();



	wet getWet();

	int getSupply();

	int getInfr();

	int getIndustry();	

	int getMob_Pop();

	int getWinMarks();
	
	bool getRiverBank();

	//сеттеры
	void setOwner(owner X);
	void setIndustry(int X);
	void setInfr(int X);
	void setSupply(int X);

	//метод
	sf::Vector2f getInsidePoint();
	
	
};

