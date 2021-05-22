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

varglo abc;

void simulation::Lecture(const std::string &filename)
{

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

void simulation::Ecriture(const std::string &filename)
{	
	ofstream myfile;
	myfile.open (filename, ios::out | ios::trunc);

	myfile<<"# "<<filename<<endl;
	myfile<<endl;
	myfile<<"# nb Gisement"<<endl;
	myfile<<abc.Gisements.size()<<endl;
	myfile<<"# Gisement: (x y rayon capacite)"<<endl;
	
	for(unsigned int i = 0; i < abc.Gisements.size(); i++)
	{
		myfile<<abc.Gisements[i].getPoint().x<<" ";
		myfile<<abc.Gisements[i].getPoint().y<<" ";
		myfile<<abc.Gisements[i].getRayon()<<" ";
		myfile<<abc.Gisements[i].getCapacite()<<endl;
	}

	myfile<<"# nb Base"<<endl;
	myfile<<abc.Bases.size()<<endl;

	myfile<<"# Base: (x y res nbP nbF nbT nbC)"<<endl;
	
	for(unsigned int i = 0; i < abc.Bases.size(); i++)
	{
		myfile<<abc.Bases[i].getPoint().x<<" ";
		myfile<<abc.Bases[i].getPoint().y<<" ";
		myfile<<abc.Bases[i].getRessource()<<" ";
		myfile<<abc.Bases[i].getProspecteurs().size()<<" ";
		myfile<<abc.Bases[i].getForeurs().size()<<" ";
		myfile<<abc.Bases[i].getTransporteurs().size()<<" ";
		myfile<<abc.Bases[i].getCommunicateurs().size()<<" ";
		myfile<<endl;
		
		myfile<<"# PROSP: (uid dp x y xb yb atteint retour found xg yg rayong capaciteg)"<<endl;
		for(unsigned int j = 0; j < abc.Bases[i].getProspecteurs().size(); j++)
		{
			myfile<<abc.Bases[i].getProspecteurs()[j].getUID() <<" ";
			myfile<<abc.Bases[i].getProspecteurs()[j].getDp() <<" ";
			myfile<<abc.Bases[i].getProspecteurs()[j].getPoint().x <<" ";
			myfile<<abc.Bases[i].getProspecteurs()[j].getPoint().y <<" ";
			myfile<<abc.Bases[i].getProspecteurs()[j].getBut().x <<" ";
			myfile<<abc.Bases[i].getProspecteurs()[j].getBut().y <<" ";
			myfile<<to_string(abc.Bases[i].getProspecteurs()[j].getAtteint()) <<" ";
			myfile<<to_string(abc.Bases[i].getProspecteurs()[j].getRetour()) <<" ";
			myfile<<to_string(abc.Bases[i].getProspecteurs()[j].getFound()) <<" ";
			
			if(abc.Bases[i].getProspecteurs()[j].getFound()==true)
			{
				myfile<<abc.Bases[i].getProspecteurs()[j].getGisementFound().getPoint().x <<" ";
				myfile<<abc.Bases[i].getProspecteurs()[j].getGisementFound().getPoint().y <<" ";
				myfile<<abc.Bases[i].getProspecteurs()[j].getGisementFound().getRayon() <<" ";
				myfile<<abc.Bases[i].getProspecteurs()[j].getGisementFound().getCapacite() <<" ";
			}
			myfile<<endl;
		}
		myfile<<endl;
		
		myfile<<"# FOR: (uid dp x y xb yb atteint)"<<endl;
		for(unsigned int j = 0; j < abc.Bases[i].getForeurs().size(); j++)
		{
			myfile<<abc.Bases[i].getForeurs()[j].getUID() <<" ";
			myfile<<abc.Bases[i].getForeurs()[j].getDp() <<" ";
			myfile<<abc.Bases[i].getForeurs()[j].getPoint().x <<" ";
			myfile<<abc.Bases[i].getForeurs()[j].getPoint().y <<" ";
			myfile<<abc.Bases[i].getForeurs()[j].getBut().x <<" ";
			myfile<<abc.Bases[i].getForeurs()[j].getBut().y <<" ";
			myfile<<to_string(abc.Bases[i].getForeurs()[j].getAtteint()) <<" ";
			myfile<<endl;
		}
		myfile<<endl;
		
		myfile<<"# TRANS: (uid dp x y xb yb atteint retour)"<<endl;
		for(unsigned int j = 0; j < abc.Bases[i].getTransporteurs().size(); j++)
		{
			myfile<<abc.Bases[i].getTransporteurs()[j].getUID() <<" ";
			myfile<<abc.Bases[i].getTransporteurs()[j].getDp() <<" ";
			myfile<<abc.Bases[i].getTransporteurs()[j].getPoint().x <<" ";
			myfile<<abc.Bases[i].getTransporteurs()[j].getPoint().y <<" ";
			myfile<<abc.Bases[i].getTransporteurs()[j].getBut().x <<" ";
			myfile<<abc.Bases[i].getTransporteurs()[j].getBut().y <<" ";
			myfile<<to_string(abc.Bases[i].getTransporteurs()[j].getAtteint()) <<" ";
			myfile<<to_string(abc.Bases[i].getTransporteurs()[j].getRetour()) <<" ";
			myfile<<endl;
		}
		myfile<<endl;
		
		myfile<<"# COM: (uid dp x y xb yb atteint)"<<endl;
		for(unsigned int j = 0; j < abc.Bases[i].getCommunicateurs().size(); j++)
		{
			myfile<<abc.Bases[i].getCommunicateurs()[j].getUID() <<" ";
			myfile<<abc.Bases[i].getCommunicateurs()[j].getDp() <<" ";
			myfile<<abc.Bases[i].getCommunicateurs()[j].getPoint().x <<" ";
			myfile<<abc.Bases[i].getCommunicateurs()[j].getPoint().y <<" ";
			myfile<<abc.Bases[i].getCommunicateurs()[j].getBut().x <<" ";
			myfile<<abc.Bases[i].getCommunicateurs()[j].getBut().y <<" ";
			myfile<<to_string(abc.Bases[i].getCommunicateurs()[j].getAtteint()) <<" ";
			myfile<<endl;
		}
		myfile<<endl;
	}

	myfile.close();
	
	//Clear all data
	abc.Bases.clear();
	abc.Gisements.clear();
	
}

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
	//cout<<"case 0: gis called"<<endl;
	abc.mode++;
	abc.nbG = stod(vs[0]);
}

