//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Visualization.h"
#include "Point_Clouds_Import.h"
#include "Adaptive_Triangulation.h"
#include "Rendering.h"
#include "Triangulation_Results.h"

#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>

using namespace std;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAdaptive_Triangulation *Adaptive_Triangulation;
double precision_calcul=1e-10;
double pi=acos((double)-1);
double precision_filtrage=1e-6;
double prec_voisin=1e-3;

//---------------------------------------------------------------------------
__fastcall TAdaptive_Triangulation::TAdaptive_Triangulation(TComponent* Owner)
		: TForm(Owner)
{


}
//-----------------------------------------------------------------------------

double TAdaptive_Triangulation::determinant_matrice_3_3(double a11, double a12, double a13,
									   double a21, double a22, double a23,
									   double a31, double a32, double a33)
{
    return a11*a22*a33 + a12*a23*a31 + a13*a21*a32 - a31*a22*a13 - a32*a23*a11 - a33*a21*a12;
}


void __fastcall TAdaptive_Triangulation::Button20Click(TObject *Sender)
{
SaveDialog1->FileName = "";

if (SaveDialog1->Execute())
{
  if(SaveDialog1->FileName.c_str() != 0 )
   {
	Screen->Cursor= crHourGlass;
    save_fichier_STL_BEY();
    Screen->Cursor= crDefault;

   }

}
        
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TAdaptive_Triangulation::save_fichier_STL_BEY()
{
   ofstream  enrg(SaveDialog1->FileName.c_str() /*fichier_as*/);

   enrg.precision(8);

	 enrg<<"solid surfaces"<<endl;

triangle_initial_BEY *parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while (parcT!=NULL)
{

			if(parcT->filtre==true){parcT=parcT->getsuiv();continue;} //Triangle filtré
			if(parcT->filtre==false && parcT->supprime==true){parcT=parcT->getsuiv();continue;}//Triangle supprimé

           double x1=parcT->gets1()->getx_pt();
           double y1=parcT->gets1()->gety_pt();
           double z1=parcT->getz_pt1();

           double x2=parcT->gets2()->getx_pt();
           double y2=parcT->gets2()->gety_pt();
           double z2=parcT->getz_pt2();

           double x3=parcT->gets3()->getx_pt();
           double y3=parcT->gets3()->gety_pt();
           double z3=parcT->getz_pt3();

           double v1x=x2-x1;
           double v1y=y2-y1;
           double v1z=z2-z1;

           double v2x=x3-x1;
           double v2y=y3-y1;
           double v2z=z3-z1;

           double nx=v1y*v2z-v1z*v2y;
           double ny=v1z*v2x-v1x*v2z;
           double nz=v1x*v2y-v1y*v2x;
           
           if(nz<0){nx=-nx; ny=-ny; nz=-nz;}

		   double module=sqrt(nx*nx+ny*ny+nz*nz);

           nx=nx/module;
           ny=ny/module;
           nz=nz/module;

           enrg<<"   facet normal"<<"   "<<nx<<"   "<<ny<<"   "<<nz<<endl;
           enrg<<"      outer loop"<<endl;
           enrg<<"         vertex"<<"   "<<x1<<"   "<<y1<<"   "<<z1<<endl;
           enrg<<"         vertex"<<"   "<<x2<<"   "<<y2<<"   "<<z2<<endl;
		   enrg<<"         vertex"<<"   "<<x3<<"   "<<y3<<"   "<<z3<<endl;
		   enrg<<"      endloop"<<endl;
		   enrg<<"   endfacet"<<endl;

		   parcT=parcT->getsuiv();
	   }

	enrg<<"endsolid";

  enrg.close();
}
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_triangles_voisins_BEY()
	   {

	   if(cible==NULL)return;

	   if(cible->getfiltre()==true)return;

			if(cible==NULL)return;

			if(CheckBox31->Checked) cible->dessiner_pts_triangle(); //Points du triangle

			double magnitude=ComboBox20->Text.ToDouble();
			if(CheckBox56->Checked) //Normale du Triangle
			{
						double xc=(cible->gets1()->getx_pt()+cible->gets2()->getx_pt()+cible->gets3()->getx_pt())/3;
						double yc=(cible->gets1()->gety_pt()+cible->gets2()->gety_pt()+cible->gets3()->gety_pt())/3;
						double zc=(cible->getz_pt1()+cible->getz_pt2()+cible->getz_pt3())/3;

						double xm=xc + magnitude*cible->geta_plan();
						double ym=yc + magnitude*cible->getb_plan();
						double zm=zc + magnitude*(-1);

						glColor3d(0.5,1,0.5);
						glLineWidth(4);
						glBegin(GL_LINES);
							glVertex3d(xc, yc, zc);
							glVertex3d(xm, ym, zm);
						 glEnd();
			}

			if(CheckBox55->Checked) //Point avec Ecart Max du triangle
			{
						glColor3d(1,0,0);
						glPointSize(5);
						glBegin(GL_POINTS);
							glVertex3d(cible->x_pt_ecart_max, cible->y_pt_ecart_max, cible->z_pt_ecart_max);
						 glEnd();
			}


			if(CheckBox19->Checked) //Triangle
			{
						glColor3d(1,1,1);
						glLineWidth(2);
						glBegin(GL_LINE_LOOP);
							glVertex3d(cible->gets1()->getx_pt(),cible->gets1()->gety_pt(),cible->getz_pt1() /*cible->gets1()->getz()*/);
							glVertex3d(cible->gets2()->getx_pt(),cible->gets2()->gety_pt(),cible->getz_pt2() /*cible->gets2()->getz()*/);
							glVertex3d(cible->gets3()->getx_pt(),cible->gets3()->gety_pt(),cible->getz_pt3() /*cible->gets3()->getz()*/);
						 glEnd();
			}

			if(CheckBox20->Checked) //Voisins du triabgle
			{
						glColor3d(1,0,0);
						glBegin(GL_TRIANGLES);
							glVertex3d(cible->gets1()->getx_pt(),cible->gets1()->gety_pt(),cible->getz_pt1() /*cible->gets1()->getz()*/);
	                        glVertex3d(cible->gets2()->getx_pt(),cible->gets2()->gety_pt(),cible->getz_pt2() /*cible->gets2()->getz()*/);
							glVertex3d(cible->gets3()->getx_pt(),cible->gets3()->gety_pt(),cible->getz_pt3() /*cible->gets3()->getz()*/);
                         glEnd();


                       if(cible->getv1()!=NULL)
                        {
                        glColor3d(1, 1, 0);
                        glBegin(GL_TRIANGLES);
                                glVertex3d(cible->getv1()->gets1()->getx_pt(),cible->getv1()->gets1()->gety_pt(),cible->getv1()->getz_pt1() /*cible->getv1()->gets1()->getz()*/);
                                glVertex3d(cible->getv1()->gets2()->getx_pt(),cible->getv1()->gets2()->gety_pt(),cible->getv1()->getz_pt2() /*cible->getv1()->gets2()->getz()*/);
                                glVertex3d(cible->getv1()->gets3()->getx_pt(),cible->getv1()->gets3()->gety_pt(),cible->getv1()->getz_pt3() /*cible->getv1()->gets3()->getz()*/);
						glEnd();
						}

					   if(cible->getv2()!=NULL)
						{
						glColor3d(1, 0.5, 0);
						glBegin(GL_TRIANGLES);
								glVertex3d(cible->getv2()->gets1()->getx_pt(),cible->getv2()->gets1()->gety_pt(),cible->getv2()->getz_pt1() /*cible->getv2()->gets1()->getz()*/);
								glVertex3d(cible->getv2()->gets2()->getx_pt(),cible->getv2()->gets2()->gety_pt(),cible->getv2()->getz_pt2() /*ible->getv2()->gets2()->getz()*/);
								glVertex3d(cible->getv2()->gets3()->getx_pt(),cible->getv2()->gets3()->gety_pt(),cible->getv2()->getz_pt3() /*cible->getv2()->gets3()->getz()*/);
						glEnd();
						}

						if(cible->getv3()!=NULL)
						{
						glColor3d(1, 0, 1);
						glBegin(GL_TRIANGLES);
								glVertex3d(cible->getv3()->gets1()->getx_pt(),cible->getv3()->gets1()->gety_pt(),cible->getv3()->getz_pt1() /*cible->getv3()->gets1()->getz()*/);
								glVertex3d(cible->getv3()->gets2()->getx_pt(),cible->getv3()->gets2()->gety_pt(),cible->getv3()->getz_pt2() /*cible->getv3()->gets2()->getz()*/);
								glVertex3d(cible->getv3()->gets3()->getx_pt(),cible->getv3()->gets3()->gety_pt(),cible->getv3()->getz_pt3() /*cible->getv3()->gets3()->getz()*/);
                        glEnd();
						}
			}

}//FONCTION


//---------------------------------------------------------------------------

void TAdaptive_Triangulation::determiner_limites_triangles_points_triangles()
{

}

//--------Calcul du nombre de triangles, de points et de sommets------------------------------------------
void __fastcall TAdaptive_Triangulation::Button19Click(TObject *Sender)
{
triangle_initial_BEY *parcT;

parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

int nbre_total_triangles, nbre_triangles_non_filtres, nbre_triangles_filtres;
nbre_total_triangles=nbre_triangles_non_filtres=nbre_triangles_filtres=0;

int nbre_pts_total, nbre_pts_non_filtres, nbre_pts_filtres;
nbre_pts_total= nbre_pts_non_filtres= nbre_pts_filtres=0;

//------------------Triangles non filtrés-------------
while (parcT!=NULL)
{
nbre_total_triangles++;
nbre_pts_total=nbre_pts_total+parcT->getnbre_pts_triangle();

if(parcT->getfiltre()==false && parcT->supprime==false)
{
nbre_triangles_non_filtres++;
nbre_pts_non_filtres=nbre_pts_non_filtres+parcT->getnbre_pts_triangle();
}

if(parcT->getfiltre()==true)
{
nbre_triangles_filtres++;
nbre_pts_filtres=nbre_pts_filtres+parcT->getnbre_pts_triangle();
}

parcT=parcT->getsuiv();
}

parcT=Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->gettete();

//-------------------------------
while (parcT!=NULL)
{
nbre_total_triangles++;
nbre_pts_total=nbre_pts_total+parcT->getnbre_pts_triangle();

if(parcT->getfiltre()==false && parcT->supprime==false)
{
nbre_triangles_non_filtres++;
nbre_pts_non_filtres=nbre_pts_non_filtres+parcT->getnbre_pts_triangle();
}

if(parcT->getfiltre()==true)
{
nbre_triangles_filtres++;
nbre_pts_filtres=nbre_pts_filtres+parcT->getnbre_pts_triangle();
}

parcT=parcT->getsuiv();
}

Triangulation_Results->Edit9->Text=nbre_total_triangles;
Triangulation_Results->Edit1->Text=nbre_triangles_non_filtres;
Triangulation_Results->Edit2->Text=nbre_triangles_filtres;

Triangulation_Results->Edit3->Text=nbre_pts_total;
Triangulation_Results->Edit4->Text=nbre_pts_non_filtres;
Triangulation_Results->Edit5->Text=nbre_pts_filtres;

Triangulation_Results->Edit6->Text=Point_Clouds_Import->nbre_sommets_projetes;
//-----------------------------------------------

Triangulation_Results->Show();
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::Button18Click(TObject *Sender)
{
if(Edit19->Text=="") //Aire_min_triangle
{
ShowMessage("Veuillez introduire l'aire minimum du triangle à ne pas subdiviser.........!!!!!!!!!");
return;
}

if(Edit19->Text.ToDouble()==0)
{
ShowMessage("Veuillez introduire une aire non nulle.........!!!!!!!!!");
return;
}

if(Edit11->Text=="") //Rapport
{
ShowMessage("Veuillez introduire le rapport exigé.........!!!!!!!!!");
return;
}

if(Edit11->Text.ToDouble()==0)
{
ShowMessage("Veuillez introduire un rapport non nul.........!!!!!!!!!");
return;
}


if(Edit32->Text=="") //Précision exigée
{
ShowMessage("Veuillez introduire la précision d'approximation exigée.........!!!!!!!!!");
return;
}

if(Edit32->Text.ToDouble()==0)
{
ShowMessage("Veuillez introduire une précision d'approximation non nulle.........!!!!!!!!!");
return;
}

Edit39->Text="";
Edit40->Text="";
Edit41->Text="";
Edit42->Text="";

if(approximation_effectuee==true && Edit32->Text.ToDouble()>=Edit34->Text.ToDouble())
{
Edit39->Text=0;
Edit40->Text=0;
Edit41->Text=0;
Edit42->Text=0;

Triangulation_Results->Show();
Visualization->DrawObjects();

return;
}

if(approximation_effectuee==false && Edit32->Text.ToDouble()>=Edit34->Text.ToDouble())
{
Edit39->Text=0;
Edit40->Text=0;
Edit41->Text=0;
Edit42->Text=0;

Triangulation_Results->Show();
Visualization->DrawObjects();

return;
}

//-------------------------
triangulation_initiale=false;  //Triangulation adaptative

	  px_s=Point_Clouds_Import->NUAGE_PTS_BEY.L/Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles; //le pas suivant X(colonnes)
	  py_s=Point_Clouds_Import->NUAGE_PTS_BEY.l/Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles; //le pas suivant y (lignes)

	  xmin=Point_Clouds_Import->NUAGE_PTS_BEY.xmin;
	  xmax=Point_Clouds_Import->NUAGE_PTS_BEY.xmax;

	  ymin=Point_Clouds_Import->NUAGE_PTS_BEY.ymin;
	  ymax=Point_Clouds_Import->NUAGE_PTS_BEY.ymax;

double start, end;

processing_time_partiel=0;
start=clock();

aire_min_triangle=Adaptive_Triangulation->Edit19->Text.ToDouble() ;
rapport=Adaptive_Triangulation->Edit11->Text.ToDouble()/100.;
precision_approximation_impose=Edit32->Text.ToDouble(); //précision exigée

double ecart_max;

	while(true)
	{
	Screen->Cursor= crHourGlass;
	Point_Clouds_Import->liste_triangle_adaptation_BEY->subdivision_adaptative_triangles();
	Screen->Cursor= crDefault;

	Affectation_Numeros_Sommets_Calcul_Zmax_Zmin_Zmoy_Sommets();

	Type_Z_Coordonnee="Z_MAX";  //Choisir Zmax
	Mise_A_Jour_Sommets_Triangles_Calcul_Ecarts_Max_Triangles_Erreurs_Max_Min();
	ecart_max=Adaptive_Triangulation->dist_max;   //Ecart max pour Zmax
	if(ecart_max<=precision_approximation_impose)break;

	Type_Z_Coordonnee="Z_MIN"; //Choisir Zmin
	Mise_A_Jour_Sommets_Triangles_Calcul_Ecarts_Max_Triangles_Erreurs_Max_Min();
	ecart_max=Adaptive_Triangulation->dist_max; //Ecart max pour Zmin
	if(ecart_max<=precision_approximation_impose)break;

	Type_Z_Coordonnee="Z_MOY"; //Choisir Zmoy
	Mise_A_Jour_Sommets_Triangles_Calcul_Ecarts_Max_Triangles_Erreurs_Max_Min();
	ecart_max=Adaptive_Triangulation->dist_max; //Ecart max pour Zmoy
	if(ecart_max<=precision_approximation_impose)break;
	}

   Adaptive_Triangulation->Edit34->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_max);
   Adaptive_Triangulation->Edit33->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_min);

end=clock();

double time=end-start; //ms
processing_time_partiel=time;

double time_s=time/1000;
double time_m=time_s/60;

double temps_m=time_m; //temps de calcul total en minutes

int temps_calcul_j=(int)(temps_m/(24*60));
Edit39->Text=temps_calcul_j;  //nbre de jours

int temps_calcul_h=(int)((temps_m-temps_calcul_j*1440)/60);
Edit40->Text=temps_calcul_h;   //nbre d'heures

double temps_reste=temps_m-(temps_calcul_h*60+temps_calcul_j*1440);
int temps_calcul_m=(int)temps_reste;

Edit41->Text=temps_calcul_m;  //nbre de minutes

double temps_calcul_s=(temps_reste-temps_calcul_m)*60;

Edit42->Text=FormatFloat("0.00",temps_calcul_s);  //nbre de secondes

//-------------------------------------------------------------
		CheckBox25->Enabled=false;
		CheckBox26->Enabled=false;

triangle_initial_BEY *parcT6=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

Adaptive_Triangulation->ComboBox27->Clear();
int num=0;

while (parcT6!=NULL)
{
	if(parcT6->getfiltre()==true){CheckBox25->Enabled=true;CheckBox26->Enabled=true;}

	if(parcT6->getfiltre()==true || parcT6->supprime==true){parcT6->setnum_triangle(-1);parcT6=parcT6->getsuiv();continue;}
	num++;
	parcT6->setnum_triangle(num);

	if(parcT6->getfiltre()==false && parcT6->supprime==false)
	{
	Adaptive_Triangulation->ComboBox27->Items->Add(parcT6->getnum_triangle()); //--Combobox des voisins

	parcT6->calculer_zmax_zmin_pts_triangle();  //--Calcul des limites Zmin et Zmax des pts du triangle
	parcT6->calculer_ecart_max_droite();        //--Calcul des ecarts max

	parcT6->settrois_sommets_non_nuls(true);
	if(parcT6->getdensite_p1()==0 || parcT6->getdensite_p2()==0 || parcT6->getdensite_p3()==0)
		parcT6->settrois_sommets_non_nuls(false);
	}
parcT6=parcT6->getsuiv();
}
Adaptive_Triangulation->ComboBox27->ItemIndex=0;

//------------------------------------------------------------------------------

Button19Click(Sender);  //calcul du nombre de triangles, de points et de sommets

Visualization->DrawObjects();

approximation_effectuee=true;

Point_Clouds_Import->liste_triangle_adaptation_BEY->determiner_parametres_filtration_triangles();

int frequence=3000;
int duree=1000;
Beep(frequence,duree);

}
//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
void __fastcall TAdaptive_Triangulation::Button17Click(TObject *Sender)
{
Screen->Cursor= crDefault;

triangle_initial_BEY *parcT;
parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while (parcT!=NULL)
{
if(parcT->getfiltre()==true){parcT=parcT->getsuiv();continue;}

if(Type_Z_Coordonnee=="Z_MAX")
{
parcT->setz_pt1(Point_Clouds_Import->sommets_triangles[parcT->gets1()->getnumero_pt()].getz_pt_max());
parcT->setz_pt2(Point_Clouds_Import->sommets_triangles[parcT->gets2()->getnumero_pt()].getz_pt_max());
parcT->setz_pt3(Point_Clouds_Import->sommets_triangles[parcT->gets3()->getnumero_pt()].getz_pt_max());
}

else if(Type_Z_Coordonnee=="Z_MIN")
{
parcT->setz_pt1(Point_Clouds_Import->sommets_triangles[parcT->gets1()->getnumero_pt()].getz_pt_min());
parcT->setz_pt2(Point_Clouds_Import->sommets_triangles[parcT->gets2()->getnumero_pt()].getz_pt_min());
parcT->setz_pt3(Point_Clouds_Import->sommets_triangles[parcT->gets3()->getnumero_pt()].getz_pt_min());
}

else if(Type_Z_Coordonnee=="Z_MOY")
{
parcT->setz_pt1(Point_Clouds_Import->sommets_triangles[parcT->gets1()->getnumero_pt()].getz_pt_moy());
parcT->setz_pt2(Point_Clouds_Import->sommets_triangles[parcT->gets2()->getnumero_pt()].getz_pt_moy());
parcT->setz_pt3(Point_Clouds_Import->sommets_triangles[parcT->gets3()->getnumero_pt()].getz_pt_moy());
}

		   parcT->calculer_nouveaux_parametres_triangle();
//------------------------------------------------------------------------------------

parcT=parcT->getsuiv();
}

mise_a_jour_informations_triangles=false; //true;

Point_Clouds_Import->liste_triangle_adaptation_BEY->distance_max_pts_plans(Adaptive_Triangulation->triangulation_initiale);  //OK les nouveaux triangles
Point_Clouds_Import->liste_triangle_adaptation_BEY->erreur_max_min_pts_triangles();

//---------------------------
Screen->Cursor= crDefault;
}
//---------------------------------------------------------------------------


//----------------------------------------------------------------------------
void TAdaptive_Triangulation::Mise_A_Jour_Sommets_Triangles_Calcul_Ecarts_Max_Triangles_Erreurs_Max_Min()
{
Screen->Cursor= crDefault;

triangle_initial_BEY *parcT;
parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while (parcT!=NULL)
{

if(parcT->filtre==true){parcT=parcT->getsuiv();continue;} //Triangle filtré
if(parcT->filtre==false && parcT->supprime==true){parcT=parcT->getsuiv();continue;}//Triangle supprimé

if(Type_Z_Coordonnee=="Z_MAX")
{
parcT->setz_pt1(Point_Clouds_Import->sommets_triangles[parcT->gets1()->getnumero_pt()].getz_pt_max());
parcT->setz_pt2(Point_Clouds_Import->sommets_triangles[parcT->gets2()->getnumero_pt()].getz_pt_max());
parcT->setz_pt3(Point_Clouds_Import->sommets_triangles[parcT->gets3()->getnumero_pt()].getz_pt_max());
}

else if(Type_Z_Coordonnee=="Z_MIN")
{
parcT->setz_pt1(Point_Clouds_Import->sommets_triangles[parcT->gets1()->getnumero_pt()].getz_pt_min());
parcT->setz_pt2(Point_Clouds_Import->sommets_triangles[parcT->gets2()->getnumero_pt()].getz_pt_min());
parcT->setz_pt3(Point_Clouds_Import->sommets_triangles[parcT->gets3()->getnumero_pt()].getz_pt_min());
}

else if(Type_Z_Coordonnee=="Z_MOY")
{
parcT->setz_pt1(Point_Clouds_Import->sommets_triangles[parcT->gets1()->getnumero_pt()].getz_pt_moy());
parcT->setz_pt2(Point_Clouds_Import->sommets_triangles[parcT->gets2()->getnumero_pt()].getz_pt_moy());
parcT->setz_pt3(Point_Clouds_Import->sommets_triangles[parcT->gets3()->getnumero_pt()].getz_pt_moy());
}

		   parcT->calculer_nouveaux_parametres_triangle();
//------------------------------------------------------------------------------------

parcT=parcT->getsuiv();
}

mise_a_jour_informations_triangles=false; //true;

Point_Clouds_Import->liste_triangle_adaptation_BEY->distance_max_pts_plans(Adaptive_Triangulation->triangulation_initiale);  //OK les nouveaux triangles
Point_Clouds_Import->liste_triangle_adaptation_BEY->erreur_max_min_pts_triangles();

//---------------------------
Screen->Cursor= crDefault;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_sommets_projetes()
{
for(int i=0; i<Point_Clouds_Import->nbre_sommets_projetes; i++)
{

glColor3d(0.5,0.8,1);
glPointSize((float)Adaptive_Triangulation->ComboBox37->Text.ToDouble());

glBegin(GL_POINTS);
glVertex3d(Point_Clouds_Import->sommets_triangles[i].getx_pt(), Point_Clouds_Import->sommets_triangles[i].gety_pt(),0);
glEnd();

}

}
//---------------------------------------------------------------------------
void __fastcall TAdaptive_Triangulation::Button16Click(TObject *Sender)
{
int indice_vertex;
Screen->Cursor= crHourGlass;

triangle_initial_BEY *parcT;

parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

int nbre_total_triangles, nbre_triangles_non_filtres;
nbre_total_triangles=nbre_triangles_non_filtres=0;
while (parcT!=NULL)
{
nbre_total_triangles++;

	if(parcT->getfiltre()==false)
	{
	nbre_triangles_non_filtres++;
	parcT->initialiser_numerotation();
	}

parcT=parcT->getsuiv();
}

Point_Clouds_Import->liste_triangle_adaptation_BEY->setnbre_triangles(nbre_total_triangles);
Point_Clouds_Import->liste_triangle_adaptation_BEY->setnbre_triangles_non_filtres(nbre_triangles_non_filtres);

double prec=1e-4;

int numero_pt=0;

  for (int i=0;i<Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles;i++)
	  for (int j=0;j<Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles;j++)
	   Point_Clouds_Import->Cellules_Sommets_Triangles[i][j].initialiser_cellule();

double xs1, ys1, zs1;
double xs2, ys2, zs2;
double xs3, ys3, zs3;
int i1, j1;
int i2, j2;
int i3, j3;
int indice_pt;

Point_Clouds_Import->sommets_triangles.clear();
int nbre_sommets_final=0;

parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();
while (parcT!=NULL)
{
if(parcT->getfiltre()==true){parcT=parcT->getsuiv();continue;}

parcT->recuperer_coordonnees_sommets_triangle(xs1, ys1, zs1, xs2, ys2, zs2, xs3, ys3, zs3);

		 if (fabs(xs1-xmin)<=1e-3) j1=0;
		 else if (fabs(xs1-xmax)<=1e-3) j1=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un;
		 else j1=(int)((xs1-xmin)/px_s);

		 if (fabs(ys1-ymin)<=1e-3) i1=0;
		 else if (fabs(ys1-ymax)<=1e-3) i1=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un;
		 else i1=(int)((ys1-ymin)/py_s);

		 Point_Clouds_Import->Cellules_Sommets_Triangles[i1][j1].chercher_point(Point_Clouds_Import->sommets_triangles, xs1, ys1, indice_pt);

		 if(indice_pt==-1)
		 {
			nbre_sommets_final++;
			indice_vertex=nbre_sommets_final-1;
			parcT->gets1()->setnumero_pt(indice_vertex);

			pt_plan_BEY sommet_TR;
			sommet_TR.affectation_initiale(xs1, ys1, zs1);
			Point_Clouds_Import->sommets_triangles.push_back(sommet_TR);

			Point_Clouds_Import->Cellules_Sommets_Triangles[i1][j1].ajouter_indice_sommet(indice_vertex);
		 }
		 else
		 {
			parcT->gets1()->setnumero_pt(indice_pt);
			Point_Clouds_Import->sommets_triangles[indice_pt].affectation_intermediaire(zs1);
		 }

		 if (fabs(xs2-xmin)<=1e-3) j2=0;
		 else if (fabs(xs2-xmax)<=1e-3) j2=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un;
		 else j2=(int)((xs2-xmin)/px_s);

		 if (fabs(ys2-ymin)<=1e-3) i2=0;
		 else if (fabs(ys2-ymax)<=1e-3) i2=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un;
		 else i2=(int)((ys2-ymin)/py_s);

		 Point_Clouds_Import->Cellules_Sommets_Triangles[i2][j2].chercher_point(Point_Clouds_Import->sommets_triangles, xs2, ys2, indice_pt);

		 if(indice_pt==-1)
		 {
			nbre_sommets_final++;
			indice_vertex=nbre_sommets_final-1;
			parcT->gets2()->setnumero_pt(indice_vertex);

			pt_plan_BEY sommet_TR;
			sommet_TR.affectation_initiale(xs2, ys2, zs2);
			Point_Clouds_Import->sommets_triangles.push_back(sommet_TR);

			Point_Clouds_Import->Cellules_Sommets_Triangles[i2][j2].ajouter_indice_sommet(indice_vertex);
		 }
		 else
		 {
			parcT->gets2()->setnumero_pt(indice_pt);
			Point_Clouds_Import->sommets_triangles[indice_pt].affectation_intermediaire(zs2);
		 }

		 if (fabs(xs3-xmin)<=1e-3) j3=0;
		 else if (fabs(xs3-xmax)<=1e-3) j3=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un;
		 else j3=(int)((xs3-xmin)/px_s);

		 if (fabs(ys3-ymin)<=1e-3) i3=0;
		 else if (fabs(ys3-ymax)<=1e-3) i3=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un;
		 else i3=(int)((ys3-ymin)/py_s);

		 Point_Clouds_Import->Cellules_Sommets_Triangles[i3][j3].chercher_point(Point_Clouds_Import->sommets_triangles, xs3, ys3, indice_pt);

		 if(indice_pt==-1)
		 {
			nbre_sommets_final++;
			indice_vertex=nbre_sommets_final-1;
			parcT->gets3()->setnumero_pt(indice_vertex);

			pt_plan_BEY sommet_TR;
			sommet_TR.affectation_initiale(xs3, ys3, zs3);
			Point_Clouds_Import->sommets_triangles.push_back(sommet_TR);

			Point_Clouds_Import->Cellules_Sommets_Triangles[i3][j3].ajouter_indice_sommet(indice_vertex);
		 }
		 else
		 {
			parcT->gets3()->setnumero_pt(indice_pt);
			Point_Clouds_Import->sommets_triangles[indice_pt].affectation_intermediaire(zs3);
		 }

parcT=parcT->getsuiv();
}

Point_Clouds_Import->nbre_sommets_projetes=nbre_sommets_final;


//------------------------------------------------------------------------------

for(int i=0; i<Point_Clouds_Import->nbre_sommets_projetes; i++)
	Point_Clouds_Import->sommets_triangles[i].calculer_Z_moy();

Screen->Cursor= crDefault;
}
//---------------------------------------------------------------------------

void TAdaptive_Triangulation::Affectation_Numeros_Sommets_Calcul_Zmax_Zmin_Zmoy_Sommets()
{
int indice_vertex;
Screen->Cursor= crHourGlass;

triangle_initial_BEY *parcT;

parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

int nbre_total_triangles, nbre_triangles_non_filtres;
nbre_total_triangles=nbre_triangles_non_filtres=0;
while (parcT!=NULL)
{
nbre_total_triangles++;

	if(parcT->filtre==true){parcT=parcT->getsuiv();continue;} //Triangle filtré
	if(parcT->filtre==false && parcT->supprime==true){parcT=parcT->getsuiv();continue;}//Triangle supprimé

	{
	nbre_triangles_non_filtres++;
	parcT->initialiser_numerotation();
	}

parcT=parcT->getsuiv();
}

Point_Clouds_Import->liste_triangle_adaptation_BEY->setnbre_triangles(nbre_total_triangles);
Point_Clouds_Import->liste_triangle_adaptation_BEY->setnbre_triangles_non_filtres(nbre_triangles_non_filtres);

double prec=1e-4;

int numero_pt=0;

  for (int i=0;i<Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles;i++)
	  for (int j=0;j<Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles;j++)
	   Point_Clouds_Import->Cellules_Sommets_Triangles[i][j].initialiser_cellule();

double xs1, ys1, zs1;
double xs2, ys2, zs2;
double xs3, ys3, zs3;
int i1, j1;
int i2, j2;
int i3, j3;
int indice_pt;

Point_Clouds_Import->sommets_triangles.clear();
int nbre_sommets_final=0;

parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();
while (parcT!=NULL)
{
	if(parcT->filtre==true){parcT=parcT->getsuiv();continue;} //Triangle filtré
	if(parcT->filtre==false && parcT->supprime==true){parcT=parcT->getsuiv();continue;}//Triangle supprimé

parcT->recuperer_coordonnees_sommets_triangle(xs1, ys1, zs1, xs2, ys2, zs2, xs3, ys3, zs3);

		 if (fabs(xs1-xmin)<=1e-3) j1=0;
		 else if (fabs(xs1-xmax)<=1e-3) j1=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un;
		 else j1=(int)((xs1-xmin)/px_s);

		 if (fabs(ys1-ymin)<=1e-3) i1=0;
		 else if (fabs(ys1-ymax)<=1e-3) i1=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un;
		 else i1=(int)((ys1-ymin)/py_s);

		 Point_Clouds_Import->Cellules_Sommets_Triangles[i1][j1].chercher_point(Point_Clouds_Import->sommets_triangles, xs1, ys1, indice_pt);

		 if(indice_pt==-1)
		 {
			nbre_sommets_final++;
			indice_vertex=nbre_sommets_final-1;
			parcT->gets1()->setnumero_pt(indice_vertex);

			pt_plan_BEY sommet_TR;
			sommet_TR.affectation_initiale(xs1, ys1, zs1);
			Point_Clouds_Import->sommets_triangles.push_back(sommet_TR);

			Point_Clouds_Import->Cellules_Sommets_Triangles[i1][j1].ajouter_indice_sommet(indice_vertex);
		 }
		 else
		 {
			parcT->gets1()->setnumero_pt(indice_pt);
			Point_Clouds_Import->sommets_triangles[indice_pt].affectation_intermediaire(zs1);
		 }

		 if (fabs(xs2-xmin)<=1e-3) j2=0;
		 else if (fabs(xs2-xmax)<=1e-3) j2=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un;
		 else j2=(int)((xs2-xmin)/px_s);

		 if (fabs(ys2-ymin)<=1e-3) i2=0;
		 else if (fabs(ys2-ymax)<=1e-3) i2=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un;
		 else i2=(int)((ys2-ymin)/py_s);

		 Point_Clouds_Import->Cellules_Sommets_Triangles[i2][j2].chercher_point(Point_Clouds_Import->sommets_triangles, xs2, ys2, indice_pt);

		 if(indice_pt==-1)
		 {
			nbre_sommets_final++;
			indice_vertex=nbre_sommets_final-1;
			parcT->gets2()->setnumero_pt(indice_vertex);

			pt_plan_BEY sommet_TR;
			sommet_TR.affectation_initiale(xs2, ys2, zs2);
			Point_Clouds_Import->sommets_triangles.push_back(sommet_TR);

			Point_Clouds_Import->Cellules_Sommets_Triangles[i2][j2].ajouter_indice_sommet(indice_vertex);
		 }
		 else
		 {
			parcT->gets2()->setnumero_pt(indice_pt);
			Point_Clouds_Import->sommets_triangles[indice_pt].affectation_intermediaire(zs2);
		 }

		 if (fabs(xs3-xmin)<=1e-3) j3=0;
		 else if (fabs(xs3-xmax)<=1e-3) j3=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un;
		 else j3=(int)((xs3-xmin)/px_s);

		 if (fabs(ys3-ymin)<=1e-3) i3=0;
		 else if (fabs(ys3-ymax)<=1e-3) i3=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un;
		 else i3=(int)((ys3-ymin)/py_s);

		 Point_Clouds_Import->Cellules_Sommets_Triangles[i3][j3].chercher_point(Point_Clouds_Import->sommets_triangles, xs3, ys3, indice_pt);

		 if(indice_pt==-1)
		 {
			nbre_sommets_final++;
			indice_vertex=nbre_sommets_final-1;
			parcT->gets3()->setnumero_pt(indice_vertex);

			pt_plan_BEY sommet_TR;
			sommet_TR.affectation_initiale(xs3, ys3, zs3);
			Point_Clouds_Import->sommets_triangles.push_back(sommet_TR);

			Point_Clouds_Import->Cellules_Sommets_Triangles[i3][j3].ajouter_indice_sommet(indice_vertex);
		 }
		 else
		 {
			parcT->gets3()->setnumero_pt(indice_pt);
			Point_Clouds_Import->sommets_triangles[indice_pt].affectation_intermediaire(zs3);
		 }

parcT=parcT->getsuiv();
}

Point_Clouds_Import->nbre_sommets_projetes=nbre_sommets_final;


//------------------------------------------------------------------------------

for(int i=0; i<Point_Clouds_Import->nbre_sommets_projetes; i++)
	Point_Clouds_Import->sommets_triangles[i].calculer_Z_moy();

Screen->Cursor= crDefault;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void cellule_sommets_triangles::chercher_point(vector <pt_plan_BEY> &sommets_triangles, double x, double y, int &indice_pt)
{
double dx, dy;
bool existe=false;
indice_pt=-1;
int indice;

 for(int i=0;i<nombre_sommets_triangles;i++)
 {
  indice=indice_sommets_triangles[i];

  dx=sommets_triangles[indice].getx_pt()-x;
  if(fabs(dx)>1e-3)continue;

  dy=sommets_triangles[indice].gety_pt()-y;
  if(fabs(dy)>1e-3)continue;

  existe=true;
  indice_pt=indice;
  break;
 }
}

//---------------------------------------------------------------------------
void __fastcall TAdaptive_Triangulation::Button15Click(TObject *Sender)
{
Screen->Cursor= crHourGlass;

seuil_aire_triangle=Adaptive_Triangulation->Edit22->Text.ToDouble();
rapport_limites_triangle_limites_points=Adaptive_Triangulation->Edit24->Text.ToDouble();
nbre_min_points_triangle=Adaptive_Triangulation->Edit26->Text.ToDouble();
ecart_max_droite=Adaptive_Triangulation->Edit28->Text.ToDouble();

triangle_initial_BEY *parc=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while(parc!=NULL)
{
if(parc->filtre==true){parc=parc->getsuiv(); continue;} //Triangle filtré
if(parc->filtre==false && parc->supprime==true){parc=parc->getsuiv(); continue;} //Triangle supprimé

if(parc->getv1()!=NULL && parc->getv2()!=NULL && parc->getv3()!=NULL){parc=parc->getsuiv(); continue;}


if((parc->getv1()!=NULL && (parc->getv2()==NULL || parc->getv3()==NULL))
 ||(parc->getv2()!=NULL && (parc->getv1()==NULL || parc->getv3()==NULL))
 ||(parc->getv3()!=NULL && (parc->getv1()==NULL || parc->getv2()==NULL))
 ||(parc->getv1()==NULL && parc->getv2()==NULL && parc->getv3()==NULL))
{
if(CheckBox40->Checked) //1er cas
if(parc->aire_triangle_2D<=seuil_aire_triangle)
parc->setfiltre(true);

double rapport, hauteur_triangle;
if(Edit31->Text!="") hauteur_triangle=Adaptive_Triangulation->Edit31->Text.ToDouble();
else hauteur_triangle=1;

if(parc->delta_Z_pts_triangle!=0 && parc->delta_Z_triangle>hauteur_triangle)
	rapport=parc->delta_Z_triangle/parc->delta_Z_pts_triangle;
else
	rapport=parc->delta_Z_triangle;

if(CheckBox41->Checked) //2ème cas
if(rapport>=rapport_limites_triangle_limites_points)
parc->setfiltre(true);


if(CheckBox46->Checked) //3ème cas
if(parc->getnbre_pts_triangle()<=nbre_min_points_triangle)
parc->setfiltre(true);

if(CheckBox51->Checked) //4ème cas
if(parc->ecart_max_droite<=ecart_max_droite)
parc->setfiltre(true);

}

parc=parc->getsuiv();
}

triangle_initial_BEY *parcT22=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();
int num=0;
while (parcT22!=NULL)
{
if(parcT22->getfiltre()==true){parcT22->setnum_triangle(-1);parcT22=parcT22->getsuiv();continue;}
num++;
parcT22->setnum_triangle(num);
parcT22=parcT22->getsuiv();
}

Point_Clouds_Import->liste_triangle_adaptation_BEY->determiner_voisins_triangles_new();    //OK OK FINAL les nouveaux triangles

Button19Click(Sender);  //calcul du nombre de triangles, de points et de sommets

Point_Clouds_Import->liste_triangle_adaptation_BEY->determiner_parametres_filtration_triangles();
Visualization->DrawObjects();

Screen->Cursor= crDefault;

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TAdaptive_Triangulation::creation_deux_triangles_milieu_cote(triangle_initial_BEY *parc)
{
liste_pts_triangle_BEY_tmp.clear();
int nbre_pts=parc->getnbre_pts_triangle();
for(int i=0; i<nbre_pts; i++)
{
   liste_pts_triangle_BEY_tmp.push_back(parc->liste_pts_triangle_BEY[i]);
}

triangle_initial_BEY *parc1;
double xmin, xmax, ymin, ymax, x_milieu, y_milieu;

double dis12=sqrt(pow(parc->gets1()->getx_pt()-parc->gets2()->getx_pt(),2)+pow(parc->gets1()->gety_pt()-parc->gets2()->gety_pt(),2));//+pow(parc->getz_pt1()-parc->getz_pt2(),2)) ;
double dis13=sqrt(pow(parc->gets1()->getx_pt()-parc->gets3()->getx_pt(),2)+pow(parc->gets1()->gety_pt()-parc->gets3()->gety_pt(),2));//+pow(parc->getz_pt1()-parc->getz_pt3(),2)) ;
double dis23=sqrt(pow(parc->gets3()->getx_pt()-parc->gets2()->getx_pt(),2)+pow(parc->gets3()->gety_pt()-parc->gets2()->gety_pt(),2));//+pow(parc->getz_pt3()-parc->getz_pt2(),2)) ;

double dis_max=max(dis12, max(dis13,dis23));

if(fabs(dis_max-dis12)<=1e-6 || parc->getdensite_m1()==0)      //Pt milieu sur le segment 12
{
x_milieu=0.5*(parc->gets1()->getx_pt()+parc->gets2()->getx_pt());
y_milieu=0.5*(parc->gets1()->gety_pt()+parc->gets2()->gety_pt());

		   parc1=new triangle_initial_BEY();

		   parc1->gets1()->setx_pt(x_milieu);
		   parc1->gets1()->sety_pt(y_milieu);
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(parc->gets2()->getx_pt());
		   parc1->gets2()->sety_pt(parc->gets2()->gety_pt());
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(parc->gets3()->getx_pt());
		   parc1->gets3()->sety_pt(parc->gets3()->gety_pt());
		   parc1->gets3()->setz(0);

		   parc1->calculer_limites_triangle();

		   parc->initialiser();

		   parc->gets1()->setx_pt(parc->gets1()->getx_pt());
		   parc->gets1()->sety_pt(parc->gets1()->gety_pt());
		   parc->gets1()->setz(0);

		   parc->gets2()->setx_pt(x_milieu);
		   parc->gets2()->sety_pt(y_milieu);
		   parc->gets2()->setz(0);

		   parc->gets3()->setx_pt(parc->gets3()->getx_pt());
		   parc->gets3()->sety_pt(parc->gets3()->gety_pt());
		   parc->gets3()->setz(0);

		   xmin=min(parc->gets1()->getx_pt(),min(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));
		   xmax=max(parc->gets1()->getx_pt(),max(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));

		   ymin=min(parc->gets1()->gety_pt(),min(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));
		   ymax=max(parc->gets1()->gety_pt(),max(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));

		   parc->setxmin_t(xmin);
		   parc->setxmax_t(xmax);

		   parc->setymin_t(ymin);
		   parc->setymax_t(ymax);

double x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1;
x11=parc1->gets1()->getx_pt(); y11=parc1->gets1()->gety_pt();

x12=parc1->gets2()->getx_pt(); y12=parc1->gets2()->gety_pt();

x13=parc1->gets3()->getx_pt(); y13=parc1->gets3()->gety_pt();

xminT1=parc1->getxmin_t();   yminT1=parc1->getymin_t();

xmaxT1=parc1->getxmax_t();  ymaxT1=parc1->getymax_t();

double x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0;
x01=parc->gets1()->getx_pt(); y01=parc->gets1()->gety_pt();

x02=parc->gets2()->getx_pt(); y02=parc->gets2()->gety_pt();

x03=parc->gets3()->getx_pt(); y03=parc->gets3()->gety_pt();

xminT0=parc->getxmin_t();   yminT0=parc->getymin_t();

xmaxT0=parc->getxmax_t(); ymaxT0=parc->getymax_t();


double x_test, y_test;

parc->setnbre_pts_triangle(0);
parc1->setnbre_pts_triangle(0);

for(int i=0; i<nbre_pts; i++)
{
x_test=liste_pts_triangle_BEY_tmp[i].p->getx();
y_test=liste_pts_triangle_BEY_tmp[i].p->gety();

		 if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0, x_test, y_test)==true)
		 {
			 parc->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

		 else //if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1, x_test, y_test)==true)
		 {
			 parc1->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }


}

//-----------------------------------------------------------------------------------------

		   parc->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();

		   if(parc->getfiltre()==false)
		   {
		   parc->approximation_pts_triangle_plan_moindre_carre();
		   parc->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   parc->distance_max_pts_plan();
		   }

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   }

		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   liste_pts_triangle_BEY_tmp.clear();

if(Adaptive_Triangulation->creer_triangles(x_milieu, y_milieu, parc->getv1())==false)
	if(Adaptive_Triangulation->creer_triangles(x_milieu, y_milieu, parc->getv2())==false)
		Adaptive_Triangulation->creer_triangles(x_milieu, y_milieu, parc->getv3());

}


else if(fabs(dis_max-dis13)<=1e-6  || parc->getdensite_m3()==0)        //Pt milieu sur le segment 13
{
x_milieu=0.5*(parc->gets1()->getx_pt()+parc->gets3()->getx_pt());
y_milieu=0.5*(parc->gets1()->gety_pt()+parc->gets3()->gety_pt());

		   parc1=new triangle_initial_BEY();

		   parc1->gets1()->setx_pt(x_milieu);
		   parc1->gets1()->sety_pt(y_milieu);
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(parc->gets2()->getx_pt());
		   parc1->gets2()->sety_pt(parc->gets2()->gety_pt());
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(parc->gets3()->getx_pt());
		   parc1->gets3()->sety_pt(parc->gets3()->gety_pt());
		   parc1->gets3()->setz(0);

		   parc1->calculer_limites_triangle();

		   parc->initialiser();

		   parc->gets1()->setx_pt(parc->gets1()->getx_pt());
		   parc->gets1()->sety_pt(parc->gets1()->gety_pt());
		   parc->gets1()->setz(0);

		   parc->gets2()->setx_pt(parc->gets2()->getx_pt());
		   parc->gets2()->sety_pt(parc->gets2()->gety_pt());
		   parc->gets2()->setz(0);

		   parc->gets3()->setx_pt(x_milieu);
		   parc->gets3()->sety_pt(y_milieu);
		   parc->gets3()->setz(0);

		   xmin=min(parc->gets1()->getx_pt(),min(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));
		   xmax=max(parc->gets1()->getx_pt(),max(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));

		   ymin=min(parc->gets1()->gety_pt(),min(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));
		   ymax=max(parc->gets1()->gety_pt(),max(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));

		   parc->setxmin_t(xmin);
		   parc->setxmax_t(xmax);

		   parc->setymin_t(ymin);
		   parc->setymax_t(ymax);


double x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1;
x11=parc1->gets1()->getx_pt(); y11=parc1->gets1()->gety_pt();

x12=parc1->gets2()->getx_pt(); y12=parc1->gets2()->gety_pt();

x13=parc1->gets3()->getx_pt(); y13=parc1->gets3()->gety_pt();

xminT1=parc1->getxmin_t();   yminT1=parc1->getymin_t();

xmaxT1=parc1->getxmax_t();  ymaxT1=parc1->getymax_t();

double x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0;
x01=parc->gets1()->getx_pt(); y01=parc->gets1()->gety_pt();

x02=parc->gets2()->getx_pt(); y02=parc->gets2()->gety_pt();

x03=parc->gets3()->getx_pt(); y03=parc->gets3()->gety_pt();

xminT0=parc->getxmin_t();   yminT0=parc->getymin_t();

xmaxT0=parc->getxmax_t(); ymaxT0=parc->getymax_t();


double x_test, y_test;

parc->setnbre_pts_triangle(0);
parc1->setnbre_pts_triangle(0);

for(int i=0; i<nbre_pts; i++)
{
x_test=liste_pts_triangle_BEY_tmp[i].p->getx();
y_test=liste_pts_triangle_BEY_tmp[i].p->gety();


		 if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0, x_test, y_test)==true)
		 {
			 parc->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

		 else //if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1, x_test, y_test)==true)
		 {
			 parc1->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

}

//-----------------------------------------------------------------------------------------

		   parc->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();

		   if(parc->getfiltre()==false)
		   {
		   parc->approximation_pts_triangle_plan_moindre_carre();
		   parc->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   parc->distance_max_pts_plan();
		   }

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   }

		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   liste_pts_triangle_BEY_tmp.clear();

if(Adaptive_Triangulation->creer_triangles(x_milieu, y_milieu, parc->getv1())==false)
	if(Adaptive_Triangulation->creer_triangles(x_milieu, y_milieu, parc->getv2())==false)
		Adaptive_Triangulation->creer_triangles(x_milieu, y_milieu, parc->getv3());

}

else if(fabs(dis_max-dis23)<=1e-6  || parc->getdensite_m2()==0)      //Pt milieu sur le segment 23
{
x_milieu=0.5*(parc->gets2()->getx_pt()+parc->gets3()->getx_pt());
y_milieu=0.5*(parc->gets2()->gety_pt()+parc->gets3()->gety_pt());

		   parc1=new triangle_initial_BEY();

		   parc1->gets1()->setx_pt(parc->gets1()->getx_pt());
		   parc1->gets1()->sety_pt(parc->gets1()->gety_pt());
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(x_milieu);
		   parc1->gets2()->sety_pt(y_milieu);
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(parc->gets3()->getx_pt());
		   parc1->gets3()->sety_pt(parc->gets3()->gety_pt());
		   parc1->gets3()->setz(0);

		   parc1->calculer_limites_triangle();

		   parc->initialiser();

		   parc->gets1()->setx_pt(parc->gets1()->getx_pt());
		   parc->gets1()->sety_pt(parc->gets1()->gety_pt());
		   parc->gets1()->setz(0);

		   parc->gets2()->setx_pt(parc->gets2()->getx_pt());
		   parc->gets2()->sety_pt(parc->gets2()->gety_pt());
		   parc->gets2()->setz(0);

		   parc->gets3()->setx_pt(x_milieu);
		   parc->gets3()->sety_pt(y_milieu);
		   parc->gets3()->setz(0);

		   xmin=min(parc->gets1()->getx_pt(),min(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));
		   xmax=max(parc->gets1()->getx_pt(),max(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));

		   ymin=min(parc->gets1()->gety_pt(),min(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));
		   ymax=max(parc->gets1()->gety_pt(),max(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));

		   parc->setxmin_t(xmin);
		   parc->setxmax_t(xmax);

		   parc->setymin_t(ymin);
		   parc->setymax_t(ymax);

double x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1;
x11=parc1->gets1()->getx_pt(); y11=parc1->gets1()->gety_pt();

x12=parc1->gets2()->getx_pt(); y12=parc1->gets2()->gety_pt();

x13=parc1->gets3()->getx_pt(); y13=parc1->gets3()->gety_pt();

xminT1=parc1->getxmin_t();   yminT1=parc1->getymin_t();

xmaxT1=parc1->getxmax_t();  ymaxT1=parc1->getymax_t();

double x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0;
x01=parc->gets1()->getx_pt(); y01=parc->gets1()->gety_pt();

x02=parc->gets2()->getx_pt(); y02=parc->gets2()->gety_pt();

x03=parc->gets3()->getx_pt(); y03=parc->gets3()->gety_pt();

xminT0=parc->getxmin_t();   yminT0=parc->getymin_t();

xmaxT0=parc->getxmax_t(); ymaxT0=parc->getymax_t();


double x_test, y_test;

parc->setnbre_pts_triangle(0);
parc1->setnbre_pts_triangle(0);

for(int i=0; i<nbre_pts; i++)
{
x_test=liste_pts_triangle_BEY_tmp[i].p->getx();
y_test=liste_pts_triangle_BEY_tmp[i].p->gety();

		 if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0, x_test, y_test)==true)
		 {
			 parc->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

		 else //if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1, x_test, y_test)==true)
		 {
			 parc1->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

}

//-----------------------------------------------------------------------------------------

		   parc->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();

		   if(parc->getfiltre()==false)
		   {
		   parc->approximation_pts_triangle_plan_moindre_carre();
		   parc->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   parc->distance_max_pts_plan();
		   }

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   }

		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   liste_pts_triangle_BEY_tmp.clear();

if(Adaptive_Triangulation->creer_triangles(x_milieu, y_milieu, parc->getv1())==false)
	if(Adaptive_Triangulation->creer_triangles(x_milieu, y_milieu, parc->getv2())==false)
		Adaptive_Triangulation->creer_triangles(x_milieu, y_milieu, parc->getv3());

}


}
//---------------------------------------------------------------------------
//------------------------------------------------------------------
void triangle_initial_BEY::calculer_deltaX_deltaY_deltaZ(double &p1p2_x, double &p1p2_y, double &p1p3_x, double &p1p3_y, double &p2p3_x, double &p2p3_y)
{
p1p2_x=s2->x_pt-s1->x_pt;
p1p2_y=s2->y_pt-s1->y_pt;

p1p3_x=s3->x_pt-s1->x_pt;
p1p3_y=s3->y_pt-s1->y_pt;

p2p3_x=s3->x_pt-s2->x_pt;
p2p3_y=s3->y_pt-s2->y_pt;
}

//---------------------------------------------------------------------------
bool triangle_initial_BEY::appartenance_pt_triangle_BEY(double x, double y, double p1p2_x, double p1p2_y, double p1p3_x, double p1p3_y, double p2p3_x, double p2p3_y)
{
if(x > (xmax_t) || x < (xmin_t) || y > (ymax_t) || y < (ymin_t)) return false;

double p1m_y=y-s1->y_pt;
double p1m_x=x-s1->x_pt;

double p1p2vp1m_z=p1p2_x * p1m_y -p1p2_y * p1m_x;//produit vectoriel
double p1mvp1p3_z=p1m_x * p1p3_y -p1m_y * p1p3_x;
double ps1=p1p2vp1m_z * p1mvp1p3_z;//produit scalaire

if(fabs(ps1)<=1e-10)ps1=0; //BEY
if(ps1<0)return false; //BEY

double p2m_y=y-s2->y_pt;
double p2m_x=x-s2->x_pt;

double p2p1vp2m_z=-p1p2_x * p2m_y -(-p1p2_y)*p2m_x ;
double p2mvp2p3_z=p2m_x * p2p3_y -p2m_y * p2p3_x;
double ps2=p2p1vp2m_z * p2mvp2p3_z;

if(fabs(ps2)<=1e-10)ps2=0; //BEY
if(ps2<0)return false; //BEY

double p3m_x=x-s3->x_pt;
double p3m_y=y-s3->y_pt;

double p3p1vp3m_z=-p1p3_x * p3m_y -(-p1p3_y)*p3m_x;
double p3mvp3p2_z=p3m_x * (-p2p3_y )-p3m_y *(-p2p3_x);
double ps3= p3p1vp3m_z  * p3mvp3p2_z;

if(fabs(ps3)<=1e-10)ps3=0;//BEY
if(ps3<0)return false; //BEY

return true;
}
//------------------------------------------------------------------

//---------------------------------------------------------------------------
void triangle_initial_BEY::creation_deux_triangles_milieu_cote(ListTriangle_BEY_BEY *liste_triangle_adaptation_BEY)
{
int nbre_pts=nbre_pts_triangle; //this->getnbre_pts_triangle();
//------------------------------------------------------------------------------
point_nuage_BEY *liste_pts_triangle_BEY_tmp;
liste_pts_triangle_BEY_tmp= new point_nuage_BEY [nbre_pts];

for(int i=0; i<nbre_pts; i++)
   liste_pts_triangle_BEY_tmp[i]=liste_pts_triangle_BEY[i];
//------------------------------------------------------------------------------

triangle_initial_BEY *parc1;//, *this_new;
triangle_initial_BEY *V1, *V2, *V3;
double x_milieu, y_milieu;

//------------------------------------------------------------------------------
double xs1=s1->x_pt;
double ys1=s1->y_pt;

double xs2=s2->x_pt;
double ys2=s2->y_pt;

double xs3=s3->x_pt;
double ys3=s3->y_pt;

double dis12=/*sqrt*/(pow(xs1-xs2,2)+pow(ys1-ys2,2));

double dis13=/*sqrt*/(pow(xs1-xs3,2)+pow(ys1-ys3,2));

double dis23=/*sqrt*/(pow(xs3-xs2,2)+pow(ys3-ys2,2));

double dis_max=max(dis12, max(dis13,dis23));

if(fabs(dis_max-dis12)<=1e-6 || densite_m1==0)      //Pt milieu sur le segment 12 :Voisin V1
{
V1=this->v1;
V2=this->v2;
V3=this->v3;

x_milieu=0.5*(xs1+xs2);

y_milieu=0.5*(ys1+ys2);

		   parc1=new triangle_initial_BEY();  //Tnew
		   parc1->affecter_coordonnees_sommets_triangle(x_milieu, y_milieu, 0, xs2, ys2, 0, xs3, ys3, 0);

		   this->initialiser(); //T1
		   this->affecter_coordonnees_sommets_triangle(xs1, ys1, 0, x_milieu, y_milieu, 0, xs3, ys3, 0);

double p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y;
this->calculer_deltaX_deltaY_deltaZ(p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y);

double p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy;
parc1->calculer_deltaX_deltaY_deltaZ(p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy);

double x_test, y_test;

for(int i=0; i<nbre_pts; i++)
{
//------------------------------------------------------------------------------
x_test=liste_pts_triangle_BEY_tmp[i].p->x;
y_test=liste_pts_triangle_BEY_tmp[i].p->y;
//------------------------------------------------------------------------------
		 if(this->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y)==true)
			 {
			 this->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
			 }
		 else if(parc1->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy)==true)
			 {
			 parc1->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
			 }
}

//-----------------------------------------------------------------------------------------

//------------------------------------------------------------------------------
		   this->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();

		   if(this->getfiltre()==false)
		   {
		   this->approximation_pts_triangle_plan_moindre_carre();
		   this->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   this->distance_max_pts_plan();
		   this->setnouveau_triangle(false);//BEY
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(this); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(this); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   parc1->setnouveau_triangle(false);//BEY
		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }
		   else
			 Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc1);


		   delete [] liste_pts_triangle_BEY_tmp;

Adaptive_Triangulation->voisin_1_supprime=false;
Adaptive_Triangulation->voisin_2_supprime=false;
Adaptive_Triangulation->voisin_3_supprime=false;

if(creer_triangles(x_milieu, y_milieu, V1, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_1_supprime=true;
if(creer_triangles(x_milieu, y_milieu, V2, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_2_supprime=true;
if(creer_triangles(x_milieu, y_milieu, V3, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_3_supprime=true;

return;
}

if(fabs(dis_max-dis13)<=1e-6  || getdensite_m3()==0)        //Pt milieu sur le segment 13: Voisin V3
{
V1=this->v1;
V2=this->v2;
V3=this->v3;

x_milieu=0.5*(xs1+xs3);

y_milieu=0.5*(ys1+ys3);

		   parc1=new triangle_initial_BEY(); //Tnew
		   parc1->affecter_coordonnees_sommets_triangle(x_milieu, y_milieu, 0, xs2, ys2, 0, xs3, ys3, 0);

		   this->initialiser();   //T1
		   this->affecter_coordonnees_sommets_triangle(xs1, ys1, 0, xs2, ys2, 0, x_milieu, y_milieu, 0);

double p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y;
this->calculer_deltaX_deltaY_deltaZ(p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y);

double p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy;
parc1->calculer_deltaX_deltaY_deltaZ(p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy);

double x_test, y_test;

for(int i=0; i<nbre_pts; i++)
{
//------------------------------------------------------------------------------
x_test=liste_pts_triangle_BEY_tmp[i].p->x;
y_test=liste_pts_triangle_BEY_tmp[i].p->y;
//------------------------------------------------------------------------------
		 if(this->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y)==true)
			 {
			 this->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
			 }

		 else if(parc1->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy)==true)
			 {
			 parc1->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
			 }
}

//-----------------------------------------------------------------------------------------

//------------------------------------------------------------------------------
		   this->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();

		   if(this->getfiltre()==false)
		   {
		   this->approximation_pts_triangle_plan_moindre_carre();
		   this->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   this->distance_max_pts_plan();
		   this->setnouveau_triangle(false);//BEY
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(this); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(this); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }


		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   parc1->setnouveau_triangle(false);//BEY
		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }
		   else
			 Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc1);

		   delete [] liste_pts_triangle_BEY_tmp;

Adaptive_Triangulation->voisin_1_supprime=false;
Adaptive_Triangulation->voisin_2_supprime=false;
Adaptive_Triangulation->voisin_3_supprime=false;

if(creer_triangles(x_milieu, y_milieu, V1, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_1_supprime=true;
if(creer_triangles(x_milieu, y_milieu, V2, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_2_supprime=true;
if(creer_triangles(x_milieu, y_milieu, V3, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_3_supprime=true;

return;
}

if(fabs(dis_max-dis23)<=1e-6  || getdensite_m2()==0)      //Pt milieu sur le segment 23: Voisin V2
{
V1=this->v1;
V2=this->v2;
V3=this->v3;

x_milieu=0.5*(xs2+xs3);

y_milieu=0.5*(ys2+ys3);

		   parc1=new triangle_initial_BEY();  //Tnew
		   parc1->affecter_coordonnees_sommets_triangle(xs1, ys1, 0, x_milieu, y_milieu, 0, xs3, ys3, 0);

		   this->initialiser();  //T1
		   this->affecter_coordonnees_sommets_triangle(xs1, ys1, 0, xs2, ys2, 0, x_milieu, y_milieu, 0);

double p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y;
this->calculer_deltaX_deltaY_deltaZ(p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y);

double p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy;
parc1->calculer_deltaX_deltaY_deltaZ(p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy);

double x_test, y_test;

for(int i=0; i<nbre_pts; i++)
{
//------------------------------------------------------------------------------
x_test=liste_pts_triangle_BEY_tmp[i].p->x;
y_test=liste_pts_triangle_BEY_tmp[i].p->y;
//------------------------------------------------------------------------------
		 if(this->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y)==true)
			 {
			 this->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
			 }

		 else if(parc1->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy)==true)
			 {
			 parc1->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
			 }
}

//-----------------------------------------------------------------------------------------

//------------------------------------------------------------------------------
		   this->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();

		   if(this->getfiltre()==false)
		   {
		   this->approximation_pts_triangle_plan_moindre_carre();
		   this->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   this->distance_max_pts_plan();
		   this->setnouveau_triangle(false);//BEY
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(this); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(this); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   parc1->setnouveau_triangle(false);//BEY
		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }
		   else
			 Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc1);

		   delete [] liste_pts_triangle_BEY_tmp;

Adaptive_Triangulation->voisin_1_supprime=false;
Adaptive_Triangulation->voisin_2_supprime=false;
Adaptive_Triangulation->voisin_3_supprime=false;

if(creer_triangles(x_milieu, y_milieu, V1, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_1_supprime=true;
if(creer_triangles(x_milieu, y_milieu, V2, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_2_supprime=true;
if(creer_triangles(x_milieu, y_milieu, V3, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_3_supprime=true;

return;
}


}
//---------------------------------------------------------------------------
void TAdaptive_Triangulation::creation_triangles_centre_gravite(triangle_initial *parc)
{
triangle_initial *parc1;
double xmin, xmax, ymin, ymax;

		   parc1=new triangle_initial();

		   parc1->gets1()->setx_pt(parc->gets1()->getx_pt());
		   parc1->gets1()->sety_pt(parc->gets1()->gety_pt());
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(parc->getxg());
		   parc1->gets2()->sety_pt(parc->getyg());
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(parc->gets3()->getx_pt());
		   parc1->gets3()->sety_pt(parc->gets3()->gety_pt());
		   parc1->gets3()->setz(0);

		   parc1->setxg((parc1->gets1()->getx_pt()+parc1->gets2()->getx_pt()+parc1->gets3()->getx_pt())/3);
		   parc1->setyg((parc1->gets1()->gety_pt()+parc1->gets2()->gety_pt()+parc1->gets3()->gety_pt())/3);

		   xmin=min(parc1->gets1()->getx_pt(),min(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));
		   xmax=max(parc1->gets1()->getx_pt(),max(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));

		   ymin=min(parc1->gets1()->gety_pt(),min(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));
		   ymax=max(parc1->gets1()->gety_pt(),max(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));

		   parc1->setxmin_t(xmin);
		   parc1->setxmax_t(xmax);

		   parc1->setymin_t(ymin);
		   parc1->setymax_t(ymax);

		   Point_Clouds_Import->liste_triangle_adaptation->ajouter_Triangle(parc1);

		   parc1=new triangle_initial();

		   parc1->gets1()->setx_pt(parc->getxg());
		   parc1->gets1()->sety_pt(parc->getyg());
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(parc->gets2()->getx_pt());
		   parc1->gets2()->sety_pt(parc->gets2()->gety_pt());
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(parc->gets3()->getx_pt());
		   parc1->gets3()->sety_pt(parc->gets3()->gety_pt());
		   parc1->gets3()->setz(0);

		   parc1->setxg((parc1->gets1()->getx_pt()+parc1->gets2()->getx_pt()+parc1->gets3()->getx_pt())/3);
		   parc1->setyg((parc1->gets1()->gety_pt()+parc1->gets2()->gety_pt()+parc1->gets3()->gety_pt())/3);

		   xmin=min(parc1->gets1()->getx_pt(),min(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));
		   xmax=max(parc1->gets1()->getx_pt(),max(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));

		   ymin=min(parc1->gets1()->gety_pt(),min(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));
		   ymax=max(parc1->gets1()->gety_pt(),max(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));

		   parc1->setxmin_t(xmin);
		   parc1->setxmax_t(xmax);

		   parc1->setymin_t(ymin);
		   parc1->setymax_t(ymax);

		   parc1->setfiltre(false);
		   parc1->seteliminer_sommet(false);

		   Point_Clouds_Import->liste_triangle_adaptation->ajouter_Triangle(parc1);

		   parc->intialiser();

		   parc->gets1()->setx_pt(parc->gets1()->getx_pt());
		   parc->gets1()->sety_pt(parc->gets1()->gety_pt());
		   parc->gets1()->setz(0);

		   parc->gets2()->setx_pt(parc->gets2()->getx_pt());
		   parc->gets2()->sety_pt(parc->gets2()->gety_pt());
		   parc->gets2()->setz(0);

		   parc->gets3()->setx_pt(parc->getxg());
		   parc->gets3()->sety_pt(parc->getyg());
		   parc->gets3()->setz(0);

		   parc->setxg((parc->gets1()->getx_pt()+parc->gets2()->getx_pt()+parc->gets3()->getx_pt())/3);
		   parc->setyg((parc->gets1()->gety_pt()+parc->gets2()->gety_pt()+parc->gets3()->gety_pt())/3);

		   xmin=min(parc->gets1()->getx_pt(),min(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));
		   xmax=max(parc->gets1()->getx_pt(),max(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));

		   ymin=min(parc->gets1()->gety_pt(),min(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));
		   ymax=max(parc->gets1()->gety_pt(),max(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));

		   parc->setxmin_t(xmin);
		   parc->setxmax_t(xmax);

		   parc->setymin_t(ymin);
		   parc->setymax_t(ymax);
}
//---------------------------------------------------------------------------
bool TAdaptive_Triangulation::creer_triangles(double xinter, double yinter, triangle_initial_BEY *voisin) //BEY
{
if(voisin==NULL)return false;//BEY

bool appartient;
double precision_calcul=1e-6;
triangle_initial_BEY *parc1;
double xmin, xmax, ymin, ymax;

if( (fabs(xinter-voisin->gets1()->getx_pt())<=precision_calcul && fabs(yinter-voisin->gets1()->gety_pt())<=precision_calcul)
  ||(fabs(xinter-voisin->gets2()->getx_pt())<=precision_calcul && fabs(yinter-voisin->gets2()->gety_pt())<=precision_calcul)
  ||(fabs(xinter-voisin->gets3()->getx_pt())<=precision_calcul && fabs(yinter-voisin->gets3()->gety_pt())<=precision_calcul))return false; //pt d'intersection est un sommet

appartient=voisin->appartence_pt_triangle(xinter, yinter); //BEY

if(appartient==false)return false;

liste_pts_triangle_BEY_tmp.clear();
int nbre_pts=voisin->getnbre_pts_triangle();
for(int i=0; i<nbre_pts; i++)
{
   liste_pts_triangle_BEY_tmp.push_back(voisin->liste_pts_triangle_BEY[i]);
}

//-----------------

double produit_s1s2_s1p=(voisin->gets2()->getx_pt()-voisin->gets1()->getx_pt())*(yinter-voisin->gets1()->gety_pt())-(voisin->gets2()->gety_pt()-voisin->gets1()->gety_pt())*(xinter-voisin->gets1()->getx_pt());
double produit_s1s3_s1p=(voisin->gets3()->getx_pt()-voisin->gets1()->getx_pt())*(yinter-voisin->gets1()->gety_pt())-(voisin->gets3()->gety_pt()-voisin->gets1()->gety_pt())*(xinter-voisin->gets1()->getx_pt());
double produit_s2s3_s2p=(voisin->gets3()->getx_pt()-voisin->gets2()->getx_pt())*(yinter-voisin->gets2()->gety_pt())-(voisin->gets3()->gety_pt()-voisin->gets2()->gety_pt())*(xinter-voisin->gets2()->getx_pt());

if(fabs(produit_s1s2_s1p)<=precision_calcul)  //pt sur le segment 12
{
		   parc1=new triangle_initial_BEY();

		   parc1->gets1()->setx_pt(xinter);
		   parc1->gets1()->sety_pt(yinter);
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(voisin->gets2()->getx_pt());
		   parc1->gets2()->sety_pt(voisin->gets2()->gety_pt());
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(voisin->gets3()->getx_pt());
		   parc1->gets3()->sety_pt(voisin->gets3()->gety_pt());
		   parc1->gets3()->setz(0);

		   parc1->calculer_limites_triangle();

		   voisin->initialiser();

		   voisin->gets1()->setx_pt(voisin->gets1()->getx_pt());
		   voisin->gets1()->sety_pt(voisin->gets1()->gety_pt());
		   voisin->gets1()->setz(0);

		   voisin->gets2()->setx_pt(xinter);
		   voisin->gets2()->sety_pt(yinter);
		   voisin->gets2()->setz(0);

		   voisin->gets3()->setx_pt(voisin->gets3()->getx_pt());
		   voisin->gets3()->sety_pt(voisin->gets3()->gety_pt());
		   voisin->gets3()->setz(0);

		   xmin=min(voisin->gets1()->getx_pt(),min(voisin->gets2()->getx_pt(),voisin->gets3()->getx_pt()));
		   xmax=max(voisin->gets1()->getx_pt(),max(voisin->gets2()->getx_pt(),voisin->gets3()->getx_pt()));

		   ymin=min(voisin->gets1()->gety_pt(),min(voisin->gets2()->gety_pt(),voisin->gets3()->gety_pt()));
		   ymax=max(voisin->gets1()->gety_pt(),max(voisin->gets2()->gety_pt(),voisin->gets3()->gety_pt()));

		   voisin->setxmin_t(xmin);
		   voisin->setxmax_t(xmax);

		   voisin->setymin_t(ymin);
		   voisin->setymax_t(ymax);

double x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1;
x11=parc1->gets1()->getx_pt(); y11=parc1->gets1()->gety_pt();

x12=parc1->gets2()->getx_pt(); y12=parc1->gets2()->gety_pt();

x13=parc1->gets3()->getx_pt(); y13=parc1->gets3()->gety_pt();

xminT1=parc1->getxmin_t();   yminT1=parc1->getymin_t();

xmaxT1=parc1->getxmax_t();  ymaxT1=parc1->getymax_t();

double x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0;
x01=voisin->gets1()->getx_pt(); y01=voisin->gets1()->gety_pt();

x02=voisin->gets2()->getx_pt();  y02=voisin->gets2()->gety_pt();

x03=voisin->gets3()->getx_pt(); y03=voisin->gets3()->gety_pt();

xminT0=voisin->getxmin_t();   yminT0=voisin->getymin_t();

xmaxT0=voisin->getxmax_t();  ymaxT0=voisin->getymax_t();

double x_test, y_test;

voisin->setnbre_pts_triangle(0);
parc1->setnbre_pts_triangle(0);

for(int i=0; i<nbre_pts; i++)
{
x_test=liste_pts_triangle_BEY_tmp[i].p->getx();
y_test=liste_pts_triangle_BEY_tmp[i].p->gety();

		 if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0, x_test, y_test)==true)
		 {
			 voisin->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

		 else //if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1, x_test, y_test)==true)
		 {
			 parc1->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

}

//-----------------------------------------------------------------------------------------
		   voisin->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();

		   if(voisin->getfiltre()==false)
		   {
		   voisin->approximation_pts_triangle_plan_moindre_carre();
		   voisin->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   voisin->distance_max_pts_plan();
		   }

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   }

		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   liste_pts_triangle_BEY_tmp.clear();
//----------Fin Affectation des points du triangle initial aux trois (03) triangles créés------
return true;
}

//////////////////pt sur le segment 13 ----------------------------------------------------------------
else if(fabs(produit_s1s3_s1p)<=precision_calcul)
{
		   parc1=new triangle_initial_BEY();

		   parc1->gets1()->setx_pt(xinter);
		   parc1->gets1()->sety_pt(yinter);
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(voisin->gets2()->getx_pt());
		   parc1->gets2()->sety_pt(voisin->gets2()->gety_pt());
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(voisin->gets3()->getx_pt());
		   parc1->gets3()->sety_pt(voisin->gets3()->gety_pt());
		   parc1->gets3()->setz(0);

		   parc1->calculer_limites_triangle();

		   voisin->initialiser();

		   voisin->gets1()->setx_pt(voisin->gets1()->getx_pt());
		   voisin->gets1()->sety_pt(voisin->gets1()->gety_pt());
		   voisin->gets1()->setz(0);

		   voisin->gets2()->setx_pt(voisin->gets2()->getx_pt());
		   voisin->gets2()->sety_pt(voisin->gets2()->gety_pt());
		   voisin->gets2()->setz(0);

		   voisin->gets3()->setx_pt(xinter);
		   voisin->gets3()->sety_pt(yinter);
		   voisin->gets3()->setz(0);

		   xmin=min(voisin->gets1()->getx_pt(),min(voisin->gets2()->getx_pt(),voisin->gets3()->getx_pt()));
		   xmax=max(voisin->gets1()->getx_pt(),max(voisin->gets2()->getx_pt(),voisin->gets3()->getx_pt()));

		   ymin=min(voisin->gets1()->gety_pt(),min(voisin->gets2()->gety_pt(),voisin->gets3()->gety_pt()));
		   ymax=max(voisin->gets1()->gety_pt(),max(voisin->gets2()->gety_pt(),voisin->gets3()->gety_pt()));

		   voisin->setxmin_t(xmin);
		   voisin->setxmax_t(xmax);

		   voisin->setymin_t(ymin);
		   voisin->setymax_t(ymax);

double x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1;
x11=parc1->gets1()->getx_pt(); y11=parc1->gets1()->gety_pt();

x12=parc1->gets2()->getx_pt(); y12=parc1->gets2()->gety_pt();

x13=parc1->gets3()->getx_pt(); y13=parc1->gets3()->gety_pt();

xminT1=parc1->getxmin_t();   yminT1=parc1->getymin_t();

xmaxT1=parc1->getxmax_t();  ymaxT1=parc1->getymax_t();

double x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0;
x01=voisin->gets1()->getx_pt(); y01=voisin->gets1()->gety_pt();

x02=voisin->gets2()->getx_pt();  y02=voisin->gets2()->gety_pt();

x03=voisin->gets3()->getx_pt(); y03=voisin->gets3()->gety_pt();

xminT0=voisin->getxmin_t();   yminT0=voisin->getymin_t();

xmaxT0=voisin->getxmax_t();  ymaxT0=voisin->getymax_t();

double x_test, y_test;

voisin->setnbre_pts_triangle(0);
parc1->setnbre_pts_triangle(0);

for(int i=0; i<nbre_pts; i++)
{
x_test=liste_pts_triangle_BEY_tmp[i].p->getx();
y_test=liste_pts_triangle_BEY_tmp[i].p->gety();

		 if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0, x_test, y_test)==true)
		 {
			 voisin->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

		 else //if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1, x_test, y_test)==true)
		 {
			 parc1->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

}

//-----------------------------------------------------------------------------------------
		   voisin->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();

		   if(voisin->getfiltre()==false)
		   {
		   voisin->approximation_pts_triangle_plan_moindre_carre();
		   voisin->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   voisin->distance_max_pts_plan();
		   }

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   }

		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   liste_pts_triangle_BEY_tmp.clear();
return true;
}

//////////////////pt sur le segment 23 ----------------------------------------------------------------
else if(fabs(produit_s2s3_s2p)<=precision_calcul)
{
		   parc1=new triangle_initial_BEY();

		   parc1->gets1()->setx_pt(voisin->gets1()->getx_pt());
		   parc1->gets1()->sety_pt(voisin->gets1()->gety_pt());
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(xinter);
		   parc1->gets2()->sety_pt(yinter);
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(voisin->gets3()->getx_pt());
		   parc1->gets3()->sety_pt(voisin->gets3()->gety_pt());
		   parc1->gets3()->setz(0);

		   parc1->calculer_limites_triangle();

		   voisin->initialiser();

		   voisin->gets1()->setx_pt(voisin->gets1()->getx_pt());
		   voisin->gets1()->sety_pt(voisin->gets1()->gety_pt());
		   voisin->gets1()->setz(0);

		   voisin->gets2()->setx_pt(voisin->gets2()->getx_pt());
		   voisin->gets2()->sety_pt(voisin->gets2()->gety_pt());
		   voisin->gets2()->setz(0);

		   voisin->gets3()->setx_pt(xinter);
		   voisin->gets3()->sety_pt(yinter);
		   voisin->gets3()->setz(0);

		   xmin=min(voisin->gets1()->getx_pt(),min(voisin->gets2()->getx_pt(),voisin->gets3()->getx_pt()));
		   xmax=max(voisin->gets1()->getx_pt(),max(voisin->gets2()->getx_pt(),voisin->gets3()->getx_pt()));

		   ymin=min(voisin->gets1()->gety_pt(),min(voisin->gets2()->gety_pt(),voisin->gets3()->gety_pt()));
		   ymax=max(voisin->gets1()->gety_pt(),max(voisin->gets2()->gety_pt(),voisin->gets3()->gety_pt()));

		   voisin->setxmin_t(xmin);
		   voisin->setxmax_t(xmax);

		   voisin->setymin_t(ymin);
		   voisin->setymax_t(ymax);

double x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1;
x11=parc1->gets1()->getx_pt(); y11=parc1->gets1()->gety_pt();

x12=parc1->gets2()->getx_pt(); y12=parc1->gets2()->gety_pt();

x13=parc1->gets3()->getx_pt(); y13=parc1->gets3()->gety_pt();

xminT1=parc1->getxmin_t();   yminT1=parc1->getymin_t();

xmaxT1=parc1->getxmax_t();  ymaxT1=parc1->getymax_t();

double x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0;
x01=voisin->gets1()->getx_pt(); y01=voisin->gets1()->gety_pt();

x02=voisin->gets2()->getx_pt();  y02=voisin->gets2()->gety_pt();

x03=voisin->gets3()->getx_pt(); y03=voisin->gets3()->gety_pt();

xminT0=voisin->getxmin_t();   yminT0=voisin->getymin_t();

xmaxT0=voisin->getxmax_t();  ymaxT0=voisin->getymax_t();

double x_test, y_test;

voisin->setnbre_pts_triangle(0);
parc1->setnbre_pts_triangle(0);

for(int i=0; i<nbre_pts; i++)
{
x_test=liste_pts_triangle_BEY_tmp[i].p->getx();
y_test=liste_pts_triangle_BEY_tmp[i].p->gety();

		 if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0, x_test, y_test)==true)
		 {
			 voisin->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

		 else// if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1, x_test, y_test)==true)
		 {
			 parc1->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

}

//-----------------------------------------------------------------------------------------
		   voisin->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();

		   if(voisin->getfiltre()==false)
		   {
		   voisin->approximation_pts_triangle_plan_moindre_carre();
		   voisin->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   voisin->distance_max_pts_plan();
		   }

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   }

		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   liste_pts_triangle_BEY_tmp.clear();
//----------Fin Affectation des points du triangle initial aux trois (03) triangles créés------
return true;
}


}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool triangle_initial_BEY::creer_triangles(double xinter, double yinter, triangle_initial_BEY *voisin, ListTriangle_BEY_BEY *liste_triangle_adaptation_BEY) //BEY
{
if(voisin==NULL)return false;//BEY

if(voisin->getfiltre()==true)return false;//BEY

bool appartient;
triangle_initial_BEY *parc1;

appartient=voisin->appartence_pt_segments_triangle(xinter, yinter); //BEY

if(appartient==false)return false;

//------------------------------------------------------------------------------
int nbre_pts=voisin->getnbre_pts_triangle();

//------------------------------------------------------------------------------
double xs1=voisin->s1->x_pt;
double ys1=voisin->s1->y_pt;

double xs2=voisin->s2->x_pt;
double ys2=voisin->s2->y_pt;

double xs3=voisin->s3->x_pt;
double ys3=voisin->s3->y_pt;

//////////////////pt sur le segment 12 ----------------------------------------------------------------
double L12=sqrt(pow(xs2-xs1,2)+pow(ys2-ys1,2));

double L12_p=sqrt(pow(xs2-xinter,2)+pow(ys2-yinter,2))
			+sqrt(pow(xs1-xinter,2)+pow(ys1-yinter,2));

bool seg12=fabs(L12-L12_p)<=1e-6;

if(seg12==true)
{
		   parc1=new triangle_initial_BEY();
		   parc1->affecter_coordonnees_sommets_triangle(xinter, yinter, 0, xs2, ys2, 0, xs3, ys3, 0);

		   triangle_initial_BEY *parc_new_voisin=new triangle_initial_BEY();
		   parc_new_voisin->affecter_coordonnees_sommets_triangle(xs1, ys1, 0, xinter, yinter, 0, xs3, ys3, 0);

double p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y;
parc_new_voisin->calculer_deltaX_deltaY_deltaZ(p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y);

double p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy;
parc1->calculer_deltaX_deltaY_deltaZ(p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy);

double x_test, y_test;

for(int i=0; i<nbre_pts; i++)
{
//------------------------------------------------------------------------------
x_test=voisin->liste_pts_triangle_BEY[i].p->x;
y_test=voisin->liste_pts_triangle_BEY[i].p->y;
//------------------------------------------------------------------------------
		 if(parc_new_voisin->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y)==true)
			 {
			 parc_new_voisin->ajouter_pt(voisin->liste_pts_triangle_BEY[i]);
			 }

		 else if(parc1->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy)==true)
			 {
			 parc1->ajouter_pt(voisin->liste_pts_triangle_BEY[i]);
			 }
}

//-----------------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		   parc_new_voisin->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();

		   if(parc_new_voisin->getfiltre()==false)
		   {
		   parc_new_voisin->approximation_pts_triangle_plan_moindre_carre();
		   parc_new_voisin->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   parc_new_voisin->distance_max_pts_plan();
		   parc_new_voisin->setnouveau_triangle(false);//BEY
		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc_new_voisin);
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(parc_new_voisin); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(parc_new_voisin); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }
		   else
			 Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc_new_voisin);

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   parc1->setnouveau_triangle(false);//BEY
		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }
		   else
			 Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc1);

return true;
}

//////////////////pt sur le segment 13 ----------------------------------------------------------------
double L13=sqrt(pow(xs3-xs1,2)+pow(ys3-ys1,2));

double L13_p=sqrt(pow(xs3-xinter,2)+pow(ys3-yinter,2))
			+sqrt(pow(xs1-xinter,2)+pow(ys1-yinter,2));

bool seg13=fabs(L13-L13_p)<=1e-6;

if(seg13==true)
{
		   parc1=new triangle_initial_BEY();
		   parc1->affecter_coordonnees_sommets_triangle(xinter, yinter, 0, xs2, ys2, 0, xs3, ys3, 0);

		   triangle_initial_BEY *parc_new_voisin=new triangle_initial_BEY();
		   parc_new_voisin->affecter_coordonnees_sommets_triangle(xs1, ys1, 0, xs2, ys2, 0, xinter, yinter, 0);

double p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y;
parc_new_voisin->calculer_deltaX_deltaY_deltaZ(p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y);

double p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy;
parc1->calculer_deltaX_deltaY_deltaZ(p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy);

double x_test, y_test;

for(int i=0; i<nbre_pts; i++)
{
x_test=voisin->liste_pts_triangle_BEY[i].p->x;
y_test=voisin->liste_pts_triangle_BEY[i].p->y;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		 if(parc_new_voisin->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y)==true)
			 {
			 parc_new_voisin->ajouter_pt(voisin->liste_pts_triangle_BEY[i]);
			 }

		 else if(parc1->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy)==true)
			 {
			 parc1->ajouter_pt(voisin->liste_pts_triangle_BEY[i]);
			 }
}

//-----------------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		   parc_new_voisin->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();

		   if(parc_new_voisin->getfiltre()==false)
		   {
		   parc_new_voisin->approximation_pts_triangle_plan_moindre_carre();
		   parc_new_voisin->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   parc_new_voisin->distance_max_pts_plan();
		   parc_new_voisin->setnouveau_triangle(false);//BEY
		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc_new_voisin);
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(parc_new_voisin); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(parc_new_voisin); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }
		   else
			 Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc_new_voisin);

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   parc1->setnouveau_triangle(false);//BEY
		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }
		   else
			 Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc1);

return true;
}

//////////////////pt sur le segment 23 ----------------------------------------------------------------
double L23=sqrt(pow(xs3-xs2,2)+pow(ys3-ys2,2));

double L23_p=sqrt(pow(xs3-xinter,2)+pow(ys3-yinter,2))
			+sqrt(pow(xs2-xinter,2)+pow(ys2-yinter,2));

bool seg23=fabs(L23-L23_p)<=1e-6;

if(seg23==true)
{
		   parc1=new triangle_initial_BEY();
		   parc1->affecter_coordonnees_sommets_triangle(xs1, ys1, 0, xinter, yinter, 0, xs3, ys3, 0);

		   triangle_initial_BEY *parc_new_voisin=new triangle_initial_BEY();
		   parc_new_voisin->affecter_coordonnees_sommets_triangle(xs1, ys1, 0, xs2, ys2, 0, xinter, yinter, 0);

double p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y;
parc_new_voisin->calculer_deltaX_deltaY_deltaZ(p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y);

double p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy;
parc1->calculer_deltaX_deltaY_deltaZ(p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy);

double x_test, y_test;

for(int i=0; i<nbre_pts; i++)
{
x_test=voisin->liste_pts_triangle_BEY[i].p->x;
y_test=voisin->liste_pts_triangle_BEY[i].p->y;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		 if(parc_new_voisin->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y)==true)
			 {
			 parc_new_voisin->ajouter_pt(voisin->liste_pts_triangle_BEY[i]);
			 }

		 else if(parc1->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy)==true)
			 {
			 parc1->ajouter_pt(voisin->liste_pts_triangle_BEY[i]);
			 }
}
//-----------------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		   parc_new_voisin->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();

		   if(parc_new_voisin->getfiltre()==false)
		   {
		   parc_new_voisin->approximation_pts_triangle_plan_moindre_carre();
		   parc_new_voisin->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   parc_new_voisin->distance_max_pts_plan();
		   parc_new_voisin->setnouveau_triangle(false);//BEY
		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc_new_voisin);
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(parc_new_voisin); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(parc_new_voisin); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }
		   else
			 Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc_new_voisin);

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   parc1->setnouveau_triangle(false);//BEY
		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }
		   else
			 Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc1);

return true;
}

}

//---------------------------------------------------------------------------
void TAdaptive_Triangulation::subdiviser_triangles_voisins(triangle_initial_BEY *parc)
{
if( Adaptive_Triangulation->creer_triangles(parc->getx1_inter(), parc->gety1_inter(), parc->getv1())==false)
	if(Adaptive_Triangulation->creer_triangles(parc->getx1_inter(), parc->gety1_inter(), parc->getv2())==false)
		Adaptive_Triangulation->creer_triangles(parc->getx1_inter(), parc->gety1_inter(), parc->getv3());

if(Adaptive_Triangulation->creer_triangles(parc->getx2_inter(), parc->gety2_inter(), parc->getv1())==false)
	if(Adaptive_Triangulation->creer_triangles(parc->getx2_inter(), parc->gety2_inter(), parc->getv2())==false)
		Adaptive_Triangulation->creer_triangles(parc->getx2_inter(), parc->gety2_inter(), parc->getv3());


}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void triangle_initial_BEY::subdiviser_triangles_voisins(ListTriangle_BEY_BEY *liste_triangle_adaptation_BEY)
{
Adaptive_Triangulation->voisin_1_supprime=false;
Adaptive_Triangulation->voisin_2_supprime=false;
Adaptive_Triangulation->voisin_3_supprime=false;

if(creer_triangles(x1_inter, y1_inter, v1, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_1_supprime=true;
if(creer_triangles(x1_inter, y1_inter, v2, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_2_supprime=true;
if(creer_triangles(x1_inter, y1_inter, v3, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_3_supprime=true;

if(creer_triangles(x2_inter, y2_inter, v1, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_1_supprime=true;
if(creer_triangles(x2_inter, y2_inter, v2, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_2_supprime=true;
if(creer_triangles(x2_inter, y2_inter, v3, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_3_supprime=true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void triangle_initial_BEY::subdiviser_triangles_voisins_NEW(ListTriangle_BEY_BEY *liste_triangle_adaptation_BEY, triangle_initial_BEY *V1, triangle_initial_BEY *V2, triangle_initial_BEY *V3)
{
Adaptive_Triangulation->voisin_1_supprime=false;
Adaptive_Triangulation->voisin_2_supprime=false;
Adaptive_Triangulation->voisin_3_supprime=false;

	  if(creer_triangles(x1_inter, y1_inter, V1, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_1_supprime=true;
 else if(creer_triangles(x1_inter, y1_inter, V2, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_2_supprime=true;
 else if(creer_triangles(x1_inter, y1_inter, V3, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_3_supprime=true;


      if(creer_triangles(x2_inter, y2_inter, V1, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_1_supprime=true;
 else if(creer_triangles(x2_inter, y2_inter, V2, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_2_supprime=true;
 else if(creer_triangles(x2_inter, y2_inter, V3, liste_triangle_adaptation_BEY)==true)Adaptive_Triangulation->voisin_3_supprime=true;
}
//---------------------------------------------------------------------------
void TAdaptive_Triangulation::voisins_a_modifier(triangle_initial_BEY *parc)
{
   parc->setcalcul_voisins(false);

   //*******voisins de parc
   if(parc->getv1()!=NULL)parc->getv1()->setcalcul_voisins(false);
   if(parc->getv2()!=NULL)parc->getv2()->setcalcul_voisins(false);
   if(parc->getv3()!=NULL)parc->getv3()->setcalcul_voisins(false);

   //*******voisins du voisin v1
   if(parc->getv1()!=NULL)
   {
   if(parc->getv1()->getv1()!=NULL)parc->getv1()->getv1()->setcalcul_voisins(false);
   if(parc->getv1()->getv2()!=NULL)parc->getv1()->getv2()->setcalcul_voisins(false);
   if(parc->getv1()->getv3()!=NULL)parc->getv1()->getv3()->setcalcul_voisins(false);
   }

   //*******voisins du voisin v2
   if(parc->getv2()!=NULL)
   {
   if(parc->getv2()->getv1()!=NULL)parc->getv2()->getv1()->setcalcul_voisins(false);
   if(parc->getv2()->getv2()!=NULL)parc->getv2()->getv2()->setcalcul_voisins(false);
   if(parc->getv2()->getv3()!=NULL)parc->getv2()->getv3()->setcalcul_voisins(false);
   }

   //*******voisins du voisin v3
   if(parc->getv3()!=NULL)
   {
   if(parc->getv3()->getv1()!=NULL)parc->getv3()->getv1()->setcalcul_voisins(false);
   if(parc->getv3()->getv2()!=NULL)parc->getv3()->getv2()->setcalcul_voisins(false);
   if(parc->getv3()->getv3()!=NULL)parc->getv3()->getv3()->setcalcul_voisins(false);
   }

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void triangle_initial_BEY::voisins_a_modifier_BEY()
{
calcul_voisins=false;

triangle_initial_BEY *v1_getv1, *v1_getv2, *v1_getv3;
triangle_initial_BEY *v2_getv1, *v2_getv2, *v2_getv3;
triangle_initial_BEY *v3_getv1, *v3_getv2, *v3_getv3;

   if(v1!=NULL)   //OK
   {
   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(v1); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;

//------------------------------------------------------------
   v1_getv1=v1->v1;
   v1_getv2=v1->v2;
   v1_getv3=v1->v3;

	   if(v1_getv1!=NULL) //OK
	   {
	   if(v1_getv1!=this)
			{Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(v1_getv1); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;}
	   }

	   if(v1_getv2!=NULL) //OK
	   {
	   if(v1_getv2!=this)
			{Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(v1_getv2); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;}
	   }

	   if(v1_getv3!=NULL) //OK
	   {
	   if(v1_getv3!=this)
			{Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(v1_getv3); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;}
	   }

//------------------------------------------------------------
   }

//------------------------------------------------------------
   if(v2!=NULL) //OK
   {
   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(v2); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
   //*******voisins du voisin v2
//------------------------------------------------------------
   v2_getv1=v2->v1;
   v2_getv2=v2->v2;
   v2_getv3=v2->v3;

	   if(v2_getv1!=NULL)  //OK
	   {
	   if(v2_getv1!=this)
			{Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(v2_getv1); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;}
	   }

	   if(v2_getv2!=NULL) //OK
	   {
	   if(v2_getv2!=this)
			{Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(v2_getv2); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;}
	   }

	   if(v2_getv3!=NULL)  //OK
	   {
	   if(v2_getv3!=this)
			{Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(v2_getv3); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;}
	   }

//------------------------------------------------------------
   }

   if(v3!=NULL)  //OK
   {
   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(v3); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
//------------------------------------------------------------------------------
   //*******voisins du voisin v3
   v3_getv1=v3->v1;
   v3_getv2=v3->v2;
   v3_getv3=v3->v3;

	   if(v3_getv1!=NULL) //OK
	   {
	   if(v3_getv1!=this)
			{Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(v3_getv1); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;}
	   }

	   if(v3_getv2!=NULL) //OK
	   {
	   if(v3_getv2!=this)
			{Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(v3_getv2); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;}
	   }

	   if(v3_getv3!=NULL) //OK
	   {
	   if(v3_getv3!=this)
			{Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(v3_getv3); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;}
	   }
//------------------------------------------------------------------------------
   }

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void triangle_initial_BEY::voisins_a_modifier()
{
   calcul_voisins=false;

   //*******voisins de parc
   if(v1!=NULL){v1->setcalcul_voisins(false); /*Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(v1);Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;*/}
   if(v2!=NULL){v2->setcalcul_voisins(false); /*Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(v2);Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;*/}
   if(v3!=NULL){v3->setcalcul_voisins(false); /*Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(v3);Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;*/}

   //*******voisins du voisin v1
   if(v1!=NULL)
   {
   if(v1->getv1()!=NULL){v1->getv1()->setcalcul_voisins(false); /*Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(v1->getv1());Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;*/}
   if(v1->getv2()!=NULL){v1->getv2()->setcalcul_voisins(false); /*Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(v1->getv2());Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;*/}
   if(v1->getv3()!=NULL){v1->getv3()->setcalcul_voisins(false); /*Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(v1->getv3());Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;*/}
   }

   //*******voisins du voisin v2
   if(v2!=NULL)
   {
   if(v2->getv1()!=NULL){v2->getv1()->setcalcul_voisins(false); /*Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(v2->getv1());Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;*/}
   if(v2->getv2()!=NULL){v2->getv2()->setcalcul_voisins(false); /*Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(v2->getv2());Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;*/}
   if(v2->getv3()!=NULL){v2->getv3()->setcalcul_voisins(false); /*Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(v2->getv3());Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;*/}
   }

   //*******voisins du voisin v3
   if(v3!=NULL)
   {
   if(v3->getv1()!=NULL){v3->getv1()->setcalcul_voisins(false); /*Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(v3->getv1());*/}
   if(v3->getv2()!=NULL){v3->getv2()->setcalcul_voisins(false); /*Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(v3->getv2());*/}
   if(v3->getv3()!=NULL){v3->getv3()->setcalcul_voisins(false); /*Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(v3->getv3());*/}
   }
}
//---------------------------------------------------------------------------
void TAdaptive_Triangulation::subdivision_sommet_1_null(triangle_initial_BEY *parc, double x_centre, double y_centre,
										  double x1_inter, double y1_inter, double x2_inter, double y2_inter,
//										  double x_p1, double y_p1, double x_p2, double y_p2)
										  double x_p3, double y_p3, double x_p2, double y_p2)
{
liste_pts_triangle_BEY_tmp.clear();
int nbre_pts=parc->getnbre_pts_triangle();
for(int i=0; i<nbre_pts; i++)
{
   liste_pts_triangle_BEY_tmp.push_back(parc->liste_pts_triangle_BEY[i]);
}

		   double xmin, xmax, ymin, ymax;
		   triangle_initial_BEY *parc1, *parc2;

		   parc1=new triangle_initial_BEY();

		   parc1->gets1()->setx_pt(x1_inter);
		   parc1->gets1()->sety_pt(y1_inter);
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(x_p2);
		   parc1->gets2()->sety_pt(y_p2);
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(x_p3);
		   parc1->gets3()->sety_pt(y_p3);
		   parc1->gets3()->setz(0);

		   parc1->calculer_limites_triangle();

//------------------------------------------------------------------------------

		   parc2=new triangle_initial_BEY();

		   parc2->gets1()->setx_pt(x1_inter);
		   parc2->gets1()->sety_pt(y1_inter);
		   parc2->gets1()->setz(0);

		   parc2->gets2()->setx_pt(x2_inter);
		   parc2->gets2()->sety_pt(y2_inter);
		   parc2->gets2()->setz(0);

		   parc2->gets3()->setx_pt(x_p2);
		   parc2->gets3()->sety_pt(y_p2);
		   parc2->gets3()->setz(0);

		   parc2->calculer_limites_triangle();

		   parc->initialiser();

		   parc->gets1()->setx_pt(x_centre);
		   parc->gets1()->sety_pt(y_centre);
		   parc->gets1()->setz(0);

		   parc->gets2()->setx_pt(x1_inter);
		   parc->gets2()->sety_pt(y1_inter);
		   parc->gets2()->setz(0);

		   parc->gets3()->setx_pt(x2_inter);
		   parc->gets3()->sety_pt(y2_inter);
		   parc->gets3()->setz(0);

		   xmin=min(parc->gets1()->getx_pt(),min(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));
		   xmax=max(parc->gets1()->getx_pt(),max(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));

		   ymin=min(parc->gets1()->gety_pt(),min(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));
		   ymax=max(parc->gets1()->gety_pt(),max(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));

		   parc->setxmin_t(xmin);
		   parc->setxmax_t(xmax);

		   parc->setymin_t(ymin);
		   parc->setymax_t(ymax);

double x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1;
x11=parc1->gets1()->getx_pt();
y11=parc1->gets1()->gety_pt();

x12=parc1->gets2()->getx_pt();
y12=parc1->gets2()->gety_pt();

x13=parc1->gets3()->getx_pt();
y13=parc1->gets3()->gety_pt();

xminT1=parc1->getxmin_t();
yminT1=parc1->getymin_t();

xmaxT1=parc1->getxmax_t();
ymaxT1=parc1->getymax_t();

//-----------Paramètres du triangle par2--------------
double x21, y21, x22, y22, x23, y23, xminT2, yminT2, xmaxT2, ymaxT2;
x21=parc2->gets1()->getx_pt();
y21=parc2->gets1()->gety_pt();

x22=parc2->gets2()->getx_pt();
y22=parc2->gets2()->gety_pt();

x23=parc2->gets3()->getx_pt();
y23=parc2->gets3()->gety_pt();

xminT2=parc2->getxmin_t();
yminT2=parc2->getymin_t();

xmaxT2=parc2->getxmax_t();
ymaxT2=parc2->getymax_t();

//-----------Paramètres du triangle par--------------
double x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0;
x01=parc->gets1()->getx_pt();
y01=parc->gets1()->gety_pt();

x02=parc->gets2()->getx_pt();
y02=parc->gets2()->gety_pt();

x03=parc->gets3()->getx_pt();
y03=parc->gets3()->gety_pt();

xminT0=parc->getxmin_t();
yminT0=parc->getymin_t();

xmaxT0=parc->getxmax_t();
ymaxT0=parc->getymax_t();


double x_test, y_test;

parc->setnbre_pts_triangle(0);
parc1->setnbre_pts_triangle(0);
parc2->setnbre_pts_triangle(0);

for(int i=0; i<nbre_pts; i++)
{
x_test=liste_pts_triangle_BEY_tmp[i].p->getx();
y_test=liste_pts_triangle_BEY_tmp[i].p->gety();

		 if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x01, y01, x02, y02, x03, y03, xminT0, yminT0, xmaxT0, ymaxT0, x_test, y_test)==true)
		 {
			 parc->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

		 else if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x11, y11, x12, y12, x13, y13, xminT1, yminT1, xmaxT1, ymaxT1, x_test, y_test)==true)
		 {
			 parc1->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }

		 else //if(Adaptive_Triangulation->appartence_pt_triangle_BEY(x21, y21, x22, y22, x23, y23, xminT2, yminT2, xmaxT2, ymaxT2, x_test, y_test)==true)
		 {
			 parc2->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
		 }


}

		   parc->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();
		   parc2->filtrage_un_triangle();

		   if(parc->getfiltre()==false)
		   {
		   parc->approximation_pts_triangle_plan_moindre_carre();
		   parc->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   parc->distance_max_pts_plan();
		   }

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   }

		   if(parc2->getfiltre()==false)
		   {
		   parc2->approximation_pts_triangle_plan_moindre_carre();
		   parc2->determiner_pts_proches_sommets_triangle(rapport, aire_min_triangle);
		   parc2->distance_max_pts_plan();
		   }

		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc2);
		   liste_pts_triangle_BEY_tmp.clear();

}

//---------------------------------------------------------------------------
void triangle_initial_BEY::calculer_limites_triangle()
{
	  double s1_xpt=s1->getx_pt();
	  double s1_ypt=s1->gety_pt();

	  double s2_xpt=s2->getx_pt();
	  double s2_ypt=s2->gety_pt();

	  double s3_xpt=s3->getx_pt();
	  double s3_ypt=s3->gety_pt();

	  xmin_t=min(s1_xpt,min(s2_xpt,s3_xpt)) -0.01;
	  xmax_t=max(s1_xpt,max(s2_xpt,s3_xpt)) +0.01;

	  ymin_t=min(s1_ypt,min(s2_ypt,s3_ypt)) -0.01;
	  ymax_t=max(s1_ypt,max(s2_ypt,s3_ypt)) +0.01;

	  double x12= s1_xpt- s2_xpt;
	  double y12= s1_ypt- s2_ypt;
	  double A=sqrt(x12*x12+y12*y12);

	  double x23= s3_xpt- s2_xpt;
	  double y23= s3_ypt- s2_ypt;
	  double B=sqrt(x23*x23+y23*y23);

	  double x31= s1_xpt- s3_xpt;
	  double y31= s1_ypt- s3_ypt;
	  double C=sqrt(x31*x31+y31*y31);

	  double P=(A+B+C)/2;

	  if(fabs(P-A)<=1e-6)P=A;
	  else if(fabs(P-B)<=1e-6)P=B;
	  else if(fabs(P-C)<=1e-6)P=C;

	  aire_triangle_2D=sqrt(P*(P-A)*(P-B)*(P-C));
}
//---------------------------------------------------------------------------
void triangle_initial_BEY::subdivision_sommet_1_null(double x_centre, double y_centre,
										  double x1_inter, double y1_inter, double x2_inter, double y2_inter,
//										  double x_p1, double y_p1, double x_p2, double y_p2)
										  double x_p3, double y_p3, double x_p2, double y_p2, ListTriangle_BEY_BEY *liste_triangle_adaptation_BEY)
{
int nbre_pts=this->getnbre_pts_triangle();

//------------------------------------------------------------------------------
point_nuage_BEY *liste_pts_triangle_BEY_tmp;

liste_pts_triangle_BEY_tmp= new point_nuage_BEY [nbre_pts] ;

for(int i=0; i<nbre_pts; i++)
   liste_pts_triangle_BEY_tmp[i]=liste_pts_triangle_BEY[i];
//------------------------------------------------------------------------------

		   triangle_initial_BEY *parc1, *parc2;

//------------------------------------------------------------------------------

//1er nouveau triangle
		   parc1=new triangle_initial_BEY();
		   parc1->affecter_coordonnees_sommets_triangle(x1_inter, y1_inter, 0, x_p2, y_p2, 0, x_p3, y_p3, 0);

//------------------------------------------------------------------------------
//2ème nouveau triangle
		   parc2=new triangle_initial_BEY();
		   parc2->affecter_coordonnees_sommets_triangle(x1_inter, y1_inter, 0, x2_inter, y2_inter, 0, x_p2, y_p2, 0);

//nouveaux paramètres du triangle parc
		   this->initialiser();
		   this->affecter_coordonnees_sommets_triangle(x_centre, y_centre, 0, x1_inter, y1_inter, 0, x2_inter, y2_inter, 0);

//------------------------------------------------------------------------------

double x_test, y_test;

double p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y;
double p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy;
double p1p2_xxx, p1p2_yyy, p1p3_xxx, p1p3_yyy, p2p3_xxx, p2p3_yyy;

this->calculer_deltaX_deltaY_deltaZ(p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y);
parc1->calculer_deltaX_deltaY_deltaZ(p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy);
parc2->calculer_deltaX_deltaY_deltaZ(p1p2_xxx, p1p2_yyy, p1p3_xxx, p1p3_yyy, p2p3_xxx, p2p3_yyy);

for(int i=0; i<nbre_pts; i++)
{
//------------------------------------------------------------------------------
x_test=liste_pts_triangle_BEY_tmp[i].p->x;
y_test=liste_pts_triangle_BEY_tmp[i].p->y;
//------------------------------------------------------------------------------

		 if(this->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_x, p1p2_y, p1p3_x, p1p3_y, p2p3_x, p2p3_y)==true)
			 {
			 this->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
			 }
		 if(parc1->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_xx, p1p2_yy, p1p3_xx, p1p3_yy, p2p3_xx, p2p3_yy)==true)
			 {
			 parc1->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
			 }
		 else if(parc2->appartenance_pt_triangle_BEY(x_test, y_test, p1p2_xxx, p1p2_yyy, p1p3_xxx, p1p3_yyy, p2p3_xxx, p2p3_yyy)==true)
			 {
			 parc2->ajouter_pt(liste_pts_triangle_BEY_tmp[i]);
			 }

}

//-----------------------------------------------------------------------------------------

//------------------------------------------------------------------------------
		   this->filtrage_un_triangle();
		   parc1->filtrage_un_triangle();
		   parc2->filtrage_un_triangle();

		   if(this->getfiltre()==false)
		   {
		   this->approximation_pts_triangle_plan_moindre_carre();
		   this->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   this->distance_max_pts_plan();
		   this->setnouveau_triangle(false);//BEY
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(this); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(this); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }

		   if(parc1->getfiltre()==false)
		   {
		   parc1->approximation_pts_triangle_plan_moindre_carre();
		   parc1->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   parc1->distance_max_pts_plan();
		   parc1->setnouveau_triangle(false);//BEY
		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc1);
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(parc1); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }
		   else
			 Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc1);

		   if(parc2->getfiltre()==false)
		   {
		   parc2->approximation_pts_triangle_plan_moindre_carre();
		   parc2->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
		   parc2->distance_max_pts_plan();
		   parc2->setnouveau_triangle(false);//BEY
		   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc2);
		   Adaptive_Triangulation->Triangles_Recherche_Voisins.push_back(parc2); Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins++;
		   Adaptive_Triangulation->Triangles_A_Calculer_Voisins.push_back(parc2); Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins++;
		   }
		   else
			 Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc2);

		   delete [] liste_pts_triangle_BEY_tmp;
}

//---------------------------------------------------------------------------
void TAdaptive_Triangulation::subdivision_centre_gravite(triangle_initial *parc)
{
noeud_point_nuage_BEY *parcP1=parc->getliste_pts_triangle()->getdebut();
while(parcP1!=NULL)
{
parcP1->setinserer_pt_triangle(false);
parcP1=parcP1->getsuiv2();
}
		   double xmin, xmax, ymin, ymax;
		   triangle_initial *parc1;

		   double x_centre=(parc->gets1()->getx_pt() + parc->gets2()->getx_pt() + parc->gets3()->getx_pt())/3;
		   double y_centre=(parc->gets1()->gety_pt() + parc->gets2()->gety_pt() + parc->gets3()->gety_pt())/3;

		   parc1=new triangle_initial();

		   parc1->gets1()->setx_pt(parc->gets1()->getx_pt());
		   parc1->gets1()->sety_pt(parc->gets1()->gety_pt());
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(parc->gets2()->getx_pt());
		   parc1->gets2()->sety_pt(parc->gets2()->gety_pt());
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(x_centre);
		   parc1->gets3()->sety_pt(y_centre);
		   parc1->gets3()->setz(0);

		   xmin=min(parc1->gets1()->getx_pt(),min(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));
		   xmax=max(parc1->gets1()->getx_pt(),max(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));

		   ymin=min(parc1->gets1()->gety_pt(),min(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));
		   ymax=max(parc1->gets1()->gety_pt(),max(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));

		   parc1->setxmin_t(xmin);
		   parc1->setxmax_t(xmax);

		   parc1->setymin_t(ymin);
		   parc1->setymax_t(ymax);

		   Point_Clouds_Import->liste_triangle_adaptation->ajouter_Triangle(parc1);
//------------------------------------------------------------------------------

		   parc1=new triangle_initial();

		   parc1->gets1()->setx_pt(parc->gets2()->getx_pt());
		   parc1->gets1()->sety_pt(parc->gets2()->gety_pt());
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(parc->gets3()->getx_pt());
		   parc1->gets2()->sety_pt(parc->gets3()->gety_pt());
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(x_centre);
		   parc1->gets3()->sety_pt(y_centre);
		   parc1->gets3()->setz(0);

		   xmin=min(parc1->gets1()->getx_pt(),min(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));
		   xmax=max(parc1->gets1()->getx_pt(),max(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));

		   ymin=min(parc1->gets1()->gety_pt(),min(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));
		   ymax=max(parc1->gets1()->gety_pt(),max(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));

		   parc1->setxmin_t(xmin);
		   parc1->setxmax_t(xmax);

		   parc1->setymin_t(ymin);
		   parc1->setymax_t(ymax);

		   Point_Clouds_Import->liste_triangle_adaptation->ajouter_Triangle(parc1);

		   parc->intialiser();

		   parc->gets1()->setx_pt(parc->gets1()->getx_pt());
		   parc->gets1()->sety_pt(parc->gets1()->gety_pt());
		   parc->gets1()->setz(0);

		   parc->gets3()->setx_pt(parc->gets3()->getx_pt());
		   parc->gets3()->sety_pt(parc->gets3()->gety_pt());
		   parc->gets3()->setz(0);

		   parc->gets2()->setx_pt(x_centre);
		   parc->gets2()->sety_pt(y_centre);
		   parc->gets2()->setz(0);

		   xmin=min(parc->gets1()->getx_pt(),min(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));
		   xmax=max(parc->gets1()->getx_pt(),max(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));

		   ymin=min(parc->gets1()->gety_pt(),min(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));
		   ymax=max(parc->gets1()->gety_pt(),max(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));

		   parc->setxmin_t(xmin);
		   parc->setxmax_t(xmax);

		   parc->setymin_t(ymin);
		   parc->setymax_t(ymax);
//-------------------------------------------------------------------
}
//---------------------------------------------------------------------------
void TAdaptive_Triangulation::subdivision_quatre_triangles(double &x12_milieu, double &y12_milieu, double &x23_milieu, double &y23_milieu, double &x13_milieu, double &y13_milieu, triangle_initial *parc)
{
noeud_point_nuage_BEY *parcP1=parc->getliste_pts_triangle()->getdebut();
while(parcP1!=NULL)
{
parcP1->setinserer_pt_triangle(false);
parcP1=parcP1->getsuiv2();
}

		   double xmin, xmax, ymin, ymax;
		   triangle_initial *parc1;

		   x12_milieu=(parc->gets1()->getx_pt() + parc->gets2()->getx_pt())/2;
		   y12_milieu=(parc->gets1()->gety_pt() + parc->gets2()->gety_pt())/2;

		   x23_milieu=(parc->gets3()->getx_pt() + parc->gets2()->getx_pt())/2;
		   y23_milieu=(parc->gets3()->gety_pt() + parc->gets2()->gety_pt())/2;

		   x13_milieu=(parc->gets1()->getx_pt() + parc->gets3()->getx_pt())/2;
		   y13_milieu=(parc->gets1()->gety_pt() + parc->gets3()->gety_pt())/2;


		   parc1=new triangle_initial();

		   parc1->gets1()->setx_pt(parc->gets1()->getx_pt());
		   parc1->gets1()->sety_pt(parc->gets1()->gety_pt());
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(x12_milieu);
		   parc1->gets2()->sety_pt(y12_milieu);
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(x13_milieu);
		   parc1->gets3()->sety_pt(y13_milieu);
		   parc1->gets3()->setz(0);

		   xmin=min(parc1->gets1()->getx_pt(),min(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));
		   xmax=max(parc1->gets1()->getx_pt(),max(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));

		   ymin=min(parc1->gets1()->gety_pt(),min(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));
		   ymax=max(parc1->gets1()->gety_pt(),max(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));

		   parc1->setxmin_t(xmin);
		   parc1->setxmax_t(xmax);

		   parc1->setymin_t(ymin);
		   parc1->setymax_t(ymax);

		   Point_Clouds_Import->liste_triangle_adaptation->ajouter_Triangle(parc1);
//------------------------------------------------------------------------------

		   parc1=new triangle_initial();

		   parc1->gets1()->setx_pt(x12_milieu);
		   parc1->gets1()->sety_pt(y12_milieu);
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(parc->gets2()->getx_pt());
		   parc1->gets2()->sety_pt(parc->gets2()->gety_pt());
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(x23_milieu);
		   parc1->gets3()->sety_pt(y23_milieu);
		   parc1->gets3()->setz(0);

		   xmin=min(parc1->gets1()->getx_pt(),min(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));
		   xmax=max(parc1->gets1()->getx_pt(),max(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));

		   ymin=min(parc1->gets1()->gety_pt(),min(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));
		   ymax=max(parc1->gets1()->gety_pt(),max(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));

		   parc1->setxmin_t(xmin);
		   parc1->setxmax_t(xmax);

		   parc1->setymin_t(ymin);
		   parc1->setymax_t(ymax);

		   Point_Clouds_Import->liste_triangle_adaptation->ajouter_Triangle(parc1);

//------------------------------------------------------------------------------

		   parc1=new triangle_initial();

		   parc1->gets1()->setx_pt(x13_milieu);
		   parc1->gets1()->sety_pt(y13_milieu);
		   parc1->gets1()->setz(0);

		   parc1->gets2()->setx_pt(x23_milieu);
		   parc1->gets2()->sety_pt(y23_milieu);
		   parc1->gets2()->setz(0);

		   parc1->gets3()->setx_pt(parc->gets3()->getx_pt());
		   parc1->gets3()->sety_pt(parc->gets3()->gety_pt());
		   parc1->gets3()->setz(0);

		   xmin=min(parc1->gets1()->getx_pt(),min(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));
		   xmax=max(parc1->gets1()->getx_pt(),max(parc1->gets2()->getx_pt(),parc1->gets3()->getx_pt()));

		   ymin=min(parc1->gets1()->gety_pt(),min(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));
		   ymax=max(parc1->gets1()->gety_pt(),max(parc1->gets2()->gety_pt(),parc1->gets3()->gety_pt()));

		   parc1->setxmin_t(xmin);
		   parc1->setxmax_t(xmax);

		   parc1->setymin_t(ymin);
		   parc1->setymax_t(ymax);

		   Point_Clouds_Import->liste_triangle_adaptation->ajouter_Triangle(parc1);

		   parc->intialiser();

		   parc->gets1()->setx_pt(x12_milieu);
		   parc->gets1()->sety_pt(y12_milieu);
		   parc->gets1()->setz(0);

		   parc->gets3()->setx_pt(x23_milieu);
		   parc->gets3()->sety_pt(y23_milieu);
		   parc->gets3()->setz(0);

		   parc->gets2()->setx_pt(x13_milieu);
		   parc->gets2()->sety_pt(y13_milieu);
		   parc->gets2()->setz(0);

		   xmin=min(parc->gets1()->getx_pt(),min(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));
		   xmax=max(parc->gets1()->getx_pt(),max(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));

		   ymin=min(parc->gets1()->gety_pt(),min(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));
		   ymax=max(parc->gets1()->gety_pt(),max(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));

		   parc->setxmin_t(xmin);
		   parc->setxmax_t(xmax);

		   parc->setymin_t(ymin);
		   parc->setymax_t(ymax);
//-------------------------------------------------------------------
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void ListTriangle_BEY::liberer_liste_pts_triangles()
{

triangle_initial *parc=tete;

while(parc!=NULL)
{
parc->initialiser_liste_pts_triangles();
parc=parc->getsuiv();
}

}
//---------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::liberer_liste_pts_triangles()
{

triangle_initial_BEY *parc=tete;

while(parc!=NULL)
{
parc->initialiser_liste_pts_triangles();
parc=parc->getsuiv();
}

}

//---------------------------------------------------------------------------
void __fastcall TAdaptive_Triangulation::Button12Click(TObject *Sender)
{
double xmin, xmax, ymin, ymax;

triangle_initial *parc=Point_Clouds_Import->liste_triangle_adaptation->gettete();

while(parc!=NULL)
{
if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}
if(!(parc->getdensite_p1()!=0 && (parc->getdensite_p2()==0 && parc->getdensite_p3()==0)))
	 {parc=parc->getsuiv(); continue;}

	 double x1=parc->gets1()->getx_pt();
	 double y1=parc->gets1()->gety_pt();

	 double x2=parc->gets3()->getx_pt();
	 double y2=parc->gets3()->gety_pt();

	 double x3=parc->gets2()->getx_pt();
	 double y3=parc->gets2()->gety_pt();

	 double x4=(parc->gets1()->getx_pt()+parc->gets3()->getx_pt())/2;
	 double y4=(parc->gets1()->gety_pt()+parc->gets3()->gety_pt())/2;

	 double X, Y, alpha, beta;

	 Adaptive_Triangulation->intersection_deux_segment_BEY( NULL, 0, x1, y1, x2, y2,  x3, y3, x4, y4, X, Y,  alpha, beta);

	 if(alpha>=0 && alpha<=1 && beta>=0 && beta<=1)
	 {
	 triangle_initial *tmp;

	 double xx3=parc->gets3()->getx_pt();
	 double yy3=parc->gets3()->gety_pt();

	 parc->gets3()->setx_pt(X);
	 parc->gets3()->sety_pt(Y);
	 parc->setz_pt3(0);

		   xmin=min(parc->gets1()->getx_pt(),min(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));
		   xmax=max(parc->gets1()->getx_pt(),max(parc->gets2()->getx_pt(),parc->gets3()->getx_pt()));

		   ymin=min(parc->gets1()->gety_pt(),min(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));
		   ymax=max(parc->gets1()->gety_pt(),max(parc->gets2()->gety_pt(),parc->gets3()->gety_pt()));

		   parc->setxmin_t(xmin);
		   parc->setxmax_t(xmax);

		   parc->setymin_t(ymin);
		   parc->setymax_t(ymax);

		   parc->setfiltre(false);

	 tmp=new triangle_initial();

	 tmp->gets1()->setx_pt(parc->gets2()->getx_pt());
	 tmp->gets1()->sety_pt(parc->gets2()->gety_pt());
	 tmp->setz_pt1(0);

	 tmp->gets2()->setx_pt(xx3);
	 tmp->gets2()->sety_pt(yy3);
	 tmp->setz_pt2(0);

	 tmp->gets3()->setx_pt(X);
	 tmp->gets3()->sety_pt(Y);
	 tmp->setz_pt3(0);


		   xmin=min(tmp->gets1()->getx_pt(),min(tmp->gets2()->getx_pt(),tmp->gets3()->getx_pt()));
		   xmax=max(tmp->gets1()->getx_pt(),max(tmp->gets2()->getx_pt(),tmp->gets3()->getx_pt()));

		   ymin=min(tmp->gets1()->gety_pt(),min(tmp->gets2()->gety_pt(),tmp->gets3()->gety_pt()));
		   ymax=max(tmp->gets1()->gety_pt(),max(tmp->gets2()->gety_pt(),tmp->gets3()->gety_pt()));

		   tmp->setxmin_t(xmin);
		   tmp->setxmax_t(xmax);

		   tmp->setymin_t(ymin);
		   tmp->setymax_t(ymax);

	 Point_Clouds_Import->liste_triangle_adaptation->ajouter_Triangle(tmp);

	 if(parc->getv1()!=NULL)
	 {
	 double angle1=Adaptive_Triangulation->calculer_angle_point(parc->getv1()->gets1()->getx_pt(),  parc->getv1()->gets1()->gety_pt()); //angle par rapport à l'axe X du premier point
	 double angle2=Adaptive_Triangulation->calculer_angle_point(parc->getv1()->gets2()->getx_pt(),  parc->getv1()->gets2()->gety_pt()); //angle par rapport à l'axe X du premier point
	 double angle3=Adaptive_Triangulation->calculer_angle_point(parc->getv1()->gets3()->getx_pt(),  parc->getv1()->gets3()->gety_pt()); //angle par rapport à l'axe X du premier point

	 double anglepm=Adaptive_Triangulation->calculer_angle_point(x4, y4); //angle par rapport à l'axe X du premier point

	 double prec=1e-8;

	 if(fabs(angle1-anglepm)<=prec && fabs(angle2-anglepm)<=prec)//point Pm est sur le segment 12
	 {
	 }

	 if(fabs(angle1-anglepm)<=prec && fabs(angle3-anglepm)<=prec)//point Pm est sur le segment 13
	 {
	 }

	 if(fabs(angle2-anglepm)<=prec && fabs(angle3-anglepm)<=prec)//point Pm est sur le segment 23
	 {
	 }

	 }

	 break;
	 }


parc=parc->getsuiv();
}

Point_Clouds_Import->liste_triangle_adaptation->liberer_liste_pts_triangles();
Point_Clouds_Import->liste_triangle_adaptation->determiner_pts_triangles(Adaptive_Triangulation->triangulation_initiale);
Point_Clouds_Import->liste_triangle_adaptation->filtrage_triangles(Adaptive_Triangulation->triangulation_initiale);
Point_Clouds_Import->liste_triangle_adaptation->distance_max_pts_plans(Adaptive_Triangulation->triangulation_initiale);
Point_Clouds_Import->liste_triangle_adaptation->erreur_max_min_pts_triangles();
Point_Clouds_Import->liste_triangle_adaptation->determiner_voisins_triangles(Adaptive_Triangulation->triangulation_initiale);

Visualization->DrawObjects();

		ComboBox27->Clear();
		for (int i=1;i<=Point_Clouds_Import->liste_triangle_adaptation->getnbre_triangles();i++) ComboBox27->Items->Add(i);
		ComboBox27->ItemIndex=0;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void triangle_initial::distance_max_pts_plan()
{

 double distance;
 double xpt,ypt,zpt;
 double a1,b1,c1,max_distance;

		 a1=a_plan;
		 b1=b_plan;
		 c1=c_plan;

         if(nbre_pts_triangle==0)return;

		 xpt=liste_pts_triangle_BEY[0].p->getx();
		 ypt=liste_pts_triangle_BEY[0].p->gety();
		 zpt=liste_pts_triangle_BEY[0].p->getz();

		   double zp=a1*xpt+b1*ypt+c1;//BEY
		   distance=fabs(zp-zpt);//BEY
		max_distance=distance;

	  double denominateur=sqrt(a1*a1+b1*b1+1); //BEY
	for(int i=0; i<nbre_pts_triangle; i++)
	  {

	   xpt=liste_pts_triangle_BEY[i].p->getx();
	   ypt=liste_pts_triangle_BEY[i].p->gety();
	   zpt=liste_pts_triangle_BEY[i].p->getz();

		   double zp=a1*xpt+b1*ypt+c1;//BEY
		   distance=fabs(zp-zpt); //BEY

	   if(distance>max_distance){max_distance=distance;}

	  }//while
      dist_pt_plan_max=max_distance;

}
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
void triangle_initial_BEY::distance_max_pts_plan()
{

 double distance;
 double max_distance;
 int indice_pt_max;

		 if(nbre_pts_triangle==0)return;

	max_distance=-1; //distance;

	double denominateur=sqrt(a_plan*a_plan+b_plan*b_plan+1); //BEY

	for(int i=0; i<nbre_pts_triangle; i++)
	{
	   distance=fabs(a_plan*liste_pts_triangle_BEY[i].p->x+b_plan*liste_pts_triangle_BEY[i].p->y-liste_pts_triangle_BEY[i].p->z+c_plan);///denominateur;

	   if(distance>max_distance)
	   {
	   max_distance=distance;
	   indice_pt_max=i;
	   }

	}//

	   x_pt_ecart_max=liste_pts_triangle_BEY[indice_pt_max].p->x;
	   y_pt_ecart_max=liste_pts_triangle_BEY[indice_pt_max].p->y;
	   z_pt_ecart_max=liste_pts_triangle_BEY[indice_pt_max].p->z;

	  dist_pt_plan_max=max_distance/denominateur;
}
//----------------------------------------------------------------------------
//---------------------------determination_des_voisins--------------------------
 void ListTriangle_BEY::determiner_voisins_triangles(bool triangulation_initiale)  //VERSION FINALE
 {
 double prec=1e-3;


//-------------------------------
if(triangulation_initiale==false)
{
triangle_initial *parcour=tete;

triangle_initial *T1;
parcour=tete;

while(parcour!=NULL)
{
 if(parcour->getfiltre()==true){parcour=parcour->getsuiv();continue;}//BEY
 if(parcour->getcalcul_voisins()==true){parcour=parcour->getsuiv();continue;}//BEY

  pt_plan* s1=parcour->gets1();
  pt_plan* s2=parcour->gets2();
  pt_plan* s3=parcour->gets3();

  double x1=s1->getx_pt();
  double y1=s1->gety_pt();

  double x2=s2->getx_pt();
  double y2=s2->gety_pt();

  double x3=s3->getx_pt();
  double y3=s3->gety_pt();

  T1=tete;// remarque

while(T1)
{
  if(T1->getfiltre()==true){T1=T1->getsuiv();continue;}//BEY
  if(T1==parcour){ T1=T1->getsuiv(); continue;}

  pt_plan* Ts1=T1->gets1();
  pt_plan* Ts2=T1->gets2();
  pt_plan* Ts3=T1->gets3();

  double x11=Ts1->getx_pt();
  double y11=Ts1->gety_pt();

  double x22=Ts2->getx_pt();
  double y22=Ts2->gety_pt();

  double x33=Ts3->getx_pt();
  double y33=Ts3->gety_pt();

//--------------------voisin V1  -----------------------------------------------

 if(parcour->getv1()==NULL)
 {
	if( ((fabs(x1-x11)<=prec && fabs(y1-y11)<=prec) && (fabs(x2-x22)<=prec && fabs(y2-y22)<=prec))
	  ||((fabs(x1-x22)<=prec && fabs(y1-y22)<=prec) && (fabs(x2-x11)<=prec && fabs(y2-y11)<=prec))) //côté 12
	  {
	   parcour->setv1(T1);
	   T1->setv1(parcour);
	   }

	else if( ((fabs(x1-x11)<=prec && fabs(y1-y11)<=prec) && (fabs(x2-x33)<=prec && fabs(y2-y33)<=prec))
		   ||((fabs(x1-x33)<=prec && fabs(y1-y33)<=prec) && (fabs(x2-x11)<=prec && fabs(y2-y11)<=prec))) //côté 13
	  {
	   parcour->setv1(T1);
	   T1->setv3(parcour);
	   }

	else if( ((fabs(x1-x22)<=prec && fabs(y1-y22)<=prec) && (fabs(x2-x33)<=prec && fabs(y2-y33)<=prec))
		   ||((fabs(x1-x33)<=prec && fabs(y1-y33)<=prec) && (fabs(x2-x22)<=prec && fabs(y2-y22)<=prec))) //côté 23
	  {
	   parcour->setv1(T1);
	   T1->setv2(parcour);
	   }
 }

//--------------------voisin V2  -----------------------------------------------

 if(parcour->getv2()==NULL)
  {
	if( ((fabs(x2-x11)<=prec && fabs(y2-y11)<=prec) && (fabs(x3-x22)<=prec && fabs(y3-y22)<=prec))
	  ||((fabs(x2-x22)<=prec && fabs(y2-y22)<=prec) && (fabs(x3-x11)<=prec && fabs(y3-y11)<=prec))) //côté 12
	  {
	   parcour->setv2(T1);
	   T1->setv1(parcour);
	  }

	else if( ((fabs(x2-x11)<=prec && fabs(y2-y11)<=prec) && (fabs(x3-x33)<=prec && fabs(y3-y33)<=prec))
		   ||((fabs(x2-x33)<=prec && fabs(y2-y33)<=prec) && (fabs(x3-x11)<=prec && fabs(y3-y11)<=prec))) //côté 13
	  {
	   parcour->setv2(T1);
	   T1->setv3(parcour);
	  }

	else if( ((fabs(x2-x22)<=prec && fabs(y2-y22)<=prec) && (fabs(x3-x33)<=prec && fabs(y3-y33)<=prec))
		   ||((fabs(x2-x33)<=prec && fabs(y2-y33)<=prec) && (fabs(x3-x22)<=prec && fabs(y3-y22)<=prec))) //côté 23
	  {
	   parcour->setv2(T1);
	   T1->setv2(parcour);
	  }
  }

//--------------------voisin V3  -----------------------------------------------

 if(parcour->getv3()==NULL)
 {
	 if(((fabs(x1-x11)<=prec && fabs(y1-y11)<=prec) && (fabs(x3-x22)<=prec && fabs(y3-y22)<=prec))
	  ||((fabs(x1-x22)<=prec && fabs(y1-y22)<=prec) && (fabs(x3-x11)<=prec && fabs(y3-y11)<=prec))) //côté 12
	  {
	   parcour->setv3(T1);
	   T1->setv1(parcour);
	  }

	 else if(((fabs(x1-x11)<=prec && fabs(y1-y11)<=prec) && (fabs(x3-x33)<=prec && fabs(y3-y33)<=prec))
	  ||((fabs(x1-x33)<=prec && fabs(y1-y33)<=prec) && (fabs(x3-x11)<=prec && fabs(y3-y11)<=prec))) //côté 13
	  {
	   parcour->setv3(T1);
	   T1->setv3(parcour);
	  }

	 else if(((fabs(x1-x22)<=prec && fabs(y1-y22)<=prec) && (fabs(x3-x33)<=prec && fabs(y3-y33)<=prec))
	  ||((fabs(x1-x33)<=prec && fabs(y1-y33)<=prec) && (fabs(x3-x22)<=prec && fabs(y3-y22)<=prec))) //côté 23
	  {
	   parcour->setv3(T1);
	   T1->setv2(parcour);
	  }
 }

if(parcour->getv1()!=NULL && parcour->getv2()!=NULL  && parcour->getv3()!=NULL)break;

 T1=T1->getsuiv();
 } //while T1

 parcour->setcalcul_voisins(true);

 parcour=parcour->getsuiv();
 } //while parcour
 }

 else if(triangulation_initiale==true)//triangulation initiale ==true
 {
triangle_initial *parcour=tete;

triangle_initial *T1;
parcour=tete;

 while(parcour!=NULL)
{
 if(parcour->getfiltre()==true){parcour=parcour->getsuiv();continue;}//BEY

  pt_plan* s1=parcour->gets1();
  pt_plan* s2=parcour->gets2();
  pt_plan* s3=parcour->gets3();

  double x1=s1->getx_pt();
  double y1=s1->gety_pt();

  double x2=s2->getx_pt();
  double y2=s2->gety_pt();

  double x3=s3->getx_pt();
  double y3=s3->gety_pt();

  T1=tete;// remarque

while(T1)
{
  if(T1->getfiltre()==true){T1=T1->getsuiv();continue;}//BEY
  if(T1==parcour){ T1=T1->getsuiv(); continue;}

  pt_plan* Ts1=T1->gets1();
  pt_plan* Ts2=T1->gets2();
  pt_plan* Ts3=T1->gets3();

  double x11=Ts1->getx_pt();
  double y11=Ts1->gety_pt();

  double x22=Ts2->getx_pt();
  double y22=Ts2->gety_pt();

  double x33=Ts3->getx_pt();
  double y33=Ts3->gety_pt();

//--------------------voisin V1  -----------------------------------------------

 if(parcour->getv1()==NULL)
 {
	if( ((fabs(x1-x11)<=prec && fabs(y1-y11)<=prec) && (fabs(x2-x22)<=prec && fabs(y2-y22)<=prec))
	  ||((fabs(x1-x22)<=prec && fabs(y1-y22)<=prec) && (fabs(x2-x11)<=prec && fabs(y2-y11)<=prec))) //côté 12
	  {
	   parcour->setv1(T1);
	   T1->setv1(parcour);
	   }

	else if( ((fabs(x1-x11)<=prec && fabs(y1-y11)<=prec) && (fabs(x2-x33)<=prec && fabs(y2-y33)<=prec))
		   ||((fabs(x1-x33)<=prec && fabs(y1-y33)<=prec) && (fabs(x2-x11)<=prec && fabs(y2-y11)<=prec))) //côté 13
	  {
	   parcour->setv1(T1);
	   T1->setv3(parcour);
	   }

	else if( ((fabs(x1-x22)<=prec && fabs(y1-y22)<=prec) && (fabs(x2-x33)<=prec && fabs(y2-y33)<=prec))
		   ||((fabs(x1-x33)<=prec && fabs(y1-y33)<=prec) && (fabs(x2-x22)<=prec && fabs(y2-y22)<=prec))) //côté 23
	  {
	   parcour->setv1(T1);
	   T1->setv2(parcour);
	   }
 }

//--------------------voisin V2  -----------------------------------------------

 if(parcour->getv2()==NULL)
  {
	if( ((fabs(x2-x11)<=prec && fabs(y2-y11)<=prec) && (fabs(x3-x22)<=prec && fabs(y3-y22)<=prec))
	  ||((fabs(x2-x22)<=prec && fabs(y2-y22)<=prec) && (fabs(x3-x11)<=prec && fabs(y3-y11)<=prec))) //côté 12
	  {
	   parcour->setv2(T1);
	   T1->setv1(parcour);
	  }

	else if( ((fabs(x2-x11)<=prec && fabs(y2-y11)<=prec) && (fabs(x3-x33)<=prec && fabs(y3-y33)<=prec))
		   ||((fabs(x2-x33)<=prec && fabs(y2-y33)<=prec) && (fabs(x3-x11)<=prec && fabs(y3-y11)<=prec))) //côté 13
	  {
	   parcour->setv2(T1);
	   T1->setv3(parcour);
	  }

	else if( ((fabs(x2-x22)<=prec && fabs(y2-y22)<=prec) && (fabs(x3-x33)<=prec && fabs(y3-y33)<=prec))
		   ||((fabs(x2-x33)<=prec && fabs(y2-y33)<=prec) && (fabs(x3-x22)<=prec && fabs(y3-y22)<=prec))) //côté 23
	  {
	   parcour->setv2(T1);
	   T1->setv2(parcour);
	  }
  }

//--------------------voisin V3  -----------------------------------------------

 if(parcour->getv3()==NULL)
 {
	 if(((fabs(x1-x11)<=prec && fabs(y1-y11)<=prec) && (fabs(x3-x22)<=prec && fabs(y3-y22)<=prec))
	  ||((fabs(x1-x22)<=prec && fabs(y1-y22)<=prec) && (fabs(x3-x11)<=prec && fabs(y3-y11)<=prec))) //côté 12
	  {
	   parcour->setv3(T1);
	   T1->setv1(parcour);
	  }

	 else if(((fabs(x1-x11)<=prec && fabs(y1-y11)<=prec) && (fabs(x3-x33)<=prec && fabs(y3-y33)<=prec))
	  ||((fabs(x1-x33)<=prec && fabs(y1-y33)<=prec) && (fabs(x3-x11)<=prec && fabs(y3-y11)<=prec))) //côté 13
	  {
	   parcour->setv3(T1);
	   T1->setv3(parcour);
	  }

	 else if(((fabs(x1-x22)<=prec && fabs(y1-y22)<=prec) && (fabs(x3-x33)<=prec && fabs(y3-y33)<=prec))
	  ||((fabs(x1-x33)<=prec && fabs(y1-y33)<=prec) && (fabs(x3-x22)<=prec && fabs(y3-y22)<=prec))) //côté 23
	  {
	   parcour->setv3(T1);
	   T1->setv2(parcour);
	  }
 }

if(parcour->getv1()!=NULL && parcour->getv2()!=NULL  && parcour->getv3()!=NULL)break;

 T1=T1->getsuiv();
 } //while T1

 parcour->setcalcul_voisins(true);

 parcour=parcour->getsuiv();
 } //while parcour

 }

} //fonction
//------------------------------------------------------------------------------
//---------------------------determination_des_voisins--------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::determiner_voisins_triangles_new()  //VERSION FINALE
{
triangle_initial_BEY *parcour=tete;

while(parcour!=NULL)
{
 if(parcour->getfiltre()==true){parcour=parcour->getsuiv();continue;}//BEY

 if(parcour->getv1()!=NULL && parcour->getv1()->getfiltre()==true) parcour->setv1(NULL);
 if(parcour->getv2()!=NULL && parcour->getv2()->getfiltre()==true) parcour->setv2(NULL);
 if(parcour->getv3()!=NULL && parcour->getv3()->getfiltre()==true) parcour->setv3(NULL);

 parcour=parcour->getsuiv();
}
}
//------------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::verifier_voisins_triangles()
{
triangle_initial_BEY *parcour=tete;

  while(parcour!=NULL)
  {
	if(parcour->filtre==true){parcour=parcour->getsuiv(); continue;}

	if(parcour->v1==NULL && parcour->v2==NULL && parcour->v3==NULL)parcour->filtre=true;
	else
	{
		if(parcour->v1!=NULL && parcour->v1->filtre==true)
		{
		parcour->v1=NULL;
		int a=1;
		int b=1;
		a=a+b;
		}

		if(parcour->v2!=NULL && parcour->v2->filtre==true)
		{
		parcour->v2=NULL;
		int a=1;
		int b=1;
		a=a+b;
		}

		if(parcour->v3!=NULL && parcour->v3->filtre==true)
		{
		parcour->v3=NULL;
		int a=1;
		int b=1;
		a=a+b;
		}
	}

		parcour=parcour->getsuiv();
  }
}

//---------------------------determination_des_voisins--------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::determiner_voisins_triangles(bool triangulation_initiale)  //VERSION FINALE
{
double xmin_P, xmax_P, ymin_P, ymax_P;
//-------------------------------
//-------------------------------
if(triangulation_initiale==false)
{
triangle_initial_BEY *parcour=tete;

triangle_initial_BEY *T1;
parcour=tete;

for(int i=0; i<Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins; i++)
{
parcour=Adaptive_Triangulation->Triangles_A_Calculer_Voisins[i];
if(parcour->getcalcul_voisins()==true)continue; //Les voisins sont calculés
if(parcour->filtre==true)continue; //Triangle filtré
if(parcour->filtre==false && parcour->supprime==true)continue;// Triangle supprimé

//-----------------------------------------------
 parcour->setcalcul_voisins(false);//BEY
 parcour->setv1(NULL);
 parcour->setv2(NULL);
 parcour->setv3(NULL);
//-----------------------------------------------

  xmin_P=parcour->xmin_t; //-0.1;
  xmax_P=parcour->xmax_t; //+0.1;

  ymin_P=parcour->ymin_t; //-0.1;
  ymax_P=parcour->ymax_t; //+0.1;

  double x1=parcour->s1->x_pt;
  double y1=parcour->s1->y_pt;

  double x2=parcour->s2->x_pt;
  double y2=parcour->s2->y_pt;

  double x3=parcour->s3->x_pt;
  double y3=parcour->s3->y_pt;

  T1=tete;// remarque

for(int j=0; j<Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins; j++)
{
T1=Adaptive_Triangulation->Triangles_Recherche_Voisins[j];
if(T1==parcour)continue; //Même triangle
if(T1->filtre==true)continue; //Triangle filtré
if(T1->filtre==false && T1->supprime==true)continue;// Triangle supprimé

  if(T1->xmin_t > xmax_P) {T1=T1->getsuiv();continue;}//BEY

  if(T1->xmax_t < xmin_P) {T1=T1->getsuiv();continue;}//BEY

  if(T1->ymin_t > ymax_P) {T1=T1->getsuiv();continue;}//BEY

  if(T1->ymax_t < ymin_P) {T1=T1->getsuiv();continue;}//BEY

  double x11=T1->s1->x_pt;
  double y11=T1->s1->y_pt;

  double x22=T1->s2->x_pt;
  double y22=T1->s2->y_pt;

  double x33=T1->s3->x_pt;
  double y33=T1->s3->y_pt;

//--------------------voisin V1  -----------------------------------------------
 bool delta_x_1_11=fabs(x1-x11)<=prec_voisin;
 bool delta_y_1_11=fabs(y1-y11)<=prec_voisin;

 bool delta_x_2_22=fabs(x2-x22)<=prec_voisin;
 bool delta_y_2_22=fabs(y2-y22)<=prec_voisin;

 bool delta_x_1_22=fabs(x1-x22)<=prec_voisin;
 bool delta_y_1_22=fabs(y1-y22)<=prec_voisin;

 bool delta_x_2_11=fabs(x2-x11)<=prec_voisin;
 bool delta_y_2_11=fabs(y2-y11)<=prec_voisin;

 bool delta_x_2_33=fabs(x2-x33)<=prec_voisin;
 bool delta_y_2_33=fabs(y2-y33)<=prec_voisin;

 bool delta_x_1_33=fabs(x1-x33)<=prec_voisin;
 bool delta_y_1_33=fabs(y1-y33)<=prec_voisin;

 bool delta_x_3_22=fabs(x3-x22)<=prec_voisin;
 bool delta_y_3_22=fabs(y3-y22)<=prec_voisin;

 bool delta_x_3_11=fabs(x3-x11)<=prec_voisin;
 bool delta_y_3_11=fabs(y3-y11)<=prec_voisin;

 bool delta_x_3_33=fabs(x3-x33)<=prec_voisin;
 bool delta_y_3_33=fabs(y3-y33)<=prec_voisin;

 if(parcour->v1==NULL)
 {
	if( ((delta_x_1_11 && delta_y_1_11) && (delta_x_2_22 && delta_y_2_22))
	  ||((delta_x_1_22 && delta_y_1_22) && (delta_x_2_11 && delta_y_2_11))) //côté 12
	  {
	   parcour->setv1(T1);
	   T1->setv1(parcour);
	  }

	else if( ((delta_x_1_11 && delta_y_1_11) && (delta_x_2_33 && delta_y_2_33))
		   ||((delta_x_1_33 && delta_y_1_33) && (delta_x_2_11 && delta_y_2_11))) //côté 13
	  {
	   parcour->setv1(T1);
	   T1->setv3(parcour);
	  }

	else if( ((delta_x_1_22 && delta_y_1_22) && (delta_x_2_33 && delta_y_2_33))
		   ||((delta_x_1_33 && delta_y_1_33) && (delta_x_2_22 && delta_y_2_22))) //côté 23
	  {
	   parcour->setv1(T1);
	   T1->setv2(parcour);
	  }
 }

//--------------------voisin V2  -----------------------------------------------
 if(parcour->v2==NULL)
  {
	if( ((delta_x_2_11 && delta_y_2_11) && (delta_x_3_22 && delta_y_3_22))
	  ||((delta_x_2_22 && delta_y_2_22) && (delta_x_3_11 && delta_y_3_11))) //côté 12
	  {
	   parcour->setv2(T1);
	   T1->setv1(parcour);
	  }

	else if( ((delta_x_2_11 && delta_y_2_11) && (delta_x_3_33 && delta_y_3_33))
		   ||((delta_x_2_33 && delta_y_2_33) && (delta_x_3_11 && delta_y_3_11))) //côté 13
	  {
	   parcour->setv2(T1);
	   T1->setv3(parcour);
	  }

	else if( ((delta_x_2_22 && delta_y_2_22) && (delta_x_3_33 && delta_y_3_33))
		   ||((delta_x_2_33 && delta_y_2_33) && (delta_x_3_22 && delta_y_3_22))) //côté 23
	  {
	   parcour->setv2(T1);
	   T1->setv2(parcour);
	  }
  }

//--------------------voisin V3  -----------------------------------------------
 if(parcour->v3==NULL)
 {
	 if(((delta_x_1_11 && delta_y_1_11) && (delta_x_3_22 && delta_y_3_22))
	  ||((delta_x_1_22 && delta_y_1_22) && (delta_x_3_11 && delta_y_3_11))) //côté 12
	  {
	   parcour->setv3(T1);
	   T1->setv1(parcour);
	  }

	 else if(((delta_x_1_11 && delta_y_1_11) && (delta_x_3_33 && delta_y_3_33))
		   ||((delta_x_1_33 && delta_y_1_33) && (delta_x_3_11 && delta_y_3_11))) //côté 13
	  {
	   parcour->setv3(T1);
	   T1->setv3(parcour);
	  }

	 else if(((delta_x_1_22 && delta_y_1_22) && (delta_x_3_33 && delta_y_3_33))
		   ||((delta_x_1_33 && delta_y_1_33) && (delta_x_3_22 && delta_y_3_22))) //côté 23
	  {
	   parcour->setv3(T1);
	   T1->setv2(parcour);
	  }
 }
//------------------------------------------------------------------------------

if(parcour->v1!=NULL && parcour->v2!=NULL && parcour->v3!=NULL)break;

 //T1=T1->getsuiv();
} //while T1

 if(parcour->v1==NULL && parcour->v2==NULL && parcour->v3==NULL)parcour->filtre=true;

 parcour->setcalcul_voisins(true);

 } //while parcour



//------------------------------

}

else if(triangulation_initiale==true)//triangulation initiale ==true
{
triangle_initial_BEY *parcour=tete;

triangle_initial_BEY *T1;
parcour=tete;

while(parcour!=NULL)
{
 if(parcour->getfiltre()==true || parcour->getcalcul_voisins()==true){parcour=parcour->getsuiv();continue;}//BEY

  xmin_P=parcour->xmin_t; //-0.1;
  xmax_P=parcour->xmax_t; //+0.1;

  ymin_P=parcour->ymin_t; //-0.1;
  ymax_P=parcour->ymax_t; //+0.1;

  double x1=parcour->s1->x_pt;
  double y1=parcour->s1->y_pt;

  double x2=parcour->s2->x_pt;
  double y2=parcour->s2->y_pt;

  double x3=parcour->s3->x_pt;
  double y3=parcour->s3->y_pt;

  T1=tete;// remarque

  T1=parcour->getprec();
  if(T1==NULL)T1=tete;

while(T1)
{
  if(T1->getfiltre()==true || T1==parcour){T1=T1->getsuiv();continue;}//BEY

  if(T1->xmin_t > xmax_P) {T1=T1->getsuiv();continue;}//BEY

  if(T1->xmax_t < xmin_P) {T1=T1->getsuiv();continue;}//BEY

  if(T1->ymin_t > ymax_P) {T1=T1->getsuiv();continue;}//BEY

  if(T1->ymax_t < ymin_P) {T1=T1->getsuiv();continue;}//BEY

  double x11=T1->s1->x_pt;
  double y11=T1->s1->y_pt;

  double x22=T1->s2->x_pt;
  double y22=T1->s2->y_pt;

  double x33=T1->s3->x_pt;
  double y33=T1->s3->y_pt;

//--------------------voisin V1  -----------------------------------------------
 bool delta_x_1_11=fabs(x1-x11)<=prec_voisin;
 bool delta_y_1_11=fabs(y1-y11)<=prec_voisin;

 bool delta_x_2_22=fabs(x2-x22)<=prec_voisin;
 bool delta_y_2_22=fabs(y2-y22)<=prec_voisin;

 bool delta_x_1_22=fabs(x1-x22)<=prec_voisin;
 bool delta_y_1_22=fabs(y1-y22)<=prec_voisin;

 bool delta_x_2_11=fabs(x2-x11)<=prec_voisin;
 bool delta_y_2_11=fabs(y2-y11)<=prec_voisin;

 bool delta_x_2_33=fabs(x2-x33)<=prec_voisin;
 bool delta_y_2_33=fabs(y2-y33)<=prec_voisin;

 bool delta_x_1_33=fabs(x1-x33)<=prec_voisin;
 bool delta_y_1_33=fabs(y1-y33)<=prec_voisin;

 bool delta_x_3_22=fabs(x3-x22)<=prec_voisin;
 bool delta_y_3_22=fabs(y3-y22)<=prec_voisin;

 bool delta_x_3_11=fabs(x3-x11)<=prec_voisin;
 bool delta_y_3_11=fabs(y3-y11)<=prec_voisin;

 bool delta_x_3_33=fabs(x3-x33)<=prec_voisin;
 bool delta_y_3_33=fabs(y3-y33)<=prec_voisin;

 if(parcour->getv1()==NULL)
 {
	if( ((delta_x_1_11 && delta_y_1_11) && (delta_x_2_22 && delta_y_2_22))
	  ||((delta_x_1_22 && delta_y_1_22) && (delta_x_2_11 && delta_y_2_11))) //côté 12
	  {
	   parcour->setv1(T1);
	   T1->setv1(parcour);
	  }

	else if( ((delta_x_1_11 && delta_y_1_11) && (delta_x_2_33 && delta_y_2_33))
		   ||((delta_x_1_33 && delta_y_1_33) && (delta_x_2_11 && delta_y_2_11))) //côté 13
	  {
	   parcour->setv1(T1);
	   T1->setv3(parcour);
	  }

	else if( ((delta_x_1_22 && delta_y_1_22) && (delta_x_2_33 && delta_y_2_33))
		   ||((delta_x_1_33 && delta_y_1_33) && (delta_x_2_22 && delta_y_2_22))) //côté 23
	  {
	   parcour->setv1(T1);
	   T1->setv2(parcour);
	  }
 }

//--------------------voisin V2  -----------------------------------------------
 if(parcour->getv2()==NULL)
  {
	if( ((delta_x_2_11 && delta_y_2_11) && (delta_x_3_22 && delta_y_3_22))
	  ||((delta_x_2_22 && delta_y_2_22) && (delta_x_3_11 && delta_y_3_11))) //côté 12
	  {
	   parcour->setv2(T1);
	   T1->setv1(parcour);
	  }

	else if( ((delta_x_2_11 && delta_y_2_11) && (delta_x_3_33 && delta_y_3_33))
		   ||((delta_x_2_33 && delta_y_2_33) && (delta_x_3_11 && delta_y_3_11))) //côté 13
	  {
	   parcour->setv2(T1);
	   T1->setv3(parcour);
	  }

	else if( ((delta_x_2_22 && delta_y_2_22) && (delta_x_3_33 && delta_y_3_33))
		   ||((delta_x_2_33 && delta_y_2_33) && (delta_x_3_22 && delta_y_3_22))) //côté 23
	  {
	   parcour->setv2(T1);
	   T1->setv2(parcour);
	  }
  }

//--------------------voisin V3  -----------------------------------------------
 if(parcour->getv3()==NULL)
 {
	 if(((delta_x_1_11 && delta_y_1_11) && (delta_x_3_22 && delta_y_3_22))
	  ||((delta_x_1_22 && delta_y_1_22) && (delta_x_3_11 && delta_y_3_11))) //côté 12
	  {
	   parcour->setv3(T1);
	   T1->setv1(parcour);
	  }

	 else if(((delta_x_1_11 && delta_y_1_11) && (delta_x_3_33 && delta_y_3_33))
		   ||((delta_x_1_33 && delta_y_1_33) && (delta_x_3_11 && delta_y_3_11))) //côté 13
	  {
	   parcour->setv3(T1);
	   T1->setv3(parcour);
	  }

	 else if(((delta_x_1_22 && delta_y_1_22) && (delta_x_3_33 && delta_y_3_33))
		   ||((delta_x_1_33 && delta_y_1_33) && (delta_x_3_22 && delta_y_3_22))) //côté 23
	  {
	   parcour->setv3(T1);
	   T1->setv2(parcour);
	  }
 }
//------------------------------------------------------------------------------

if(parcour->getv1()!=NULL && parcour->getv2()!=NULL  && parcour->getv3()!=NULL)break;

 T1=T1->getsuiv();
 } //while T1

 parcour->setcalcul_voisins(true);

 parcour=parcour->getsuiv();
 } //while parcour

 }


} //fonction
//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ListTriangle_BEY::distance_max_pts_plans(bool triangulation_initiale) //VERSION FINALE
{
if(triangulation_initiale==false)
{
	triangle_initial *parcT4=tete;
	while (parcT4!=NULL)
	{
	if(parcT4->getfiltre()==true){parcT4=parcT4->getsuiv();continue;};

	parcT4->distance_max_pts_plan();

	parcT4=parcT4->getsuiv();
	}
}

else if(triangulation_initiale==true)
{
	triangle_initial *parcT4=tete;
	while (parcT4!=NULL)
	{
	if(parcT4->getfiltre()==true){parcT4=parcT4->getsuiv();continue;};

	parcT4->distance_max_pts_plan();

	parcT4=parcT4->getsuiv();
	}
}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::distance_max_pts_plans(bool triangulation_initiale) //VERSION FINALE
{
if(triangulation_initiale==false)
{
	triangle_initial_BEY *parcT4=tete;
	while (parcT4!=NULL)
	{
	if(parcT4->getfiltre()==true){parcT4=parcT4->getsuiv();continue;}; //TOUS LES TRIANGLES NON FILTRES

	parcT4->distance_max_pts_plan();
	parcT4->setnouveau_triangle(false);//BEY
	parcT4=parcT4->getsuiv();
	}
}

else if(triangulation_initiale==true)
{
	triangle_initial_BEY *parcT4=tete;
	while (parcT4!=NULL)
	{
	if(parcT4->getfiltre()==true){parcT4=parcT4->getsuiv();continue;};

	parcT4->distance_max_pts_plan();

	parcT4=parcT4->getsuiv();
	}
}

}
//---------------------------------------------------------------------------
void ListTriangle_BEY::erreur_max_min_pts_triangles() //VERSION FINALE
{

	double max_distance1,min_distance1, dist_pt_plan_max;

	 max_distance1=-1e10;
	 min_distance1=1e10;

triangle_initial *parcT5=tete;

while (parcT5!=NULL)
{
if(parcT5->getfiltre()==true){parcT5=parcT5->getsuiv();continue;};

dist_pt_plan_max=parcT5->getdist_pt_plan_max();

if (dist_pt_plan_max>max_distance1)max_distance1=dist_pt_plan_max;
if (dist_pt_plan_max<min_distance1)min_distance1=dist_pt_plan_max;

parcT5=parcT5->getsuiv();
}

	  Adaptive_Triangulation->dist_max=max_distance1;
	  Adaptive_Triangulation->dist_min=min_distance1;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::erreur_max_min_pts_triangles() //VERSION FINALE
{

	double max_distance1,min_distance1, dist_pt_plan_max;

	 max_distance1=-1e10;
	 min_distance1=1e10;

triangle_initial_BEY *parcT5=tete;

while (parcT5!=NULL)
{
	if(parcT5->filtre==true){parcT5=parcT5->getsuiv();continue;} //Triangle filtré
	if(parcT5->filtre==false && parcT5->supprime==true){parcT5=parcT5->getsuiv();continue;} //Triangle supprimé

	{
	dist_pt_plan_max=parcT5->getdist_pt_plan_max();

	if (dist_pt_plan_max>max_distance1)max_distance1=dist_pt_plan_max;
	else if (dist_pt_plan_max<min_distance1)min_distance1=dist_pt_plan_max;
	}
parcT5=parcT5->getsuiv();
}

	  Adaptive_Triangulation->dist_max=max_distance1;
	  Adaptive_Triangulation->dist_min=min_distance1;
}

//---------------------------------------------------------------------------
void triangle_initial::approximation_pts_triangle_plan_moindre_carre()
{
double a[3][3],b[3],x[3];
double xx,yy,zz;
double x1,y1,x2,y2,x3,y3;

	   double a00=0;
	   double a01=0;
	   double a02=0;

       double a10=0;
       double a11=0;
       double a12=0;

       double a20=0;
       double a21=0;
       double a22=0;

       double b0=0;
       double b1=0;
       double b2=0;

	   if(nbre_pts_triangle==0)return;

		for(int i=0; i<nbre_pts_triangle; i++)
		 {
			xx=liste_pts_triangle_BEY[i].p->getx();
			yy=liste_pts_triangle_BEY[i].p->gety();
			zz=liste_pts_triangle_BEY[i].p->getz();

			a00=a00+xx*xx;
			a01=a01+xx*yy;
			a02=a02+xx;

			a10=a10+xx*yy;
			a11=a11+yy*yy;
			a12=a12+yy;

			a20=a20+xx;
			a21=a21+yy;
			a22=nbre_pts_triangle;

			b0=b0+xx*zz;
			b1=b1+yy*zz;
			b2=b2+zz;
         }

             a[0][0]=a00;
             a[0][1]=a01;
             a[0][2]=a02;

             a[1][0]=a10;
             a[1][1]=a11;
             a[1][2]=a12;

             a[2][0]=a20;
             a[2][1]=a21;
             a[2][2]=a22;

             b[0]=b0;
             b[1]=b1;
             b[2]=b2;

             bool probleme;
            Adaptive_Triangulation->gauss_pivot_total(a,b,x, probleme);

			 x1=s1->getx_pt();
			 y1=s1->gety_pt();

			 x2=s2->getx_pt();
			 y2=s2->gety_pt();

			 x3=s3->getx_pt();
			 y3=s3->gety_pt();

			 double z1=x[0]*x1+x[1]*y1+x[2];
			 double z2=x[0]*x2+x[1]*y2+x[2];
			 double z3=x[0]*x3+x[1]*y3+x[2];

			 a_plan=x[0];
			 b_plan=x[1];
			 c_plan=x[2];

			 z_pt1=z1;
			 z_pt2=z2;
			 z_pt3=z3;

//--------calcul du vecteur normal unitaire-------------

		   double v1x=x2-x1;
		   double v1y=y2-y1;
		   double v1z=z2-z1;

		   double v2x=x3-x1;
		   double v2y=y3-y1;
		   double v2z=z3-z1;

		   double Nx=v1y*v2z-v1z*v2y;
		   double Ny=v1z*v2x-v1x*v2z;
		   double Nz=v1x*v2y-v1y*v2x;

		   if(Nz<0){Nx=-Nx; Ny=-Ny; Nz=-Nz;}

		   double module=sqrt(Nx*Nx+Ny*Ny+Nz*Nz);

		   nx=Nx/module;
		   ny=Ny/module;
		   nz=Nz/module;

		   aire_tr=module/2;

//--------FIN calcul du vecteur normal unitaire-------------
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void triangle_initial_BEY::approximation_pts_triangle_plan_moindre_carre()
{
//-------------Nouvelle stratégie---------------
double a[3][3],b[3],x[3];
double xx,yy,zz;
double x1,y1,x2,y2,x3,y3;

	   a[0][0]=0;
	   a[0][1]=0;
	   a[0][2]=0;

	   a[1][0]=0;
       a[1][1]=0;
	   a[1][2]=0;

	   a[2][0]=0;
       a[2][1]=0;
       a[2][2]=0;

	   b[0]=0;
	   b[1]=0;
	   b[2]=0;

	   //nbre_pts_triangle=liste_pts_triangle_BEY.size();

	   if(nbre_pts_triangle==0)return;

		for(int i=0; i<nbre_pts_triangle; i++)
		 {
			xx=liste_pts_triangle_BEY[i].p->x;
			yy=liste_pts_triangle_BEY[i].p->y;
			zz=liste_pts_triangle_BEY[i].p->z;

			a[0][0]=a[0][0]+xx*xx; //liste_pts_triangle_BEY[i].p->xx;
			a[0][1]=a[0][1]+xx*yy; //liste_pts_triangle_BEY[i].p->xy;
			a[0][2]=a[0][2]+xx; //liste_pts_triangle_BEY[i].p->getx();

			a[1][1]=a[1][1]+yy*yy; //liste_pts_triangle_BEY[i].p->yy;
			a[1][2]=a[1][2]+yy; //liste_pts_triangle_BEY[i].p->gety();

			b[0]=b[0]+xx*zz;

			b[1]=b[1]+yy*zz;
			b[2]=b[2]+zz;
		 }


			  //------Matrice symétrique
			  a[1][0]=a[0][1]; //BEY
			  a[2][0]=a[0][2]; //BEY
			  a[2][1]=a[1][2]; //BEY

			a[2][2]=nbre_pts_triangle;

			 bool probleme;
			Adaptive_Triangulation->gauss_pivot_total(a,b,x, probleme);

			 x1=s1->x_pt;
			 y1=s1->y_pt;

			 x2=s2->x_pt;
			 y2=s2->y_pt;

			 x3=s3->x_pt;
			 y3=s3->y_pt;

			 double z1=x[0]*x1+x[1]*y1+x[2];
			 double z2=x[0]*x2+x[1]*y2+x[2];
			 double z3=x[0]*x3+x[1]*y3+x[2];

			 a_plan=x[0];
			 b_plan=x[1];
			 c_plan=x[2];

			 z_pt1=z1;
			 z_pt2=z2;
			 z_pt3=z3;

//--------calcul du vecteur normal unitaire-------------

		   double v1x=x2-x1;
		   double v1y=y2-y1;
		   double v1z=z2-z1;

		   double v2x=x3-x1;
		   double v2y=y3-y1;
		   double v2z=z3-z1;

		   double Nx=v1y*v2z-v1z*v2y;
		   double Ny=v1z*v2x-v1x*v2z;
		   double Nz=v1x*v2y-v1y*v2x;

		   if(Nz<0){Nx=-Nx; Ny=-Ny; Nz=-Nz;}

		   double module=sqrt(Nx*Nx+Ny*Ny+Nz*Nz);

		   nx=Nx/module;
		   ny=Ny/module;
		   nz=Nz/module;

		   aire_tr=module/2;
//--------FIN calcul du vecteur normal unitaire-------------


//----------------------------------------------
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void ListTriangle_BEY::approximation_pts_triangles_plan_moindre_carre(bool triangulation_initiale) //VERSION FINALE
{

if(triangulation_initiale==false)
{
triangle_initial *parcT3=tete;

while (parcT3!=NULL)
{
if(parcT3->getfiltre()==true){parcT3=parcT3->getsuiv();continue;};

   parcT3->approximation_pts_triangle_plan_moindre_carre();

   parcT3=parcT3->getsuiv();
}
}
else if(triangulation_initiale==true)
{
triangle_initial *parcT3=tete;

while (parcT3!=NULL)
{
if(parcT3->getfiltre()==true){parcT3=parcT3->getsuiv();continue;};

   parcT3->approximation_pts_triangle_plan_moindre_carre();

   parcT3=parcT3->getsuiv();
}

}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::approximation_pts_triangles_plan_moindre_carre(bool triangulation_initiale) //VERSION FINALE
{

if(triangulation_initiale==false)
{
triangle_initial_BEY *parcT3=tete;

while (parcT3!=NULL)
{
if(parcT3->getfiltre()==true){parcT3=parcT3->getsuiv();continue;};
if(parcT3->getnouveau_triangle()==false){parcT3=parcT3->getsuiv();continue;}//HERE BEY OK OK

   parcT3->approximation_pts_triangle_plan_moindre_carre();
   parcT3->setnouveau_triangle(false);//BEY
   parcT3=parcT3->getsuiv();
}
}
else if(triangulation_initiale==true)
{
triangle_initial_BEY *parcT3=tete;

while (parcT3!=NULL)
{
if(parcT3->getfiltre()==true){parcT3=parcT3->getsuiv();continue;};

   parcT3->approximation_pts_triangle_plan_moindre_carre();

   parcT3=parcT3->getsuiv();
}

}
}
//---------------------------------------------------------------------------
void TAdaptive_Triangulation::intersection_deux_segment_BEY(triangle_initial *parc, int num_point, double x1,double y1,double x2,double y2, double x3,double y3,double x4,double y4,double & X,double & Y, double & alpha,double & beta)
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

   if(parc!=NULL)
   {
	if(num_point==1){parc->setx1_inter(X); parc->sety1_inter(Y);}
	else if(num_point==2){parc->setx2_inter(X); parc->sety2_inter(Y);}
   }

 }

}//foction
//----------------------------------------------------------------------------
void ListTriangle_BEY::determiner_pts_triangles(bool triangulation_initiale)   //VERSION FINALE
{
if(triangulation_initiale==false)
{
triangle_initial *parc1=tete;

while (parc1!=NULL)
{
	if(parc1->getfiltre()==true){parc1=parc1->getsuiv();continue;}
	parc1->initialiser_liste_pts_triangles();
	parc1=parc1->getsuiv();
}

//*****************************************************************************

double xmin=Point_Clouds_Import->nuage_pts_BEY->getxmin();
double ymin=Point_Clouds_Import->nuage_pts_BEY->getymin();

int i1,i2,i3;
int j1,j2,j3;
double x1, y1, x2, y2, x3, y3, xminT, yminT, xmaxT, ymaxT;
int imin, jmin, imax, jmax;
pt_plan *s1, *s2, *s3;

parc1=tete;

while (parc1!=NULL)
{
if(parc1->getfiltre()==true){parc1=parc1->getsuiv();continue;}

//------------------------------------------------------
		 s1=parc1->gets1();
		 s2=parc1->gets2();
		 s3=parc1->gets3();

		 j1 =(int)((s1->getx_pt()-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j1<0)j1=0;
		 else if (j1>=Adaptive_Triangulation->nbre_cellule_x) j1=Adaptive_Triangulation->nbre_cellule_x-1;

		 i1 =(int)((s1->gety_pt()-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i1<0)i1=0;
		 else if (i1>=Adaptive_Triangulation->nbre_cellule_y) i1=Adaptive_Triangulation->nbre_cellule_y-1;

		 j2 =(int)((s2->getx_pt()-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j2<0)j2=0;
		 else if (j2>=Adaptive_Triangulation->nbre_cellule_x) j2=Adaptive_Triangulation->nbre_cellule_x-1;

		 i2 =(int)((s2->gety_pt()-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i2<0)i2=0;
		 else if (i2>=Adaptive_Triangulation->nbre_cellule_y) i2=Adaptive_Triangulation->nbre_cellule_y-1;

		 j3 =(int)((s3->getx_pt()-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j3<0)j3=0;
		 else if (j3>=Adaptive_Triangulation->nbre_cellule_x) j3=Adaptive_Triangulation->nbre_cellule_x-1;

		 i3 =(int)((s3->gety_pt()-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i3<0)i3=0;
		 else if (i3>=Adaptive_Triangulation->nbre_cellule_y) i3=Adaptive_Triangulation->nbre_cellule_y-1;

		 imin=min(i1, min(i2,i3));
		 jmin=min(j1, min(j2,j3));

		 imax=max(i1, max(i2,i3));
		 jmax=max(j1, max(j2,j3));

x1=parc1->gets1()->getx_pt();
y1=parc1->gets1()->gety_pt();

x2=parc1->gets2()->getx_pt();
y2=parc1->gets2()->gety_pt();

x3=parc1->gets3()->getx_pt();
y3=parc1->gets3()->gety_pt();

xminT=parc1->getxmin_t();
yminT=parc1->getymin_t();

xmaxT=parc1->getxmax_t();
ymaxT=parc1->getymax_t();

	  for (int i=imin;i<=imax;i++)
	  {
		for (int j=jmin;j<=jmax;j++)
		{
		 int nbre_pts_cel=Point_Clouds_Import->cellule_points_BEY[i][j].nbre_pts_cellule;
		 for(int ii=0; ii<nbre_pts_cel; ii++)
		 {
		 double xp=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->getx();
		 double yp=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->gety();

		 bool appartient=Adaptive_Triangulation->appartence_pt_triangle_BEY(x1, y1, x2, y2, x3, y3, xminT, yminT, xmaxT, ymaxT, xp, yp);

			 if(appartient==true)
			 {
			 parc1->ajouter_pt(Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]);
			 }
		 }
		}
	  }

	parc1=parc1->getsuiv();
}
}

else if(triangulation_initiale==true)//triangulation initiale ==true
{
triangle_initial *parc1=tete;

while (parc1!=NULL)
{

	parc1->initialiser_liste_pts_triangles();
	parc1=parc1->getsuiv();
}

//*****************************************************************************

double xmin=Point_Clouds_Import->NUAGE_PTS_BEY.xmin;
double ymin=Point_Clouds_Import->NUAGE_PTS_BEY.ymin;

int i1,i2,i3;
int j1,j2,j3;
double x1, y1, x2, y2, x3, y3, xminT, yminT, xmaxT, ymaxT;
int imin, jmin, imax, jmax;
pt_plan *s1, *s2, *s3;

parc1=tete;

while (parc1!=NULL)
{
//------------------------------------------------------
		 s1=parc1->gets1();
		 s2=parc1->gets2();
		 s3=parc1->gets3();

		 j1 =(int)((s1->getx_pt()-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j1<0)j1=0;
		 else if (j1>=Adaptive_Triangulation->nbre_cellule_x) j1=Adaptive_Triangulation->nbre_cellule_x-1;

		 i1 =(int)((s1->gety_pt()-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i1<0)i1=0;
		 else if (i1>=Adaptive_Triangulation->nbre_cellule_y) i1=Adaptive_Triangulation->nbre_cellule_y-1;

		 j2 =(int)((s2->getx_pt()-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j2<0)j2=0;
		 else if (j2>=Adaptive_Triangulation->nbre_cellule_x) j2=Adaptive_Triangulation->nbre_cellule_x-1;

		 i2 =(int)((s2->gety_pt()-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i2<0)i2=0;
		 else if (i2>=Adaptive_Triangulation->nbre_cellule_y) i2=Adaptive_Triangulation->nbre_cellule_y-1;

		 j3 =(int)((s3->getx_pt()-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j3<0)j3=0;
		 else if (j3>=Adaptive_Triangulation->nbre_cellule_x) j3=Adaptive_Triangulation->nbre_cellule_x-1;

		 i3 =(int)((s3->gety_pt()-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i3<0)i3=0;
		 else if (i3>=Adaptive_Triangulation->nbre_cellule_y) i3=Adaptive_Triangulation->nbre_cellule_y-1;

		 imin=min(i1, min(i2,i3));
		 jmin=min(j1, min(j2,j3));

		 imax=max(i1, max(i2,i3));
		 jmax=max(j1, max(j2,j3));

x1=parc1->gets1()->getx_pt();
y1=parc1->gets1()->gety_pt();

x2=parc1->gets2()->getx_pt();
y2=parc1->gets2()->gety_pt();

x3=parc1->gets3()->getx_pt();
y3=parc1->gets3()->gety_pt();

xminT=parc1->getxmin_t();
yminT=parc1->getymin_t();

xmaxT=parc1->getxmax_t();
ymaxT=parc1->getymax_t();

	  for (int i=imin;i<=imax;i++)
	  {
		for (int j=jmin;j<=jmax;j++)
		{
		 int nbre_pts_cel=Point_Clouds_Import->cellule_points_BEY[i][j].nbre_pts_cellule;
		 for(int ii=0; ii<nbre_pts_cel; ii++)
		 {

		 double xp=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->getx();
		 double yp=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->gety();

		 bool appartient=Adaptive_Triangulation->appartence_pt_triangle_BEY(x1, y1, x2, y2, x3, y3, xminT, yminT, xmaxT, ymaxT, xp, yp);

			 if(appartient==true)
			 {
			 parc1->ajouter_pt(Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]);
			 }
		 }
		}
	  }

	parc1=parc1->getsuiv();
}
}

}
//----------------------------------------------------------------------------
void triangle_initial_BEY::determiner_pts_triangle()
{
int i1,i2,i3;
int j1,j2,j3;
double x1, y1, x2, y2, x3, y3, xminT, yminT, xmaxT, ymaxT;
int imin, jmin, imax, jmax;
//------------------------------------------------------
		double xmin=Point_Clouds_Import->NUAGE_PTS_BEY.xmin;
		double ymin=Point_Clouds_Import->NUAGE_PTS_BEY.ymin;

		x1=s1->x_pt;
		y1=s1->y_pt;

		x2=s2->x_pt;
		y2=s2->y_pt;

		x3=s3->x_pt;
		y3=s3->y_pt;

		xminT=xmin_t;
		yminT=ymin_t;

		xmaxT=xmax_t;
		ymaxT=ymax_t;

		 j1 =(int)((x1-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j1<0)j1=0;
		 else if (j1>=Adaptive_Triangulation->nbre_cellule_x) j1=Adaptive_Triangulation->nbre_cellule_x-1;

		 i1 =(int)((y1-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i1<0)i1=0;
		 else if (i1>=Adaptive_Triangulation->nbre_cellule_y) i1=Adaptive_Triangulation->nbre_cellule_y-1;

		 j2 =(int)((x2-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j2<0)j2=0;
		 else if (j2>=Adaptive_Triangulation->nbre_cellule_x) j2=Adaptive_Triangulation->nbre_cellule_x-1;

		 i2 =(int)((y2-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i2<0)i2=0;
		 else if (i2>=Adaptive_Triangulation->nbre_cellule_y) i2=Adaptive_Triangulation->nbre_cellule_y-1;

		 j3 =(int)((x3-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j3<0)j3=0;
		 else if (j3>=Adaptive_Triangulation->nbre_cellule_x) j3=Adaptive_Triangulation->nbre_cellule_x-1;

		 i3 =(int)((y3-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i3<0)i3=0;
		 else if (i3>=Adaptive_Triangulation->nbre_cellule_y) i3=Adaptive_Triangulation->nbre_cellule_y-1;

		 imin=min(i1, min(i2,i3));
		 jmin=min(j1, min(j2,j3));

		 imax=max(i1, max(i2,i3));
		 jmax=max(j1, max(j2,j3));

	  for (int i=imin;i<=imax;i++)
	  {
		for (int j=jmin;j<=jmax;j++)
		{
		 int nbre_pts_cel=Point_Clouds_Import->cellule_points_BEY[i][j].nbre_pts_cellule;
		 for(int ii=0; ii<nbre_pts_cel; ii++)
		 {
		 point_nuage* PT=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii];
		 if(PT->inserer_pt_triangle==true)continue;

		 double xp=PT->getx();
		 double yp=PT->gety();

		 bool appartient=Adaptive_Triangulation->appartence_pt_triangle_BEY(x1, y1, x2, y2, x3, y3, xminT, yminT, xmaxT, ymaxT, xp, yp);

			 if(appartient==true)
			 {
			 PT->inserer_pt_triangle=true;
			 ajouter_pt(PT);
			 }
		 }
		}
	  }

 }

//----------------------------------------------------------------------------

ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::determiner_pts_triangles(bool triangulation_initiale)   //VERSION FINALE
{
if(triangulation_initiale==false)
{
triangle_initial_BEY *parc1=tete;

while (parc1!=NULL)
{
	if(parc1->getfiltre()==true){parc1=parc1->getsuiv();continue;}
	if(parc1->getnouveau_triangle()==false){parc1=parc1->getsuiv();continue;}//HERE BEY  OK OK

	parc1->initialiser_liste_pts_triangles();
	parc1=parc1->getsuiv();
}

//*****************************************************************************

double xmin=Point_Clouds_Import->nuage_pts_BEY->getxmin();
double ymin=Point_Clouds_Import->nuage_pts_BEY->getymin();

int i1,i2,i3;
int j1,j2,j3;
double x1, y1, x2, y2, x3, y3, xminT, yminT, xmaxT, ymaxT;
int imin, jmin, imax, jmax;
pt_plan *s1, *s2, *s3;

parc1=tete;

while (parc1!=NULL)
{
if(parc1->getfiltre()==true){parc1=parc1->getsuiv();continue;}
if(parc1->getnouveau_triangle()==false){parc1=parc1->getsuiv();continue;}//HERE BEY OK OK

//------------------------------------------------------
		 s1=parc1->gets1();
		 s2=parc1->gets2();
		 s3=parc1->gets3();

		x1=s1->getx_pt();
		y1=s1->gety_pt();

		x2=s2->getx_pt();
		y2=s2->gety_pt();

		x3=s3->getx_pt();
		y3=s3->gety_pt();

		xminT=parc1->getxmin_t();
		yminT=parc1->getymin_t();

		xmaxT=parc1->getxmax_t();
		ymaxT=parc1->getymax_t();

		 j1 =(int)((x1-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j1<0)j1=0;
		 else if (j1>=Adaptive_Triangulation->nbre_cellule_x) j1=Adaptive_Triangulation->nbre_cellule_x-1;

		 i1 =(int)((y1-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i1<0)i1=0;
		 else if (i1>=Adaptive_Triangulation->nbre_cellule_y) i1=Adaptive_Triangulation->nbre_cellule_y-1;

		 j2 =(int)((x2-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j2<0)j2=0;
		 else if (j2>=Adaptive_Triangulation->nbre_cellule_x) j2=Adaptive_Triangulation->nbre_cellule_x-1;

		 i2 =(int)((y2-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i2<0)i2=0;
		 else if (i2>=Adaptive_Triangulation->nbre_cellule_y) i2=Adaptive_Triangulation->nbre_cellule_y-1;

		 j3 =(int)((x3-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j3<0)j3=0;
		 else if (j3>=Adaptive_Triangulation->nbre_cellule_x) j3=Adaptive_Triangulation->nbre_cellule_x-1;

		 i3 =(int)((y3-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i3<0)i3=0;
		 else if (i3>=Adaptive_Triangulation->nbre_cellule_y) i3=Adaptive_Triangulation->nbre_cellule_y-1;

		 imin=min(i1, min(i2,i3));
		 jmin=min(j1, min(j2,j3));

		 imax=max(i1, max(i2,i3));
		 jmax=max(j1, max(j2,j3));

	  for (int i=imin;i<=imax;i++)
	  {
		for (int j=jmin;j<=jmax;j++)
		{
		 int nbre_pts_cel=Point_Clouds_Import->cellule_points_BEY[i][j].nbre_pts_cellule;
		 for(int ii=0; ii<nbre_pts_cel; ii++)
		 {
		 point_nuage* PT=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii];
		 if(PT->inserer_pt_triangle==true)continue;

		 double xp=PT->getx();
		 double yp=PT->gety();

		 bool appartient=Adaptive_Triangulation->appartence_pt_triangle_BEY(x1, y1, x2, y2, x3, y3, xminT, yminT, xmaxT, ymaxT, xp, yp);

			 if(appartient==true)
			 {
			 PT->inserer_pt_triangle=true;
			 parc1->ajouter_pt(PT);
			 }
		 }
		}
	  }

	parc1=parc1->getsuiv();
}
}

else if(triangulation_initiale==true)//triangulation initiale ==true
{
triangle_initial_BEY *parc1=tete;

while (parc1!=NULL)
{
	parc1->initialiser_liste_pts_triangles();
	parc1=parc1->getsuiv();
}

//*****************************************************************************

double xmin=Point_Clouds_Import->NUAGE_PTS_BEY.xmin;
double ymin=Point_Clouds_Import->NUAGE_PTS_BEY.ymin;

int i1,i2,i3;
int j1,j2,j3;
double x1, y1, x2, y2, x3, y3, xminT, yminT, xmaxT, ymaxT;
int imin, jmin, imax, jmax;
pt_plan *s1, *s2, *s3;

parc1=tete;

while (parc1!=NULL)
{

//------------------------------------------------------
		 s1=parc1->gets1();
		 s2=parc1->gets2();
		 s3=parc1->gets3();

		x1=s1->getx_pt();
		y1=s1->gety_pt();

		x2=s2->getx_pt();
		y2=s2->gety_pt();

		x3=s3->getx_pt();
		y3=s3->gety_pt();

		xminT=parc1->getxmin_t();
		yminT=parc1->getymin_t();

		xmaxT=parc1->getxmax_t();
		ymaxT=parc1->getymax_t();

		 j1 =(int)((x1-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j1<0)j1=0;
		 else if (j1>=Adaptive_Triangulation->nbre_cellule_x) j1=Adaptive_Triangulation->nbre_cellule_x-1;

		 i1 =(int)((y1-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i1<0)i1=0;
		 else if (i1>=Adaptive_Triangulation->nbre_cellule_y) i1=Adaptive_Triangulation->nbre_cellule_y-1;

		 j2 =(int)((x2-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j2<0)j2=0;
		 else if (j2>=Adaptive_Triangulation->nbre_cellule_x) j2=Adaptive_Triangulation->nbre_cellule_x-1;

		 i2 =(int)((y2-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i2<0)i2=0;
		 else if (i2>=Adaptive_Triangulation->nbre_cellule_y) i2=Adaptive_Triangulation->nbre_cellule_y-1;

		 j3 =(int)((x3-xmin)/Adaptive_Triangulation->pas_cell_x);
		 if(j3<0)j3=0;
		 else if (j3>=Adaptive_Triangulation->nbre_cellule_x) j3=Adaptive_Triangulation->nbre_cellule_x-1;

		 i3 =(int)((y3-ymin)/Adaptive_Triangulation->pas_cell_y);
		 if(i3<0)i3=0;
		 else if (i3>=Adaptive_Triangulation->nbre_cellule_y) i3=Adaptive_Triangulation->nbre_cellule_y-1;

		 imin=min(i1, min(i2,i3));
		 jmin=min(j1, min(j2,j3));

		 imax=max(i1, max(i2,i3));
		 jmax=max(j1, max(j2,j3));

	  for (int i=imin;i<=imax;i++)
	  {
		for (int j=jmin;j<=jmax;j++)
		{
		 int nbre_pts_cel=Point_Clouds_Import->cellule_points_BEY[i][j].nbre_pts_cellule;
		 for(int ii=0; ii<nbre_pts_cel; ii++)
		 {
		 point_nuage* PT=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii];
		 if(PT->inserer_pt_triangle==true)continue;

		 double xp=PT->getx();
		 double yp=PT->gety();

		 bool appartient=Adaptive_Triangulation->appartence_pt_triangle_BEY(x1, y1, x2, y2, x3, y3, xminT, yminT, xmaxT, ymaxT, xp, yp);

			 if(appartient==true)
			 {
			 PT->inserer_pt_triangle=true;
			 parc1->ajouter_pt(PT);
			 }
		 }
		}
	  }

	parc1=parc1->getsuiv();
}
}

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TAdaptive_Triangulation::Button11Click(TObject *Sender)
{
Point_Clouds_Import->liste_triangle_adaptation->determiner_pts_proches_sommets_triangles(Adaptive_Triangulation->triangulation_initiale);

Point_Clouds_Import->liste_triangle_adaptation->filtrer_triangles_distances_sommets_triangle();
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void ListTriangle_BEY::filtrage_triangles(bool triangulation_initiale)  //VERSION FINALE
{
double precision_calcul=1e-6;
if(triangulation_initiale==false)
{
triangle_initial *parcT2=tete;

while (parcT2!=NULL)
{
			   parcT2->filtrage_un_triangle();
			   parcT2=parcT2->getsuiv();
}
}
else if(triangulation_initiale==true)
{
triangle_initial *parcT2=tete;

while (parcT2!=NULL)
{
			   parcT2->filtrage_un_triangle();
			   parcT2=parcT2->getsuiv();
}
}
}
//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::filtrage_triangles(bool triangulation_initiale)  //VERSION FINALE
{
double precision_calcul=1e-6;
if(triangulation_initiale==false)
{
triangle_initial_BEY *parcT2=tete;

while (parcT2!=NULL)
{
if(parcT2->getnouveau_triangle()==false){parcT2=parcT2->getsuiv();continue;}//HERE BEY Ok OK
			   parcT2->filtrage_un_triangle();
			   parcT2=parcT2->getsuiv();
}
}
else if(triangulation_initiale==true)
{
triangle_initial_BEY *parcT2=tete;

while (parcT2!=NULL)
{
			   parcT2->filtrage_un_triangle();
			   parcT2=parcT2->getsuiv();
}
}


}
//------------------------------------------------------------------------------

//---------------------------------------------------------------------------
void triangle_initial::filtrage_un_triangle()
{
double precision_calcul=1e-6;

if(nbre_pts_triangle<3)   //nbre de pts est inférieur à 3
	{
	filtre=true;
	return;
	}


filtre=true;


double x0=liste_pts_triangle_BEY[0].p->getx();
double y0=liste_pts_triangle_BEY[0].p->gety();

double angle0=Adaptive_Triangulation->calculer_angle_point(x0, y0); //angle par rapport à l'axe X du premier point

				   for(int i=1; i<nbre_pts_triangle; i++)
				   {
					 x0= liste_pts_triangle_BEY[i].p->getx();
					 y0= liste_pts_triangle_BEY[i].p->gety();

					 if(fabs(angle0-Adaptive_Triangulation->calculer_angle_point(x0,y0))>precision_calcul)
					 {
					 filtre=false;
					 break;
					 }
				   }

filtre=false;

double x12=s2->getx_pt()-s1->getx_pt();
double y12=s2->gety_pt()-s1->gety_pt();

double x13=s3->getx_pt()-s1->getx_pt();
double y13=s3->gety_pt()-s1->gety_pt();

double produit_vec=x12*y13 - y12*x13;

					 if(fabs(produit_vec)<precision_calcul)
					 {
					 filtre=true;
					 }

}
//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
void triangle_initial_BEY::filtrage_un_triangle()
{
filtre=false;

if(nbre_pts_triangle<3)   //nbre de pts est inférieur à 3
	{
	filtre=true;
	return;
	}

filtre=true;

double Vx, Vy;

double x0=liste_pts_triangle_BEY[0].p->x;
double y0=liste_pts_triangle_BEY[0].p->y;

int debut;

Vx=liste_pts_triangle_BEY[1].p->x-x0;
Vy=liste_pts_triangle_BEY[1].p->y-y0;

debut=2;

if(fabs(Vx)<1e-6 && fabs(Vy)<1e-6)
{
 for(int i=2; i<nbre_pts_triangle; i++)
 {
	Vx=liste_pts_triangle_BEY[i].p->x-x0;
	Vy=liste_pts_triangle_BEY[i].p->y-y0;

   if(fabs(Vx)>1e-6 || fabs(Vy)>1e-6)
   {
   debut=i;
   break;
   }
 }
}

				   for(int i=debut; i<nbre_pts_triangle; i++)
				   {
					 if(fabs(Vx*(liste_pts_triangle_BEY[i].p->y-y0)-Vy*(liste_pts_triangle_BEY[i].p->x-x0))>precision_filtrage)
					 {
					 filtre=false;
					 break;
					 }
				   }

filtre=false;

double x12=s2->x_pt-s1->x_pt;
double y12=s2->y_pt-s1->y_pt;

double x13=s3->x_pt-s1->x_pt;
double y13=s3->y_pt-s1->y_pt;


					 if(fabs(x12*y13 - y12*x13)<precision_filtrage)
					 {
					 filtre=true;
					 }

}
//------------------------------------------------------------------------------

void TAdaptive_Triangulation::dessiner_centre_gravite_pts_triangle_BEY()
{
	 glColor3d(0.1,0.8,1);
	 glPointSize((float)Adaptive_Triangulation->ComboBox33->Text.ToDouble());

triangle_initial *parcT=Point_Clouds_Import->liste_triangle_adaptation->gettete();

while (parcT!=NULL)
{

      if(parcT->getfiltre()==true){parcT=parcT->getsuiv();continue;}


       glBegin(GL_POINTS);
       glVertex3d(parcT->getliste_pts_triangle()->getxg(),parcT->getliste_pts_triangle()->getyg(),parcT->getliste_pts_triangle()->getzg());
       glEnd();

parcT=parcT->getsuiv();
}
}
//-------------------------------------------------------------------------

//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_centre_gravite_triangle_BEY()
   {
     glColor3d(0.5,1,0.8);
	 glPointSize((float)Adaptive_Triangulation->ComboBox32->Text.ToDouble());

triangle_initial *parcT=Point_Clouds_Import->liste_triangle_adaptation->gettete();

while (parcT!=NULL)
{

      if(parcT->getfiltre()==true){parcT=parcT->getsuiv();continue;}


       glBegin(GL_POINTS);
       glVertex3d(parcT->getxg(),parcT->getyg(),parcT->getzg());
       glEnd();

parcT=parcT->getsuiv();
}
}
//-------------------------------------------------------------------------

//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_centre_cercle_circonscrit_sommets_triangle_BEY()
   {

     glColor3d(0.8,0.3,1);
	 glLineWidth((float)Adaptive_Triangulation->ComboBox31->Text.ToDouble());

triangle_initial *parcT=Point_Clouds_Import->liste_triangle_adaptation->gettete();

while (parcT!=NULL)
{

      if(parcT->getfiltre()==true){parcT=parcT->getsuiv();continue;}


       glBegin(GL_LINES);
       glVertex3d(parcT->getxc(),parcT->getyc(),parcT->getzc());
       glVertex3d(parcT->gets1()->getx_pt(),parcT->gets1()->gety_pt(),0);

       glVertex3d(parcT->getxc(),parcT->getyc(),parcT->getzc());
       glVertex3d(parcT->gets2()->getx_pt(),parcT->gets2()->gety_pt(),0);

       glVertex3d(parcT->getxc(),parcT->getyc(),parcT->getzc());
       glVertex3d(parcT->gets3()->getx_pt(),parcT->gets3()->gety_pt(),0);

       glEnd();
       
parcT=parcT->getsuiv();

}
}
//-------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_centre_cercle_circonscrit_BEY()
   {

	 glPointSize((float)Adaptive_Triangulation->ComboBox30->Text.ToDouble());

triangle_initial *parcT=Point_Clouds_Import->liste_triangle_adaptation->gettete();

while (parcT!=NULL)
{


      if(parcT->getfiltre()==true){parcT=parcT->getsuiv();continue;}


       glBegin(GL_POINTS);
       glVertex3d(parcT->getxc(),parcT->getyc(),parcT->getzc());
       glEnd();

parcT=parcT->getsuiv();
}
}
//-------------------------------------------------------------------------

//--------------------------------------------------------------------------
void ListTriangle_BEY::filtrer_triangles_distances_sommets_triangle()
   {

triangle_initial *parcT=tete;

while (parcT!=NULL)
{

     noeud_point_nuage_BEY *t;

     if(parcT->getfiltre()==true){parcT=parcT->getsuiv();continue;}


      double xx1=parcT->gets1()->getx_pt();
      double yy1=parcT->gets1()->gety_pt();
      double zz1=parcT->getz_pt1();


      double xx2=parcT->gets2()->getx_pt();
      double yy2=parcT->gets2()->gety_pt();
      double zz2=parcT->getz_pt2();

      double xx3=parcT->gets3()->getx_pt();
      double yy3=parcT->gets3()->gety_pt();
      double zz3=parcT->getz_pt3();

    parcT->setxg((xx1+xx2+xx3)/3);
    parcT->setyg((yy1+yy2+yy3)/3);
    parcT->setzg(0);


    double dist12=sqrt(pow(xx2-xx1,2)+ pow(yy2-yy1,2));//+ pow(zz2-zz1,2));
    double dist13=sqrt(pow(xx3-xx1,2)+ pow(yy3-yy1,2));//+ pow(zz3-zz1,2));
    double dist23=sqrt(pow(xx3-xx2,2)+ pow(yy3-yy2,2));//+ pow(zz3-zz2,2));

    double s=0.5*(dist12+dist13+dist23);//demi périmètre

    double rayon_circonscrit=(dist12*dist13*dist23)/(4*sqrt(s*(s-dist12)*(s-dist13)*(s-dist23)));

    double xc, yc, Rc, preci;
    preci=1e-10;

    if(fabs(yy1-yy2)>preci && fabs(yy3-yy2)>preci) Adaptive_Triangulation->calculer_centre_cercle_circonscrit(xx1, yy1, xx2, yy2, xx3, yy3, xc, yc, Rc);

    else if(fabs(yy2-yy3)>preci && fabs(yy1-yy3)>preci) Adaptive_Triangulation->calculer_centre_cercle_circonscrit(xx2, yy2, xx3, yy3, xx1, yy1, xc, yc, Rc);

    else if(fabs(yy2-yy1)>preci && fabs(yy3-yy1)>preci) Adaptive_Triangulation->calculer_centre_cercle_circonscrit(xx3, yy3, xx1, yy1, xx2, yy2, xc, yc, Rc);

    parcT->setxc(xc);
    parcT->setyc(yc);
    parcT->setzc(0);
    parcT->setRc(Rc);

    double dist_seg_min=min(dist12,min(dist13,dist23));

    double poucentage=Adaptive_Triangulation->Edit12->Text.ToDouble();
    double distance_minimale=rayon_circonscrit*poucentage*0.01;

    int nbre_proche_p1,nbre_proche_p2,nbre_proche_p3;

    nbre_proche_p1=nbre_proche_p2=nbre_proche_p3=0;

    t=parcT->getliste_pts_triangle()->getdebut();

     while (t)
    {
    double x=t->getpoint()->getx();
    double y=t->getpoint()->gety();
    double z=t->getpoint()->getz();

    double dist1=sqrt(pow(xx1-x,2)+ pow(yy1-y,2));//+ pow(zz1-z,2));
    double dist2=sqrt(pow(xx2-x,2)+ pow(yy2-y,2));//+ pow(zz2-z,2));
    double dist3=sqrt(pow(xx3-x,2)+ pow(yy3-y,2));//+ pow(zz3-z,2));

    if     (t->getindice_pt_proche()==1 && dist1<=distance_minimale){t->setindice_pt_proche(1);nbre_proche_p1++;t=t->getsuiv2();continue;}
    else if(t->getindice_pt_proche()==2 && dist2<=distance_minimale){t->setindice_pt_proche(2);nbre_proche_p2++;t=t->getsuiv2();continue;}
    else if(t->getindice_pt_proche()==3 && dist3<=distance_minimale){t->setindice_pt_proche(3);nbre_proche_p3++;t=t->getsuiv2();continue;}
    else   {t->setindice_pt_proche(0);t=t->getsuiv2();continue;}

    t=t->getsuiv2();
    }

parcT=parcT->getsuiv();
}
}


//------------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_triangle_eliminer_sommet_BEY()
  {

if(Adaptive_Triangulation->RadioButton2->Checked || Adaptive_Triangulation->RadioButton7->Checked)
{
Rendering->reglage_eclairage();
glEnable(GL_DEPTH_TEST);
}


     glColor3d(0, 1, 1);

triangle_initial_BEY *parc=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while(parc!=NULL)
{
		 if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}
		 if(parc->gettrois_sommets_non_nuls()==false){parc=parc->getsuiv(); continue;}

		 if(Adaptive_Triangulation->RadioButton6->Checked)glBegin(GL_LINE_LOOP);
		 if(Adaptive_Triangulation->RadioButton7->Checked)glBegin(GL_POLYGON);

			glVertex3d(parc->gets1()->getx_pt(),parc->gets1()->gety_pt(),parc->getz_pt1());

			glVertex3d(parc->gets2()->getx_pt(),parc->gets2()->gety_pt(),parc->getz_pt2());

            glVertex3d(parc->gets3()->getx_pt(),parc->gets3()->gety_pt(),parc->getz_pt3());
           glEnd();


parc=parc->getsuiv();
}



if(Adaptive_Triangulation->RadioButton2->Checked || Adaptive_Triangulation->RadioButton6->Checked)
{
glDisable(GL_DEPTH_TEST);
glDisable(GL_LIGHTING);
}

}

//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_pts_proches_sommets_triangle_BEY()
   {

	 glPointSize((float)Adaptive_Triangulation->ComboBox28->Text.ToDouble());

 triangle_initial_BEY *parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while (parcT!=NULL)
{
	 if(parcT->getfiltre()==true){parcT=parcT->getsuiv(); continue;}
	   parcT->dessiner_pts_proches_sommets_triangle();

parcT=parcT->getsuiv();
}
}
//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_pts_proches_sommets_triangle_sommets_nuls_BEY()
   {

	 glPointSize((float)Adaptive_Triangulation->ComboBox40->Text.ToDouble());

 triangle_initial_BEY *parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while (parcT!=NULL)
{

	 if(parcT->getfiltre()==true){parcT=parcT->getsuiv(); continue;}
	 if(parcT->gettrois_sommets_non_nuls()==true){parcT=parcT->getsuiv(); continue;}
	   parcT->dessiner_pts_proches_sommets_triangle();

parcT=parcT->getsuiv();
}
}
//-------------------------------------------------------------------------
//---------------------------------------------------------------------------
void triangle_initial_BEY::dessiner_pts_proches_sommets_triangle_sommets_nuls_BEY()
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

//-------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_pts_proches_milieux_triangle_BEY()
{

glPointSize((float)Adaptive_Triangulation->ComboBox38->Text.ToDouble());

triangle_initial_BEY *parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while (parcT!=NULL)
{
	 if(parcT->getfiltre()==true){parcT=parcT->getsuiv(); continue;}
	   parcT->dessiner_pts_proches_milieux_segments_triangle();

parcT=parcT->getsuiv();
}
}
//-------------------------------------------------------------------------

//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_pts_eloingnes_deux_sommets_nulles_triangle_BEY()
{
     glColor3d(0.2,0.5,0.8);
	 glPointSize((float)Adaptive_Triangulation->ComboBox34->Text.ToDouble());

 triangle_initial *parc=Point_Clouds_Import->liste_triangle_adaptation->gettete();

while (parc!=NULL)
{

     if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}

	 if(parc->getdensite_p1()!=0 && parc->getdensite_p2()==0 && parc->getdensite_p3()==0)
	 {
	double x1,y1,z1;
    x1=parc->getx_loin();
    y1=parc->gety_loin();
    z1=0;

       glBegin(GL_POINTS);
       glVertex3d(x1,y1,z1);
       glEnd();
     }


	 if(parc->getdensite_p2()!=0 && parc->getdensite_p1()==0 && parc->getdensite_p3()==0)
	 {
	double x1,y1,z1;
	x1=parc->getx_loin();
	y1=parc->gety_loin();
	z1=0;

	   glBegin(GL_POINTS);
	   glVertex3d(x1,y1,z1);
	   glEnd();
	 }


	 if(parc->getdensite_p3()!=0 && parc->getdensite_p2()==0 && parc->getdensite_p1()==0)
	 {
	double x1,y1,z1;
    x1=parc->getx_loin();
    y1=parc->gety_loin();
    z1=0;

       glBegin(GL_POINTS);
       glVertex3d(x1,y1,z1);
       glEnd();
     }

parc=parc->getsuiv();
}
}
//-------------------------------------------------------------------------


//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_pts_proches_un_sommet_nulles_triangle_BEY()
   {
     glColor3d(1,0.2,0.5);
	 glPointSize((float)Adaptive_Triangulation->ComboBox35->Text.ToDouble());

 triangle_initial *parc=Point_Clouds_Import->liste_triangle_adaptation->gettete();

while (parc!=NULL)
{

     if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}

	 if(parc->getdensite_p1()==0 && parc->getdensite_p2()!=0 && parc->getdensite_p3()!=0)
	 {
	double x1,y1,z1;
	x1=parc->getx_proche();
	y1=parc->gety_proche();
	z1=0;

	   glBegin(GL_POINTS);
	   glVertex3d(x1,y1,z1);
	   glEnd();
	 }


	 if(parc->getdensite_p2()==0 && parc->getdensite_p1()!=0 && parc->getdensite_p3()!=0)
	 {
	double x1,y1,z1;
	x1=parc->getx_proche();
	y1=parc->gety_proche();
	z1=0;

	   glBegin(GL_POINTS);
	   glVertex3d(x1,y1,z1);
	   glEnd();
	 }


	 if(parc->getdensite_p3()==0 && parc->getdensite_p2()!=0 && parc->getdensite_p1()!=0)
	 {
	double x1,y1,z1;
    x1=parc->getx_proche();
    y1=parc->gety_proche();
    z1=0;

       glBegin(GL_POINTS);
       glVertex3d(x1,y1,z1);
       glEnd();
     }

parc=parc->getsuiv();
}
}
//-------------------------------------------------------------------------

//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_segment_intersection_un_sommet_nulle_triangle_BEY()
   {
     glColor3d(0.5,0.9,1);
	 glLineWidth((float)Adaptive_Triangulation->ComboBox36->Text.ToDouble());

 triangle_initial_BEY *parc=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while (parc!=NULL)
{

     if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}

	if((parc->getdensite_p1()==0 && parc->getdensite_p2()!=0 && parc->getdensite_p3()!=0)
	 ||(parc->getdensite_p2()==0 && parc->getdensite_p1()!=0 && parc->getdensite_p3()!=0)
	 ||(parc->getdensite_p3()==0 && parc->getdensite_p2()!=0 && parc->getdensite_p1()!=0))
	 {
	 glColor3d(0.5,0.9,1);
	   glBegin(GL_LINES);
	   glVertex3d(parc->getx1_inter(),parc->gety1_inter(),0);
	   glVertex3d(parc->getx2_inter(),parc->gety2_inter(),0);
	   glEnd();
	 }


	if((parc->getdensite_p1()!=0 && parc->getdensite_p2()==0 && parc->getdensite_p3()==0)
	 ||(parc->getdensite_p2()!=0 && parc->getdensite_p1()==0 && parc->getdensite_p3()==0)
	 ||(parc->getdensite_p3()!=0 && parc->getdensite_p2()==0 && parc->getdensite_p1()==0))
	 {
	 glColor3d(0.5,0.9,1);
	   glBegin(GL_LINES);
	   glVertex3d(parc->getx1_inter(),parc->gety1_inter(),0);
	   glVertex3d(parc->getx2_inter(),parc->gety2_inter(),0);
	   glEnd();
	 }

parc=parc->getsuiv();
}
}
//-------------------------------------------------------------------------

void TAdaptive_Triangulation::mise_a_jour_triangulation()
{

Point_Clouds_Import->liste_triangle_adaptation_BEY->erreur_max_min_pts_triangles();      //OK OK FINAL pour tous les triangles


Point_Clouds_Import->liste_triangle_adaptation_BEY->determiner_voisins_triangles(Adaptive_Triangulation->triangulation_initiale);    //OK OK FINAL les nouveaux triangles


//*****************************
//********************

//*************************************

triangle_initial_BEY *parcT5=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();
while (parcT5!=NULL)
{
parcT5->setnouveau_triangle(false);
parcT5=parcT5->getsuiv();
}

//*************************************
}
//-------------------------------------------------------------------------
//-------------Flltrer les triangles sans voisins--------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::Filtrer_triangles_sans_voisins()
{
triangle_initial_BEY *parcT2;

parcT2=tete;
while (parcT2!=NULL)
{
		   if(parcT2->filtre==false && parcT2->v1==NULL && parcT2->v2==NULL && parcT2->v3==NULL)
			   parcT2->filtre=true;

		   if(parcT2->nbre_pts_triangle==0)parcT2->filtre=true;

		   parcT2=parcT2->getsuiv();
}

//-----M-A-J des voisins

parcT2=tete;
while (parcT2!=NULL)
{
		   if(parcT2->supprime==true && parcT2->filtre==false){parcT2=parcT2->getsuiv();continue;} //Triangle supprimé
		   if(parcT2->filtre==true){parcT2=parcT2->getsuiv();continue;}                            //Triangle filtré

		   if(parcT2->v1!=NULL && parcT2->v1->filtre==true)parcT2->v1=NULL;
		   if(parcT2->v1!=NULL && parcT2->supprime==true && parcT2->filtre==false)parcT2->v1=NULL;

		   if(parcT2->v2!=NULL && parcT2->v2->filtre==true)parcT2->v2=NULL;
		   if(parcT2->v2!=NULL && parcT2->supprime==true && parcT2->filtre==false)parcT2->v2=NULL;

		   if(parcT2->v3!=NULL && parcT2->v3->filtre==true)parcT2->v3=NULL;
		   if(parcT2->v3!=NULL && parcT2->supprime==true && parcT2->filtre==false)parcT2->v3=NULL;

		   parcT2=parcT2->getsuiv();
}

}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

void ListTriangle_BEY_BEY::modifier_couleurs_triangles()
{
triangle_initial_BEY *parcT2;//, *suiv, *prec;
parcT2=tete;
while (parcT2!=NULL)
{
		   if(parcT2->supprime==false || parcT2->getfiltre()==true){parcT2=parcT2->getsuiv();continue;}
		   parcT2->affecter_couleur();
		   parcT2=parcT2->getsuiv();
}
}
//-------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::mise_a_jour_triangulation()
{
triangle_initial_BEY *parcT2;

int nbre_triangles_supprimes=0;
parcT2=tete;
while (parcT2!=NULL)
{
		   if(parcT2->filtre==true){parcT2=parcT2->getsuiv();continue;}
		   if(parcT2->supprime==false){parcT2=parcT2->getsuiv();continue;}

		   triangle_initial_BEY* this_suiv=parcT2->getsuiv();
		   supprimer_Triangle_milieu(parcT2);
		   parcT2=this_suiv;

		   nbre_triangles_supprimes++;
		   if(nbre_triangles_supprimes==Adaptive_Triangulation->Nbre_Triangles_Supprimes)break;
}


//------------------------------------------------------------------------------
erreur_max_min_pts_triangles();      //OK OK FINAL pour tous les triangles

determiner_voisins_triangles(Adaptive_Triangulation->triangulation_initiale);    //OK OK FINAL les nouveaux triangles
//*****************************
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::mise_a_jour_triangulation_voisins_triangles_supprimes()
{
triangle_initial_BEY *parcT2, *v1, *v2, *v3;


for(int i=0; i<Adaptive_Triangulation->Nbre_Triangles_Supprimes; i++)
{
   parcT2=Adaptive_Triangulation->Triangles_Supprimes[i];

			v1=parcT2->v1;
			if(v1!=NULL)
			 {
					  if(v1->v1==parcT2)v1->v1=NULL;
				 else if(v1->v2==parcT2)v1->v2=NULL;
				 else if(v1->v3==parcT2)v1->v3=NULL;
			 }

			v2=parcT2->v2;
			if(v2!=NULL)
			 {
					  if(v2->v1==parcT2)v2->v1=NULL;
				 else if(v2->v2==parcT2)v2->v2=NULL;
				 else if(v2->v3==parcT2)v2->v3=NULL;
			 }

			v3=parcT2->v3;
			if(v3!=NULL)
			 {
					  if(v3->v1==parcT2)v3->v1=NULL;
				 else if(v3->v2==parcT2)v3->v2=NULL;
				 else if(v3->v3==parcT2)v3->v3=NULL;
			 }


}

}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void TAdaptive_Triangulation::mise_a_jour_triangulation_initiale()
{

//------------------------------------------------------------------------------
Point_Clouds_Import->liste_triangle_adaptation->determiner_pts_triangles(Adaptive_Triangulation->triangulation_initiale); //OK OK les nouveaux triangles

Point_Clouds_Import->liste_triangle_adaptation->filtrage_triangles(Adaptive_Triangulation->triangulation_initiale);   //OK OK les nouveaux triangles

Point_Clouds_Import->liste_triangle_adaptation->determiner_pts_proches_sommets_triangles(Adaptive_Triangulation->triangulation_initiale);   //OK OK les nouveaux triangles


Point_Clouds_Import->liste_triangle_adaptation->determiner_voisins_triangles(Adaptive_Triangulation->triangulation_initiale);   //OK OK les nouveaux triangles


//*****************************
//********************

//*************************************

triangle_initial *parcT5=Point_Clouds_Import->liste_triangle_adaptation->gettete();
while (parcT5!=NULL)
{
parcT5->setcalcul_pts_proche(true);
parcT5=parcT5->getsuiv();
}

//*************************************

}
//-------------------------------------------------------------------------

void TAdaptive_Triangulation::calculer_pt_bissectrice(double x, double y, double x1, double y1, double x2, double y2, double & x_milieu, double & y_milieu)
{
double denom1=sqrt(pow(x1-x,2)+pow(y1-y,2));
//double x_p1_prime=(x1-x)/sqrt(pow(x1-x,2)+pow(y1-y,2))+x;
//double y_p1_prime=(y1-y)/sqrt(pow(x1-x,2)+pow(y1-y,2))+y;
double x_p1_prime=(x1-x)/denom1+x;
double y_p1_prime=(y1-y)/denom1+y;

double denom2=sqrt(pow(x2-x,2)+pow(y2-y,2));
//double x_p2_prime=(x2-x)/sqrt(pow(x2-x,2)+pow(y2-y,2))+x;
//double y_p2_prime=(y2-y)/sqrt(pow(x2-x,2)+pow(y2-y,2))+y;
double x_p2_prime=(x2-x)/denom2+x;
double y_p2_prime=(y2-y)/denom2+y;

x_milieu=(x_p1_prime+x_p2_prime)/2;
y_milieu=(y_p1_prime+y_p2_prime)/2;

x_milieu=1000*(x_milieu-x)+x_milieu;
y_milieu=1000*(y_milieu-y)+y_milieu;
}
//-------------------------------------------------------------------------

void triangle_initial_BEY::calculer_pt_bissectrice(int point_centre, double & x_milieu, double & y_milieu)
{
double x, y, x1, y1, x2, y2;

if(point_centre==1)
{
	x=s1->x_pt;
	y=s1->y_pt;

	x1=s2->x_pt;
	y1=s2->y_pt;

	x2=s3->x_pt;
	y2=s3->y_pt;
}
else if(point_centre==2)
{
	x=s2->x_pt;
	y=s2->y_pt;

	x1=s1->x_pt;
	y1=s1->y_pt;

	x2=s3->x_pt;
	y2=s3->y_pt;
}
else if(point_centre==3)
{
	x=s3->x_pt;
	y=s3->y_pt;

	x1=s1->x_pt;
	y1=s1->y_pt;

	x2=s2->x_pt;
	y2=s2->y_pt;
}

double denom1=sqrt(pow(x1-x,2)+pow(y1-y,2));

double x_p1_prime=(x1-x)/denom1+x;
double y_p1_prime=(y1-y)/denom1+y;

double denom2=sqrt(pow(x2-x,2)+pow(y2-y,2));

double x_p2_prime=(x2-x)/denom2+x;
double y_p2_prime=(y2-y)/denom2+y;

x_milieu=(x_p1_prime+x_p2_prime)/2;
y_milieu=(y_p1_prime+y_p2_prime)/2;

x_milieu=1000*(x_milieu-x)+x_milieu;
y_milieu=1000*(y_milieu-y)+y_milieu;
}
//-----------------------------------------------------------------

//-----------------------------------------------------------------
void TAdaptive_Triangulation::verification(triangle_initial_BEY *parc)
{

	int nbre_pts_v1, nbre_pts_v2, nbre_pts_v3;

	if(parc->getv1()!=NULL && parc->getv1()->getnbre_pts_triangle()!=parc->getv1()->liste_pts_triangle_BEY.size())
	{
	nbre_pts_v1=parc->getv1()->liste_pts_triangle_BEY.size();
	int a=1;
	int b=1;
	a=a+b;
	}

	if(parc->getv2()!=NULL && parc->getv2()->getnbre_pts_triangle()!=parc->getv2()->liste_pts_triangle_BEY.size())
	{
	nbre_pts_v2=parc->getv2()->liste_pts_triangle_BEY.size();
	int a=1;
	int b=1;
	a=a+b;
	}

	if(parc->getv3()!=NULL && parc->getv3()->getnbre_pts_triangle()!=parc->getv3()->liste_pts_triangle_BEY.size())
	{
	nbre_pts_v3=parc->getv3()->liste_pts_triangle_BEY.size();
	int a=1;
	int b=1;
	a=a+b;
	}

}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------
void TAdaptive_Triangulation::gestion_voisins_triangle_filtre_suprime(triangle_initial_BEY *parc)
{
   if(parc==NULL)return;

	triangle_initial_BEY *v1, *v2, *v3;

		if(parc->filtre==true || parc->supprime==true)
		{
			v1=parc->v1;
			v2=parc->v2;
			v3=parc->v3;

			if(v1!=NULL)
			{
					 if(v1->v1==parc)v1->v1=NULL;
				else if(v1->v2==parc)v1->v2=NULL;
				else if(v1->v3==parc)v1->v3=NULL;
			}

			if(v2!=NULL)
			{
					 if(v2->v1==parc)v2->v1=NULL;
				else if(v2->v2==parc)v2->v2=NULL;
				else if(v2->v3==parc)v2->v3=NULL;
			}

			if(v3!=NULL)
			{
					 if(v3->v1==parc)v3->v1=NULL;
				else if(v3->v2==parc)v3->v2=NULL;
				else if(v3->v3==parc)v3->v3=NULL;
			}
		}

}
//----------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::subdivision_adaptative_triangles()
{
double x_milieu, y_milieu;
double xinter_bissec, yinter_bissec;
double xinter, yinter;
double alpha, beta;
triangle_initial_BEY *V1, *V2, *V3;//, *suiv;
double xs1, ys1, xs2, ys2, xs3, ys3;

int nbre_initial=nbre_triangles;
int nbre_final;

triangle_initial_BEY *parc=tete;

bool fin_subdivision=false;

while(true)
{
while(parc!=NULL)  //BEY
{
if(parc->filtre==true){parc=parc->getsuiv();continue;} //Triangle filtré
if(parc->filtre==false && parc->supprime==true){parc=parc->getsuiv();continue;}//Triangle supprimé

//-------------------------------------------------------

if(parc->aire_triangle_2D>=Adaptive_Triangulation->aire_min_triangle) //Aire triangle plus grand que le seuil
{
//------------------------------------------------------------------------------
	if(parc->getdensite_p1()!=0 && parc->getdensite_p2()==0 && parc->getdensite_p3()==0)
	{
//	Adaptive_Triangulation->Points_Proches_Seulement_Un_Sommet=true;

	Adaptive_Triangulation->Triangles_Recherche_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins=0;

	Adaptive_Triangulation->Triangles_A_Calculer_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins=0;

	//Adaptive_Triangulation->Triangles_Supprimes.clear();
	Adaptive_Triangulation->Nbre_Triangles_Supprimes=0;

	V1=parc->v1;
	V2=parc->v2;
	V3=parc->v3;

	parc->recuperer_parametres_triangle_subdivision(xs1, ys1, xs2, ys2, xs3, ys3);

	parc->determiner_pt_eloingne(xs1, ys1);//détermination du pt le plus éloigné de P1

	parc->calculer_pt_bissectrice(1, x_milieu, y_milieu);

	parc->calculer_pts_intersection_segments_triangles_cercle(1, xs1, ys1, parc->getrayon_loin(), xs1, ys1, x_milieu, y_milieu, xinter_bissec, yinter_bissec);//intersection cercle de rayon loin avec la bissectrice

	double x_normale_bissectrice=-(yinter_bissec-ys1); double y_normale_bissectrice=  xinter_bissec-xs1;
	double x1_new=xinter_bissec+100000*x_normale_bissectrice; double y1_new=yinter_bissec+100000*y_normale_bissectrice;
	double x2_new=xinter_bissec-100000*x_normale_bissectrice; double y2_new=yinter_bissec-100000*y_normale_bissectrice;

	parc->intersection_deux_segment_BEY(1, x1_new, y1_new, x2_new, y2_new,  xs1, ys1, xs3, ys3, xinter, yinter,  alpha, beta);
	parc->intersection_deux_segment_BEY(2, x1_new, y1_new, x2_new, y2_new,  xs1, ys1, xs2, ys2, xinter, yinter,  alpha, beta);

//	parc->voisins_a_modifier();
	parc->voisins_a_modifier_BEY();
	parc->subdivision_sommet_1_null(xs1, ys1, parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), xs3,  ys3, xs2, ys2, this);
	parc->subdiviser_triangles_voisins_NEW(this, V1, V2, V3);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V1);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V2);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V3);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};

	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(parc);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V1);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V2);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V3);

	mise_a_jour_triangulation();

	if(Adaptive_Triangulation->dist_max<=Adaptive_Triangulation->precision_approximation_impose)
	{
	fin_subdivision=true;
	break;
	}

	if(parc->getfiltre()==true || parc->supprime==true){parc=parc->getsuiv(); continue;}
	}
	//-------------------------------------------------------------------------------

	if(parc->getdensite_p2()!=0 && parc->getdensite_p1()==0 && parc->getdensite_p3()==0)
	{
//	Adaptive_Triangulation->Points_Proches_Seulement_Un_Sommet=true;

	Adaptive_Triangulation->Triangles_Recherche_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins=0;

	Adaptive_Triangulation->Triangles_A_Calculer_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins=0;

	//Adaptive_Triangulation->Triangles_Supprimes.clear();
	Adaptive_Triangulation->Nbre_Triangles_Supprimes=0;

	V1=parc->v1;
	V2=parc->v2;
	V3=parc->v3;

	parc->recuperer_parametres_triangle_subdivision(xs1, ys1, xs2, ys2, xs3, ys3);

	parc->determiner_pt_eloingne(xs2, ys2);//détermination du pt le plus éloigné de P2

	parc->calculer_pt_bissectrice(2, x_milieu, y_milieu);

	parc->calculer_pts_intersection_segments_triangles_cercle(1, xs2, ys2, parc->getrayon_loin(), xs2, ys2, x_milieu, y_milieu, xinter_bissec, yinter_bissec);//intersection cercle de rayon loin avec la bissectrice

	double x_normale_bissectrice=-(yinter_bissec-ys2); double y_normale_bissectrice=  xinter_bissec-xs2;
	double x1_new=xinter_bissec+100000*x_normale_bissectrice; double y1_new=yinter_bissec+100000*y_normale_bissectrice;
	double x2_new=xinter_bissec-100000*x_normale_bissectrice; double y2_new=yinter_bissec-100000*y_normale_bissectrice;

	parc->intersection_deux_segment_BEY(1, x1_new, y1_new, x2_new, y2_new,  xs2, ys2, xs1, ys1, xinter, yinter,  alpha, beta);
	parc->intersection_deux_segment_BEY(2, x1_new, y1_new, x2_new, y2_new,  xs2, ys2, xs3, ys3, xinter, yinter,  alpha, beta);

//	parc->voisins_a_modifier();
	parc->voisins_a_modifier_BEY();
	parc->subdivision_sommet_1_null(xs2, ys2, parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), xs1, ys1, xs3, ys3, this);
	parc->subdiviser_triangles_voisins_NEW(this, V1, V2, V3);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V1);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V2);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V3);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};

	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(parc);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V1);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V2);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V3);

	mise_a_jour_triangulation();

	if(Adaptive_Triangulation->dist_max<=Adaptive_Triangulation->precision_approximation_impose)
	{
	fin_subdivision=true;
	break;
	}

	if(parc->getfiltre()==true || parc->supprime==true){parc=parc->getsuiv(); continue;}
	}


	if(parc->getdensite_p3()!=0 && parc->getdensite_p1()==0 && parc->getdensite_p2()==0)
	{
//	Adaptive_Triangulation->Points_Proches_Seulement_Un_Sommet=true;

	Adaptive_Triangulation->Triangles_Recherche_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins=0;

	Adaptive_Triangulation->Triangles_A_Calculer_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins=0;

	//Adaptive_Triangulation->Triangles_Supprimes.clear();
	Adaptive_Triangulation->Nbre_Triangles_Supprimes=0;

	V1=parc->v1;
	V2=parc->v2;
	V3=parc->v3;

	parc->recuperer_parametres_triangle_subdivision(xs1, ys1, xs2, ys2, xs3, ys3);

	parc->determiner_pt_eloingne(xs3, ys3);//détermination du pt le plus éloigné de P3

	parc->calculer_pt_bissectrice(3, x_milieu, y_milieu);

	parc->calculer_pts_intersection_segments_triangles_cercle(1, xs3, ys3, parc->getrayon_loin(), xs3, ys3, x_milieu, y_milieu, xinter_bissec, yinter_bissec);//intersection cercle de rayon loin avec la bissectrice

	double x_normale_bissectrice=-(yinter_bissec-ys3); double y_normale_bissectrice=  xinter_bissec-xs3;
	double x1_new=xinter_bissec+100000*x_normale_bissectrice; double y1_new=yinter_bissec+100000*y_normale_bissectrice;
	double x2_new=xinter_bissec-100000*x_normale_bissectrice; double y2_new=yinter_bissec-100000*y_normale_bissectrice;

	parc->intersection_deux_segment_BEY(1, x1_new, y1_new, x2_new, y2_new,  xs3, ys3, xs1, ys1, xinter, yinter,  alpha, beta);
	parc->intersection_deux_segment_BEY(2, x1_new, y1_new, x2_new, y2_new,  xs3, ys3, xs2, ys2, xinter, yinter,  alpha, beta);

//	parc->voisins_a_modifier();
	parc->voisins_a_modifier_BEY();
	parc->subdivision_sommet_1_null(xs3, ys3, parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), xs1, ys1, xs2, ys2, this);
	parc->subdiviser_triangles_voisins_NEW(this, V1, V2, V3);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V1);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V2);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V3);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};

	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(parc);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V1);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V2);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V3);

	mise_a_jour_triangulation();

	if(Adaptive_Triangulation->dist_max<=Adaptive_Triangulation->precision_approximation_impose)
	{
	fin_subdivision=true;
	break;
	}

	if(parc->getfiltre()==true || parc->supprime==true){parc=parc->getsuiv(); continue;}
	}

	if(parc->getdensite_p1()==0 && parc->getdensite_p2()!=0 && parc->getdensite_p3()!=0)
	{
//	Adaptive_Triangulation->Points_Proches_Seulement_Un_Sommet=false;

	Adaptive_Triangulation->Triangles_Recherche_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins=0;

	Adaptive_Triangulation->Triangles_A_Calculer_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins=0;

	//Adaptive_Triangulation->Triangles_Supprimes.clear();
	Adaptive_Triangulation->Nbre_Triangles_Supprimes=0;

	V1=parc->v1;
	V2=parc->v2;
	V3=parc->v3;

	parc->recuperer_parametres_triangle_subdivision(xs1, ys1, xs2, ys2, xs3, ys3);

	parc->determiner_pt_proche(xs1, ys1);//détermination du pt le plus proche de P1

	parc->calculer_pts_intersection_segments_triangles_cercle(1, xs1, ys1, parc->getrayon_proche(), xs1, ys1, xs3, ys3, xinter, yinter);
	parc->calculer_pts_intersection_segments_triangles_cercle(2, xs1, ys1, parc->getrayon_proche(), xs1, ys1, xs2, ys2, xinter, yinter);

//	parc->voisins_a_modifier();
	parc->voisins_a_modifier_BEY();
	parc->subdivision_sommet_1_null(xs1, ys1, parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), xs3, ys3, xs2, ys2, this);
	parc->subdiviser_triangles_voisins_NEW(this, V1, V2, V3);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V1);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V2);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V3);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};

	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(parc);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V1);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V2);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V3);

	mise_a_jour_triangulation();

	if(Adaptive_Triangulation->dist_max<=Adaptive_Triangulation->precision_approximation_impose)
	{
	fin_subdivision=true;
	break;
	}

	if(parc->getfiltre()==true || parc->supprime==true){parc=parc->getsuiv(); continue;}
	}

	if(parc->getdensite_p2()==0 && parc->getdensite_p1()!=0 && parc->getdensite_p3()!=0)
	{
//	Adaptive_Triangulation->Points_Proches_Seulement_Un_Sommet=false;

	Adaptive_Triangulation->Triangles_Recherche_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins=0;

	Adaptive_Triangulation->Triangles_A_Calculer_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins=0;

	//Adaptive_Triangulation->Triangles_Supprimes.clear();
	Adaptive_Triangulation->Nbre_Triangles_Supprimes=0;

	V1=parc->v1;
	V2=parc->v2;
	V3=parc->v3;

	parc->recuperer_parametres_triangle_subdivision(xs1, ys1, xs2, ys2, xs3, ys3);

	parc->determiner_pt_proche(xs2, ys2);//détermination du pt le plus proche de P2

	parc->calculer_pts_intersection_segments_triangles_cercle(1, xs2, ys2, parc->getrayon_proche(), xs2, ys2, xs1, ys1, xinter, yinter);
	parc->calculer_pts_intersection_segments_triangles_cercle(2, xs2, ys2, parc->getrayon_proche(), xs2, ys2, xs3, ys3, xinter, yinter);

//	parc->voisins_a_modifier();
	parc->voisins_a_modifier_BEY();
	parc->subdivision_sommet_1_null(xs2, ys2, parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), xs1, ys1, xs3, ys3, this);
	parc->subdiviser_triangles_voisins_NEW(this, V1, V2, V3);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V1);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V2);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V3);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};

	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(parc);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V1);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V2);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V3);

	mise_a_jour_triangulation();

	if(Adaptive_Triangulation->dist_max<=Adaptive_Triangulation->precision_approximation_impose)
	{
	fin_subdivision=true;
	break;
	}

	if(parc->getfiltre()==true || parc->supprime==true){parc=parc->getsuiv(); continue;}
	}

	if(parc->getdensite_p3()==0 && parc->getdensite_p1()!=0 && parc->getdensite_p2()!=0)
	{
//	Adaptive_Triangulation->Points_Proches_Seulement_Un_Sommet=false;

	Adaptive_Triangulation->Triangles_Recherche_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins=0;

	Adaptive_Triangulation->Triangles_A_Calculer_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins=0;

	//Adaptive_Triangulation->Triangles_Supprimes.clear();
	Adaptive_Triangulation->Nbre_Triangles_Supprimes=0;

	V1=parc->v1;
	V2=parc->v2;
	V3=parc->v3;

	parc->recuperer_parametres_triangle_subdivision(xs1, ys1, xs2, ys2, xs3, ys3);

	parc->determiner_pt_proche(xs3, ys3);//détermination du pt le plus proche de P3

	parc->calculer_pts_intersection_segments_triangles_cercle(1, xs3, ys3, parc->getrayon_proche(), xs3, ys3, xs1, ys1, xinter, yinter);
	parc->calculer_pts_intersection_segments_triangles_cercle(2, xs3, ys3, parc->getrayon_proche(), xs3, ys3, xs2, ys2, xinter, yinter);

//	parc->voisins_a_modifier();
	parc->voisins_a_modifier_BEY();
	parc->subdivision_sommet_1_null(xs3, ys3, parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), xs1, ys1, xs2, ys2, this);
	parc->subdiviser_triangles_voisins_NEW(this, V1, V2, V3);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V1);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V2);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V3);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};

	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(parc);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V1);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V2);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V3);

	mise_a_jour_triangulation();

	if(Adaptive_Triangulation->dist_max<=Adaptive_Triangulation->precision_approximation_impose)
	{
	fin_subdivision=true;
	break;
	}

	if(parc->getfiltre()==true || parc->supprime==true){parc=parc->getsuiv(); continue;}
	}


	if(parc->getdensite_m1()==0 || parc->getdensite_m2()==0 || parc->getdensite_m3()==0)
	{
	Adaptive_Triangulation->Triangles_Recherche_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins=0;

	Adaptive_Triangulation->Triangles_A_Calculer_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins=0;

	//Adaptive_Triangulation->Triangles_Supprimes.clear();
	Adaptive_Triangulation->Nbre_Triangles_Supprimes=0;

	V1=parc->v1;
	V2=parc->v2;
	V3=parc->v3;

//	parc->voisins_a_modifier();
	parc->voisins_a_modifier_BEY();
	parc->creation_deux_triangles_milieu_cote(this);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V1);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V2);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V3);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};

//    suiv=parc->suiv;
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(parc);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V1);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V2);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V3);

	mise_a_jour_triangulation();

	if(Adaptive_Triangulation->dist_max<=Adaptive_Triangulation->precision_approximation_impose)
	{
	fin_subdivision=true;
	break;
	}

	if(parc->getfiltre()==true || parc->supprime==true){parc=parc->getsuiv(); continue;}
//	if(parc->getfiltre()==true || parc->supprime==true){parc=suiv; continue;}
	}

}//Fin aire triangle plus grand que le seuil

	if(parc->supprime==false)//BEY
	if(parc->getdist_pt_plan_max()>Adaptive_Triangulation->precision_approximation_impose)// && parc->getdist_pt_plan_max()>precision_calcul_approximation)
	{
	Adaptive_Triangulation->Triangles_Recherche_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_Recherche_Voisins=0;

	Adaptive_Triangulation->Triangles_A_Calculer_Voisins.clear();
	Adaptive_Triangulation->Nbre_Triangles_A_Calculer_Voisins=0;

	//Adaptive_Triangulation->Triangles_Supprimes.clear();
	Adaptive_Triangulation->Nbre_Triangles_Supprimes=0;

	V1=parc->v1;
	V2=parc->v2;
	V3=parc->v3;

//	parc->voisins_a_modifier();
	parc->voisins_a_modifier_BEY();
	parc->creation_deux_triangles_milieu_cote(this);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V1);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V2);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;/*Adaptive_Triangulation->Triangles_Supprimes.push_back(V3);*/Adaptive_Triangulation->Nbre_Triangles_Supprimes++;};

//    suiv=parc->suiv;
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(parc);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V1);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V2);
	Adaptive_Triangulation->gestion_voisins_triangle_filtre_suprime(V3);

	mise_a_jour_triangulation();

	if(Adaptive_Triangulation->dist_max<=Adaptive_Triangulation->precision_approximation_impose)
	{
	fin_subdivision=true;
	break;
	}

	if(parc->getfiltre()==true || parc->supprime==true){parc=parc->getsuiv(); continue;}
//	if(parc->getfiltre()==true || parc->supprime==true){parc=suiv; continue;}
	}

parc=parc->getsuiv();
}

//------------------------------------------------------------------------------

	if(fin_subdivision==true)break;

	 Adaptive_Triangulation->Edit20->Text=nbre_triangles;
//	 Adaptive_Triangulation->Edit20->Refresh();

	nbre_final=nbre_triangles;
	if(nbre_final==nbre_initial)break;
	else {nbre_initial=nbre_final; parc=tete;}

}
Screen->Cursor= crDefault;

Adaptive_Triangulation->mise_a_jour_informations_triangles=false; //true;

   Adaptive_Triangulation->Edit34->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_max);
   Adaptive_Triangulation->Edit33->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_min);

//   Adaptive_Triangulation->Edit33->Refresh();
//   Adaptive_Triangulation->Edit34->Refresh();

//----------------------------------------------

}
//------------------------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::determiner_parametres_filtration_triangles()
{
double aire_min_tr, rapport_limites_max, ecart_min_droite;
int nbre_pts_min;

aire_min_tr=1e10;
rapport_limites_max=-1;
ecart_min_droite=1e10;
nbre_pts_min=10000000000;

triangle_initial_BEY *parc=tete;

while(parc!=NULL)
{
if(parc->filtre==true){parc=parc->getsuiv(); continue;} //Triangle filtré
if(parc->filtre==false && parc->supprime==true){parc=parc->getsuiv(); continue;} //Triangle supprimé

if(parc->getv1()!=NULL && parc->getv2()!=NULL && parc->getv3()!=NULL){parc=parc->getsuiv(); continue;}


if((parc->getv1()!=NULL && (parc->getv2()==NULL || parc->getv3()==NULL))
 ||(parc->getv2()!=NULL && (parc->getv1()==NULL || parc->getv3()==NULL))
 ||(parc->getv3()!=NULL && (parc->getv1()==NULL || parc->getv2()==NULL))
 ||(parc->getv1()==NULL && parc->getv2()==NULL && parc->getv3()==NULL))
{
if(parc->aire_triangle_2D<=aire_min_tr)aire_min_tr=parc->aire_triangle_2D;

double rapport, hauteur_triangle;;

if(Adaptive_Triangulation->Edit31->Text!="") hauteur_triangle=Adaptive_Triangulation->Edit31->Text.ToDouble();
else hauteur_triangle=1;

if(fabs(parc->delta_Z_pts_triangle)>1e-6 && parc->delta_Z_triangle>hauteur_triangle)
	rapport=parc->delta_Z_triangle/parc->delta_Z_pts_triangle;
else
	rapport=parc->delta_Z_triangle;

if(rapport>=rapport_limites_max)rapport_limites_max=rapport;


if(parc->getnbre_pts_triangle()<=nbre_pts_min)nbre_pts_min=parc->getnbre_pts_triangle();

if(parc->ecart_max_droite<=ecart_min_droite)ecart_min_droite=parc->ecart_max_droite;
}
parc=parc->getsuiv();
}

Adaptive_Triangulation->Edit13->Text=FormatFloat("0.000000", aire_min_tr);
Adaptive_Triangulation->Edit29->Text=FormatFloat("0", nbre_pts_min);
Adaptive_Triangulation->Edit14->Text=FormatFloat("0.000000", rapport_limites_max);
Adaptive_Triangulation->Edit30->Text=FormatFloat("0.000000", ecart_min_droite);

Adaptive_Triangulation->Edit22->Text=FormatFloat("0.000000", aire_min_tr-aire_min_tr/10000); //pour l'affichage
Adaptive_Triangulation->Edit26->Text=FormatFloat("0", nbre_pts_min);
Adaptive_Triangulation->Edit24->Text=FormatFloat("0.000000", rapport_limites_max-rapport_limites_max/10000); //pour l'affichage
Adaptive_Triangulation->Edit28->Text=FormatFloat("0.000000", ecart_min_droite-ecart_min_droite/10000); //pour l'affichage
}
//----------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::traitement_triangles_frontieres_densites_nulles()
{
double x_milieu, y_milieu;
double xinter_bissec, yinter_bissec;
double xinter, yinter;
double alpha, beta;
triangle_initial_BEY *V1, *V2, *V3;
double xs1, ys1, xs2, ys2, xs3, ys3;
//pt_plan *s1, *s2, *s3;
//determiner_pts_proches_sommets_triangles(Adaptive_Triangulation->triangulation_initiale);

double precision_approximation=Adaptive_Triangulation->Edit32->Text.ToDouble();
double precision_calcul_approximation=precision_approximation;
double aire_triangle_subdivise=Adaptive_Triangulation->Edit19->Text.ToDouble();

int nbre_initial=nbre_triangles;
int nbre_final;
//bool modification;

triangle_initial_BEY *parc=tete;
//triangle_initial_BEY *parc_suiv;

triangle_initial_BEY *FIN=fin;

bool fin_subdivision=false;

//while(true)
{
while(parc!=NULL)  //BEY
{

if(parc->getprec()==FIN)break;

if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}
if(parc->getv1()!=NULL && parc->getv2()!=NULL && parc->getv3()!=NULL){parc=parc->getsuiv(); continue;}

if((parc->getv1()!=NULL && parc->getv2()==NULL && parc->getv3()==NULL)
 ||(parc->getv2()!=NULL && parc->getv1()==NULL && parc->getv3()==NULL)
 ||(parc->getv3()!=NULL && parc->getv1()==NULL && parc->getv2()==NULL)
 ||(parc->getv1()==NULL && parc->getv2()==NULL && parc->getv3()==NULL)) //Un seul voisin ou sans voisin

{
//Adaptive_Triangulation->Edit21->Text=parc->getnum_triangle();
//Adaptive_Triangulation->Edit21->Refresh();

	 //modification=false;
	if(parc->getdensite_p1()!=0 && parc->getdensite_p2()==0 && parc->getdensite_p3()==0)
	{
	V1=parc->getv1();
	V2=parc->getv2();
	V3=parc->getv3();
	parc->recuperer_parametres_triangle_subdivision(xs1, ys1, xs2, ys2, xs3, ys3);

//	parc->determiner_pt_eloingne(parc->gets1());//détermination du pt le plus éloigné de P1
//	parc->determiner_pt_eloingne(s1);//détermination du pt le plus éloigné de P1
	parc->determiner_pt_eloingne(xs1, ys1);//détermination du pt le plus éloigné de P1

//	Adaptive_Triangulation->calculer_pt_bissectrice(parc->gets1()->getx_pt(), parc->gets1()->gety_pt(), parc->gets2()->getx_pt(), parc->gets2()->gety_pt(),parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), x_milieu, y_milieu);
	Adaptive_Triangulation->calculer_pt_bissectrice(xs1, ys1, xs2, ys2, xs3, ys3, x_milieu, y_milieu);

//	parc->calculer_pts_intersection_segments_triangles_cercle(1, parc->gets1()->getx_pt(), parc->gets1()->gety_pt(), parc->getrayon_loin(), parc->gets1()->getx_pt(), parc->gets1()->gety_pt(),x_milieu, y_milieu, xinter_bissec, yinter_bissec);//intersection cercle de rayon loin avec la bissectrice
	parc->calculer_pts_intersection_segments_triangles_cercle(1, xs1, ys1, parc->getrayon_loin(), xs1, ys1, x_milieu, y_milieu, xinter_bissec, yinter_bissec);//intersection cercle de rayon loin avec la bissectrice

//	double x_normale_bissectrice=-(yinter_bissec-parc->gets1()->gety_pt()); double y_normale_bissectrice=  xinter_bissec-parc->gets1()->getx_pt();
	double x_normale_bissectrice=-(yinter_bissec-ys1); double y_normale_bissectrice=  xinter_bissec-xs1;
	double x1_new=xinter_bissec+100000*x_normale_bissectrice; double y1_new=yinter_bissec+100000*y_normale_bissectrice;
	double x2_new=xinter_bissec-100000*x_normale_bissectrice; double y2_new=yinter_bissec-100000*y_normale_bissectrice;

//	parc->intersection_deux_segment_BEY(1, x1_new, y1_new, x2_new, y2_new,  parc->gets1()->getx_pt(), parc->gets1()->gety_pt(), parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), xinter, yinter,  alpha, beta);
	parc->intersection_deux_segment_BEY(1, x1_new, y1_new, x2_new, y2_new,  xs1, ys1, xs3, ys3, xinter, yinter,  alpha, beta);
//	parc->intersection_deux_segment_BEY(2, x1_new, y1_new, x2_new, y2_new,  parc->gets1()->getx_pt(), parc->gets1()->gety_pt(), parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), xinter, yinter,  alpha, beta);
	parc->intersection_deux_segment_BEY(2, x1_new, y1_new, x2_new, y2_new,  xs1, ys1, xs2, ys2, xinter, yinter,  alpha, beta);

	parc->voisins_a_modifier();
//	parc->subdivision_sommet_1_null(parc->gets1()->getx_pt(),  parc->gets1()->gety_pt(), parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), parc->gets3()->getx_pt(),  parc->gets3()->gety_pt(), parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), this);
	parc->subdivision_sommet_1_null(xs1, ys1, parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), xs3,  ys3, xs2, ys2, this);
	//parc->subdiviser_triangles_voisins(this);
	parc->subdiviser_triangles_voisins_NEW(this, V1, V2, V3);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;};

	mise_a_jour_triangulation();

	if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}
	}
	//-------------------------------------------------------------------------------

	if(parc->getdensite_p2()!=0 && parc->getdensite_p1()==0 && parc->getdensite_p3()==0)
	{

	V1=parc->getv1();
	V2=parc->getv2();
	V3=parc->getv3();
	parc->recuperer_parametres_triangle_subdivision(xs1, ys1, xs2, ys2, xs3, ys3);

//	parc->determiner_pt_eloingne(parc->gets2());//détermination du pt le plus éloigné de P2
//	parc->determiner_pt_eloingne(s2);//détermination du pt le plus éloigné de P2
	parc->determiner_pt_eloingne(xs2, ys2);//détermination du pt le plus éloigné de P1

//	Adaptive_Triangulation->calculer_pt_bissectrice(parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), parc->gets1()->getx_pt(), parc->gets1()->gety_pt(),parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), x_milieu, y_milieu);
	Adaptive_Triangulation->calculer_pt_bissectrice(xs2, ys2, xs1, ys1, xs3, ys3, x_milieu, y_milieu);
//	parc->calculer_pts_intersection_segments_triangles_cercle(1, parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), parc->getrayon_loin(), parc->gets2()->getx_pt(), parc->gets2()->gety_pt(),x_milieu, y_milieu, xinter_bissec, yinter_bissec);//intersection cercle de rayon loin avec la bissectrice
	parc->calculer_pts_intersection_segments_triangles_cercle(1, xs2, ys2, parc->getrayon_loin(), xs2, ys2, x_milieu, y_milieu, xinter_bissec, yinter_bissec);//intersection cercle de rayon loin avec la bissectrice

//	double x_normale_bissectrice=-(yinter_bissec-parc->gets2()->gety_pt()); double y_normale_bissectrice=  xinter_bissec-parc->gets2()->getx_pt();
	double x_normale_bissectrice=-(yinter_bissec-ys2); double y_normale_bissectrice=  xinter_bissec-xs2;
	double x1_new=xinter_bissec+100000*x_normale_bissectrice; double y1_new=yinter_bissec+100000*y_normale_bissectrice;
	double x2_new=xinter_bissec-100000*x_normale_bissectrice; double y2_new=yinter_bissec-100000*y_normale_bissectrice;

//	parc->intersection_deux_segment_BEY(1, x1_new, y1_new, x2_new, y2_new,  parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), parc->gets1()->getx_pt(), parc->gets1()->gety_pt(), xinter, yinter,  alpha, beta);
	parc->intersection_deux_segment_BEY(1, x1_new, y1_new, x2_new, y2_new,  xs2, ys2, xs1, ys1, xinter, yinter,  alpha, beta);
//	parc->intersection_deux_segment_BEY(2, x1_new, y1_new, x2_new, y2_new,  parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), xinter, yinter,  alpha, beta);
	parc->intersection_deux_segment_BEY(2, x1_new, y1_new, x2_new, y2_new,  xs2, ys2, xs3, ys3, xinter, yinter,  alpha, beta);

	parc->voisins_a_modifier();
//	parc->subdivision_sommet_1_null(parc->gets2()->getx_pt(),  parc->gets2()->gety_pt(), parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), parc->gets1()->getx_pt(),  parc->gets1()->gety_pt(), parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), this);
	parc->subdivision_sommet_1_null(xs2, ys2, parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), xs1, ys1, xs3, ys3, this);
	//parc->subdiviser_triangles_voisins(this);
	parc->subdiviser_triangles_voisins_NEW(this, V1, V2, V3);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;};

	mise_a_jour_triangulation();

	if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}
	}


	if(parc->getdensite_p3()!=0 && parc->getdensite_p1()==0 && parc->getdensite_p2()==0)
	{
	V1=parc->getv1();
	V2=parc->getv2();
	V3=parc->getv3();
	parc->recuperer_parametres_triangle_subdivision(xs1, ys1, xs2, ys2, xs3, ys3);

//	parc->determiner_pt_eloingne(parc->gets3());//détermination du pt le plus éloigné de P3
//	parc->determiner_pt_eloingne(s3);//détermination du pt le plus éloigné de P3
	parc->determiner_pt_eloingne(xs3, ys3);//détermination du pt le plus éloigné de P1

//	Adaptive_Triangulation->calculer_pt_bissectrice(parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), parc->gets1()->getx_pt(), parc->gets1()->gety_pt(),parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), x_milieu, y_milieu);
	Adaptive_Triangulation->calculer_pt_bissectrice(xs3, ys3, xs1, ys1, xs2, ys2, x_milieu, y_milieu);
//	parc->calculer_pts_intersection_segments_triangles_cercle(1, parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), parc->getrayon_loin(), parc->gets3()->getx_pt(), parc->gets3()->gety_pt(),x_milieu, y_milieu, xinter_bissec, yinter_bissec);//intersection cercle de rayon loin avec la bissectrice
	parc->calculer_pts_intersection_segments_triangles_cercle(1, xs3, ys3, parc->getrayon_loin(), xs3, ys3, x_milieu, y_milieu, xinter_bissec, yinter_bissec);//intersection cercle de rayon loin avec la bissectrice

//	double x_normale_bissectrice=-(yinter_bissec-parc->gets3()->gety_pt()); double y_normale_bissectrice=  xinter_bissec-parc->gets3()->getx_pt();
	double x_normale_bissectrice=-(yinter_bissec-ys3); double y_normale_bissectrice=  xinter_bissec-xs3;
	double x1_new=xinter_bissec+100000*x_normale_bissectrice; double y1_new=yinter_bissec+100000*y_normale_bissectrice;
	double x2_new=xinter_bissec-100000*x_normale_bissectrice; double y2_new=yinter_bissec-100000*y_normale_bissectrice;

//	parc->intersection_deux_segment_BEY(1, x1_new, y1_new, x2_new, y2_new,  parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), parc->gets1()->getx_pt(), parc->gets1()->gety_pt(), xinter, yinter,  alpha, beta);
	parc->intersection_deux_segment_BEY(1, x1_new, y1_new, x2_new, y2_new,  xs3, ys3, xs1, ys1, xinter, yinter,  alpha, beta);
//	parc->intersection_deux_segment_BEY(2, x1_new, y1_new, x2_new, y2_new,  parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), xinter, yinter,  alpha, beta);
	parc->intersection_deux_segment_BEY(2, x1_new, y1_new, x2_new, y2_new,  xs3, ys3, xs2, ys2, xinter, yinter,  alpha, beta);

	parc->voisins_a_modifier();
//	parc->subdivision_sommet_1_null(parc->gets3()->getx_pt(),  parc->gets3()->gety_pt(), parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), parc->gets1()->getx_pt(),  parc->gets1()->gety_pt(), parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), this);
	parc->subdivision_sommet_1_null(xs3, ys3, parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), xs1, ys1, xs2, ys2, this);
	//parc->subdiviser_triangles_voisins(this);
	parc->subdiviser_triangles_voisins_NEW(this, V1, V2, V3);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;};

	mise_a_jour_triangulation();

	if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}
	}

	if(parc->getdensite_p1()==0 && parc->getdensite_p2()!=0 && parc->getdensite_p3()!=0)
	{

	V1=parc->getv1();
	V2=parc->getv2();
	V3=parc->getv3();
	parc->recuperer_parametres_triangle_subdivision(xs1, ys1, xs2, ys2, xs3, ys3);

//	parc->determiner_pt_proche(parc->gets1());//détermination du pt le plus proche de P1
//	parc->determiner_pt_proche(s1);//détermination du pt le plus proche de P1
	parc->determiner_pt_proche(xs1, ys1);//détermination du pt le plus proche de P1

//	parc->calculer_pts_intersection_segments_triangles_cercle(1, parc->gets1()->getx_pt(), parc->gets1()->gety_pt(), parc->getrayon_proche(), parc->gets1()->getx_pt(), parc->gets1()->gety_pt(),parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), xinter, yinter);
	parc->calculer_pts_intersection_segments_triangles_cercle(1, xs1, ys1, parc->getrayon_proche(), xs1, ys1, xs3, ys3, xinter, yinter);
//	parc->calculer_pts_intersection_segments_triangles_cercle(2, parc->gets1()->getx_pt(), parc->gets1()->gety_pt(), parc->getrayon_proche(), parc->gets1()->getx_pt(), parc->gets1()->gety_pt(),parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), xinter, yinter);
	parc->calculer_pts_intersection_segments_triangles_cercle(2, xs1, ys1, parc->getrayon_proche(), xs1, ys1, xs2, ys2, xinter, yinter);

	parc->voisins_a_modifier();
//	parc->subdivision_sommet_1_null(parc->gets1()->getx_pt(),  parc->gets1()->gety_pt(), parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), parc->gets3()->getx_pt(),  parc->gets3()->gety_pt(), parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), this);
	parc->subdivision_sommet_1_null(xs1, ys1, parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), xs3, ys3, xs2, ys2, this);
	//parc->subdiviser_triangles_voisins(this);
	parc->subdiviser_triangles_voisins_NEW(this, V1, V2, V3);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;};

	mise_a_jour_triangulation();

	if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}
	}

	if(parc->getdensite_p2()==0 && parc->getdensite_p1()!=0 && parc->getdensite_p3()!=0)
	{

	V1=parc->getv1();
	V2=parc->getv2();
	V3=parc->getv3();
	parc->recuperer_parametres_triangle_subdivision(xs1, ys1, xs2, ys2, xs3, ys3);

//	parc->determiner_pt_proche(parc->gets2());//détermination du pt le plus proche de P2
//	parc->determiner_pt_proche(s2);//détermination du pt le plus proche de P2
	parc->determiner_pt_proche(xs2, ys2);//détermination du pt le plus proche de P2

//	parc->calculer_pts_intersection_segments_triangles_cercle(1, parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), parc->getrayon_proche(), parc->gets2()->getx_pt(), parc->gets2()->gety_pt(),parc->gets1()->getx_pt(), parc->gets1()->gety_pt(), xinter, yinter);
	parc->calculer_pts_intersection_segments_triangles_cercle(1, xs2, ys2, parc->getrayon_proche(), xs2, ys2, xs1, ys1, xinter, yinter);
//	parc->calculer_pts_intersection_segments_triangles_cercle(2, parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), parc->getrayon_proche(), parc->gets2()->getx_pt(), parc->gets2()->gety_pt(),parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), xinter, yinter);
	parc->calculer_pts_intersection_segments_triangles_cercle(2, xs2, ys2, parc->getrayon_proche(), xs2, ys2, xs3, ys3, xinter, yinter);

	parc->voisins_a_modifier();
//	parc->subdivision_sommet_1_null(parc->gets2()->getx_pt(),  parc->gets2()->gety_pt(), parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), parc->gets1()->getx_pt(),  parc->gets1()->gety_pt(), parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), this);
	parc->subdivision_sommet_1_null(xs2, ys2, parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), xs1, ys1, xs3, ys3, this);
	//parc->subdiviser_triangles_voisins(this);
	parc->subdiviser_triangles_voisins_NEW(this, V1, V2, V3);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;};

	mise_a_jour_triangulation();

	if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}
	}

	if(parc->getdensite_p3()==0 && parc->getdensite_p1()!=0 && parc->getdensite_p2()!=0)
	{

	V1=parc->getv1();
	V2=parc->getv2();
	V3=parc->getv3();
	parc->recuperer_parametres_triangle_subdivision(xs1, ys1, xs2, ys2, xs3, ys3);

//	parc->determiner_pt_proche(parc->gets3());//détermination du pt le plus proche de P3
//	parc->determiner_pt_proche(s3);//détermination du pt le plus proche de P3
	parc->determiner_pt_proche(xs3, ys3);//détermination du pt le plus proche de P3

//	parc->calculer_pts_intersection_segments_triangles_cercle(1, parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), parc->getrayon_proche(), parc->gets3()->getx_pt(), parc->gets3()->gety_pt(),parc->gets1()->getx_pt(), parc->gets1()->gety_pt(), xinter, yinter);
	parc->calculer_pts_intersection_segments_triangles_cercle(1, xs3, ys3, parc->getrayon_proche(), xs3, ys3, xs1, ys1, xinter, yinter);
//	parc->calculer_pts_intersection_segments_triangles_cercle(2, parc->gets3()->getx_pt(), parc->gets3()->gety_pt(), parc->getrayon_proche(), parc->gets3()->getx_pt(), parc->gets3()->gety_pt(),parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), xinter, yinter);
	parc->calculer_pts_intersection_segments_triangles_cercle(2, xs3, ys3, parc->getrayon_proche(), xs3, ys3, xs2, ys2, xinter, yinter);

	parc->voisins_a_modifier();
//	parc->subdivision_sommet_1_null(parc->gets3()->getx_pt(),  parc->gets3()->gety_pt(), parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), parc->gets1()->getx_pt(),  parc->gets1()->gety_pt(), parc->gets2()->getx_pt(), parc->gets2()->gety_pt(), this);
	parc->subdivision_sommet_1_null(xs3, ys3, parc->getx1_inter(), parc->gety1_inter(), parc->getx2_inter(), parc->gety2_inter(), xs1, ys1, xs2, ys2, this);
	//parc->subdiviser_triangles_voisins(this);
	parc->subdiviser_triangles_voisins_NEW(this, V1, V2, V3);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;};

	mise_a_jour_triangulation();

	if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}
	}

	if(parc->getdensite_m1()==0 || parc->getdensite_m2()==0 || parc->getdensite_m3()==0)
	{
	V1=parc->getv1();
	V2=parc->getv2();
	V3=parc->getv3();

	parc->voisins_a_modifier();
	parc->creation_deux_triangles_milieu_cote(this);

	if(Adaptive_Triangulation->voisin_1_supprime==true){V1->supprime=true;};
	if(Adaptive_Triangulation->voisin_2_supprime==true){V2->supprime=true;};
	if(Adaptive_Triangulation->voisin_3_supprime==true){V3->supprime=true;};

	mise_a_jour_triangulation();

	if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}
	}

}//Fin aire triangle plus grand que le seuil

	//-------------------------CAS 8--------------------------------------------
//------subdivision des triangles en dehors de la tolérance-------------------------------------------------
	

parc=parc->getsuiv();
}

//------------------------------------------------------------------------------

	//if(fin_subdivision==true)break;

	 Adaptive_Triangulation->Edit20->Text=nbre_triangles;
//	 Adaptive_Triangulation->Edit20->Refresh();

	nbre_final=nbre_triangles;
	//if(nbre_final==nbre_initial)break;
	//else {nbre_initial=nbre_final; parc=tete;}

	//if(Adaptive_Triangulation->Edit6->Text.ToDouble()<Adaptive_Triangulation->Edit32->Text.ToDouble())break;
}
Screen->Cursor= crDefault;

Adaptive_Triangulation->mise_a_jour_informations_triangles=false; //true;

   Adaptive_Triangulation->Edit34->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_max);
   Adaptive_Triangulation->Edit33->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_min);


}


//---------------------------------------------------------------------------
void __fastcall TAdaptive_Triangulation::Button10Click(TObject *Sender)
{
Screen->Cursor= crHourGlass;
Point_Clouds_Import->liste_triangle_adaptation_BEY->subdivision_adaptative_triangles();
Screen->Cursor= crDefault;

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TAdaptive_Triangulation::Lancer_Approche_Subdivision_Triangles()
{
Screen->Cursor= crHourGlass;
Point_Clouds_Import->liste_triangle_adaptation_BEY->subdivision_adaptative_triangles();
Screen->Cursor= crDefault;

}
//---------------------------------------------------------------------------


//------------------------------------------------------------------------------
void triangle_initial::determiner_pts_proches_sommets_triangle(double rapport, double aire_min_triangle)
{
calcul_pts_proche=true;

  double dist_pp1, dist_pp2, dist_pp3;
  double dist_pm1, dist_pm2, dist_pm3;


	  double xx1=s1->getx_pt();
	  double yy1=s1->gety_pt();
	  double zz1=z_pt1;


	  double xx2=s2->getx_pt();
	  double yy2=s2->gety_pt();
	  double zz2=z_pt2;

	  double xx3=s3->getx_pt();
	  double yy3=s3->gety_pt();
	  double zz3=z_pt3;

	  double x_m1=(xx1+xx2)/2;
	  double y_m1=(yy1+yy2)/2;

	  double x_m2=(xx3+xx2)/2;
	  double y_m2=(yy3+yy2)/2;

	  double x_m3=(xx1+xx3)/2;
	  double y_m3=(yy1+yy3)/2;


//*************************
	double dist12=sqrt(pow(xx2-xx1,2)+ pow(yy2-yy1,2));//+ pow(zz2-zz1,2));
	double dist13=sqrt(pow(xx3-xx1,2)+ pow(yy3-yy1,2));//+ pow(zz3-zz1,2));
	double dist23=sqrt(pow(xx3-xx2,2)+ pow(yy3-yy2,2));//+ pow(zz3-zz2,2));

	double min_s1s2_s1s3=min(dist12, dist13);
	double min_s2s1_s2s3=min(dist12, dist23);
	double min_s3s1_s3s2=min(dist13, dist23);

	double seuil_s1=rapport*min_s1s2_s1s3;
	double seuil_s2=rapport*min_s2s1_s2s3;
	double seuil_s3=rapport*min_s3s1_s3s2;

	double seuil_m1=rapport*dist12;
	double seuil_m2=rapport*dist23;
	double seuil_m3=rapport*dist13;

	nbre_pts_proche_p1=nbre_pts_proche_p2=nbre_pts_proche_p3=0;
	nbre_pts_proche_m1=nbre_pts_proche_m2=nbre_pts_proche_m3=0;

	noeud_point_nuage_BEY *t;

	dist_pp1=dist_pp2=dist_pp3=1e10;
	dist_pm1=dist_pm2=dist_pm3=1e10;

	int nbre_pts_triangle_tmp=0;
	t=liste_pts_triangle->getdebut();

	for(int i=0; i<nbre_pts_triangle; i++)
	{
	nbre_pts_triangle_tmp++;

	double x=liste_pts_triangle_BEY[i].p->getx();
	double y=liste_pts_triangle_BEY[i].p->gety();

	double dist1=sqrt(pow(xx1-x,2)+ pow(yy1-y,2));
	double dist2=sqrt(pow(xx2-x,2)+ pow(yy2-y,2));
	double dist3=sqrt(pow(xx3-x,2)+ pow(yy3-y,2));

	double dist_m1=sqrt(pow(x_m1-x,2)+ pow(y_m1-y,2));
	double dist_m2=sqrt(pow(x_m2-x,2)+ pow(y_m2-y,2));
	double dist_m3=sqrt(pow(x_m3-x,2)+ pow(y_m3-y,2));

	double dist_min=min(dist1,min(dist2,dist3));

	double dist_min_m=min(dist_m1,min(dist_m2,dist_m3));

		 if(fabs(dist1-dist_min)<=1e-6){dist_pp1=min(dist1,dist_pp1); liste_pts_triangle_BEY[i].indice_pt_proche=1;nbre_pts_proche_p1++;}
	else if(fabs(dist2-dist_min)<=1e-6){dist_pp2=min(dist2,dist_pp2); liste_pts_triangle_BEY[i].indice_pt_proche=2;nbre_pts_proche_p2++;}
	else if(fabs(dist3-dist_min)<=1e-6){dist_pp3=min(dist3,dist_pp3); liste_pts_triangle_BEY[i].indice_pt_proche=3;nbre_pts_proche_p3++;}

		 if(fabs(dist_m1-dist_min_m)<=1e-6){dist_pm1=min(dist_m1,dist_pm1); liste_pts_triangle_BEY[i].indice_pt_proche_milieu=1; nbre_pts_proche_m1++;}
	else if(fabs(dist_m2-dist_min_m)<=1e-6){dist_pm2=min(dist_m2,dist_pm2); liste_pts_triangle_BEY[i].indice_pt_proche_milieu=2; nbre_pts_proche_m2++;}
	else if(fabs(dist_m3-dist_min_m)<=1e-6){dist_pm3=min(dist_m3,dist_pm3); liste_pts_triangle_BEY[i].indice_pt_proche_milieu=3; nbre_pts_proche_m3++;}
	}

   //liste_pts_triangle->setnbre_pt(nbre_pts_triangle_tmp);
   nbre_pts_triangle=nbre_pts_triangle_tmp;

   double denominateur=1./nbre_pts_triangle;

   densite_p1=nbre_pts_proche_p1*denominateur;
   densite_p2=nbre_pts_proche_p2*denominateur;
   densite_p3=nbre_pts_proche_p3*denominateur;

   densite_m1=nbre_pts_proche_m1*denominateur;
   densite_m2=nbre_pts_proche_m2*denominateur;
   densite_m3=nbre_pts_proche_m3*denominateur;

//calcul_normal_triangle_BEY();      // ICI


if(aire_tr>=aire_min_triangle)
{
if(dist_pp1>1e-6 && dist_pp1 > seuil_s1) densite_p1=0;  //BEY
if(dist_pp2>1e-6 && dist_pp2 > seuil_s2) densite_p2=0;  //BEY
if(dist_pp3>1e-6 && dist_pp3 > seuil_s3) densite_p3=0;  //BEY

if(dist_pm1>1e-6 && dist_pm1 > seuil_m1) densite_m1=0;  //BEY
if(dist_pm2>1e-6 && dist_pm2 > seuil_m2) densite_m2=0;  //BEY
if(dist_pm3>1e-6 && dist_pm3 > seuil_m3) densite_m3=0;  //BEY
}

   if(densite_p1==0 || densite_p2==0 || densite_p3==0)   eliminer_sommet=true;

}
//------------------------------------------------------------------------------
void triangle_initial_BEY::determiner_pts_proches_sommets_triangle(double rapport, double aire_min_triangle)
{
  double dist_pp1, dist_pp2, dist_pp3;
  double dist_pm1, dist_pm2, dist_pm3;

	  double xx1=s1->x_pt;
	  double yy1=s1->y_pt;
	  double zz1=z_pt1;

	  double xx2=s2->x_pt;
	  double yy2=s2->y_pt;
	  double zz2=z_pt2;

	  double xx3=s3->x_pt;
	  double yy3=s3->y_pt;
	  double zz3=z_pt3;

	  double x_m1=(xx1+xx2)/2;
	  double y_m1=(yy1+yy2)/2;

	  double x_m2=(xx3+xx2)/2;
	  double y_m2=(yy3+yy2)/2;

	  double x_m3=(xx1+xx3)/2;
	  double y_m3=(yy1+yy3)/2;


//*************************
	double dist12=/*sqrt*/(pow(xx2-xx1,2)+ pow(yy2-yy1,2));
	double dist13=/*sqrt*/(pow(xx3-xx1,2)+ pow(yy3-yy1,2));
	double dist23=/*sqrt*/(pow(xx3-xx2,2)+ pow(yy3-yy2,2));



	double max_s1s2_s1s3=sqrt(max(dist12, dist13));
	double max_s2s1_s2s3=sqrt(max(dist12, dist23));
	double max_s3s1_s3s2=sqrt(max(dist13, dist23));


	double seuil_s1=rapport*max_s1s2_s1s3;
	double seuil_s2=rapport*max_s2s1_s2s3;
	double seuil_s3=rapport*max_s3s1_s3s2;

	double seuil_m1=rapport*dist12;
	double seuil_m2=rapport*dist23;
	double seuil_m3=rapport*dist13;

	int nbre_pts_proche_p1, nbre_pts_proche_p2, nbre_pts_proche_p3;

	nbre_pts_proche_p1=nbre_pts_proche_p2=nbre_pts_proche_p3=0;

	int nbre_pts_proche_m1, nbre_pts_proche_m2, nbre_pts_proche_m3;
	nbre_pts_proche_m1=nbre_pts_proche_m2=nbre_pts_proche_m3=0;

	dist_pp1=dist_pp2=dist_pp3=1e10;
	dist_pm1=dist_pm2=dist_pm3=1e10;

	//nbre_pts_triangle=liste_pts_triangle_BEY.size();
	for(int i=0; i<nbre_pts_triangle; i++)
	{
//	double x=liste_pts_triangle_BEY[i].p->getx();
//	double y=liste_pts_triangle_BEY[i].p->gety();

	double x=liste_pts_triangle_BEY[i].p->x;
	double y=liste_pts_triangle_BEY[i].p->y;

	double dist1=/*sqrt*/(pow(xx1-x,2)+ pow(yy1-y,2));
	double dist2=/*sqrt*/(pow(xx2-x,2)+ pow(yy2-y,2));
	double dist3=/*sqrt*/(pow(xx3-x,2)+ pow(yy3-y,2));

	double dist_m1=/*sqrt*/(pow(x_m1-x,2)+ pow(y_m1-y,2));
	double dist_m2=/*sqrt*/(pow(x_m2-x,2)+ pow(y_m2-y,2));
	double dist_m3=/*sqrt*/(pow(x_m3-x,2)+ pow(y_m3-y,2));

	double dist_min=min(dist1,min(dist2,dist3));

	double dist_min_m=min(dist_m1,min(dist_m2,dist_m3));

		 if(fabs(dist1-dist_min)<=1e-6){dist_pp1=min(dist1,dist_pp1); liste_pts_triangle_BEY[i].indice_pt_proche=1;nbre_pts_proche_p1++;}
	else if(fabs(dist2-dist_min)<=1e-6){dist_pp2=min(dist2,dist_pp2); liste_pts_triangle_BEY[i].indice_pt_proche=2;nbre_pts_proche_p2++;}
	else if(fabs(dist3-dist_min)<=1e-6){dist_pp3=min(dist3,dist_pp3); liste_pts_triangle_BEY[i].indice_pt_proche=3;nbre_pts_proche_p3++;}

		 if(fabs(dist_m1-dist_min_m)<=1e-6){dist_pm1=min(dist_m1,dist_pm1); liste_pts_triangle_BEY[i].indice_pt_proche_milieu=1; nbre_pts_proche_m1++;}
	else if(fabs(dist_m2-dist_min_m)<=1e-6){dist_pm2=min(dist_m2,dist_pm2); liste_pts_triangle_BEY[i].indice_pt_proche_milieu=2; nbre_pts_proche_m2++;}
	else if(fabs(dist_m3-dist_min_m)<=1e-6){dist_pm3=min(dist_m3,dist_pm3); liste_pts_triangle_BEY[i].indice_pt_proche_milieu=3; nbre_pts_proche_m3++;}
	}

	dist_pp1=sqrt(dist_pp1);
	dist_pp2=sqrt(dist_pp2);
	dist_pp3=sqrt(dist_pp3);

	dist_pm1=sqrt(dist_pm1);
	dist_pm2=sqrt(dist_pm2);
	dist_pm3=sqrt(dist_pm3);

   double denominateur=1./nbre_pts_triangle;

   densite_p1=nbre_pts_proche_p1*denominateur;
   densite_p2=nbre_pts_proche_p2*denominateur;
   densite_p3=nbre_pts_proche_p3*denominateur;

   densite_m1=nbre_pts_proche_m1*denominateur;
   densite_m2=nbre_pts_proche_m2*denominateur;
   densite_m3=nbre_pts_proche_m3*denominateur;

//calcul_normal_triangle_BEY();      // ICI


//if(aire_tr>=aire_min_triangle)
if(aire_triangle_2D>=aire_min_triangle)
{
if(dist_pp1>1e-6 && dist_pp1 > seuil_s1 ) densite_p1=0;  //BEY
if(dist_pp2>1e-6 && dist_pp2 > seuil_s2 ) densite_p2=0;  //BEY
if(dist_pp3>1e-6 && dist_pp3 > seuil_s3 ) densite_p3=0;  //BEY

if(dist_pm1>1e-6 && dist_pm1 > seuil_m1 ) densite_m1=0;  //BEY
if(dist_pm2>1e-6 && dist_pm2 > seuil_m2 ) densite_m2=0;  //BEY
if(dist_pm3>1e-6 && dist_pm3 > seuil_m3 ) densite_m3=0;  //BEY
}

   if(densite_p1==0 || densite_p2==0 || densite_p3==0)   eliminer_sommet=true;

}
//-------------------------------------------------------------------------------

void ListTriangle_BEY::determiner_pts_proches_sommets_triangles(bool triangulation_initiale)   //VERSION FINALE
{
if(triangulation_initiale==false)
{
triangle_initial *parcT=tete;

	while (parcT!=NULL)
	{
	if(parcT->getfiltre()==true){parcT=parcT->getsuiv();continue;}
//	if(parcT->getcalcul_pts_proche()==true){parcT=parcT->getsuiv();continue;}
//	if(parcT->getcalcul_voisins()==true){parcT=parcT->getsuiv();continue;}

	   parcT->seteliminer_sommet(false);

	   parcT->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);

	   parcT=parcT->getsuiv();
	}
}
else if(triangulation_initiale==true)
{
triangle_initial *parcT=tete;

	while (parcT!=NULL)
	{
	if(parcT->getfiltre()==true){parcT=parcT->getsuiv();continue;}

	   parcT->seteliminer_sommet(false);

	   parcT->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);

	   parcT=parcT->getsuiv();
	}
}


}

//------------------------------------------------------------------------------
ListTriangle_BEY_BEY & ListTriangle_BEY_BEY::determiner_pts_proches_sommets_triangles(bool triangulation_initiale)   //VERSION FINALE
{
if(triangulation_initiale==false)
{
triangle_initial_BEY *parcT=tete;

	while (parcT!=NULL)
	{
	if(parcT->getfiltre()==true){parcT=parcT->getsuiv();continue;}
	if(parcT->getnouveau_triangle()==false){parcT=parcT->getsuiv();continue;}//HERE BEY OK OK
//	if(parcT->getcalcul_pts_proche()==true){parcT=parcT->getsuiv();continue;}
//	if(parcT->getcalcul_voisins()==true){parcT=parcT->getsuiv();continue;}

	   parcT->seteliminer_sommet(false);

	   parcT->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);

	   parcT=parcT->getsuiv();
	}
}
else if(triangulation_initiale==true)
{
triangle_initial_BEY *parcT=tete;

	while (parcT!=NULL)
	{
	if(parcT->getfiltre()==true){parcT=parcT->getsuiv();continue;}

	   parcT->seteliminer_sommet(false);

	   parcT->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);

	   parcT=parcT->getsuiv();
	}
}


}

//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void __fastcall TAdaptive_Triangulation::CheckBox28Click(TObject *Sender)
{
//Adaptive_Triangulation->cible= Point_Clouds_Import->liste_triangle_adaptation->gettete();
ComboBox27Click(Sender);
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

//-----------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::ComboBox27Click(TObject *Sender)
{
int indice_triangle_cible=ComboBox27->Text.ToInt();

triangle_initial_BEY *parcT6=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();
while (parcT6!=NULL)
{
		  if(parcT6->getnum_triangle()==indice_triangle_cible)
		  {
          Adaptive_Triangulation->cible=parcT6;
          break;
          }

parcT6=parcT6->getsuiv();
}

if(Adaptive_Triangulation->cible->getfiltre()==false && Adaptive_Triangulation->cible->supprime==false)
{
/*Edit16->Text=FormatFloat("0.0000",parcT6->getliste_pts_triangle()->getdensite_p1());
Edit17->Text=FormatFloat("0.0000",parcT6->getliste_pts_triangle()->getdensite_p2());
Edit18->Text=FormatFloat("0.0000",parcT6->getliste_pts_triangle()->getdensite_p3());*/

parcT6->distance_max_pts_plan();

Edit16->Text=FormatFloat("0.0000",parcT6->getdensite_p1());
Edit17->Text=FormatFloat("0.0000",parcT6->getdensite_p2());
Edit18->Text=FormatFloat("0.0000",parcT6->getdensite_p3());

Edit37->Text=FormatFloat("0.0000000",parcT6->getdist_pt_plan_max());
}
else
{
Edit16->Text="";
Edit17->Text="";
Edit18->Text="";
Edit37->Text="";
}
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

double TAdaptive_Triangulation::calculer_angle_point(double x0, double y0)
 {
double result_final, angle_position;

double x,y; //coordonnées de n'importe quel point du plan

//x=-123456789.123456789;
//y=-123456789.123456789;

x=-9999.9999;
y=-9999.9999;

double R=sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0));

double bey=(y-y0)/R;
if(bey>1)bey=1;
if(bey<-1)bey=-1;

double result_initial=asin(bey)*180/pi;

if(x>=x0 && y>=y0)result_final=result_initial;
else if(x<=x0 && y>=y0)result_final=180-result_initial;
else if(x<=x0 && y<=y0)result_final=180+fabs(result_initial);
else if(x>=x0 && y<=y0)result_final=360-fabs(result_initial);

if(result_final==360)result_final=0;

angle_position=result_final;

return angle_position;

 }
//-------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//--------------Triangulation Uniforme------------------------------------------
//------------------------------------------------------------------------------
void __fastcall TAdaptive_Triangulation::Button9Click(TObject *Sender)
{
CheckBox21->Checked=false;

CheckBox24->Checked=false;
CheckBox22->Checked=false;
CheckBox27->Checked=false;

CheckBox23->Checked=false;
CheckBox26->Checked=false;
CheckBox25->Checked=false;

CheckBox28->Checked=false;
CheckBox29->Checked=false;
CheckBox42->Checked=false;

CheckBox43->Checked=false;

CheckBox30->Checked=false;
CheckBox47->Checked=false;

rapport=Adaptive_Triangulation->Edit11->Text.ToDouble()/100.;
aire_min_triangle=Adaptive_Triangulation->Edit19->Text.ToDouble() ;
/*
	 for (int i=0;i<nbre_cellule_y;i++)
		for (int j=0;j<nbre_cellule_x;j++)
			Point_Clouds_Import->cellule_points[i][j].initialiser_appartenace_pts();
*/
triangulation_initiale=true;  //Triangulation uniforme

//0)---------------Génération de la triangulation initiale dans le plan XY
 if (Edit9->Text=="" || Edit10->Text=="")
  {
  ShowMessage(" Donner le nombre de segments!!!");
  return;
  }

if (Edit9->Text.ToInt()==0 || Edit10->Text.ToInt()==0)
  {
  if (Edit9->Text.ToInt()==0)Edit9->Text="";
  if (Edit10->Text.ToInt()==0)Edit10->Text="";

  ShowMessage(" Le nombre de segments doit être strictement positif!!!!");
  return;
  }

Edit39->Text="";
Edit40->Text="";
Edit41->Text="";
Edit42->Text="";

double start, end;

  Button6->Visible=false;
  BitBtn1->Visible=false;

	 if(premiere_triangulation==true)
	 {
		delete Point_Clouds_Import->liste_triangle_adaptation_BEY;
		delete Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY;
		Button1Click(Sender);//création des cellules
	 }

start=clock();

	 Screen->Cursor= crHourGlass;
	 nbre_segments_x=Edit9->Text.ToInt();
	 nbre_segments_y=Edit10->Text.ToInt();

  Point_Clouds_Import->point_plan = new pt_plan*[nbre_segments_y+1];

 for (int j = 0; j < nbre_segments_y+1; j++)
	 Point_Clouds_Import->point_plan [j] = new pt_plan[nbre_segments_x+1];

 px1=Point_Clouds_Import->NUAGE_PTS_BEY.L/nbre_segments_x; //le pas suivant X(colonnes)
 py1=Point_Clouds_Import->NUAGE_PTS_BEY.l/nbre_segments_y; //le pas suivant y (lignes)

 double xmin1=Point_Clouds_Import->NUAGE_PTS_BEY.xmin;
 double ymin1=Point_Clouds_Import->NUAGE_PTS_BEY.ymin;

//---------------APPROCHE ADAPTATIVE--------------------

Point_Clouds_Import->liste_triangle_adaptation_BEY=new ListTriangle_BEY_BEY();
Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY=new ListTriangle_BEY_BEY();

//1)-----------affectation des triangles à la liste des triangles------------
   triangle_initial_BEY *parc;
//------------Génération des triangles-----------------
for (int i=0;i<nbre_segments_y;i++)    //génération des sommets des triangles dans le plan XY
 for (int j=0;j<nbre_segments_x;j++)
   {
	double x1=xmin1+j*px1;
	double y1=ymin1+i*py1;

	double x2=x1+px1;
	double y2=y1;

	double x3=x1+px1;
	double y3=y1+py1;

	double x4=x1;
	double y4=y1+py1;

		   //----1er triangle
		   parc=new triangle_initial_BEY();

		   parc->affecter_coordonnees_sommets_triangle(x1, y1, Point_Clouds_Import->NUAGE_PTS_BEY.zmin, x3, y3, Point_Clouds_Import->NUAGE_PTS_BEY.zmin, x4, y4, Point_Clouds_Import->NUAGE_PTS_BEY.zmin);

			   //Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc);

		   parc->determiner_pts_triangle();
		   parc->filtrage_un_triangle();

		   if(parc->filtre==false)
		   {
			   parc->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
			   parc->approximation_pts_triangle_plan_moindre_carre();
			   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc);
		   }
		   else
			   Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc);

		   //----2ème triangle
		   parc=new triangle_initial_BEY();

		   parc->affecter_coordonnees_sommets_triangle(x1, y1, Point_Clouds_Import->NUAGE_PTS_BEY.zmin, x2, y2, Point_Clouds_Import->NUAGE_PTS_BEY.zmin, x3, y3, Point_Clouds_Import->NUAGE_PTS_BEY.zmin);

			   //Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc);

		   parc->determiner_pts_triangle();
		   parc->filtrage_un_triangle();

		   if(parc->filtre==false)
		   {
			   parc->determiner_pts_proches_sommets_triangle(Adaptive_Triangulation->rapport, Adaptive_Triangulation->aire_min_triangle);
			   parc->approximation_pts_triangle_plan_moindre_carre();
			   Point_Clouds_Import->liste_triangle_adaptation_BEY->ajouter_Triangle(parc);
		   }
		   else
			   Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->ajouter_Triangle(parc);

   }

//-------------------------------------------------------------------------------
//--------------------------------------------------------------------------------


		CheckBox25->Enabled=false;
		CheckBox26->Enabled=false;

//triangle_initial_BEY *parcT6=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();
triangle_initial_BEY *parcT6=Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->gettete();

while (parcT6!=NULL)
{
if(parcT6->getfiltre()==true){CheckBox25->Enabled=true;CheckBox26->Enabled=true;break;}
parcT6=parcT6->getsuiv();
}
//------------------------------------------------------------------------------

Point_Clouds_Import->liste_triangle_adaptation_BEY->determiner_voisins_triangles(Adaptive_Triangulation->triangulation_initiale); //OK

//---------------------------------------------

  CheckBox3->Visible=true;
  CheckBox4->Visible=true;
  ComboBox2->Visible=true;
  ComboBox4->Visible=true;
  CheckBox5->Visible=true;
  ComboBox5->Visible=true;
  CheckBox6->Visible=true;
  ComboBox6->Visible=true;
  CheckBox7->Visible=true;
  ComboBox7->Visible=true;
  CheckBox8->Visible=true;
  ComboBox8->Visible=true;
  GroupBox4->Visible=true;
  GroupBox7->Visible=true;

	  px_s=Point_Clouds_Import->NUAGE_PTS_BEY.L/Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles; //le pas suivant X(colonnes)
	  py_s=Point_Clouds_Import->NUAGE_PTS_BEY.l/Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles; //le pas suivant y (lignes)

	  xmin=Point_Clouds_Import->NUAGE_PTS_BEY.xmin;
	  xmax=Point_Clouds_Import->NUAGE_PTS_BEY.xmax;

	  ymin=Point_Clouds_Import->NUAGE_PTS_BEY.ymin;
	  ymax=Point_Clouds_Import->NUAGE_PTS_BEY.ymax;

double ecart_max_zmax, ecart_max_zmin, ecart_max_zmoy;

Affectation_Numeros_Sommets_Calcul_Zmax_Zmin_Zmoy_Sommets();

Type_Z_Coordonnee="Z_MAX";
Mise_A_Jour_Sommets_Triangles_Calcul_Ecarts_Max_Triangles_Erreurs_Max_Min();
ecart_max_zmax=Adaptive_Triangulation->dist_max;
   Triangulation_Results->Edit25->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_min);
   Triangulation_Results->Edit26->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_max);

Type_Z_Coordonnee="Z_MIN";
Mise_A_Jour_Sommets_Triangles_Calcul_Ecarts_Max_Triangles_Erreurs_Max_Min();
ecart_max_zmin=Adaptive_Triangulation->dist_max;
   Triangulation_Results->Edit27->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_min);
   Triangulation_Results->Edit28->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_max);

Type_Z_Coordonnee="Z_MOY";
Mise_A_Jour_Sommets_Triangles_Calcul_Ecarts_Max_Triangles_Erreurs_Max_Min();
ecart_max_zmoy=Adaptive_Triangulation->dist_max;
   Triangulation_Results->Edit29->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_min);
   Triangulation_Results->Edit30->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_max);

double ecart_min=min(ecart_max_zmax,min(ecart_max_zmin,ecart_max_zmoy));

if(ecart_min==ecart_max_zmax)
{
Type_Z_Coordonnee="Z_MAX";
Mise_A_Jour_Sommets_Triangles_Calcul_Ecarts_Max_Triangles_Erreurs_Max_Min();
}

else if(ecart_min==ecart_max_zmin)
{
Type_Z_Coordonnee="Z_MIN";
Mise_A_Jour_Sommets_Triangles_Calcul_Ecarts_Max_Triangles_Erreurs_Max_Min();
}

else if(ecart_min==ecart_max_zmoy)
{
Type_Z_Coordonnee="Z_MOY";
Mise_A_Jour_Sommets_Triangles_Calcul_Ecarts_Max_Triangles_Erreurs_Max_Min();
}

   Adaptive_Triangulation->Edit34->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_max);
   Adaptive_Triangulation->Edit33->Text=FormatFloat("0.0000000",Adaptive_Triangulation->dist_min);

//--------------------------------------------------
//-----------Temps de calcul
end=clock();

Button19Click(Sender);  //calcul du nombre de triangles, de points et de sommets
Triangulation_Results->Show();

double time=end-start; //ms

double time_s=time/1000;
double time_m=time_s/60;

double temps_m=time_m; //temps de calcul total en minutes

int temps_calcul_j=(int)(temps_m/(24*60));
Edit39->Text=temps_calcul_j;  //nbre de jours

int temps_calcul_h=(int)((temps_m-temps_calcul_j*1440)/60);
Edit40->Text=temps_calcul_h;   //nbre d'heures

double temps_reste=temps_m-(temps_calcul_h*60+temps_calcul_j*1440);
int temps_calcul_m=(int)temps_reste;

Edit41->Text=temps_calcul_m;  //nbre de minutes

double temps_calcul_s=(temps_reste-temps_calcul_m)*60;

Edit42->Text=FormatFloat("0.00",temps_calcul_s);  //nbre de secondes

//------------------------------------
//------------------------------------

triangle_initial_BEY *parcT66=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();
ComboBox27->Clear();
while (parcT66!=NULL)
{
//	parcT66->triangle_pour_calculer_voisin=false;

	if(parcT66->getfiltre()==false && parcT66->supprime==false)
	{
	ComboBox27->Items->Add(parcT66->getnum_triangle());
//-------------------Calcul des limites Zmin et Zmax des pts du triangle ainsi que des ecarts max
	parcT66->calculer_zmax_zmin_pts_triangle();
	parcT66->calculer_ecart_max_droite();
	}
parcT66=parcT66->getsuiv();
}
ComboBox27->ItemIndex=0;


//---------------------------------------
CheckBox27->Checked=true;

Visualization->DrawObjects();

approximation_effectuee=false;
premiere_triangulation=true;

//------------------------------------------------------------------------------

Point_Clouds_Import->liste_triangle_adaptation_BEY->determiner_parametres_filtration_triangles();

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

Screen->Cursor= crDefault;

int frequence=3000;
int duree=1000;
Beep(frequence,duree);

//---------------------------------------------
creation_cellules=false;
//	 if(creation_cellules==true)
	 {
		 for (int j = 0; j < nbre_cellule_y; j++)
			delete[] Point_Clouds_Import->cellule_points_BEY[j];

		 delete[] Point_Clouds_Import->cellule_points_BEY; //declaration de la matrice cellules
	 }

GroupBox2->Visible=false;
//---------------------------------------------

//Point_Clouds_Import->NUAGE_PTS_BEY.liberer_nuage_pts_BEY();
}
//---------------------------------------------------------------------------

//----------------------------------------------------------
void __fastcall TAdaptive_Triangulation::Button1Click(TObject *Sender)
{

//_______________________________________exception d'edit

 if (Edit1->Text=="" || Edit2->Text=="")
  {
  ShowMessage(" Donner le nombre de cellules");
  return;
  }

if (Edit1->Text.ToInt()==0 || Edit2->Text.ToInt()==0)
  {

  if (Edit1->Text.ToInt()==0)Edit1->Text="";
  if (Edit2->Text.ToInt()==0)Edit2->Text="";

  ShowMessage(" Le nombre de cellules doit être strictement positif!!!!");
  return;
  }

  Button6->Visible=false;
  BitBtn1->Visible=false;
    
    Screen->Cursor= crHourGlass;

//------------
  CheckBox3->Visible=false;
  CheckBox4->Visible=false;
  ComboBox2->Visible=false;
  ComboBox4->Visible=false;
  CheckBox5->Visible=false;
  ComboBox5->Visible=false;
  CheckBox6->Visible=false;
  ComboBox6->Visible=false;
  CheckBox7->Visible=false;
  ComboBox7->Visible=false;
  CheckBox8->Visible=false;
  ComboBox8->Visible=false;
  GroupBox4->Visible=false;
  GroupBox7->Visible=false;
  GroupBox5->Visible=false;
  GroupBox6->Visible=false;

  Edit3->Text="";
  Edit4->Text="";
//------------
//__________________________________________________
	 if(creation_cellules==true)
	 {
		 for (int j = 0; j < nbre_cellule_y; j++)
			delete[] Point_Clouds_Import->cellule_points_BEY[j];

		 delete[] Point_Clouds_Import->cellule_points_BEY; //declaration de la matrice cellules
	 }

	 nbre_cellule_x=Edit1->Text.ToInt();
	 nbre_cellule_y=Edit2->Text.ToInt();
	 double zmin, zmax;


//	 px=Point_Clouds_Import->nuage_pts_BEY->getL()/nbre_cellule_x; //le pas suivant X(colonnes)
//	 py=Point_Clouds_Import->nuage_pts_BEY->getl()/nbre_cellule_y; //le pas suivant y (lignes)

	  px=Point_Clouds_Import->NUAGE_PTS_BEY.L/nbre_cellule_x; //le pas suivant X(colonnes)
	  py=Point_Clouds_Import->NUAGE_PTS_BEY.l/nbre_cellule_y; //le pas suivant y (lignes)

creation_cellules=true;


 Point_Clouds_Import->cellule_points_BEY = new cellule_BEY*[nbre_cellule_y]; //declaration de la matrice cellules
   for (int j = 0; j < nbre_cellule_y; j++)
	Point_Clouds_Import->cellule_points_BEY [j] = new cellule_BEY [nbre_cellule_x];

creer_liste_BEY();


double xmin1=Point_Clouds_Import->NUAGE_PTS_BEY.xmin;
double ymin1=Point_Clouds_Import->NUAGE_PTS_BEY.ymin;

for (int i=0;i<nbre_cellule_y;i++)
 {
		for (int j=0;j<nbre_cellule_x;j++)
		{
		 //noeud_point_nuage_BEY *test;

		 //test=Point_Clouds_Import->cellule_points_BEY[i][j].getliste_pts_cellule_BEY()->getdebut();

		int nbre_pts=Point_Clouds_Import->cellule_points_BEY[i][j].nbre_pts_cellule;
		//if(test==NULL)
		if(nbre_pts==0)
		{
		   Point_Clouds_Import->cellule_points_BEY[i][j].setzmin_cellule(Point_Clouds_Import->NUAGE_PTS_BEY.zmin);
		   //Point_Clouds_Import->cellule_points_BEY[i][j].setzmax_cellule(Point_Clouds_Import->NUAGE_PTS_BEY.zmax);
		   Point_Clouds_Import->cellule_points_BEY[i][j].setzmax_cellule(Point_Clouds_Import->NUAGE_PTS_BEY.zmin);
		}
		else
		{
//		   zmin=test->getpoint()->getz();
//		   zmax=test->getpoint()->getz();

		   zmin=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[0]->z;
		   zmax=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[0]->z;

		 //test=test->getsuiv1();

		 //while(test!=NULL)
		 for(int ii=1; ii<nbre_pts; ii++)
		 {
//		  if(zmin>test->getpoint()->getz())zmin=test->getpoint()->getz();
//		  if(zmax<test->getpoint()->getz())zmax=test->getpoint()->getz();
//		  test=test->getsuiv1();


		  if(zmin>Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->z)zmin=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->z;
		  if(zmax<Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->z)zmax=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->z;
		 }
		 Point_Clouds_Import->cellule_points_BEY[i][j].setzmin_cellule(zmin);
		 Point_Clouds_Import->cellule_points_BEY[i][j].setzmax_cellule(zmax);
		}

	   Point_Clouds_Import->cellule_points_BEY[i][j].setxmin_cellule(xmin1+j*px);
	   Point_Clouds_Import->cellule_points_BEY[i][j].setxmax_cellule(xmin1+j*px+px);

	   Point_Clouds_Import->cellule_points_BEY[i][j].setymin_cellule(ymin1+i*py);
	   Point_Clouds_Import->cellule_points_BEY[i][j].setymax_cellule(ymin1+i*py+py);
	}

 }

xmin1=Point_Clouds_Import->NUAGE_PTS_BEY.xmin;
ymin1=Point_Clouds_Import->NUAGE_PTS_BEY.ymin;

double px_s=Point_Clouds_Import->NUAGE_PTS_BEY.L/Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles; //le pas suivant X(colonnes)
double py_s=Point_Clouds_Import->NUAGE_PTS_BEY.l/Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles; //le pas suivant y (lignes)

for (int i=0;i<Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles;i++)
{
 for (int j=0;j<Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles;j++)
 {
	Point_Clouds_Import->Cellules_Sommets_Triangles[i][j].setxmin_cellule(xmin1+j*px_s);
//	Point_Clouds_Import->Cellules_Sommets_Triangles[i][j].setxmax_cellule(xmin1+j*px_s+px_s);

	Point_Clouds_Import->Cellules_Sommets_Triangles[i][j].setymin_cellule(ymin1+i*py_s);
//	Point_Clouds_Import->Cellules_Sommets_Triangles[i][j].setymax_cellule(ymin1+i*py_s+py_s);

//	Point_Clouds_Import->Cellules_Sommets_Triangles[i][j].setzmin_cellule(Point_Clouds_Import->NUAGE_PTS_BEY.zmin);
//	Point_Clouds_Import->Cellules_Sommets_Triangles[i][j].setzmax_cellule(Point_Clouds_Import->NUAGE_PTS_BEY.zmax);
 }
}




//----------------------------------------------------------------------------------------
//--------------------------------------------------------------

//--------------------------------------------------------------

//      Adaptive_Triangulation->pas_cell_x=Point_Clouds_Import->nuage_pts_BEY->getL()/Adaptive_Triangulation->nbre_cellule_x; //le pas suivant X(colonnes)
//	  Adaptive_Triangulation->pas_cell_y=Point_Clouds_Import->nuage_pts_BEY->getl()/Adaptive_Triangulation->nbre_cellule_y; //le pas suivant y (lignes)

	pas_cell_x=px;
	pas_cell_y=py;

	   GroupBox2->Visible=true;
       //GroupBox3->Visible=true;
       Visualization->DrawObjects();
 Screen->Cursor= crDefault;

int frequence=3000;
int duree=1000;
Beep(frequence,duree);

GroupBox2->Visible=true;

}; //fonction


//______________________________________________
void TAdaptive_Triangulation::creer_liste()
{

}

//______________________________________________
void TAdaptive_Triangulation::creer_liste_BEY()
{
	  int i, j;
	  point_nuage  *p;

//	  test=Point_Clouds_Import->nuage_pts_BEY->getdebut();

//	  px=Point_Clouds_Import->nuage_pts_BEY->getL()/nbre_cellule_x; //le pas suivant X(colonnes)
//	  py=Point_Clouds_Import->nuage_pts_BEY->getl()/nbre_cellule_y; //le pas suivant y (lignes)

	  px=Point_Clouds_Import->NUAGE_PTS_BEY.L/nbre_cellule_x; //le pas suivant X(colonnes)
	  py=Point_Clouds_Import->NUAGE_PTS_BEY.l/nbre_cellule_y; //le pas suivant y (lignes)


	  double xmin=Point_Clouds_Import->NUAGE_PTS_BEY.xmin;
	  double xmax=Point_Clouds_Import->NUAGE_PTS_BEY.xmax;

	  double ymin=Point_Clouds_Import->NUAGE_PTS_BEY.ymin;
	  double ymax=Point_Clouds_Import->NUAGE_PTS_BEY.ymax;

	  int nbre_pts=Point_Clouds_Import->NUAGE_PTS_BEY.nbre_pts_total;

	 for(int ii=0; ii<nbre_pts; ii++)
	 {
		 if (fabs(Point_Clouds_Import->NUAGE_PTS_BEY.nuage_pts_BEY[ii].getx()-xmin)<=1e-3)
			 j=0;
		 else if (fabs(Point_Clouds_Import->NUAGE_PTS_BEY.nuage_pts_BEY[ii].getx()-xmax)<=1e-3)
			 j=nbre_cellule_x-1;
		 else
			 j=(int)((Point_Clouds_Import->NUAGE_PTS_BEY.nuage_pts_BEY[ii].getx()-xmin)/px);

		 if (fabs(Point_Clouds_Import->NUAGE_PTS_BEY.nuage_pts_BEY[ii].gety()-ymin)<=1e-3)
			 i=0;
		 else if (fabs(Point_Clouds_Import->NUAGE_PTS_BEY.nuage_pts_BEY[ii].gety()-ymax)<=1e-3)
			 i=nbre_cellule_y-1;
		 else
			 i=(int)((Point_Clouds_Import->NUAGE_PTS_BEY.nuage_pts_BEY[ii].gety()-ymin)/py);

		 p=Point_Clouds_Import->NUAGE_PTS_BEY.retourner_adresse_pt(ii);
		 p->inserer_pt_triangle=false;

/*
		 test = new noeud_point_nuage_BEY;
		 test->setpoint(p);
		 Point_Clouds_Import->cellule_points[i][j].getliste_pts_cellule_BEY()->inserer_pts_cellule(test);
*/
		 Point_Clouds_Import->cellule_points_BEY[i][j].ajouter_pt(p);
		 //Point_Clouds_Import->cellule_points[i][j].ajouter_pt_int(ii);
	 }
}

///__________________________________________________________
liste_point & liste_point::inserer_pts_cellule(noeud_point_nuage * c)

{
  if(debut==NULL)
  {
   debut=c;
   debut->setsuiv1(NULL);
   debut->setprec1(NULL);
  }
  else
  {
    if(fin==NULL)                             // un seul element
    {
    fin=c;
    fin->setsuiv1(NULL);

    fin->setprec1(debut);
    debut->setsuiv1(c);

    }
    else
	{
	 c->setprec1(fin);
	 fin->setsuiv1(c);
	 fin=c;
	 fin->setsuiv1(NULL);
	}

  }

	 return *this;
}

//---------------------------------------------------------------------------
///__________________________________________________________
liste_point_BEY & liste_point_BEY::inserer_pts_cellule(noeud_point_nuage_BEY * c)

{
  if(debut==NULL)
  {
   debut=c;
   debut->setsuiv1(NULL);
//   debut->setprec1(NULL);
  }
  else
  {
	if(fin==NULL)                             // un seul element
	{
	fin=c;
	fin->setsuiv1(NULL);

//	fin->setprec1(debut);
	debut->setsuiv1(c);

	}
	else
	{
//	 c->setprec1(fin);
	 fin->setsuiv1(c);
	 fin=c;
	 fin->setsuiv1(NULL);
	}

  }

	 return *this;
}

//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::Edit1KeyPress(TObject *Sender, char &Key)
{
switch (Key)
 {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case 0x08:break;
  default : Key=0x0;
 }
}

 //___________________________________________________________________________

void __fastcall TAdaptive_Triangulation::CheckBox1Click(TObject *Sender)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::FormShow(TObject *Sender)
{
Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles=1111;
Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles_moins_un=Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles-1;

 Point_Clouds_Import->Cellules_Sommets_Triangles = new cellule_sommets_triangles*[Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles]; //declaration de la matrice cellules
   for (int j = 0; j < Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles; j++)
	Point_Clouds_Import->Cellules_Sommets_Triangles [j] = new cellule_sommets_triangles [Point_Clouds_Import->Nbre_Cellules_Sommets_Triangles];

red_surface=0;
green_surface=1;
blue_surface=0;

nbre_segments_x=-1;
nbre_segments_y=-1;
premiere_triangulation=false;
creation_cellules=false;
//creation_cellules_sommets_triangles=false;
//nbre_cellules_sommets=50;
//Label7->Caption=Point_Clouds_Import->OpenDialog1->FileName;

Left=Screen->Width-Width;
Top=(Screen->Height-Height)/2;;
Top=-6;

maj=false;
//Edit1->Text="";
//Edit2->Text="";

Edit3->Text="";
Edit4->Text="";

GroupBox2->Visible=false;
CheckBox1->Checked=false;
CheckBox2->Checked=false;
GroupBox3->Visible=false;
GroupBox5->Visible=false;
GroupBox6->Visible=false;
GroupBox4->Visible=false;
GroupBox7->Visible=false;
CheckBox3->Checked=false;
CheckBox4->Checked=false;
CheckBox3->Visible=false;
CheckBox4->Visible=false;
ComboBox2->Visible=false;
ComboBox4->Visible=false;
CheckBox5->Visible=false;
ComboBox5->Visible=false;
CheckBox6->Visible=false;
ComboBox6->Visible=false;
CheckBox7->Visible=false;
ComboBox7->Visible=false;
CheckBox8->Visible=false;
ComboBox8->Visible=false;
CheckBox12->Enabled=false;
ComboBox12->Enabled=false;

BitBtn1->Visible=false;
//Panel2->Visible=false;
Button6->Visible=false;


Edit39->Text="";
Edit40->Text="";
Edit41->Text="";
Edit42->Text="";

Visualization->DrawObjects();



}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::FormClose(TObject *Sender, TCloseAction &Action)
{
Visualization->Close();
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::CheckBox2Click(TObject *Sender)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------



//_______________________________________________

void __fastcall TAdaptive_Triangulation::Button2Click(TObject *Sender)
{


 if (Edit3->Text=="" || Edit4->Text=="")
  {
  ShowMessage(" Donner le nombre de segments!!!");
  return;
  }

if (Edit3->Text.ToInt()==0 || Edit4->Text.ToInt()==0)
  {

  if (Edit3->Text.ToInt()==0)Edit3->Text="";
  if (Edit4->Text.ToInt()==0)Edit4->Text="";

  ShowMessage(" Le nombre de segments doit être strictement positif!!!!");
  return;
  }

  Button6->Visible=false;
  BitBtn1->Visible=false;

     Screen->Cursor= crHourGlass;
     nbre_segments_x=Edit3->Text.ToInt();
     nbre_segments_y=Edit4->Text.ToInt();

  Point_Clouds_Import->point_plan = new pt_plan*[nbre_segments_y+1];

 for (int j = 0; j < nbre_segments_y+1; j++)
     Point_Clouds_Import->point_plan [j] = new pt_plan[nbre_segments_x+1];



 px1=Point_Clouds_Import->nuage_pts_BEY->getL()/nbre_segments_x; //le pas suivant X(colonnes)
 py1=Point_Clouds_Import->nuage_pts_BEY->getl()/nbre_segments_y; //le pas suivant y (lignes)

for (int i=0;i<nbre_segments_y+1;i++)
 { for (int j=0;j<nbre_segments_x+1;j++)
   {


       double xmin1=Point_Clouds_Import->nuage_pts_BEY->getxmin();
       double ymin1=Point_Clouds_Import->nuage_pts_BEY->getymin();
       Point_Clouds_Import->point_plan[i][j].setx_pt(xmin1+j*px1);
       Point_Clouds_Import->point_plan[i][j].sety_pt(ymin1+i*py1);

   }
  CheckBox3->Visible=true;
  CheckBox4->Visible=true;
  ComboBox2->Visible=true;
  ComboBox4->Visible=true;
  CheckBox5->Visible=true;
  ComboBox5->Visible=true;
  CheckBox6->Visible=true;
  ComboBox6->Visible=true;
  CheckBox7->Visible=true;
  ComboBox7->Visible=true;
  CheckBox8->Visible=true;
  ComboBox8->Visible=true;
  GroupBox4->Visible=true;
  GroupBox7->Visible=true;


 }
//--------------------------------triangle-----------------------------




    px1=Point_Clouds_Import->nuage_pts_BEY->getL()/nbre_segments_x; //le pas suivant X(colonnes)
    py1=Point_Clouds_Import->nuage_pts_BEY->getl()/nbre_segments_y; //le pas suivant y (lignes)

 Point_Clouds_Import->triangle_plan = new triangle_initial*[nbre_segments_y];

 for (int j = 0; j < nbre_segments_y; j++)
     Point_Clouds_Import->triangle_plan [j] = new triangle_initial[nbre_segments_x*2];

    for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {


      if(j % 2 == 0)

      {
      Point_Clouds_Import->triangle_plan[i][j].setp1(&Point_Clouds_Import->point_plan[i][j/2]);
      Point_Clouds_Import->triangle_plan[i][j].setp2(&Point_Clouds_Import->point_plan[i+1][j/2+1]);
      Point_Clouds_Import->triangle_plan[i][j].setp3(&Point_Clouds_Import->point_plan[i+1][j/2]);


       }

      if(j % 2 == 1)
      {

      Point_Clouds_Import->triangle_plan[i][j].setp1(&Point_Clouds_Import->point_plan[i][(j-1)/2]);
      Point_Clouds_Import->triangle_plan[i][j].setp2(&Point_Clouds_Import->point_plan[i][((j-1)/2)+1]);
      Point_Clouds_Import->triangle_plan[i][j].setp3(&Point_Clouds_Import->point_plan[i+1][((j-1)/2)+1]);
      }

     }


  }


//--------------------------------limites triangle---------------------

 double xmin_t1,xmax_t1,ymin_t1,ymax_t1;
 for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {

        xmin_t1=Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt();
        xmax_t1=Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt();

        ymin_t1=Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt();
        ymax_t1=Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt();

  //__________________________xmin,xmax

      if(xmin_t1>Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt())
      xmin_t1=Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt();

      if(xmax_t1<Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt())
      xmax_t1=Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt();


      if(xmin_t1>Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt())
      xmin_t1=Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt();

      if(xmax_t1<Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt())
      xmax_t1=Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt();


  //_____________________________Ymin,Ymax

   if(ymin_t1>Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt())
      ymin_t1=Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt();

      if(ymax_t1<Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt())
      ymax_t1=Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt();


      if(ymin_t1>Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt())
      ymin_t1=Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt();

      if(ymax_t1<Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt())
      ymax_t1=Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt();



      Point_Clouds_Import->triangle_plan[i][j].setxmin_t(xmin_t1);
      Point_Clouds_Import->triangle_plan[i][j].setxmax_t(xmax_t1);
      Point_Clouds_Import->triangle_plan[i][j].setymin_t(ymin_t1);
      Point_Clouds_Import->triangle_plan[i][j].setymax_t(ymax_t1);
      }



  }

 //--------------------------------liste points triangle------------------------
      noeud_point_nuage_BEY *test;
      test=Point_Clouds_Import->nuage_pts_BEY->getdebut();
       int i,j;

       px1=Point_Clouds_Import->nuage_pts_BEY->getL()/nbre_segments_x;
       py1=Point_Clouds_Import->nuage_pts_BEY->getl()/nbre_segments_y;

       double alpha12,alpha23,alpha31,alpha1,alpha2;
       double xa,xb,xp,ya,yb,yp;
       double xa1,ya1,xb1,yb1,xc1,yc1,xd1,yd1,xp1,yp1;

       while (test!=NULL)
      {



		   j =(int)((test->getpoint()->getx()-Point_Clouds_Import->nuage_pts_BEY->getxmin())/px1);
		   i =(int)((test->getpoint()->gety()-Point_Clouds_Import->nuage_pts_BEY->getymin())/py1);

             if (j==nbre_segments_x) j=nbre_segments_x-1;
             if (i==nbre_segments_y) i=nbre_segments_y-1;

//----------------------------------------------------------------------


        xa1=Point_Clouds_Import->triangle_plan[i][j*2].getp1()->getx_pt();
        ya1=Point_Clouds_Import->triangle_plan[i][j*2].getp1()->gety_pt();

        xb1=Point_Clouds_Import->triangle_plan[i][j*2].getp2()->getx_pt();
        yb1=Point_Clouds_Import->triangle_plan[i][j*2].getp2()->gety_pt();

        xc1=Point_Clouds_Import->triangle_plan[i][j*2].getp3()->getx_pt();
        yc1=Point_Clouds_Import->triangle_plan[i][j*2].getp3()->gety_pt();


        xd1=Point_Clouds_Import->triangle_plan[i][(j*2)+1].getp2()->getx_pt();
        yd1=Point_Clouds_Import->triangle_plan[i][(j*2)+1].getp2()->gety_pt();

        xp1=test->getpoint()->getx();
        yp1=test->getpoint()->gety();

         if((fabs(xa1-xp1)<=precision_calcul && fabs(ya1-yp1)<=precision_calcul)||
            (fabs(xb1-xp1)<=precision_calcul && fabs(yb1-yp1)<=precision_calcul)||
            (fabs(xc1-xp1)<=precision_calcul && fabs(yc1-yp1)<=precision_calcul)||
            (fabs(yp1-yb1)<=precision_calcul && xp1>=xc1 && xp1<=xb1)||
            (fabs(xp1-xa1)<=precision_calcul && yp1>=ya1 && yp1<=yc1))
           {
           Point_Clouds_Import->triangle_plan[i][2*j].getliste_pts_triangle()->inserer_pts_triangle(test);
           Point_Clouds_Import->triangle_plan[i][2*j].nbre_points();
           test=test->getsuiv();
           }
         else
		   if ((fabs(xd1-xp1)<=precision_calcul && fabs(yd1-yp1)<=precision_calcul)||
			(fabs(yp1-ya1)<=precision_calcul && xp1>=xa1 && xp1<=xd1)||
			(fabs(xp1-xd1)<=precision_calcul && yp1>=yd1 && yp1<=yb1))
           {
           Point_Clouds_Import->triangle_plan[i][2*j+1].getliste_pts_triangle()->inserer_pts_triangle(test);
           Point_Clouds_Import->triangle_plan[i][2*j+1].nbre_points();
           test=test->getsuiv();
           }
           else
           if (fabs(xp1-xa1)>=precision_calcul && (fabs((py1/px1)-((yp1-ya1)/(xp1-xa1)))<=precision_calcul))
           {
           Point_Clouds_Import->triangle_plan[i][2*j+1].getliste_pts_triangle()->inserer_pts_triangle(test);
           Point_Clouds_Import->triangle_plan[i][2*j+1].nbre_points();
            test=test->getsuiv();
           }


              else
              {


//_________________________________

              xa=Point_Clouds_Import->triangle_plan[i][2*j].getp1()->getx_pt();
              ya=Point_Clouds_Import->triangle_plan[i][2*j].getp1()->gety_pt();

              xb=Point_Clouds_Import->triangle_plan[i][2*j].getp2()->getx_pt();
              yb=Point_Clouds_Import->triangle_plan[i][2*j].getp2()->gety_pt();

              xp=test->getpoint()->getx();
              yp=test->getpoint()->gety();


              alpha12=calcul_angle_deux_segments(xa,ya,xb,yb,xp,yp);


              xa=Point_Clouds_Import->triangle_plan[i][2*j].getp2()->getx_pt();
              ya=Point_Clouds_Import->triangle_plan[i][2*j].getp2()->gety_pt();

              xb=Point_Clouds_Import->triangle_plan[i][2*j].getp3()->getx_pt();
              yb=Point_Clouds_Import->triangle_plan[i][2*j].getp3()->gety_pt();

              xp=test->getpoint()->getx();
              yp=test->getpoint()->gety();


             alpha23=calcul_angle_deux_segments(xa,ya,xb,yb,xp,yp);


              xa=Point_Clouds_Import->triangle_plan[i][2*j].getp3()->getx_pt();
              ya=Point_Clouds_Import->triangle_plan[i][2*j].getp3()->gety_pt();

              xb=Point_Clouds_Import->triangle_plan[i][2*j].getp1()->getx_pt();
              yb=Point_Clouds_Import->triangle_plan[i][2*j].getp1()->gety_pt();

              xp=test->getpoint()->getx();
              yp=test->getpoint()->gety();


             alpha31=calcul_angle_deux_segments(xa,ya,xb,yb,xp,yp);

             alpha1=alpha12+alpha23+alpha31;


//__________________________

              xa=Point_Clouds_Import->triangle_plan[i][2*j+1].getp1()->getx_pt();
              ya=Point_Clouds_Import->triangle_plan[i][2*j+1].getp1()->gety_pt();

              xb=Point_Clouds_Import->triangle_plan[i][2*j+1].getp2()->getx_pt();
              yb=Point_Clouds_Import->triangle_plan[i][2*j+1].getp2()->gety_pt();

              xp=test->getpoint()->getx();
              yp=test->getpoint()->gety();



              alpha12=calcul_angle_deux_segments(xa,ya,xb,yb,xp,yp);


              xa=Point_Clouds_Import->triangle_plan[i][2*j+1].getp2()->getx_pt();
              ya=Point_Clouds_Import->triangle_plan[i][2*j+1].getp2()->gety_pt();

              xb=Point_Clouds_Import->triangle_plan[i][2*j+1].getp3()->getx_pt();
              yb=Point_Clouds_Import->triangle_plan[i][2*j+1].getp3()->gety_pt();

              xp=test->getpoint()->getx();
              yp=test->getpoint()->gety();


             alpha23=calcul_angle_deux_segments(xa,ya,xb,yb,xp,yp);


              xa=Point_Clouds_Import->triangle_plan[i][2*j+1].getp3()->getx_pt();
              ya=Point_Clouds_Import->triangle_plan[i][2*j+1].getp3()->gety_pt();

              xb=Point_Clouds_Import->triangle_plan[i][2*j+1].getp1()->getx_pt();
              yb=Point_Clouds_Import->triangle_plan[i][2*j+1].getp1()->gety_pt();

              xp=test->getpoint()->getx();
              yp=test->getpoint()->gety();


             alpha31=calcul_angle_deux_segments(xa,ya,xb,yb,xp,yp);

             alpha2=alpha12+alpha23+alpha31;

			  if (fabs(alpha1)>pi)
              {
              Point_Clouds_Import->triangle_plan[i][j*2].getliste_pts_triangle()->inserer_pts_triangle(test);

			  Point_Clouds_Import->triangle_plan[i][2*j].nbre_points();
			  }

			  if (fabs(alpha2)>pi)
               {
			   Point_Clouds_Import->triangle_plan[i][j*2+1].getliste_pts_triangle()->inserer_pts_triangle(test);

               Point_Clouds_Import->triangle_plan[i][2*j+1].nbre_points();
              }

              test=test->getsuiv();
             }


          }


//nbre de points des triangles
int somme=0;
     for (int i=0;i<nbre_segments_y;i++)
     {
     for (int j=0;j<nbre_segments_x*2;j++)
      {
       somme=somme+Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle();
      }
     }

     if(somme!=Point_Clouds_Import->nuage_pts_BEY->getnbre_pt())
     {
     ShowMessage("Erreur dans votre programme  !!!!!!!");
     }

//
//-------------------------------------------------
     double a[3][3],b[3],x[3];
     double xx,yy,zz;
     double x1,y1,x2,y2,x3,y3;

     for (int i=0;i<nbre_segments_y;i++)
     {
     for (int j=0;j<nbre_segments_x*2;j++)
      {

	   noeud_point_nuage_BEY *temp;
	   noeud_point_nuage_BEY *temp1;

             if (Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle()<3)Point_Clouds_Import->triangle_plan[i][j].setfiltre(true);



                if (Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false)
                {
                temp=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();

                temp1=temp->getsuiv2();

                     while (temp1!=NULL)
                     {


                          if (fabs(temp->getpoint()->getx()-temp1->getpoint()->getx())<precision_calcul)
                          {
                          Point_Clouds_Import->triangle_plan[i][j].setfiltre(true);
                          temp1=temp1->getsuiv2();
                          continue;
                          }
                          else
                          {
                              Point_Clouds_Import->triangle_plan[i][j].setfiltre(false);
                              break;
                          }


                     }

                }







                if (Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false)
                {
                temp=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();

                temp1=temp->getsuiv2();

                     while (temp1!=NULL)
                     {


                          if (fabs(temp->getpoint()->gety()-temp1->getpoint()->gety())<precision_calcul)
                          {
                          Point_Clouds_Import->triangle_plan[i][j].setfiltre(true);
                          temp1=temp1->getsuiv2();
                          continue;
                          }
                          else
                          {
                              Point_Clouds_Import->triangle_plan[i][j].setfiltre(false);
                              break;
                          }


                     }

                }




         if (Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false)
                {

                Point_Clouds_Import->triangle_plan[i][j].setfiltre(true);

                temp=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();

                double angle0=calculer_angle_point(temp->getpoint()->getx(), temp->getpoint()->gety()); //angle par rapport à l'axe X du premier point

                temp1=temp->getsuiv2();

                   while(temp1!=NULL)
                   {
                     if(fabs(angle0-calculer_angle_point(temp1->getpoint()->getx(),temp1->getpoint()->gety()))>precision_calcul)
                     {
                     Point_Clouds_Import->triangle_plan[i][j].setfiltre(false);
                     break;
                     }

                     temp1=temp1->getsuiv2();
                   }




                }

//--------------------------------------fin filtre----------------------------


      if (Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;

       double a00=0;
       double a01=0;
       double a02=0;

       double a10=0;
       double a11=0;
       double a12=0;

       double a20=0;
       double a21=0;
       double a22=0;

       double b0=0;
       double b1=0;
       double b2=0;

	 noeud_point_nuage_BEY *test;

          test=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();
          Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle();

         while (test!=NULL)
           {


            xx=test->getpoint()->getx();

            yy=test->getpoint()->gety();

            zz=test->getpoint()->getz();

            a00=a00+xx*xx;
            a01=a01+xx*yy;
            a02=a02+xx;

            a10=a10+xx*yy;
            a11=a11+yy*yy;
            a12=a12+yy;

            a20=a20+xx;
            a21=a21+yy;
			a22=Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle();


           b0=b0+xx*zz;
           b1=b1+yy*zz;
           b2=b2+zz;

           test=test->getsuiv2();

            }



             a[0][0]=a00;
             a[0][1]=a01;
             a[0][2]=a02;

             a[1][0]=a10;
             a[1][1]=a11;
             a[1][2]=a12;

             a[2][0]=a20;
             a[2][1]=a21;
             a[2][2]=a22;

             b[0]=b0;
             b[1]=b1;
             b[2]=b2;

             bool probleme;

            gauss_pivot_total(a,b,x,probleme);

             x1=Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt();
             y1=Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt();

             x2=Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt();
             y2=Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt();

             x3=Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt();
             y3=Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt();

             double z1=x[0]*x1+x[1]*y1+x[2];
             double z2=x[0]*x2+x[1]*y2+x[2];
             double z3=x[0]*x3+x[1]*y3+x[2];

			 Point_Clouds_Import->triangle_plan[i][j].seta_plan(x[0]);
			 Point_Clouds_Import->triangle_plan[i][j].setb_plan(x[1]);
			 Point_Clouds_Import->triangle_plan[i][j].setc_plan(x[2]);

//--------------------------------------------------------
		   double nx=x[0];
		   double ny=x[1];
		   double nz=-1;

		   if(nz<0){nx=-nx; ny=-ny; nz=-nz;}

		   double module=sqrt(nx*nx+ny*ny+nz*nz);

		   nx=nx/module;
		   ny=ny/module;
		   nz=nz/module;

		   Point_Clouds_Import->triangle_plan[i][j].setnx(nx);
		   Point_Clouds_Import->triangle_plan[i][j].setny(ny);
		   Point_Clouds_Import->triangle_plan[i][j].setnz(nz);

//--------------------------------------------------------

             if(z1>2*Point_Clouds_Import->nuage_pts_BEY->getzmax() || z1<2*Point_Clouds_Import->nuage_pts_BEY->getzmin()
             || z2>2*Point_Clouds_Import->nuage_pts_BEY->getzmax() || z2<2*Point_Clouds_Import->nuage_pts_BEY->getzmin()
             || z3>2*Point_Clouds_Import->nuage_pts_BEY->getzmax() || z3<2*Point_Clouds_Import->nuage_pts_BEY->getzmin())
             {
             int b=0;
             triangle_initial tr=Point_Clouds_Import->triangle_plan[i][j];
             b++;
             }

			 Point_Clouds_Import->triangle_plan[i][j].setz_pt1(z1);
			 Point_Clouds_Import->triangle_plan[i][j].setz_pt2(z2);
             Point_Clouds_Import->triangle_plan[i][j].setz_pt3(z3);





    } //for
  } //for


 double distance;
 double xpt,ypt,zpt;
 double a1,b1,c1,max_distance;
for (int i=0;i<nbre_segments_y;i++)
     {
     for (int j=0;j<nbre_segments_x*2;j++)
      {
      if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;

         a1=Point_Clouds_Import->triangle_plan[i][j].geta_plan();
         b1=Point_Clouds_Import->triangle_plan[i][j].getb_plan();
         c1=Point_Clouds_Import->triangle_plan[i][j].getc_plan();

         noeud_point_nuage_BEY *point_p;
		 point_p=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();

         xpt=point_p->getpoint()->getx();
         ypt=point_p->getpoint()->gety();
         zpt=point_p->getpoint()->getz();


         distance=fabs(a1*xpt+b1*ypt-zpt+c1)/sqrt(a1*a1+b1*b1+1);

        max_distance=distance;

        point_p=point_p->getsuiv2();

         while (point_p!=NULL)
         {

         xpt=point_p->getpoint()->getx();
         ypt=point_p->getpoint()->gety();
         zpt=point_p->getpoint()->getz();


         distance=fabs(a1*xpt+b1*ypt-zpt+c1)/sqrt(a1*a1+b1*b1+1);

       if(distance>max_distance){max_distance=distance;}


       point_p=point_p->getsuiv2();
      }//while
      Point_Clouds_Import->triangle_plan[i][j].setdist_pt_plan_max(max_distance);
     }//for
    }//for

	double max_distance1,min_distance1;

     max_distance1=-1;
     min_distance1=1e20;

    for (int i=0;i<nbre_segments_y;i++)
     {
     for (int j=0;j<nbre_segments_x*2;j++)
      {
       if (Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false)
       {

        if (Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max()>max_distance1)
             {max_distance1=Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max();}

        if (Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max()<min_distance1)
             {min_distance1=Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max();}
       }




   }//for
}//for
      dist_max=max_distance1;
      dist_min=min_distance1;

      //GroupBox5->Visible=true;
	  Edit34->Text=FormatFloat("0.0000000",dist_max);
	  Edit33->Text=FormatFloat("0.0000000",dist_min);

//	  Edit33->Refresh();
//	  Edit34->Refresh();

	  Screen->Cursor= crDefault;


//---------------Triangles filtrés----------------------------------------------
        CheckBox10->Enabled=false;
        CheckBox11->Enabled=false;

       for (int i=0;i<nbre_segments_y;i++)
         for (int j=0;j<nbre_segments_x*2;j++)
         {
           if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true){CheckBox10->Enabled=true;CheckBox11->Enabled=true;break;}
         }

         affectation_num_triangle();
//------------------------------------------------------------------------------


   Adaptive_Triangulation->choix_z_triangle();
   GroupBox6->Visible=true;


}//fonction

//------------------------------la fonction de subdivision----------------
void TAdaptive_Triangulation::subdivision_x(int div,int nb_x)
   {

   double *temp;
   double npx1;

   temp= new double[nb_x];

     npx1=vx_pas[div]/2;

     for (int j=0;j<div;j++)temp[j]=vx_pas[j];

     for (int j=div+2;j<nb_x;j++)temp[j]=vx_pas[j-1];

     temp[div]=npx1;
     temp[div+1]=npx1;

     delete  vx_pas;
     vx_pas= new double[nb_x];

     for (int j=0;j<nb_x;j++)
     {
     vx_pas[j]=temp[j];
     int a=1;
     a++;
     }
     delete temp;

   } //fonction

//----------------------------------------------
void TAdaptive_Triangulation::subdivision_y(int div,int nb_y)
   {

   double *temp;
   double npx1;

   temp= new double[nb_y];

     npx1=vy_pas[div]/2;

     for (int j=0;j<div;j++)temp[j]=vy_pas[j];

     for (int j=div+2;j<nb_y;j++)temp[j]=vy_pas[j-1];

     temp[div]=npx1;
     temp[div+1]=npx1;

     delete  vy_pas;
     vy_pas= new double[nb_y];

     for (int j=0;j<nb_y;j++)
     {
     vy_pas[j]=temp[j];
     int a=1;
     a++;
     }
	 delete temp;
   } //fonction




//------------------------------------------------

double TAdaptive_Triangulation::calcul_angle_deux_segments(double xa,double ya,double xb,double yb,double xp,double yp)
     {
      double modv,vz,v1x,v1y,v2x,v2y,modv1,modv2,psv;
      double alpha,sin_alpha,cos_alpha;

//__________________vecteur V1[pa]

      v1x=xa-xp;
      v1y=ya-yp;
      modv1=sqrt(v1x*v1x+v1y*v1y);

//_________________vecteur V2[pb]
      v2x=xb-xp;
      v2y=yb-yp;
      modv2=sqrt(v2x*v2x+v2y*v2y);

//__________________vecteur V dans le cas ou z=0

      vz=(v1x*v2y)-(v1y*v2x);                 //produit vectoriel de V1,V2
      modv=sqrt(vz*vz);
      psv=v1x*v2x+v1y*v2y;                     //produit scalaire  de V1,V2


//____________________calcul de sinus alpha et cosinus alpha

      sin_alpha=vz/(modv1*modv2);
      cos_alpha=psv/(modv1*modv2);

      if (vz/(modv1*modv2)>1 || vz/(modv1*modv2)<-1)

       {
       int a=0;
       a++;
       }

       if (fabs(sin_alpha-1)<=precision_calcul && fabs(cos_alpha)<=precision_calcul)

       {
	   alpha=pi/2;
       }
       else
       if (fabs(sin_alpha+1)<=precision_calcul && fabs(cos_alpha)<=precision_calcul)

       {
	   alpha=-pi/2;
       }


       else
       if (sin_alpha>0 && cos_alpha>0)

       {
       alpha=asin(sin_alpha);    // alpha=asin(modv/(modv1*modv2));
       }

       else
       if (sin_alpha>0 && cos_alpha<0)
       {
	   alpha=pi-asin(sin_alpha);    //  alpha=p-(asin(modv/(modv1*modv2)));

       }

       else
       if (sin_alpha<0 && cos_alpha>0)
       {
       alpha=asin(sin_alpha);      // alpha=asin(modv/(modv1*modv2));

       }

       else
        if (sin_alpha<0 && cos_alpha<0)
       {
	   alpha=-pi-asin(sin_alpha);  //  alpha=-p-asin(modv/(modv1*modv2));

       }


       return alpha;



   }//



//---------------------------------------------

liste_point &  liste_point::inserer_pts_triangle(noeud_point_nuage *t)


 {

  if(debut==NULL)
  {
   debut=t;
   debut->setsuiv2(NULL);
   debut->setprec2(NULL);
  }
  else
  {
    if(fin==NULL)                             // un seul element
    {
    fin=t;
    fin->setsuiv2(NULL);

    fin->setprec2(debut);
    debut->setsuiv2(t);

    }
    else
    {

     t->setprec2(fin);
     fin->setsuiv2(t);
     fin=t;
     fin->setsuiv2(NULL);

    }


  }
     nbre_pt++;
     return *this;
}

//----------------------------------------------

liste_point_BEY &  liste_point_BEY::inserer_pts_triangle(noeud_point_nuage_BEY *t)
 {

  if(debut==NULL)
  {
   debut=t;
   debut->setsuiv2(NULL);
//   debut->setprec2(NULL);
  }
  else
  {
	if(fin==NULL)                             // un seul element
	{
	fin=t;
	fin->setsuiv2(NULL);

//    fin->setprec2(debut);
	debut->setsuiv2(t);

	}
	else
	{

//	 t->setprec2(fin);
	 fin->setsuiv2(t);
	 fin=t;
	 fin->setsuiv2(NULL);

	}


  }
	 nbre_pt++;
	 return *this;
}
//----------------------------------------------------------------------------

//------------------------------------
void TAdaptive_Triangulation::gauss_pivot_total(double a[3][3],double b[3],double x[3], bool &probleme)
{

	 double p,l,max,temp;
	 int i,j,k,ligne,colonne,pivot[3],temps;
	 int n=3;


 for(i=0;i<n;i++) pivot[i]=i;
 for(k=0;k<n-1;k++)
 {


 max=0;
 for(i=k;i<n;i++) for (j=k;j<n;j++)
 if(fabs(a[i][j])>max)
 {
 max=fabs(a[i][j]);
 ligne=i;
 colonne=j;
 }


 for(j=k;j<n;j++)
 {
 temp=a[k][j];
 a[k][j]=a[ligne][j] ;
 a[ligne][j]=temp;
 }
 temp=b[k];
 b[k]=b[ligne];
 b[ligne]=temp;

 for(i=0;i<n;i++)
 {
 temp=a[i][k];
 a[i][k]=a[i][colonne] ;
 a[i][colonne]=temp;
 }


  temps=pivot[k];
 pivot[k]=pivot[colonne];
 pivot[colonne]=temps;
 if (a[k][k]==0)
// if (fabs(a[k][k])<=1e-20)
 {
 ShowMessage(" le pivot est nul on peut pas diviser!!!!");
  return;
 }

//__________________________réduction

 for(i=k+1;i<n;i++)
 {
 p=a[i][k]/a[k][k];
 for (j=k;j<n;j++) a[i][j]=a[i][j]-p*a[k][j];
 b[i]=b[i]-p*b[k];
 }
 }

//__________________________Résolution

 for(i=n-1;i>=0;i--)
 {
 l=0;
 for(j=i+1;j<n;j++)
 l=l+a[i][j]*b[j];

  if (fabs(a[i][i])==0)
  {
  /*double abc=a[i][i];
  int nn=10;
  nn++;*/
  probleme=true;
  return ;
     // ShowMessage(" le pivot est nul on peut pas diviser!!!!");
  }
 b[i]=(b[i]-l)/a[i][i];
 }
//__________________________pivotation des solutions


 for(i=0;i<n;i++)
{
 x[pivot[i]]=b[i];
int f=0;
f++;
}

}//fonction gauss

//******************************************************************************
//-------------------------fonction de gausse pivot totale pour résoudre un system lineaire-----------


void TAdaptive_Triangulation::gauss_pivot_total_4_4(double a[4][4],double b[4],double x[4], bool &probleme)
{

     double p,l,max,temp;
	 int i,j,k,ligne,colonne,pivot[4],temps;
     int n=4;

//__________________________vecteur de pivotation des solutions

 for(i=0;i<n;i++) pivot[i]=i;
 for(k=0;k<n-1;k++)
 {

//___________________________max pour le pivot total

 max=0;
 for(i=k;i<n;i++) for (j=k;j<n;j++)
 if(fabs(a[i][j])>max)
 {
 max=fabs(a[i][j]);
 ligne=i;
 colonne=j;
 }

//_______________________pivotations

 for(j=k;j<n;j++)
 {
 temp=a[k][j];
 a[k][j]=a[ligne][j] ;
 a[ligne][j]=temp;
 }
 temp=b[k];
 b[k]=b[ligne];
 b[ligne]=temp;

 for(i=0;i<n;i++)
 {
 temp=a[i][k];
 a[i][k]=a[i][colonne] ;
 a[i][colonne]=temp;
 }

//______________________calculer les elements du vecteur accordé aux pivotations

  temps=pivot[k];
 pivot[k]=pivot[colonne];
 pivot[colonne]=temps;
 if (a[k][k]==0)
// if (fabs(a[k][k])<=1e-20)
 {
 ShowMessage(" le pivot est nul on peut pas diviser!!!!");
  return;
 }

//__________________________réduction

 for(i=k+1;i<n;i++)
 {
 p=a[i][k]/a[k][k];
 for (j=k;j<n;j++) a[i][j]=a[i][j]-p*a[k][j];
 b[i]=b[i]-p*b[k];
 }
 }

//__________________________Résolution

 for(i=n-1;i>=0;i--)
 {
 l=0;
 for(j=i+1;j<n;j++)
 l=l+a[i][j]*b[j];

  if (fabs(a[i][i])==0)
  {
  double abc=a[i][i];
  int nn=10;
  nn++;
  probleme=true;
  return ;
     // ShowMessage(" le pivot est nul on peut pas diviser!!!!");
  }
 b[i]=(b[i]-l)/a[i][i];
 }
//__________________________pivotation des solutions


 for(i=0;i<n;i++)
{
 x[pivot[i]]=b[i];
int f=0;
f++;
}





}//fonction gauss





//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^les fonctions de dessin^^^^^^^^^^^^^^^^^^^^^^^^
 void TAdaptive_Triangulation::dessiner_toutes_listes_points()
   {
     int indice2=0;

	 glPointSize((float)Adaptive_Triangulation->ComboBox3->Text.ToDouble());

     for (int i=0;i<Adaptive_Triangulation->nbre_cellule_y;i++)
      {
      for (int j=0;j<Adaptive_Triangulation->nbre_cellule_x;j++)
       {
        if(indice2==0) glColor3d(1,0,0);
        if(indice2==1) glColor3d(0,1,0);
        if(indice2==2) glColor3d(0,0,1);
        if(indice2==3) glColor3d(1,1,0);
        if(indice2==4) glColor3d(1,0,1);
        if(indice2==5) glColor3d(1,1,1);
        if(indice2==6) glColor3d(0,0.5,0);
        if(indice2==7) glColor3d(1,0.5,0);

        indice2=indice2+1;
        if(indice2==8)indice2=0;



//     noeud_point_nuage_BEY *c;

	 //c=Point_Clouds_Import->cellule_points[i][j].getliste_pts_cellule_BEY()->getdebut();
	 double x1,y1,z1;
//	while (c)
	for(int ii=0; ii<Point_Clouds_Import->cellule_points_BEY[i][j].nbre_pts_cellule; ii++)
	{

	x1=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->x;
	y1=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->y;
	z1=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->z;


       glBegin(GL_POINTS);
       glVertex3d(x1,y1,z1);
       glEnd();


      //c=c->getsuiv1();
    }

 }

}
}

//------------------------------------------------------------------------------
 void TAdaptive_Triangulation::dessiner_toutes_listes_points_vector()
   {
     int indice2=0;

	 glPointSize((float)Adaptive_Triangulation->ComboBox3->Text.ToDouble());

     for (int i=0;i<Adaptive_Triangulation->nbre_cellule_y;i++)
      {
      for (int j=0;j<Adaptive_Triangulation->nbre_cellule_x;j++)
       {
        if(indice2==0) glColor3d(1,0,0);
        if(indice2==1) glColor3d(0,1,0);
        if(indice2==2) glColor3d(0,0,1);
        if(indice2==3) glColor3d(1,1,0);
        if(indice2==4) glColor3d(1,0,1);
        if(indice2==5) glColor3d(1,1,1);
        if(indice2==6) glColor3d(0,0.5,0);
        if(indice2==7) glColor3d(1,0.5,0);

        indice2=indice2+1;
        if(indice2==8)indice2=0;

	 int nbre_pts=Point_Clouds_Import->cellule_points_BEY[i][j].nbre_pts_cellule;
     double x1,y1,z1;

	for(int ii=0; ii<nbre_pts; ii++)
    {

	x1=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->getx();
	y1=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->gety();
	z1=Point_Clouds_Import->cellule_points_BEY[i][j].liste_pts_cellule_BEY_vector[ii]->getz();

	   glBegin(GL_POINTS);
	   glVertex3d(x1,y1,z1);
	   glEnd();
	}

 }

}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void TAdaptive_Triangulation::dessiner_toutes_listes_points_vector_int()
   {
     int indice2=0;

	 glPointSize((float)Adaptive_Triangulation->ComboBox3->Text.ToDouble());

     for (int i=0;i<Adaptive_Triangulation->nbre_cellule_y;i++)
      {
      for (int j=0;j<Adaptive_Triangulation->nbre_cellule_x;j++)
       {
        if(indice2==0) glColor3d(1,0,0);
        if(indice2==1) glColor3d(0,1,0);
        if(indice2==2) glColor3d(0,0,1);
        if(indice2==3) glColor3d(1,1,0);
        if(indice2==4) glColor3d(1,0,1);
        if(indice2==5) glColor3d(1,1,1);
        if(indice2==6) glColor3d(0,0.5,0);
        if(indice2==7) glColor3d(1,0.5,0);

        indice2=indice2+1;
        if(indice2==8)indice2=0;

	 int nbre_pts=Point_Clouds_Import->cellule_points_BEY[i][j].nbre_pts_cellule;
	 double x1,y1,z1;
	 //int indice_pt;

	for(int ii=0; ii<nbre_pts; ii++)
	{
	//indice_pt=Point_Clouds_Import->cellule_points[i][j].liste_pts_cellule_BEY_vector_int[ii];

	point_nuage pt=Point_Clouds_Import->NUAGE_PTS_BEY.retourner_pt(ii);

	x1=pt.getx();
	y1=pt.gety();
	z1=pt.getz();

	   glBegin(GL_POINTS);
	   glVertex3d(x1,y1,z1);
	   glEnd();
	}

 }

}
}

//------------------------------------------------------------------------------
 void cellule_BEY::dessiner_cellules()
 {

	 glLineWidth((float)Adaptive_Triangulation->ComboBox1->Text.ToDouble());

	   glColor3d(0,0,1);
	   glBegin(GL_LINE_LOOP);

	  glVertex3d(xmin_cellule, ymin_cellule, zmin_cellule);
		  glVertex3d(xmax_cellule, ymin_cellule, zmin_cellule);

		  glVertex3d(xmax_cellule, ymax_cellule, zmin_cellule);
		  glVertex3d(xmin_cellule, ymax_cellule, zmin_cellule);


	   glEnd();

	   glBegin(GL_LINE_LOOP);

	  glVertex3d(xmin_cellule, ymin_cellule, zmax_cellule);
		  glVertex3d(xmax_cellule, ymin_cellule, zmax_cellule);

		  glVertex3d(xmax_cellule, ymax_cellule, zmax_cellule);
		  glVertex3d(xmin_cellule, ymax_cellule, zmax_cellule);


	   glEnd();

	   glBegin(GL_LINES);

		glVertex3d(xmin_cellule, ymin_cellule, zmax_cellule);
			glVertex3d(xmin_cellule, ymin_cellule, zmin_cellule);

			glVertex3d(xmax_cellule, ymin_cellule, zmax_cellule);
			glVertex3d(xmax_cellule, ymin_cellule, zmin_cellule);


			glVertex3d(xmax_cellule, ymax_cellule, zmax_cellule);
			glVertex3d(xmax_cellule, ymax_cellule, zmin_cellule);

			glVertex3d(xmin_cellule, ymax_cellule, zmax_cellule);
			glVertex3d(xmin_cellule, ymax_cellule, zmin_cellule);

	   glEnd();
 }
 //-----------------------------------------------------------------------------

 void cellule::dessiner_cellules()
 {

	 glLineWidth((float)Adaptive_Triangulation->ComboBox1->Text.ToDouble());

	   glColor3d(0,0,1);
	   glBegin(GL_LINE_LOOP);

	  glVertex3d(xmin_cellule, ymin_cellule, zmin_cellule);
		  glVertex3d(xmax_cellule, ymin_cellule, zmin_cellule);

		  glVertex3d(xmax_cellule, ymax_cellule, zmin_cellule);
		  glVertex3d(xmin_cellule, ymax_cellule, zmin_cellule);


	   glEnd();

	   glBegin(GL_LINE_LOOP);

	  glVertex3d(xmin_cellule, ymin_cellule, zmax_cellule);
		  glVertex3d(xmax_cellule, ymin_cellule, zmax_cellule);

		  glVertex3d(xmax_cellule, ymax_cellule, zmax_cellule);
		  glVertex3d(xmin_cellule, ymax_cellule, zmax_cellule);


	   glEnd();

	   glBegin(GL_LINES);

		glVertex3d(xmin_cellule, ymin_cellule, zmax_cellule);
			glVertex3d(xmin_cellule, ymin_cellule, zmin_cellule);

			glVertex3d(xmax_cellule, ymin_cellule, zmax_cellule);
			glVertex3d(xmax_cellule, ymin_cellule, zmin_cellule);


			glVertex3d(xmax_cellule, ymax_cellule, zmax_cellule);
			glVertex3d(xmax_cellule, ymax_cellule, zmin_cellule);

			glVertex3d(xmin_cellule, ymax_cellule, zmax_cellule);
			glVertex3d(xmin_cellule, ymax_cellule, zmin_cellule);

	   glEnd();
 }
 //-----------------------------------------------------------------------------
void cellule_sommets_triangles::dessiner_cellules()
{
double  zmin_cellule, zmax_cellule;
zmin_cellule= zmax_cellule=0;

	 glLineWidth((float)Adaptive_Triangulation->ComboBox43->Text.ToDouble());

	   glColor3d(1,0.5,0.3);
	   glBegin(GL_LINE_LOOP);

		  glVertex3d(xmin_cellule, ymin_cellule, zmin_cellule);
		  glVertex3d(xmin_cellule+Adaptive_Triangulation->px_s, ymin_cellule, zmin_cellule);

		  glVertex3d(xmin_cellule+Adaptive_Triangulation->px_s, ymin_cellule+Adaptive_Triangulation->py_s, zmin_cellule);
		  glVertex3d(xmin_cellule, ymin_cellule+Adaptive_Triangulation->py_s, zmin_cellule);


	   glEnd();

	   glBegin(GL_LINE_LOOP);

		  glVertex3d(xmin_cellule, ymin_cellule, zmax_cellule);
		  glVertex3d(xmin_cellule+Adaptive_Triangulation->px_s, ymin_cellule, zmax_cellule);

		  glVertex3d(xmin_cellule+Adaptive_Triangulation->px_s, ymin_cellule+Adaptive_Triangulation->py_s, zmax_cellule);
		  glVertex3d(xmin_cellule, ymin_cellule+Adaptive_Triangulation->py_s, zmax_cellule);


	   glEnd();

	   glBegin(GL_LINES);

			glVertex3d(xmin_cellule, ymin_cellule, zmax_cellule);
			glVertex3d(xmin_cellule, ymin_cellule, zmin_cellule);

			glVertex3d(xmin_cellule+Adaptive_Triangulation->px_s, ymin_cellule, zmax_cellule);
			glVertex3d(xmin_cellule+Adaptive_Triangulation->px_s, ymin_cellule, zmin_cellule);


			glVertex3d(xmin_cellule+Adaptive_Triangulation->px_s, ymin_cellule+Adaptive_Triangulation->py_s, zmax_cellule);
			glVertex3d(xmin_cellule+Adaptive_Triangulation->px_s, ymin_cellule+Adaptive_Triangulation->py_s, zmin_cellule);

			glVertex3d(xmin_cellule, ymin_cellule+Adaptive_Triangulation->py_s, zmax_cellule);
			glVertex3d(xmin_cellule, ymin_cellule+Adaptive_Triangulation->py_s, zmin_cellule);

	   glEnd();
 }

 //-----------------------------------------------------------------------------
 void cellule_sommets_BEY::dessiner_cellules()
 {

	 //glLineWidth((double)Adaptive_Triangulation->ComboBox43->Text.ToDouble());

	   glColor3d(1,0,1);
	   glBegin(GL_LINE_LOOP);
		  glVertex3d(xmin_cellule, ymin_cellule, zmin_cellule);
		  glVertex3d(xmax_cellule, ymin_cellule, zmin_cellule);

		  glVertex3d(xmax_cellule, ymax_cellule, zmin_cellule);
		  glVertex3d(xmin_cellule, ymax_cellule, zmin_cellule);
	   glEnd();

	   glBegin(GL_LINE_LOOP);
		  glVertex3d(xmin_cellule, ymin_cellule, zmax_cellule);
		  glVertex3d(xmax_cellule, ymin_cellule, zmax_cellule);

		  glVertex3d(xmax_cellule, ymax_cellule, zmax_cellule);
		  glVertex3d(xmin_cellule, ymax_cellule, zmax_cellule);
	   glEnd();

	   glBegin(GL_LINES);
			glVertex3d(xmin_cellule, ymin_cellule, zmax_cellule);
			glVertex3d(xmin_cellule, ymin_cellule, zmin_cellule);

			glVertex3d(xmax_cellule, ymin_cellule, zmax_cellule);
			glVertex3d(xmax_cellule, ymin_cellule, zmin_cellule);


			glVertex3d(xmax_cellule, ymax_cellule, zmax_cellule);
			glVertex3d(xmax_cellule, ymax_cellule, zmin_cellule);

			glVertex3d(xmin_cellule, ymax_cellule, zmax_cellule);
			glVertex3d(xmin_cellule, ymax_cellule, zmin_cellule);
	   glEnd();
 }

//-------------------------
 void TAdaptive_Triangulation::dessiner_limite_triangle()
 {
   glColor3d(1,0.5,0.5 );
	 glLineWidth((float)Adaptive_Triangulation->ComboBox5->Text.ToDouble());

   for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {

      glBegin(GL_LINE_LOOP);


          glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getxmin_t(),Point_Clouds_Import->triangle_plan[i][j].getymin_t(),0);
   	  glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getxmax_t(),Point_Clouds_Import->triangle_plan[i][j].getymin_t(),0);

          glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getxmax_t(),Point_Clouds_Import->triangle_plan[i][j].getymax_t(),0);
          glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getxmin_t(),Point_Clouds_Import->triangle_plan[i][j].getymax_t(),0);





       glEnd();

      }
    }
 }


//-------------------------

void TAdaptive_Triangulation::dessiner_points_plan()
   {

	 glPointSize((float)Adaptive_Triangulation->ComboBox2->Text.ToDouble());
      glColor3d(1,1,0);
     for (int i=0;i<Adaptive_Triangulation->nbre_segments_y+1;i++)
      {
      for (int j=0;j<Adaptive_Triangulation->nbre_segments_x+1;j++)
       {



   double b,b1;

    b=Point_Clouds_Import->point_plan[i][j].getx_pt();
    b1=Point_Clouds_Import->point_plan[i][j].gety_pt();

      glBegin(GL_POINTS);
       glVertex3d(b,b1,0);
       glEnd();

    }
   }
}

//-------------------------

void TAdaptive_Triangulation::dessiner_points_triangle()
{
      int indice3=0;

	 glPointSize((float)Adaptive_Triangulation->ComboBox6->Text.ToDouble());

     for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {
        if(indice3==0) glColor3d(1,0,0);
        if(indice3==1) glColor3d(0,1,0);
        if(indice3==2) glColor3d(0,0,1);
        if(indice3==3) glColor3d(1,1,0);
        if(indice3==4) glColor3d(1,0,1);
        if(indice3==5) glColor3d(1,1,1);
        if(indice3==6) glColor3d(0,0.5,0);
        if(indice3==7) glColor3d(1,0.5,0);

        indice3=indice3+1;
        if(indice3==8)indice3=0;


     noeud_point_nuage_BEY *t;

       t=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();


     double x1,y1,z1;
     while (t)
    {

    x1=t->getpoint()->getx();
    y1=t->getpoint()->gety();
    z1=t->getpoint()->getz();



       glBegin(GL_POINTS);
       glVertex3d(x1,y1,z1);
       glEnd();


      t=t->getsuiv2();
    }

 }

}

}
//-------------------------

void TAdaptive_Triangulation::dessiner_points_triangle_BEY()
{
glPointSize((float)Adaptive_Triangulation->ComboBox21->Text.ToDouble());

int indice3=0;

triangle_initial_BEY *parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while (parcT!=NULL)
{
parcT->dessiner_pts_triangle();
parcT=parcT->getsuiv();
}

}
//------------------------------------------------------------------------------

//-------------------------

void TAdaptive_Triangulation::determiner_pts_proches_sommets_triangle()
   {

     for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {

     noeud_point_nuage_BEY *t;

     if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;


      double xx1=Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt();
      double yy1=Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt();
      double zz1=Point_Clouds_Import->triangle_plan[i][j].getz_pt1();


      double xx2=Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt();
      double yy2=Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt();
      double zz2=Point_Clouds_Import->triangle_plan[i][j].getz_pt2();

      double xx3=Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt();
      double yy3=Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt();
      double zz3=Point_Clouds_Import->triangle_plan[i][j].getz_pt3();

      int nbre_proche_p1,nbre_proche_p2,nbre_proche_p3;

      nbre_proche_p1=nbre_proche_p2=nbre_proche_p3=0;

//     double x1,y1,z1;

    t=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();

    double xg=0;
    double yg=0;
    int nbre_pts_triangle=0;

     while (t)
    {
    nbre_pts_triangle++;
    
    double x=t->getpoint()->getx();
    double y=t->getpoint()->gety();
//    double z=t->getpoint()->getz();

    xg=xg+x;
    yg=yg+y;

    double dist1=sqrt(pow(xx1-x,2)+ pow(yy1-y,2));//+ pow(zz1-z,2));
    double dist2=sqrt(pow(xx2-x,2)+ pow(yy2-y,2));//+ pow(zz2-z,2));
    double dist3=sqrt(pow(xx3-x,2)+ pow(yy3-y,2));//+ pow(zz3-z,2));

    double dist_min=min(dist1,min(dist2,dist3));

    if(dist1==dist_min){t->setindice_pt_proche(1);nbre_proche_p1++;t=t->getsuiv2();continue;}
    if(dist2==dist_min){t->setindice_pt_proche(2);nbre_proche_p2++;t=t->getsuiv2();continue;}
    if(dist3==dist_min){t->setindice_pt_proche(3);nbre_proche_p3++;t=t->getsuiv2();continue;}

    //t=t->getsuiv2();
    }

   Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setnbre_pt(nbre_pts_triangle);

   /*Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setnbre_pts_proche_p1(nbre_proche_p1);
   Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setnbre_pts_proche_p2(nbre_proche_p2);
   Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setnbre_pts_proche_p3(nbre_proche_p3);*/

   Point_Clouds_Import->triangle_plan[i][j].setnbre_pts_proche_p1(nbre_proche_p1);
   Point_Clouds_Import->triangle_plan[i][j].setnbre_pts_proche_p2(nbre_proche_p2);
   Point_Clouds_Import->triangle_plan[i][j].setnbre_pts_proche_p3(nbre_proche_p3);

//   Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setxg(xg/Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getnbre_pt());
//   Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setyg(yg/Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getnbre_pt());
   Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setxg(xg/Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle());
   Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setyg(yg/Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle());

   Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setzg(0);
 }

}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_centre_cercle_circonscrit()
   {

	 glPointSize((float)Adaptive_Triangulation->ComboBox14->Text.ToDouble());

     for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {

      if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;


       glBegin(GL_POINTS);
       glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getxc(),Point_Clouds_Import->triangle_plan[i][j].getyc(),Point_Clouds_Import->triangle_plan[i][j].getzc());
       glEnd();
 }

}
}
//-------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_centre_gravite_triangle()
   {
     glColor3d(0.5,1,0.8);
     glPointSize((float)Adaptive_Triangulation->ComboBox16->Text.ToDouble());

     for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {

      if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;


       glBegin(GL_POINTS);
       glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getxg(),Point_Clouds_Import->triangle_plan[i][j].getyg(),Point_Clouds_Import->triangle_plan[i][j].getzg());
       glEnd();
 }

}
}
//-------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_centre_gravite_pts_triangle()
   {
	 glColor3d(0.1,0.8,1);
	 glPointSize((float)Adaptive_Triangulation->ComboBox17->Text.ToDouble());

     for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {

      if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;


       glBegin(GL_POINTS);
       glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getxg(),Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getyg(),Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getzg());
       glEnd();
 }

}
}
//-------------------------------------------------------------------------

//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_centre_cercle_circonscrit_sommets_triangle()
   {

	 glLineWidth((float)Adaptive_Triangulation->ComboBox15->Text.ToDouble());

     for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {

      if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;


       glBegin(GL_LINES);
       glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getxc(),Point_Clouds_Import->triangle_plan[i][j].getyc(),Point_Clouds_Import->triangle_plan[i][j].getzc());
       glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt(),Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt(),0);

       glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getxc(),Point_Clouds_Import->triangle_plan[i][j].getyc(),Point_Clouds_Import->triangle_plan[i][j].getzc());
       glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt(),Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt(),0);

       glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getxc(),Point_Clouds_Import->triangle_plan[i][j].getyc(),Point_Clouds_Import->triangle_plan[i][j].getzc());
       glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt(),Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt(),0);

       glEnd();
 }

}
}
//-------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_pts_proches_sommets_triangle()
   {

	 glPointSize((float)Adaptive_Triangulation->ComboBox13->Text.ToDouble());

     for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {

     noeud_point_nuage_BEY *t;

     if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;

       t=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();


     double x1,y1,z1;
     while (t)
    {
    if(t->getindice_pt_proche()==0){t=t->getsuiv2();continue;}

    x1=t->getpoint()->getx();
    y1=t->getpoint()->gety();
    z1=t->getpoint()->getz();

       if(t->getindice_pt_proche()==1)glColor3d(1,0,0);
       if(t->getindice_pt_proche()==2)glColor3d(0,1,0);
       if(t->getindice_pt_proche()==3)glColor3d(0,1,1);

       glBegin(GL_POINTS);
       glVertex3d(x1,y1,z1);
       glEnd();


      t=t->getsuiv2();
    }

 }

}
}
//-------------------------------------------------------------------------
void TAdaptive_Triangulation::calculer_centre_cercle_circonscrit(double x1,double y1,double x2,double y2,double x3,double y3,double &xc,double &yc,double &Rc)
{
double a=-(x2-x1)/(y2-y1);

double b=(x2*x2-x1*x1+y2*y2-y1*y1)/(2*(y2-y1));

double aprime=-(x3-x2)/(y3-y2);

double bprime=(x3*x3-x2*x2+y3*y3-y2*y2)/(2*(y3-y2));

xc=(b-bprime)/(aprime-a);
yc=a*xc+b;

Rc=sqrt(pow(x1-xc,2)+pow(y1-yc,2));



}
//-------------------------------------------------------------------------
//--------------------------------------------------------------------------
void TAdaptive_Triangulation::filtrer_triangles_distances_sommets_triangle()
   {

     for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {

	 noeud_point_nuage_BEY *t;

     if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;


      double xx1=Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt();
      double yy1=Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt();
      double zz1=Point_Clouds_Import->triangle_plan[i][j].getz_pt1();


      double xx2=Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt();
      double yy2=Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt();
      double zz2=Point_Clouds_Import->triangle_plan[i][j].getz_pt2();

      double xx3=Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt();
      double yy3=Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt();
      double zz3=Point_Clouds_Import->triangle_plan[i][j].getz_pt3();

    Point_Clouds_Import->triangle_plan[i][j].setxg((xx1+xx2+xx3)/3);
    Point_Clouds_Import->triangle_plan[i][j].setyg((yy1+yy2+yy3)/3);
    Point_Clouds_Import->triangle_plan[i][j].setzg(0);


    double dist12=sqrt(pow(xx2-xx1,2)+ pow(yy2-yy1,2));//+ pow(zz2-zz1,2));
    double dist13=sqrt(pow(xx3-xx1,2)+ pow(yy3-yy1,2));//+ pow(zz3-zz1,2));
    double dist23=sqrt(pow(xx3-xx2,2)+ pow(yy3-yy2,2));//+ pow(zz3-zz2,2));

    double s=0.5*(dist12+dist13+dist23);//demi périmètre

    double rayon_circonscrit=(dist12*dist13*dist23)/(4*sqrt(s*(s-dist12)*(s-dist13)*(s-dist23)));

    double xc, yc, Rc, preci;
    preci=1e-10;

    if(fabs(yy1-yy2)>preci && fabs(yy3-yy2)>preci) calculer_centre_cercle_circonscrit(xx1, yy1, xx2, yy2, xx3, yy3, xc, yc, Rc);

    else if(fabs(yy2-yy3)>preci && fabs(yy1-yy3)>preci) calculer_centre_cercle_circonscrit(xx2, yy2, xx3, yy3, xx1, yy1, xc, yc, Rc);

    else if(fabs(yy2-yy1)>preci && fabs(yy3-yy1)>preci) calculer_centre_cercle_circonscrit(xx3, yy3, xx1, yy1, xx2, yy2, xc, yc, Rc);

    Point_Clouds_Import->triangle_plan[i][j].setxc(xc);
    Point_Clouds_Import->triangle_plan[i][j].setyc(yc);
    Point_Clouds_Import->triangle_plan[i][j].setzc(0);
    Point_Clouds_Import->triangle_plan[i][j].setRc(Rc);

    double dist_seg_min=min(dist12,min(dist13,dist23));

    double poucentage=Edit7->Text.ToDouble();

//    double distance_minimale=dist_seg_min*poucentage*0.01;
    double distance_minimale=rayon_circonscrit*poucentage*0.01;

    int nbre_proche_p1,nbre_proche_p2,nbre_proche_p3;

    nbre_proche_p1=nbre_proche_p2=nbre_proche_p3=0;

//     double x1,y1,z1;

    t=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();

     while (t)
    {
//    t->setindice_pt_proche(0);

    double x=t->getpoint()->getx();
    double y=t->getpoint()->gety();
    double z=t->getpoint()->getz();

    double dist1=sqrt(pow(xx1-x,2)+ pow(yy1-y,2));//+ pow(zz1-z,2));
    double dist2=sqrt(pow(xx2-x,2)+ pow(yy2-y,2));//+ pow(zz2-z,2));
    double dist3=sqrt(pow(xx3-x,2)+ pow(yy3-y,2));//+ pow(zz3-z,2));

    //double dist_min=min(dist1,min(dist2,dist3));

    if     (t->getindice_pt_proche()==1 && dist1<=distance_minimale){t->setindice_pt_proche(1);nbre_proche_p1++;t=t->getsuiv2();continue;}
    else if(t->getindice_pt_proche()==2 && dist2<=distance_minimale){t->setindice_pt_proche(2);nbre_proche_p2++;t=t->getsuiv2();continue;}
    else if(t->getindice_pt_proche()==3 && dist3<=distance_minimale){t->setindice_pt_proche(3);nbre_proche_p3++;t=t->getsuiv2();continue;}
    else   {t->setindice_pt_proche(0);t=t->getsuiv2();continue;}

    t=t->getsuiv2();
    }

/*   Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setnbre_pts_proche_p1(nbre_proche_p1);
   Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setnbre_pts_proche_p2(nbre_proche_p2);
   Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setnbre_pts_proche_p3(nbre_proche_p3);*/

   Point_Clouds_Import->triangle_plan[i][j].setnbre_pts_proche_p1(nbre_proche_p1);
   Point_Clouds_Import->triangle_plan[i][j].setnbre_pts_proche_p2(nbre_proche_p2);
   Point_Clouds_Import->triangle_plan[i][j].setnbre_pts_proche_p3(nbre_proche_p3);

/*   if(Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getnbre_pts_proche_p1()==0
   || Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getnbre_pts_proche_p2()==0
   || Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getnbre_pts_proche_p3()==0) Adaptive_Triangulation->repartition_pt_correcte_triangle=false;*/
   if(Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_proche_p1()==0
   || Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_proche_p2()==0
   || Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_proche_p3()==0) Adaptive_Triangulation->repartition_pt_correcte_triangle=false;

 }

}
}


//------------------------------------------------------------------------------


//--------------------------------------------------------------------------
void TAdaptive_Triangulation::calculer_nbre_pts_triangles()
   {

     for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {

     if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;

	noeud_point_nuage_BEY *t;

	t=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();

	int nbre_pts_triangle=0;
     while (t)
    {
    nbre_pts_triangle++;
    t=t->getsuiv2();
    }

   Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->setnbre_pt(nbre_pts_triangle);
//   double diff=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getnbre_pt()-Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle();
   double diff=Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle()-Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle();

   if(diff!=0)
   {
   int bey=10;
   bey++;
//   ShowMessage("DIFFERENCE...............!!!!!!");
   }
  }

  }
}


//------------------------------------------------------------------------------




//------------------------------------------------------------------------------

void TAdaptive_Triangulation::dessiner_points_triangle_nf()
   {


      int indice3=0;

	 glPointSize((float)Adaptive_Triangulation->ComboBox9->Text.ToDouble());

     for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {
        if(indice3==0) glColor3d(1,0,0);
        if(indice3==1) glColor3d(0,1,0);
        if(indice3==2) glColor3d(0,0,1);
        if(indice3==3) glColor3d(1,1,0);
        if(indice3==4) glColor3d(1,0,1);
        if(indice3==5) glColor3d(1,1,1);
        if(indice3==6) glColor3d(0,0.5,0);
        if(indice3==7) glColor3d(1,0.5,0);

        indice3=indice3+1;
        if(indice3==8)indice3=0;


     noeud_point_nuage_BEY *t;

     if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;

	   t=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();


     double x1,y1,z1;
     while (t)
    {

    x1=t->getpoint()->getx();
    y1=t->getpoint()->gety();
    z1=t->getpoint()->getz();



       glBegin(GL_POINTS);
       glVertex3d(x1,y1,z1);
       glEnd();


      t=t->getsuiv2();
    }

 }

}


}
//------------------------------------------------------------------------------

void TAdaptive_Triangulation::dessiner_points_triangle_nf_BEY()
   {

glPointSize((float)Adaptive_Triangulation->ComboBox22->Text.ToDouble());

int indice3=0;

triangle_initial_BEY *parc=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while (parc!=NULL)
{
//	if(parc->getfiltre()==true || parc->supprime==true){parc=parc->getsuiv();continue;}
	if(parc->filtre==true){parc=parc->getsuiv();continue;} //Triangle filtré
	if(parc->filtre==false && parc->supprime==true){parc=parc->getsuiv();continue;}//Triangle supprimé

	parc->dessiner_pts_triangle();
parc=parc->getsuiv();

}

}
//------------------------------------------------------------------------------

void TAdaptive_Triangulation::dessiner_points_triangle_filtres_BEY()
   {

glPointSize((float)Adaptive_Triangulation->ComboBox24->Text.ToDouble());

int indice3=0;

triangle_initial_BEY *parc=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while (parc!=NULL)
{
//	if(parc->getfiltre()==true || parc->supprime==true){parc=parc->getsuiv();continue;}
	if(parc->filtre==false){parc=parc->getsuiv();continue;} //Triangle filtré
//	if(parc->filtre==false && parc->supprime==true){parc=parc->getsuiv();continue;}//Triangle supprimé

	parc->dessiner_pts_triangle();
parc=parc->getsuiv();

}

}


//-------------------------

void TAdaptive_Triangulation::dessiner_points_triangle_f()
   {

glPointSize((float)Adaptive_Triangulation->ComboBox10->Text.ToDouble());

int indice3=0;

noeud_point_nuage_BEY *t;

triangle_initial *parcT=Point_Clouds_Import->liste_triangle_adaptation->gettete();

while (parcT!=NULL)
{
	if(parcT->getfiltre()==false){parcT=parcT->getsuiv();continue;}

        if(indice3==0) glColor3d(1,0,0);
        if(indice3==1) glColor3d(0,1,0);
        if(indice3==2) glColor3d(0,0,1);
        if(indice3==3) glColor3d(1,1,0);
        if(indice3==4) glColor3d(1,0,1);
        if(indice3==5) glColor3d(1,1,1);
        if(indice3==6) glColor3d(0,0.5,0);
        if(indice3==7) glColor3d(1,0.5,0);

        indice3=indice3+1;
        if(indice3==8)indice3=0;


t=parcT->getliste_pts_triangle()->getdebut();
while (t!=NULL)
{

    double x1,y1,z1;

    x1=t->getpoint()->getx();
    y1=t->getpoint()->gety();
    z1=t->getpoint()->getz();

       glBegin(GL_POINTS);
       glVertex3d(x1,y1,z1);
       glEnd();


      t=t->getsuiv2();
}


parcT=parcT->getsuiv();

}



}
//-------------------------------------------------------------------------------

void TAdaptive_Triangulation::dessiner_points_triangle_f_BEY()
{

glPointSize((float)Adaptive_Triangulation->ComboBox24->Text.ToDouble());

//int indice3=0;

//triangle_initial_BEY *parcT=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();
triangle_initial_BEY *parcT=Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->gettete(); //Triangles filtrés

while (parcT!=NULL)
{
if(parcT->getfiltre()==false){parcT=parcT->getsuiv();continue;}
   parcT->dessiner_pts_triangle();

parcT=parcT->getsuiv();
}

}

//-------------------------

void TAdaptive_Triangulation::dessiner_triangle()
  {
     glColor3d(1, 1,0 );
	 glLineWidth((float)Adaptive_Triangulation->ComboBox4->Text.ToDouble());

       for (int i=0;i<nbre_segments_y;i++)
         { for (int j=0;j<nbre_segments_x*2;j++)
         {

         glBegin(GL_LINE_LOOP);

            glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt(),Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt(),0);
	    glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt(),Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt(),0);
	    glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt(),Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt(),0);
           glEnd();


          }
         }

   }
//-------------------------

void TAdaptive_Triangulation::dessiner_triangle_BEY()
{
     glColor3d(1, 1,0 );
	 glLineWidth((float)Adaptive_Triangulation->ComboBox23->Text.ToDouble());

triangle_initial_BEY *parc=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

	while(parc!=NULL)
	{

			 glBegin(GL_LINE_LOOP);

				glVertex3d(parc->gets1()->getx_pt(),parc->gets1()->gety_pt(),parc->gets1()->getz());
				glVertex3d(parc->gets2()->getx_pt(),parc->gets2()->gety_pt(),parc->gets2()->getz());
				glVertex3d(parc->gets3()->getx_pt(),parc->gets3()->gety_pt(),parc->gets3()->getz());
			   glEnd();

	parc=parc->getsuiv();
	}

}

//-------------------------

void TAdaptive_Triangulation::dessiner_triangle_3D()
  {

if(Adaptive_Triangulation->RadioButton2->Checked)
{
Rendering->reglage_eclairage();
glEnable(GL_DEPTH_TEST);
}


//	 glColor3d(0, 1, 0);
	 glColor3d(red_surface, green_surface, blue_surface);

	 if(Adaptive_Triangulation->Visible)glLineWidth((float)Adaptive_Triangulation->ComboBox8->Text.ToDouble());


       for (int i=0;i<nbre_segments_y;i++)
		 { for (int j=0;j<nbre_segments_x*2;j++)
         {
           if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;


         if(Adaptive_Triangulation->Visible)
         {
         if(Adaptive_Triangulation->RadioButton1->Checked)glBegin(GL_LINE_LOOP);
         if(Adaptive_Triangulation->RadioButton2->Checked)glBegin(GL_POLYGON);
         }

//          glNormal3d(Point_Clouds_Import->triangle_plan[i][j].getp1()->getnx_pt(),Point_Clouds_Import->triangle_plan[i][j].getp1()->getny_pt(),Point_Clouds_Import->triangle_plan[i][j].getp1()->getnz_pt());
			glNormal3d(Point_Clouds_Import->triangle_plan[i][j].getnx(), Point_Clouds_Import->triangle_plan[i][j].getny(), Point_Clouds_Import->triangle_plan[i][j].getnz()); // ajouter
			glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt(),Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt(),Point_Clouds_Import->triangle_plan[i][j].getz_pt1());

//          glNormal3d(Point_Clouds_Import->triangle_plan[i][j].getp2()->getnx_pt(),Point_Clouds_Import->triangle_plan[i][j].getp2()->getny_pt(),Point_Clouds_Import->triangle_plan[i][j].getp2()->getnz_pt());
			glNormal3d(Point_Clouds_Import->triangle_plan[i][j].getnx(), Point_Clouds_Import->triangle_plan[i][j].getny(), Point_Clouds_Import->triangle_plan[i][j].getnz()); // ajouter
		glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt(),Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt(),Point_Clouds_Import->triangle_plan[i][j].getz_pt2());

//          glNormal3d(Point_Clouds_Import->triangle_plan[i][j].getp3()->getnx_pt(),Point_Clouds_Import->triangle_plan[i][j].getp3()->getny_pt(),Point_Clouds_Import->triangle_plan[i][j].getp3()->getnz_pt());
            glNormal3d(Point_Clouds_Import->triangle_plan[i][j].getnx(), Point_Clouds_Import->triangle_plan[i][j].getny(), Point_Clouds_Import->triangle_plan[i][j].getnz()); // ajouter
	    glVertex3d(Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt(),Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt(),Point_Clouds_Import->triangle_plan[i][j].getz_pt3());
           glEnd();





     }


 }


if(Adaptive_Triangulation->RadioButton2->Checked)
{
glDisable(GL_DEPTH_TEST);
glDisable(GL_LIGHTING);
}

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_triangle_3D_BEY()
{

	if(Adaptive_Triangulation->RadioButton2->Checked || Adaptive_Triangulation->RadioButton7->Checked)
	{
	Rendering->reglage_eclairage();
	glEnable(GL_DEPTH_TEST);
	}


//	 glColor3d(0, 1, 0);
	 glColor3d(red_surface, green_surface, blue_surface);

	 glLineWidth((float)Adaptive_Triangulation->ComboBox26->Text.ToDouble());

triangle_initial_BEY *parc=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

	while(parc!=NULL)
	{
		 //if(parc->getfiltre()==true || parc->supprime==true){parc=parc->getsuiv(); continue;}
	if(parc->filtre==true){parc=parc->getsuiv();continue;} //Triangle filtré
	if(parc->filtre==false && parc->supprime==true){parc=parc->getsuiv();continue;}//Triangle supprimé


		 if(Adaptive_Triangulation->RadioButton6->Checked)glBegin(GL_LINE_LOOP);
		 if(Adaptive_Triangulation->RadioButton7->Checked)glBegin(GL_POLYGON);

//			glNormal3d(parc->gets1()->getnx_pt(),parc->gets1()->getny_pt(),parc->gets1()->getnz_pt());
			glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
			glVertex3d(parc->gets1()->getx_pt(),parc->gets1()->gety_pt(),parc->getz_pt1());

//			glNormal3d(parc->gets2()->getnx_pt(),parc->gets2()->getny_pt(),parc->gets2()->getnz_pt());
			glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
			glVertex3d(parc->gets2()->getx_pt(),parc->gets2()->gety_pt(),parc->getz_pt2());

//			glNormal3d(parc->gets3()->getnx_pt(),parc->gets3()->getny_pt(),parc->gets3()->getnz_pt());
			glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
			glVertex3d(parc->gets3()->getx_pt(),parc->gets3()->gety_pt(),parc->getz_pt3());
		   glEnd();


	parc=parc->getsuiv();
	}



	if(Adaptive_Triangulation->RadioButton2->Checked || Adaptive_Triangulation->RadioButton6->Checked)
	{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	}

}
//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_triangle_3D_Filtres_BEY()
{

	if(Adaptive_Triangulation->RadioButton2->Checked || Adaptive_Triangulation->RadioButton7->Checked)
	{
	Rendering->reglage_eclairage();
	glEnable(GL_DEPTH_TEST);
	}


//	 glColor3d(0, 1, 0);
	 glColor3d(1, 0, 0);

	 glLineWidth((float)Adaptive_Triangulation->ComboBox25->Text.ToDouble());

triangle_initial_BEY *parc=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

	while(parc!=NULL)
	{
		 //if(parc->getfiltre()==true || parc->supprime==true){parc=parc->getsuiv(); continue;}
	if(parc->filtre==false){parc=parc->getsuiv();continue;} //Triangle filtré
//	if(parc->filtre==false && parc->supprime==true){parc=parc->getsuiv();continue;}//Triangle supprimé


		 if(Adaptive_Triangulation->RadioButton6->Checked)glBegin(GL_LINE_LOOP);
		 if(Adaptive_Triangulation->RadioButton7->Checked)glBegin(GL_POLYGON);

//			glNormal3d(parc->gets1()->getnx_pt(),parc->gets1()->getny_pt(),parc->gets1()->getnz_pt());
			glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
			glVertex3d(parc->gets1()->getx_pt(),parc->gets1()->gety_pt(),parc->getz_pt1());

//			glNormal3d(parc->gets2()->getnx_pt(),parc->gets2()->getny_pt(),parc->gets2()->getnz_pt());
			glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
			glVertex3d(parc->gets2()->getx_pt(),parc->gets2()->gety_pt(),parc->getz_pt2());

//			glNormal3d(parc->gets3()->getnx_pt(),parc->gets3()->getny_pt(),parc->gets3()->getnz_pt());
			glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
			glVertex3d(parc->gets3()->getx_pt(),parc->gets3()->gety_pt(),parc->getz_pt3());
		   glEnd();


	parc=parc->getsuiv();
	}



	if(Adaptive_Triangulation->RadioButton2->Checked || Adaptive_Triangulation->RadioButton6->Checked)
	{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	}

}
//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_triangle_3D_Elimination_BEY()
{

 /*if (Edit22->Text=="" && Edit24->Text=="" && Edit26->Text=="" && Edit28->Text=="")
  {
  return;
  }*/

	 double epais_ligne=Adaptive_Triangulation->ComboBox41->Text.ToDouble();

	 double epais_point=Adaptive_Triangulation->ComboBox42->Text.ToDouble();

triangle_initial_BEY *parc=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

	while(parc!=NULL)
	{
		if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}

		//----au moins un triangle voisin filtré  : ne pas filtrer un triangle avec trois voisins
		if(parc->getv1()!=NULL && parc->getv2()!=NULL && parc->getv3()!=NULL){parc=parc->getsuiv(); continue;}

		//----au moins un triangle voisin filtré  : ne pas filtrer un triangle avec trois voisins
		//if((parc->getv1()!=NULL && parc->getv1()->getfiltre()==true) || (parc->getv2()!=NULL && parc->getv2()->getfiltre()==true)
		//|| (parc->getv3()!=NULL && parc->getv3()->getfiltre()==true))

		//----Triangles frontières-----------
		//Un voisin non NULL et deux voisins NULL
		/*if((parc->getv1()!=NULL && parc->getv2()==NULL && parc->getv3()==NULL)
		 ||(parc->getv2()!=NULL && parc->getv1()==NULL && parc->getv3()==NULL)
		 ||(parc->getv3()!=NULL && parc->getv1()==NULL && parc->getv2()==NULL)
		 ||(parc->getv1()==NULL && parc->getv2()==NULL && parc->getv3()==NULL))
		 */
		 //Un voisin non NULL et au moins un voisin NULL ou bien les trois voisins sont nuls
		if((parc->getv1()!=NULL && (parc->getv2()==NULL || parc->getv3()==NULL))
		 ||(parc->getv2()!=NULL && (parc->getv1()==NULL || parc->getv3()==NULL))
		 ||(parc->getv3()!=NULL && (parc->getv1()==NULL || parc->getv2()==NULL))
		 ||(parc->getv1()==NULL && parc->getv2()==NULL && parc->getv3()==NULL))
		  {

			if(Edit22->Text!="")
			{
				seuil_aire_triangle=Adaptive_Triangulation->Edit22->Text.ToDouble();
				if(Adaptive_Triangulation->CheckBox48->Checked && parc->aire_triangle_2D<=seuil_aire_triangle)
				{
				glPointSize((float)epais_point);
				parc->dessiner_pts_triangle();

					glLineWidth((float)epais_ligne);
					glBegin(GL_LINE_LOOP);
					glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
					glVertex3d(parc->gets1()->getx_pt(),parc->gets1()->gety_pt(),parc->getz_pt1());

					glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
					glVertex3d(parc->gets2()->getx_pt(),parc->gets2()->gety_pt(),parc->getz_pt2());

					glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
					glVertex3d(parc->gets3()->getx_pt(),parc->gets3()->gety_pt(),parc->getz_pt3());
					glEnd();
				}
			}

			double rapport, hauteur_triangle;

			if(Edit31->Text!="") hauteur_triangle=Adaptive_Triangulation->Edit31->Text.ToDouble();
			else hauteur_triangle=1;

			if(parc->delta_Z_pts_triangle!=0 && parc->delta_Z_triangle>hauteur_triangle)
				rapport=parc->delta_Z_triangle/parc->delta_Z_pts_triangle;
			else
				rapport=parc->delta_Z_triangle;

				if(Edit24->Text!="")
				{
					rapport_limites_triangle_limites_points=Adaptive_Triangulation->Edit24->Text.ToDouble();
					if(Adaptive_Triangulation->CheckBox49->Checked && rapport>=rapport_limites_triangle_limites_points)
					{
					glPointSize((float)epais_point);
					parc->dessiner_pts_triangle();

						glLineWidth((float)epais_ligne);
						glBegin(GL_LINE_LOOP);
						glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
						glVertex3d(parc->gets1()->getx_pt(),parc->gets1()->gety_pt(),parc->getz_pt1());

						glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
						glVertex3d(parc->gets2()->getx_pt(),parc->gets2()->gety_pt(),parc->getz_pt2());

						glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
						glVertex3d(parc->gets3()->getx_pt(),parc->gets3()->gety_pt(),parc->getz_pt3());
						glEnd();
					}
				}


			if(Edit26->Text!="")
			{
				nbre_min_points_triangle=Adaptive_Triangulation->Edit26->Text.ToDouble();
				if(Adaptive_Triangulation->CheckBox50->Checked && parc->getnbre_pts_triangle()<=nbre_min_points_triangle)
				{
				glPointSize((float)epais_point);
				parc->dessiner_pts_triangle();

					glLineWidth((float)epais_ligne);
					glBegin(GL_LINE_LOOP);
					glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
					glVertex3d(parc->gets1()->getx_pt(),parc->gets1()->gety_pt(),parc->getz_pt1());

					glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
					glVertex3d(parc->gets2()->getx_pt(),parc->gets2()->gety_pt(),parc->getz_pt2());

					glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
					glVertex3d(parc->gets3()->getx_pt(),parc->gets3()->gety_pt(),parc->getz_pt3());
					glEnd();
				}
			}

			if(Edit28->Text!="")
			{
				ecart_max_droite=Adaptive_Triangulation->Edit28->Text.ToDouble();
				if(Adaptive_Triangulation->CheckBox52->Checked && parc->ecart_max_droite<=ecart_max_droite)
				{
				glPointSize((float)epais_point);
				parc->dessiner_pts_triangle();

					glLineWidth((float)epais_ligne);
					glBegin(GL_LINE_LOOP);
					glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
					glVertex3d(parc->gets1()->getx_pt(),parc->gets1()->gety_pt(),parc->getz_pt1());

					glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
					glVertex3d(parc->gets2()->getx_pt(),parc->gets2()->gety_pt(),parc->getz_pt2());

					glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
					glVertex3d(parc->gets3()->getx_pt(),parc->gets3()->gety_pt(),parc->getz_pt3());
					glEnd();
				}
			}
		  }

	parc=parc->getsuiv();
	}
}

//------------------------------------------------------------------------------
void TAdaptive_Triangulation::dessiner_triangle_3D_sommets_nuls_BEY()
  {

if(Adaptive_Triangulation->RadioButton2->Checked || Adaptive_Triangulation->RadioButton7->Checked)
{
Rendering->reglage_eclairage();
glEnable(GL_DEPTH_TEST);
}


	 glColor3d(1, 1, 0);
	 glLineWidth((float)Adaptive_Triangulation->ComboBox39->Text.ToDouble());


triangle_initial_BEY *parc=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();

while(parc!=NULL)
{
		 if(parc->getfiltre()==true){parc=parc->getsuiv(); continue;}

		 if(parc->gettrois_sommets_non_nuls()==true){parc=parc->getsuiv(); continue;}

		 if(Adaptive_Triangulation->RadioButton6->Checked)glBegin(GL_LINE_LOOP);
         if(Adaptive_Triangulation->RadioButton7->Checked)glBegin(GL_POLYGON);

//			glNormal3d(parc->gets1()->getnx_pt(),parc->gets1()->getny_pt(),parc->gets1()->getnz_pt());
			glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
			glVertex3d(parc->gets1()->getx_pt(),parc->gets1()->gety_pt(),parc->getz_pt1());

//			glNormal3d(parc->gets2()->getnx_pt(),parc->gets2()->getny_pt(),parc->gets2()->getnz_pt());
			glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
			glVertex3d(parc->gets2()->getx_pt(),parc->gets2()->gety_pt(),parc->getz_pt2());

//			glNormal3d(parc->gets3()->getnx_pt(),parc->gets3()->getny_pt(),parc->gets3()->getnz_pt());
            glNormal3d(parc->getnx(),parc->getny(),parc->getnz());
            glVertex3d(parc->gets3()->getx_pt(),parc->gets3()->gety_pt(),parc->getz_pt3());
           glEnd();


parc=parc->getsuiv();
}



if(Adaptive_Triangulation->RadioButton2->Checked || Adaptive_Triangulation->RadioButton6->Checked)
{
glDisable(GL_DEPTH_TEST);
glDisable(GL_LIGHTING);
}

}


//-------------------------

void TAdaptive_Triangulation::dessiner_triangle_3D_f()
  {

if(Adaptive_Triangulation->RadioButton2->Checked)
{
Rendering->reglage_eclairage();
glEnable(GL_DEPTH_TEST);
}

	 glColor3d(0.5, 0.9, 0.2);
	 glLineWidth((float)Adaptive_Triangulation->ComboBox11->Text.ToDouble());

triangle_initial *parc=Point_Clouds_Import->liste_triangle_adaptation->gettete();

while(parc!=NULL)
{
         if(parc->getfiltre()==false){parc=parc->getsuiv(); continue;}

         if(Adaptive_Triangulation->RadioButton1->Checked)glBegin(GL_LINE_LOOP);
         if(Adaptive_Triangulation->RadioButton2->Checked)glBegin(GL_POLYGON);

            glNormal3d(parc->gets1()->getnx_pt(),parc->gets1()->getny_pt(),parc->gets1()->getnz_pt());
            glVertex3d(parc->gets1()->getx_pt(),parc->gets1()->gety_pt(),parc->gets1()->getz());

            glNormal3d(parc->gets2()->getnx_pt(),parc->gets2()->getny_pt(),parc->gets2()->getnz_pt());
            glVertex3d(parc->gets2()->getx_pt(),parc->gets2()->gety_pt(),parc->gets2()->getz());

            glNormal3d(parc->gets3()->getnx_pt(),parc->gets3()->getny_pt(),parc->gets3()->getnz_pt());
            glVertex3d(parc->gets3()->getx_pt(),parc->gets3()->gety_pt(),parc->gets3()->getz());
           glEnd();


parc=parc->getsuiv();
}




if(Adaptive_Triangulation->RadioButton2->Checked)
{
glDisable(GL_DEPTH_TEST);
glDisable(GL_LIGHTING);
}

}


//-------------------------

void TAdaptive_Triangulation::dessiner_triangle_3D_f_BEY()
  {

if(Adaptive_Triangulation->RadioButton7->Checked)
{
Rendering->reglage_eclairage();
glEnable(GL_DEPTH_TEST);
}

	 glColor3d(1, 0, 0);
     glLineWidth((float)Adaptive_Triangulation->ComboBox25->Text.ToDouble());

//triangle_initial_BEY *parc=Point_Clouds_Import->liste_triangle_adaptation_BEY->gettete();
triangle_initial_BEY *parc=Point_Clouds_Import->liste_triangle_Filtres_adaptation_BEY->gettete(); //Triangles filtrés

while(parc!=NULL)
{
         if(parc->getfiltre()==false){parc=parc->getsuiv(); continue;}

         if(Adaptive_Triangulation->RadioButton6->Checked)glBegin(GL_LINE_LOOP);
         if(Adaptive_Triangulation->RadioButton7->Checked)glBegin(GL_POLYGON);

//            glNormal3d(parc->gets1()->getnx_pt(),parc->gets1()->getny_pt(),parc->gets1()->getnz_pt());
            glVertex3d(parc->gets1()->getx_pt(),parc->gets1()->gety_pt(),parc->gets1()->getz());

//            glNormal3d(parc->gets2()->getnx_pt(),parc->gets2()->getny_pt(),parc->gets2()->getnz_pt());
            glVertex3d(parc->gets2()->getx_pt(),parc->gets2()->gety_pt(),parc->gets2()->getz());

//            glNormal3d(parc->gets3()->getnx_pt(),parc->gets3()->getny_pt(),parc->gets3()->getnz_pt());
            glVertex3d(parc->gets3()->getx_pt(),parc->gets3()->gety_pt(),parc->gets3()->getz());
           glEnd();


parc=parc->getsuiv();
}

if(Adaptive_Triangulation->RadioButton6->Checked)
{
glDisable(GL_DEPTH_TEST);
glDisable(GL_LIGHTING);
}

}



//------------------------------------------------------------------------------

//------------------------------------------------------------------------------


void __fastcall TAdaptive_Triangulation::Edit3KeyPress(TObject *Sender, char &Key)
{

switch (Key)
 {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case 0x08:break;
  default : Key=0x0;
 }
}

//---------------------------------------------------------------------------








//-------------------------

void __fastcall TAdaptive_Triangulation::Button3Click(TObject *Sender)
{


if (Edit32->Text=="")
  {
  ShowMessage(" donner la precision!!!");
  return;
  }

  if (Edit32->Text.ToDouble()==0)
  {
  ShowMessage(" la precision doit être strictement positive!!!");
  return;
  }


bool subdiviser_ligne, subdiviser_colonne;


subdiviser_colonne=true;
subdiviser_ligne=false;

//-------------  Filtrage des triangles en fonction des points proches des sommets P1, P2 et P3

repartition_pt_correcte_triangle=true;

Adaptive_Triangulation->determiner_pts_proches_sommets_triangle();
Adaptive_Triangulation->filtrer_triangles_distances_sommets_triangle();
//-------------

if(maj==false) precision=Edit32->Text.ToDouble();

//if (Adaptive_Triangulation->dist_max <= precision && repartition_pt_correcte_triangle==true) return;
if (Adaptive_Triangulation->dist_max <= precision)
{
//   GroupBox6->Visible=true;
//   Adaptive_Triangulation->choix_z_triangle();
   return;
}

int nbre_subdivision=0;

//while (Adaptive_Triangulation->dist_max >precision || repartition_pt_correcte_triangle==false)
while (Adaptive_Triangulation->dist_max >precision)
  {
nbre_subdivision++;

//if(nbre_subdivision==10)break;

   Screen->Cursor= crHourGlass;
   int div,nb_x,nb_y;

   vx_pas= new double[nbre_segments_x];

   vy_pas= new double[nbre_segments_y];

   subdiv_col= new bool [nbre_segments_x];

   subdiv_lig= new bool [nbre_segments_y];

   int nbr_div_x=0;
   int nbr_div_y=0;

   for (int j=0;j<nbre_segments_x;j++)subdiv_col[j]=0;

   for (int j=0;j<nbre_segments_y;j++)subdiv_lig[j]=0;

   px1=Point_Clouds_Import->nuage_pts_BEY->getL()/nbre_segments_x;
   py1=Point_Clouds_Import->nuage_pts_BEY->getl()/nbre_segments_y;

   for (int j=0;j<nbre_segments_x;j++)vx_pas[j]=px1;

   for (int j=0;j<nbre_segments_y;j++)vy_pas[j]=py1;


//--------Determination des colonnes à subdiviser------------------
if(subdiviser_colonne==true)
{

      for (int j=0;j<nbre_segments_x;j=j+2)
      {
       for (int i=0;i<nbre_segments_y;i++)
        {
//          if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false && (Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max()>precision || Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getnbre_pts_proche_p1()==0 || Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getnbre_pts_proche_p2()==0 || Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getnbre_pts_proche_p3()==0))
		  if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false && (Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max()>precision || Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_proche_p1()==0 || Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_proche_p2()==0 || Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_proche_p3()==0))
		  {
                  subdiv_col[j/2]=1;
                  nbr_div_x=nbr_div_x+1;
                  break;
          }

//          if(Point_Clouds_Import->triangle_plan[i][j+1].getfiltre()==false && (Point_Clouds_Import->triangle_plan[i][j+1].getdist_pt_plan_max()>precision || Point_Clouds_Import->triangle_plan[i][j+1].getliste_pts_triangle()->getnbre_pts_proche_p1()==0 || Point_Clouds_Import->triangle_plan[i][j+1].getliste_pts_triangle()->getnbre_pts_proche_p2()==0 || Point_Clouds_Import->triangle_plan[i][j+1].getliste_pts_triangle()->getnbre_pts_proche_p3()==0))
		  if(Point_Clouds_Import->triangle_plan[i][j+1].getfiltre()==false && (Point_Clouds_Import->triangle_plan[i][j+1].getdist_pt_plan_max()>precision || Point_Clouds_Import->triangle_plan[i][j+1].getnbre_pts_proche_p1()==0 || Point_Clouds_Import->triangle_plan[i][j+1].getnbre_pts_proche_p2()==0 || Point_Clouds_Import->triangle_plan[i][j+1].getnbre_pts_proche_p3()==0))
		  {
                  subdiv_col[j/2]=1;
                  nbr_div_x=nbr_div_x+1;
                  break;
          }

          }//for
       }//for

}
//--------Determination des lignes à subdiviser------------------
if(subdiviser_ligne==true)
{

       for (int i=0;i<nbre_segments_y;i++)
        {
          for (int j=0;j<nbre_segments_x*2;j++)
           {
//                 if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false && (Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max()>precision  || Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getnbre_pts_proche_p1()==0 || Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getnbre_pts_proche_p2()==0 || Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getnbre_pts_proche_p3()==0))
				 if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false && (Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max()>precision  || Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_proche_p1()==0 || Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_proche_p2()==0 || Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_proche_p3()==0))
				  {
                  subdiv_lig[i]=1;
                  nbr_div_y=nbr_div_y+1;
                  break;
                  }
         }  //for
       }  //for

}

//--------Determination des nouveaux pas suivant X------------------

        int incre_x=-1;

         nb_x=nbre_segments_x;

         for (int i=0;i<nbre_segments_x;i++)
         {
               if (subdiv_col[i]==1)
               {
                 incre_x++;
                 div=i+incre_x;
                 nb_x++;
                 subdivision_x(div,nb_x);


                }

        }  //for

        nbre_segments_x=nb_x;

     for (int j=0;j<nbre_segments_x;j++)
     {
     double a=vx_pas[j];
     a++;
     }

//--------Determination des nouveaux pas suivant Y------------------
        int incre_y=-1;

         nb_y=nbre_segments_y;

          for (int i=0;i<nbre_segments_y;i++)
               {
              if (subdiv_lig[i]==1)
                {
                 incre_y++;
                 div=i+incre_y;
                 nb_y++;
                 subdivision_y(div,nb_y);
                }

        }  //for

       nbre_segments_y=nb_y;

       for (int j=0;j<nbre_segments_y;j++)
     {
     double a=vy_pas[j];
     a++;
     }

//-----------------creation des triangles----------------------------------



//--------------------------------creation des sommets-----------------

  Point_Clouds_Import->point_plan = new pt_plan*[nbre_segments_y+1];

 for (int j = 0; j < nbre_segments_y+1; j++)
     Point_Clouds_Import->point_plan [j] = new pt_plan[nbre_segments_x+1];

    double xmin=Point_Clouds_Import->nuage_pts_BEY->getxmin();
    double ymin=Point_Clouds_Import->nuage_pts_BEY->getymin();

//-----------------Matrice des points----------------------------------
    for (int i=0;i<nbre_segments_y+1;i++)
     {
      for (int j=0;j<nbre_segments_x+1;j++)
      {

        double somvx_pas=0;
        for (int k=0;k<=j-1;k++)somvx_pas=somvx_pas+vx_pas[k];

        double somvy_pas=0;
        for (int k=0;k<=i-1;k++)somvy_pas=somvy_pas+vy_pas[k];

        double x1=xmin+somvx_pas;
        double y1=ymin+somvy_pas;

       Point_Clouds_Import->point_plan[i][j].setx_pt(x1);
       Point_Clouds_Import->point_plan[i][j].sety_pt(y1);


     }//for


  }//for

  //

//---------------------------------------------------
 Point_Clouds_Import->triangle_plan = new triangle_initial*[nbre_segments_y];
 for (int j = 0; j < nbre_segments_y; j++)
     Point_Clouds_Import->triangle_plan [j] = new triangle_initial[nbre_segments_x*2];

    for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {
      if(j % 2 == 0)

      {
      Point_Clouds_Import->triangle_plan[i][j].setp1(&Point_Clouds_Import->point_plan[i][j/2]);
      Point_Clouds_Import->triangle_plan[i][j].setp2(&Point_Clouds_Import->point_plan[i+1][j/2+1]);
      Point_Clouds_Import->triangle_plan[i][j].setp3(&Point_Clouds_Import->point_plan[i+1][j/2]);
      }

      if(j % 2 == 1)
      {

      Point_Clouds_Import->triangle_plan[i][j].setp1(&Point_Clouds_Import->point_plan[i][(j-1)/2]);
      Point_Clouds_Import->triangle_plan[i][j].setp2(&Point_Clouds_Import->point_plan[i][((j-1)/2)+1]);
      Point_Clouds_Import->triangle_plan[i][j].setp3(&Point_Clouds_Import->point_plan[i+1][((j-1)/2)+1]);
      }

     }


  }
  //---------------------------limites triangles----------------------------
  double xmin_ta1,xmax_ta1,ymin_ta1,ymax_ta1;
 for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {

        xmin_ta1=Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt();
        xmax_ta1=Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt();

        ymin_ta1=Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt();
        ymax_ta1=Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt();

  //__________________________xmin,xmax______________

      if(xmin_ta1>Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt())
      xmin_ta1=Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt();

      if(xmax_ta1<Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt())
      xmax_ta1=Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt();


      if(xmin_ta1>Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt())
      xmin_ta1=Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt();

      if(xmax_ta1<Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt())
      xmax_ta1=Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt();


  //_____________________________Ymin,Ymax_____________

   if(ymin_ta1>Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt())
      ymin_ta1=Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt();

      if(ymax_ta1<Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt())
      ymax_ta1=Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt();


      if(ymin_ta1>Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt())
      ymin_ta1=Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt();

      if(ymax_ta1<Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt())
      ymax_ta1=Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt();



      Point_Clouds_Import->triangle_plan[i][j].setxmin_t(xmin_ta1);
      Point_Clouds_Import->triangle_plan[i][j].setxmax_t(xmax_ta1);
      Point_Clouds_Import->triangle_plan[i][j].setymin_t(ymin_ta1);
      Point_Clouds_Import->triangle_plan[i][j].setymax_t(ymax_ta1);
      }



  }


//___________________________déterminer la nouvelle liste de triangle__________________________________

for (int i=0;i<nbre_segments_y;i++)
        for (int j=0;j<nbre_segments_x*2;j++)
              Point_Clouds_Import->triangle_plan[i][j].setfiltre(false);

int i_min,i_max,j_min,j_max;

for (int i=0;i<nbre_segments_y;i++)
        {
        for (int j=0;j<nbre_segments_x;j++)
           {

			i_min=(int)((Point_Clouds_Import->triangle_plan[i][2*j].getp1()->gety_pt()-Point_Clouds_Import->nuage_pts_BEY->getymin())/py);
			j_min=(int)((Point_Clouds_Import->triangle_plan[i][2*j].getp1()->getx_pt()-Point_Clouds_Import->nuage_pts_BEY->getxmin())/px);
			i_max=(int)((Point_Clouds_Import->triangle_plan[i][2*j].getp2()->gety_pt()-Point_Clouds_Import->nuage_pts_BEY->getymin())/py);
			j_max=(int)((Point_Clouds_Import->triangle_plan[i][2*j].getp2()->getx_pt()-Point_Clouds_Import->nuage_pts_BEY->getxmin())/px);


           if (j_max==nbre_cellule_x)

             j_max=nbre_cellule_x-1;



           if (i_max==nbre_cellule_y)
             i_max=nbre_cellule_y-1;


//-----test d'appartenance point à un triangle------------------


 //noeud_point_nuage_BEY *test;


		 }//for
        }//for



//nbre de points des triangles
int somme=0;
     for (int i=0;i<nbre_segments_y;i++)
     {
     for (int j=0;j<nbre_segments_x*2;j++)
      {
	   somme=somme+Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle();
      }
     }

     if(somme!=Point_Clouds_Import->nuage_pts_BEY->getnbre_pt())
     {
     //ShowMessage("Erreur dans votre programme  !!!!!!!");
     }

//

//--------------------------calcul la cordonnée z par moindre carré----------
     //return;

     double a[3][3],b[3],x[3];
     double xx,yy,zz;
     double x1,y1,x2,y2,x3,y3;

     for (int i=0;i<nbre_segments_y;i++)
     {
     for (int j=0;j<nbre_segments_x*2;j++)
      {
//____ Gestion des exceptions: plan vertical et nbre de points inferieur à 3

	   noeud_point_nuage_BEY *temp;
       noeud_point_nuage_BEY *temp1;

//---- verification du nombre de points
       if (Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle()<3)Point_Clouds_Import->triangle_plan[i][j].setfiltre(true);


//--------- verification si les points sont alignés suivant x,

                if (Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false)
                {
                temp=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();

                temp1=temp->getsuiv2();

                     while (temp1!=NULL)
                     {


                          if (fabs(temp->getpoint()->getx()-temp1->getpoint()->getx())<precision_calcul)
                          {
                          Point_Clouds_Import->triangle_plan[i][j].setfiltre(true);
                          temp1=temp1->getsuiv2();
                          continue;
                          }
                          else
                          {
                              Point_Clouds_Import->triangle_plan[i][j].setfiltre(false);
                              break;
                          }


                     }

                }


//--------- verification si les points sont alignés suivant y,


                if (Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false)
                {
                temp=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();

                temp1=temp->getsuiv2();

                     while (temp1!=NULL)
                     {


                          if (fabs(temp->getpoint()->gety()-temp1->getpoint()->gety())<precision_calcul)
                          {
                          Point_Clouds_Import->triangle_plan[i][j].setfiltre(true);
                          temp1=temp1->getsuiv2();
                          continue;
                          }
                          else
                          {
                              Point_Clouds_Import->triangle_plan[i][j].setfiltre(false);
                              break;
                          }


                     }

                }



//--------- verification si les points sont alignés suivant une droite,



         if (Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false)
                {
                temp=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();

                temp1=temp->getsuiv2();

                if (fabs(temp1->getpoint()->getx()-temp->getpoint()->getx())>precision_calcul)
                {
                double pente= (temp1->getpoint()->gety()-temp->getpoint()->gety())/(temp1->getpoint()->getx()-temp->getpoint()->getx());

                temp1=temp->getsuiv2();

                     while (temp1!=NULL)
                     {
                     if (fabs(temp1->getpoint()->getx()-temp->getpoint()->getx())>precision_calcul)
                        {

                       double pente1= (temp1->getpoint()->gety()-temp->getpoint()->gety())/(temp1->getpoint()->getx()-temp->getpoint()->getx());


                         if (fabs(pente-pente1)<precision_calcul)
                          {
                          Point_Clouds_Import->triangle_plan[i][j].setfiltre(true);
                          temp1=temp1->getsuiv2();
                          continue;
                          }
                          else
                          {
                              Point_Clouds_Import->triangle_plan[i][j].setfiltre(false);
                              break;
                          }
                        }

                       else
                       {

                       temp1=temp1->getsuiv2();

                       }
                     }//while
                 } //if
                 else
                 {
                  Point_Clouds_Import->triangle_plan[i][j].setfiltre(false);

                 }
                }

//--------------------------------------fin filtre----------------------------


      if (Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;

       double a00=0;
       double a01=0;
       double a02=0;

       double a10=0;
       double a11=0;
       double a12=0;

       double a20=0;
       double a21=0;
       double a22=0;

       double b0=0;
       double b1=0;
       double b2=0;

     noeud_point_nuage_BEY *test;

          test=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();
          Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle();

         while (test!=NULL)
           {


            xx=test->getpoint()->getx();

            yy=test->getpoint()->gety();

            zz=test->getpoint()->getz();

            a00=a00+xx*xx;
            a01=a01+xx*yy;
            a02=a02+xx;

            a10=a10+xx*yy;
            a11=a11+yy*yy;
            a12=a12+yy;

            a20=a20+xx;
            a21=a21+yy;
            a22=Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle();


            b0=b0+xx*zz;
            b1=b1+yy*zz;
            b2=b2+zz;

            test=test->getsuiv2();

            }



             a[0][0]=a00;
             a[0][1]=a01;
             a[0][2]=a02;

             a[1][0]=a10;
             a[1][1]=a11;
             a[1][2]=a12;

             a[2][0]=a20;
             a[2][1]=a21;
             a[2][2]=a22;

             b[0]=b0;
             b[1]=b1;
             b[2]=b2;

             bool probleme;
            gauss_pivot_total(a,b,x, probleme);

             x1=Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt();
             y1=Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt();

             x2=Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt();
             y2=Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt();

             x3=Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt();
             y3=Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt();

			 double z1=x[0]*x1+x[1]*y1+x[2];
             double z2=x[0]*x2+x[1]*y2+x[2];
			 double z3=x[0]*x3+x[1]*y3+x[2];

//--------------------------------------------------------
		   double nx=x[0];
		   double ny=x[1];
		   double nz=-1;

		   if(nz<0){nx=-nx; ny=-ny; nz=-nz;}

		   double module=sqrt(nx*nx+ny*ny+nz*nz);

		   nx=nx/module;
		   ny=ny/module;
		   nz=nz/module;

		   Point_Clouds_Import->triangle_plan[i][j].setnx(nx);
		   Point_Clouds_Import->triangle_plan[i][j].setny(ny);
		   Point_Clouds_Import->triangle_plan[i][j].setnz(nz);
//--------------------------------------------------------

			 Point_Clouds_Import->triangle_plan[i][j].seta_plan(x[0]);
			 Point_Clouds_Import->triangle_plan[i][j].setb_plan(x[1]);
			 Point_Clouds_Import->triangle_plan[i][j].setc_plan(x[2]);

			 if(z1>2*Point_Clouds_Import->nuage_pts_BEY->getzmax() || z1<2*Point_Clouds_Import->nuage_pts_BEY->getzmin()
			 || z2>2*Point_Clouds_Import->nuage_pts_BEY->getzmax() || z2<2*Point_Clouds_Import->nuage_pts_BEY->getzmin()
			 || z3>2*Point_Clouds_Import->nuage_pts_BEY->getzmax() || z3<2*Point_Clouds_Import->nuage_pts_BEY->getzmin())
			 {
			 int b=0;
			 triangle_initial tr=Point_Clouds_Import->triangle_plan[i][j];
			 b++;
			 }

			 Point_Clouds_Import->triangle_plan[i][j].setz_pt1(z1);
			 Point_Clouds_Import->triangle_plan[i][j].setz_pt2(z2);
			 Point_Clouds_Import->triangle_plan[i][j].setz_pt3(z3);





	} //for
  } //for



  //------------------distance maximum entre les point de triangle et le plan-------
 double distance;
 double xpt,ypt,zpt;
 double a1,b1,c1,max_distance;
for (int i=0;i<nbre_segments_y;i++)
	 {
	 for (int j=0;j<nbre_segments_x*2;j++)
	  {
	  if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;

		 a1=Point_Clouds_Import->triangle_plan[i][j].geta_plan();
		 b1=Point_Clouds_Import->triangle_plan[i][j].getb_plan();
		 c1=Point_Clouds_Import->triangle_plan[i][j].getc_plan();

		 noeud_point_nuage_BEY *point_p;
		 point_p=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();

		 xpt=point_p->getpoint()->getx();
		 ypt=point_p->getpoint()->gety();
		 zpt=point_p->getpoint()->getz();


		 distance=fabs(a1*xpt+b1*ypt-zpt+c1)/sqrt(a1*a1+b1*b1+1);

		max_distance=distance;

		point_p=point_p->getsuiv2();

		 while (point_p!=NULL)
		 {

		 xpt=point_p->getpoint()->getx();
		 ypt=point_p->getpoint()->gety();
		 zpt=point_p->getpoint()->getz();


		 distance=fabs(a1*xpt+b1*ypt-zpt+c1)/sqrt(a1*a1+b1*b1+1);

	   if(distance>max_distance){max_distance=distance;}


	   point_p=point_p->getsuiv2();
	  }//while
	  Point_Clouds_Import->triangle_plan[i][j].setdist_pt_plan_max(max_distance);
	 }//for
	}//for
	//---------------------------l'erreur-----------------------------------
	double max_distance1, min_distance1;

	 max_distance1=-1;
	 min_distance1=1e20;


	for (int i=0;i<nbre_segments_y;i++)
	 {
	 for (int j=0;j<nbre_segments_x*2;j++)
	  {
	   if (Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false)
	   {

		if (Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max()>max_distance1)
			 {max_distance1=Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max();}

		if (Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max()<min_distance1)
			 {min_distance1=Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max();}


	   }




   }//for
}//for
	  dist_max=max_distance1;
	  dist_min=min_distance1;


	  //GroupBox5->Visible=true;
	  Edit34->Text=FormatFloat("0.0000000",dist_max);
	  Edit33->Text=FormatFloat("0.0000000",dist_min);

//	  Edit33->Refresh();
//	  Edit34->Refresh();

//-------------  Filtrage des triangles en fonction des points proches des sommets P1, P2 et P3
repartition_pt_correcte_triangle=true;

Adaptive_Triangulation->determiner_pts_proches_sommets_triangle();
Adaptive_Triangulation->filtrer_triangles_distances_sommets_triangle();
//-------------

       Screen->Cursor= crDefault;

if(subdiviser_ligne==true){subdiviser_ligne=false; subdiviser_colonne=true;continue;}

if(subdiviser_ligne==false){subdiviser_ligne=true; subdiviser_colonne=false;continue;}


  }//while


   GroupBox6->Visible=true;
   Adaptive_Triangulation->choix_z_triangle();



//---------------Triangles filtrés----------------------------------------------
		CheckBox11->Enabled=false;
		CheckBox10->Enabled=false;

	   for (int i=0;i<nbre_segments_y;i++)
		 for (int j=0;j<nbre_segments_x*2;j++)
		 {
		   if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true){CheckBox11->Enabled=true;CheckBox10->Enabled=true;break;}
		 }

Visualization->DrawObjects();
//------------------------------------------------------------------------------



}//fonction




//--------------------------------calcul et choix de hauteur z de chaque triangle-------------------------------------------

void TAdaptive_Triangulation::choix_z_triangle()
{

double z1,z2,z3,z4,z5,z6;
double z_pt_max,z_pt_min,z_pt_moy;

 int compt;
 double som;



//--------------------------1 Zpt egale a (xmin,ymin) de nuage

    if (Point_Clouds_Import->triangle_plan[0][0].getfiltre()==true &&  Point_Clouds_Import->triangle_plan[0][1].getfiltre()==true)
        Point_Clouds_Import->point_plan[0][0].setfiltre(true);

    if (Point_Clouds_Import->triangle_plan[0][0].getfiltre()==false ||  Point_Clouds_Import->triangle_plan[0][1].getfiltre()==false)
    {
         som=0;
         compt=0;

         if (Point_Clouds_Import->triangle_plan[0][0].getfiltre()==false) {z1=Point_Clouds_Import->triangle_plan[0][0].getz_pt1(); z_pt_min=z_pt_max=z1; som=som+z1;compt++;}
         if (Point_Clouds_Import->triangle_plan[0][1].getfiltre()==false) {z2=Point_Clouds_Import->triangle_plan[0][1].getz_pt1(); z_pt_min=z_pt_max=z2; som=som+z2;compt++;}


         //calcul de z plan max
         if(Point_Clouds_Import->triangle_plan[0][0].getfiltre()==false && z_pt_max<z1)     z_pt_max=z1;

         if(Point_Clouds_Import->triangle_plan[0][1].getfiltre()==false && z_pt_max<z2)     z_pt_max=z2;

         Point_Clouds_Import->point_plan[0][0].setz_pt_max(z_pt_max);


 //calcul de z plan moyen

            z_pt_moy=som/compt;

            Point_Clouds_Import->point_plan[0][0].setz_pt_moy(z_pt_moy);


 //calcul de z plan min
         if(Point_Clouds_Import->triangle_plan[0][0].getfiltre()==false && z_pt_min>z1)     z_pt_min=z1;

         if(Point_Clouds_Import->triangle_plan[0][1].getfiltre()==false && z_pt_min>z2)     z_pt_min=z2;

         Point_Clouds_Import->point_plan[0][0].setz_pt_min(z_pt_min);

    }



 //--------------------------2 Zpt egale a (xmax,ymax)de nuage

     int ii=nbre_segments_y-1;
     int jj=nbre_segments_x*2-1;

    if (Point_Clouds_Import->triangle_plan[ii][jj].getfiltre()==true &&  Point_Clouds_Import->triangle_plan[ii][jj-1].getfiltre()==true)
        Point_Clouds_Import->point_plan[nbre_segments_y][nbre_segments_x].setfiltre(true);

   if (Point_Clouds_Import->triangle_plan[ii][jj].getfiltre()==false ||  Point_Clouds_Import->triangle_plan[ii][jj-1].getfiltre()==false)
    {
      som=0;
      compt=0;

       if (Point_Clouds_Import->triangle_plan[ii][jj].getfiltre()==false)   {z1=Point_Clouds_Import->triangle_plan[ii][jj].getz_pt3();      z_pt_min=z_pt_max=z1; som=som+z1;compt++;}
       if (Point_Clouds_Import->triangle_plan[ii][jj-1].getfiltre()==false) {z2=Point_Clouds_Import->triangle_plan[ii][jj-1].getz_pt2();    z_pt_min=z_pt_max=z2; som=som+z2;compt++;}


  //calcul de z plan max
      if(Point_Clouds_Import->triangle_plan[ii][jj].getfiltre()==false   && z_pt_max<z1)    z_pt_max=z1;

      if(Point_Clouds_Import->triangle_plan[ii][jj-1].getfiltre()==false && z_pt_max<z2)    z_pt_max=z2;

      Point_Clouds_Import->point_plan[nbre_segments_y][nbre_segments_x].setz_pt_max(z_pt_max);



 //calcul de z plan moyen

      z_pt_moy=som/compt;

      Point_Clouds_Import->point_plan[nbre_segments_y][nbre_segments_x].setz_pt_moy(z_pt_moy);



 //calcul de z plan min
      if(Point_Clouds_Import->triangle_plan[ii][jj].getfiltre()==false && z_pt_min>z1)      z_pt_min=z1;

      if(Point_Clouds_Import->triangle_plan[ii][jj-1].getfiltre()==false && z_pt_min>z2)    z_pt_min=z2;

       Point_Clouds_Import->point_plan[nbre_segments_y][nbre_segments_x].setz_pt_min(z_pt_min);



  }




 //-------------------------3 Zpt egale a limites (xmax,ymin) de nuage
if (Point_Clouds_Import->triangle_plan[0][jj].getfiltre()==true)
        Point_Clouds_Import->point_plan[0][nbre_segments_x].setfiltre(true);

if (Point_Clouds_Import->triangle_plan[0][jj].getfiltre()==false)
{
z1=Point_Clouds_Import->triangle_plan[0][jj].getz_pt2();


  //calcul de z plan max
      Point_Clouds_Import->point_plan[0][nbre_segments_x].setz_pt_max(z1);


 //calcul de z plan moyen


      Point_Clouds_Import->point_plan[0][nbre_segments_x].setz_pt_moy(z1);


 //calcul de z plan min

       Point_Clouds_Import->point_plan[0][nbre_segments_x].setz_pt_min(z1);
      

   }
//-------------------4 Zpt egale a limites (xmin,ymax) de nuage

 if (Point_Clouds_Import->triangle_plan[ii][0].getfiltre()==true)
        Point_Clouds_Import->point_plan[nbre_segments_y][0].setfiltre(true);

 if (Point_Clouds_Import->triangle_plan[ii][0].getfiltre()==false)
 {
 z1=Point_Clouds_Import->triangle_plan[ii][0].getz_pt3();


 // calcul de z plan max

         Point_Clouds_Import->point_plan[nbre_segments_y][0].setz_pt_max(z1);


 // calcul de z plan moyen


      Point_Clouds_Import->point_plan[nbre_segments_y][0].setz_pt_moy(z1);


 // calcul de z plan min

       Point_Clouds_Import->point_plan[nbre_segments_y][0].setz_pt_min(z1);
       
   }

//-------------------------5 Zpt egale z de point  (xmax,!ymax) de nuage
 for (int i=1;i<nbre_segments_y;i++)
   {

   if (Point_Clouds_Import->triangle_plan[i][jj].getfiltre()==true && Point_Clouds_Import->triangle_plan[i-1][jj].getfiltre()==true
          && Point_Clouds_Import->triangle_plan[i-1][jj-1].getfiltre()==true) {Point_Clouds_Import->point_plan[i][nbre_segments_x].setfiltre(true);  continue;}

 if (Point_Clouds_Import->triangle_plan[i][jj].getfiltre()==false || Point_Clouds_Import->triangle_plan[i-1][jj].getfiltre()==false
          || Point_Clouds_Import->triangle_plan[i-1][jj-1].getfiltre()==false)
      {
         som=0;
         compt=0;

     if (Point_Clouds_Import->triangle_plan[i][jj].getfiltre()==false)      {z1=Point_Clouds_Import->triangle_plan[i][jj].getz_pt2();      z_pt_min=z_pt_max=z1; som=som+z1;compt++;}
     if (Point_Clouds_Import->triangle_plan[i-1][jj].getfiltre()==false)    {z2=Point_Clouds_Import->triangle_plan[i-1][jj].getz_pt3();    z_pt_min=z_pt_max=z2; som=som+z2;compt++;}
	 if (Point_Clouds_Import->triangle_plan[i-1][jj-1].getfiltre()==false)  {z3=Point_Clouds_Import->triangle_plan[i-1][jj-1].getz_pt2();  z_pt_min=z_pt_max=z3; som=som+z3;compt++;}



//calcul de z plan max
      if(Point_Clouds_Import->triangle_plan[i][jj].getfiltre()==false && z_pt_max<z1)       z_pt_max=z1;

      if(Point_Clouds_Import->triangle_plan[i-1][jj].getfiltre()==false && z_pt_max<z2)     z_pt_max=z2;

      if(Point_Clouds_Import->triangle_plan[i-1][jj-1].getfiltre()==false && z_pt_max<z3)   z_pt_max=z3;

         Point_Clouds_Import->point_plan[i][nbre_segments_x].setz_pt_max(z_pt_max);


 //calcul de z plan moyen

      z_pt_moy=som/compt;

      Point_Clouds_Import->point_plan[i][nbre_segments_x].setz_pt_moy(z_pt_moy);


 //calcul de z plan min
      if(Point_Clouds_Import->triangle_plan[i][jj].getfiltre()==false && z_pt_min>z1)       z_pt_min=z1;

      if(Point_Clouds_Import->triangle_plan[i-1][jj].getfiltre()==false && z_pt_min>z2)     z_pt_min=z2;

      if(Point_Clouds_Import->triangle_plan[i-1][jj-1].getfiltre()==false && z_pt_min>z3)   z_pt_min=z3;

       Point_Clouds_Import->point_plan[i][nbre_segments_x].setz_pt_min(z_pt_min);
       
    }
    }//for i


  //-------------------------6 Zpt egale z de point  (xmin,!ymax) de nuage
  for (int i=1;i<nbre_segments_y;i++)
   {

  if (Point_Clouds_Import->triangle_plan[i][0].getfiltre()==true && Point_Clouds_Import->triangle_plan[i][1].getfiltre()==true
          && Point_Clouds_Import->triangle_plan[i-1][0].getfiltre()==true) {Point_Clouds_Import->point_plan[i][0].setfiltre(true);continue;}



 if (Point_Clouds_Import->triangle_plan[i][0].getfiltre()==false || Point_Clouds_Import->triangle_plan[i][1].getfiltre()==false
          || Point_Clouds_Import->triangle_plan[i-1][0].getfiltre()==false)
      {

          som=0;
          compt=0;
     if (Point_Clouds_Import->triangle_plan[i][0].getfiltre()==false)   {z1=Point_Clouds_Import->triangle_plan[i][0].getz_pt1();     z_pt_min=z_pt_max=z1; som=som+z1;compt++;}
     if (Point_Clouds_Import->triangle_plan[i][1].getfiltre()==false)   {z2=Point_Clouds_Import->triangle_plan[i][1].getz_pt1();     z_pt_min=z_pt_max=z2; som=som+z2;compt++;}
     if (Point_Clouds_Import->triangle_plan[i-1][0].getfiltre()==false) {z3=Point_Clouds_Import->triangle_plan[i-1][0].getz_pt3();   z_pt_min=z_pt_max=z3; som=som+z2;compt++;}


 // calcul de z plan max
      if(Point_Clouds_Import->triangle_plan[i][0].getfiltre()==false && z_pt_max<z1)        z_pt_max=z1;

      if(Point_Clouds_Import->triangle_plan[i][1].getfiltre()==false && z_pt_max<z2)        z_pt_max=z2;

      if(Point_Clouds_Import->triangle_plan[i-1][0].getfiltre()==false && z_pt_max<z3)      z_pt_max=z3;

         Point_Clouds_Import->point_plan[i][0].setz_pt_max(z_pt_max);


 // calcul de z plan moyen

      z_pt_moy=som/compt;

      Point_Clouds_Import->point_plan[i][0].setz_pt_moy(z_pt_moy);


 // calcul de z plan min

      if(Point_Clouds_Import->triangle_plan[i][0].getfiltre()==false && z_pt_min>z1)        z_pt_min=z1;

      if(Point_Clouds_Import->triangle_plan[i][1].getfiltre()==false && z_pt_min>z2)        z_pt_min=z2;

      if(Point_Clouds_Import->triangle_plan[i-1][0].getfiltre()==false && z_pt_min>z3)      z_pt_min=z3;

       Point_Clouds_Import->point_plan[i][0].setz_pt_min(z_pt_min);
       
    }
    
  }//for  i

//-------------------------7 Zpt egale z de point  (!xmax,ymin) de nuage
  for (int j=1;j<nbre_segments_x;j++)
     {

     if (Point_Clouds_Import->triangle_plan[0][2*j].getfiltre()==true && Point_Clouds_Import->triangle_plan[0][2*j-1].getfiltre()==true
          && Point_Clouds_Import->triangle_plan[0][2*j+1].getfiltre()==true)  {Point_Clouds_Import->point_plan[0][j].setfiltre(true);continue;}

     if (Point_Clouds_Import->triangle_plan[0][2*j].getfiltre()==false || Point_Clouds_Import->triangle_plan[0][2*j-1].getfiltre()==false
          || Point_Clouds_Import->triangle_plan[0][2*j+1].getfiltre()==false)
      {


         compt=0;
         som=0;

     if (Point_Clouds_Import->triangle_plan[0][2*j].getfiltre()==false)   {z1=Point_Clouds_Import->triangle_plan[0][2*j].getz_pt1();    z_pt_min=z_pt_max=z1; som=som+z1;compt++;}
     if (Point_Clouds_Import->triangle_plan[0][2*j-1].getfiltre()==false) {z2=Point_Clouds_Import->triangle_plan[0][2*j-1].getz_pt2();  z_pt_min=z_pt_max=z2; som=som+z2;compt++;}
     if (Point_Clouds_Import->triangle_plan[0][2*j+1].getfiltre()==false) {z3=Point_Clouds_Import->triangle_plan[0][2*j+1].getz_pt1();  z_pt_min=z_pt_max=z3; som=som+z3;compt++;}


     // calcul de z plan max
      if(Point_Clouds_Import->triangle_plan[0][2*j].getfiltre()==false && z_pt_max<z1)       z_pt_max=z1;

      if(Point_Clouds_Import->triangle_plan[0][2*j-1].getfiltre()==false && z_pt_max<z2)     z_pt_max=z2;

      if(Point_Clouds_Import->triangle_plan[0][2*j+1].getfiltre()==false && z_pt_max<z3)     z_pt_max=z3;

         Point_Clouds_Import->point_plan[0][j].setz_pt_max(z_pt_max);

 // calcul de z plan moyen

      z_pt_moy=som/compt;

      Point_Clouds_Import->point_plan[0][j].setz_pt_moy(z_pt_moy);

 // calcul de z plan min
      if(Point_Clouds_Import->triangle_plan[0][2*j].getfiltre()==false && z_pt_min>z1)       z_pt_min=z1;

      if(Point_Clouds_Import->triangle_plan[0][2*j-1].getfiltre()==false && z_pt_min>z2)     z_pt_min=z2;

      if(Point_Clouds_Import->triangle_plan[0][2*j+1].getfiltre()==false && z_pt_min>z3)     z_pt_min=z3;

       Point_Clouds_Import->point_plan[0][j].setz_pt_min(z_pt_min);
  
    }

 }//for j
   //-------------------------8 Zpt egale z de point  (!xmax,ymax) de nuage
  for (int j=1;j<nbre_segments_x;j++)
   {
 if (Point_Clouds_Import->triangle_plan[ii][2*j].getfiltre()==true && Point_Clouds_Import->triangle_plan[ii][2*j-1].getfiltre()==true
          && Point_Clouds_Import->triangle_plan[ii][2*j-2].getfiltre()==true) {Point_Clouds_Import->point_plan[nbre_segments_y][j].setfiltre(true);continue;}

 if (Point_Clouds_Import->triangle_plan[ii][2*j].getfiltre()==false || Point_Clouds_Import->triangle_plan[ii][2*j-1].getfiltre()==false
          || Point_Clouds_Import->triangle_plan[ii][2*j-2].getfiltre()==false)
      {



     compt=0;
     som=0;

     if (Point_Clouds_Import->triangle_plan[ii][2*j].getfiltre()==false)    {z1=Point_Clouds_Import->triangle_plan[ii][2*j].getz_pt3();    z_pt_min=z_pt_max=z1; som=som+z1;compt++;}
     if (Point_Clouds_Import->triangle_plan[ii][2*j-1].getfiltre()==false)  {z2=Point_Clouds_Import->triangle_plan[ii][2*j-1].getz_pt3();  z_pt_min=z_pt_max=z2; som=som+z2;compt++;}
     if (Point_Clouds_Import->triangle_plan[ii][2*j-2].getfiltre()==false)  {z3=Point_Clouds_Import->triangle_plan[ii][2*j-2].getz_pt2();  z_pt_min=z_pt_max=z3; som=som+z3;compt++;}


 //calcul de z plan max
      if(Point_Clouds_Import->triangle_plan[ii][2*j].getfiltre()==false && z_pt_max<z1)     z_pt_max=z1;

      if(Point_Clouds_Import->triangle_plan[ii][2*j-1].getfiltre()==false && z_pt_max<z2)    z_pt_max=z2;

      if(Point_Clouds_Import->triangle_plan[ii][2*j-2].getfiltre()==false && z_pt_max<z3)    z_pt_max=z3;

         Point_Clouds_Import->point_plan[nbre_segments_y][j].setz_pt_max(z_pt_max);
        // Point_Clouds_Import->point_plan[nbre_segments_y][j].setz(z_pt_max);

 //calcul de z plan moyen


      z_pt_moy=(som)/compt;
      Point_Clouds_Import->point_plan[nbre_segments_y][j].setz_pt_moy(z_pt_moy);
     // Point_Clouds_Import->point_plan[nbre_segments_y][j].setz(z_pt_moy);

 //calcul de z plan min
      if(Point_Clouds_Import->triangle_plan[ii][2*j].getfiltre()==false && z_pt_min>z1)      z_pt_min=z1;

      if(Point_Clouds_Import->triangle_plan[ii][2*j-1].getfiltre()==false && z_pt_min>z2)    z_pt_min=z2;

       if(Point_Clouds_Import->triangle_plan[ii][2*j-2].getfiltre()==false && z_pt_min>z3)   z_pt_min=z3;

       Point_Clouds_Import->point_plan[nbre_segments_y][j].setz_pt_min(z_pt_min);
    //   Point_Clouds_Import->point_plan[nbre_segments_y][j].setz(z_pt_min);

   }
  }//for j



 //____________________9 fin exeption



   for (int i=1;i<nbre_segments_y;i++)
   {
     for (int j=1;j<nbre_segments_x;j++)
     {

     if(i!=0 && j!=0 && i!=nbre_segments_y && j!=nbre_segments_x)
     {

   if (Point_Clouds_Import->triangle_plan[i][2*j-1].getfiltre()==true      && Point_Clouds_Import->triangle_plan[i][2*j].getfiltre()==true
       && Point_Clouds_Import->triangle_plan[i][2*j+1].getfiltre()==true   && Point_Clouds_Import->triangle_plan[i-1][2*j-2].getfiltre()==true
       && Point_Clouds_Import->triangle_plan[i-1][2*j-1].getfiltre()==true && Point_Clouds_Import->triangle_plan[i-1][2*j].getfiltre()==true)
       {
       Point_Clouds_Import->point_plan[i][j].setfiltre(true);
       continue;
       }

     compt=0;
     som=0;

	if (Point_Clouds_Import->triangle_plan[i][2*j-1].getfiltre()==false)   {z1=Point_Clouds_Import->triangle_plan[i][2*j-1].getz_pt2();  z_pt_min=z_pt_max=z1;som=som+z1;compt++;}
    if (Point_Clouds_Import->triangle_plan[i][2*j].getfiltre()==false)     {z2=Point_Clouds_Import->triangle_plan[i][2*j].getz_pt1();    z_pt_min=z_pt_max=z2;som=som+z2;compt++;}
    if (Point_Clouds_Import->triangle_plan[i][2*j+1].getfiltre()==false)   { z3=Point_Clouds_Import->triangle_plan[i][2*j+1].getz_pt1(); z_pt_min=z_pt_max=z3;som=som+z3;compt++;}

    if (Point_Clouds_Import->triangle_plan[i-1][2*j-2].getfiltre()==false) {z4=Point_Clouds_Import->triangle_plan[i-1][2*j-2].getz_pt2(); z_pt_min=z_pt_max=z4;som=som+z4;compt++;}
    if (Point_Clouds_Import->triangle_plan[i-1][2*j-1].getfiltre()==false) {z5=Point_Clouds_Import->triangle_plan[i-1][2*j-1].getz_pt3(); z_pt_min=z_pt_max=z5;som=som+z5;compt++;}
    if (Point_Clouds_Import->triangle_plan[i-1][2*j].getfiltre()==false)   {z6=Point_Clouds_Import->triangle_plan[i-1][2*j].getz_pt3();   z_pt_min=z_pt_max=z6;som=som+z6;compt++;}



 //--------------------calcul de z plan max
      if(Point_Clouds_Import->triangle_plan[i][2*j-1].getfiltre()==false && z_pt_max<z1)    z_pt_max=z1;

      if(Point_Clouds_Import->triangle_plan[i][2*j].getfiltre()==false && z_pt_max<z2)      z_pt_max=z2;

      if(Point_Clouds_Import->triangle_plan[i][2*j+1].getfiltre()==false && z_pt_max<z3)    z_pt_max=z3;

      if(Point_Clouds_Import->triangle_plan[i-1][2*j-2].getfiltre()==false && z_pt_max<z4)  z_pt_max=z4;

      if(Point_Clouds_Import->triangle_plan[i-1][2*j-1].getfiltre()==false && z_pt_max<z5)  z_pt_max=z5;

      if(Point_Clouds_Import->triangle_plan[i-1][2*j].getfiltre()==false && z_pt_max<z6)    z_pt_max=z6;

      Point_Clouds_Import->point_plan[i][j].setz_pt_max(z_pt_max);
     // Point_Clouds_Import->point_plan[i][j].setz(z_pt_max);

 //-------------------calcul de z plan moyen

         z_pt_moy=som/compt;

      Point_Clouds_Import->point_plan[i][j].setz_pt_moy(z_pt_moy);
     // Point_Clouds_Import->point_plan[i][j].setz(z_pt_moy);

 //--------------calcul de z plan min
      if(Point_Clouds_Import->triangle_plan[i][2*j-1].getfiltre()==false && z_pt_min>z1)    z_pt_min=z1;

      if(Point_Clouds_Import->triangle_plan[i][2*j].getfiltre()==false && z_pt_min>z2)      z_pt_min=z2;

      if(Point_Clouds_Import->triangle_plan[i][2*j+1].getfiltre()==false && z_pt_min>z3)    z_pt_min=z3;

      if(Point_Clouds_Import->triangle_plan[i-1][2*j-2].getfiltre()==false && z_pt_min>z4)  z_pt_min=z4;

      if(Point_Clouds_Import->triangle_plan[i-1][2*j-1].getfiltre()==false && z_pt_min>z5)  z_pt_min=z5;

      if(Point_Clouds_Import->triangle_plan[i-1][2*j].getfiltre()==false && z_pt_min>z6)    z_pt_min=z6;


      Point_Clouds_Import->point_plan[i][j].setz_pt_min(z_pt_min);
     // Point_Clouds_Import->point_plan[i][j].setz(z_pt_min);
   }//if






}//for
}//for

  }//fonction choix de z



//---------------------------------calcul de la normale-------------------------------------------

                                  


//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::Button4Click(TObject *Sender)
{
	for (int i=0;i<nbre_segments_y;i++)
	 { for (int j=0;j<nbre_segments_x*2;j++)
	  {

	  if (mode=="min")   //Zmin
	  {
	  if(j % 2 == 0)

	  {
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt1(Point_Clouds_Import->point_plan[i][j/2].getz_pt_min());
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt2(Point_Clouds_Import->point_plan[i+1][j/2+1].getz_pt_min());
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt3(Point_Clouds_Import->point_plan[i+1][j/2].getz_pt_min());
	  }

	  if(j % 2 == 1)
	  {

	  Point_Clouds_Import->triangle_plan[i][j].setz_pt1(Point_Clouds_Import->point_plan[i][(j-1)/2].getz_pt_min());
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt2(Point_Clouds_Import->point_plan[i][((j-1)/2)+1].getz_pt_min());
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt3(Point_Clouds_Import->point_plan[i+1][((j-1)/2)+1].getz_pt_min());
	  }

	 }//if

	   if (mode=="moy")      //Zmoy
	  {
	  if(j % 2 == 0)

	  {
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt1(Point_Clouds_Import->point_plan[i][j/2].getz_pt_moy());
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt2(Point_Clouds_Import->point_plan[i+1][j/2+1].getz_pt_moy());
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt3(Point_Clouds_Import->point_plan[i+1][j/2].getz_pt_moy());
	  }

	  if(j % 2 == 1)
	  {

	  Point_Clouds_Import->triangle_plan[i][j].setz_pt1(Point_Clouds_Import->point_plan[i][(j-1)/2].getz_pt_moy());
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt2(Point_Clouds_Import->point_plan[i][((j-1)/2)+1].getz_pt_moy());
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt3(Point_Clouds_Import->point_plan[i+1][((j-1)/2)+1].getz_pt_moy());
	  }

	 }//if

	  if (mode=="max")    //Zmax
	  {
	  if(j % 2 == 0)

	  {
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt1(Point_Clouds_Import->point_plan[i][j/2].getz_pt_max());
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt2(Point_Clouds_Import->point_plan[i+1][j/2+1].getz_pt_max());
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt3(Point_Clouds_Import->point_plan[i+1][j/2].getz_pt_max());
	  }

	  if(j % 2 == 1)
	  {

	  Point_Clouds_Import->triangle_plan[i][j].setz_pt1(Point_Clouds_Import->point_plan[i][(j-1)/2].getz_pt_max());
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt2(Point_Clouds_Import->point_plan[i][((j-1)/2)+1].getz_pt_max());
	  Point_Clouds_Import->triangle_plan[i][j].setz_pt3(Point_Clouds_Import->point_plan[i+1][((j-1)/2)+1].getz_pt_max());
	  }

	 }//if
	} //for
  }//for
///___________________________________________________
	for (int i=0;i<nbre_segments_y+1;i++)
	 { for (int j=0;j<nbre_segments_x+1;j++)
	  {
	   if (Point_Clouds_Import->point_plan[i][j].getfiltre()==true) continue;

	  if (RadioButton3->Checked)Point_Clouds_Import->point_plan[i][j].setz(Point_Clouds_Import->point_plan[i][j].getz_pt_min());

	  if (RadioButton4->Checked)Point_Clouds_Import->point_plan[i][j].setz(Point_Clouds_Import->point_plan[i][j].getz_pt_moy());

	  if (RadioButton5->Checked)Point_Clouds_Import->point_plan[i][j].setz(Point_Clouds_Import->point_plan[i][j].getz_pt_max());
	  }
	 }
  //----------------------------calcul de la normal de triangle ------------------

 double a_plan1,b_plan1,c_plan1;
 double  nx1,nx2,nx3,ny1,ny2,ny3,nz1,nz2,nz3;
 double a,b,c;
	for (int i=0;i<nbre_segments_y;i++)
	 {
	 for (int j=0;j<nbre_segments_x*2;j++)
	  {
		if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;

			  nx1=Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt();
			  ny1=Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt();
			  nz1=Point_Clouds_Import->triangle_plan[i][j].getz_pt1();

			  nx2=Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt();
			  ny2=Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt();
			  nz2=Point_Clouds_Import->triangle_plan[i][j].getz_pt2();

			  nx3=Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt();
			  ny3=Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt();
			  nz3=Point_Clouds_Import->triangle_plan[i][j].getz_pt3();

   //calcul produit vectoriel p1p2_

   double   x1=nx2-nx1;
   double   y1=ny2-ny1;
   double   z1=nz2-nz1;

   //calcul produit vectoriel p1p3_

   double   x2=nx3-nx1;
   double   y2=ny3-ny1;
   double   z2=nz3-nz1;


	 a_plan1=y1*z2-z1*y2;
	 b_plan1=z1*x2-x1*z2;
	 c_plan1=x1*y2-y1*x2;

	 double d=-a_plan1*nx1-b_plan1*ny1-c_plan1*nz1;

	 a=-a_plan1/c_plan1;
	 b=-b_plan1/c_plan1;
	 c=-d/c_plan1;

   Point_Clouds_Import->triangle_plan[i][j].seta_plan(a);
   Point_Clouds_Import->triangle_plan[i][j].setb_plan(b);
   Point_Clouds_Import->triangle_plan[i][j].setc_plan(c);


//--------------------------------------------------------
		   double nx=a_plan1;
		   double ny=b_plan1;
		   double nz=c_plan1;

		   if(nz<0){nx=-nx; ny=-ny; nz=-nz;}

		   double module=sqrt(nx*nx+ny*ny+nz*nz);

		   nx=nx/module;
		   ny=ny/module;
		   nz=nz/module;

		   Point_Clouds_Import->triangle_plan[i][j].setnx(nx);
		   Point_Clouds_Import->triangle_plan[i][j].setny(ny);
		   Point_Clouds_Import->triangle_plan[i][j].setnz(nz);

//--------------------------------------------------------
   }//for
}//for

  //------------------distance maximum entre les point de triangle et le nouveau plan-------
 double distance;
 double xpt,ypt,zpt;
 double a1,b1,c1,max_distance,min_distance;
for (int i=0;i<nbre_segments_y;i++)
	 {
	 for (int j=0;j<nbre_segments_x*2;j++)
	  {
	  if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;

		 a1=Point_Clouds_Import->triangle_plan[i][j].geta_plan();
		 b1=Point_Clouds_Import->triangle_plan[i][j].getb_plan();
		 c1=Point_Clouds_Import->triangle_plan[i][j].getc_plan();

		 noeud_point_nuage_BEY *point_p;
		 point_p=Point_Clouds_Import->triangle_plan[i][j].getliste_pts_triangle()->getdebut();

		 xpt=point_p->getpoint()->getx();
		 ypt=point_p->getpoint()->gety();
		 zpt=point_p->getpoint()->getz();


		 distance=fabs(a1*xpt+b1*ypt-zpt+c1)/sqrt(a1*a1+b1*b1+1);

		max_distance=distance;
		min_distance=distance;

		point_p=point_p->getsuiv2();

		 while (point_p!=NULL)
		 {

		 xpt=point_p->getpoint()->getx();
		 ypt=point_p->getpoint()->gety();
		 zpt=point_p->getpoint()->getz();


		 distance=fabs(a1*xpt+b1*ypt-zpt+c1)/sqrt(a1*a1+b1*b1+1);

	   if(distance>max_distance){max_distance=distance;}
	   if(distance<min_distance){min_distance=distance;}

	   point_p=point_p->getsuiv2();
	  }//while
	  Point_Clouds_Import->triangle_plan[i][j].setdist_pt_plan_max(max_distance);
	  Point_Clouds_Import->triangle_plan[i][j].setdist_pt_plan_min(min_distance);
	 }//for
	}//for
	//---------------------------l'erreur-----------------------------------
	double max_distance1, min_distance1;

	 max_distance1=-1e10;
	 min_distance1=1e10;

	for (int i=0;i<nbre_segments_y;i++)
	 {
	 for (int j=0;j<nbre_segments_x*2;j++)
	  {
	   if (Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false)
	   {

		if (Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max()>max_distance1)
			 {
			 max_distance1=Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_max();
			 }

		if (Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_min()<min_distance1)
			 {
			 min_distance1=Point_Clouds_Import->triangle_plan[i][j].getdist_pt_plan_min();
			 }

	   }




   }//for
}//for
	  //double dist_min;
	  dist_max=max_distance1;
	  dist_min=min_distance1;


	  //GroupBox5->Visible=true;
	  Edit33->Text=FormatFloat("0.0000000",dist_min);
	  Edit34->Text=FormatFloat("0.0000000",dist_max);

	   Visualization->DrawObjects();
	   Screen->Cursor= crDefault;

}//fonction
//---------------------------------------------------------------------------
//fonction
//---------------------------------------------------------------------------
//---------------Triangles filtrés----------------------------------------------
void TAdaptive_Triangulation::gestion_checkbox11()
{
        CheckBox11->Enabled=false;
        CheckBox10->Enabled=false;

       for (int i=0;i<nbre_segments_y;i++)
         for (int j=0;j<nbre_segments_x*2;j++)
         {
           if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true){CheckBox11->Enabled=true;CheckBox10->Enabled=true;break;}
         }
}
//------------------------------------------------------------------------------

//------------Triangles sur chaque ligne où leur Zmax est en dehors des limites du brut--------------

void TAdaptive_Triangulation::traintement_triangles_hors_brut()
{
double ecart=30;

       for (int i=0;i<nbre_segments_y;i++)
         for (int j=0;j<nbre_segments_x*2;j++)
         {
           if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false &&
           ( (Point_Clouds_Import->triangle_plan[i][j].getz_pt1()>Point_Clouds_Import->nuage_pts_BEY->getzmax()+ecart || Point_Clouds_Import->triangle_plan[i][j].getz_pt1()<Point_Clouds_Import->nuage_pts_BEY->getzmin()-ecart)
           ||(Point_Clouds_Import->triangle_plan[i][j].getz_pt2()>Point_Clouds_Import->nuage_pts_BEY->getzmax()+ecart || Point_Clouds_Import->triangle_plan[i][j].getz_pt2()<Point_Clouds_Import->nuage_pts_BEY->getzmin()-ecart)
		   ||(Point_Clouds_Import->triangle_plan[i][j].getz_pt3()>Point_Clouds_Import->nuage_pts_BEY->getzmax()+ecart || Point_Clouds_Import->triangle_plan[i][j].getz_pt3()<Point_Clouds_Import->nuage_pts_BEY->getzmin()-ecart)))
           {

           Point_Clouds_Import->triangle_plan[i][j].setfiltre(true);
           }
         }
}
//------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
void __fastcall TAdaptive_Triangulation::ComboBox12Click(TObject *Sender)
{
		for (int i=0;i<nbre_segments_y;i++)
         {
         for (int j=0;j<nbre_segments_x*2;j++)
         {
          if(Point_Clouds_Import->triangle_plan[i][j].getnum_triangle()==ComboBox12->Text.ToInt())
          {
          Point_Clouds_Import->cible=&Point_Clouds_Import->triangle_plan[i][j];
          break;
          }
        }
}

        
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::CheckBox12Click(TObject *Sender)
{

Point_Clouds_Import->cible=&Point_Clouds_Import->triangle_plan[0][0];
Visualization->DrawObjects();
}



//------- Intégration des triangles filtrés et non vides avec la condition que leurs trois sommets ne soient pas filtrés----------- 

void TAdaptive_Triangulation::integration_triangles()
{
    for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {
       if (Point_Clouds_Import->triangle_plan[i][j].getfiltre()==false) continue;

	  if (!(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true && Point_Clouds_Import->triangle_plan[i][j].getnbre_pts_triangle()>0
      &&  Point_Clouds_Import->triangle_plan[i][j].getp1()->getfiltre()==false && Point_Clouds_Import->triangle_plan[i][j].getp2()->getfiltre()==false
	  &&  Point_Clouds_Import->triangle_plan[i][j].getp3()->getfiltre()==false)) continue;

      Point_Clouds_Import->triangle_plan[i][j].setfiltre(false);

	  if (RadioButton3->Checked)
      {
      if(j % 2 == 0)

      {
      Point_Clouds_Import->triangle_plan[i][j].setz_pt1(Point_Clouds_Import->point_plan[i][j/2].getz_pt_min());
      Point_Clouds_Import->triangle_plan[i][j].setz_pt2(Point_Clouds_Import->point_plan[i+1][j/2+1].getz_pt_min());
      Point_Clouds_Import->triangle_plan[i][j].setz_pt3(Point_Clouds_Import->point_plan[i+1][j/2].getz_pt_min());
      }

      if(j % 2 == 1)
      {

      Point_Clouds_Import->triangle_plan[i][j].setz_pt1(Point_Clouds_Import->point_plan[i][(j-1)/2].getz_pt_min());
      Point_Clouds_Import->triangle_plan[i][j].setz_pt2(Point_Clouds_Import->point_plan[i][((j-1)/2)+1].getz_pt_min());
      Point_Clouds_Import->triangle_plan[i][j].setz_pt3(Point_Clouds_Import->point_plan[i+1][((j-1)/2)+1].getz_pt_min());
      }

     }//if

	   if (RadioButton4->Checked)
      {
      if(j % 2 == 0)

      {
      Point_Clouds_Import->triangle_plan[i][j].setz_pt1(Point_Clouds_Import->point_plan[i][j/2].getz_pt_moy());
      Point_Clouds_Import->triangle_plan[i][j].setz_pt2(Point_Clouds_Import->point_plan[i+1][j/2+1].getz_pt_moy());
      Point_Clouds_Import->triangle_plan[i][j].setz_pt3(Point_Clouds_Import->point_plan[i+1][j/2].getz_pt_moy());
      }

      if(j % 2 == 1)
      {

      Point_Clouds_Import->triangle_plan[i][j].setz_pt1(Point_Clouds_Import->point_plan[i][(j-1)/2].getz_pt_moy());
      Point_Clouds_Import->triangle_plan[i][j].setz_pt2(Point_Clouds_Import->point_plan[i][((j-1)/2)+1].getz_pt_moy());
      Point_Clouds_Import->triangle_plan[i][j].setz_pt3(Point_Clouds_Import->point_plan[i+1][((j-1)/2)+1].getz_pt_moy());
      }

     }//if

	  if (RadioButton5->Checked)
      {
      if(j % 2 == 0)

      {
      Point_Clouds_Import->triangle_plan[i][j].setz_pt1(Point_Clouds_Import->point_plan[i][j/2].getz_pt_max());
      Point_Clouds_Import->triangle_plan[i][j].setz_pt2(Point_Clouds_Import->point_plan[i+1][j/2+1].getz_pt_max());
      Point_Clouds_Import->triangle_plan[i][j].setz_pt3(Point_Clouds_Import->point_plan[i+1][j/2].getz_pt_max());
      }

      if(j % 2 == 1)
      {

      Point_Clouds_Import->triangle_plan[i][j].setz_pt1(Point_Clouds_Import->point_plan[i][(j-1)/2].getz_pt_max());
      Point_Clouds_Import->triangle_plan[i][j].setz_pt2(Point_Clouds_Import->point_plan[i][((j-1)/2)+1].getz_pt_max());
      Point_Clouds_Import->triangle_plan[i][j].setz_pt3(Point_Clouds_Import->point_plan[i+1][((j-1)/2)+1].getz_pt_max());
      }

     }//if
    } //for
  }//for
}


// __________________________déterminer voisins des triangles_____________________________


void TAdaptive_Triangulation ::determination_voisins()
{
//----------------------------cas1----------------------------------------------


for (int j=0;j<nbre_segments_x*2;j++)
      {

      
       if(j % 2 == 0 && j==0)
          {
          Point_Clouds_Import->triangle_plan[0][j].setv1(&Point_Clouds_Import->triangle_plan[0][j+1]);
          Point_Clouds_Import->triangle_plan[0][j].setv2(&Point_Clouds_Import->triangle_plan[1][j+1]);
          Point_Clouds_Import->triangle_plan[0][j].setv3(NULL);
          }

       if(j % 2 == 0 && j!=0)
          {
          Point_Clouds_Import->triangle_plan[0][j].setv1(&Point_Clouds_Import->triangle_plan[0][j+1]);
          Point_Clouds_Import->triangle_plan[0][j].setv2(&Point_Clouds_Import->triangle_plan[1][j+1]);
          Point_Clouds_Import->triangle_plan[0][j].setv3(&Point_Clouds_Import->triangle_plan[0][j-1]);
          }

          if(j % 2 == 1 && j!=Adaptive_Triangulation->nbre_segments_x*2-1)
          {
          Point_Clouds_Import->triangle_plan[0][j].setv1(NULL);
          Point_Clouds_Import->triangle_plan[0][j].setv2(&Point_Clouds_Import->triangle_plan[0][j+1]);
          Point_Clouds_Import->triangle_plan[0][j].setv3(&Point_Clouds_Import->triangle_plan[0][j-1]);
          }

          if(j % 2 == 1 && j==Adaptive_Triangulation->nbre_segments_x*2-1)
          {
		 Point_Clouds_Import->triangle_plan[0][Adaptive_Triangulation->nbre_segments_x*2-1].setv1(NULL);
         Point_Clouds_Import->triangle_plan[0][Adaptive_Triangulation->nbre_segments_x*2-1].setv2(NULL);
         Point_Clouds_Import->triangle_plan[0][Adaptive_Triangulation->nbre_segments_x*2-1].setv3(&Point_Clouds_Import->triangle_plan[0][Adaptive_Triangulation->nbre_segments_x*2-2]);
        }
    }//for j

//----------------------------cas2----------------------------------------------
for (int j=0;j<nbre_segments_x*2;j++)
      {



        if(j % 2 == 0 && j!=0)
         {

          Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j].setv1(&Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j+1]);
          Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j].setv2(NULL);
          Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j].setv3(&Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j-1]);

          }

          if(j % 2 == 0 && j==0)
         {

          Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j].setv1(&Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j+1]);
          Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j].setv2(NULL);
          Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j].setv3(NULL);

          }


          if(j % 2 == 1 && j!=Adaptive_Triangulation->nbre_segments_x*2-1)
          {

          Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j].setv1(&Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-2][j-1]);
          Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j].setv2(&Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j+1]);
          Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j].setv3(&Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j-1]);
          }

           if(j % 2 == 1 && j==Adaptive_Triangulation->nbre_segments_x*2-1)
          {

          Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j].setv1(&Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-2][j-1]);
          Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j].setv2(NULL);
          Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j].setv3(&Point_Clouds_Import->triangle_plan[Adaptive_Triangulation->nbre_segments_y-1][j-1]);
          }



    


 }//for j

 //-------------------------------cas 3---------------------------------------
for (int i=1;i<nbre_segments_y-1;i++)
     {


           Point_Clouds_Import->triangle_plan[i][0].setv1(&Point_Clouds_Import->triangle_plan[i][1]);
           Point_Clouds_Import->triangle_plan[i][0].setv2(&Point_Clouds_Import->triangle_plan[i+1][1]);
           Point_Clouds_Import->triangle_plan[i][0].setv3(NULL);


           Point_Clouds_Import->triangle_plan[i][1].setv1(&Point_Clouds_Import->triangle_plan[i-1][0]);
           Point_Clouds_Import->triangle_plan[i][1].setv2(&Point_Clouds_Import->triangle_plan[i][2]);
           Point_Clouds_Import->triangle_plan[i][1].setv3(&Point_Clouds_Import->triangle_plan[i][0]);




}//for i


 //-------------------------------cas 4---------------------------------------

for (int i=1;i<nbre_segments_y-1;i++)
     {


           Point_Clouds_Import->triangle_plan[i][nbre_segments_x*2-1].setv1(&Point_Clouds_Import->triangle_plan[i-1][nbre_segments_x*2-2]);
           Point_Clouds_Import->triangle_plan[i][nbre_segments_x*2-1].setv2(NULL);
           Point_Clouds_Import->triangle_plan[i][nbre_segments_x*2-1].setv3(&Point_Clouds_Import->triangle_plan[i][nbre_segments_x*2-2]);


           Point_Clouds_Import->triangle_plan[i][nbre_segments_x*2-2].setv1(&Point_Clouds_Import->triangle_plan[i][nbre_segments_x*2-1]);
           Point_Clouds_Import->triangle_plan[i][nbre_segments_x*2-2].setv2(&Point_Clouds_Import->triangle_plan[i+1][nbre_segments_x*2-1]);
           Point_Clouds_Import->triangle_plan[i][nbre_segments_x*2-2].setv3(&Point_Clouds_Import->triangle_plan[i][nbre_segments_x*2-3]);


}//for i


//----------------------------------------cas 5--------------------------------
 for (int i=1;i<nbre_segments_y-1;i++)
     { for (int j=2;j<nbre_segments_x*2-2;j++)
      {

         if(j % 2 == 0)
          {
          Point_Clouds_Import->triangle_plan[i][j].setv1(&Point_Clouds_Import->triangle_plan[i][j+1]);
          Point_Clouds_Import->triangle_plan[i][j].setv2(&Point_Clouds_Import->triangle_plan[i+1][j+1]);
          Point_Clouds_Import->triangle_plan[i][j].setv3(&Point_Clouds_Import->triangle_plan[i][j-1]);
          }

           if(j % 2 == 1)
           {
          Point_Clouds_Import->triangle_plan[i][j].setv1(&Point_Clouds_Import->triangle_plan[i-1][j-1]);
          Point_Clouds_Import->triangle_plan[i][j].setv2(&Point_Clouds_Import->triangle_plan[i][j+1]);
          Point_Clouds_Import->triangle_plan[i][j].setv3(&Point_Clouds_Import->triangle_plan[i][j-1]);
           }

 } //for
}//for
}
//-----------------------------------------------------------------------------
void TAdaptive_Triangulation ::affectation_num_triangle()
{

     int num=0;
        for (int i=0;i<nbre_segments_y;i++)
          for (int j=0;j<nbre_segments_x*2;j++)
            {
			 Point_Clouds_Import->triangle_plan[i][j].setnum_triangle(num);
             num++;
            }
}
//-----------------------------------------------------------------------------
void TAdaptive_Triangulation ::remplissage_Combobox()
{
        ComboBox12->Clear();

        int num=0;
        for (int i=0;i<nbre_segments_y;i++)
          for (int j=0;j<nbre_segments_x*2;j++)
            {
             ComboBox12->Items->Add(num);
             num++;
            }

        ComboBox12->ItemIndex=0;

}

//--------------------------------------------------------------------------
void TAdaptive_Triangulation::affectation_ligne_colonne_pt()
{

for (int i=0;i<nbre_segments_y;i++)
     { for (int j=0;j<nbre_segments_x*2;j++)
      {


      if(j % 2 == 0)

      {

      Point_Clouds_Import->triangle_plan[i][j].getp1()->setlgn_pt_plan(i);
      Point_Clouds_Import->triangle_plan[i][j].getp1()->setcol_pt_plan(j/2);

      Point_Clouds_Import->triangle_plan[i][j].getp2()->setlgn_pt_plan(i+1);
      Point_Clouds_Import->triangle_plan[i][j].getp2()->setcol_pt_plan(j/2+1);

      Point_Clouds_Import->triangle_plan[i][j].getp3()->setlgn_pt_plan(i+1);
      Point_Clouds_Import->triangle_plan[i][j].getp3()->setcol_pt_plan(j/2);


      }

      if(j % 2 == 1)
      {

      Point_Clouds_Import->triangle_plan[i][j].getp1()->setlgn_pt_plan(i);
      Point_Clouds_Import->triangle_plan[i][j].getp1()->setcol_pt_plan((j-1)/2);

      Point_Clouds_Import->triangle_plan[i][j].getp2()->setlgn_pt_plan(i);
      Point_Clouds_Import->triangle_plan[i][j].getp2()->setcol_pt_plan(((j-1)/2)+1);

      Point_Clouds_Import->triangle_plan[i][j].getp3()->setlgn_pt_plan(i+1);
      Point_Clouds_Import->triangle_plan[i][j].getp3()->setcol_pt_plan(((j-1)/2)+1);

      }

     }

 }
}
//---------------------------------------------------------------------------
void __fastcall TAdaptive_Triangulation::Button6Click(TObject *Sender)
{
SaveDialog1->FileName = "";

if (SaveDialog1->Execute())
{
filename_as=SaveDialog1->FileName.c_str();

// if(filename_as==0) StrCopy( filename_as ,"asmaa");

  if(SaveDialog1->FileName != NULL )
   {
//   StrCopy(fichier_as,filename_as );

    Screen->Cursor= crHourGlass;
    save_fichier_STL();
    Screen->Cursor= crDefault;

   }

}

}
//---------------------------------------------------------------------------
void TAdaptive_Triangulation::save_fichier_STL()
{
   ofstream  enrg(SaveDialog1->FileName.c_str());

   enrg.precision(8);
//   enrg.scientific;

     enrg<<"solid surfaces"<<endl;

       for (int i=0;i<Adaptive_Triangulation->nbre_segments_y;i++)
         { for (int j=0;j<Adaptive_Triangulation->nbre_segments_x*2;j++)
         {
           if(Point_Clouds_Import->triangle_plan[i][j].getfiltre()==true)continue;

           double x1=Point_Clouds_Import->triangle_plan[i][j].getp1()->getx_pt();
           double y1=Point_Clouds_Import->triangle_plan[i][j].getp1()->gety_pt();
           double z1=Point_Clouds_Import->triangle_plan[i][j].getz_pt1();

           double x2=Point_Clouds_Import->triangle_plan[i][j].getp2()->getx_pt();
           double y2=Point_Clouds_Import->triangle_plan[i][j].getp2()->gety_pt();
           double z2=Point_Clouds_Import->triangle_plan[i][j].getz_pt2();

           double x3=Point_Clouds_Import->triangle_plan[i][j].getp3()->getx_pt();
           double y3=Point_Clouds_Import->triangle_plan[i][j].getp3()->gety_pt();
           double z3=Point_Clouds_Import->triangle_plan[i][j].getz_pt3();

           double v1x=x2-x1;
           double v1y=y2-y1;
           double v1z=z2-z1;

           double v2x=x3-x1;
           double v2y=y3-y1;
           double v2z=z3-z1;

           double nx=v1y*v2z-v1z*v2y;
           double ny=v1z*v2x-v1x*v2z;
           double nz=v1x*v2y-v1y*v2x;
           
           if(nz<0){nx=-nx; ny=-ny; nz=-nz;}

           double module=sqrt(nx*nx+ny*ny+nz*nz);

           nx=nx/module;
           ny=ny/module;
		   nz=nz/module;

           enrg<<"   facet normal"<<"   "<<nx<<"   "<<ny<<"   "<<nz<<endl;
           enrg<<"      outer loop"<<endl;
           enrg<<"         vertex"<<"   "<<x1<<"   "<<y1<<"   "<<z1<<endl;
           enrg<<"         vertex"<<"   "<<x2<<"   "<<y2<<"   "<<z2<<endl;
           enrg<<"         vertex"<<"   "<<x3<<"   "<<y3<<"   "<<z3<<endl;
           enrg<<"      endloop"<<endl;
           enrg<<"   endfacet"<<endl;

        }
       }

    enrg<<"endsolid";

  enrg.close();  
}
//----------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::Button7Click(TObject *Sender)
{
Adaptive_Triangulation->determiner_pts_proches_sommets_triangle();
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::Button8Click(TObject *Sender)
{
Adaptive_Triangulation->determiner_pts_proches_sommets_triangle();
Adaptive_Triangulation->filtrer_triangles_distances_sommets_triangle();
}
//---------------------------------------------------------------------------

bool TAdaptive_Triangulation::appartence_pt_triangle(triangle_initial *parcour, double x, double y)
{

double x1, y1, x2, y2, x3, y3;
double prec=1;

//point à l'exterieur de l'enveloppe
if(x > (parcour->getxmax_t()+prec) || x < (parcour->getxmin_t()-prec) || y > (parcour->getymax_t()+prec) || y < (parcour->getymin_t()-prec)) return false;

// point à l'intérieur de l'enveloppe
x1=parcour->gets1()->getx_pt();
y1=parcour->gets1()->gety_pt();

x2=parcour->gets2()->getx_pt();
y2=parcour->gets2()->gety_pt();

x3=parcour->gets3()->getx_pt();
y3=parcour->gets3()->gety_pt();

//double produit1=(x2-x1)*(y-y1)-(y2-y1)*(x-x1);
//double produit2=(x3-x1)*(y-y1)-(y3-y1)*(x-x1);
//double produit3=(x3-x2)*(y-y2)-(y3-y2)*(x-x2);

//if(fabs(produit1)<=1e-6 || fabs(produit2)<=1e-6 || fabs(produit3)<=1e-6)return true;

double p1p2_x=x2-x1; double p1p2_y=y2-y1;
double p1p3_x=x3-x1; double p1p3_y=y3-y1;
double p2p3_x=x3-x2; double p2p3_y=y3-y2;
double p1m_x=x-x1;   double p1m_y=y-y1;
double p2m_x=x-x2;   double p2m_y=y-y2;
double p3m_x=x-x3;   double p3m_y=y-y3;

double p1p2vp1m_z=p1p2_x * p1m_y -p1p2_y * p1m_x;//produit vectoriel
double p1mvp1p3_z=p1m_x * p1p3_y -p1m_y * p1p3_x;
double ps1=p1p2vp1m_z * p1mvp1p3_z;//produit scalaire

double p2p1vp2m_z=-p1p2_x * p2m_y -(-p1p2_y)*p2m_x ;
double p2mvp2p3_z=p2m_x * p2p3_y -p2m_y * p2p3_x;
double ps2=p2p1vp2m_z * p2mvp2p3_z;

double p3p1vp3m_z=-p1p3_x * p3m_y -(-p1p3_y)*p3m_x;
double p3mvp3p2_z=p3m_x * (-p2p3_y )-p3m_y *(-p2p3_x);
double ps3= p3p1vp3m_z  * p3mvp3p2_z;

if(fabs(ps1)<=1e-4)ps1=0; //BEY
if(fabs(ps2)<=1e-4)ps2=0; //BEY
if(fabs(ps3)<=1e-4)ps3=0; //BEY

if(ps1>=0 && ps2>=0 && ps3>=0) return true;

return false;
}
//------------------------------------------------------------------
//---------------------------------------------------------------------------
bool triangle_initial::appartence_pt_triangle(double x, double y)
{

double x1, y1, x2, y2, x3, y3;
double prec=1;

//point à l'exterieur de l'enveloppe
if(x > (xmax_t+prec) || x < (xmin_t-prec) || y > (ymax_t+prec) || y < (ymin_t-prec)) return false;

// point à l'intérieur de l'enveloppe
x1=s1->getx_pt();
y1=s1->gety_pt();

x2=s2->getx_pt();
y2=s2->gety_pt();

x3=s3->getx_pt();
y3=s3->gety_pt();

//double produit1=(x2-x1)*(y-y1)-(y2-y1)*(x-x1);
//double produit2=(x3-x1)*(y-y1)-(y3-y1)*(x-x1);
//double produit3=(x3-x2)*(y-y2)-(y3-y2)*(x-x2);

//if(fabs(produit1)<=1e-6 || fabs(produit2)<=1e-6 || fabs(produit3)<=1e-6)return true;

double p1p2_x=x2-x1; double p1p2_y=y2-y1;
double p1p3_x=x3-x1; double p1p3_y=y3-y1;
double p2p3_x=x3-x2; double p2p3_y=y3-y2;
double p1m_x=x-x1;   double p1m_y=y-y1;
double p2m_x=x-x2;   double p2m_y=y-y2;
double p3m_x=x-x3;   double p3m_y=y-y3;

double p1p2vp1m_z=p1p2_x * p1m_y -p1p2_y * p1m_x;//produit vectoriel
double p1mvp1p3_z=p1m_x * p1p3_y -p1m_y * p1p3_x;
double ps1=p1p2vp1m_z * p1mvp1p3_z;//produit scalaire

double p2p1vp2m_z=-p1p2_x * p2m_y -(-p1p2_y)*p2m_x ;
double p2mvp2p3_z=p2m_x * p2p3_y -p2m_y * p2p3_x;
double ps2=p2p1vp2m_z * p2mvp2p3_z;

double p3p1vp3m_z=-p1p3_x * p3m_y -(-p1p3_y)*p3m_x;
double p3mvp3p2_z=p3m_x * (-p2p3_y )-p3m_y *(-p2p3_x);
double ps3= p3p1vp3m_z  * p3mvp3p2_z;

if(fabs(ps1)<=1e-4)ps1=0; //BEY
if(fabs(ps2)<=1e-4)ps2=0; //BEY
if(fabs(ps3)<=1e-4)ps3=0; //BEY

if(ps1>=0 && ps2>=0 && ps3>=0) return true;

//if(seg12==true || seg13==true || seg23==true)return true;

return false;
}
//------------------------------------------------------------------
//---------------------------------------------------------------------------
bool triangle_initial_BEY::appartence_pt_triangle(double x, double y)
{

double x1, y1, x2, y2, x3, y3;
double prec=1;

//point à l'exterieur de l'enveloppe
if(x > (xmax_t+prec) || x < (xmin_t-prec) || y > (ymax_t+prec) || y < (ymin_t-prec)) return false;

// point à l'intérieur de l'enveloppe
x1=s1->getx_pt();
y1=s1->gety_pt();

x2=s2->getx_pt();
y2=s2->gety_pt();

x3=s3->getx_pt();
y3=s3->gety_pt();

//double produit1=(x2-x1)*(y-y1)-(y2-y1)*(x-x1);
//double produit2=(x3-x1)*(y-y1)-(y3-y1)*(x-x1);
//double produit3=(x3-x2)*(y-y2)-(y3-y2)*(x-x2);

//if(fabs(produit1)<=1e-6 || fabs(produit2)<=1e-6 || fabs(produit3)<=1e-6)return true;

double p1p2_x=x2-x1; double p1p2_y=y2-y1;
double p1p3_x=x3-x1; double p1p3_y=y3-y1;
double p2p3_x=x3-x2; double p2p3_y=y3-y2;
double p1m_x=x-x1;   double p1m_y=y-y1;
double p2m_x=x-x2;   double p2m_y=y-y2;
double p3m_x=x-x3;   double p3m_y=y-y3;

double p1p2vp1m_z=p1p2_x * p1m_y -p1p2_y * p1m_x;//produit vectoriel
double p1mvp1p3_z=p1m_x * p1p3_y -p1m_y * p1p3_x;
double ps1=p1p2vp1m_z * p1mvp1p3_z;//produit scalaire

double p2p1vp2m_z=-p1p2_x * p2m_y -(-p1p2_y)*p2m_x ;
double p2mvp2p3_z=p2m_x * p2p3_y -p2m_y * p2p3_x;
double ps2=p2p1vp2m_z * p2mvp2p3_z;

double p3p1vp3m_z=-p1p3_x * p3m_y -(-p1p3_y)*p3m_x;
double p3mvp3p2_z=p3m_x * (-p2p3_y )-p3m_y *(-p2p3_x);
double ps3= p3p1vp3m_z  * p3mvp3p2_z;

if(fabs(ps1)<=1e-4)ps1=0; //BEY
if(fabs(ps2)<=1e-4)ps2=0; //BEY
if(fabs(ps3)<=1e-4)ps3=0; //BEY

if(ps1>=0 && ps2>=0 && ps3>=0) return true;


return false;
}
//------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool triangle_initial_BEY::appartence_pt_segments_triangle(double x, double y)
{

//double x1, y1, x2, y2, x3, y3;
//double prec=1;

//point à l'exterieur de l'enveloppe
if(x > (xmax_t+0.1) || x < (xmin_t-0.1) || y > (ymax_t+0.1) || y < (ymin_t-0.1)) return false;

// point à l'intérieur de l'enveloppe


//double produit1=(x2-x1)*(y-y1)-(y2-y1)*(x-x1);
//double produit2=(x3-x1)*(y-y1)-(y3-y1)*(x-x1);
//double produit3=(x3-x2)*(y-y2)-(y3-y2)*(x-x2);

//if(fabs(produit1)<=1e-6 || fabs(produit2)<=1e-6 || fabs(produit3)<=1e-6)return true;


//double prec1=1e-3;
//P entre P1 et P2

double L12=sqrt(pow(s2->x_pt-s1->x_pt,2)+pow(s2->y_pt-s1->y_pt,2));
double L12_p=sqrt(pow(s2->x_pt-x,2)+pow(s2->y_pt-y,2))+sqrt(pow(s1->x_pt-x,2)+pow(s1->y_pt-y,2));
bool seg12=fabs(L12-L12_p)<=1e-3;


if(seg12==true)return true;    //BEY

//P entre P1 et P3                       _

double L13=sqrt(pow(s3->x_pt-s1->x_pt,2)+pow(s3->y_pt-s1->y_pt,2));
double L13_p=sqrt(pow(s3->x_pt-x,2)+pow(s3->y_pt-y,2))+sqrt(pow(s1->x_pt-x,2)+pow(s1->y_pt-y,2));
bool seg13=fabs(L13-L13_p)<=1e-3;


if(seg13==true)return true;    //BEY

//P entre P2 et P3

double L23=sqrt(pow(s2->x_pt-s3->x_pt,2)+pow(s2->y_pt-s3->y_pt,2));
double L23_p=sqrt(pow(s2->x_pt-x,2)+pow(s2->y_pt-y,2))+sqrt(pow(s3->x_pt-x,2)+pow(s3->y_pt-y,2));
bool seg23=fabs(L23-L23_p)<=1e-3;


if(seg23==true)return true;    //BEY

return false;
}
//------------------------------------------------------------------
//---------------------------------------------------------------------------
bool TAdaptive_Triangulation::appartence_pt_triangle_BEY_NEW(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3, double &xminT, double &yminT, double &xmaxT, double &ymaxT, double x, double y, double p1p2_x, double p1p2_y, double p1p3_x, double p1p3_y, double p2p3_x, double p2p3_y)
{

//double prec=1;
//double prec=0.1;

//point à l'exterieur de l'enveloppe
if(x > (xmaxT+0.1) || x < (xminT-0.1) || y > (ymaxT+0.1) || y < (yminT-0.1)) return false;

// point à l'intérieur de l'enveloppe

//double produit1=(x2-x1)*(y-y1)-(y2-y1)*(x-x1);
//double produit2=(x3-x1)*(y-y1)-(y3-y1)*(x-x1);
//double produit3=(x3-x2)*(y-y2)-(y3-y2)*(x-x2);

//if(fabs(produit1)<=1e-6 || fabs(produit2)<=1e-6 || fabs(produit3)<=1e-6)return true;




//double p1p2_x=x2-x1;
//double p1p2_y=y2-y1;
double p1m_y=y-y1;
double p1m_x=x-x1;
//double p1p3_y=y3-y1;
//double p1p3_x=x3-x1;

double p1p2vp1m_z=p1p2_x * p1m_y -p1p2_y * p1m_x;//produit vectoriel
double p1mvp1p3_z=p1m_x * p1p3_y -p1m_y * p1p3_x;
double ps1=p1p2vp1m_z * p1mvp1p3_z;//produit scalaire

if(fabs(ps1)<=1e-6)ps1=0; //BEY
if(ps1<0)return false; //BEY

double p2m_y=y-y2;
double p2m_x=x-x2;
//double p2p3_y=y3-y2;
//double p2p3_x=x3-x2;

double p2p1vp2m_z=-p1p2_x * p2m_y -(-p1p2_y)*p2m_x ;
double p2mvp2p3_z=p2m_x * p2p3_y -p2m_y * p2p3_x;
double ps2=p2p1vp2m_z * p2mvp2p3_z;

if(fabs(ps2)<=1e-6)ps2=0; //BEY
if(ps2<0)return false; //BEY

double p3m_x=x-x3;
double p3m_y=y-y3;

double p3p1vp3m_z=-p1p3_x * p3m_y -(-p1p3_y)*p3m_x;
double p3mvp3p2_z=p3m_x * (-p2p3_y )-p3m_y *(-p2p3_x);
double ps3= p3p1vp3m_z  * p3mvp3p2_z;

if(fabs(ps3)<=1e-6)ps3=0; //BEY
if(ps3<0)return false; //BEY

return true;


//if(seg12==true || seg13==true || seg23==true)return true;

//return false;
}
//------------------------------------------------------------------

//---------------------------------------------------------------------------
bool TAdaptive_Triangulation::appartence_pt_triangle_BEY(double x1, double y1, double x2, double y2, double x3, double y3, double xminT, double yminT, double xmaxT, double ymaxT, double x, double y)
{

//double prec=1;
double prec=0.1;

//point à l'exterieur de l'enveloppe
if(x > (xmaxT+prec) || x < (xminT-prec) || y > (ymaxT+prec) || y < (yminT-prec)) return false;

// point à l'intérieur de l'enveloppe

//double produit1=(x2-x1)*(y-y1)-(y2-y1)*(x-x1);
//double produit2=(x3-x1)*(y-y1)-(y3-y1)*(x-x1);
//double produit3=(x3-x2)*(y-y2)-(y3-y2)*(x-x2);

//if(fabs(produit1)<=1e-6 || fabs(produit2)<=1e-6 || fabs(produit3)<=1e-6)return true;

double p1p2_x=x2-x1;
double p1p2_y=y2-y1;
double p1m_y=y-y1;
double p1m_x=x-x1;
double p1p3_y=y3-y1;
double p1p3_x=x3-x1;

double p1p2vp1m_z=p1p2_x * p1m_y -p1p2_y * p1m_x;//produit vectoriel
double p1mvp1p3_z=p1m_x * p1p3_y -p1m_y * p1p3_x;
double ps1=p1p2vp1m_z * p1mvp1p3_z;//produit scalaire

if(fabs(ps1)<=1e-6)ps1=0; //BEY
if(ps1<0)return false; //BEY

double p2m_y=y-y2;
double p2m_x=x-x2;
double p2p3_y=y3-y2;
double p2p3_x=x3-x2;

double p2p1vp2m_z=-p1p2_x * p2m_y -(-p1p2_y)*p2m_x ;
double p2mvp2p3_z=p2m_x * p2p3_y -p2m_y * p2p3_x;
double ps2=p2p1vp2m_z * p2mvp2p3_z;

if(fabs(ps2)<=1e-6)ps2=0; //BEY
if(ps2<0)return false; //BEY

double p3m_x=x-x3;
double p3m_y=y-y3;

double p3p1vp3m_z=-p1p3_x * p3m_y -(-p1p3_y)*p3m_x;
double p3mvp3p2_z=p3m_x * (-p2p3_y )-p3m_y *(-p2p3_x);
double ps3= p3p1vp3m_z  * p3mvp3p2_z;

if(fabs(ps3)<=1e-6)ps3=0; //BEY
if(ps3<0)return false; //BEY

return true;


//if(seg12==true || seg13==true || seg23==true)return true;

//return false;
}
//------------------------------------------------------------------


void __fastcall TAdaptive_Triangulation::Button13Click(TObject *Sender)
{
//---------------APPROCHE ADAPTATIVE--------------------

Point_Clouds_Import->liste_triangle_adaptation=new ListTriangle_BEY();

//1)-----------affectation des triangles à la liste des triangles------------
   triangle_initial *parc;

	   for (int i=0;i<nbre_segments_y;i++)
		 for (int j=0;j<nbre_segments_x*2;j++)
          {
		   parc=new triangle_initial();

           parc=&Point_Clouds_Import->triangle_plan[i][j];

		   Point_Clouds_Import->liste_triangle_adaptation->ajouter_Triangle(parc);
     }

//-------------------------------------------------------------------------

}

//-------------------------------------------------------------------------
void __fastcall TAdaptive_Triangulation::Button14Click(TObject *Sender)
{
Screen->Cursor= crHourGlass;
Point_Clouds_Import->liste_triangle_adaptation->determiner_pts_proches_sommets_triangles(Adaptive_Triangulation->triangulation_initiale);
Screen->Cursor= crDefault;

Visualization->DrawObjects();

}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::RadioButton11Click(TObject *Sender)
{
if(Edit32->Text=="")return;

precision_approximation_impose=Edit32->Text.ToDouble();

precision_calcul_approximation=precision_approximation_impose;

}
//---------------------------------------------------------------------------





void __fastcall TAdaptive_Triangulation::CheckBox48Click(TObject *Sender)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::CheckBox49Click(TObject *Sender)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::CheckBox50Click(TObject *Sender)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::Edit22Change(TObject *Sender)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::Edit24Change(TObject *Sender)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::Edit26Change(TObject *Sender)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

//------------------------------------------------------------------------------
//void triangle_initial_BEY::determiner_pt_eloingne(pt_plan *s)
void triangle_initial_BEY::determiner_pt_eloingne(double xx1, double yy1)
{
double dist, dist_max;
double x_loin,y_loin;   //coordonnées du 1er pt le plus éloigné

//double xx1=s->getx_pt();
//double yy1=s->gety_pt();

	dist_max=-1e10;
	//nbre_pts_triangle=liste_pts_triangle_BEY.size();
	for(int i=0; i<nbre_pts_triangle; i++)
	{
//	double x=liste_pts_triangle_BEY[i].p->getx();
//	double y=liste_pts_triangle_BEY[i].p->gety();
	double x=liste_pts_triangle_BEY[i].p->x;
	double y=liste_pts_triangle_BEY[i].p->y;

	dist=/*sqrt*/(pow(xx1-x,2)+ pow(yy1-y,2));

	if(dist>dist_max){dist_max=dist; x_loin=x; y_loin=y;}
	}

	rayon_loin = sqrt(dist_max);

}
//----------------------------------------------------------------------

//---------------------------------------------------------------------------
void triangle_initial_BEY::intersection_deux_segment_BEY(int num_point, double x1,double y1,double x2,double y2, double x3,double y3,double x4,double y4,double & X,double & Y, double & alpha,double & beta)
{

 alpha=-1;
 beta=-1;
 double  deter_glob;

 double d_x,d_y;//,X1,Y1;

 deter_glob=(x2-x1)*(y3-y4)-(y2-y1)*(x3-x4);

 d_x=(x3-x1)*(y3-y4)-(y3-y1)*(x3-x4);
 d_y=(x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);

 if(fabs(deter_glob)>1e-10)
 {


 beta=d_y/deter_glob;
// if(beta<0 && fabs(beta)<=1e-4)beta=0;

 if(beta>=1) beta=0.5; //Intersection avec un coté du triangle: le pt n'appartient pas au segment : forcer le pt à être dans le segment

  X=beta*(x4-x3)+x3;
  Y=beta*(y4-y3)+y3;

	if(num_point==1){x1_inter=X; y1_inter=Y;}
	else if(num_point==2){x2_inter=X; y2_inter=Y;}
 }

}//foction
//----------------------------------------------------------------------------





void __fastcall TAdaptive_Triangulation::Button21Click(TObject *Sender)
{
Screen->Cursor= crHourGlass;
rapport=Adaptive_Triangulation->Edit11->Text.ToDouble()/100.;
Point_Clouds_Import->liste_triangle_adaptation_BEY->determiner_pts_proches_sommets_triangles(true);
Point_Clouds_Import->liste_triangle_adaptation_BEY->traitement_triangles_frontieres_densites_nulles();
Button19Click(Sender);  //calcul du nombre de triangles, de points et de sommets
Point_Clouds_Import->liste_triangle_adaptation_BEY->determiner_parametres_filtration_triangles();
Visualization->DrawObjects();
Screen->Cursor= crDefault;
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::CheckBox52Click(TObject *Sender)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::Button22Click(TObject *Sender)
{
if(!ColorDialog1->Execute())return;

int couleur,rouge,vert,bleu,quotient1,quotient2;
couleur = ColorToRGB(ColorDialog1->Color);
rouge= couleur % 256;
quotient1=couleur / 256;
vert=quotient1 % 256;
quotient2=quotient1 / 256;
bleu=quotient2 % 256;

red_surface=rouge/255.;
green_surface=vert/255.;
blue_surface=bleu/255.;

Visualization->DrawObjects();
}
//---------------------------------------------------------------------------





void __fastcall TAdaptive_Triangulation::CheckBox29Click(TObject *Sender)
{
Point_Clouds_Import->RadioButton1->Checked=true;
Point_Clouds_Import->ComboBox3->ItemIndex=2;

Visualization->DrawObjects();
}
//---------------------------------------------------------------------------



void __fastcall TAdaptive_Triangulation::Button23Click(TObject *Sender)
{
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
if(RadioButton16->Checked)
{
double precision_incrementale;
processing_time_total=0;

int nbre_increments=Edit35->Text.ToInt();
double precision_exigee=Edit32->Text.ToDouble();
double ecart_max=Edit34->Text.ToDouble();

double pas=(ecart_max-precision_exigee)/nbre_increments;

//double ecart_initial=nbre_increments*precision_exigee;

for(int i=1; i<=nbre_increments+20; i++)
{
// precision_incrementale=ecart_initial - (i-1)*precision_exigee;

 precision_incrementale=ecart_max - i*pas;

 if(precision_incrementale<precision_exigee)precision_incrementale=precision_exigee;

 Edit32->Text= precision_incrementale;
 Edit32->Refresh();

 Edit36->Text= i;
 Edit36->Refresh();

 Button18Click(Sender);

 Edit33->Refresh();
 Edit34->Refresh();

 processing_time_total=processing_time_total+processing_time_partiel;

 if(Edit34->Text.ToDouble()<=precision_exigee)break;
}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
if(RadioButton12->Checked)
{
double precision_incrementale;
processing_time_total=0;

int nbre_increments=1000000; //Edit35->Text.ToInt();
double precision_exigee=Edit32->Text.ToDouble();
double precision_initiale_uniforme=Edit34->Text.ToDouble();
double rapport_reduction_erreur=Edit35->Text.ToDouble();

precision_incrementale=precision_initiale_uniforme;
//double ecart_initial=nbre_increments*precision_exigee;

for(int i=1; i<=nbre_increments; i++)
{
// precision_incrementale=ecart_initial - (i-1)*precision_exigee;
 precision_incrementale=precision_incrementale/rapport_reduction_erreur;

 if(precision_incrementale<precision_exigee)precision_incrementale=precision_exigee;

 Edit32->Text= precision_incrementale;
 Edit32->Refresh();

 Edit36->Text= i;
 Edit36->Refresh();

 Button18Click(Sender);

 Edit33->Refresh();
 Edit34->Refresh();

 processing_time_total=processing_time_total+processing_time_partiel;

 if(Edit34->Text.ToDouble()<=precision_exigee)break;
}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

double time=processing_time_total;
double time_s=time/1000;
double time_m=time_s/60;

double temps_m=time_m; //temps de calcul total en minutes

int temps_calcul_j=(int)(temps_m/(24*60));
Edit39->Text=temps_calcul_j;  //nbre de jours

int temps_calcul_h=(int)((temps_m-temps_calcul_j*1440)/60);
Edit40->Text=temps_calcul_h;   //nbre d'heures

double temps_reste=temps_m-(temps_calcul_h*60+temps_calcul_j*1440);
int temps_calcul_m=(int)temps_reste;

Edit41->Text=temps_calcul_m;  //nbre de minutes

double temps_calcul_s=(temps_reste-temps_calcul_m)*60;

Edit42->Text=FormatFloat("0.00",temps_calcul_s);  //nbre de secondes

}
//---------------------------------------------------------------------------


void __fastcall TAdaptive_Triangulation::RadioButton16Click(TObject *Sender)
{
Label34->Caption="Nbre d'incréments";
}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::RadioButton12Click(TObject *Sender)
{
Label34->Caption="Rapport de réduction de l'erreur";
}
//---------------------------------------------------------------------------


void __fastcall TAdaptive_Triangulation::Edit32KeyPress(TObject *Sender, System::WideChar &Key)

{
  AnsiString BEY;
int position;

        switch(Key)
        {
                case'0':  break;
                case'1':  break;
                case'2':  break;
                case'3':  break;
                case'4':  break;
                case'5':  break;
                case'6':  break;
                case'7':  break;
                case'8':  break;
                case'9':  break;
                case'\b':  break;
                case'.':
                {
                BEY=Edit32->Text;
                position=BEY.AnsiPos(".");
				if(position!=0){Key=0x0; break;}
				break;
				}

				default :{Key=0x0; break;}

		}

}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::Button24Click(TObject *Sender)
{

Point_Clouds_Import->liste_triangle_adaptation_BEY->Filtrer_triangles_sans_voisins();

Button19Click(Sender);  //calcul du nombre de triangles, de points et de sommets

Visualization->DrawObjects();

}
//---------------------------------------------------------------------------

void __fastcall TAdaptive_Triangulation::Button25Click(TObject *Sender)
{
Point_Clouds_Import->liste_triangle_adaptation_BEY->modifier_couleurs_triangles();
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

