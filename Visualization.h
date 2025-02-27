//---------------------------------------------------------------------------

#ifndef VisualizationH
#define VisualizationH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <gl\gl.h>
#include <gl\glu.h>

double min(double a, double b){if(a<b) return a;else return b;}
double max(double a, double b){if(a>b) return a;else return b;}

const GLubyte X_maj[10] = {0x81, 0xc3, 0x66, 0x24, 0x18, 0x24, 0x26, 0x42, 0xc3, 0x81};
const GLubyte Y_maj[10] = {0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1c, 0x14, 0x22, 0x41};
const GLubyte Z_maj[10] = {0xff, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0xff};

typedef enum {rien,Vue3D,Zoom,ZoomAll,Fenetre,Rotx,Roty,Rotz,Rotxy,Rotxz,Rotyz,projxy,projxz,projyz,translation} typeselection;
typedef enum {MB_UP,MB_DOWN} typeetat;

typeselection selection=rien;
TMouseButton MouseButton;
typeetat EtatButton=MB_UP;
int mposx,mposy;

bool sel_souris, trouve;
//---------------------------------------------------------------------------

class Region_Selection
{
  private:

  double x1,y1,x2,y2;
  double x1_reel,y1_reel,z1_reel,x2_reel,y2_reel,z2_reel;

  public:

  Region_Selection(){x1=y1=x2=y2=0;}
  Region_Selection(double X1,double Y1,double X2,double Y2){x1=X1; y1=Y1; x2=X2; y2=Y2;}
  void SetX1(double X1){ x1=X1;}
  void SetY1(double Y1){ y1=Y1;}
  void SetX2(double X2){ x2=X2;}
  void SetY2(double Y2){ y2=Y2;}

  void SetX1_reel(double X1){ x1_reel=X1;}
  void SetY1_reel(double Y1){ y1_reel=Y1;}
  void SetX2_reel(double X2){ x2_reel=X2;}
  void SetY2_reel(double Y2){ y2_reel=Y2;}
  void SetZ1_reel(double X2){ z1_reel=X2;}
  void SetZ2_reel(double Y2){ z2_reel=Y2;}


  double GetX1(){return x1;}
  double GetY1(){return y1;}
  double GetX2(){return x2;}
  double GetY2(){return y2;}

  double GetX1_reel(){return x1_reel;}
  double GetY1_reel(){return y1_reel;}
  double GetX2_reel(){return x2_reel;}
  double GetY2_reel(){return y2_reel;}
  double GetZ1_reel(){return z1_reel;}
  double GetZ2_reel(){return z2_reel;}

  double MinX(){ return min(x1_reel,x2_reel);}
  double MinY(){ return min(y1_reel,y2_reel);}
  double MinZ(){ return min(z1_reel,z2_reel);}

  double MaxX(){ return max(x1_reel,x2_reel);}
  double MaxY(){ return max(y1_reel,y2_reel);}
  double MaxZ(){ return max(z1_reel,z2_reel);}

  double Width(){ return (max(x1_reel,x2_reel)- min(x1_reel,x2_reel));}   //largeur
  double Height(){ return (max(y1_reel,y2_reel)- min(y1_reel,y2_reel));}    //hauteur

  double MinX_ecran(){ return min(x1,x2);}
  double MinY_ecran(){ return min(y1,y2);}

  double MaxX_ecran(){ return max(x1,x2);}
  double MaxY_ecran(){ return max(y1,y2);}

  double Width_ecran(){ return (max(x1,x2)- min(x1,x2));}   //largeur
  double Height_ecran(){ return (max(y1,y2)- min(y1,y2));}    //hauteur

/*
  double MinX_ecran(){ return min(x1,x2)+5;}    //BEY
  double MinY_ecran(){ return min(y1,y2)+5;}    //BEY

  double MaxX_ecran(){ return max(x1,x2)-5;}    //BEY
  double MaxY_ecran(){ return max(y1,y2)-5;}    //BEY

  double Width_ecran(){ return (max(x1,x2)- min(x1,x2)-10);}   //largeur      //BEY
  double Height_ecran(){ return (max(y1,y2)- min(y1,y2)-10);}    //hauteur    //BEY
*/
  void dessiner();
  void modifier_limites_zones();  //Réduire la zone sélectionée

};
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class TVisualization : public TForm
{
__published:	// Composants gérés par l'EDI
	TPopupMenu *PopupMenu1;
	TMenuItem *Selection1;
	TMenuItem *N1;
	TMenuItem *Vue3D1;
	TMenuItem *Zoom1;
	TMenuItem *ZoomRgion1;
	TMenuItem *ZoomAll1;
	TMenuItem *Rotation1;
	TMenuItem *suivantX1;
	TMenuItem *suivantY1;
	TMenuItem *suivantZ1;
	TMenuItem *rotation3D1;
	TMenuItem *XZ2;
	TMenuItem *YZ2;
	TMenuItem *Projection1;
	TMenuItem *XY1;
	TMenuItem *XZ1;
	TMenuItem *YZ1;
	TMenuItem *Translation1;
	TMenuItem *N3;
	TMenuItem *N2;
	TMenuItem *Volumedevisualisation1;
	TMenuItem *Rglagedelalumire1;
	TMenuItem *N4;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Vue3D1Click(TObject *Sender);
	void __fastcall Zoom1Click(TObject *Sender);
	void __fastcall ZoomRgion1Click(TObject *Sender);
	void __fastcall ZoomAll1Click(TObject *Sender);
	void __fastcall suivantX1Click(TObject *Sender);
	void __fastcall suivantY1Click(TObject *Sender);
	void __fastcall suivantZ1Click(TObject *Sender);
	void __fastcall rotation3D1Click(TObject *Sender);
	void __fastcall XZ2Click(TObject *Sender);
	void __fastcall YZ2Click(TObject *Sender);
	void __fastcall XY1Click(TObject *Sender);
	void __fastcall XZ1Click(TObject *Sender);
	void __fastcall YZ1Click(TObject *Sender);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Translation1Click(TObject *Sender);
	void __fastcall Rglagedelalumire1Click(TObject *Sender);

private:	// Déclarations utilisateur
public:		// Déclarations utilisateur
	__fastcall TVisualization(TComponent* Owner);
	void __fastcall DrawObjects();
	void mettre_a_jour_coordonnees_projetees(){};

	GLdouble nRangex_min;
	GLdouble nRangex_max;
	GLdouble nRangey_min;
	GLdouble nRangey_max;
	GLdouble nRangez_min;
	GLdouble nRangez_max;

 double tx,ty,tz,scalex,scaley,scalez,rotx,roty,rotz,proj_z,proj_y,proj_x;
 float Vision[11];

float m_LightParam[11];

    HDC hdc;
    HGLRC hrc;
	int PixelFormat;
void __fastcall SetPixelFormatDescriptor();
AnsiString AppDir;

	int w, h;

	void dessiner_axes_repere();
    void __fastcall IdleLoop(TObject*, bool&);
	void Coordonnee_3D_a_partir_ecran(int X, int Y);


   Region_Selection zone;
   bool select_p1;
   bool transformation_geometrique;
   void zoomer();
   bool zoom_region, zoom_all;
   void activer_zoom();
   void Zoom_All();
   double minx,miny,minz,maxx,maxy,maxz;
   void Calculer_Limites_Globales_Scene(double minx, double miny, double minz, double maxx, double maxy, double maxz);
};
//---------------------------------------------------------------------------
extern PACKAGE TVisualization *Visualization;
//---------------------------------------------------------------------------
#endif
