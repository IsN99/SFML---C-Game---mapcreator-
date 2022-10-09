#include "MatrixGraph.h"
#include <iostream>

//конструктор 1
MatrixGraph::MatrixGraph(int n) : VertexNum (n)
{
	GraphEdges = new bool* [VertexNum];
	for (int i = 0; i < VertexNum; i++)
	{
		GraphEdges [i] = new bool[VertexNum];
		for (int j = 0; j < VertexNum; j++)
		{
			GraphEdges[i][j] = false;
		}
	}

}
//конструтор копирования
MatrixGraph::MatrixGraph(const MatrixGraph& other) {
	this->VertexNum = other.VertexNum;
	this->GraphEdges = new bool* [VertexNum];
	for (int i = 0; i < VertexNum; i++)
	{
		GraphEdges[i] = new bool[VertexNum];
		for (int j = 0; j < VertexNum; j++)
		{
			this->GraphEdges[i][j] = other.GraphEdges[i][j];
		}
	}
}
//конструктор переноса
MatrixGraph::MatrixGraph(MatrixGraph&& other) {
	this->VertexNum = other.VertexNum;
	this->GraphEdges = other.GraphEdges;
	other.GraphEdges = nullptr;
}
//оператор присваивания (копирования)
MatrixGraph& MatrixGraph::  operator = (const MatrixGraph& other) {
	//проверка и удаление
	if (GraphEdges != nullptr) {
		for (int i = 0; i < VertexNum; i++)
		{
			if (GraphEdges[i] != nullptr) {
				delete[] GraphEdges[i];
			}
		}
		delete[] GraphEdges;
	}
	//копирование
	this->VertexNum = other.VertexNum;
	this->GraphEdges = new bool* [VertexNum];
	for (int i = 0; i < VertexNum; i++)
	{
		GraphEdges[i] = new bool[VertexNum];
		for (int j = 0; j < VertexNum; j++)
		{
			this->GraphEdges[i][j] = other.GraphEdges[i][j];
		}
	}
	return *this;
}
//оператор переноса
MatrixGraph& MatrixGraph:: operator = (MatrixGraph&& other) {
	//проверка и удаление
	if (GraphEdges != nullptr) {
		for (int i = 0; i < VertexNum; i++)
		{
			if (GraphEdges[i] != nullptr) {
				delete[] GraphEdges[i];
			}
		}
		delete[] GraphEdges;
	}
	//перенос
	this->VertexNum = other.VertexNum;
	this->GraphEdges = other.GraphEdges;
	other.GraphEdges = nullptr;
	return *this;
}
//проверка на равенство
bool MatrixGraph::operator == (const MatrixGraph& other) {
	
	if (this->VertexNum != other.VertexNum) {
		return false;
	} else 
	
	for (int i = 0; i < VertexNum; i++)
	{
		for (int j = 0; j < VertexNum; j++)
		{
			if (this->GraphEdges[i][j] != other.GraphEdges[i][j]) {
				return false;
			}
		}
	}
	return true;
}
//провекрка на неравенство
bool MatrixGraph::operator != (const MatrixGraph& other) {
	if (this->VertexNum != other.VertexNum) {
		return true;
	}
	else
		for (int i = 0; i < VertexNum; i++)
		{
			for (int j = 0; j < VertexNum; j++)
			{
				if (this->GraphEdges[i][j] != other.GraphEdges[i][j]) {
					return true;
				}
			}
		}
	return false;
}
//деструктор
MatrixGraph::~MatrixGraph() {
	
	if (GraphEdges != nullptr) {
		for (int i = 0; i < VertexNum; i++)
		{
			if (GraphEdges[i] != nullptr) {
				delete[] GraphEdges[i];
			}
		}
		delete[] GraphEdges;
	}
}

//добавить вершину
void MatrixGraph::AddVertex() {
	MatrixGraph Temp(this->VertexNum + 1);
		for (int i = 0; i < this->VertexNum; i++)
	{
		for (int j = 0; j < this->VertexNum; j++) 
		{
			Temp.GraphEdges[i][j] = this->GraphEdges[i][j];
		}
	}

	if (GraphEdges != nullptr) 
		
	{
		for (int i = 0; i < VertexNum; i++)
		{
			if (GraphEdges[i] != nullptr) 
			{
				delete[] GraphEdges[i];
			}
		}
			delete[] GraphEdges;
		}
	this->VertexNum = Temp.VertexNum;
	this->GraphEdges = Temp.GraphEdges;
	Temp.GraphEdges = nullptr;
}
//добавить ребро
void MatrixGraph::AddEdge(int from, int to) {
	if (from < 0 || from >= VertexNum || to < 0 || to >= VertexNum) { return; }
	GraphEdges[from][to] = true;
}
//проверка на наличие ребра
bool MatrixGraph::HasEdge(int from, int to) {
	if (from < 0 || from >= VertexNum || to < 0 || to >= VertexNum) { return false; }
	return (GraphEdges[from][to] == true);
}
int MatrixGraph::CountVertex() {
	return VertexNum;
}

//опция
void MatrixGraph::Print()
{
	for (int i = 0; i < VertexNum; i++) {
		for (int j = 0; j < VertexNum; j++) {
			if (GraphEdges[i][j] == true)
			{
				std::cout << i << "->" << j << std::endl;
			}
		}
	}
}

MatrixGraph FillEdges()
{
	setlocale(LC_ALL, "rus");
	std::cout << "Введите количество вершин в графе" << std::endl;
	int Y;
	std::cin >> Y;
	MatrixGraph A(Y);
	std::cout << "Введите количество ребер" << std::endl;
	int X;
	std::cin >> X;
	for (int i = 0; i < X; i++) {
		std::cout << "Ввод " << i << "-ого ребра" << std::endl << std::endl;
		int a;
		int b;
		std::cout << "Введите первую вершину" << std::endl;
		std::cin >> a;
		std::cout << "Введите вторую вершину" << std::endl;
		std::cin >> b;
		A.AddEdge(a, b);
	}
	return A;
}
