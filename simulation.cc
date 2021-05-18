#include "simulation.h"
#include "constantes.h"

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void simulation::Lecture(const std::string &filename)
{
	varglo abc;

	abc.mode = 0;

	string l;
	string m;
	vector<string> ls;

	ifstream ifs(filename);

	if (!ifs.fail())
	{
		while (getline(ifs, l))
		{
			istringstream ss(l);

			while (ss >> m)
				ls.push_back(m);

			if (ls[0][0] == '#' || ls.size() == 0)
			{
				ls.clear();
				continue;
			}

			assignLine(abc, ls);

			ls.clear();
		}
		ifs.close();
	}
	else
		cout << "error reading file" << endl;
}
/*
void simulation::Ecriture(varglo abc, const std::string &filename)
{
	std::ofstream ofs(filename);

	if (!ofs.is_open())
		return ;

	ofs << abc.Gisements.size();
	for (const auto& gisement : abc.Gisements)
		ofs << gisement;

	ofs << abc.Bases.size();
	for (const auto& base : abc.Bases)
		ofs << base;

	ofs.close();
}
*/
void simulation::assignLine(varglo &abc, vector<string> vs)
{
	switch (abc.mode)
	{
	case 0:
		assignCase0(abc, vs);
		break;
	case 1:
		assignCase1(abc, vs);
		break;
	case 2:
		assignCase2(abc, vs);
		break;
	case 3:
		assignCase3(abc, vs);
		break;
	case 4:
		assignCase4(abc, vs);
		break;
	case 5:
		assignCase5(abc, vs);
		break;
	case 6:
		assignCase6(abc, vs);
		break;
	}
}

void simulation::assignCase0(varglo &abc, std::vector<std::string> vs)
{
	abc.mode++;
	abc.nbG = stod(vs[0]);
}

void simulation::assignCase1(varglo &abc, std::vector<std::string> vs)
{
	if (abc.nbG == 0)
	{
		abc.nbB = stod(vs[0]);
		abc.mode++;
		return;
	}
	if (vs.size() != 4)
	{
		exit(EXIT_FAILURE);
	}

	gisement::Gisement g(stod(vs[0]), stod(vs[1]));
	g.rayon = stod(vs[2]);
	g.capacite = stod(vs[3]);

	abc.Gisements.push_back(g);

	abc.nbG--;
}

void simulation::assignCase2(varglo &abc, std::vector<std::string> vs)
{
	geomod::Point p(stod(vs[0]), stod(vs[1]));

	base::Base b(p);
	b.setRessource(b, stod(vs[2]));
	b.setBID(b, abc.Bases.size());
	
	
	abc.Bases.push_back(b);
	abc.nbP = stod(vs[3]);
	abc.nbF = stod(vs[4]);
	abc.nbT = stod(vs[5]);
	abc.nbC = stod(vs[6]);

	if (abc.nbC == 0)
	{
		cout << message::missing_robot_communication(b.getPoint().x, b.getPoint().y);
		exit(EXIT_FAILURE);
	}

	abc.mode++;

	abc.nbB--;
}

void simulation::assignCase3(varglo &abc, std::vector<std::string> vs)
{
	if (abc.nbP == 0)
	{
		abc.mode++;
		assignCase4(abc, vs);
	}
	else
	{
		
		Robot_Prosp rP;
		//uid dp x y xb yb atteint retour found xg yg rayong capaciteg 
		rP.setUID(rP, stod(vs[0]));
		rP.setDp(rP, stod(vs[1]));
		geomod::Point p(stod(vs[2]),stod(vs[3]));
		rP.setPoint(rP, p);
		geomod::Point but(stod(vs[4]), stod(vs[5]));
		rP.setBut(rP, but);
		rP.setAtteint(rP, to_bool(vs[6]));
		rP.setRetour(rP, stod(vs[7]));
		rP.setFound(rP, to_bool(vs[8]));
		
		if(rP.getFound()==true)
		{
			gisement::Gisement g;
			geomod::Point gCentre(stod(vs[9]),stod(vs[10]));
			g.centre = gCentre;
			g.rayon = stod(vs[11]);
			g.capacite = stod(vs[12]);
			
			rP.setGisementFound(rP, g);
		}
		
		abc.Bases[abc.whichBase].base::Base::add_prospecteur(rP);
		abc.Bases[abc.whichBase].add_UID(stod(vs[0]));
		abc.nbP--;
	}
}

