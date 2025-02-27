//---------------------------------------------------------------------------

#ifndef Point_Clouds_ImportH
#define Point_Clouds_ImportH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <vector>
#include <gl\gl.h>
#include <gl\glu.h>

using namespace std;
bool continuer;

//---------------------------------------------------------
class pt_plan_BEY;
class cellule_sommets_triangles
{
	double xmin_cellule,ymin_cellule;

	vector<int> indice_sommets_triangles;
	int nombre_sommets_triangles;

    float R ,G, B;

public:
	 cellule_sommets_triangles()
	 {
	 indice_sommets_triangles.clear();
	 nombre_sommets_triangles=0;

	 xmin_cellule=ymin_cellule=1e10;

	 R =(float)( (rand() % 255) /255.);
	 B =(float)( (rand() % 255) /255.);
	 G =(float)( (rand() % 255) /255.);
	 }

	 ~cellule_sommets_triangles()
	 {
	 indice_sommets_triangles.clear();
	 }

void initialiser_cellule()
{
	 if(nombre_sommets_triangles==0)return;

	 indice_sommets_triangles.clear();
	 nombre_sommets_triangles=0;
}

void chercher_point(vector <pt_plan_BEY> &sommets_triangles, double x, double y, int &indice_pt);

void setR(float r){ R=r;}
void setB(float b){ B=b;}
void setG(float g){ G=g;}

float getR(){ return R;}
float getB(){ return B;}
float getG(){ return G;}

void ajouter_indice_sommet(int indice){indice_sommets_triangles.push_back(indice);nombre_sommets_triangles++;}

vector<int>  getindice_sommets_triangles(){return indice_sommets_triangles;}
void setindice_sommets_triangles(vector<int> a){indice_sommets_triangles=a;}

void setnombre_sommets_triangles(int l){nombre_sommets_triangles=l;}
int getnombre_sommets_triangles(){return nombre_sommets_triangles;}

	double getxmin_cellule()  {return xmin_cellule;}

	double getymin_cellule()  {return ymin_cellule;}

	void setxmin_cellule(double x1) {xmin_cellule=x1;}

	void setymin_cellule(double y1) {ymin_cellule=y1;}

	void dessiner_cellules();
    void dessiner_liste_points_cellule();
};


//............................................................
class point_nuage

{
 public:

 float x;
 float y;
 float z;

  ~point_nuage()
  {
  }

  point_nuage()
  {
  x=y=z;
  }

  bool inserer_pt_triangle;
  float getx()  {return x;}
  float gety()  {return y;}
  float getz()  {return z;}


  void setx(float x1) {x=x1;}
  void sety(float y1) {y=y1;}
  void setz(float z1) {z=z1;}

	bool getinserer_pt_triangle()  {return  inserer_pt_triangle;}
    void setinserer_pt_triangle(bool x){inserer_pt_triangle=x;}


    bool operator==(point_nuage *h)
	{
     if(fabs(x-h->getx())<=1e-6 && fabs(y-h->gety())<=1e-6 && fabs(z-h->getz())<=1e-6 )
      return true;
      else return false;
    }

} ;
//---------------------------
class Nuage_Pts_BEY
{
public:

int nbre_pts_total;
point_nuage *nuage_pts_BEY;
double xmin,xmax,ymin,ymax,zmin,zmax, L, l, H;

void creer_tableau()
{
nuage_pts_BEY = new point_nuage [nbre_pts_total];
}

~Nuage_Pts_BEY()
{
delete nuage_pts_BEY;
}

void affecter_pt(int i, double x, double y, double z)
{
nuage_pts_BEY[i].setx((float)x);
nuage_pts_BEY[i].sety((float)y);
nuage_pts_BEY[i].setz((float)z);
}

void liberer_nuage_pts_BEY()
{
delete[] nuage_pts_BEY;
}

point_nuage * retourner_adresse_pt(int i){return  &nuage_pts_BEY[i];}
point_nuage retourner_pt(int i){return  nuage_pts_BEY[i];}
void chercher_pptes_nuage_points();
void inverser_nuage_points();

void dessiner_nuage_pts();
void dessiner_brut_min();
};


//............................................................

 class noeud_point_nuage
{
	 int indice_pt_proche;
	 bool ajouter;
	 bool ajouter_dexel;
     bool ignore;
     bool ajouter_limite;

	 point_nuage  *p;
     bool ajouter_horizontal;

	 noeud_point_nuage *suiv;
	 noeud_point_nuage *prec;

	 noeud_point_nuage *suiv_new;
	 noeud_point_nuage *prec_new;

	 noeud_point_nuage *suiv1;
	 noeud_point_nuage *prec1;

	 noeud_point_nuage *suiv_new_n ;
	 noeud_point_nuage *prec_new_n ;

	 noeud_point_nuage *suiv2;
	 noeud_point_nuage *prec2;
	 bool inserer_pt_triangle;
	 AnsiString type;
	 double ecart;

	  public:

	~noeud_point_nuage()
	{
	delete p;
	}

	noeud_point_nuage()
	{
	inserer_pt_triangle=false;

	p=NULL;

	suiv=NULL;
	prec=NULL;

	suiv_new=NULL;
	prec_new=NULL;

	suiv1=NULL;
	prec1=NULL;

	suiv_new_n=NULL;
	prec_new_n=NULL;

	suiv2=NULL;
	prec2=NULL;

	}

	bool getajouter_limite(){return ajouter_limite;}     //non
	void setajouter_limite(bool e){ajouter_limite=e;}

	bool getignore(){return ignore;}        //non
	void setignore(bool e){ignore=e;}

	void setsuiv_new(noeud_point_nuage *h) {suiv_new=h;  }   //non
	noeud_point_nuage * getsuiv_new()        {return suiv_new;}

	void setprec_new(noeud_point_nuage *h) {prec_new=h;  }  //non
	noeud_point_nuage * getprec_new()        {return prec_new;}

	double getecart(){return ecart;}   //non
	void setecart(double e){ecart=e;}

	bool getajouter_horizontal(){return ajouter_horizontal;}   //non
	void setajouter_horizontal(bool e){ajouter_horizontal=e;}

	AnsiString  gettype(){return type;}    //non
	void settype(AnsiString n){type=n;}

	bool getajouter_dexel(){return ajouter_dexel;}   //non
	void setajouter_dexel(bool e){ajouter_dexel=e;}

	bool getajouter(){return ajouter;}    //non
	void setajouter(bool e){ajouter=e;}

	void setsuiv_new_n(noeud_point_nuage *h) {suiv_new_n=h;  }
	noeud_point_nuage * getsuiv_new_n()        {return suiv_new_n;}

	void setprec_new_n(noeud_point_nuage *h) {prec_new_n=h;  }  //non
	noeud_point_nuage * getprec_new_n()        {return prec_new_n;}

	bool getinserer_pt_triangle()  {return  inserer_pt_triangle;}
    void setinserer_pt_triangle(bool x){inserer_pt_triangle=x;}


    int getindice_pt_proche()  {return indice_pt_proche;}
    void setindice_pt_proche(int x1) {indice_pt_proche=x1;}


    void setpoint(point_nuage *point) {p=point;}
    point_nuage * getpoint()           {return p;}

    void setsuiv(noeud_point_nuage *h) {suiv=h;  }
    noeud_point_nuage * getsuiv()        {return suiv;}

    void setprec(noeud_point_nuage *h) {prec=h;}
    noeud_point_nuage * getprec()      {return prec;}


    void setsuiv1(noeud_point_nuage *h) {suiv1=h;  }
    noeud_point_nuage * getsuiv1()        {return suiv1;}

	void setprec1(noeud_point_nuage *h) {prec1=h;}
    noeud_point_nuage * getprec1()      {return prec1;}


    void setsuiv2(noeud_point_nuage *h) {suiv2=h;  }
    noeud_point_nuage * getsuiv2()        {return suiv2;}

    void setprec2(noeud_point_nuage *h) {prec2=h;}
    noeud_point_nuage * getprec2()      {return prec2;}

    noeud_point_nuage & operator=(noeud_point_nuage *h)
     {p=h->p;
      return *this;

     }


   } ;
//------------------------------------------------------------------------------
class point_nuage_BEY
{
public:
	 int indice_pt_proche;
	 int indice_pt_proche_milieu;
	 point_nuage  *p;
	 bool inserer_pt_triangle;

 point_nuage_BEY()
 {
	  indice_pt_proche=0;
	  indice_pt_proche_milieu=0;
	  inserer_pt_triangle=false;
 }

};
 //............................................................

 class noeud_point_nuage_BEY
{
	 int indice_pt_proche;
	 int indice_pt_proche_milieu;

	 point_nuage  *p;

	 noeud_point_nuage_BEY *suiv;
	 noeud_point_nuage_BEY *suiv1;
	 noeud_point_nuage_BEY *suiv2;

	 bool inserer_pt_triangle;

	  public:

	  ~noeud_point_nuage_BEY()
	  {
	  delete p;
	  }

	  noeud_point_nuage_BEY()
	  {
	  inserer_pt_triangle=false;

	  p=NULL;
	  suiv=NULL;
	  suiv1=NULL;
	  suiv2=NULL;
	  }

	bool getinserer_pt_triangle()  {return  inserer_pt_triangle;}
	void setinserer_pt_triangle(bool x){inserer_pt_triangle=x;}

	int getindice_pt_proche()  {return indice_pt_proche;}
	void setindice_pt_proche(int x1) {indice_pt_proche=x1;}

	int getindice_pt_proche_milieu()  {return indice_pt_proche_milieu;}
	void setindice_pt_proche_milieu(int x1) {indice_pt_proche_milieu=x1;}

	void setpoint(point_nuage *point) {p=point;}
	point_nuage * getpoint()           {return p;}

	void setsuiv(noeud_point_nuage_BEY *h) {suiv=h;  }
	noeud_point_nuage_BEY * getsuiv()        {return suiv;}

	void setsuiv1(noeud_point_nuage_BEY *h) {suiv1=h;  }
	noeud_point_nuage_BEY * getsuiv1()        {return suiv1;}

	void setsuiv2(noeud_point_nuage_BEY *h) {suiv2=h;  }
	noeud_point_nuage_BEY * getsuiv2()        {return suiv2;}

