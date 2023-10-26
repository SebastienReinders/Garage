#include "applicgaragewindow.h"
#include "ui_applicgaragewindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <sstream>
using namespace std;

#define REPERTOIRE_IMAGES "images/"


ApplicGarageWindow::ApplicGarageWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::ApplicGarageWindow)
{
        
    ui->setupUi(this);

    // Configuration de la table des options (projet en cours)
    ui->tableWidgetOptions->setColumnCount(3);
    ui->tableWidgetOptions->setRowCount(5);
    for (int i=0 ; i<5 ; i++) ui->tableWidgetOptions->setRowHeight(i,10);
    QStringList labelsTableOptions;
    labelsTableOptions << "Code" << "Prix" << "Intitulé";
    ui->tableWidgetOptions->setHorizontalHeaderLabels(labelsTableOptions);
    ui->tableWidgetOptions->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetOptions->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetOptions->horizontalHeader()->setVisible(true);
    ui->tableWidgetOptions->horizontalHeader()->setDefaultSectionSize(60);
    ui->tableWidgetOptions->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetOptions->verticalHeader()->setVisible(false);
    ui->tableWidgetOptions->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des employes (Personnel Garage)
    ui->tableWidgetEmployes->setColumnCount(4);
    ui->tableWidgetEmployes->setRowCount(0);
    QStringList labelsTableEmployes;
    labelsTableEmployes << "Numéro" << "Nom" << "Prénom" << "Fonction";
    ui->tableWidgetEmployes->setHorizontalHeaderLabels(labelsTableEmployes);
    ui->tableWidgetEmployes->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetEmployes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetEmployes->horizontalHeader()->setVisible(true);
    ui->tableWidgetEmployes->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetEmployes->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetEmployes->verticalHeader()->setVisible(false);
    ui->tableWidgetEmployes->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des clients
    ui->tableWidgetClients->setColumnCount(4);
    ui->tableWidgetClients->setRowCount(0);
    QStringList labelsTableClients;
    labelsTableClients << "Numéro" << "Nom" << "Prénom" << "GSM";
    ui->tableWidgetClients->setHorizontalHeaderLabels(labelsTableClients);
    ui->tableWidgetClients->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetClients->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetClients->horizontalHeader()->setVisible(true);
    ui->tableWidgetClients->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetClients->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetClients->verticalHeader()->setVisible(false);
    ui->tableWidgetClients->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des contrats
    ui->tableWidgetContrats->setColumnCount(4);
    ui->tableWidgetContrats->setRowCount(0);
    QStringList labelsTableContrats;
    labelsTableContrats << "Numéro" << "Vendeur" << "Client" << "Voiture";
    ui->tableWidgetContrats->setHorizontalHeaderLabels(labelsTableContrats);
    ui->tableWidgetContrats->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetContrats->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetContrats->horizontalHeader()->setVisible(true);
    ui->tableWidgetContrats->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetContrats->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetContrats->verticalHeader()->setVisible(false);
    ui->tableWidgetContrats->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Importation des modeles (étape 10)
    // TO DO
    Garage::getInstance().importeModeles();
    for (int i = 0; i < 25; i++)
    {
        if (Garage::getInstance().getModele(i).getPrixDeBase() != 0)
        ajouteModeleDisponible(Garage::getInstance().getModele(i).getNom(),Garage::getInstance().getModele(i).getPrixDeBase());
    }

    // Importation des options (étape 10)
    // TO DO
    Garage::getInstance().importeOptions();
    
    for (int i = 0; i < 25; i++)
    {
        if (Garage::getInstance().getOption(i).getPrix() != 0)
        ajouteOptionDisponible(Garage::getInstance().getOption(i).getIntitule(),Garage::getInstance().getOption(i).getPrix());
    }
    // Ouverture (et/ou creation) du fichier Garage.data (étape 12)
    // TO DO -> AUSSI POUR LE 11 AVEC ADMIN 

    videTableEmployes();
    ajouteTupleTableEmployes(Garage::getInstance().getEmployes()[0].Tuple());
    setRole();  // acces a tout pour l'instant

            //9999
    /*Garage::getInstance().save();
    cout << "Apres l ecriture, voici la lecture" << endl;
    //gerer le cas ou le fichier n existe plus ou pas ??? 
    Garage::getInstance().load("Garage.data");
    Garage::getInstance().afficheEmployes();*/

    //******* EXEMPLES (A SUPPRIMER) *******************************************
    //setTableOption(1,"XY08","Toit ouvrant",850.0);
    //ajouteModeleDisponible("Ferrari Daytona SP3",2100000.0);
    //ajouteModeleDisponible("Peugeot 208",18500.0);
    //ajouteOptionDisponible("Peinture metallisee",450.0);
    //ajouteOptionDisponible("Systeme GPS",1100.0);
    //setModele("Peugeot 308",120,1,22300.0,"308.jpg");
    //ajouteTupleTableEmployes("2;Wagner;Jean-Marc;Vendeur");
    //ajouteTupleTableClients("8;Leonard;Anne;0475/47.25.36");
    //ajouteTupleTableContrats("3;Wagner Jean-Marc;Quettier Patrick;508_ProjetQuettier");
    //**************************************************************************
cout << "On commence a lire sur disque " << endl << endl;
    Garage::getInstance().load("Garage.data");


}