void simulation::assignCase4(varglo &abc, std::vector<std::string> vs)
{
	if (abc.nbF == 0)
	{
		abc.mode++;
		assignCase5(abc, vs);
	}

	else
	{
		Robot_For rF;
		rF.setUID(rF, stod(vs[0]));
		
		rF.setDp(rF, stod(vs[1]));
		geomod::Point p(stod(vs[2]),stod(vs[3]));
		rF.setPoint(rF, p);
		geomod::Point but(stod(vs[4]), stod(vs[5]));
		rF.setBut(rF, but);
		rF.setAtteint(rF, to_bool(vs[6]));
		
		
		abc.Bases[abc.whichBase].base::Base::add_foreur(rF);
		abc.Bases[abc.whichBase].add_UID(stod(vs[0]));
		abc.nbF--;
	}
}

void simulation::assignCase5(varglo &abc, std::vector<std::string> vs)
{
	if (abc.nbT == 0)
	{
		abc.mode++;
		assignCase6(abc, vs);
	}
	else
	{
		Robot_Trans rT;
		rT.setUID(rT, stod(vs[0]));
		
		rT.setDp(rT, stod(vs[1]));
		geomod::Point p(stod(vs[2]),stod(vs[3]));
		rT.setPoint(rT, p);
		geomod::Point but(stod(vs[4]), stod(vs[5]));
		rT.setBut(rT, but);
		rT.setAtteint(rT, to_bool(vs[6]));
		rT.setRetour(rT, stod(vs[7]));
		
		abc.Bases[abc.whichBase].base::Base::add_transport(rT);
		abc.Bases[abc.whichBase].add_UID(stod(vs[0]));

		abc.nbT--;
	}
}

void simulation::assignCase6(varglo &abc, std::vector<std::string> vs)
{
	Robot_Com rC;
	rC.setUID(rC, stod(vs[0]));
	
	rC.setDp(rC, stod(vs[1]));
	geomod::Point po(stod(vs[2]), stod(vs[3]));
	rC.setPoint(rC, po);
	geomod::Point but(stod(vs[4]), stod(vs[5]));
	rC.setBut(rC, but);
	rC.setAtteint(rC, to_bool(vs[6]));
	
	abc.Bases[abc.whichBase].base::Base::add_communicateur(rC);
	abc.Bases[abc.whichBase].add_UID(stod(vs[0]));
	abc.nbC--;

	if (abc.nbC == 0)
	{
		for (size_t i = 0; i < abc.Bases.size(); i++)
		{
			if (abc.Bases[i].is_valid() == false)
			{
				cout << message::missing_robot_communication(abc.Bases[i].getPoint().x, abc.Bases[i].getPoint().y);
				exit(EXIT_FAILURE);
			}
			abc.Bases[i].check_uids();
		}

		if (abc.nbB == 0)
		{
			for (unsigned int i = 0; i < abc.Gisements.size(); i++)
			{
				for (unsigned int j = 0; j < abc.Gisements.size(); j++)
				{
					if (i == j)
						continue;
					if (gisement::Gisement::intersection_g(abc.Gisements[i], abc.Gisements[j]) == true)
					{
						cout << message::field_superposition(abc.Gisements[i].centre.x, abc.Gisements[i].centre.y, abc.Gisements[j].centre.x, abc.Gisements[j].centre.y);
						exit(EXIT_FAILURE);
					}
				}
			}

			for (unsigned int i = 0; i < abc.Bases.size(); i++)
			{
				for (unsigned int j = 0; j < abc.Bases.size(); j++)
				{
					if (i == j)
						continue;
					if (base::Base::intersection(abc.Bases[i], abc.Bases[j]) == true)
					{
						cout << message::base_superposition(abc.Bases[i].getPoint().x, abc.Bases[i].getPoint().y, abc.Bases[j].getPoint().x, abc.Bases[j].getPoint().y);
						exit(EXIT_FAILURE);
					}
				}
			}

			for (unsigned int i = 0; i < abc.Bases.size(); i++)
			{
				for (unsigned int j = 0; j < abc.Gisements.size(); j++)
				{
					if (geomod::intersect(abc.Bases[i].getPoint(), rayon_base, abc.Gisements[j].centre, abc.Gisements[j].rayon) == true)
					{
						cout << message::base_field_superposition(abc.Bases[i].getPoint().x, abc.Bases[i].getPoint().y, abc.Gisements[j].centre.x, abc.Gisements[j].centre.y);
						exit(EXIT_FAILURE);
					}
				}
			}
			cout << message::success();

			exit(EXIT_SUCCESS);
		}
		else
		{
			abc.mode = 2;
			abc.whichBase++;
		}
	}
}