	noeud_point_nuage_BEY & operator=(noeud_point_nuage_BEY *h)
	 {p=h->p;
	  return *this;
	 }

} ;

 //............................................................
class liste_point
{
 int nbre_pt;
 bool retenir;

 int nbre_pts_proche_p1;
 int nbre_pts_proche_p2;
 int nbre_pts_proche_p3;

 double densite_p1, densite_p2, densite_p3;
 double xg, yg, zg;

 noeud_point_nuage *debut;
 noeud_point_nuage *fin;

 double xmin,xmax,ymin,ymax,zmin,zmax, L, l, H;
 double nx,ny,nz;

 public:

	~liste_point()
   {
	noeud_point_nuage *prev=debut;
	while (debut!=NULL)
	{
	   debut=debut->getsuiv();
	   delete prev;
	   prev=debut;
	}
   }

   liste_point()
   {
	 debut=NULL;
	 fin=NULL;
	 nbre_pt=0;
   }
   void chercher_pptes_nuage_points();
   void chercher_pptes_nuage_pointsnew();

    bool getretenir()  {return retenir;}
    void setretenir(bool x1) {retenir=x1;}

   liste_point &  ajouter_element_new(noeud_point_nuage *);
   liste_point &  ajouter_element_new2(noeud_point_nuage *);

	double getnx()  {return nx;}
	void setnx(double x1) {nx=x1;}

    double getny()  {return ny;}
    void setny(double x1) {ny=x1;}

    double getnz()  {return nz;}
    void setnz(double x1) {nz=x1;}


  double getxg()  {return xg;}
  void setxg(double z1) {xg=z1;}

  double getyg()  {return yg;}
  void setyg(double z1) {yg=z1;}

  double getzg()  {return zg;}
  void setzg(double z1) {zg=z1;}

	void initialiser(){ debut=NULL;   fin=NULL;}


    double getdensite_p1()  {return densite_p1;}
    void setdensite_p1(double x1) {densite_p1=x1;}

    double getdensite_p2()  {return densite_p2;}
    void setdensite_p2(double x1) {densite_p2=x1;}

    double getdensite_p3()  {return densite_p3;}
    void setdensite_p3(double x1) {densite_p3=x1;}

    int getnbre_pts_proche_p1()  {return nbre_pts_proche_p1;}
    void setnbre_pts_proche_p1(int x1) {nbre_pts_proche_p1=x1;}

    int getnbre_pts_proche_p2()  {return nbre_pts_proche_p2;}
    void setnbre_pts_proche_p2(int x1) {nbre_pts_proche_p2=x1;}

    int getnbre_pts_proche_p3()  {return nbre_pts_proche_p3;}
    void setnbre_pts_proche_p3(int x1) {nbre_pts_proche_p3=x1;}

    int getnbre_pt()  {return nbre_pt;}
    void setnbre_pt(int x1) {nbre_pt=x1;}

   noeud_point_nuage * getfin(){return fin;}
   void setfin(noeud_point_nuage *f){fin=f;}

   noeud_point_nuage * getdebut() {return debut;}
   void setdebut(noeud_point_nuage *f){debut=f;}

   liste_point &  ajouter_element(noeud_point_nuage *);

   liste_point &  inserer_pts_cellule(noeud_point_nuage *);

   liste_point &  inserer_pts_triangle(noeud_point_nuage *);

   liste_point & operator=(liste_point *A)
    {
      debut=A->getdebut();
      return *this;
    }


    double getxmin()  {return xmin;}
    double getxmax()  {return xmax;}

    double getymin()  {return ymin;}
    double getymax()  {return ymax;}

    double getzmax()  {return zmax;}
    double getzmin()  {return zmin;}

     double getL()  {return L;}
     double getl()  {return l;}
     double getH()  {return H;}

     void setxmin(double x1) {xmin=x1;}
     void setxmax(double x2) {xmax=x2;}

     void setymin(double y1) {ymin=y1;}
     void setymax(double y2) {ymax=y2;}

     void setzmin(double z1) {zmin=z1;}
     void setzmax(double z2) {zmax=z2;}

     void setL(double zz)  {L=zz;}
     void setl(double zx) {l=zx;}
     void setH(double zy) {H=zy;}

    void dessiner_liste_point();
    void dessiner_brut_min();

    void inverser_nuage_points();


};
 //............................................................
class liste_point_BEY
{
 int nbre_pt;

 double xg, yg, zg;
 double xmin,xmax,ymin,ymax,zmin,zmax;

 noeud_point_nuage_BEY *debut;
 noeud_point_nuage_BEY *fin;


 public:

   ~liste_point_BEY()
   {
   }

   liste_point_BEY()
   {
	 debut=NULL;
	 fin=NULL;
	 nbre_pt=0;
   }

   void effacer_liste();

   void chercher_pptes_nuage_points();

   liste_point_BEY &  ajouter_element_new(noeud_point_nuage_BEY *);
   liste_point_BEY &  ajouter_element_new2(noeud_point_nuage_BEY *);

  double getxg()  {return xg;}
  void setxg(double z1) {xg=z1;}

  double getyg()  {return yg;}
  void setyg(double z1) {yg=z1;}

  double getzg()  {return zg;}
  void setzg(double z1) {zg=z1;}

	void initialiser(){ debut=NULL;   fin=NULL;}

	int getnbre_pt()  {return nbre_pt;}
	void setnbre_pt(int x1) {nbre_pt=x1;}

   noeud_point_nuage_BEY * getfin(){return fin;}
   void setfin(noeud_point_nuage_BEY *f){fin=f;}

   noeud_point_nuage_BEY * getdebut() {return debut;}
   void setdebut(noeud_point_nuage_BEY *f){debut=f;}

   liste_point_BEY &  ajouter_element(noeud_point_nuage_BEY *);

   liste_point_BEY &  inserer_pts_cellule(noeud_point_nuage_BEY *);

   liste_point_BEY &  inserer_pts_triangle(noeud_point_nuage_BEY *);

   liste_point_BEY & operator=(liste_point_BEY *A)
	{
	  debut=A->getdebut();
	  return *this;
	}


	double getxmin()  {return xmin;}
	double getxmax()  {return xmax;}

	double getymin()  {return ymin;}
	double getymax()  {return ymax;}

	double getzmax()  {return zmax;}
	double getzmin()  {return zmin;}

	double getL()  {return xmax-xmin;}
	double getl()  {return ymax-ymin;}
	double getH()  {return zmax-zmin;}

	void setxmin(double x1) {xmin=x1;}
	void setxmax(double x2) {xmax=x2;}

	void setymin(double y1) {ymin=y1;}
	void setymax(double y2) {ymax=y2;}

	void setzmin(double z1) {zmin=z1;}
	void setzmax(double z2) {zmax=z2;}

	void dessiner_liste_point();
	void dessiner_brut_min();

	void inverser_nuage_points();
};

//------------------------------------------------------------------------------
class noeud_liste_point
{

liste_point *L;

noeud_liste_point *suiv_new2;
noeud_liste_point *prec_new2;

noeud_liste_point *suiv_cel;
noeud_liste_point *prec_cel;
int indice;

bool L_modifier;

bool traitement;

public:

   ~noeud_liste_point()
   {
   delete L;
   }

   noeud_liste_point()
   {
	 L=new liste_point();
	 suiv_new2=NULL;
	 prec_new2=NULL;

	 suiv_cel=NULL;
	 prec_cel=NULL;

     L_modifier=false;
     indice=0;
     traitement=false;
   }

liste_point* getL(){return L;}
void setL(liste_point* l){L=l;}

int  getindice(){return indice;}
void setindice(int l){indice=l;}

 noeud_liste_point* getsuiv_new2(){return suiv_new2;}
 void setsuiv_new2(noeud_liste_point *f){suiv_new2=f;}

 noeud_liste_point* getprec_new2(){return prec_new2;}
 void setprec_new2(noeud_liste_point *f){prec_new2=f;}


 noeud_liste_point* getsuiv_cel(){return suiv_cel;}
 void setsuiv_cel(noeud_liste_point *f){suiv_cel=f;}

 noeud_liste_point* getprec_cel(){return prec_new2;}
 void setprec_cel(noeud_liste_point *f){prec_cel=f;}


bool gettraitement(){return traitement;}
void settraitement(bool a){traitement=a;}

bool getL_modifier(){return L_modifier;}
void setL_modifier(bool a){L_modifier=a;}

};

 //............................................................
class liste_de_liste_point
{
 int nbre_pt;

 noeud_liste_point *Debut;
 noeud_liste_point *Fin;
 public:

   ~liste_de_liste_point()
   {
   }

   liste_de_liste_point()
   {
     Debut=NULL;
     Fin=NULL;
   }
    void initialiser(){ Debut=NULL;   Fin=NULL;}


    int getnbre_pt()  {return nbre_pt;}
    void setnbre_pt(int x1) {nbre_pt=x1;}

   noeud_liste_point * getFin(){return Fin;}
   void setFin(noeud_liste_point *f){Fin=f;}

   noeud_liste_point * getDebut() {return Debut;}
   void setDebut(noeud_liste_point *f){Debut=f;}
   liste_de_liste_point & ajouter_element_liste_de_liste(noeud_liste_point *);
   liste_de_liste_point & ajouter_liste_poroi_cel(noeud_liste_point *);

};
//-----------------------------------------------------------------------
class fichier_texte
{
  AnsiString nom_f;
		bool syntaxe;

   public:
		fichier_texte()
		{
		}

		~fichier_texte()
		{
		}

		void verifier_fichier(AnsiString fichier);
        void lecture_affectation_fichier();

        AnsiString getnom_f()
            {return nom_f;}
        void setnom_f(AnsiString x1)
            {nom_f=x1;}

        bool getsyntaxe()
            {return syntaxe;}
        void setsyntaxe(bool x1)
            {syntaxe=x1;}

};


//---------------------------------------------------------
class cellule
{

	double xmax_cellule,xmin_cellule;
	double ymax_cellule,ymin_cellule;
	double zmax_cellule,zmin_cellule;

	liste_point *liste_pts_cellule;
	liste_point_BEY *liste_pts_cellule_BEY;


