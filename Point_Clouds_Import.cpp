//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdlib.h>

#include "Visualization.h"
#include "Point_Clouds_Import.h"
#include "Adaptive_Triangulation.h"
#include "Rendering.h"

#include <fstream>
#include <iostream>


using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPoint_Clouds_Import *Point_Clouds_Import;
bool save=true;
extern AnsiString AppDir;
char fichier [200],fichierlu [200];
int nbre_pt=0;

//----------------------------------------!!!!!!!!!!!!!!!!!!----------------


//---------------------------------------------------------------------------
__fastcall TPoint_Clouds_Import::TPoint_Clouds_Import(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void liste_point_BEY::effacer_liste()
{
 noeud_point_nuage_BEY *next;
 noeud_point_nuage_BEY *courant=debut;

	 while(courant!=NULL)
	 {
	  next = courant->getsuiv();
	  free(courant);
	  courant = next;
	 }

  debut=NULL;
  fin=NULL;
}

//---------------------------------------------------------------------------
void __fastcall TPoint_Clouds_Import::Button1Click(TObject *Sender)
{
  Point_Clouds_Import->OpenDialog1->FileName="";

if(OpenDialog1->Execute())
{
	 Screen->Cursor= crHourGlass;

	 if(lecture_nuage_pts==true)nuage_pts_BEY->effacer_liste(); //BEY

	 nuage_pts_BEY =new liste_point_BEY;
	 nuage_pts_BEY->initialiser();

	 int nbre_pt_total=0;

for(int i=0;i<OpenDialog1->Files->Count;i++)
{

	 AnsiString fichier =  OpenDialog1->Files->Strings[i];
	 entree.setnom_f(fichier);
	 entree.verifier_fichier(fichier); //vérification et récupération du nombre de pts

		 if(entree.getsyntaxe()==false)
		 {
		 ShowMessage("Le fichier contient des erreurs.......!!!!");
		 Screen->Cursor= crDefault;
		 //return;

		 continue;
		 }

//---------------------------------------------------lecture du fichier----------------------------------------

	 nbre_pt_total=nbre_pt_total+nbre_pt;

	 ifstream fin(entree.getnom_f().c_str());

	 nuage_pts_BEY->setnbre_pt(nbre_pt_total);

	 double xx2,yy2,zz2;


	   for(int i=0;i<nbre_pt;i++)
			 {
			 fin>>xx2;
			 fin>>yy2;
			 fin>>zz2;

			 point_nuage *pt=new point_nuage;

			 pt->setx((float)xx2);
			 pt->sety((float)yy2);
			 pt->setz((float)zz2);

			 noeud_point_nuage_BEY *p=new noeud_point_nuage_BEY;
			 p->setpoint(pt);

			 nuage_pts_BEY->ajouter_element(p);
			 }

	   fin.close();

	}
}

	lecture_nuage_pts=true;

	 int ij=0;
	 noeud_point_nuage_BEY *temp3;
	 temp3=nuage_pts_BEY->getdebut();

	 while(temp3!=NULL)
	 {
			 temp3=temp3->getsuiv();
			 ij++;
	 }

	 nuage_pts_BEY->setnbre_pt(ij);

			 //Point_Clouds_Import->Caption="Lecture du nuage de points (points générés)";

	   nuage_pts_BEY->chercher_pptes_nuage_points();
	   GroupBox5->Visible=true;
	   GroupBox6->Visible=true;
	   Button3->Visible=true;
	   Edit10->Text=nuage_pts_BEY->getnbre_pt();

	   Visualization->Calculer_Limites_Globales_Scene(nuage_pts_BEY->getxmin(), nuage_pts_BEY->getymin(), nuage_pts_BEY->getzmin(), nuage_pts_BEY->getxmax(), nuage_pts_BEY->getymax(), nuage_pts_BEY->getzmax());

//*******************************

Screen->Cursor= crDefault;

GroupBox8->Visible=true;

}//fonction

//------------------------------------------------------------------------------
void liste_point_BEY::inverser_nuage_points()
{

noeud_point_nuage_BEY *t;
t=debut;

while (t)
{
  double z=2*Point_Clouds_Import->Edit13->Text.ToDouble()-t->getpoint()->getz();
  t->getpoint()->setz((float)z);
  t=t->getsuiv();
}


t=debut;

double z3;

zmax=z3=t->getpoint()->getz();
zmin=z3=t->getpoint()->getz();

t=t->getsuiv();

while (t)
{
  z3=t->getpoint()->getz();

 if (z3>zmax)zmax=z3;
 if (z3<zmin)zmin=z3;

 t=t->getsuiv();
}

  double L=xmax-xmin;
  double l=ymax-ymin;
  double H=zmax-zmin;

  Point_Clouds_Import->Edit1->Text=FormatFloat("0.000",xmax);
  Point_Clouds_Import->Edit4->Text=FormatFloat("0.000",xmin);

  Point_Clouds_Import->Edit2->Text=FormatFloat("0.000",ymax);
  Point_Clouds_Import->Edit5->Text=FormatFloat("0.000",ymin);

  Point_Clouds_Import->Edit3->Text=FormatFloat("0.000",zmax);
  Point_Clouds_Import->Edit6->Text=FormatFloat("0.000",zmin);

  Point_Clouds_Import->Edit7->Text=FormatFloat("0.000",L);
  Point_Clouds_Import->Edit8->Text=FormatFloat("0.000",l);
  Point_Clouds_Import->Edit9->Text=FormatFloat("0.000",H);

//---------------------------
//---------------------------

} //fonction


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Nuage_Pts_BEY::inverser_nuage_points()
{
double z_inversion=Point_Clouds_Import->Edit13->Text.ToDouble();

for (int i=0; i<nbre_pts_total; i++)
{
  double z=2*z_inversion-nuage_pts_BEY[i].getz();
  nuage_pts_BEY[i].setz((float)z);
}


float z3;

zmax=nuage_pts_BEY[0].getz();
zmin=nuage_pts_BEY[0].getz();

for(int i=0; i<nbre_pts_total; i++)
{
  z3=nuage_pts_BEY[i].getz();

 if (z3>zmax)zmax=z3;
 if (z3<zmin)zmin=z3;
}

  H=zmax-zmin;

  Point_Clouds_Import->Edit1->Text=FormatFloat("0.000",xmax);
  Point_Clouds_Import->Edit4->Text=FormatFloat("0.000",xmin);

  Point_Clouds_Import->Edit2->Text=FormatFloat("0.000",ymax);
  Point_Clouds_Import->Edit5->Text=FormatFloat("0.000",ymin);

  Point_Clouds_Import->Edit3->Text=FormatFloat("0.000",zmax);
  Point_Clouds_Import->Edit6->Text=FormatFloat("0.000",zmin);

  Point_Clouds_Import->Edit7->Text=FormatFloat("0.000",L);
  Point_Clouds_Import->Edit8->Text=FormatFloat("0.000",l);
  Point_Clouds_Import->Edit9->Text=FormatFloat("0.000",H);

} //fonction


//------------------------------------------------------------------------------

void liste_point_BEY::chercher_pptes_nuage_points()
{

noeud_point_nuage_BEY *t;
t=debut;


double x1,x2,x3;

xmax=x1=t->getpoint()->getx();
xmin=x1=t->getpoint()->getx();

ymax=x2=t->getpoint()->gety();
ymin=x2=t->getpoint()->gety();

zmax=x3=t->getpoint()->getz();
zmin=x3=t->getpoint()->getz();

t=t->getsuiv();

while (t)
{
   x1=t->getpoint()->getx();
   x2=t->getpoint()->gety();
   x3=t->getpoint()->getz();

 if (x1>xmax)xmax=x1;
 if (x1<xmin)xmin=x1;

 if (x2>ymax)ymax=x2;
 if (x2<ymin)ymin=x2;

 if (x3>zmax)zmax=x3;
 if (x3<zmin)zmin=x3;

t=t->getsuiv();

 }

  double L=xmax-xmin;
  double l=ymax-ymin;
  double H=zmax-zmin;

  Point_Clouds_Import->Edit1->Text=FormatFloat("0.000",xmax);
  Point_Clouds_Import->Edit4->Text=FormatFloat("0.000",xmin);

  Point_Clouds_Import->Edit2->Text=FormatFloat("0.000",ymax);
  Point_Clouds_Import->Edit5->Text=FormatFloat("0.000",ymin);

  Point_Clouds_Import->Edit3->Text=FormatFloat("0.000",zmax);
  Point_Clouds_Import->Edit6->Text=FormatFloat("0.000",zmin);

  Point_Clouds_Import->Edit7->Text=FormatFloat("0.000",L);
  Point_Clouds_Import->Edit8->Text=FormatFloat("0.000",l);
  Point_Clouds_Import->Edit9->Text=FormatFloat("0.000",H);

} //fonction

//----------------------------------------------------------------------
void liste_point::chercher_pptes_nuage_points()
{

noeud_point_nuage *t;
 t=debut;


double x1,x2,x3;

xmax=x1=t->getpoint()->getx();
xmin=x1=t->getpoint()->getx();

ymax=x2=t->getpoint()->gety();
ymin=x2=t->getpoint()->gety();

zmax=x3=t->getpoint()->getz();
zmin=x3=t->getpoint()->getz();

t=t->getsuiv();

while (t)
{
   x1=t->getpoint()->getx();
   x2=t->getpoint()->gety();
   x3=t->getpoint()->getz();

 if (x1>xmax)xmax=x1;
 if (x1<xmin)xmin=x1;

 if (x2>ymax)ymax=x2;
 if (x2<ymin)ymin=x2;

 if (x3>zmax)zmax=x3;
 if (x3<zmin)zmin=x3;

t=t->getsuiv();

 }

  L=xmax-xmin;
  l=ymax-ymin;
  H=zmax-zmin;

  Point_Clouds_Import->Edit1->Text=FormatFloat("0.000",xmax);
  Point_Clouds_Import->Edit4->Text=FormatFloat("0.000",xmin);

  Point_Clouds_Import->Edit2->Text=FormatFloat("0.000",ymax);
  Point_Clouds_Import->Edit5->Text=FormatFloat("0.000",ymin);

  Point_Clouds_Import->Edit3->Text=FormatFloat("0.000",zmax);
  Point_Clouds_Import->Edit6->Text=FormatFloat("0.000",zmin);

  Point_Clouds_Import->Edit7->Text=FormatFloat("0.000",L);
  Point_Clouds_Import->Edit8->Text=FormatFloat("0.000",l);
  Point_Clouds_Import->Edit9->Text=FormatFloat("0.000",H);

} //fonction
  //----------------------------------------------------------------------
void Nuage_Pts_BEY::chercher_pptes_nuage_points()
{

float x1,x2,x3;

xmax=-100000000;
xmin=100000000;

ymax=-100000000;
ymin=100000000;

zmax=-100000000;
zmin=100000000;

for(int i=0; i<nbre_pts_total; i++)
{
   x1=nuage_pts_BEY[i].getx();
   x2=nuage_pts_BEY[i].gety();
   x3=nuage_pts_BEY[i].getz();

 if (x1>xmax)xmax=x1;
 if (x1<xmin)xmin=x1;

 if (x2>ymax)ymax=x2;
 if (x2<ymin)ymin=x2;

 if (x3>zmax)zmax=x3;
 if (x3<zmin)zmin=x3;

}

  L=xmax-xmin;
  l=ymax-ymin;
  H=zmax-zmin;

  Point_Clouds_Import->Edit1->Text=FormatFloat("0.000",xmax);
  Point_Clouds_Import->Edit4->Text=FormatFloat("0.000",xmin);

  Point_Clouds_Import->Edit2->Text=FormatFloat("0.000",ymax);
  Point_Clouds_Import->Edit5->Text=FormatFloat("0.000",ymin);

  Point_Clouds_Import->Edit3->Text=FormatFloat("0.000",zmax);
  Point_Clouds_Import->Edit6->Text=FormatFloat("0.000",zmin);

  Point_Clouds_Import->Edit7->Text=FormatFloat("0.000",L);
  Point_Clouds_Import->Edit8->Text=FormatFloat("0.000",l);
  Point_Clouds_Import->Edit9->Text=FormatFloat("0.000",H);

} //fonction

//------------------------------------------------------------------

	void liste_point::dessiner_liste_point()
    {
     if(Adaptive_Triangulation->CheckBox7->Checked)glPointSize((float)Adaptive_Triangulation->ComboBox7->Text.ToDouble());


     glColor3d(1,0,0);

	noeud_point_nuage *p;
    p=debut;
    double x1,y1,z1;

    while (p)
    {
    x1=p->getpoint()->getx();
    y1=p->getpoint()->gety();
    z1=p->getpoint()->getz();

       glBegin(GL_POINTS);
       glVertex3d(x1,y1,z1);
       glEnd();


      p=p->getsuiv();
    }

    } //fonction

//------------------------------------------------------------------

void Nuage_Pts_BEY::dessiner_nuage_pts()
{
	 if(Point_Clouds_Import->CheckBox4->Checked)glPointSize((float)Point_Clouds_Import->ComboBox1->Text.ToDouble());
	 if(Adaptive_Triangulation->CheckBox7->Checked)glPointSize((float)Adaptive_Triangulation->ComboBox7->Text.ToDouble());
	 if(Adaptive_Triangulation->CheckBox21->Checked)glPointSize((float)Adaptive_Triangulation->ComboBox20->Text.ToDouble());

	 glColor3d(1,0,0);

	double x1,y1,z1;

	for (int i=0; i<nbre_pts_total; i++)
	{
	x1=nuage_pts_BEY[i].getx();
	y1=nuage_pts_BEY[i].gety();
	z1=nuage_pts_BEY[i].getz();

	   glBegin(GL_POINTS);
	   glVertex3d(x1,y1,z1);
	   glEnd();
	}

} //fonction


//-----------------------------------------------------------------

//-----------------------------------------------------------------

    void liste_point_BEY::dessiner_liste_point()
    {
	 if(Adaptive_Triangulation->CheckBox7->Checked)glPointSize((float)Adaptive_Triangulation->ComboBox7->Text.ToDouble());

     glColor3d(1,0,0);

    noeud_point_nuage_BEY *p;
    p=debut;
    double x1,y1,z1;

    while (p)
    {
    x1=p->getpoint()->getx();
    y1=p->getpoint()->gety();
    z1=p->getpoint()->getz();

       glBegin(GL_POINTS);
       glVertex3d(x1,y1,z1);
       glEnd();


      p=p->getsuiv();
    }

    } //fonction

//-----------------------------------------------------------------
void liste_point::dessiner_brut_min()
{

	 glLineWidth((float)Point_Clouds_Import->ComboBox3->Text.ToDouble());

	   glColor3d(1,0,0);
	   glBegin(GL_LINE_LOOP);
	  glVertex3d(xmin, ymin, zmax);
		  glVertex3d(xmin, ymax, zmax);

		  glVertex3d(xmax, ymax, zmax);
		  glVertex3d(xmax, ymin, zmax);

	   glEnd();


	   glBegin(GL_LINE_LOOP);
	  glVertex3d(xmin, ymin, zmin);
		  glVertex3d(xmin, ymax, zmin);

		  glVertex3d(xmax, ymax, zmin);
		  glVertex3d(xmax, ymin, zmin);

	   glEnd();

	   glBegin(GL_LINES);
	  glVertex3d(xmin, ymin, zmax);
		  glVertex3d(xmin, ymin, zmin);

		  glVertex3d(xmax, ymax, zmax);
		  glVertex3d(xmax, ymax, zmin);

		  glVertex3d(xmin, ymax, zmax);
		  glVertex3d(xmin, ymax, zmin);

		  glVertex3d(xmax, ymin, zmax);
		  glVertex3d(xmax, ymin, zmin);
	   glEnd();

 //--------------------------------------

	   if(Point_Clouds_Import->RadioButton2->Checked)
	   {
	   glColor3d(0,1,0);
	   glBegin(GL_POLYGON);
	  glVertex3d(xmin, ymin, zmax);
		  glVertex3d(xmin, ymax, zmax);

		  glVertex3d(xmax, ymax, zmax);
		  glVertex3d(xmax, ymin, zmax);

	   glEnd();


	   glBegin(GL_POLYGON);
	  glVertex3d(xmin, ymin, zmin);
		  glVertex3d(xmin, ymax, zmin);

		  glVertex3d(xmax, ymax, zmin);
		  glVertex3d(xmax, ymin, zmin);

	   glEnd();

	  glBegin(GL_POLYGON);
	  glVertex3d(xmax, ymax,zmax);
		  glVertex3d(xmax, ymin, zmax);

		  glVertex3d(xmax, ymin, zmin);
		  glVertex3d(xmax, ymax, zmin);

	   glEnd();
		 glBegin(GL_POLYGON);
	  glVertex3d(xmin, ymax,zmax);
		  glVertex3d(xmin, ymin, zmax);

		  glVertex3d(xmin, ymin, zmin);
		  glVertex3d(xmin, ymax, zmin);

	   glEnd();

		 glBegin(GL_POLYGON);
	  glVertex3d(xmin, ymin,zmax);
		  glVertex3d(xmin, ymin, zmin);

		  glVertex3d(xmax, ymin, zmin);
		  glVertex3d(xmax, ymin, zmax);

	   glEnd();

		glBegin(GL_POLYGON);

	  glVertex3d(xmin, ymax,zmax);
		  glVertex3d(xmin, ymax, zmin);

		  glVertex3d(xmax, ymax, zmin);
		  glVertex3d(xmax, ymax, zmax);

	   glEnd();

	   }


} //fonction

//-----------------------------------------------------------------
void Nuage_Pts_BEY::dessiner_brut_min()
{

	   glColor3d(0,1,0);

	   if(Point_Clouds_Import->RadioButton1->Checked)  //Filaire
	   {
	   glLineWidth((float)Point_Clouds_Import->ComboBox3->Text.ToDouble());

	   glBegin(GL_LINE_LOOP);
	   glVertex3d(xmin, ymin, zmax);
		  glVertex3d(xmin, ymax, zmax);

		  glVertex3d(xmax, ymax, zmax);
		  glVertex3d(xmax, ymin, zmax);

	   glEnd();


	   glBegin(GL_LINE_LOOP);
	   glVertex3d(xmin, ymin, zmin);
		  glVertex3d(xmin, ymax, zmin);

		  glVertex3d(xmax, ymax, zmin);
		  glVertex3d(xmax, ymin, zmin);

	   glEnd();

	   glBegin(GL_LINES);
	   glVertex3d(xmin, ymin, zmax);
		  glVertex3d(xmin, ymin, zmin);

		  glVertex3d(xmax, ymax, zmax);
		  glVertex3d(xmax, ymax, zmin);

		  glVertex3d(xmin, ymax, zmax);
		  glVertex3d(xmin, ymax, zmin);

		  glVertex3d(xmax, ymin, zmax);
		  glVertex3d(xmax, ymin, zmin);
	   glEnd();
	   }

 //--------------------------------------

	   else if(Point_Clouds_Import->RadioButton2->Checked) //Rendu
	   {
		 glEnable(GL_DEPTH_TEST);
		 Rendering->reglage_eclairage();

	   glBegin(GL_POLYGON);
		  glNormal3d(0,0,1);
		  glVertex3d(xmin, ymin, zmax);
		  glVertex3d(xmin, ymax, zmax);
		  glVertex3d(xmax, ymax, zmax);
		  glVertex3d(xmax, ymin, zmax);
	   glEnd();

	   glBegin(GL_POLYGON);
		  glNormal3d(0,0,-1);
		  glVertex3d(xmin, ymin, zmin);
		  glVertex3d(xmin, ymax, zmin);
		  glVertex3d(xmax, ymax, zmin);
		  glVertex3d(xmax, ymin, zmin);
	   glEnd();

	   glBegin(GL_POLYGON);
		  glNormal3d(1,0,0);
		  glVertex3d(xmax, ymax,zmax);
		  glVertex3d(xmax, ymin, zmax);
		  glVertex3d(xmax, ymin, zmin);
		  glVertex3d(xmax, ymax, zmin);
	   glEnd();

		 glBegin(GL_POLYGON);
		  glNormal3d(-1,0,0);
		  glVertex3d(xmin, ymax,zmax);
		  glVertex3d(xmin, ymin, zmax);
		  glVertex3d(xmin, ymin, zmin);
		  glVertex3d(xmin, ymax, zmin);
	   glEnd();

		 glBegin(GL_POLYGON);
		  glNormal3d(0,-1,0);
		  glVertex3d(xmin, ymin,zmax);
		  glVertex3d(xmin, ymin, zmin);
		  glVertex3d(xmax, ymin, zmin);
		  glVertex3d(xmax, ymin, zmax);
	   glEnd();

		glBegin(GL_POLYGON);
		  glNormal3d(0,1,0);
		  glVertex3d(xmin, ymax,zmax);
		  glVertex3d(xmin, ymax, zmin);
		  glVertex3d(xmax, ymax, zmin);
		  glVertex3d(xmax, ymax, zmax);
	   glEnd();

		  glDisable(GL_DEPTH_TEST);
		  glDisable(GL_LIGHTING);
	   }
} //fonction
//-------------------------------------------------------------------------------
	void liste_point_BEY::dessiner_brut_min()
	{

	 glLineWidth((float)Point_Clouds_Import->ComboBox3->Text.ToDouble());

	   glColor3d(1,0,0);
	   glBegin(GL_LINE_LOOP);
	  glVertex3d(xmin, ymin, zmax);
		  glVertex3d(xmin, ymax, zmax);

		  glVertex3d(xmax, ymax, zmax);
		  glVertex3d(xmax, ymin, zmax);

	   glEnd();


	   glBegin(GL_LINE_LOOP);
	  glVertex3d(xmin, ymin, zmin);
		  glVertex3d(xmin, ymax, zmin);

		  glVertex3d(xmax, ymax, zmin);
		  glVertex3d(xmax, ymin, zmin);

	   glEnd();

	   glBegin(GL_LINES);
	  glVertex3d(xmin, ymin, zmax);
		  glVertex3d(xmin, ymin, zmin);

		  glVertex3d(xmax, ymax, zmax);
		  glVertex3d(xmax, ymax, zmin);

		  glVertex3d(xmin, ymax, zmax);
		  glVertex3d(xmin, ymax, zmin);

		  glVertex3d(xmax, ymin, zmax);
		  glVertex3d(xmax, ymin, zmin);
	   glEnd();

 //---------------les polygones -----------------------

	   if(Point_Clouds_Import->RadioButton2->Checked)
	   {
	   glColor3d(0,1,0);
	   glBegin(GL_POLYGON);
	  glVertex3d(xmin, ymin, zmax);
		  glVertex3d(xmin, ymax, zmax);

		  glVertex3d(xmax, ymax, zmax);
		  glVertex3d(xmax, ymin, zmax);

	   glEnd();


	   glBegin(GL_POLYGON);
	  glVertex3d(xmin, ymin, zmin);
		  glVertex3d(xmin, ymax, zmin);

		  glVertex3d(xmax, ymax, zmin);
		  glVertex3d(xmax, ymin, zmin);

	   glEnd();

	  glBegin(GL_POLYGON);
	  glVertex3d(xmax, ymax,zmax);
		  glVertex3d(xmax, ymin, zmax);

		  glVertex3d(xmax, ymin, zmin);
		  glVertex3d(xmax, ymax, zmin);

	   glEnd();
		 glBegin(GL_POLYGON);
	  glVertex3d(xmin, ymax,zmax);
		  glVertex3d(xmin, ymin, zmax);

		  glVertex3d(xmin, ymin, zmin);
		  glVertex3d(xmin, ymax, zmin);

	   glEnd();

		 glBegin(GL_POLYGON);
	  glVertex3d(xmin, ymin,zmax);
		  glVertex3d(xmin, ymin, zmin);

		  glVertex3d(xmax, ymin, zmin);
		  glVertex3d(xmax, ymin, zmax);

	   glEnd();

		glBegin(GL_POLYGON);

	  glVertex3d(xmin, ymax,zmax);
		  glVertex3d(xmin, ymax, zmin);

		  glVertex3d(xmax, ymax, zmin);
		  glVertex3d(xmax, ymax, zmax);

	   glEnd();

	   }


	} //fonction



//****************************************************************************

void fichier_texte:: verifier_fichier(AnsiString fichier)
{
	  syntaxe=true;
	  char a[50];


//-------------------------------------------------------------

  char *filename = 0;

  filename = fichier.c_str();
  fichier.Length();
  int i1=fichier.Length();

//-----------------------------------------------


   if( !((filename != 0 ) && (i1>4) && (filename[i1-4]=='.')&& (filename[i1-3]=='t') && (filename[i1-2]=='x') && (filename[i1-1]=='t')) )
   {
        ShowMessage("L'extension du fichier sélectionné est incorrecte ...........!!!!!!!!!!!!!!");
        syntaxe=false;
        return ;
   }

ifstream fin(nom_f.c_str());

int compt=0;

while(!fin.eof())
{
fin>>a;
compt++;
}

fin.close();

if(compt % 3!=0)
{
  ShowMessage(" Manque de coordonnées dans le fichier sélectionné ...........!!!!");
  syntaxe=false;
  return;
}
else
{
if (fin.eof()){nbre_pt=compt/3; }
}
} //fonction
//--------------------------------------------------------------------------------

liste_point_BEY & liste_point_BEY::ajouter_element(noeud_point_nuage_BEY * p)
{
  if(debut==NULL)
  {
   debut=p;
   debut->setsuiv(NULL);
  }
  else
  {
	if(fin==NULL)                   // un seul element
	{
	fin=p;
	fin->setsuiv(NULL);

	debut->setsuiv(p);

	}
	else
	{
	 fin->setsuiv(p);
	 fin=p;
	 fin->setsuiv(NULL);
	}

  }

	 return *this;
} //fonction
//---------------------------------------------------------------------------
//--------------------------------------------------------------------------------

liste_point & liste_point::ajouter_element(noeud_point_nuage * p)
	{
  if(debut==NULL)
  {
   debut=p;
   debut->setsuiv(NULL);
   debut->setprec(NULL);
  }
  else
  {
	if(fin==NULL)                   // un seul element
	{
	fin=p;
	fin->setsuiv(NULL);

	fin->setprec(debut);
	debut->setsuiv(p);

	}
	else
	{
	 p->setprec(fin);
	 fin->setsuiv(p);
	 fin=p;
	 fin->setsuiv(NULL);


	}

  }

	 return *this;
	} //fonction
//---------------------------------------------------------------------------
void TPoint_Clouds_Import::dessiner_point_cible()
{
	 glPointSize(1);
	 glColor3d(0,0,1);

       glBegin(GL_POINTS);
         glVertex3d(point_cible.getx(),point_cible.gety(),point_cible.getz());
       glEnd();
}
//---------------------------------------------------------------------------



void __fastcall TPoint_Clouds_Import::FormShow(TObject *Sender)
{
continuer=false;
lecture_nuage_pts=false;

Left=Screen->Width-Width;
Top=(Screen->Height-Height)/2;;


Top=10;
Left=Screen->Width-Width;


save=true;
//Point_Clouds_Import->Caption="Lecture du nuage de points";

GroupBox5->Visible=false;
GroupBox6->Visible=false;
GroupBox8->Visible=false;

Button3->Visible=false;

fichier_enregistre=false;
points_generes=false;
}
//---------------------------------------------------------------------------

void __fastcall TPoint_Clouds_Import::FormClose(TObject *Sender, TCloseAction &Action)
{
if(continuer==false)Visualization->Close();
}//fonction


//---------------------------------------------------------------------------

void __fastcall TPoint_Clouds_Import::CheckBox2Click(TObject *Sender)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

void __fastcall TPoint_Clouds_Import::Button3Click(TObject *Sender)
{
continuer=true;
CheckBox4->Checked=false;
CheckBox5->Checked=false;
Visualization->DrawObjects();

Adaptive_Triangulation->Show();
Point_Clouds_Import->Close();
}//fonction
//---------------------------------------------------------------------------

void TPoint_Clouds_Import::filtrer_points_double()
{
	   noeud_point_nuage *temp;
	   noeud_point_nuage *temp1;
	   noeud_point_nuage *p,*p1,*p2;
	   int nbre_pts=Point_Clouds_Import->nuage_pts->getnbre_pt();
	   temp=Point_Clouds_Import->nuage_pts->getdebut();


			while (temp!=NULL)
			 {
			   temp1=temp->getsuiv();
					   while (temp1!=NULL)
					   {
						  if(fabs(temp->getpoint()->getx()-temp1->getpoint()->getx())<1e-6
						  && fabs(temp->getpoint()->gety()-temp1->getpoint()->gety())<1e-6
                          && fabs(temp->getpoint()->getz()-temp1->getpoint()->getz())<1e-6)
                          {
						   p2=temp1->getsuiv();
						   p=temp1->getprec();


						  if(temp1!=Point_Clouds_Import->nuage_pts->getfin())
						   {
						   p->setsuiv(p2);
						   p2->setprec(p);


						   temp1=p;
						   temp1=temp1->getsuiv();
						   nbre_pts--;
						   Point_Clouds_Import->nuage_pts->setnbre_pt(nbre_pts);
						   }
						   else
						   {
						   p->setsuiv(NULL);

						   Point_Clouds_Import->nuage_pts->setfin(p);

						   nbre_pts--;
						   Point_Clouds_Import->nuage_pts->setnbre_pt(nbre_pts);
						   break;
						   }

					   }
						  else
						  temp1=temp1->getsuiv();
					   }
				  temp=temp->getsuiv();
			 }
//-------------------------------------------------------------------------------------

}

//-------------------------------------------------------------------------------------
void triangle_initial:: calcul_normal_triangle()
{
double Mod;

double nx1,nx2,nx3;
double ny1,ny2,ny3;
double nz1,nz2,nz3;

			  nx1=p1->getx_pt();
			  ny1=p1->gety_pt();
			  nz1=z_pt1;

			  nx2=p2->getx_pt();
			  ny2=p2->gety_pt();
			  nz2=z_pt2;

			  nx3=p3->getx_pt();
			  ny3=p3->gety_pt();
			  nz3=z_pt3;

   double   x1=nx2-nx1;
   double   y1=ny2-ny1;
   double   z1=nz2-nz1;

   double   x2=nx3-nx1;
   double   y2=ny3-ny1;
   double   z2=nz3-nz1;

	 nx=y1*z2-z1*y2;
	 ny=z1*x2-x1*z2;
	 nz=x1*y2-y1*x2;

 Mod=sqrt(nx*nx+ny*ny+nz*nz);
 aire_tr=Mod/2;

   nx=nx/Mod;
   ny=ny/Mod;
   nz=nz/Mod;

   if(nz<0){nx=-nx; ny=-ny; nz=-nz;}


}//fonction

//-----------------------------------------------------------------------------
void triangle_initial:: calcul_normal_triangle_BEY()
{
double nx1,nx2,nx3;
double ny1,ny2,ny3;
double nz1,nz2,nz3;

			  nx1=s1->getx_pt();
			  ny1=s1->gety_pt();
			  nz1=z_pt1;

			  nx2=s2->getx_pt();
			  ny2=s2->gety_pt();
			  nz2=z_pt2;

			  nx3=s3->getx_pt();
			  ny3=s3->gety_pt();
			  nz3=z_pt3;

   double   x1=nx2-nx1;
   double   y1=ny2-ny1;
   double   z1=nz2-nz1;

   double   x2=nx3-nx1;
   double   y2=ny3-ny1;
   double   z2=nz3-nz1;

	 nx=y1*z2-z1*y2;
	 ny=z1*x2-x1*z2;
	 nz=x1*y2-y1*x2;

	 if(nz<0){nx=-nx; ny=-ny; nz=-nz;}

	 double module=sqrt(nx*nx+ny*ny+nz*nz);

	 nx=nx/module;
	 ny=ny/module;
	 nz=nz/module;


 aire_tr=module/2;

}//fonction

//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
void triangle_initial_BEY:: calcul_normal_triangle()
{
 //----------------------------------------------------
double Mod;

double nx1,nx2,nx3;
double ny1,ny2,ny3;
double nz1,nz2,nz3;

			  nx1=s1->getx_pt();
			  ny1=s1->gety_pt();

			  nz1=z_pt1;

			  nx2=s2->getx_pt();
			  ny2=s2->gety_pt();

			  nz2=z_pt2;

			  nx3=s3->getx_pt();
			  ny3=s3->gety_pt();
			  nz3=z_pt3;

   double   x1=nx2-nx1;
   double   y1=ny2-ny1;
   double   z1=nz2-nz1;

   double   x2=nx3-nx1;
   double   y2=ny3-ny1;
   double   z2=nz3-nz1;

	 nx=y1*z2-z1*y2;
	 ny=z1*x2-x1*z2;
	 nz=x1*y2-y1*x2;

 Mod=sqrt(nx*nx+ny*ny+nz*nz);
 aire_tr=Mod/2;

   nx=nx/Mod;
   ny=ny/Mod;
   nz=nz/Mod;

   if(nz<0){nx=-nx; ny=-ny; nz=-nz;}


}//fonction

//-----------------------------------------------------------------------------
void triangle_initial_BEY:: calcul_normal_triangle_BEY()
{
double nx1,nx2,nx3;
double ny1,ny2,ny3;
double nz1,nz2,nz3;

			  nx1=s1->getx_pt();
			  ny1=s1->gety_pt();
			  nz1=z_pt1;

			  nx2=s2->getx_pt();
			  ny2=s2->gety_pt();
			  nz2=z_pt2;

			  nx3=s3->getx_pt();
			  ny3=s3->gety_pt();
			  nz3=z_pt3;

   double   x1=nx2-nx1;
   double   y1=ny2-ny1;
   double   z1=nz2-nz1;

   double   x2=nx3-nx1;
   double   y2=ny3-ny1;
   double   z2=nz3-nz1;

	 nx=y1*z2-z1*y2;
	 ny=z1*x2-x1*z2;
	 nz=x1*y2-y1*x2;

	 if(nz<0){nx=-nx; ny=-ny; nz=-nz;}

	 double module=sqrt(nx*nx+ny*ny+nz*nz);

	 nx=nx/module;
	 ny=ny/module;
	 nz=nz/module;


 aire_tr=module/2;

}//fonction

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void TPoint_Clouds_Import::dessiner_triangles_voisins()
	   {

				if(cible==NULL)return;

						glColor3d(1,0,0);
						glBegin(GL_TRIANGLES);
							glVertex3d(cible->getp1()->getx_pt(),cible->getp1()->gety_pt(),cible->getp1()->getz());
							glVertex3d(cible->getp2()->getx_pt(),cible->getp2()->gety_pt(),cible->getp2()->getz());
								glVertex3d(cible->getp3()->getx_pt(),cible->getp3()->gety_pt(),cible->getp3()->getz());
						 glEnd();


                       if(cible->getv1()!=NULL)
                        {
                        glColor3d(1, 1, 0);
                        glBegin(GL_TRIANGLES);
                                glVertex3d(cible->getv1()->getp1()->getx_pt(),cible->getv1()->getp1()->gety_pt(),cible->getv1()->getp1()->getz());
                                glVertex3d(cible->getv1()->getp2()->getx_pt(),cible->getv1()->getp2()->gety_pt(),cible->getv1()->getp2()->getz());
                                glVertex3d(cible->getv1()->getp3()->getx_pt(),cible->getv1()->getp3()->gety_pt(),cible->getv1()->getp3()->getz());
                         glEnd();

                        }

                       if(cible->getv2()!=NULL)
                        {
                        glColor3d(1, 0.5, 0);
                        glBegin(GL_TRIANGLES);
                                glVertex3d(cible->getv2()->getp1()->getx_pt(),cible->getv2()->getp1()->gety_pt(),cible->getv2()->getp1()->getz());
                                glVertex3d(cible->getv2()->getp2()->getx_pt(),cible->getv2()->getp2()->gety_pt(),cible->getv2()->getp2()->getz());
                                glVertex3d(cible->getv2()->getp3()->getx_pt(),cible->getv2()->getp3()->gety_pt(),cible->getv2()->getp3()->getz());
                         glEnd();
                         }

                        if(cible->getv3()!=NULL)
                        {
                        glColor3d(1, 0, 1);
                        glBegin(GL_TRIANGLES);
                                glVertex3d(cible->getv3()->getp1()->getx_pt(),cible->getv3()->getp1()->gety_pt(),cible->getv3()->getp1()->getz());
                                glVertex3d(cible->getv3()->getp2()->getx_pt(),cible->getv3()->getp2()->gety_pt(),cible->getv3()->getp2()->getz());
                                glVertex3d(cible->getv3()->getp3()->getx_pt(),cible->getv3()->getp3()->gety_pt(),cible->getv3()->getp3()->getz());
                                glEnd();
                        }

}//FONCTION
//-----------------------------------------------------------------------------


void __fastcall TPoint_Clouds_Import::Button5Click(TObject *Sender)
{

if (Edit13->Text=="" || Edit13->Text=="-")
  {
  ShowMessage(" Donner la coordonnée Z");
  return;
  }

NUAGE_PTS_BEY.inverser_nuage_points();
}
//---------------------------------------------------------------------------
ListTriangle_BEY & ListTriangle_BEY::ajouter_Triangle(triangle_initial  *T1)
 {
double x1=T1->gets1()->getx_pt();
double y1=T1->gets1()->gety_pt();

double x2=T1->gets2()->getx_pt();
double y2=T1->gets2()->gety_pt();

double x3=T1->gets3()->getx_pt();
double y3=T1->gets3()->gety_pt();

double produit=(x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);
if(fabs(produit)<=1e-6) return *this;
//------------------------------------------------------------------


	  if(tete==NULL){
					   tete=T1;
					   fin=NULL;
					   tete->setsuiv(fin);
					   nbre_triangles++;
					}

		else {

				if(fin==NULL){
							   fin=T1;
							   fin->setsuiv(NULL);
							   fin->setprec(tete);
							   tete->setsuiv(fin);
							   nbre_triangles++;
							 }
				else {
					   T1->setprec(fin);
					   fin->setsuiv(T1);
					   fin=T1;
					   fin->setsuiv(NULL);
					   nbre_triangles++;
					 }

			  }

	  T1->setnum_triangle(nbre_triangles);

	 return *this;
   }
//------------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::ajouter_Triangle(triangle_initial_BEY  *T1)
{
	  if(tete==NULL){
					   tete=T1;
					   fin=NULL;
					   tete->setsuiv(fin);
					   nbre_triangles++;
					}

		else {

				if(fin==NULL){
							   fin=T1;
							   fin->setsuiv(NULL);
							   fin->setprec(tete);
							   tete->setsuiv(fin);
							   nbre_triangles++;
							 }
				else {
					   T1->setprec(fin);
					   fin->setsuiv(T1);
					   fin=T1;
					   fin->setsuiv(NULL);
					   nbre_triangles++;
					 }

			  }

	  T1->setnum_triangle(nbre_triangles);

	 return *this;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::supprimer_Triangle_debut(triangle_initial_BEY  *T1)
{

if(nbre_triangles==0)return *this;

triangle_initial_BEY *a_effacer = tete;

	   tete = tete->getsuiv();
	   tete->setprec(NULL);
	   delete a_effacer;

	   nbre_triangles--;

	   if (nbre_triangles == 0)
	   {
	   fin = NULL;
	   tete->setsuiv(fin);
	   }
return *this;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::supprimer_Triangle_fin(triangle_initial_BEY  *T1)
{
if(nbre_triangles==0)return *this;

		if(nbre_triangles == 1)
		{
		  delete tete;
		  fin = tete = NULL;
		}
		else
		{
		  triangle_initial_BEY *fin_tmp=fin->getprec();
		  delete fin;
		  fin=fin_tmp;
		  fin->setsuiv(NULL);
		}
		nbre_triangles--;
return *this;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::supprimer_Triangle_milieu(triangle_initial_BEY  *T1)
{
if(T1==tete)
{
supprimer_Triangle_debut(T1);
}
else if (T1==fin)
{
supprimer_Triangle_fin(T1);
}
else
{
	triangle_initial_BEY  *tmp=tete;
	for(int i=1; i<nbre_triangles; i++)
	{
	if(T1!=tmp)tmp=tmp->getsuiv();
	else break;
	}

	T1->getprec()->setsuiv(T1->getsuiv());
	T1->getsuiv()->setprec(T1->getprec());

	delete T1;
	nbre_triangles--;
}


return *this;

}
//------------------------------------------------------------------------------

//---------------------------------------------------------------------------
void triangle_initial:: intersection_deux_segment_BEY(int num_point, double x1,double y1,double x2,double y2, double x3,double y3,double x4,double y4,double & X,double & Y, double & alpha,double & beta)
{

 alpha=-1;
 beta=-1;
 double  deter_glob=0;

 double d_x,d_y,X1,Y1;

 deter_glob=(x2-x1)*(y3-y4)-(y2-y1)*(x3-x4);

 d_x=(x3-x1)*(y3-y4)-(y3-y1)*(x3-x4);
 d_y=(x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);

 if(fabs(deter_glob)>1e-10)
 {
 alpha=d_x/deter_glob;
 beta=d_y/deter_glob;

 X=alpha*(x2-x1)+x1;
 Y=alpha*(y2-y1)+y1;

 if(beta>1)beta=1;
 X1=beta*(x4-x3)+x3;
 Y1=beta*(y4-y3)+y3;

 X=X1;
 Y=Y1;

	if(num_point==1){x1_inter=X; y1_inter=Y;}
	else if(num_point==2){x2_inter=X; y2_inter=Y;}
 }

}//foction
//----------------------------------------------------------------------------

//------------------------------------------------------------------------------
void triangle_initial:: calculer_pts_intersection_segments_triangles_cercle(int num_point, double xc, double yc, double R, double x1, double y1, double x2, double y2, double &xinter, double &yinter)
{
double A=pow(x2-x1,2)+pow(y2-y1,2);
double B=2*((x1-xc)*(x2-x1)+(y1-yc)*(y2-y1));
double C=pow(x1-xc,2)+pow(y1-yc,2)-R*R;

double determinant=B*B-4*A*C;

double t1=(-B-sqrt(determinant))/(2*A);

double t2=(-B+sqrt(determinant))/(2*A);

if(t1>=1)t1=1;

if(t1>=0)
{
xinter=x1+t1*(x2-x1);
yinter=y1+t1*(y2-y1);
}

if(t2>=1)t2=1;

if(t2>=0)
{
xinter=x1+t2*(x2-x1);
yinter=y1+t2*(y2-y1);
}

if(fabs(pow(xinter-xc,2)+pow(yinter-yc,2)-R*R)>1e-6)
{
int a=10;
a++;
}

if(num_point==1){x1_inter=xinter; y1_inter=yinter;}
else if(num_point==2){x2_inter=xinter; y2_inter=yinter;}

}
//------------------------------------------------------------------------------
void triangle_initial_BEY::calculer_zmax_zmin_pts_triangle()
{
	nbre_pts_triangle=liste_pts_triangle_BEY.size();

	zmax_pts_triangle=liste_pts_triangle_BEY[0].p->getz();
	zmin_pts_triangle=liste_pts_triangle_BEY[0].p->getz();

	for(int i=1; i<nbre_pts_triangle; i++)
	{
		zmax_pts_triangle=max(zmax_pts_triangle, liste_pts_triangle_BEY[i].p->getz());
		zmin_pts_triangle=min(zmin_pts_triangle, liste_pts_triangle_BEY[i].p->getz());
	}

	zmax_t=max(z_pt1, max(z_pt2,z_pt3));
	zmin_t=min(z_pt1, min(z_pt2,z_pt3));

delta_Z_triangle=zmax_t-zmin_t;
delta_Z_pts_triangle=zmax_pts_triangle-zmin_pts_triangle;

nbre_pts_triangle=liste_pts_triangle_BEY.size();
}
//------------------------------------------------------------------------------
void triangle_initial_BEY::calculer_ecart_max_droite()
{
	double determinant;
	double a, b;
	double somme_xi=0;
	double somme_xi_carre=0;
	double somme_yi=0;
	double somme_xiyi=0;

    nbre_pts_triangle=liste_pts_triangle_BEY.size();
	for(int i=0; i<nbre_pts_triangle; i++)
	{
		somme_yi=somme_yi+liste_pts_triangle_BEY[i].p->gety();
		somme_xi_carre=somme_xi_carre+liste_pts_triangle_BEY[i].p->getx()*liste_pts_triangle_BEY[i].p->getx();
		somme_xi=somme_xi+liste_pts_triangle_BEY[i].p->getx();
		somme_xiyi=somme_xiyi+liste_pts_triangle_BEY[i].p->getx()*liste_pts_triangle_BEY[i].p->gety();
	}

   determinant=nbre_pts_triangle*somme_xi_carre - somme_xi*somme_xi;

   if(fabs(determinant)<=1e-10)
   {
	ecart_max_droite=0;
	return;
   }

   a=(nbre_pts_triangle*somme_xiyi - somme_xi*somme_yi)/determinant;

   b=(somme_yi*somme_xi_carre -somme_xi*somme_xiyi)/determinant;

   double denominateur=1./sqrt(a*a+1);

   double ecart_pt;
   ecart_max_droite=-1;

	for(int i=1; i<nbre_pts_triangle; i++)
	{
	ecart_pt=denominateur*fabs(a*liste_pts_triangle_BEY[i].p->getx() -liste_pts_triangle_BEY[i].p->gety() +b);
	ecart_max_droite=max(ecart_max_droite, ecart_pt);
	}
}

//------------------------------------------------------------------------------

void triangle_initial_BEY::calculer_pts_intersection_segments_triangles_cercle(int num_point, double xc, double yc, double R, double x1, double y1, double x2, double y2, double &xinter, double &yinter)
{
double A=pow(x2-x1,2)+pow(y2-y1,2);
double B=2*((x1-xc)*(x2-x1)+(y1-yc)*(y2-y1));
double C=pow(x1-xc,2)+pow(y1-yc,2)-R*R;

double determinant=B*B-4*A*C;

double sqrt_deter=sqrt(determinant);
double inverse_deux_A=1./(2*A);

double t1=(-B-sqrt_deter)*inverse_deux_A;

double t2=(-B+sqrt_deter)*inverse_deux_A;

if(t1>=1)t1=0.5;
if(t2>=1)t2=0.5;


if(t1>=0)
{
xinter=x1+t1*(x2-x1);
yinter=y1+t1*(y2-y1);
}

else if(t2>=0)
{
xinter=x1+t2*(x2-x1);
yinter=y1+t2*(y2-y1);
}

if(num_point==1){x1_inter=xinter; y1_inter=yinter;}
else if(num_point==2){x2_inter=xinter; y2_inter=yinter;}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void triangle_initial:: calculer_pts_intersection_segments_triangles_normale_bissectrices(double xc, double yc, double R, double x1, double y1, double x2, double y2, double &xinter, double &yinter)
{
double A=pow(x2-x1,2)+pow(y2-y1,2);
double B=2*((x1-xc)*(x2-x1)+(y1-yc)*(y2-y1));
double C=pow(x1-xc,2)+pow(y1-yc,2)-R*R;

double determinant=B*B-4*A*C;

double t1=(-B-sqrt(determinant))/(2*A);

double t2=(-B+sqrt(determinant))/(2*A);

if(t1>=1)t1=1;

if(t1>=0)
{
xinter=x1+t1*(x2-x1);
yinter=y1+t1*(y2-y1);
}

if(t2>=1)t2=1;

if(t2>=0)
{
xinter=x1+t2*(x2-x1);
yinter=y1+t2*(y2-y1);
}

if(fabs(pow(xinter-xc,2)+pow(yinter-yc,2)-R*R)>1e-6)
{
int a=10;
a++;
}

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void triangle_initial_BEY:: calculer_pts_intersection_segments_triangles_normale_bissectrices(double xc, double yc, double R, double x1, double y1, double x2, double y2, double &xinter, double &yinter)
{
double A=pow(x2-x1,2)+pow(y2-y1,2);
double B=2*((x1-xc)*(x2-x1)+(y1-yc)*(y2-y1));
double C=pow(x1-xc,2)+pow(y1-yc,2)-R*R;

double determinant=B*B-4*A*C;

double t1=(-B-sqrt(determinant))/(2*A);

double t2=(-B+sqrt(determinant))/(2*A);

if(t1>=1)t1=0.5;

if(t1>=0)
{
xinter=x1+t1*(x2-x1);
yinter=y1+t1*(y2-y1);
}

if(t2>=1)t2=0.5;

if(t2>=0)
{
xinter=x1+t2*(x2-x1);
yinter=y1+t2*(y2-y1);
}

if(fabs(pow(xinter-xc,2)+pow(yinter-yc,2)-R*R)>1e-6)
{
int a=10;
a++;
}

}
//------------------------------------------------------------------------------
void triangle_initial:: determiner_pt_eloingne(pt_plan *s)
{
double dist, dist_max;

double xx1=s->getx_pt();
double yy1=s->gety_pt();

noeud_point_nuage_BEY *t;

	t=liste_pts_triangle->getdebut();

	x_loin=t->getpoint()->getx();
	y_loin=t->getpoint()->gety();
	dist_max=sqrt(pow(xx1-x_loin,2)+ pow(yy1-y_loin,2));

	t=t->getsuiv2();

	while (t)
	{
	double x=t->getpoint()->getx();
	double y=t->getpoint()->gety();

	dist=sqrt(pow(xx1-x,2)+ pow(yy1-y,2));

	if(dist>dist_max){dist_max=dist; x_loin=x; y_loin=y;}

	t=t->getsuiv2();
	}

	rayon_loin = dist_max;

}
//----------------------------------------------------------------------
//------------------------------------------------------------------------------
void triangle_initial:: determiner_pt_proche(pt_plan *s)
{
double dist, dist_min;

double xx1=s->getx_pt();
double yy1=s->gety_pt();

noeud_point_nuage_BEY *t;

    t=liste_pts_triangle->getdebut();

    x_proche=t->getpoint()->getx();
    y_proche=t->getpoint()->gety();
    dist_min=sqrt(pow(xx1-x_proche,2)+ pow(yy1-y_proche,2));

    t=t->getsuiv2();

    while (t)
    {
    double x=t->getpoint()->getx();
    double y=t->getpoint()->gety();

    dist=sqrt(pow(xx1-x,2)+ pow(yy1-y,2));

    if(dist<dist_min){dist_min=dist; x_proche=x; y_proche=y;}

    t=t->getsuiv2();
    }

    rayon_proche = dist_min;

}
//----------------------------------------------------------------------
//------------------------------------------------------------------------------
void triangle_initial_BEY:: determiner_pt_proche(double xx1, double yy1)
{
double dist, dist_min;
double x_proche,y_proche;

	x_proche=liste_pts_triangle_BEY[0].p->x;
	y_proche=liste_pts_triangle_BEY[0].p->y;

	dist_min=(pow(xx1-x_proche,2)+ pow(yy1-y_proche,2));

	for(int i=1; i<nbre_pts_triangle; i++)
	{
	double x=liste_pts_triangle_BEY[i].p->x;
	double y=liste_pts_triangle_BEY[i].p->y;

	dist=(pow(xx1-x,2)+ pow(yy1-y,2));

	if(dist<dist_min){dist_min=dist; x_proche=x; y_proche=y;}
	}

	rayon_proche = sqrt(dist_min);
}
//----------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void liste_point::chercher_pptes_nuage_pointsnew()
{

noeud_point_nuage *t;
 t=debut;

double x1,x2,x3;

xmax=x1=t->getpoint()->getx();
xmin=x1=t->getpoint()->getx();

ymax=x2=t->getpoint()->gety();
ymin=x2=t->getpoint()->gety();

zmax=x3=t->getpoint()->getz();
zmin=x3=t->getpoint()->getz();

t=t->getsuiv_new_n();

while (t)
{
   x1=t->getpoint()->getx();
   x2=t->getpoint()->gety();
   x3=t->getpoint()->getz();

 if (x1>xmax)xmax=x1;
 if (x1<xmin)xmin=x1;

 if (x2>ymax)ymax=x2;
 if (x2<ymin)ymin=x2;

 if (x3>zmax)zmax=x3;
 if (x3<zmin)zmin=x3;

t=t->getsuiv_new_n();

 }

} //fonction

//-------------------------------------------------------------------------------
//-----------------Affecter couleur--------------------------------------------
void triangle_initial::affecter_couleur()
 {
	R = (rand() % 255) /255.;
	B = (rand() % 255) /255.;
	G = (rand() % 255) /255.;
 }
 //------------------------------------------------------------------------------




void __fastcall TPoint_Clouds_Import::Button6Click(TObject *Sender)
{
	 int nbre_pt_total;
	 float xx2,yy2,zz2,xmax,xmin,ymax,ymin,zmax,zmin;

  Point_Clouds_Import->OpenDialog1->FileName="";

if(OpenDialog1->Execute())
{
	 Screen->Cursor= crHourGlass;

	 nbre_pt_total=0;


for(int i=0;i<OpenDialog1->Files->Count;i++)
{

	 AnsiString fichier =  OpenDialog1->Files->Strings[i];
	 entree.setnom_f(fichier);
	 entree.verifier_fichier(fichier);

		 if(entree.getsyntaxe()==false)
		 {
		 ShowMessage("Le fichier contient des erreurs.......!!!!");
		 Screen->Cursor= crDefault;
		 continue;
		 }

	 nbre_pt_total=nbre_pt_total+nbre_pt;

	 ifstream fin(entree.getnom_f().c_str());

	 NUAGE_PTS_BEY.nbre_pts_total=nbre_pt_total;
	 NUAGE_PTS_BEY.creer_tableau();

//----------------------
xmax=-100000000;
xmin=100000000;

ymax=-100000000;
ymin=100000000;

zmax=-100000000;
zmin=100000000;

	   for(int i=0;i<nbre_pt_total;i++)
			 {
			 fin>>xx2;
			 fin>>yy2;
			 fin>>zz2;

				 if (xx2>xmax)xmax=xx2;
				 else if (xx2<xmin)xmin=xx2;

				 if (yy2>ymax)ymax=yy2;
				 else if (yy2<ymin)ymin=yy2;

				 if (zz2>zmax)zmax=zz2;
				 else if (zz2<zmin)zmin=zz2;

			 NUAGE_PTS_BEY.affecter_pt(i,xx2,yy2,zz2);
			 }

	   fin.close();

	}
}


  float L=xmax-xmin;
  float l=ymax-ymin;
  float H=zmax-zmin;

  Point_Clouds_Import->Edit1->Text=FormatFloat("0.000",xmax);
  Point_Clouds_Import->Edit4->Text=FormatFloat("0.000",xmin);

  Point_Clouds_Import->Edit2->Text=FormatFloat("0.000",ymax);
  Point_Clouds_Import->Edit5->Text=FormatFloat("0.000",ymin);

  Point_Clouds_Import->Edit3->Text=FormatFloat("0.000",zmax);
  Point_Clouds_Import->Edit6->Text=FormatFloat("0.000",zmin);

  Point_Clouds_Import->Edit7->Text=FormatFloat("0.000",L);
  Point_Clouds_Import->Edit8->Text=FormatFloat("0.000",l);
  Point_Clouds_Import->Edit9->Text=FormatFloat("0.000",H);

  NUAGE_PTS_BEY.xmin=xmin;
  NUAGE_PTS_BEY.xmax=xmax;

  NUAGE_PTS_BEY.ymin=ymin;
  NUAGE_PTS_BEY.ymax=ymax;

  NUAGE_PTS_BEY.zmin=zmin;
  NUAGE_PTS_BEY.zmax=zmax;

  NUAGE_PTS_BEY.L=L;
  NUAGE_PTS_BEY.l=l;
  NUAGE_PTS_BEY.H=H;

  Point_Clouds_Import->Edit1->Text=FormatFloat("0.000",xmax);
  Point_Clouds_Import->Edit4->Text=FormatFloat("0.000",xmin);

  Point_Clouds_Import->Edit2->Text=FormatFloat("0.000",ymax);
  Point_Clouds_Import->Edit5->Text=FormatFloat("0.000",ymin);

  Point_Clouds_Import->Edit3->Text=FormatFloat("0.000",zmax);
  Point_Clouds_Import->Edit6->Text=FormatFloat("0.000",zmin);

  Point_Clouds_Import->Edit7->Text=FormatFloat("0.000",L);
  Point_Clouds_Import->Edit8->Text=FormatFloat("0.000",l);
  Point_Clouds_Import->Edit9->Text=FormatFloat("0.000",H);

			 //Point_Clouds_Import->Caption="Lecture du nuage de points (points générés)";

	   GroupBox5->Visible=true;
	   GroupBox6->Visible=true;
	   Button3->Visible=true;
	   Edit10->Text=NUAGE_PTS_BEY.nbre_pts_total;

	   Visualization->Calculer_Limites_Globales_Scene(xmin, ymin, zmin, xmax, ymax, zmax);

Screen->Cursor= crDefault;

GroupBox8->Visible=true;

Visualization->Vue3D1Click(Sender);
Visualization->ZoomAll1Click(Sender);

CheckBox4->Checked=true;
CheckBox5->Checked=true;
Visualization->DrawObjects();

}
//---------------------------------------------------------------------------
void triangle_initial::dessiner_pts_triangle()
{
double x1,y1,z1;
glColor3d(R,G,B);

	for(int i=0; i<nbre_pts_triangle; i++)
	{
		x1=liste_pts_triangle_BEY[i].p->getx();
		y1=liste_pts_triangle_BEY[i].p->gety();
		z1=liste_pts_triangle_BEY[i].p->getz();

		   glBegin(GL_POINTS);
			   glVertex3d(x1,y1,z1);
		   glEnd();

	}
}
//---------------------------------------------------------------------------
void triangle_initial::dessiner_pts_proches_sommets_triangle()
{
	 double x1,y1,z1;
	for(int i=0; i<nbre_pts_triangle; i++)
	{
	if(liste_pts_triangle_BEY[i].indice_pt_proche==0)continue;

	   x1=liste_pts_triangle_BEY[i].p->getx();
	   y1=liste_pts_triangle_BEY[i].p->gety();
	   z1=liste_pts_triangle_BEY[i].p->getz();

	   if(liste_pts_triangle_BEY[i].indice_pt_proche==1)glColor3d(1,0,0);
	   if(liste_pts_triangle_BEY[i].indice_pt_proche==2)glColor3d(0,1,0);
	   if(liste_pts_triangle_BEY[i].indice_pt_proche==3)glColor3d(0,1,1);

	   glBegin(GL_POINTS);
	   glVertex3d(x1,y1,z1);
	   glEnd();
	}
}
//---------------------------------------------------------------------------
void triangle_initial::dessiner_pts_proches_milieux_segments_triangle()
{
	 double x1,y1,z1;
	for(int i=0; i<nbre_pts_triangle; i++)
	{
	if(liste_pts_triangle_BEY[i].indice_pt_proche==0)continue;

	   x1=liste_pts_triangle_BEY[i].p->getx();
	   y1=liste_pts_triangle_BEY[i].p->gety();
	   z1=liste_pts_triangle_BEY[i].p->getz();

	   if(liste_pts_triangle_BEY[i].indice_pt_proche_milieu==1)glColor3d(1,0,0);
	   if(liste_pts_triangle_BEY[i].indice_pt_proche_milieu==2)glColor3d(0,1,0);
	   if(liste_pts_triangle_BEY[i].indice_pt_proche_milieu==3)glColor3d(0,1,1);

	   glBegin(GL_POINTS);
	   glVertex3d(x1,y1,z1);
	   glEnd();
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void triangle_initial_BEY::dessiner_pts_triangle()
{
double x1,y1,z1;
glColor3d(R,G,B);
	for(int i=0; i<nbre_pts_triangle; i++)
	{
		x1=liste_pts_triangle_BEY[i].p->getx();
		y1=liste_pts_triangle_BEY[i].p->gety();
		z1=liste_pts_triangle_BEY[i].p->getz();

		   glBegin(GL_POINTS);
			   glVertex3d(x1,y1,z1);
		   glEnd();

	}
}
//---------------------------------------------------------------------------
void triangle_initial_BEY::dessiner_pts_proches_sommets_triangle()
{
	 double x1,y1,z1;
	for(int i=0; i<nbre_pts_triangle; i++)
	{
	if(liste_pts_triangle_BEY[i].indice_pt_proche==0)continue;

	   x1=liste_pts_triangle_BEY[i].p->getx();
	   y1=liste_pts_triangle_BEY[i].p->gety();
	   z1=liste_pts_triangle_BEY[i].p->getz();

	   if(liste_pts_triangle_BEY[i].indice_pt_proche==1)glColor3d(1,0,0);
	   if(liste_pts_triangle_BEY[i].indice_pt_proche==2)glColor3d(0,1,0);
	   if(liste_pts_triangle_BEY[i].indice_pt_proche==3)glColor3d(0,1,1);

	   glBegin(GL_POINTS);
	   glVertex3d(x1,y1,z1);
	   glEnd();
	}
}
//---------------------------------------------------------------------------
void triangle_initial_BEY::dessiner_pts_proches_milieux_segments_triangle()
{
	 double x1,y1,z1;
	for(int i=0; i<nbre_pts_triangle; i++)
	{
	if(liste_pts_triangle_BEY[i].indice_pt_proche==0)continue;

	   x1=liste_pts_triangle_BEY[i].p->getx();
	   y1=liste_pts_triangle_BEY[i].p->gety();
	   z1=liste_pts_triangle_BEY[i].p->getz();

	   if(liste_pts_triangle_BEY[i].indice_pt_proche_milieu==1)glColor3d(1,0,0);
	   if(liste_pts_triangle_BEY[i].indice_pt_proche_milieu==2)glColor3d(0,1,0);
	   if(liste_pts_triangle_BEY[i].indice_pt_proche_milieu==3)glColor3d(0,1,1);

	   glBegin(GL_POINTS);
	   glVertex3d(x1,y1,z1);
	   glEnd();
	}
}
//---------------------------------------------------------------------------

void ListTriangle_BEY::liberer_memoire()
{
triangle_initial *parcT=tete;

	while (parcT!=NULL)
	{
	   parcT->liberer_memoire();
	   parcT=parcT->getsuiv();
	}
}
//---------------------------------------------------------------------------
void ListTriangle_BEY_BEY::liberer_memoire()
{
triangle_initial_BEY *prev=tete;
	while (tete!=NULL)
	{
	   tete=tete->getsuiv();
	   delete prev;
	   prev=tete;
	}
nbre_triangles=0;
nbre_triangles_non_filtres=0;
}
//------------------------------------------------------------------------------
void __fastcall TPoint_Clouds_Import::CheckBox4Click(TObject *Sender)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

void __fastcall TPoint_Clouds_Import::CheckBox5Click(TObject *Sender)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