bool simulation::to_bool(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	istringstream is(str);
	bool b;
	is >> boolalpha >> b;
	return b;
}


void simulation::sim(varglo abc) //theoriquement au lieu de abc ca doit etre Bases.
{
	//a optimiser:
	///algo de forage
	///algo de transport
	///algo de placement des robots_com
	///importance des gisements
	
	for(unsigned int i = 0; i < abc.Bases.size(); i++)
	{
		for(unsigned int j = 0; j < abc.Bases.size(); j++)
		{
			updateVoisin(abc.Bases[i], abc.Bases[j]);       //chaque robot update son vecteur voisinUIDs.
		}
		
		simulation::connexion(abc.Bases[i]); //pour determiner si les robots doivent etre en AUTO ou REMOTE //+interconnexion?
		simulation::maintenance(abc.Bases[i]);    
		simulation::creation(abc.Bases[i]);  
		simulation::updateRemote(abc.Bases[i]); //(taB[i].robots)
		simulation::updateAutonomous(abc.Bases[i]); //(taB[i].robots)
	}
			
	     
	for(unsigned int i = 0; i < abc.Bases.size(); i++)
	{
		if(abc.Bases[i].getRessource() <= 0)
			abc.Bases.erase(abc.Bases.begin()+i); 
	}
}
///P F T C

