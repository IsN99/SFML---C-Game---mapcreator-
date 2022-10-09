#pragma once

#include "Province.h"
#include <vector>
#include <list>
#include <cmath>

//������� � ��������� ���� � ������ ����

class Map
{
public:
	Map(std::vector <Province> &P);
	//Map();

	void Draw(sf::RenderWindow &W);
	
private:
	
	//���������

	void FillRiver(std::vector <Province>& P);

	void FillRoads(std::vector <Province>& P);

	std::vector <Province> Proves; //������������ ���������
	std::vector <std::vector <bool>> River;
	std::vector <std::vector <int>> Roads;
	 

	

	
};