void simulation::assignCase1(varglo &abc, std::vector<std::string> vs)
{
	//cout<<"case 1: ass_gis called"<<endl;
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

	gisement::Gisement g(stod(vs[0]), stod(vs[1]), stod(vs[2]), stod(vs[3]));

	abc.Gisements.push_back(g);

	abc.nbG--;
}

void simulation::assignCase2(varglo &abc, std::vector<std::string> vs)
{
	//cout<<"case 2: ass_bas called"<<endl;
	
	geomod::Point p(stod(vs[0]), stod(vs[1]));

	base::Base b(p);
	b.setRessource(b, stod(vs[2]));
	b.setBID(b, abc.Bases.size()); //le premier BID c'est 0
	
	
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
	//cout<<"case 3: ass_p called"<<endl;
	
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
		
		
		rP.setRetour(rP, to_bool(vs[7]));
		rP.setFound(rP, to_bool(vs[8]));
		
		if(rP.getFound()==true)
		{
			gisement::Gisement g(stod(vs[9]), stod(vs[10]), stod(vs[11]), stod(vs[12]));
			
			rP.setGisementFound(rP, g);
		}
		
		abc.Bases[abc.whichBase].base::Base::add_prospecteur(rP);
		abc.Bases[abc.whichBase].add_UID(stod(vs[0]));
		abc.nbP--;
	}
}

void simulation::assignCase4(varglo &abc, std::vector<std::string> vs)
{
	//cout<<"case 4: ass_g called"<<endl;
	
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
		rT.setRetour(rT, to_bool(vs[7]));
		
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
						cout << message::field_superposition(abc.Gisements[i].getPoint().x, abc.Gisements[i].getPoint().y, abc.Gisements[j].getPoint().x, abc.Gisements[j].getPoint().y);
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
					if (geomod::intersect(abc.Bases[i].getPoint(), rayon_base, abc.Gisements[j].getPoint(), abc.Gisements[j].getRayon()) == true)
					{
						cout << message::base_field_superposition(abc.Bases[i].getPoint().x, abc.Bases[i].getPoint().y, abc.Gisements[j].getPoint().x, abc.Gisements[j].getPoint().y);
						exit(EXIT_FAILURE);
					}
				}
			}
			
			cout << message::success();
			cout<<"message success"<<endl;
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

std::string simulation::to_string(bool arg1)
{
	if(arg1==0)
		return "false";
	else if(arg1==1)
		return "true";
}