	liste_de_liste_point *liste_paroi_cellule;
	int nombre_liste_point_paroi;
	int indice_max;

public:
	cellule()
	 {
	 liste_pts_cellule_BEY_vector.clear();
	 nbre_pts_cellule=0;

	 xmax_cellule=ymax_cellule=zmax_cellule=-1e10;
	 xmin_cellule=ymin_cellule=zmin_cellule=1e10;

	 liste_pts_cellule=new liste_point();
	 liste_pts_cellule_BEY=new liste_point_BEY();

	 liste_paroi_cellule=NULL;
	 }

	~cellule()
	 {
	 liste_pts_cellule_BEY_vector.clear();
	 nbre_pts_cellule=0;

	 delete liste_pts_cellule;
	 delete liste_pts_cellule_BEY;
	 delete liste_paroi_cellule;
	 }


void ajouter_pt(point_nuage *p){liste_pts_cellule_BEY_vector.push_back(p);nbre_pts_cellule++;}
int  getindice_max(){return indice_max;}
void setindice_max(int l){indice_max=l;}

liste_de_liste_point * getliste_paroi_cellule(){return  liste_paroi_cellule;}
void setliste_paroi_cellule( liste_de_liste_point *a){liste_paroi_cellule=a;}

void initialiser_appartenace_pts()
{
	for(int i=0; i<nbre_pts_cellule; i++)
	{
     liste_pts_cellule_BEY_vector[i]->inserer_pt_triangle=false;
	}
}

	vector<point_nuage*>  liste_pts_cellule_BEY_vector;
	int nbre_pts_cellule;

	int getnombre_liste_point_paroi()  {return nombre_liste_point_paroi;}
	void setnombre_liste_point_paroi(int e)  {nombre_liste_point_paroi=e;}


	double getxmin_cellule()  {return xmin_cellule;}
	double getxmax_cellule()  {return xmax_cellule;}

    double getymin_cellule()  {return ymin_cellule;}
    double getymax_cellule() {return ymax_cellule;}

    double getzmin_cellule()  {return zmin_cellule;}
    double getzmax_cellule()  {return zmax_cellule;}


    void setxmin_cellule(double x1) {xmin_cellule=x1;}
    void setxmax_cellule(double x2) {xmax_cellule=x2;}

    void setymin_cellule(double y1) {ymin_cellule=y1;}
    void setymax_cellule(double y2) {ymax_cellule=y2;}

	void setzmin_cellule(double z1) {zmin_cellule=z1;}
	void setzmax_cellule(double z2) {zmax_cellule=z2;}

	liste_point_BEY *getliste_pts_cellule_BEY()       {return liste_pts_cellule_BEY;}
	void setliste_pts_cellule_BEY(liste_point_BEY * x1) {liste_pts_cellule_BEY=x1;}

	liste_point *getliste_pts_cellule()       {return liste_pts_cellule;}
	void setliste_pts_cellule(liste_point * x1) {liste_pts_cellule=x1;}


    void dessiner_cellules();
    void dessiner_liste_points_cellule();

   };
//---------------------------------------------------------
class cellule_BEY
{

	double xmax_cellule,xmin_cellule;
	double ymax_cellule,ymin_cellule;
	double zmax_cellule,zmin_cellule;

	int indice_max;

public:
	cellule_BEY()
	 {
	 liste_pts_cellule_BEY_vector.clear();
	 nbre_pts_cellule=0;

	 xmax_cellule=ymax_cellule=zmax_cellule=-1e10;
	 xmin_cellule=ymin_cellule=zmin_cellule=1e10;
	 }

	~cellule_BEY()
	 {
	 liste_pts_cellule_BEY_vector.clear();
	 nbre_pts_cellule=0;
	 }


void ajouter_pt(point_nuage *p){liste_pts_cellule_BEY_vector.push_back(p);nbre_pts_cellule++;}
int  getindice_max(){return indice_max;}
void setindice_max(int l){indice_max=l;}

void initialiser_appartenace_pts()
{
	for(int i=0; i<nbre_pts_cellule; i++)
	{
     liste_pts_cellule_BEY_vector[i]->inserer_pt_triangle=false;
	}
}

	vector<point_nuage*>  liste_pts_cellule_BEY_vector;
	int nbre_pts_cellule;

	double getxmin_cellule()  {return xmin_cellule;}
	double getxmax_cellule()  {return xmax_cellule;}

    double getymin_cellule()  {return ymin_cellule;}
    double getymax_cellule() {return ymax_cellule;}

    double getzmin_cellule()  {return zmin_cellule;}
    double getzmax_cellule()  {return zmax_cellule;}


    void setxmin_cellule(double x1) {xmin_cellule=x1;}
    void setxmax_cellule(double x2) {xmax_cellule=x2;}

    void setymin_cellule(double y1) {ymin_cellule=y1;}
    void setymax_cellule(double y2) {ymax_cellule=y2;}

	void setzmin_cellule(double z1) {zmin_cellule=z1;}
	void setzmax_cellule(double z2) {zmax_cellule=z2;}

    void dessiner_cellules();
    void dessiner_liste_points_cellule();

   };

//---------------------------------------------------------
class cellule_sommets_BEY
{

	double xmax_cellule,xmin_cellule;
	double ymax_cellule,ymin_cellule;
	double zmax_cellule,zmin_cellule;

public:
	cellule_sommets_BEY()
	 {
	 liste_pts_cellule_BEY_vector.clear();
	 nbre_pts_cellule=0;
	 }

	~cellule_sommets_BEY()
	 {
	 liste_pts_cellule_BEY_vector.clear();
	 nbre_pts_cellule=0;
	 }


void ajouter_pt(point_nuage p){liste_pts_cellule_BEY_vector.push_back(p);nbre_pts_cellule++;}

	vector<point_nuage>  liste_pts_cellule_BEY_vector;
	int nbre_pts_cellule;

	double getxmin_cellule()  {return xmin_cellule;}
	double getxmax_cellule()  {return xmax_cellule;}

    double getymin_cellule()  {return ymin_cellule;}
    double getymax_cellule() {return ymax_cellule;}

    void setxmin_cellule(double x1) {xmin_cellule=x1;}
    void setxmax_cellule(double x2) {xmax_cellule=x2;}

    void setymin_cellule(double y1) {ymin_cellule=y1;}
    void setymax_cellule(double y2) {ymax_cellule=y2;}

    double getzmin_cellule()  {return zmin_cellule;}
    double getzmax_cellule()  {return zmax_cellule;}

	void setzmin_cellule(double z1) {zmin_cellule=z1;}
	void setzmax_cellule(double z2) {zmax_cellule=z2;}

	void dessiner_cellules();
	void dessiner_liste_points_cellule();
   };


//----------------------------------------------------------
class pt_plan
{
  public :

 double x_pt,y_pt;
 double z_pt_max,z_pt_min,z_pt_moy,z ;
 double nx_pt,ny_pt,nz_pt;

 bool filtre;
 AnsiString type_pt_plan;
 int lgn_pt_plan,col_pt_plan;
 int numero_pt;

  bool depart;

  bool sommet_modifie;
  pt_plan()
  {
  filtre=depart=false; type_pt_plan="rien" ;nx_pt=ny_pt=nz_pt=0;
  }

  ~pt_plan()
  {
  type_pt_plan=" ";
  }

  void affecter_coordonnees(double x1, double y1, double z1)  {x_pt=x1; y_pt=y1;  z =z1;}
  int getnumero_pt()  {return numero_pt;}
  void setnumero_pt(int x1) {numero_pt=x1;}


  int getlgn_pt_plan()  {return lgn_pt_plan;}
  void setlgn_pt_plan(int x1) {lgn_pt_plan=x1;}

  int getcol_pt_plan()  {return col_pt_plan;}
  void setcol_pt_plan(int x1) {col_pt_plan=x1;}


  bool getfiltre()  {return  filtre;}
  void setfiltre(bool x2)  { filtre=x2;}

  double getx_pt()  {return x_pt;}
  double gety_pt()  {return y_pt;}


   bool getdepart()  {return  depart;}
   void setdepart(bool x2)  { depart=x2;}

  void setx_pt(double x1) {x_pt=x1;}
  void sety_pt(double y1) {y_pt=y1;}

  double getz_pt_max()  {return z_pt_max;}
  void setz_pt_max(double z1) {z_pt_max=z1;}

  double getz_pt_min()  {return z_pt_min;}
  void setz_pt_min(double z1) {z_pt_min=z1;}

  double getz_pt_moy()  {return z_pt_moy;}
  void setz_pt_moy(double z1) {z_pt_moy=z1;}

  void setnx_pt(double z1) {nx_pt=z1;}
  double getnx_pt()  {return nx_pt;}

  void setny_pt(double z1) {ny_pt=z1;}
  double getny_pt()  {return ny_pt;}

  void setnz_pt(double z1) {nz_pt=z1;}
  double getnz_pt()  {return nz_pt;}

  void setz(double z1) { z =z1;}
  double getz()  {return  z;}

  AnsiString gettype_pt_plan() {return type_pt_plan;}
  void settype_pt_plan(AnsiString x1) {type_pt_plan=x1;}
};
//----------------------------------------------------------
class pt_plan_BEY

{

 double x_pt,y_pt;
 double z_pt_max,z_pt_min,z_pt_moy;

  public :
  int nbre_pts_commun;

  ~pt_plan_BEY()
  {
  }
  pt_plan_BEY(){nbre_pts_commun=0;z_pt_moy=0;}
  void ajouter_pt_commun(){nbre_pts_commun++;}
  void ajouter_somme_moy(double a){z_pt_moy=z_pt_moy+a;}
  void calculer_Z_moy(){z_pt_moy=z_pt_moy/nbre_pts_commun;}
  void affectation_initiale(double x, double y, double z)
  {
  x_pt=x;
  y_pt=y;
  z_pt_max=z;
  z_pt_min=z;
  z_pt_moy=z_pt_moy+z;
  nbre_pts_commun++;
  }

  void affectation_intermediaire(double z)
  {
  z_pt_max=max(z_pt_max, z);
  z_pt_min=min(z_pt_min, z);
  z_pt_moy=z_pt_moy+z;
  nbre_pts_commun++;
  }

