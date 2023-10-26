.SILENT:

CO=g++
OBJS_QT = main.o applicgaragewindow.o moc_applicgaragewindow.o Classes/Garage.o Classes/Option.o Classes/Modele.o Classes/Voiture.o Classes/Personne.o Classes/Intervenant.o Classes/Client.o Classes/Employe.o Classes/Exception.o Classes/OptionException.o Classes/PasswordException.o Classes/Vecteur.o Classes/Iterateur.o Classes/Contrat.o
PROGRAMS = ApplicGarage

all:	$(PROGRAMS)

ApplicGarage:	$(OBJS_QT)
		echo Creation de ApplicGarage...
		$(CO) -Wl,-O1 -o ApplicGarage $(OBJS_QT) /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread 					
		#rm main.o

main.o:	InterfaceQt/main.cpp
		echo Creation de main.o
		$(CO) -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o main.o InterfaceQt/main.cpp

applicgaragewindow.o:	InterfaceQt/applicgaragewindow.cpp InterfaceQt/applicgaragewindow.h InterfaceQt/ui_applicgaragewindow.h
		echo Creation de applicgaragewindow.o
		$(CO) -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o applicgaragewindow.o InterfaceQt/applicgaragewindow.cpp

moc_applicgaragewindow.o:	InterfaceQt/moc_applicgaragewindow.cpp InterfaceQt/applicgaragewindow.h
		echo Creation de moc_applicgaragewindow.o
		$(CO) -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o moc_applicgaragewindow.o InterfaceQt/moc_applicgaragewindow.cpp


Classes/Contrat.o:	Classes/Contrat.h Classes/Contrat.cpp
	echo "Creation de l objet Contrat.o"
	g++ Classes/Contrat.cpp -c -o Classes/Contrat.o #-D DEBUG


Classes/Garage.o:	Classes/Garage.h Classes/Garage.cpp
	echo "Creation de l objet Garage.o"
	g++ Classes/Garage.cpp -c -o Classes/Garage.o #-D DEBUG

Classes/Option.o:	Classes/Option.h Classes/Option.cpp
	echo "Creation de Option.o"
	g++ Classes/Option.cpp -c -o Classes/Option.o #-D DEBUG

Classes/Modele.o:	Classes/Modele.h Classes/Modele.cpp
	echo "Creation de Modele.o"
	g++ Classes/Modele.cpp -c -o Classes/Modele.o #-D DEBUG

Classes/Voiture.o:	Classes/Voiture.h Classes/Voiture.cpp
	echo "Creation de Voiture.o"
	g++ Classes/Voiture.cpp -c -o Classes/Voiture.o #-D DEBUG

Classes/Personne.o:	Classes/Personne.h Classes/Personne.cpp
	echo "Creation de Personne.o"
	g++ Classes/Personne.cpp -c -o Classes/Personne.o #-D DEBUG

Classes/Intervenant.o:	Classes/Intervenant.h Classes/Intervenant.cpp
	echo "Creation d Intervenant.o"
	g++ Classes/Intervenant.cpp -c -o Classes/Intervenant.o #-D DEBUG

Classes/Client.o:	Classes/Client.h Classes/Client.cpp
	echo "Creation de Client.o"
	g++ Classes/Client.cpp -c -o Classes/Client.o

Classes/Employe.o:	Classes/Employe.h Classes/Employe.cpp
	echo "Creation d employe"
	g++ Classes/Employe.cpp -c -o Classes/Employe.o

Classes/Exception.o:	Classes/Exception.h Classes/Exception.cpp
	echo "Creation Exception"
	g++ Classes/Exception.cpp -c -o Classes/Exception.o

Classes/OptionException.o:	Classes/OptionException.h Classes/OptionException.cpp
	echo "Creation OptionException"
	g++ Classes/OptionException.cpp -c -o Classes/OptionException.o

Classes/PasswordException.o:	Classes/PasswordException.h Classes/PasswordException.cpp
	echo "Creation PasswordException"
	g++ Classes/PasswordException.cpp -c -o Classes/PasswordException.o

Classes/Vecteur.o:	Classes/Vecteur.h Classes/Vecteur.cpp
	echo "Creation Template"
	g++ Classes/Vecteur.cpp -c -o Classes/Vecteur.o

Classes/Iterateur.o:	Classes/Iterateur.h Classes/Iterateur.cpp
	echo "Creation Iterateur"
	g++ Classes/Iterateur.cpp -c -o Classes/Iterateur.o


#clean:
#	@rm -f $(OBJS_QT) core
	

#clobber:	clean
#	@rm -f tags $(PROGRAMS) *~ *.log