ApplicGarageWindow::~ApplicGarageWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Titre de la fenêtre (ne pas modifier) //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setTitre(string titre)
{
    this->setWindowTitle(titre.c_str());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Gestion des roles (ne pas modifier) ////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setRole(int val)
{
    // val = 0 --> personne n'est loggé
    // val = 1 --> un administratif est loggé
    // val = 2 --> un vendeur loggé
    // val = 3 --> on a accès à tout

    if (val == 0)
    {
        ui->actionLogin->setEnabled(true);
        ui->actionLogout->setEnabled(false);
        ui->actionReset_Mot_de_passe->setEnabled(false);
        ui->menuEmployes->setEnabled(false);
        ui->menuClients->setEnabled(false);
        ui->menuVoiture->setEnabled(false);
        ui->comboBoxModelesDisponibles->setEnabled(false);
        ui->comboBoxOptionsDisponibles->setEnabled(false);
        ui->pushButtonOuvrirProjet->setEnabled(false);
        ui->pushButtonNouveauProjet->setEnabled(false);
        ui->pushButtonReduction->setEnabled(false);
        ui->pushButtonEnregistrerProjet->setEnabled(false);
        ui->pushButtonAjouterOption->setEnabled(false);
        ui->pushButtonSupprimerOption->setEnabled(false);
        ui->pushButtonChoisirModele->setEnabled(false);
        ui->pushButtonVisualiserVoiture->setEnabled(false);
        ui->pushButtonNouveauContrat->setEnabled(false);
        ui->pushButtonSupprimerContrat->setEnabled(false);
    }

    if (val == 1)
    {
        ui->actionLogin->setEnabled(false);
        ui->actionLogout->setEnabled(true);
        ui->actionReset_Mot_de_passe->setEnabled(true);
        ui->menuEmployes->setEnabled(true);
        ui->menuClients->setEnabled(false);
        ui->menuVoiture->setEnabled(false);
        ui->comboBoxModelesDisponibles->setEnabled(false);
        ui->comboBoxOptionsDisponibles->setEnabled(false);
        ui->pushButtonOuvrirProjet->setEnabled(false);
        ui->pushButtonNouveauProjet->setEnabled(false);
        ui->pushButtonReduction->setEnabled(false);
        ui->pushButtonEnregistrerProjet->setEnabled(false);
        ui->pushButtonAjouterOption->setEnabled(false);
        ui->pushButtonSupprimerOption->setEnabled(false);
        ui->pushButtonChoisirModele->setEnabled(false);
        ui->pushButtonVisualiserVoiture->setEnabled(true);
        ui->pushButtonNouveauContrat->setEnabled(false);
        ui->pushButtonSupprimerContrat->setEnabled(true);
    }

    if (val == 2)
    {
        ui->actionLogin->setEnabled(false);
        ui->actionLogout->setEnabled(true);
        ui->actionReset_Mot_de_passe->setEnabled(true);
        ui->menuEmployes->setEnabled(false);
        ui->menuClients->setEnabled(true);
        ui->menuVoiture->setEnabled(true);
        ui->comboBoxModelesDisponibles->setEnabled(true);
        ui->comboBoxOptionsDisponibles->setEnabled(true);
        ui->pushButtonOuvrirProjet->setEnabled(true);
        ui->pushButtonNouveauProjet->setEnabled(true);
        ui->pushButtonReduction->setEnabled(true);
        ui->pushButtonEnregistrerProjet->setEnabled(true);
        ui->pushButtonAjouterOption->setEnabled(true);
        ui->pushButtonSupprimerOption->setEnabled(true);
        ui->pushButtonChoisirModele->setEnabled(true);
        ui->pushButtonVisualiserVoiture->setEnabled(true);
        ui->pushButtonNouveauContrat->setEnabled(true);
        ui->pushButtonSupprimerContrat->setEnabled(true);
    }

    if (val == 3)
    {
        ui->actionLogin->setEnabled(true);
        ui->actionLogout->setEnabled(true);
        ui->actionReset_Mot_de_passe->setEnabled(true);
        ui->menuEmployes->setEnabled(true);
        ui->menuClients->setEnabled(true);
        ui->menuVoiture->setEnabled(true);
        ui->comboBoxModelesDisponibles->setEnabled(true);
        ui->comboBoxOptionsDisponibles->setEnabled(true);
        ui->pushButtonOuvrirProjet->setEnabled(true);
        ui->pushButtonNouveauProjet->setEnabled(true);
        ui->pushButtonReduction->setEnabled(true);
        ui->pushButtonEnregistrerProjet->setEnabled(true);
        ui->pushButtonAjouterOption->setEnabled(true);
        ui->pushButtonSupprimerOption->setEnabled(true);
        ui->pushButtonChoisirModele->setEnabled(true);
        ui->pushButtonVisualiserVoiture->setEnabled(true);
        ui->pushButtonNouveauContrat->setEnabled(true);
        ui->pushButtonSupprimerContrat->setEnabled(true);
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Table des options du projet en cours (ne pas modifier) /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setTableOption(int indice,string code,string intitule,float prix)
{
    // Modifie l'option de la ligne correspondant à l'indice fourni dans la table des options de l'interface graphique
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(code.c_str());
    ui->tableWidgetOptions->setItem(indice,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    char tmp[20];
    sprintf(tmp,"%.2f",prix);
    if (prix < 0.0) item->setText("");
    else item->setText(tmp);
    ui->tableWidgetOptions->setItem(indice,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(intitule.c_str());
    ui->tableWidgetOptions->setItem(indice,2,item);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videTableOption()
{
    for (int i=0 ; i<5 ; i++) setTableOption(i);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceOptionSelectionneeTable() const
{
    // retourne l'indice de l'option selectionnee dans la table des options
    QModelIndexList liste = ui->tableWidgetOptions->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combobox des modèles disponibles (ne pas modifier) /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteModeleDisponible(const char* nom,float prixDeBase)
{
    // ajoute un modèle dans le combobox correspondant (juste le nom et le prix)
    stringstream ss;
    char temp[20];
    sprintf(temp,"%.2f",prixDeBase);
    ss << nom << " (" << temp << ")";
    ui->comboBoxModelesDisponibles->addItem(ss.str().c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videComboboxModelesDisponibles()
{
    ui->comboBoxModelesDisponibles->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceModeleSelectionneCombobox() const
{
    // retourne l'indice du modèle selectionné dans le combobox des modèles
    return ui->comboBoxModelesDisponibles->currentIndex();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combox des options disponibles (ne pas modifier) ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteOptionDisponible(string intitule,float prix)
{
    // ajoute une option dans le combobox correspondant
    stringstream ss;
    char temp[20];
    sprintf(temp,"%.2f",prix);
    ss << intitule << " (" << temp << ")";
    ui->comboBoxOptionsDisponibles->addItem(ss.str().c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videComboboxOptionsDisponibles()
{
    ui->comboBoxOptionsDisponibles->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceOptionSelectionneeCombobox() const
{
    // retourne l'indice de l'option selectionnée dans le combobox des options
    return ui->comboBoxOptionsDisponibles->currentIndex();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Gestion du Projet en cours (ne pas modifier) ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setNomProjetEnCours(string nom)
{
    // Remplit le champ nom de l'interface graphique avec le nom reçu
    ui->lineEditNomProjet->setText(nom.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicGarageWindow::getNomProjetEnCours() const
{
    return ui->lineEditNomProjet->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setModele(string nom,int puissance,int moteur,float prixDeBase,string imageModele)
{
    // Remplit les champs correspondants dans l'interface graphique
    // pour le moteur (int) : 0=Essence, 1=Diesel, 2=Electrique, 3=Hybride
    ui->lineEditNomModele->setText(nom.c_str());
    ui->lineEditPuissance->setText(to_string(puissance).c_str());
    char tmp[20];
    sprintf(tmp,"%.2f",prixDeBase);
    ui->lineEditPrixDeBase->setText(tmp);

    ui->radioButtonEssence->setChecked(false);
    ui->radioButtonDiesel->setChecked(false);
    ui->radioButtonElectrique->setChecked(false);
    ui->radioButtonHybride->setChecked(false);

    if (moteur == 0) ui->radioButtonEssence->setChecked(true);
    if (moteur == 1) ui->radioButtonDiesel->setChecked(true);
    if (moteur == 2) ui->radioButtonElectrique->setChecked(true);
    if (moteur == 3) ui->radioButtonHybride->setChecked(true);

    // Met à jour l'image du modèle
    string cheminComplet = REPERTOIRE_IMAGES + imageModele;
    QLabel* label = new QLabel();
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label->setScaledContents(true);
    QPixmap *pixmap_img = new QPixmap(cheminComplet.c_str());
    label->setPixmap(*pixmap_img);
    label->resize(label->pixmap()->size());
    ui->scrollArea->setWidget(label);

    cout << "J'ai recu l image suivante en parametres :" << imageModele << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setPrix(float prix)
{
  char tmp[20];
  sprintf(tmp,"%.2f",prix);
  ui->lineEditPrix->setText(tmp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Employes (ne pas modifier) //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteTupleTableEmployes(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple.c_str(),199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char numero[20];
    strcpy(numero,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char nom[40];
    strcpy(nom,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char prenom[40];
    strcpy(prenom,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char fonction[40];
    strcpy(fonction,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetEmployes->rowCount();
    nbLignes++;
    ui->tableWidgetEmployes->setRowCount(nbLignes);
    ui->tableWidgetEmployes->setRowHeight(nbLignes-1,10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(numero);
    ui->tableWidgetEmployes->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(nom);
    ui->tableWidgetEmployes->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(prenom);
    ui->tableWidgetEmployes->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(fonction);
    ui->tableWidgetEmployes->setItem(nbLignes-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videTableEmployes()
{
    ui->tableWidgetEmployes->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceEmployeSelectionne()
{
    QModelIndexList liste = ui->tableWidgetEmployes->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Clients (ne pas modifier) ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteTupleTableClients(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple.c_str(),199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char numero[20];
    strcpy(numero,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char nom[40];
    strcpy(nom,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char prenom[40];
    strcpy(prenom,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char gsm[40];
    strcpy(gsm,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetClients->rowCount();
    nbLignes++;
    ui->tableWidgetClients->setRowCount(nbLignes);
    ui->tableWidgetClients->setRowHeight(nbLignes-1,10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(numero);
    ui->tableWidgetClients->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(nom);
    ui->tableWidgetClients->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(prenom);
    ui->tableWidgetClients->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(gsm);
    ui->tableWidgetClients->setItem(nbLignes-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videTableClients()
{
    ui->tableWidgetClients->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceClientSelectionne()
{
    QModelIndexList liste = ui->tableWidgetClients->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Contrats (ne pas modifier) //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteTupleTableContrats(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple.c_str(),199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char numero[20];
    strcpy(numero,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char vendeur[40];
    strcpy(vendeur,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char client[40];
    strcpy(client,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char voiture[40];
    strcpy(voiture,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetContrats->rowCount();
    nbLignes++;
    ui->tableWidgetContrats->setRowCount(nbLignes);
    ui->tableWidgetContrats->setRowHeight(nbLignes-1,10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(numero);
    ui->tableWidgetContrats->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(vendeur);
    ui->tableWidgetContrats->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(client);
    ui->tableWidgetContrats->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(voiture);
    ui->tableWidgetContrats->setItem(nbLignes-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videTableContrats()
{
    ui->tableWidgetContrats->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceContratSelectionne()
{
    QModelIndexList liste = ui->tableWidgetContrats->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::dialogueMessage(const char* titre,const char* message)
{
   QMessageBox::information(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::dialogueErreur(const char* titre,const char* message)
{
   QMessageBox::critical(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicGarageWindow::dialogueDemandeTexte(const char* titre,const char* question)
{
    QString chaine = QInputDialog::getText(this,titre,question);
    return chaine.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::dialogueDemandeInt(const char* titre,const char* question)
{
    return QInputDialog::getInt(this,titre,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ApplicGarageWindow::dialogueDemandeFloat(const char* titre,const char* question)
{
    return QInputDialog::getDouble(this,titre,question);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionQuitter_triggered()
{
  // TO DO (étape 12)

  QApplication::exit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::closeEvent(QCloseEvent *event)
{
  if (event == NULL) {}  // pour éviter le warning
  // TO DO (étape 12)

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionNouveau_modele_triggered()
{
  // Saisie des informations (aucune vérification n'est faite --> à gérer si vous voulez)
    string nomModele;
    int puissance, moteur, vrai;
    float prixDeBase;
    string image;
                /*Vérification du nom : Le nom doit avoir au moins un caractère*/

    do {
        nomModele = dialogueDemandeTexte("Nouveau modèle","Nom :");
        if ((nomModele.empty()) == 1)
        {
            dialogueErreur("Erreur de nom","Le nom doit contenir au moins un caractère !!");
            vrai = 0;
        }
        else
        {
            vrai = 1;
        }

    } while (vrai == 0);


                /*Vérification de la puissance : 1elle doit être comprise entre 1000 et 2000*/
    while (vrai == 1)
    {
         puissance = dialogueDemandeInt("Nouveau modèle","Puissance :");
         if (puissance < 1000 || puissance > 2000)
         {
            dialogueErreur("Puissance", "La puissance doit etre comprise entre 1000 et 2000");
         }
         else
         {
            vrai = 2;
         }
    }

                /*Vérification moteur : 0 à 3*/
    while(vrai == 2)
    {
        moteur = dialogueDemandeInt("Nouveau modèle :","Moteur (0=essence,1=diesel,2=électrique,3=hybride) :");
        if (moteur < 0 || moteur > 3)
        {
            dialogueErreur("Moteur", "Lisez les instructions. Introduire une valeur comprise entre 0 et 4 svp.");
        }
        else
        {
            vrai = 3;
        }
    }
 
                /*Vérification prix*/
    while (vrai == 3)
    {
        prixDeBase = dialogueDemandeFloat("Nouveau modèle","Prix de base :");
        if (prixDeBase < 0 || prixDeBase > 80000)
        {
            dialogueErreur("Prix", "Le prix DOIT etre positif et logique - T'es pas chez porche ");
        }
        else
        {
            vrai = 4;
        }
    }

                /*On vérifie qu'il y a bien une image*/
    while (vrai == 4)
    {
          image = dialogueDemandeTexte("Nouveau modèle","Nom du fichier de l'image :");
          if (image.length() < 5)
          {
            dialogueErreur("Image", "Indiquer le nom de l image suivi d'un point et son extention (exemple 1.jpg");
          }
          else
          {
            vrai = 1;
          }
    }



  // TO DO (étape 9)
            // Pour moteur :
  const char* NomModele = new char[100];
  NomModele = nomModele.c_str();

  Moteur m3;

  switch (moteur)
  {
    case 0 : m3 = Essence;
        break;
    case 1 : m3 = Diesel;
        break;
    case 2 : m3 = Electrique;
        break;
    case 3 : m3 = Hybride;
        break;
  }


  Garage::getInstance().ajouteModele(Modele(NomModele, puissance, m3, prixDeBase, image));
            //ERREUR 1 IMAGE
  //Garage::getInstance().ajoutImageModele(NomModele, image);
  
  ajouteModeleDisponible(NomModele, prixDeBase);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionNouvelle_option_triggered()
{

  // TO DO (étape 9)

    string code;
    string intitule;
    float prix;
    int vrai = 0;


    try
    {

                        /*Vérification du code : doit avoir 4 caracteres */
        while (vrai == 0)
        {
             code = dialogueDemandeTexte("Nouvelle option : ","Code :");
             if (code.length() != 4)
             {
                dialogueErreur("Code : ", "Le code doit etre composé de 4 caracteres.");
             }
             else
             {
                vrai = 1;
             }
             //vrai = 1;
        }


                        /*Vérification de l'intitule : ne peut etre vide*/
        while (vrai == 1)
        {
             intitule = dialogueDemandeTexte("Nouvelle option","Intitule :");
             if (intitule.empty() == 1)
             {
                dialogueErreur("Intitule : ", "L'intitule ne peut etre nul.");
             }
             else
             {
                vrai = 2;
             }

             //vrai = 2;
        }



                    /*Vérification prix option doit etre positif*/
        while(vrai == 2)
        {
            prix = dialogueDemandeFloat("Nouvelle option :","Prix");
            if (prix < 0)
            {
                dialogueErreur("Prix : ", "Le prix ne peut etre negatif.");
            }
            else
            {
                vrai = 3;
            }

            //vrai = 3;
        }
            //Ajout dans vecteur Option

        Garage::getInstance().ajouteOption(Option(code, intitule, prix));
    }





    catch(OptionException e)
    {
        const char* erreur  = new char[100];
        string recup;

        recup = e.Exception::getException();
        erreur = recup.c_str();
        printf("\n\nErreur vaut : %s\n\n", erreur);
              cout << "Original : " << e.Exception::getException().c_str();
        dialogueErreur("Erreur option : ", erreur);
    }
     
    catch(Exception e)
    {
        const char* erreur = new char[100];
        erreur = e.Exception::getException().c_str();
        printf("\n\nErreur vaut : %s\n\n", erreur);
        cout << "Original : " << e.Exception::getException().c_str();
      
        
        dialogueErreur("Erreur option : ", erreur);
    }
    //Ajout dans fenetre combobox       
  
    ajouteOptionDisponible(intitule, prix);


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionAjouterEmploye_triggered()
{
  // TO DO (étape 11)
    Employe e;
    int vrai = 0;




        do {
            e.setNom(dialogueDemandeTexte("Employé : ", "Introduisez le nom : "));
            if ((e.getNom().empty()) == 1)
            {
                dialogueErreur("Erreur de nom","Le nom doit contenir au moins un caractère !!");
                vrai = 0;
            }
            else
            {
                vrai = 1;
            }

        } while (vrai == 0);


                    /*Vérification du prenom : meme chose que nom*/
        while (vrai == 1)
        {
             e.setPrenom(dialogueDemandeTexte("Employé : ", "Introduisez le prenom : "));
             if ((e.getPrenom().empty()) == 1)
             {
                dialogueErreur("Prenom", "Le prenom doit contenir au moins un caractère !!");
             }
             else
             {
                vrai = 2;
             }
        }

                /*Meme chose que prenom et nom*/
        while(vrai == 2)
        {
             e.setLogin(dialogueDemandeTexte("Employé : ", "Introduisez le login : "));
             if ((e.getLogin().empty()) == 1)
             {
                dialogueErreur("Login", "Le login doit contenir au moins un caractère !!");
             }
             else
             {
                vrai = 3;
             }
        }
        e.setFonction(dialogueDemandeTexte("Employé : ", "Introduisez la fonction (Administratif OU Vendeur) : "));

        Garage::getInstance().ajouteEmploye(e.getNom(), e.getPrenom(), e.getLogin(), e.getFonction());



        videTableEmployes();
        Vecteur<Employe> employes2 = Garage::getInstance().getEmployes();

        Iterateur<Employe> iter(employes2);
        iter.reset();
        Employe temp;

        while(!iter.end())
        {
            temp = (Employe)iter; 
        
            ajouteTupleTableEmployes(temp.Tuple());

            iter++;
        }
        cout << endl<< endl<< endl<< endl<< endl<< endl;
    Garage::getInstance().afficheEmployes();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionSupprimerEmploye_par_numero_triggered()
{
  // TO DO (étape 11)
    int choix;

    choix = dialogueDemandeInt("Employe ", "Entrez le numero à supprimer");

    cout << endl << "Votre choix : " << choix << endl;

    Garage::getInstance().supprimeEmployeParNumero(choix);

        videTableEmployes();
        Garage::getInstance().afficheEmployes();
        //Mise a jour du vecteur d employes
        Vecteur<Employe> employes3 = Garage::getInstance().getEmployes();

        Iterateur<Employe> iter(employes3);
        iter.reset();
        Employe temp;
        int i = 0;
        while(!iter.end())
        {
            temp = employes3[i]; 
        
            ajouteTupleTableEmployes(temp.Tuple());

            iter++;
            i++;
        }


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionSupprimerEmploye_selection_triggered()
{
  // TO DO (étape 11)
    Garage::getInstance().afficheEmployes();
                    
    if (getIndiceEmployeSelectionne() != -1)
    {
        Garage::getInstance().supprimeEmployeParIndice(getIndiceEmployeSelectionne());
    }
    else
    {
        dialogueErreur("Suppression", "Aucune ligne selectionnée");
    }

        videTableEmployes();
        Garage::getInstance().afficheEmployes();
        //Mise a jour du vecteur d employes
        Vecteur<Employe> employes3 = Garage::getInstance().getEmployes();

        Iterateur<Employe> iter(employes3);
        iter.reset();
        Employe temp;
        int i = 0;
        while(!iter.end())
        {
            temp = employes3[i]; 
        
            ajouteTupleTableEmployes(temp.Tuple());

            iter++;
            i++;
        }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionAjouterClient_triggered()
{
  // TO DO (étape 11)
    Client e;
    int vrai = 0;


        do {
            e.setNom(dialogueDemandeTexte("Client : ", "Introduisez le nom : "));
            if ((e.getNom().empty()) == 1)
            {
                dialogueErreur("Erreur de nom","Le nom doit contenir au moins un caractère !!");
                vrai = 0;
            }
            else
            {
                vrai = 1;
            }

        } while (vrai == 0);


                    /*Vérification du prenom : meme chose que nom*/
        while (vrai == 1)
        {
             e.setPrenom(dialogueDemandeTexte("Client : ", "Introduisez le prenom : "));
             if ((e.getPrenom().empty()) == 1)
             {
                dialogueErreur("Prenom", "Le prenom doit contenir au moins un caractère !!");
             }
             else
             {
                vrai = 2;
             }
        }

                /*Meme chose que prenom et nom*/
        while(vrai == 2)
        {
             e.setGsm(dialogueDemandeTexte("Client : ", "Introduisez le GSM : "));
             if ((e.getGsm().size()) < 10)
             {
                dialogueErreur("GSM", "Le GSM doit contenir au moins 10 caractère !!");
             }
             else
             {
                vrai = 3;
             }
        }
        

        Garage::getInstance().ajouteClient(e.getNom(), e.getPrenom(), e.getGsm());



        videTableClients();
        Vecteur<Client> clients1 = Garage::getInstance().getClients();

        Iterateur<Client> iter(clients1);
        iter.reset();
        Client temp;

        while(!iter.end())
        {
            temp = (Client)iter; 
        
            ajouteTupleTableClients(temp.Tuple());

            iter++;

        }
        cout << endl<< endl<< endl<< endl<< endl<< endl;
    Garage::getInstance().afficheClients();


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionSupprimerClient_par_numero_triggered()
{
  // TO DO (étape 11)
    // A faire apres correction employés.

    int choix;

    choix = dialogueDemandeInt("Client ", "Entrez le numero à supprimer");

    cout << endl << "Votre choix : " << choix << endl;

    Garage::getInstance().supprimeClientParNumero(choix);

        videTableClients();
        Garage::getInstance().afficheClients();
        //Mise a jour du vecteur d employes
        Vecteur<Client> clients3 = Garage::getInstance().getClients();

        Iterateur<Client> iter(clients3);
        iter.reset();
        Client temp;
        int i = 0;
        while(!iter.end())
        {
            temp = clients3[i]; 
        
            ajouteTupleTableClients(temp.Tuple());

            iter++;
            i++;
        }


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionSupprimerClient_selection_triggered()
{
  // TO DO (étape 11)
    Garage::getInstance().afficheClients();
                    
    if (getIndiceClientSelectionne() != -1)
    {
        Garage::getInstance().supprimeClientParIndice(getIndiceClientSelectionne());
    }
    else
    {
        dialogueErreur("Suppression", "Aucune ligne selectionnée");
    }

        videTableClients();
        Garage::getInstance().afficheClients();

        //Mise a jour du vecteur d employes
        Vecteur<Client> clients3 = Garage::getInstance().getClients();

        Iterateur<Client> iter(clients3);
        iter.reset();
        Client temp;

        while(!iter.end())
        {
            temp = (Client)iter; 
        
            ajouteTupleTableClients(temp.Tuple());

            iter++;

        }
        
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionLogin_triggered()
{
  // TO DO (étape 11)
        string log = dialogueDemandeTexte("Connection : ", "Introduisez le login : ");
        

        Vecteur<Employe> employes3 = Garage::getInstance().getEmployes();
        int vrai = 0;
        Iterateur<Employe> iter(employes3);
        iter.reset();
        Employe temp;

        int i = 0;
        Garage::getInstance().afficheEmployes();

        while(!iter.end())
        {
            temp = (Employe)iter; 
            if (temp.getLogin() == log)
            {
                (Garage::EmplEnCours) = &Garage::getInstance().getEmployes()[i];
                vrai = 1;
                iter.end();
            }
            iter++;
            i++;
        }

        if (vrai == 0)
        {
            dialogueErreur ("Login", "Login incorrect");
        }
        else
        {
            try
            {
                if (Garage::EmplEnCours->motDePasseExiste() == 0)
                {
                    dialogueErreur ("Login", "Première connection. Vous devez choisir un mot de passe AlPHANUMERIQUE d'au moins 6 caractères. Faites le maintenant et relogez-vous.");
                    string mdpintroduit = dialogueDemandeTexte("Login", "Entrez le mot de passe");
                    Garage::EmplEnCours->setMotDePasse(mdpintroduit);
                }
                else
                {
                    if (Garage::EmplEnCours->getMotDePasse() == dialogueDemandeTexte("Login", "Mot de passe :"))
                    {
                        if (Garage::EmplEnCours->getFonction() == "Vendeur")
                        {
                            setRole(2);
                        }
                        else
                        {
                            setRole(1);
                        }
                        setTitre(Garage::EmplEnCours->getNom());
                    }
                    else
                    {
                        dialogueErreur("Login", "Mot de passe non reconnu");
                    }
                }

            }

                catch(Exception p)
                {
                    const char* erreur = new char[100];
                    erreur = p.Exception::getException().c_str();
                    cout << "Original : " << p.Exception::getException().c_str()<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl;
                    dialogueErreur("Erreur mdp",p.Exception::getException().c_str());
                }                
            

            catch(Exception p)
            {
                const char* erreur = new char[100];
                erreur = p.Exception::getException().c_str();
                cout << "Original : " << p.Exception::getException().c_str();
                dialogueErreur("Erreur mdp",p.Exception::getException().c_str());
            }
      

        }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionLogout_triggered()
{
  // TO DO (étape 11)
    setRole();
    setTitre("Application Garage");
    Garage::EmplEnCours = NULL;

            //9999
    /*Garage::getInstance().save();
    cout << "Apres l ecriture, voici la lecture" << endl;
    Garage::getInstance().load("Garage.data");*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionReset_Mot_de_passe_triggered()
{
  // TO DO (étape 11)
    Garage::EmplEnCours->ResetMotDePasse();
    dialogueErreur("Mot de passe", "Mot de passe réinitialisé");

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonChoisirModele_clicked()
{
  // TO DO (étape 9)
    int i = getIndiceModeleSelectionneCombobox();

    if (i == -1)
    {
        dialogueErreur("Modele : ", "Aucun modele selectionné");
    }
    else
    {
      Garage::getProjetEnCours().setModele(Garage::getInstance().getModele(i));
      ApplicGarageWindow::setModele(Garage::getProjetEnCours().getModele().getNom(), Garage::getProjetEnCours().getModele().getPuissance(), Garage::getProjetEnCours().getModele().getMoteur(), Garage::getProjetEnCours().getModele().getPrixDeBase(), Garage::getProjetEnCours().getModele().getImage());
      setPrix(Garage::getProjetEnCours().Voiture::getPrix());
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonAjouterOption_clicked()
{
  // TO DO (étape 9)

    try
    { 
        int i = getIndiceOptionSelectionneeCombobox();

        if (i == -1)
        {
            dialogueErreur("Option : ", "Aucune option selectionnée");
        }
        else
        {
            Option o;
                        // On met l option dans la voiture (entre position 0 et 4 du vecteur options dans voiture)
            Garage::getProjetEnCours().AjouteOption(Garage::getInstance().getOption(i));
            o = Garage::getInstance().getOption(i);
                        //

            for (int j = 0; j < 5; j++)
            {
                if(/*v.getOption(j)->Option::getCode() == o.Option::getCode() && */Garage::getProjetEnCours().getOption(j) != NULL)
                {
                    ApplicGarageWindow::setTableOption(j, Garage::getProjetEnCours().getOption(j)->Option::getCode(), Garage::getProjetEnCours().getOption(j)->Option::getIntitule(), Garage::getProjetEnCours().getOption(j)->Option::getPrix());   
                }

            }
                
        }
        setPrix(Garage::getProjetEnCours().Voiture::getPrix());
    }

    catch(OptionException e)
    {
        const char* erreur  = new char[100];
        string recup;

        recup = e.Exception::getException();
        erreur = recup.c_str();
        dialogueErreur("Erreur option : ", erreur);
    }
     
    catch(Exception e)
    {
        const char* erreur = new char[100];
        erreur = e.Exception::getException().c_str();
        cout << "Original : " << e.Exception::getException().c_str();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonSupprimerOption_clicked()
{
  // TO DO (étape 9)
    int i = getIndiceOptionSelectionneeTable();
    if (i == -1)
    {
        dialogueErreur("Supprime option :", "Choisir une ligne avec une option");
    }
    else
    {
        // On n'a pas fait la vérification d'exception en effet impossible d'avoir une erreur.
        Option* o = new Option;
        o = Garage::getProjetEnCours().Voiture::getOption(i);
        Garage::getProjetEnCours().Voiture::RetireOption(o->getCode());

videTableOption();
            for (int j = 0; j < 5; j++)
            {
                if(Garage::getProjetEnCours().getOption(j) != NULL)
                {
                    ApplicGarageWindow::setTableOption(j, Garage::getProjetEnCours().getOption(j)->Option::getCode(), Garage::getProjetEnCours().getOption(j)->Option::getIntitule(), Garage::getProjetEnCours().getOption(j)->Option::getPrix());   
                }
            }
                
        
        setPrix(Garage::getProjetEnCours().Voiture::getPrix());

    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonReduction_clicked()
{
  // TO DO (étape 9)
    int i = getIndiceOptionSelectionneeTable();
    if (i == -1)
    {
        dialogueErreur("Reduction option :", "Choisir une ligne avec une option");
    }
    else
    {
        Option o = *(Garage::getProjetEnCours()[i]);
        o--;
       // Option p(const Option &o);

                // Doit venir ici  Garage::getProjetEnCours()[i]->Option::setPrix(o->getPrix())
        Garage::getProjetEnCours()[i]->setPrix(o.getPrix());
        cout << *Garage::getProjetEnCours()[i] << endl;
        //Garage::getProjetEnCours()[i] = &o;

        setPrix(Garage::getProjetEnCours().Voiture::getPrix());
    }

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonEnregistrerProjet_clicked()
{
  // TO DO (étape 9)
    setNomProjetEnCours(getNomProjetEnCours());

    Garage::getProjetEnCours().setNom(ApplicGarageWindow::getNomProjetEnCours());
    Garage::getProjetEnCours().Save();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonOuvrirProjet_clicked()
{
  // TO DO (étape 9)

    Garage::getProjetEnCours().Load(getNomProjetEnCours());
    ApplicGarageWindow::setModele(Garage::getProjetEnCours().getModele().getNom(), Garage::getProjetEnCours().getModele().getPuissance(), Garage::getProjetEnCours().getModele().getMoteur(), Garage::getProjetEnCours().getModele().getPrixDeBase(), Garage::getProjetEnCours().getModele().getImage());
    setPrix(Garage::getProjetEnCours().Voiture::getPrix());
    for (int j = 0; j < 5; j++)
    {
        if(/*v.getOption(j)->Option::getCode() == o.Option::getCode() && */Garage::getProjetEnCours().getOption(j) != NULL)
        {
            ApplicGarageWindow::setTableOption(j, Garage::getProjetEnCours().getOption(j)->Option::getCode(), Garage::getProjetEnCours().getOption(j)->Option::getIntitule(), Garage::getProjetEnCours().getOption(j)->Option::getPrix());   
        }
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonNouveauProjet_clicked()
{
  // TO DO (étape 9)

    Garage::resetProjetEnCours();
    ApplicGarageWindow::setModele("Peugeot 308",120,1,22300.0,"308.jpg");
    setPrix(Garage::getProjetEnCours().Voiture::getPrix());
    for (int j = 0; j < 5; j++)
    {

        ApplicGarageWindow::setTableOption(j, " "," ", -1.0);   

    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonNouveauContrat_clicked()
{
  // TO DO (étape 13)


    //d abord on construit avec donnees projet en cours,  puis on les insere dans vecteur


    Garage::getInstance().ajouteContrat(Contrat::numero, getIndiceClientSelectionne(), Garage::EmplEnCours->getNumero(), getNomProjetEnCours());



    ostringstream s2;
    string ven, cli, proj;
    if (getIndiceClientSelectionne() != -1)
    {
        cli = Garage::getInstance().getClients()[getIndiceClientSelectionne()].getNom();
    }
    else
    {
        dialogueErreur ("Erreur :", "Selectionnez un client AVANT");
    }
    

    

    s2 << Contrat::numero  << ";" << Garage::EmplEnCours->getNom() << ";" << cli << ";" <<getNomProjetEnCours(); 

    //return s2.str();

    ajouteTupleTableContrats(s2.str());
    Contrat::numero++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonSupprimerContrat_clicked()
{
  // TO DO (étape 13)
   // getIndiceContratSelectionne();
    ostringstream s2;
    Garage::getInstance().getContrats().retire(getIndiceContratSelectionne());
    videTableContrats();

    for (int i = 0; i < Garage::getInstance().getContrats().size(); i++)
    {

    }


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonVisualiserVoiture_clicked()
{
  // TO DO (étape 13)
Garage::getInstance().save();

}

