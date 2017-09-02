#ifndef PORTEFEUILLE_H
#define PORTEFEUILLE_H

class Portefeuille
{
public:
	int depot(int montant);
	int retrait(int montant);
	int solde() const;

private:
	int _solde{0};
};

#endif