void simulation::sim() //theoriquement au lieu de abc ca doit etre Bases.
{
	cout<<endl;
	for(unsigned int i = 0; i < abc.Bases.size(); i++)
	{
		for(unsigned int j = 0; j < abc.Bases.size(); j++)
		{
			updateVoisin(abc.Bases[i], abc.Bases[j]); //OK
		}
		
	simulation::connexion(abc.Bases[i]); //OK
	simulation::maintenance(abc.Bases[i]);    
	simulation::creation(abc.Bases[i]);   
	simulation::updateRemote(abc.Bases[i]); 
	simulation::updateAutonomous(abc.Bases[i]); 
	}

	
	/* //display of voisins
	for(unsigned int i = 0; i < abc.Bases.size(); i++) //display of voisins
	{
		for(unsigned int j = 0; j < abc.Bases[i].getUIDs().size(); j++)
		{
			cout<<"BID: "<<abc.Bases[i].getBID()<<" UID: "<<abc.Bases[i].searchByUID(abc.Bases[i].getUIDs()[j]).getUID()<<endl;
			cout<<"Mode: "<<abc.Bases[i].searchByUID(abc.Bases[i].getUIDs()[j]).getMode()<<endl;
			
			for(unsigned int k = 0; k < abc.Bases[i].searchByUID(abc.Bases[i].getUIDs()[j]).getVoisinUIDs().size(); k++)
			{
				for(unsigned int l = 0; l < abc.Bases[i].searchByUID(abc.Bases[i].getUIDs()[j]).getVoisinUIDs()[k].size(); l++)
				{
					cout<<abc.Bases[i].searchByUID(abc.Bases[i].getUIDs()[j]).getVoisinUIDs()[k][l]<<" ";
				} 
				
				cout<<endl;
			}
			cout<<endl;
		}
	}
	*/
	
	/*  //display of modes
	for(unsigned int j = 0; j < abc.Bases.size(); j++)
	{
		for(unsigned int i = 0; i < abc.Bases[j].getUIDs().size(); i++)
		{
			cout<<"UID: "<<abc.Bases[j].searchByUID(abc.Bases[j].getUIDs()[i]).getUID()<<" current mode: "<<abc.Bases[j].searchByUID(abc.Bases[j].getUIDs()[i]).getMode()<<endl;
		}
	}
	*/
	     
	for(unsigned int i = 0; i < abc.Bases.size(); i++)
	{
		if(abc.Bases[i].getRessource() <= 0)
			abc.Bases.erase(abc.Bases.begin()+i); 
	}
}
///P F T C

void simulation::updateVoisin(base::Base &B1, base::Base &B2)
{	
	for(unsigned int i = 0; i < B1.getUIDs().size(); i++)
	{
		for(unsigned int j = 0; j < B2.getUIDs().size(); j++)
		{	
			if(geomod::inCircle(B1.searchByUID(B1.getUIDs()[i]).getPoint(), B2.searchByUID(B2.getUIDs()[j]).getPoint(), rayon_comm)==true)
			{
				B1.searchByUID(B1.getUIDs()[i]).addVoisinUID(B1.searchByUID(B1.getUIDs()[i]), B2.getBID(), B2.searchByUID(B2.getUIDs()[j]).getUID());
			}
		}
	}
}

void simulation::connexion (base::Base &B1)
{
	double startUID = 69420;
	
	for(unsigned int i = 0; i < B1.getCommunicateurs().size(); i++)
	{
		if(geomod::overlap(B1.getPoint(), B1.getCommunicateurs()[i].getPoint()))
		{
			startUID = B1.getCommunicateurs()[i].getUID();
			break;
		}
	}
	
	for(unsigned int i = 0; i < B1.getUIDs().size(); i++)
	{
		B1.searchByUID(B1.getUIDs()[i]).setMode(B1.searchByUID(B1.getUIDs()[i]), 0);
	}	
	subConnexion(B1, startUID);
}

void simulation::subConnexion(base::Base &B, double uid)
{
	if(B.searchByUID(uid).getMode()==0)
	{
		B.searchByUID(uid).setMode(B.searchByUID(uid), 1); 

		for(unsigned int i = 0; i < B.searchByUID(uid).getVoisinUIDs()[B.getBID()].size(); i++)
		{
			simulation::subConnexion(B, B.searchByUID(uid).getVoisinUIDs()[B.getBID()][i]);
		}
	}
}

void simulation::maintenance(base::Base &B1)
{
	for(unsigned int i = 0; i < B1.getUIDs().size(); i++)
	{
		if(geomod::overlap(B1.searchByUID(B1.getUIDs()[i]).getPoint(), B1.getPoint())&&B1.searchByUID(B1.getUIDs()[i]).getDp()!=0)
		{
			double x = B1.getRessource()-cost_repair*B1.searchByUID(B1.getUIDs()[i]).getDp();
		//	cout<<"Base "<<B1.getBID()<<" ressource: "<<B1.getRessource()<<" -> "<<x<<endl;
			B1.setRessource(B1, x);
			x = 0;
			B1.searchByUID(B1.getUIDs()[i]).setDp(B1.searchByUID(B1.getUIDs()[i]), x); 
		//	cout<<"Robot "<<B1.searchByUID(B1.getUIDs()[i]).getUID()<<": maintained"<<endl;
		}
	}
}

