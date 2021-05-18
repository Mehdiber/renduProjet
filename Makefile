LDFLAGS := `pkg-config --libs gtkmm-3.0`
CXXFLAGS := `pkg-config --cflags gtkmm-3.0`


projet: projet.o geomod.o simulation.o message.o base.o gisement.o robot.o gui.o myarea.o Shapes.o
	g++ -o projet projet.o geomod.o simulation.o message.o base.o gisement.o robot.o gui.o myarea.o Shapes.o $(LDFLAGS)

projet.o: projet.cc
	g++ -c $(CXXFLAGS) projet.cc

geomod.o: geomod.cc
	g++ -c $(CXXFLAGS) geomod.cc

simulation.o: simulation.cc
	g++ -c $(CXXFLAGS) simulation.cc

message.o: message.cc
	g++ -c $(CXXFLAGS) message.cc

base.o: base.cc
	g++ -c $(CXXFLAGS) base.cc

gisement.o: gisement.cc
	g++ -c $(CXXFLAGS) gisement.cc

robot.o: robot.cc
	g++ -c $(CXXFLAGS) robot.cc

myarea.o: myarea.cc
	g++ -c $(CXXFLAGS) myarea.cc

gui.o: gui.cc
	g++ -c $(CXXFLAGS) gui.cc

Shapes.o: Shapes.cc
	g++ -c $(CXXFLAGS) Shapes.cc
