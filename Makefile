projet: projet.o geomod.o simulation.o message.o base.o gisement.o robot.o
	g++ -o projet projet.o geomod.o simulation.o message.o base.o gisement.o robot.o

projet.o: projet.cc
	g++ -c projet.cc
	
geomod.o: geomod.cc
	g++ -c geomod.cc

simulation.o: simulation.cc
	g++ -c simulation.cc

message.o: message.cc
	g++ -c message.cc

base.o: base.cc
	g++ -c base.cc
	
gisement.o: gisement.cc
	g++ -c gisement.cc
	
robot.o: robot.cc
	g++ -c robot.cc