  double getx_pt()  {return x_pt;}
  double gety_pt()  {return y_pt;}

  void setx_pt(double x1) {x_pt=x1;}
  void sety_pt(double y1) {y_pt=y1;}

  double getz_pt_max()  {return z_pt_max;}
  void setz_pt_max(double z1) {z_pt_max=z1;}

  double getz_pt_min()  {return z_pt_min;}
  void setz_pt_min(double z1) {z_pt_min=z1;}

  double getz_pt_moy()  {return z_pt_moy;}
  void setz_pt_moy(double z1) {z_pt_moy=z1;}
};
//...........................................................


//-----------------------------------

class noeud_triangle_initial;
class liste_triangle_initial;
class triangle_initial;
class liste_noeud_trajet;
//-----------------------------------

 class noeud_point_plan
{

   AnsiString type;
   AnsiString type_pt;
   pt_plan  *point;
   int lgn_pt,col_pt;

   bool insere;
   bool fin_liste;

  double x_st,y_st,z_st;
  double nx_st,ny_st,nz_st;

	noeud_point_plan *suiv3;
	noeud_point_plan *prec3;

	noeud_point_plan *suiv4;
	noeud_point_plan *prec4;

	liste_triangle_initial   *liste_triangles_trier;

	liste_noeud_trajet *liste_trajet_pt_stat;


  public:

	~noeud_point_plan()
	{
	delete point;
	}

	noeud_point_plan()
	{
	point=NULL;
	insere=fin_liste=false;

	type_pt="non stat";
	type="rien";

	suiv3=prec3=suiv4=prec4=NULL;
	point= new pt_plan;
   liste_triangles_trier=NULL;
   liste_trajet_pt_stat=NULL;
   }


  void setx_st(double x1) {x_st=x1;}
  void sety_st(double y1) {y_st=y1;}
  void setz_st(double z1) {z_st=z1;}

  void setnx_st(double x1) {nx_st=x1;}
  void setny_st(double y1) {ny_st=y1;}
  void setnz_st(double z1) {nz_st=z1;}


  double getx_st()  {return x_st;}
  double gety_st()  {return y_st;}
  double getz_st()  {return z_st;}

  double getnx_st()  {return nx_st;}
  double getny_st()  {return ny_st;}
  double getnz_st()  {return nz_st;}

	bool getinsere()  {return  insere;}
	void setinsere(bool x2)  { insere=x2;}

	bool getfin_liste()  {return  fin_liste;}
	void setfin_liste(bool x2)  { fin_liste=x2;}

	void setpoint(pt_plan *pt) {point=pt;}
	pt_plan * getpoint()          {return point;}

//________________________________________________________
    void setsuiv3(noeud_point_plan *h) {suiv3=h;  }
    noeud_point_plan * getsuiv3(){return suiv3;}

    void setprec3( noeud_point_plan *h) {prec3=h;}
    noeud_point_plan * getprec3()      {return prec3;}


    void setsuiv4(noeud_point_plan *h) {suiv4=h;  }
    noeud_point_plan * getsuiv4(){return suiv4;}

    void setprec4( noeud_point_plan *h) {prec4=h;}
    noeud_point_plan * getprec4()      {return prec4;}

//_________________________________________________________________

    int getlgn_pt()  {return lgn_pt;}
    void setlgn_pt(int x1) {lgn_pt=x1;}

    int getcol_pt()  {return col_pt;}
    void setcol_pt(int x1) {col_pt=x1;}

    AnsiString gettype() {return type;}
    void settype(AnsiString x1) {type=x1;}

    AnsiString gettype_pt() {return type_pt;}
    void settype_pt(AnsiString x1) {type_pt=x1;}

    liste_triangle_initial  *getliste_triangles_trier(){return liste_triangles_trier;}
    void setliste_triangles_trier(liste_triangle_initial  * x1) {liste_triangles_trier=x1;}

    liste_noeud_trajet  *getliste_trajet_pt_stat(){return liste_trajet_pt_stat;}
    void setliste_trajet_pt_stat(liste_noeud_trajet  * x1) {liste_trajet_pt_stat=x1;}
} ;

//............................................................
class liste_point_plan
{
noeud_point_plan *debut_p;
noeud_point_plan *fin_p;
int nbre_pt;
int nbre_pt_stat;

 public:

   liste_point_plan()
   {
     debut_p=NULL;
     fin_p=NULL;
     nbre_pt=0;
     nbre_pt_stat=0;
   }

   ~liste_point_plan()
   {
	 delete debut_p;
	 delete fin_p;
   }

	int getnbre_pt()  {return nbre_pt;}
    void setnbre_pt(int x1) {nbre_pt=x1;}

   noeud_point_plan * getfin_p(){return fin_p;}
   void setfin_p(noeud_point_plan *f){fin_p=f;}

   noeud_point_plan * getdebut_p() {return debut_p;}
   void setdebut_p(noeud_point_plan *f){debut_p=f;}

   int getnbre_pt_stat()  {return nbre_pt_stat;}
   void setnbre_pt_stat(int x1) {nbre_pt_stat=x1;}

   liste_point_plan &  inserer_pts_plan(noeud_point_plan *);
   liste_point_plan &  inserer_pts_plan_trier(noeud_point_plan *);

   liste_point_plan & operator=(   liste_point_plan *A)

	{
	  debut_p=A->getdebut_p();
	  return *this;
	}

	  void permuter_point_suiv_z( noeud_point_plan *p1, noeud_point_plan *p2);
	  void permuter_points_stationnaire( noeud_point_plan *p1, noeud_point_plan *p2);
 };

//________________________________________________________________

class triangle_initial
{
  int num_triangle;
  int nbre_pts_triangle;
  int nbre_pts_proche_p1, nbre_pts_proche_p2, nbre_pts_proche_p3;
  bool nouveau_triangle;
  bool calcul_voisins;
  bool filtre;
  bool calcul_pts_proche;
  bool trois_sommets_non_nuls;

  liste_point_BEY *liste_pts_triangle;

  int nbre_pts_proche_m1, nbre_pts_proche_m2, nbre_pts_proche_m3;

  double densite_p1, densite_p2, densite_p3;
  double densite_m1;
  double densite_m2;
  double densite_m3;
  double R ,G, B;
  double xc, yc, zc, Rc;
  double xg, yg, zg;
  double nx,ny,nz;

  int seg12, seg32, seg13;

  bool approximation_plan;
  bool passage_numerotation;


  pt_plan *p1, *p2, *p3;

  pt_plan *s1, *s2, *s3;

  triangle_initial *suiv;
  triangle_initial *prec;

  bool eliminer_sommet;

  triangle_initial *v1, *v2, *v3;
  AnsiString type_tri;
  bool frontiere;
  bool inserer_tri ;
  bool passage;

  double xmax_t,ymax_t,zmax_t,xmin_t,ymin_t,zmin_t;
  double z_pt1,z_pt2,z_pt3;

  double x_loin,y_loin;
  double rayon_loin;

  double x_proche,y_proche;
  double rayon_proche;

  double x1_inter, y1_inter;
  double x2_inter, y2_inter;

  double a_plan,b_plan,c_plan;

  double dist_pt_plan_max;
  double dist_pt_plan_min;
  double aire_tr;

  public:
  ~triangle_initial()
  {
  liste_pts_triangle_BEY.clear();
  delete liste_pts_triangle;

  delete p1, p2, p3;

  delete s1, s2, s3;
  }

  triangle_initial()
  {
  nbre_pts_triangle=0;

  nbre_pts_proche_p1=0;
  nbre_pts_proche_p2=0;
  nbre_pts_proche_p3=0;

  nbre_pts_proche_m1=0;
  nbre_pts_proche_m2=0;
  nbre_pts_proche_m3=0;

  densite_p1=0;
  densite_p2=0;
  densite_p3=0;

  densite_m1=0;
  densite_m2=0;
  densite_m3=0;

  seg12=0;
  seg13=0;
  seg32=0;

  approximation_plan=false;
  nouveau_triangle=true;
  calcul_voisins=false;
  filtre=false;
  calcul_pts_proche=false;

  dist_pt_plan_max=0;

  passage=false;

  p1=NULL;
  p2=NULL;
  p3=NULL;

  s1=new pt_plan();
  s2=new pt_plan();
  s3=new pt_plan();

  v1=NULL;
  v2=NULL;
  v3=NULL;

  liste_pts_triangle =new liste_point_BEY();
  liste_pts_triangle_BEY.clear();

  nbre_pts_triangle=0;
  filtre=inserer_tri=frontiere=eliminer_sommet=false;
  type_tri="rien";

  z_pt1=z_pt2=z_pt3=0;

  affecter_couleur();
  }

	void intialiser_liste_pts_triangle_BEY()
	{
	liste_pts_triangle_BEY.clear();
	nbre_pts_triangle=0;
	}

	void intialiser()
	{
	liste_pts_triangle =new liste_point_BEY();
	liste_pts_triangle_BEY.clear();
	nbre_pts_triangle=0;

	nbre_pts_proche_p1=0;
	nbre_pts_proche_p2=0;
	nbre_pts_proche_p3=0;

	nbre_pts_proche_m1=0;
	nbre_pts_proche_m2=0;
	nbre_pts_proche_m3=0;

	densite_p1=0;
	densite_p2=0;
	densite_p3=0;

	densite_m1=0;
	densite_m2=0;
	densite_m3=0;

	seg12=0;
	seg13=0;
	seg32=0;

	filtre=false;
	eliminer_sommet=false;
	calcul_pts_proche=false;
	calcul_voisins=false;
	nouveau_triangle=true;

	  dist_pt_plan_max=0;

	  passage=false;

	  filtre=inserer_tri=frontiere=eliminer_sommet=false;
	  type_tri="rien";

	  z_pt1=z_pt2=z_pt3=0;
	}

	vector <point_nuage_BEY> liste_pts_triangle_BEY;
	void ajouter_pt(point_nuage *p){point_nuage_BEY bey; bey.p=p;  liste_pts_triangle_BEY.push_back(bey);nbre_pts_triangle++;}

	void liberer_memoire()
	{
	  liste_pts_triangle_BEY.clear();
	  nbre_pts_triangle=0;

	  delete liste_pts_triangle;

	  delete s1;
	  delete s2;
	  delete s3;
	}

