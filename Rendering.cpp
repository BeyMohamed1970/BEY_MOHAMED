//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Rendering.h"
#include "Visualization.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRendering *Rendering;
//---------------------------------------------------------------------------
__fastcall TRendering::TRendering(TComponent* Owner)
        : TForm(Owner)
{
int a=1;
int b=1;
a=a+b;

}
//---------------------------------------------------------------------------

void __fastcall TRendering::FormShow(TObject *Sender)
{
Left=Screen->Width - Width;
Top=(Screen->Height - Height)/2;

P1->Caption=EA->Position;
P2->Caption=ED->Position;
P3->Caption=ES->Position;
P4->Caption=X->Position;
P5->Caption=Y->Position;
P6->Caption=Z->Position;
P7->Caption=MA->Position;
P8->Caption=MD->Position;
P9->Caption=MS->Position;
P10->Caption=MB->Position;
P11->Caption=ME->Position;

Rendering->Button1Click(Sender);

}
//--------------------------------------
void TRendering::FormShow_BEY()
{
Left=Screen->Width - Width;
Top=(Screen->Height - Height)/2;

pas=1000;


P1->Caption=EA->Position;
P2->Caption=ED->Position;
P3->Caption=ES->Position;
P4->Caption=X->Position;
P5->Caption=Y->Position;
P6->Caption=Z->Position;
P7->Caption=MA->Position;
P8->Caption=MD->Position;
P9->Caption=MS->Position;
P10->Caption=MB->Position;
P11->Caption=ME->Position;

Edit1->Text=500;

if (Edit1->Text==""){ ShowMessage (" Veuillez introduire la distance.............!!!!!!!!");return;}

distance=Edit1->Text.ToDouble();
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TRendering::XChange(TObject *)
{
  Visualization->Vision[0]=X->Position;
  P4->Caption=X->Position;
  Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void __fastcall TRendering::YChange(TObject *)
{
  Visualization->Vision[1]=Y->Position;
  P5->Caption=Y->Position;
  Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void __fastcall TRendering::ZChange(TObject *)
{
   Visualization->Vision[2]=Z->Position;
   P6->Caption=Z->Position;
  Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void __fastcall TRendering::EAChange(TObject *)
{
  Visualization->Vision[3] = EA->Position;
  P1->Caption=EA->Position;
  Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void __fastcall TRendering::EDChange(TObject *)
{
  Visualization->Vision[4] = ED->Position;
  P2->Caption=ED->Position;
  Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void __fastcall TRendering::ESChange(TObject *)
{
  Visualization->Vision[5] = ES->Position;
  P3->Caption=ES->Position;
  Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void __fastcall TRendering::MAChange(TObject *)
{
  Visualization->Vision[6] = MA->Position;
  P7->Caption=MA->Position;
  Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void __fastcall TRendering::MDChange(TObject *)
{
  Visualization->Vision[7] = MD->Position;
  P8->Caption=MD->Position;
  Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void __fastcall TRendering::MSChange(TObject *)
{
  Visualization->Vision[8] = MS->Position;
  P9->Caption=MS->Position;
  Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void __fastcall TRendering::MBChange(TObject *)
{
  Visualization->Vision[9] = MB->Position;
  P10->Caption=MB->Position;
  Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void __fastcall TRendering::MEChange(TObject *)
{
  Visualization->Vision[10] = ME->Position;
  P11->Caption=ME->Position;
  Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void __fastcall TRendering::BitBtn2Click(TObject *)
{
Close();        
}
//---------------------------------------------------------------------------
void __fastcall TRendering::FormClose(TObject *, TCloseAction &Action)
{
CheckBox1->Checked=false;
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

void __fastcall TRendering::CheckBox1Click(TObject *)
{
Visualization->DrawObjects();
}
//---------------------------------------------------------------------------

void __fastcall TRendering::Button1Click(TObject *)
{
if (Edit1->Text==""){ ShowMessage (" Veuillez introduire la distance.............!!!!!!!!");return;}

distance=Edit1->Text.ToDouble();
Visualization->DrawObjects();

}
//---------------------------------------------------------------------------

//****************************************************************************
void TRendering::reglage_eclairage()
{
distance=Edit1->Text.ToDouble();

double xmin=limite_surface_x_min;
double ymin=limite_surface_y_min;

double xmax=limite_surface_x_max;
double ymax=limite_surface_y_max;

double zmin=limite_surface_z_min;
double zmax=limite_surface_z_max;


//--------------------------------------------------------------
//--------------------------------------------------------------
  float fPos0[] =
  {
		  Visualization->Vision[0],
		  Visualization->Vision[1],
		  Visualization->Vision[2],
		  1.f
  };

  glLightfv(GL_LIGHT0, GL_POSITION, fPos0);

  float f0 = Visualization->Vision[3]/100.f;
  float fAmbient0[4] = { f0, f0, f0, 0.f };
  glLightfv(GL_LIGHT0, GL_AMBIENT, fAmbient0);

  f0 = Visualization->Vision[4]/100.f;
  float fDiffuse0[4] = { f0, f0, f0, 0.f };
  glLightfv(GL_LIGHT0, GL_DIFFUSE, fDiffuse0);


  f0 = Visualization->Vision[5]/100.f;
  float fSpecular0[4] = { f0, f0, f0, 0.f };
  glLightfv(GL_LIGHT0, GL_SPECULAR, fSpecular0);

  f0 = Visualization->Vision[6]/100.f;
  float fAmbMat0[4] = { f0, f0, f0, 0.f };
  glMaterialfv(GL_FRONT, GL_AMBIENT, fAmbMat0);

  f0 = Visualization->Vision[7]/100.f;
  float fDifMat0[4] = { f0, f0, f0, 1.f };
  glMaterialfv(GL_FRONT, GL_DIFFUSE, fDifMat0);

  f0 = Visualization->Vision[8]/100.f;
  float fSpecMat0[4] = { f0, f0, f0, 0.f };
  glMaterialfv(GL_FRONT, GL_SPECULAR, fSpecMat0);

  float fShine0 = 128 * Visualization->Vision[9]/100.f;
  glMaterialf(GL_FRONT, GL_SHININESS, fShine0);

  f0 = Visualization->Vision[10]/100.f;
  float fEmission0[4] = { f0, f0, f0, 0.f };
  glMaterialfv(GL_FRONT, GL_EMISSION, fEmission0);


//--------------------------------------------------------------
  float fPos1[] =
  {
		  (float) distance,
		  (float)(ymin+(ymin+ymax)/2),
		  (float)(zmin+(zmin+zmax)/2),
		  1.f
  };
  glLightfv(GL_LIGHT1, GL_POSITION, fPos1);

  float f1 = Visualization->Vision[3]/100.f;
  float fAmbient1[4] = { f1, f1, f1, 0.f };
  glLightfv(GL_LIGHT1, GL_AMBIENT, fAmbient1);

  f1 = Visualization->Vision[4]/100.f;
  float fDiffuse1[4] = { f1, f1, f1, 0.f };
  glLightfv(GL_LIGHT1, GL_DIFFUSE, fDiffuse1);

  f1 = Visualization->Vision[5]/100.f;
  float fSpecular1[4] = { f1, f1, f1, 0.f };
  glLightfv(GL_LIGHT1, GL_SPECULAR, fSpecular1);

  float fPos2[] =
  {
		  (float)(-distance),
		  (float)(ymin+(ymin+ymax)/2),
		  (float)(zmin+(zmin+zmax)/2),
		  1.f
  };
  glLightfv(GL_LIGHT2, GL_POSITION, fPos2);

  float f2 = Visualization->Vision[3]/100.f;
  float fAmbient2[4] = { f2, f2, f2, 0.f };
  glLightfv(GL_LIGHT2, GL_AMBIENT, fAmbient2);

  f2 = Visualization->Vision[4]/100.f;
  float fDiffuse2[4] = { f2, f2, f2, 0.f };
  glLightfv(GL_LIGHT2, GL_DIFFUSE, fDiffuse2);

  f2 = Visualization->Vision[5]/100.f;
  float fSpecular2[4] = { f2, f2, f2, 0.f };
  glLightfv(GL_LIGHT2, GL_SPECULAR, fSpecular2);

  float fPos3[] =
  {
		  (float)(xmin+(xmin+xmax)/2),
		  (float)(-distance),
		  (float)(zmin+(zmin+zmax)/2),
          1.f
  };
  glLightfv(GL_LIGHT3, GL_POSITION, fPos3);

  float f3 = Visualization->Vision[3]/100.f;
  float fAmbient3[4] = { f3, f3, f3, 0.f };
  glLightfv(GL_LIGHT3, GL_AMBIENT, fAmbient3);

  f3 = Visualization->Vision[4]/100.f;
  float fDiffuse3[4] = { f3, f3, f3, 0.f };
  glLightfv(GL_LIGHT3, GL_DIFFUSE, fDiffuse3);

  f3 = Visualization->Vision[5]/100.f;
  float fSpecular3[4] = { f3, f3, f3, 0.f };
  glLightfv(GL_LIGHT3, GL_SPECULAR, fSpecular3);

  float fPos4[] =
  {
		  (float)(xmin+(xmin+xmax)/2),
		  (float)(distance),
		  (float)(zmin+(zmin+zmax)/2),
          1.f
  };
  glLightfv(GL_LIGHT4, GL_POSITION, fPos4);

  float f4 = Visualization->Vision[3]/100.f;
  float fAmbient4[4] = { f4, f4, f4, 0.f };
  glLightfv(GL_LIGHT4, GL_AMBIENT, fAmbient4);

  f4 = Visualization->Vision[4]/100.f;
  float fDiffuse4[4] = { f4, f4, f4, 0.f };
  glLightfv(GL_LIGHT4, GL_DIFFUSE, fDiffuse4);

  f4 = Visualization->Vision[5]/100.f;
  float fSpecular4[4] = { f4, f4, f4, 0.f };
  glLightfv(GL_LIGHT4, GL_SPECULAR, fSpecular4);

  float fPos5[] =
  {
		  (float)(xmin+(xmin+xmax)/2),
		  (float)(ymin+(ymin+ymax)/2),
		  (float)(-distance),
          1.f
  };
  glLightfv(GL_LIGHT5, GL_POSITION, fPos5);

  float f5 = Visualization->Vision[3]/100.f;
  float fAmbient5[4] = { f5, f5, f5, 0.f };
  glLightfv(GL_LIGHT5, GL_AMBIENT, fAmbient5);

  f5 = Visualization->Vision[4]/100.f;
  float fDiffuse5[4] = { f5, f5, f5, 0.f };
  glLightfv(GL_LIGHT5, GL_DIFFUSE, fDiffuse5);

  f5 = Visualization->Vision[5]/100.f;
  float fSpecular5[4] = { f5, f5, f5, 0.f };
  glLightfv(GL_LIGHT5, GL_SPECULAR, fSpecular5);

glEnable(GL_LIGHTING);

if(Rendering->CheckBox7->Checked)  glEnable(GL_LIGHT0); else glDisable(GL_LIGHT0);
if(Rendering->CheckBox2->Checked)  glEnable(GL_LIGHT1); else glDisable(GL_LIGHT1);
if(Rendering->CheckBox3->Checked)  glEnable(GL_LIGHT2); else glDisable(GL_LIGHT2);
if(Rendering->CheckBox4->Checked)  glEnable(GL_LIGHT3); else glDisable(GL_LIGHT3);
if(Rendering->CheckBox6->Checked)  glEnable(GL_LIGHT4); else glDisable(GL_LIGHT4);
if(Rendering->CheckBox5->Checked)  glEnable(GL_LIGHT5); else glDisable(GL_LIGHT5);

glEnable(GL_COLOR_MATERIAL);
glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
glShadeModel(GL_SMOOTH);
glEnable(GL_DEPTH_TEST);

Rendering->lancer_parametrage(Sender);
}
//******************************************************************************


void __fastcall TRendering::Button2Click(TObject *)
{

X->Position=(X->Min+X->Max)/2;
Y->Position=(Y->Min+Y->Max)/2;
Z->Position=Z->Max;

Visualization->DrawObjects();
}
//---------------------------------------------------------------------------
void TRendering::activation_lumieres()
{
  Visualization->Vision[3] = EA->Position;
  P1->Caption=EA->Position;

  Visualization->Vision[4] = ED->Position;
  P2->Caption=ED->Position;

  Visualization->Vision[5] = ES->Position;
  P3->Caption=ES->Position;

  Visualization->Vision[0]=X->Position;
  P4->Caption=X->Position;
  
  Visualization->Vision[1]=Y->Position;
  P5->Caption=Y->Position;

  Visualization->Vision[6] = MA->Position;
  P7->Caption=MA->Position;

  Visualization->Vision[7] = MD->Position;
  P8->Caption=MD->Position;

  Visualization->Vision[8] = MS->Position;
  P9->Caption=MS->Position;

  Visualization->Vision[9] = MB->Position;
  P10->Caption=MB->Position;

  Visualization->Vision[10] = ME->Position;
  P11->Caption=ME->Position;

  
  Visualization->DrawObjects();

}
//-----------------------------------------
void TRendering::initialiser_limites()
{
		limite_surface_x_min=1e10;
		limite_surface_y_min=1e10;
		limite_surface_x_max=-1e10;
		limite_surface_y_max=-1e10;
		limite_surface_z_min=1e10;
		limite_surface_z_max=-1e10;
        }

//-----------------------------------------
void __fastcall TRendering::Button3Click(TObject *)
{
if(ComboBox1->Text=="Plastique noir")
{
  Visualization->Vision[6] = (float)(0.*100);
  Visualization->Vision[7] = (float)(0.01*100);
  Visualization->Vision[8] = (float)(0.5*100);
  Visualization->Vision[9] = (float)(32*100/128.);
  Visualization->Vision[10] = 0;
}

if(ComboBox1->Text=="Cuivre")
{
  Visualization->Vision[6] = (float)(0.329412*100);
  Visualization->Vision[7] = (float)(0.780392*100);
  Visualization->Vision[8] = (float)(0.992157*100);
  Visualization->Vision[9] = (float)(27.8974*100/128.);
  Visualization->Vision[10] = 0;
}

if(ComboBox1->Text=="Bronze")
{
  Visualization->Vision[6] = (float)(0.2125*100);
  Visualization->Vision[7] = (float)(0.714*100);
  Visualization->Vision[8] = (float)(0.393548*100);
  Visualization->Vision[9] = (float)(25.6*100/128.);
  Visualization->Vision[10] = 0;
}

if(ComboBox1->Text=="Chrome")
{
  Visualization->Vision[6] = (float)(0.25*100);
  Visualization->Vision[7] = (float)(0.4*100);
  Visualization->Vision[8] = (float)(0.774597*100);
  Visualization->Vision[9] = (float)(76.8*100/128.);
  Visualization->Vision[10] = 0;
}

if(ComboBox1->Text=="Cuivre rouge")
{
  Visualization->Vision[6] = (float)(0.19125*100);
  Visualization->Vision[7] = (float)(0.7038*100);
  Visualization->Vision[8] = (float)(0.256777*100);
  Visualization->Vision[9] = (float)(12.8*100/128.);
  Visualization->Vision[10] = 0;
}

if(ComboBox1->Text=="Or")
{
  Visualization->Vision[6] = (float)(0.24725*100);
  Visualization->Vision[7] = (float)(0.75164*100);
  Visualization->Vision[8] = (float)(0.628281*100);
  Visualization->Vision[9] = (float)(51.2*100/128.);
  Visualization->Vision[10] = 0;
}

if(ComboBox1->Text=="Étain")
{
  Visualization->Vision[6] = (float)(0.10588*100);
  Visualization->Vision[7] = (float)(0.427451*100);
  Visualization->Vision[8] = (float)(0.3333*100);
  Visualization->Vision[9] = (float)(9.84615*100/128.);
  Visualization->Vision[10] = 0;
}

if(ComboBox1->Text=="Argent")
{
  Visualization->Vision[6] = (float)(0.19225*100);
  Visualization->Vision[7] = (float)(0.50754*100);
  Visualization->Vision[8] = (float)(0.508273*100);
  Visualization->Vision[9] = (float)(51.2*100/128.);
  Visualization->Vision[10] = 0;
}

if(ComboBox1->Text=="Argent brillant")
{
  Visualization->Vision[6] = (float)(0.23125*100);
  Visualization->Vision[7] = (float)(0.2775*100);
  Visualization->Vision[8] = (float)(0.773911*100);
  Visualization->Vision[9] = (float)(89.6*100/128.);
  Visualization->Vision[10] = 0;
}


MA->Position=(int)Visualization->Vision[6];
MD->Position=(int)Visualization->Vision[7] ;
MS->Position=(int)Visualization->Vision[8] ;
MB->Position=(int)Visualization->Vision[9] ;
ME->Position=(int)Visualization->Vision[10] ;

P7->Caption=MA->Position;
P8->Caption=MD->Position;
P9->Caption=MS->Position;
P10->Caption=MB->Position;
P11->Caption=ME->Position;


Visualization->DrawObjects();
}
//---------------------------------------------------------------------------


void TRendering::lancer_parametrage(TObject *Sender)
{
//---------------------------------------------------------------------------
  Visualization->Vision[0]=X->Position;
  P4->Caption=X->Position;

  Visualization->Vision[1]=Y->Position;
  P5->Caption=Y->Position;

   Visualization->Vision[2]=Z->Position;
   P6->Caption=Z->Position;

  Visualization->Vision[3] = EA->Position;
  P1->Caption=EA->Position;

  Visualization->Vision[4] = ED->Position;
  P2->Caption=ED->Position;

  Visualization->Vision[5] = ES->Position;
  P3->Caption=ES->Position;

  Visualization->Vision[6] = MA->Position;
  P7->Caption=MA->Position;

  Visualization->Vision[7] = MD->Position;
  P8->Caption=MD->Position;

  Visualization->Vision[8] = MS->Position;
  P9->Caption=MS->Position;

  Visualization->Vision[9] = MB->Position;
  P10->Caption=MB->Position;

  Visualization->Vision[10] = ME->Position;
  P11->Caption=ME->Position;
//---------------------------------------------------------------------------
}