void simulation::updateVoisin(base::Base B1, base::Base B2) //les robots de B1 sauvegardent les UIDs des robots de B2 rencontres. How bout rewriting it with B.searchByUID()?
{
	for(unsigned int i = 0; i < B1.getProspecteurs().size(); i++)
	{
		for(unsigned int j = 0; j < B2.getProspecteurs().size(); j++)
		{
			if(geomod::inCircle(B1.getProspecteurs()[i].getPoint(), B2.getProspecteurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getProspecteurs()[i].addVoisinUID(B1.getProspecteurs()[i], B2.getBID(), B2.getProspecteurs()[j].getUID());
			}
		}
		for(unsigned int j = 0; j < B2.getForeurs().size(); j++)
		{
			if(geomod::inCircle(B1.getProspecteurs()[i].getPoint(), B2.getForeurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getProspecteurs()[i].addVoisinUID(B1.getProspecteurs()[i], B2.getBID(), B2.getForeurs()[j].getUID());
			}
		}
		for(unsigned int j = 0; j < B2.getTransporteurs().size(); j++)
		{
			if(geomod::inCircle(B1.getProspecteurs()[i].getPoint(), B2.getTransporteurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getProspecteurs()[i].addVoisinUID(B1.getProspecteurs()[i], B2.getBID(), B2.getTransporteurs()[j].getUID());
			}
		}
		for(unsigned int j = 0; j < B2.getCommunicateurs().size(); j++)
		{
			if(geomod::inCircle(B1.getProspecteurs()[i].getPoint(), B2.getCommunicateurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getProspecteurs()[i].addVoisinUID(B1.getProspecteurs()[i], B2.getBID(), B2.getCommunicateurs()[j].getUID());
			}
		}
	}
	
	
	for(unsigned int i = 0; i < B1.getForeurs().size(); i++)
	{
		for(unsigned int j = 0; j < B2.getProspecteurs().size(); j++)
		{
			if(geomod::inCircle(B1.getForeurs()[i].getPoint(), B2.getProspecteurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getForeurs()[i].addVoisinUID(B1.getForeurs()[i], B2.getBID(), B2.getProspecteurs()[j].getUID());
			}
		}
		for(unsigned int j = 0; j < B2.getForeurs().size(); j++)
		{
			if(geomod::inCircle(B1.getForeurs()[i].getPoint(), B2.getForeurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getForeurs()[i].addVoisinUID(B1.getForeurs()[i], B2.getBID(), B2.getForeurs()[j].getUID());
			}
		}
		for(unsigned int j = 0; j < B2.getTransporteurs().size(); j++)
		{
			if(geomod::inCircle(B1.getForeurs()[i].getPoint(), B2.getTransporteurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getForeurs()[i].addVoisinUID(B1.getForeurs()[i], B2.getBID(), B2.getTransporteurs()[j].getUID());
			}
		}
		for(unsigned int j = 0; j < B2.getCommunicateurs().size(); j++)
		{
			if(geomod::inCircle(B1.getForeurs()[i].getPoint(), B2.getCommunicateurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getForeurs()[i].addVoisinUID(B1.getForeurs()[i], B2.getBID(), B2.getCommunicateurs()[j].getUID());
			}
		}
	}
	
	
	for(unsigned int i = 0; i < B1.getTransporteurs().size(); i++)
	{
		for(unsigned int j = 0; j < B2.getProspecteurs().size(); j++)
		{
			if(geomod::inCircle(B1.getTransporteurs()[i].getPoint(), B2.getProspecteurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getTransporteurs()[i].addVoisinUID(B1.getTransporteurs()[i], B2.getBID(), B2.getProspecteurs()[j].getUID());
			}
		}
		for(unsigned int j = 0; j < B2.getForeurs().size(); j++)
		{
			if(geomod::inCircle(B1.getTransporteurs()[i].getPoint(), B2.getForeurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getTransporteurs()[i].addVoisinUID(B1.getTransporteurs()[i], B2.getBID(), B2.getForeurs()[j].getUID());
			}
		}
		for(unsigned int j = 0; j < B2.getTransporteurs().size(); j++)
		{
			if(geomod::inCircle(B1.getTransporteurs()[i].getPoint(), B2.getTransporteurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getTransporteurs()[i].addVoisinUID(B1.getTransporteurs()[i], B2.getBID(), B2.getTransporteurs()[j].getUID());
			}
		}
		for(unsigned int j = 0; j < B2.getCommunicateurs().size(); j++)
		{
			if(geomod::inCircle(B1.getTransporteurs()[i].getPoint(), B2.getCommunicateurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getTransporteurs()[i].addVoisinUID(B1.getTransporteurs()[i], B2.getBID(), B2.getCommunicateurs()[j].getUID());
			}
		}
	}
	
	
	
	for(unsigned int i = 0; i < B1.getCommunicateurs().size(); i++)
	{
		for(unsigned int j = 0; j < B2.getProspecteurs().size(); j++)
		{
			if(geomod::inCircle(B1.getCommunicateurs()[i].getPoint(), B2.getProspecteurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getCommunicateurs()[i].addVoisinUID(B1.getCommunicateurs()[i], B2.getBID(), B2.getProspecteurs()[j].getUID());
			}
		}
		for(unsigned int j = 0; j < B2.getForeurs().size(); j++)
		{
			if(geomod::inCircle(B1.getCommunicateurs()[i].getPoint(), B2.getForeurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getCommunicateurs()[i].addVoisinUID(B1.getCommunicateurs()[i], B2.getBID(), B2.getForeurs()[j].getUID());
			}
		}
		for(unsigned int j = 0; j < B2.getTransporteurs().size(); j++)
		{
			if(geomod::inCircle(B1.getCommunicateurs()[i].getPoint(), B2.getTransporteurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getCommunicateurs()[i].addVoisinUID(B1.getCommunicateurs()[i], B2.getBID(), B2.getTransporteurs()[j].getUID());
			}
		}
		for(unsigned int j = 0; j < B2.getCommunicateurs().size(); j++)
		{
			if(geomod::inCircle(B1.getCommunicateurs()[i].getPoint(), B2.getCommunicateurs()[j].getPoint(), rayon_comm)==true)
			{
				B1.getCommunicateurs()[i].addVoisinUID(B1.getCommunicateurs()[i], B2.getBID(), B2.getCommunicateurs()[j].getUID());
			}
		}
	}
}

void simulation::connexion (base::Base B1)
{
	double startUID;
	
	for(unsigned int i = 0; i < B1.getCommunicateurs().size(); i++)
	{
		if(B1.getPoint().x==B1.getCommunicateurs()[i].getPoint().x && B1.getPoint().y==B1.getCommunicateurs()[i].getPoint().y)
		{
			startUID = B1.getCommunicateurs()[i].getUID();
			break;
		}
	}
	
	subConnexion(B1, startUID);
}

void simulation::subConnexion(base::Base B, double uid)
{
	if(B.searchByUID(uid).getInRange()==false)
	{
		B.searchByUID(uid).setInRange(B.searchByUID(uid), true); //error 
		
		for(unsigned int i = 0; i < B.searchByUID(uid).getVoisinUIDs()[B.getBID()].size(); i++)
		{
			simulation::subConnexion(B, B.searchByUID(uid).getVoisinUIDs()[B.getBID()][i]);
		}
	}
}



void simulation::maintenance(base::Base B1)
{
	for(unsigned int i = 0; i < B1.getUIDs().size(); i++)
	{
		if(geomod::overlap(B1.searchByUID(B1.getUIDs()[i]).getPoint(), B1.getPoint()))
		{
			double x = B1.getRessource()-cost_repair*B1.searchByUID(B1.getUIDs()[i]).getDp();
			B1.setRessource(B1, x);
			x = 0;
			B1.searchByUID(B1.getUIDs()[i]).setDp(B1.searchByUID(B1.getUIDs()[i]), x); 
		}
	}
}



void simulation::creation(base::Base B1) //test 1: creation d'un prosp par appel
{
	if(B1.getUIDs().size()!=max_robots)
	{
		Robot_Prosp r;
		r.setPoint(r, B1.getPoint());
		geomod::Point but;
		but.x = B1.getPoint().x;
		but.y = B1.getPoint().y+100; //pour qu'ils se dirigent vers le nord;
		r.setBut(r, but);
		r.setUID(r, generateUID(B1));
		r.setDp(r, 0);
		r.setAtteint(r, false);
		r.setMode(r, 'a'); //upon creation: auto
		r.setInRange(r, false);
		r.setRetour(r, false);
		r.setFound(r, false);
		//faire des conctructeurs neat pour ca ^^^
	}
}

void simulation::updateRemote(base::Base B1)
{
	for(unsigned int i = 0; i < B1.getUIDs().size(); i++)
	{
		if(B1.searchByUID(B1.getUIDs()[i]).getMode()=='r')
			move(B1.searchByUID(B1.getUIDs()[i]));
	}
}

void simulation::updateAutonomous(base::Base B1)
{
	for(unsigned int i = 0; i < B1.getUIDs().size(); i++)
	{
		if(B1.searchByUID(B1.getUIDs()[i]).getMode()=='a')
			move(B1.searchByUID(B1.getUIDs()[i]));
	}
}

double simulation::generateUID(base::Base B1) //try uids from zero to inf as long as theres no such uid in B1.UIDs
{
	double uid = 0;
	bool dupli = false;
	
	while(true)
	{
		for(unsigned int i = 0; i < B1.getUIDs().size(); i++)
		{
			if(uid == B1.getUIDs()[i])
				dupli = true;
		}
		
		if(dupli == false)
			return uid;
		else
			uid++;
	}
}

void simulation::move(Robot& r)
{
	double vx = r.getBut().x - r.getPoint().x;
	double vy = r.getBut().y - r.getPoint().y;
	
	geomod::Vector v(vx, vy);
	
	if(geomod::vectorNorm(v, r.getPoint(), r.getBut()) < deltaD)
	{
		r.setPoint(r, r.getBut());
		r.setAtteint(r, true);
	}
	else
	{
		double newX = (deltaD/geomod::vectorNorm(v, r.getPoint(), r.getBut()))*vx;
		double newY = (deltaD/geomod::vectorNorm(v, r.getPoint(), r.getBut()))*vy;
	
		geomod::Point newP(newX, newY);
	
		r.setPoint(r, newP);
	}	
}