	double getdensite_p1()  {return densite_p1;}
	void setdensite_p1(double x1) {densite_p1=x1;}

	double getdensite_p2()  {return densite_p2;}
	void setdensite_p2(double x1) {densite_p2=x1;}

	double getdensite_p3()  {return densite_p3;}
	void setdensite_p3(double x1) {densite_p3=x1;}

	int getnbre_pts_proche_p1()  {return nbre_pts_proche_p1;}
	void setnbre_pts_proche_p1(int x1) {nbre_pts_proche_p1=x1;}

    int getnbre_pts_proche_p2()  {return nbre_pts_proche_p2;}
    void setnbre_pts_proche_p2(int x1) {nbre_pts_proche_p2=x1;}

    int getnbre_pts_proche_p3()  {return nbre_pts_proche_p3;}
    void setnbre_pts_proche_p3(int x1) {nbre_pts_proche_p3=x1;}

	int getseg12(){return seg12;}
	int getseg13(){return seg13;}
	int getseg32(){return seg32;}

	void setseg12(int x1) {seg12=x1;}
	void setseg13(int x1) {seg13=x1;}
	void setseg32(int x1) {seg32=x1;}

 void setR(double r){ R=r;}
 void setB(double b){ B=b;}
 void setG(double g){ G=g;}

 double getR(){ return R;}
 double getB(){ return B;}
 double getG(){ return G;}

 void affecter_couleur();

 bool appartence_pt_triangle(double x, double y);
 void filtrage_un_triangle();

  bool gettrois_sommets_non_nuls()  {return trois_sommets_non_nuls;}
  void settrois_sommets_non_nuls(bool z1) {trois_sommets_non_nuls=z1;}

  void initialiser_liste_pts_triangles(){delete liste_pts_triangle; liste_pts_triangle =new liste_point_BEY();};
  void determiner_pt_eloingne(pt_plan *s);
  void determiner_pt_proche(pt_plan *s);
  void calculer_pts_intersection_segments_triangles_cercle(int num_point, double xc, double yc, double R, double x1, double y1, double x2, double y2, double & xinter, double & yinter);
  void intersection_deux_segment_BEY(int num_point, double x1,double y1,double x2,double y2, double x3,double y3,double x4,double y4,double & X,double & Y, double & alpha,double & beta);

  void calculer_pts_intersection_segments_triangles_normale_bissectrices(double xc, double yc, double R, double x1, double y1, double x2, double y2, double & xinter, double & yinter);


  bool getnouveau_triangle()  {return nouveau_triangle;}
  void setnouveau_triangle(bool z1) {nouveau_triangle=z1;}

  bool getcalcul_voisins()  {return calcul_voisins;}
  void setcalcul_voisins(bool z1) {calcul_voisins=z1;}

  bool getapproximation_plan()  {return approximation_plan;}
  void setapproximation_plan(bool z1) {approximation_plan=z1;}

  bool getpassage_numerotation()  {return passage_numerotation;}
  void setpassage_numerotation(bool z1) {passage_numerotation=z1;}

  double getdensite_m1()  {return densite_m1;}
  void setdensite_m1(double z1) {densite_m1=z1;}

  double getdensite_m2()  {return densite_m2;}
  void setdensite_m2(double z1) {densite_m2=z1;}

  double getdensite_m3()  {return densite_m3;}
  void setdensite_m3(double z1) {densite_m3=z1;}

  double getxc()  {return xc;}
  void setxc(double z1) {xc=z1;}

  double getyc()  {return yc;}
  void setyc(double z1) {yc=z1;}

  double getzc()  {return zc;}
  void setzc(double z1) {zc=z1;}

  double getRc()  {return Rc;}
  void setRc(double z1) {Rc=z1;}

  double getxg()  {return xg;}
  void setxg(double z1) {xg=z1;}

  double getyg()  {return yg;}
  void setyg(double z1) {yg=z1;}

  double getzg()  {return zg;}
  void setzg(double z1) {zg=z1;}

  triangle_initial* getsuiv(){return suiv;}
  triangle_initial* getprec(){return prec;}

  void setsuiv(triangle_initial* t){suiv=t;}
  void setprec(triangle_initial* t){prec=t;}


   int getnum_triangle()  {return num_triangle;}
	void setnum_triangle(int x1) {num_triangle=x1;}

  pt_plan* getp1(){return p1;}
  pt_plan* getp2(){return p2;}
  pt_plan* getp3(){return p3;}

  pt_plan* gets1(){return s1;}
  pt_plan* gets2(){return s2;}
  pt_plan* gets3(){return s3;}

  void setp1(pt_plan *p) {p1=p;}
  void setp2(pt_plan *p) {p2=p;}
  void setp3(pt_plan *p) {p3=p;}

  void sets1(pt_plan* s) {s1=s;}
  void sets2(pt_plan* s) {s2=s;}
  void sets3(pt_plan* s) {s3=s;}


  triangle_initial* getv1(){return v1;}
  triangle_initial* getv2(){return v2;}
  triangle_initial* getv3(){return v3;}


  void setv1(triangle_initial *p) {v1=p;}
  void setv2(triangle_initial *p) {v2=p;}
  void setv3(triangle_initial *p) {v3=p;}

  double getz_pt1()  {return z_pt1;}
  void setz_pt1(double z1) {z_pt1=z1;}

  double getz_pt2()  {return z_pt2;}
  void setz_pt2(double z1) {z_pt2=z1;}

  double getz_pt3()  {return z_pt3;}
  void setz_pt3(double z1) {z_pt3=z1;}

  double getdist_pt_plan_max()  {return dist_pt_plan_max;}    //la distance max entre les points de triangle et le plan
  double getdist_pt_plan_min()  {return dist_pt_plan_min;}    //la distance min entre les points de triangle et le plan

  void setdist_pt_plan_max(double z1) {dist_pt_plan_max=z1;}
  void setdist_pt_plan_min(double z1) {dist_pt_plan_min=z1;}


  liste_point_BEY *getliste_pts_triangle()       {return liste_pts_triangle;}
  void setliste_pts_triangle(liste_point_BEY * x1) {liste_pts_triangle=x1;}

  int getnbre_pts_triangle()  {return nbre_pts_triangle;}
  void setnbre_pts_triangle(int x1) {nbre_pts_triangle=x1;}


	void setx1_inter(double a)  {x1_inter=a;}
	void sety1_inter(double a)  {y1_inter=a;}

	void setx2_inter(double a)  {x2_inter=a;}
	void sety2_inter(double a)  {y2_inter=a;}

    double getx1_inter()  {return x1_inter;}
    double gety1_inter()  {return y1_inter;}

    double getx2_inter()  {return x2_inter;}
    double gety2_inter()  {return y2_inter;}

    double getx_loin()  {return x_loin;}
    double gety_loin()  {return y_loin;}

    double getx_proche()  {return x_proche;}
    double gety_proche()  {return y_proche;}

    double getrayon_proche()  {return rayon_proche;}
    double getrayon_loin()  {return rayon_loin;}

    double getxmin_t()  {return xmin_t;}
    double getxmax_t()  {return xmax_t;}

    double getymin_t()  {return ymin_t;}
    double getymax_t() {return ymax_t;}

    double getzmin_t()  {return zmin_t;}
    double getzmax_t()  {return zmax_t;}


    void setxmin_t(double x1) {xmin_t=x1;}
    void setxmax_t(double x2) {xmax_t=x2;}

    void setymin_t(double y1) {ymin_t=y1;}
    void setymax_t(double y2) {ymax_t=y2;}

    void setzmin_t(double z1) {zmin_t=z1;}
    void setzmax_t(double z2) {zmax_t=z2;}

     double geta_plan()  {return a_plan;}
     void seta_plan(double z1) {a_plan=z1;}

     double getb_plan()  {return b_plan;}
     void setb_plan(double z2) {b_plan=z2;}

     double getc_plan()  {return c_plan;}
     void setc_plan(double z3) {c_plan=z3;}

    void nbre_points(){nbre_pts_triangle++;}

    bool getcalcul_pts_proche()  {return  calcul_pts_proche;}
    void setcalcul_pts_proche(bool x2)  { calcul_pts_proche=x2;}


    bool getfiltre()  {return  filtre;}
    void setfiltre(bool x2)  { filtre=x2;}

    bool geteliminer_sommet()  {return  eliminer_sommet;}
    void seteliminer_sommet(bool x2)  { eliminer_sommet=x2;}

     bool getfrontiere()  {return  frontiere;}
    void setfrontiere(bool x2)  { frontiere=x2;}

     bool getpassage()  {return  passage;}
     void setpassage(bool x2)  { passage=x2;}


    void calcul_normal_triangle();
    void calcul_normal_triangle_BEY();

    double getaire_tr()  {return aire_tr;}
    void setaire_tr(double z1) {aire_tr=z1;}

     void setnx(double z1) {nx=z1;}
     double getnx()  {return nx;}

     void setny(double z1) {ny=z1;}
     double getny()  {return ny;}

     void setnz(double z1) {nz=z1;}
     double getnz()  {return nz;}

     AnsiString gettype_tri() {return type_tri;}
     void settype_tri(AnsiString x1) {type_tri=x1;}

     bool getinserer_tri()  {return  inserer_tri;}
    void setinserer_tri(bool x2)  { inserer_tri=x2;}

   void determiner_pts_proches_sommets_triangle(double rapport, double aire_min_triangle);

   void approximation_pts_triangle_plan_moindre_carre();
   void distance_max_pts_plan();
   void dessiner_pts_triangle();
   void dessiner_pts_proches_sommets_triangle();
   void dessiner_pts_proches_milieux_segments_triangle();
 };

//____________________classe triangle____________________________________________
class ListTriangle_BEY_BEY;

class triangle_initial_BEY
{
  public:

  bool filtre;
  bool supprime;
  int num_triangle;
  int nbre_pts_triangle;
  triangle_initial_BEY *suiv;
  triangle_initial_BEY *prec;
  triangle_initial_BEY *v1, *v2, *v3;

  double densite_p1, densite_p2, densite_p3;
  double densite_m1;
  double densite_m2;
  double densite_m3;

  float R ,G, B;

