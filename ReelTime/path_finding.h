#pragma once
#include <map>
#include <list>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "map_game.h"

class PathFinding{
public:
	PathFinding();
	bool deja_present_dans_liste(std::pair<int, int> n, l_noeud& l);
	std::pair<int, int> meilleur_noeud(l_noeud& l);
	void ajouter_cases_adjacentes(std::pair <int, int>& n, MapGame* map);
	void findRoad(MapGame* map, const int start_x, const int start_y, const int end_x, const int end_y);
	void ajouter_liste_fermee(std::pair<int, int>& p);
	void retrouver_chemin();
	float distance(int x1, int y1, int x2, int y2);
	void resetPath();

	l_noeud liste_ouverte;
	l_noeud liste_fermee;
	std::list<point> chemin;

	struct point arrivee;
	noeud depart;

private:
};
