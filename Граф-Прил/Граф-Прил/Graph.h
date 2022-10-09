#pragma once

class Graph
{	
public:
	
	virtual ~Graph() {};


	virtual void AddVertex() = 0;
	virtual void AddEdge(int from, int to) = 0;
	virtual bool HasEdge(int from, int to) = 0;
	virtual int CountVertex() = 0;
};