  bool nouveau_triangle;
  bool calcul_voisins;
//  bool filtre;
  bool trois_sommets_non_nuls;
  pt_plan *s1, *s2, *s3;
  bool eliminer_sommet;
  double nx,ny,nz;
  bool passage_numerotation;

  double xmax_t,ymax_t,zmax_t,xmin_t,ymin_t,zmin_t;
  double z_pt1,z_pt2,z_pt3;
  double x1_inter, y1_inter;
  double x2_inter, y2_inter;
  double a_plan,b_plan,c_plan;
  double dist_pt_plan_max;
  double dist_pt_plan_min;
  double aire_tr;
  double rayon_loin;
  double rayon_proche;

  ~triangle_initial_BEY()
  {
  liste_pts_triangle_BEY.clear();
  nbre_pts_triangle=0;

  delete s1;
  delete s2;
  delete s3;

  suiv=NULL;
  prec=NULL;

  v1=NULL;
  v2=NULL;
  v3=NULL;
  }

  triangle_initial_BEY()
  {
  triangle_pour_calculer_voisin=true;
  nbre_pts_triangle=0;
  num_triangle=-1;
  densite_p1=0;
  densite_p2=0;
  densite_p3=0;

  densite_m1=0;
  densite_m2=0;
  densite_m3=0;

  nouveau_triangle=true;
  calcul_voisins=false;
  filtre=false;
  dist_pt_plan_max=0;
  s1=new pt_plan();
  s2=new pt_plan();
  s3=new pt_plan();

  v1=NULL;
  v2=NULL;
  v3=NULL;
  liste_pts_triangle_BEY.clear();

  nbre_pts_triangle=0;
  filtre=false;
  z_pt1=z_pt2=z_pt3=0;

  affecter_couleur();
  supprime=false;

  suiv=NULL;
  prec=NULL;
  }

  void liberer_memoire_liste_pts_triangle()
  {
  nbre_pts_triangle=0;
  liste_pts_triangle_BEY.clear();
  }

    bool appartenance_pt_triangle_BEY(double x, double y, double p1p2_x, double p1p2_y, double p1p3_x, double p1p3_y, double p2p3_x, double p2p3_y);
	void calculer_deltaX_deltaY_deltaZ(double &p1p2_x, double &p1p2_y, double &p1p3_x, double &p1p3_y, double &p2p3_x, double &p2p3_y);
	void affecter_coordonnees_sommets_triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
	{
		   s1->setx_pt(x1);
		   s1->sety_pt(y1);
		   s1->setz(z1);

		   s2->setx_pt(x2);
		   s2->sety_pt(y2);
		   s2->setz(z2);

		   s3->setx_pt(x3);
		   s3->sety_pt(y3);
		   s3->setz(z3);

		   calculer_limites_triangle();
	}

	void recuperer_parametres_triangle_subdivision(double &xs1, double &ys1, double &xs2, double &ys2, double &xs3, double &ys3)
	{
	xs1=s1->x_pt;
	ys1=s1->y_pt;

	xs2=s2->x_pt;
	ys2=s2->y_pt;

	xs3=s3->x_pt;
	ys3=s3->y_pt;

	}


	void calculer_nouveaux_parametres_triangle()
	{
	double x1, y1, z1, x2, y2, z2, x3, y3, z3;

	x1=s1->getx_pt();
	y1=s1->gety_pt();
	z1=z_pt1;

	x2=s2->getx_pt();
	y2=s2->gety_pt();
	z2=z_pt2;

	x3=s3->getx_pt();
	y3=s3->gety_pt();
	z3=z_pt3;

		   double v1x=x2-x1;
		   double v1y=y2-y1;
		   double v1z=z2-z1;

		   double v2x=x3-x1;
		   double v2y=y3-y1;
		   double v2z=z3-z1;

		   double nx1=v1y*v2z-v1z*v2y;
		   double ny1=v1z*v2x-v1x*v2z;
		   double nz1=v1x*v2y-v1y*v2x;

		   if(nz1<0){nx1=-nx1; ny1=-ny1; nz1=-nz1;}

		   double module=sqrt(nx*nx+ny*ny+nz*nz);

		   aire_tr=module/2;

		   nx=nx1/module;
		   ny=ny1/module;
		   nz=nz1/module;

           double a_plan1=nx;
           double b_plan1=ny;
           double c_plan1=nz;

          double d=-a_plan1*x1-b_plan1*y1-c_plan1*z1;

		  a_plan=-a_plan1/c_plan1;
		  b_plan=-b_plan1/c_plan1;
		  c_plan=-d/c_plan1;
	}

	void recupere_parametres_triangle(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3, double &xminT, double &yminT, double &xmaxT, double &ymaxT, double &p1p2_x, double &p1p2_y, double &p1p3_x, double &p1p3_y, double &p2p3_x, double &p2p3_y)
	{
	x1=s1->getx_pt();
	y1=s1->gety_pt();

	x2=s2->getx_pt();
	y2=s2->gety_pt();

	x3=s3->getx_pt();
	y3=s3->gety_pt();

	xminT=xmin_t;
	yminT=ymin_t;

	xmaxT=xmax_t;
	ymaxT=ymax_t;

	p1p2_x=x2-x1;
	p1p2_y=y2-y1;

	p1p3_x=x3-x1;
	p1p3_y=y3-y1;

	p2p3_x=x3-x2;
	p2p3_y=y3-y2;
	}

	void recuperer_coordonnees_sommets_triangle(double &xs1, double &ys1, double &zs1, double &xs2, double &ys2, double &zs2, double &xs3, double &ys3, double &zs3)
	{
	xs1=s1->getx_pt();
	ys1=s1->gety_pt();
	zs1=z_pt1;

	xs2=s2->getx_pt();
	ys2=s2->gety_pt();
	zs2=z_pt2;

	xs3=s3->getx_pt();
	ys3=s3->gety_pt();
	zs3=z_pt3;
	}

	void initialiser_numerotation()
	{
	passage_numerotation=false;
	s1->setnumero_pt(-1);
	s2->setnumero_pt(-1);
	s3->setnumero_pt(-1);
	}

	void intialiser_liste_pts_triangle_BEY()
	{
	liste_pts_triangle_BEY.clear();
	nbre_pts_triangle=0;
	}

	void initialiser_voisins(int indice)
	{
	if(indice==1)
	{
	v1->intialiser_liste_pts_triangle_BEY();
	v1->setfiltre(true);
	}

	if(indice==2)
	{
	v2->intialiser_liste_pts_triangle_BEY();
	v2->setfiltre(true);
	}

	if(indice==3)
	{
	v3->intialiser_liste_pts_triangle_BEY();
	v3->setfiltre(true);
	}
	}

	void initialiser()
	{
    triangle_pour_calculer_voisin=true;
	liste_pts_triangle_BEY.clear();
	nbre_pts_triangle=0;

	densite_p1=0;
	densite_p2=0;
	densite_p3=0;

	densite_m1=0;
	densite_m2=0;
	densite_m3=0;

	filtre=false;
	eliminer_sommet=false;
	calcul_voisins=false;
	nouveau_triangle=true;

	dist_pt_plan_max=0;
	filtre=false;
	z_pt1=z_pt2=z_pt3=0;
	supprime=false;

	v1=NULL;
	v2=NULL;
	v3=NULL;
	}

	void intialiser_this()
	{
    triangle_pour_calculer_voisin=true;
	nbre_pts_triangle=0;

	densite_p1=0;
	densite_p2=0;
	densite_p3=0;

	densite_m1=0;
	densite_m2=0;
	densite_m3=0;

	filtre=false;
	eliminer_sommet=false;
	calcul_voisins=false;
	nouveau_triangle=true;

	dist_pt_plan_max=0;
	filtre=false;
	z_pt1=z_pt2=z_pt3=0;
	supprime=false;

	v1=NULL;
	v2=NULL;
	v3=NULL;
	}

	double ecart_max_droite;
	double zmax_pts_triangle, zmin_pts_triangle;
	double aire_triangle_2D;
	double delta_Z_triangle, delta_Z_pts_triangle;
	float x_pt_ecart_max, y_pt_ecart_max, z_pt_ecart_max;
    bool triangle_pour_calculer_voisin;

	vector <point_nuage_BEY> liste_pts_triangle_BEY;
	void calculer_zmax_zmin_pts_triangle();
	void calculer_ecart_max_droite();

	void ajouter_pt(point_nuage *p){point_nuage_BEY bey; bey.p=p;  liste_pts_triangle_BEY.push_back(bey);nbre_pts_triangle++;}
	void ajouter_pt(point_nuage_BEY p){liste_pts_triangle_BEY.push_back(p);nbre_pts_triangle++;}
    void calculer_pt_bissectrice(int point_centre, double & x_milieu, double & y_milieu);
	void liberer_memoire_BEY()
	{
	  liste_pts_triangle_BEY.clear();
	  nbre_pts_triangle=0;

	  delete s1;
	  delete s2;
	  delete s3;
	}

	bool comparer_nbre_pts()
	{
	bool resultat;
	resultat=(int)nbre_pts_triangle==(int)liste_pts_triangle_BEY.size();
    return resultat;
	}

	double getdensite_p1()  {return densite_p1;}
	void setdensite_p1(double x1) {densite_p1=x1;}

	double getdensite_p2()  {return densite_p2;}
	void setdensite_p2(double x1) {densite_p2=x1;}

	double getdensite_p3()  {return densite_p3;}
	void setdensite_p3(double x1) {densite_p3=x1;}

 void determiner_nbre_pts_triangle(){/*nbre_pts_triangle=liste_pts_triangle_BEY.size();*/}
 void setR(float r){ R=r;}
 void setB(float b){ B=b;}
 void setG(float g){ G=g;}

 float getR(){ return R;}
 float getB(){ return B;}
 float getG(){ return G;}

  bool gettrois_sommets_non_nuls()  {return trois_sommets_non_nuls;}
  void settrois_sommets_non_nuls(bool z1) {trois_sommets_non_nuls=z1;}

  void setnouveau_triangle(bool z1) {nouveau_triangle=z1;}

  bool getcalcul_voisins()  {return calcul_voisins;}
  void setcalcul_voisins(bool z1) {calcul_voisins=z1;}

