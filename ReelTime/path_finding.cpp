#include "path_finding.h"

PathFinding::PathFinding() {

}

void PathFinding::resetPath()
{
	std::cout << "reset path " << std::endl;
	this->liste_ouverte.empty();
	this->liste_fermee.empty();
	this->chemin.empty();	
	this->arrivee.x = 0;
	this->arrivee.y = 0;
	this->depart.cout_f = 0;
	this->depart.cout_g = 0;
	this->depart.cout_h = 0;
}

void PathFinding::findRoad(MapGame* map, const int start_x, const int start_y, const int end_x, const int end_y)
{
	this->arrivee.x = end_x;
	this->arrivee.y = end_y;

	this->depart.parent.first = start_x;
	this->depart.parent.second = start_y;

	std::pair <int, int> courant(this->depart.parent.first, this->depart.parent.second);

	/* déroulement de l'algo A* */
	// ajout de courant dans la liste ouverte

	this->liste_ouverte[courant] = this->depart;
	this->ajouter_liste_fermee(courant);
	this->ajouter_cases_adjacentes(courant, map);

	while (!((courant.first == this->arrivee.x) && (courant.second == this->arrivee.y))
		&&
		(!this->liste_ouverte.empty())
		) {


		// on cherche le meilleur noeud de la liste ouverte, on sait qu'elle n'est pas vide donc il existe
		courant = this->meilleur_noeud(this->liste_ouverte);

		// on le passe dans la liste fermee, il ne peut pas déjà y être
		this->ajouter_liste_fermee(courant);

		this->ajouter_cases_adjacentes(courant, map);
	}

	if ((courant.first == this->arrivee.x) && (courant.second == this->arrivee.y)) {
		this->retrouver_chemin();
	}
	else {
		/* pas de solution */
		std::cout << "errreuurrrr" << std::endl;
	}
}

float PathFinding::distance(int x1, int y1, int x2, int y2) {
	//return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}


bool PathFinding::deja_present_dans_liste(std::pair<int, int> n, l_noeud& l) {
	l_noeud::iterator i = l.find(n);
	if (i == l.end())
		return false;
	else
		return true;
}

std::pair<int, int> PathFinding::meilleur_noeud(l_noeud& l) {
	float m_coutf = l.begin()->second.cout_f;
	std::pair<int, int> m_noeud = l.begin()->first;

	for (l_noeud::iterator i = l.begin(); i != l.end(); i++)
		if (i->second.cout_f< m_coutf) {
			m_coutf = i->second.cout_f;
			m_noeud = i->first;
		}

	return m_noeud;
}

void PathFinding::ajouter_cases_adjacentes(std::pair <int, int>& n, MapGame* map) {
	noeud tmp;

	// on met tous les noeud adjacents dans la liste ouverte (+vérif)
	for (int i = n.first - 1; i <= n.first + 1; i++) {
		if ((i<0) || (i >= map->width))
			continue;
		for (int j = n.second - 1; j <= n.second + 1; j++) {
			if ((j<0) || (j >= map->height))
				continue;
			if ((i == n.first) && (j == n.second))  // case actuelle n
				continue;
			if (map->getOnThisPositionNoeud(i, j)->passable == false)
				// obstace, terrain non franchissable
				continue;
			// it for 4 direction onlye - remove if you wanna 8 direction
			if (((i == n.first - 1 || i == n.first + 1) && j == n.second) || ((j == n.second - 1 || j == n.second + 1) && i == n.first))
			{
				std::pair<int, int> it(i, j);

				if (!this->deja_present_dans_liste(it, this->liste_fermee)) {
					/* le noeud n'est pas déjà présent dans la liste fermée */

					tmp.cout_g = this->liste_fermee[n].cout_g + this->distance(i, j, n.first, n.second) + map->getOnThisPositionNoeud(i, j)->weight;
					tmp.cout_h = this->distance(i, j, this->arrivee.x, this->arrivee.y);
					tmp.cout_f = tmp.cout_g + tmp.cout_h;
					tmp.parent = n;

					if (this->deja_present_dans_liste(it, liste_ouverte)) {
						/* le noeud est déjà présent dans la liste ouverte, il faut comparer les couts */
						if (tmp.cout_f < this->liste_ouverte[it].cout_f) {
							/* si le nouveau chemin est meilleur, on update */
							this->liste_ouverte[it] = tmp;
						}

						/* le noeud courant a un moins bon chemin, on ne change rien */


					}
					else {
						/* le noeud n'est pas présent dans la liste ouverte, on l'ajoute */
						this->liste_ouverte[std::pair<int, int>(i, j)] = tmp;
					}
				}
			}
		}
	}
}


void PathFinding::ajouter_liste_fermee(std::pair<int, int>& p) {
	noeud& n = this->liste_ouverte[p];
	this->liste_fermee[p] = n;

	// il faut le supprimer de la liste ouverte, ce n'est plus une solution explorable
	if (this->liste_ouverte.erase(p) == 0)
		std::cout << "n'apparait pas dans la liste ouverte, impossible à supprimer" << std::endl;
	return;
}

void PathFinding::retrouver_chemin() {
	// l'arrivée est le dernier élément de la liste fermée.
	noeud& tmp = this->liste_fermee[std::pair<int, int>(arrivee.x, arrivee.y)];

	struct point n;
	std::pair<int, int> prec;
	n.x = this->arrivee.x;
	n.y = this->arrivee.y;
	prec.first = tmp.parent.first;
	prec.second = tmp.parent.second;
	this->chemin.push_front(n);

	while (prec != std::pair<int, int>(this->depart.parent.first, this->depart.parent.second)) {
		n.x = prec.first;
		n.y = prec.second;
		this->chemin.push_front(n);

		tmp = this->liste_fermee[tmp.parent];
		prec.first = tmp.parent.first;
		prec.second = tmp.parent.second;
	}
}
