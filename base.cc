#include "base.h"

#include <algorithm>
#include <iostream>

using namespace std;

base::Base::Base(const geomod::Point &coord) : p(coord)
{
	
}

void base::Base::add_UID(double arg1)
{
	UIDs.push_back(arg1);
}

double base::Base::get_bad_uid() const
{
	return bad_uid;
}

void base::Base::add_prospecteur(const Robot_Prosp &prosp)
{
	auto checker = [prosp](const Robot_Prosp &rp)
	{ return rp.getUID() == prosp.getUID(); };
	auto it = std::find_if(prospecteurs.begin(), prospecteurs.end(), checker);

	if (it != prospecteurs.end())
	{
		cout << message::identical_robot_uid(prosp.getUID());
		exit(EXIT_FAILURE);
	}
	
	else
	{
		prospecteurs.push_back(prosp);
	}
}

void base::Base::add_transport(const Robot_Trans &trans)
{
	auto checker = [trans](const Robot_Trans &rp)
	{ return rp.getUID() == trans.getUID(); };
	auto it = std::find_if(transporteurs.begin(), transporteurs.end(), checker);

	if (it != transporteurs.end())
	{
		cout << message::identical_robot_uid(trans.getUID());
		exit(EXIT_FAILURE);
	}
	else
		transporteurs.push_back(trans);
}

void base::Base::add_foreur(const Robot_For &foreur)
{
	auto checker = [foreur](const Robot_For &rp)
	{ return rp.getUID() == foreur.getUID(); };
	auto it = std::find_if(foreurs.begin(), foreurs.end(), checker);

	if (it != foreurs.end())
	{
		cout << message::identical_robot_uid(foreur.getUID());
		exit(EXIT_FAILURE);
	}
	else
		foreurs.push_back(foreur);
}
geomod::Point base::Base::getPoint() const
{

	return p;
}

void base::Base::add_communicateur(const Robot_Com &com)
{
	auto checker = [com](const Robot_Com &rp)
	{ return rp.getUID() == com.getUID(); };
	auto it = std::find_if(communicateurs.begin(), communicateurs.end(), checker);

	if (it != communicateurs.end())
	{
		cout << message::identical_robot_uid(com.getUID());
		exit(EXIT_FAILURE);
	}
	else
		communicateurs.push_back(com);
}

std::vector<double> base::Base::getUIDs() const
{
	return UIDs;
}

bool base::Base::is_valid() const
{
	bool valid(false);
	for (unsigned int i = 0; i < communicateurs.size(); i++)
	{
		if (geomod::areEqual(communicateurs[i].getPoint(), p) == true)
		{
			valid = true;
		}
	}
	return valid;
}

void base::Base::check_uids() const
{
	
	//std::cout<<"check_uids() called"<<endl;
	unsigned int i(0);
	unsigned int j(0);
	while (i < UIDs.size()) //for() serait plus simple mais j' avais des bugs sur Geany
	{
		while (j < UIDs.size())
		{
			if (i != j && UIDs[i] == UIDs[j])
			{
				cout << message::identical_robot_uid(UIDs[i]);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

bool base::Base::intersection(Base A, Base B)
{
	return geomod::intersect(A.p, rayon_base, B.p, rayon_base);
}

std::vector<Robot_Prosp> base::Base::getProspecteurs() const
{
	return prospecteurs;
}

std::vector<Robot_For> base::Base::getForeurs() const
{
	return foreurs;
}

std::vector<Robot_Trans> base::Base::getTransporteurs() const
{
	return transporteurs;
}

std::vector<Robot_Com> base::Base::getCommunicateurs() const
{
	return communicateurs;
}

double base::Base::getRessource() const
{
	return ressource;
}
void base::Base::setRessource(Base& b, double arg1) const
{
	b.ressource = arg1;
}

double base::Base::getBID() const
{
	return BID;
}
void base::Base::setBID(Base& b, double arg1) const
{
	b.BID = arg1;
}

void base::Base::setConnectionStatus(Base& b, double arg1, double arg2) const
{
	b.connectionStatus[arg1].push_back(arg2);
}
double base::Base::getConnectionStatus(double arg1, double arg2) const
{
	return connectionStatus[arg1][arg2];
}

Robot& base::Base::searchByUID(double uid)
{
	for(unsigned int i = 0; i < prospecteurs.size(); i++)
		if(prospecteurs[i].getUID()==uid)
			return prospecteurs[i];
			
	for(unsigned int i = 0; i < foreurs.size(); i++)
		if(foreurs[i].getUID()==uid)
			return foreurs[i];
			
	for(unsigned int i = 0; i < transporteurs.size(); i++)
		if(transporteurs[i].getUID()==uid)
			return transporteurs[i];
			
	for(unsigned int i = 0; i < communicateurs.size(); i++)
		if(communicateurs[i].getUID()==uid)
			return communicateurs[i];
}
/*
std::ostream &operator<<(std::ostream &os, const base::Base &base)
{
	os << base.p.x << " ";
	os << base.p.y << " ";
	//os << base.ressource << " "; TODO: faire l'affichage des ressources

	auto prospecteurs = base.getProspecteurs();
	auto communicateurs = base.getCommunicateurs();
	auto foreurs = base.getForeurs();
	auto transporteurs = base.getTransporteurs();

	os << prospecteurs.size() << " ";
	os << foreurs.size() << " ";
	os << transporteurs.size() << " ";
	os << communicateurs.size() << "\n";

	for (const auto& prosp : prospecteurs)
		os << prosp;
	for (const auto& foreur : foreurs)
		os << foreur;
	for (const auto& transporteur : transporteurs)
		os << transporteur;
	for (const auto& communicateur : communicateurs)
		os << communicateur;
	return os;
}
*/