  double getdensite_m1()  {return densite_m1;}
  void setdensite_m1(double z1) {densite_m1=z1;}

  double getdensite_m2()  {return densite_m2;}
  void setdensite_m2(double z1) {densite_m2=z1;}

  double getdensite_m3()  {return densite_m3;}
  void setdensite_m3(double z1) {densite_m3=z1;}

  bool getnouveau_triangle()  {return nouveau_triangle;}

  triangle_initial_BEY* getsuiv(){return suiv;}
  triangle_initial_BEY* getprec(){return prec;}

  void setsuiv(triangle_initial_BEY* t){suiv=t;}
  void setprec(triangle_initial_BEY* t){prec=t;}

  int getnum_triangle()  {return num_triangle;}
  void setnum_triangle(int x1) {num_triangle=x1;}


  pt_plan* gets1(){return s1;}
  pt_plan* gets2(){return s2;}
  pt_plan* gets3(){return s3;}

  void sets1(pt_plan* s) {s1=s;}
  void sets2(pt_plan* s) {s2=s;}
  void sets3(pt_plan* s) {s3=s;}

  triangle_initial_BEY* getv1(){return v1;}
  triangle_initial_BEY* getv2(){return v2;}
  triangle_initial_BEY* getv3(){return v3;}

  void setv1(triangle_initial_BEY *p) {v1=p;}
  void setv2(triangle_initial_BEY *p) {v2=p;}
  void setv3(triangle_initial_BEY *p) {v3=p;}

  double getz_pt1()  {return z_pt1;}
  void setz_pt1(double z1) {z_pt1=z1;}

  double getz_pt2()  {return z_pt2;}
  void setz_pt2(double z1) {z_pt2=z1;}

  double getz_pt3()  {return z_pt3;}
  void setz_pt3(double z1) {z_pt3=z1;}

  double getdist_pt_plan_max()  {return dist_pt_plan_max;}
  double getdist_pt_plan_min()  {return dist_pt_plan_min;}

  void setdist_pt_plan_max(double z1) {dist_pt_plan_max=z1;}
  void setdist_pt_plan_min(double z1) {dist_pt_plan_min=z1;}

  int getnbre_pts_triangle()  {return nbre_pts_triangle;}
  void setnbre_pts_triangle(int x1) {nbre_pts_triangle=x1;}

	void setx1_inter(double a)  {x1_inter=a;}
	void sety1_inter(double a)  {y1_inter=a;}

	void setx2_inter(double a)  {x2_inter=a;}
	void sety2_inter(double a)  {y2_inter=a;}

	double getx1_inter()  {return x1_inter;}
	double gety1_inter()  {return y1_inter;}

	double getx2_inter()  {return x2_inter;}
	double gety2_inter()  {return y2_inter;}

	double getrayon_loin()  {return rayon_loin;}

	double getrayon_proche()  {return rayon_proche;}

	double getxmin_t()  {return xmin_t;}
	double getxmax_t()  {return xmax_t;}

	double getymin_t()  {return ymin_t;}
	double getymax_t() {return ymax_t;}

	double getzmin_t()  {return zmin_t;}
	double getzmax_t()  {return zmax_t;}

	void setxmin_t(double x1) {xmin_t=x1;}
	void setxmax_t(double x2) {xmax_t=x2;}

	void setymin_t(double y1) {ymin_t=y1;}
	void setymax_t(double y2) {ymax_t=y2;}

	void setzmin_t(double z1) {zmin_t=z1;}
	void setzmax_t(double z2) {zmax_t=z2;}

	 double geta_plan()  {return a_plan;}
	 void seta_plan(double z1) {a_plan=z1;}

	 double getb_plan()  {return b_plan;}
	 void setb_plan(double z2) {b_plan=z2;}

	 double getc_plan()  {return c_plan;}
	 void setc_plan(double z3) {c_plan=z3;}

	bool getfiltre()  {return  filtre;}
	void setfiltre(bool x2)  { filtre=x2;}

	bool geteliminer_sommet()  {return  eliminer_sommet;}
	void seteliminer_sommet(bool x2)  { eliminer_sommet=x2;}

	double getaire_tr()  {return aire_tr;}
	void setaire_tr(double z1) {aire_tr=z1;}

	 void setnx(double z1) {nx=z1;}
	 double getnx()  {return nx;}

	 void setny(double z1) {ny=z1;}
	 double getny()  {return ny;}

	 void setnz(double z1) {nz=z1;}
	 double getnz()  {return nz;}

  bool getpassage_numerotation()  {return passage_numerotation;}
  void setpassage_numerotation(bool z1) {passage_numerotation=z1;}


 void affecter_couleur()
  {
	R =(float)( (rand() % 255) /255.);
	B =(float)( (rand() % 255) /255.);
	G =(float)( (rand() % 255) /255.);
 }


 bool appartence_pt_triangle(double x, double y);  //OK NEW
 bool appartence_pt_segments_triangle(double x, double y);  //OK NEW
 void filtrage_un_triangle(); //OK NEW
 void determiner_pts_triangle();
  void initialiser_liste_pts_triangles(){liste_pts_triangle_BEY.clear(); nbre_pts_triangle=0;}; //OK NEW
  void determiner_pt_eloingne(double x, double y); //OK NEW
  void determiner_pt_proche(double x, double y);   //OK NEW
  void calculer_pts_intersection_segments_triangles_cercle(int num_point, double xc, double yc, double R, double x1, double y1, double x2, double y2, double & xinter, double & yinter); //OK NEW
  void intersection_deux_segment_BEY(int num_point, double x1,double y1,double x2,double y2, double x3,double y3,double x4,double y4,double & X,double & Y, double & alpha,double & beta); //OK NEW
  void calculer_pts_intersection_segments_triangles_normale_bissectrices(double xc, double yc, double R, double x1, double y1, double x2, double y2, double & xinter, double & yinter); //OK NEW

   void nbre_points(){nbre_pts_triangle++;} //OK NEW
   void calcul_normal_triangle();  //OK NEW
   void calcul_normal_triangle_BEY(); //OK NEW
   void determiner_pts_proches_sommets_triangle(double rapport, double aire_min_triangle); //OK NEW
   void approximation_pts_triangle_plan_moindre_carre(); //OK NEW
   void distance_max_pts_plan(); //OK NEW
   void dessiner_pts_triangle();  //OK NEW
   void dessiner_pts_proches_sommets_triangle();  //OK NEW
   void dessiner_pts_proches_milieux_segments_triangle();  //OK NEW
   void	dessiner_pts_proches_sommets_triangle_sommets_nuls_BEY(); //OK NEW
   void voisins_a_modifier(); //OK NEW
   void voisins_a_modifier_BEY();
   void subdivision_sommet_1_null(double x_centre, double y_centre,
										  double x1_inter, double y1_inter, double x2_inter, double y2_inter,
										  double x_p3, double y_p3, double x_p2, double y_p2, ListTriangle_BEY_BEY *liste_triangle_adaptation_BEY); //OK NEW
   void subdiviser_triangles_voisins(ListTriangle_BEY_BEY *liste_triangle_adaptation_BEY); //OK NEW
   void subdiviser_triangles_voisins_NEW(ListTriangle_BEY_BEY *liste_triangle_adaptation_BEY, triangle_initial_BEY *V1, triangle_initial_BEY *V2, triangle_initial_BEY *V3);
   bool creer_triangles(double xinter, double yinter, triangle_initial_BEY *voisin, ListTriangle_BEY_BEY *liste_triangle_adaptation_BEY); //OK NEW
   void creation_deux_triangles_milieu_cote(ListTriangle_BEY_BEY *liste_triangle_adaptation_BEY);
   void calculer_limites_triangle();
};



//--------------------------------------------------------
 class noeud_triangle_initial
{
triangle_initial *triangle;
bool voisin_pt_stat;
noeud_triangle_initial *suiv5;
noeud_triangle_initial *prec5;

 public:

	noeud_triangle_initial()
	{
    triangle=NULL;
	suiv5=prec5=NULL;
	voisin_pt_stat=false;
	}

	~noeud_triangle_initial()
	{
	delete triangle;
	}

	bool getvoisin_pt_stat()  {return  voisin_pt_stat;}
    void setvoisin_pt_stat(bool x2)  { voisin_pt_stat=x2;}


    void settriangle(triangle_initial *tri) {triangle=tri;}
    triangle_initial * gettriangle()          {return triangle;}


    void setsuiv5(noeud_triangle_initial *h) {suiv5=h;  }
    noeud_triangle_initial * getsuiv5(){return suiv5;}

    void setprec5( noeud_triangle_initial *h) {prec5=h;}
    noeud_triangle_initial * getprec5()      {return prec5;}


};

//-------------------------------------------------
class liste_triangle_initial
{
noeud_triangle_initial *debut_t;
noeud_triangle_initial *fin_t;
int nbre_tri;

 public:

   liste_triangle_initial ()
   {
     debut_t=NULL;
     fin_t=NULL;
     nbre_tri=0;
   }

   ~liste_triangle_initial ()
   {
	 debut_t=NULL;
	 fin_t=NULL;
	 nbre_tri=0;
   }

   int getnbre_tri()  {return nbre_tri;}
   void setnbre_tri(int x1) {nbre_tri=x1;}

   noeud_triangle_initial * getfin_t(){return fin_t;}
   void setfin_t(noeud_triangle_initial *f){fin_t=f;}

   noeud_triangle_initial * getdebut_t() {return debut_t;}
   void setdebut_t(noeud_triangle_initial *f){debut_t=f;}

   liste_triangle_initial  &  inserer_triangle(noeud_triangle_initial *);

   liste_triangle_initial  & operator=(   liste_triangle_initial  *A)

    {
      debut_t=A->getdebut_t();
      return *this;
    }


};

//--------------------------------------------------------
 class noeud_trajet
{
bool bon_sens;
liste_point_plan *trajet;

noeud_trajet *suivt;
noeud_trajet *prect;

 public:

    noeud_trajet()
    {
     suivt=prect=NULL;

	 trajet=new liste_point_plan;

     bon_sens=false;
    }

	~noeud_trajet()
	{
	 suivt=prect=NULL;
	 delete trajet;
	}

