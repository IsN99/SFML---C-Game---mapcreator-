#pragma once

#include "Graph.h"

class MatrixGraph: public Graph
{
private:
	int VertexNum;
	bool** GraphEdges;
public:
	MatrixGraph(int n);
	MatrixGraph(const MatrixGraph &other);
	MatrixGraph(MatrixGraph&& other);

	MatrixGraph& operator = (const MatrixGraph& other);
	MatrixGraph& operator = (MatrixGraph&& other);
	
	bool operator == (const MatrixGraph& other);
	bool operator != (const MatrixGraph& other);

	//interface
	~MatrixGraph() override;

	void AddVertex() override;
	void AddEdge(int from, int to) override;
	bool HasEdge(int from, int to) override;
	int CountVertex() override;
	
	//option
	void Print();
};

MatrixGraph FillEdges();