void simulation::creation(base::Base &B1) //test 1: creation d'un prosp par appel
{
	/*
	if(B1.getUIDs().size()!=max_robots)
	{
		cout<<"creating new prosp"<<endl;
		
		Robot_Prosp r;
		r.setPoint(r, B1.getPoint());
		geomod::Point but;
		but.x = B1.getPoint().x;
		but.y = B1.getPoint().y+100; //pour qu'ils se dirigent vers le nord;
		r.setBut(r, but);
		r.setUID(r, generateUID(B1));
		r.setDp(r, 0);
		r.setAtteint(r, false);
		r.setMode(r, 0); //upon creation: auto
		r.setInRange(r, false);
		r.setRetour(r, false);
		r.setFound(r, false);
		//faire des conctructeurs neat pour ca s'il reste un peu de temps
	}
	* */
}

void simulation::updateRemote(base::Base &B1)
{
	for(unsigned int i = 0; i < B1.getUIDs().size(); i++)
	{
		if(B1.searchByUID(B1.getUIDs()[i]).getMode()==1&&geomod::overlap(B1.searchByUID(B1.getUIDs()[i]).getPoint(),B1.searchByUID(B1.getUIDs()[i]).getBut())==false)
		{
		//	cout<<"remote robot "<<B1.searchByUID(B1.getUIDs()[i]).getUID()<<" updated from ("<<B1.searchByUID(B1.getUIDs()[i]).getPoint().x<<", "<<B1.searchByUID(B1.getUIDs()[i]).getPoint().y;
			move(B1.searchByUID(B1.getUIDs()[i]));
		//	cout<<") to ("<<B1.searchByUID(B1.getUIDs()[i]).getPoint().x<<", "<<B1.searchByUID(B1.getUIDs()[i]).getPoint().y<<") new dp: "<<B1.searchByUID(B1.getUIDs()[i]).getDp()<<endl;
		}
	}
}

void simulation::updateAutonomous(base::Base &B1)
{
	for(unsigned int i = 0; i < B1.getUIDs().size(); i++)
	{
		if(B1.searchByUID(B1.getUIDs()[i]).getMode()==0&&geomod::overlap(B1.searchByUID(B1.getUIDs()[i]).getPoint(),B1.searchByUID(B1.getUIDs()[i]).getBut())==false)
		{
		//	cout<<"autonomous robot "<<B1.searchByUID(B1.getUIDs()[i]).getUID()<<" updated from ("<<B1.searchByUID(B1.getUIDs()[i]).getPoint().x<<", "<<B1.searchByUID(B1.getUIDs()[i]).getPoint().y;
			move(B1.searchByUID(B1.getUIDs()[i]));
		//	cout<<") to ("<<B1.searchByUID(B1.getUIDs()[i]).getPoint().x<<", "<<B1.searchByUID(B1.getUIDs()[i]).getPoint().y<<") new dp: "<<B1.searchByUID(B1.getUIDs()[i]).getDp()<<endl;
		}
	}
}

double simulation::generateUID(base::Base &B1) //try uids from zero to inf as long as theres no such uid in B1.UIDs
{
	double uid = 0;
	bool dupli;
	
	while(dupli == true)
	{
		dupli = false;
		for(unsigned int i = 0; i < B1.getUIDs().size(); i++)
		{
			if(uid == B1.getUIDs()[i])
			{
				dupli = true;
			}
		}
		
		if(dupli==true)
		{
			uid++;
		}
	}
	
	return uid;
}

void simulation::move(Robot& r) //update position, update dp
{
	geomod::Vector optDir(geomod::nVect(r.getPoint(), r.getBut()).x, geomod::nVect(r.getPoint(), r.getBut()).y);
	
	if(optDir.norm<deltaD)
	{
		r.setDp(r, r.getDp()+optDir.norm);
		r.setPoint(r, r.getBut());
		r.setAtteint(r, true);
	}
	else
	{
		double dx = (deltaD/optDir.norm)*(r.getBut().x-r.getPoint().x);
		double dy = (deltaD/optDir.norm)*(r.getBut().y-r.getPoint().y);
		geomod::Point newPoint(r.getPoint().x+dx, r.getPoint().y+dy);
		
		r.setDp(r, r.getDp()+deltaD);
		
		r.setPoint(r, newPoint);
	}
}

void simulation::control(base::Base &B1)
{
//	cout << "Base " << B1.getBID() <<":"<<endl;
	
	for(unsigned int i = 0; i < B1.getUIDs().size(); i++)
	{
//		cout << "UIDs["<<i<<"]: "<<B1.getUIDs()[i]<<endl;
	}
	
	cout<<endl;
}