     bool getbon_sens()  {return  bon_sens;}
    void setbon_sens(bool x2)  { bon_sens=x2;}

    void settrajet(liste_point_plan *tra) {trajet=tra;}
    liste_point_plan * gettrajet()          {return trajet;}
 

    void setsuivt(noeud_trajet *h) {suivt=h;  }
    noeud_trajet * getsuivt(){return suivt;}

    void setprect( noeud_trajet *h) {prect=h;}
    noeud_trajet * getprect()      {return prect;}


};

//----------------------------------------
class liste_noeud_trajet
{
noeud_trajet *debut;
noeud_trajet *fin;
int nbre_trajet;

float rayon_optim;
float vitesse_avance,vitesse_eng,vitesse_deg,longueur,rayon;

public:

   liste_noeud_trajet ()
   {
     debut=NULL;
     fin=NULL;
     nbre_trajet=0;
   }

   ~liste_noeud_trajet ()
   {
     debut=NULL;
     fin=NULL;
   }

	 void setrayon(float z1) {rayon=z1;}
	 float getrayon()  {return rayon;}

	  void setrayon_optim(float z1) {rayon_optim=z1;}
     float getrayon_optim()  {return rayon_optim;}

	 void setvitesse_avance(float z1) {vitesse_avance=z1;}
	 float getvitesse_avance()  {return vitesse_avance;}

	  void setvitesse_eng(float z1) {vitesse_eng=z1;}
     float getvitesse_eng()  {return vitesse_eng;}

	 void setvitesse_deg(float z1) {vitesse_deg=z1;}
     float getvitesse_deg()  {return vitesse_deg;}

	 void setlongueur(float z1) {longueur=z1;}
     float getlongueur()  {return longueur;}

     int getnbre_trajet()  {return nbre_trajet;}
   void setnbre_trajet(int x1) {nbre_trajet=x1;}

   noeud_trajet * getfin(){return fin;}
   void setfin(noeud_trajet *f){fin=f;}

   noeud_trajet * getdebut() {return debut;}
   void setdebut_t(noeud_trajet *f){debut=f;}

   liste_noeud_trajet  &  inserer_noeud_trajet(noeud_trajet *);


   liste_noeud_trajet  & operator=(liste_noeud_trajet  *A)

    {
      debut=A->getdebut ();
      return *this;
    }


};

//---------------------------------------------------------------------------------

//--------------------------------------------------------
class ListTriangle_BEY
{

triangle_initial *tete;
triangle_initial *fin;

int nbre_triangles;
int nbre_triangles_non_filtres;

public:

ListTriangle_BEY()
{
tete=fin=NULL;
nbre_triangles=0;
};

~ListTriangle_BEY()
{
tete=fin=NULL;
};

void liberer_memoire();

ListTriangle_BEY & ajouter_Triangle(triangle_initial *T1);

int getnbre_triangles_non_filtres(){return nbre_triangles_non_filtres;};
void setnbre_triangles_non_filtres(int x){nbre_triangles_non_filtres=x;};

int getnbre_triangles(){return nbre_triangles;};
void setnbre_triangles(int x){nbre_triangles=x;};

triangle_initial* gettete(){return tete;};
triangle_initial* getfin(){return fin;};

void settete(triangle_initial* x){tete=x;};
void setfin(triangle_initial* x){fin=x;};

void filtrer_triangles_distances_sommets_triangle();

void determiner_voisins_triangles(bool triangulation_initiale); //OK
void determiner_pts_proches_sommets_triangles(bool triangulation_initiale); //OK
void determiner_pts_triangles(bool triangulation_initiale); //OK
void filtrage_triangles(bool triangulation_initiale); //OK
void approximation_pts_triangles_plan_moindre_carre(bool triangulation_initiale); //OK
void distance_max_pts_plans(bool triangulation_initiale);  //OK
void erreur_max_min_pts_triangles(); //OK

void liberer_liste_pts_triangles();
};

//--------------------------------------------------------
class ListTriangle_BEY_BEY
{

triangle_initial_BEY *tete;
triangle_initial_BEY *fin;

int nbre_triangles;
int nbre_triangles_non_filtres;

public:

ListTriangle_BEY_BEY()
{
tete=fin=NULL;
nbre_triangles=0;
nbre_triangles_non_filtres=0;
};

~ListTriangle_BEY_BEY()
{
triangle_initial_BEY *prev=tete;
	while (tete!=NULL)
	{
	   tete=tete->getsuiv();
	   delete prev;
	   prev=tete;
	}
};


void liberer_memoire();
void modifier_couleurs_triangles();
ListTriangle_BEY_BEY & ajouter_Triangle(triangle_initial_BEY *T1);
ListTriangle_BEY_BEY & supprimer_Triangle_milieu(triangle_initial_BEY *T1);
ListTriangle_BEY_BEY & supprimer_Triangle_debut(triangle_initial_BEY *T1);
ListTriangle_BEY_BEY & supprimer_Triangle_fin(triangle_initial_BEY *T1);

int getnbre_triangles_non_filtres(){return nbre_triangles_non_filtres;};
void setnbre_triangles_non_filtres(int x){nbre_triangles_non_filtres=x;};

int getnbre_triangles(){return nbre_triangles;};
void setnbre_triangles(int x){nbre_triangles=x;};

triangle_initial_BEY* gettete(){return tete;};
triangle_initial_BEY* getfin(){return fin;};

void settete(triangle_initial_BEY* x){tete=x;};
void setfin(triangle_initial_BEY* x){fin=x;};

ListTriangle_BEY_BEY & filtrer_triangles_distances_sommets_triangle();

ListTriangle_BEY_BEY & determiner_voisins_triangles(bool triangulation_initiale); //OK NEW
ListTriangle_BEY_BEY & verifier_voisins_triangles();
ListTriangle_BEY_BEY & determiner_voisins_triangles_new(); //OK NEW
ListTriangle_BEY_BEY & determiner_pts_proches_sommets_triangles(bool triangulation_initiale); //OK NEW
ListTriangle_BEY_BEY & determiner_pts_triangles(bool triangulation_initiale); //OK NEW
ListTriangle_BEY_BEY & filtrage_triangles(bool triangulation_initiale); //OK NEW
ListTriangle_BEY_BEY & approximation_pts_triangles_plan_moindre_carre(bool triangulation_initiale); //OK NEW
ListTriangle_BEY_BEY & distance_max_pts_plans(bool triangulation_initiale);  //OK NEW
ListTriangle_BEY_BEY & erreur_max_min_pts_triangles(); //OK  NEW

ListTriangle_BEY_BEY & liberer_liste_pts_triangles(); //OK  NEW
ListTriangle_BEY_BEY & mise_a_jour_triangulation(); //OK  NEW
ListTriangle_BEY_BEY & mise_a_jour_triangulation_voisins_triangles_supprimes(); //OK  NEW
ListTriangle_BEY_BEY & subdivision_adaptative_triangles();
ListTriangle_BEY_BEY & traitement_triangles_frontieres_densites_nulles();
ListTriangle_BEY_BEY & determiner_parametres_filtration_triangles();
ListTriangle_BEY_BEY & Filtrer_triangles_sans_voisins();
};


//_________________________________________________________________________________
class TPoint_Clouds_Import : public TForm
{
__published:	// IDE-managed Components
        TSaveDialog *SaveDialog1;
        TButton *Button1;
	TOpenDialog *OpenDialog2;
        TGroupBox *GroupBox5;
        TGroupBox *GroupBox4;
        TLabel *Label4;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label5;
        TLabel *Label3;
        TLabel *Label6;
        TEdit *Edit1;
        TEdit *Edit4;
        TEdit *Edit5;
        TEdit *Edit2;
        TEdit *Edit6;
        TEdit *Edit3;
        TGroupBox *GroupBox3;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *Edit7;
        TEdit *Edit8;
        TEdit *Edit9;
        TLabel *Label10;
        TEdit *Edit10;
        TGroupBox *GroupBox6;
        TButton *Button3;
        TComboBox *ComboBox1;
        TComboBox *ComboBox3;
        TGroupBox *GroupBox8;
        TLabel *Label11;
        TEdit *Edit13;
        TButton *Button5;
	TOpenDialog *OpenDialog1;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TButton *Button6;
	TGroupBox *GroupBox2;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall CheckBox4Click(TObject *Sender);
	void __fastcall CheckBox5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPoint_Clouds_Import(TComponent* Owner);

        fichier_texte entree;

        liste_point *nuage_pts;
		liste_point_BEY *nuage_pts_BEY;

		Nuage_Pts_BEY NUAGE_PTS_BEY;

		liste_point_plan *liste_points_plan;
		liste_point_plan *liste_points_plan_trier;

		liste_triangle_initial *liste_triangles_pt_stat;


		triangle_initial *cible;
		point_nuage point_cible;

		void dessiner_point_cible();

		bool fichier_enregistre, points_generes;
		void dessiner_triangles_voisins();
		bool fichier_valid;

		cellule **cellule_points;
		cellule_BEY **cellule_points_BEY; //BEY
		cellule_sommets_BEY **cellule_sommets;
		pt_plan **point_plan;

		vector <pt_plan_BEY> sommets_triangles;

		triangle_initial **triangle_plan;

        void filtrer_points_double();

        ListTriangle_BEY *liste_triangle_adaptation;
        ListTriangle_BEY_BEY *liste_triangle_adaptation_BEY;
        ListTriangle_BEY_BEY *liste_triangle_Filtres_adaptation_BEY;
		int nbre_sommets_projetes;
		bool lecture_nuage_pts;
        bool test_paroi_vert(noeud_point_nuage *, noeud_point_nuage *,noeud_point_nuage *, double &nx, double &ny, double &nz, double &D);
		bool test_paroi_horizontal(noeud_point_nuage *c1,noeud_point_nuage *c2,noeud_point_nuage *c3, double &nx, double &ny, double &nz, double &D);
		cellule_sommets_triangles **Cellules_Sommets_Triangles;
		int Nbre_Cellules_Sommets_Triangles, Nbre_Cellules_Sommets_Triangles_moins_un;
};
//---------------------------------------------------------------------------
extern PACKAGE TPoint_Clouds_Import *Point_Clouds_Import;
//---------------------------------------------------------------------------

#endif
