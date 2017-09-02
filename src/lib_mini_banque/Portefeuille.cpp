#include "Portefeuille.h"

int
Portefeuille::depot(int montant)
{
	if (montant > 0 && (montant % 5) == 0) {
		_solde += montant;
	}
	return _solde;
}

int
Portefeuille::retrait(int montant)
{
	if (montant > 0 && montant <= _solde && (montant % 5) == 0) {
		_solde -= montant;
	}
	return _solde;
}

int
Portefeuille::solde() const
{
	return _solde;
}

