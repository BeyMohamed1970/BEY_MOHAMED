//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Visualization.h"
#include "Rendering.h"
#include "Point_Clouds_Import.h"
#include "Adaptive_Triangulation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVisualization *Visualization;

double pi=acos((double)-1);

//---------------------------------------------------------------------------
__fastcall TVisualization::TVisualization(TComponent* Owner)
	: TForm(Owner)
{
  Application->OnIdle = IdleLoop;
}
//---------------------------------------------------------------------------
void __fastcall TVisualization::FormCreate(TObject *Sender)
{

	m_LightParam[0] = 0;
	m_LightParam[1] = 0;
	m_LightParam[2] = 10000;
	m_LightParam[3] = 15;
	m_LightParam[4] = 70;
	m_LightParam[5] = 100;
	m_LightParam[6] = 100;
	m_LightParam[7] = 100;
	m_LightParam[8] = 40;
	m_LightParam[9] = 70;
	m_LightParam[10] = 0;

   hdc = GetDC(Handle);

   SetPixelFormatDescriptor();
   hrc = wglCreateContext(hdc);
   if(hrc == NULL)
		ShowMessage(":-)~ hrc == NULL");
   if(wglMakeCurrent(hdc, hrc) == false)
		ShowMessage("Could not MakeCurrent");

   glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

   glColorMaterial(GL_FRONT, GL_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

   glEnable(GL_NORMALIZE);

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------//---------------------------------------------------------------------------
void __fastcall TVisualization::SetPixelFormatDescriptor()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0,0,0,0,0,0,
		0,0,
		0,0,0,0,0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,
	};
	PixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, PixelFormat, &pfd);

}
//---------------------------------------------------------------------------
void __fastcall TVisualization::FormShow(TObject *Sender)
{
transformation_geometrique=true;
zoom_region=false;
zoom_all=false;

 AnsiString exeFile=Application->ExeName;
 AnsiString exePath=ExtractFilePath(exeFile);
 AppDir=exePath;

//---------------------------------------
Visualization->transformation_geometrique=true;

Height= Screen->Height;
Left=0;
Top=0;


Rendering->X->Min=-5000;
Rendering->X->Max=5000;

Rendering->Y->Min=-5000;
Rendering->Y->Max=5000;

Rendering->Z->Min=-5000;
Rendering->Z->Max=5000;

Rendering->X->Position=0;
Rendering->P4->Caption=Rendering->X->Position;

Rendering->Y->Position=0;
Rendering->P5->Caption=Rendering->Y->Position;

Rendering->Z->Position=Rendering->Z->Max/2;
Rendering->P6->Caption=Rendering->Z->Position;

Rendering->EA->Position=7;
Rendering->P1->Caption=Rendering->EA->Position;

Rendering->ED->Position=20;
Rendering->P2->Caption=Rendering->ED->Position;

Rendering->ES->Position=100;
Rendering->P3->Caption=Rendering->ES->Position;

Rendering->MA->Position=0;
Rendering->P7->Caption=Rendering->MA->Position;

Rendering->MD->Position=0;
Rendering->P8->Caption=Rendering->MD->Position;

Rendering->MS->Position=30;
Rendering->P9->Caption=Rendering->MS->Position;

Rendering->MB->Position=50;
Rendering->P10->Caption=Rendering->MB->Position;

Rendering->ME->Position=0;
Rendering->P11->Caption=Rendering->ME->Position;

Rendering->Edit1->Text=Rendering->Z->Position;

Rendering->Button1Click(Sender);

nRangex_min = -100.0;
nRangex_max = 100.0;
nRangey_min = -100.0;
nRangey_max = 100.0;
nRangez_min = -10000.0;
nRangez_max = 10000.0;

tx=0,ty=0,tz=0,scalex=1,scaley=1,scalez=1,rotx=0,roty=0,rotz=0,proj_z=1,proj_y=0,proj_x=0;

  Visualization->Vision[3] = 15;
  Visualization->Vision[4] = 70;
  Visualization->Vision[5] = 0;
  Visualization->Vision[6] = 100;
  Visualization->Vision[7] = 100;
  Visualization->Vision[8] = 40;
  Visualization->Vision[9] = 70;
  Visualization->Vision[10] = 0;


 Point_Clouds_Import->Show();
}
//---------------------------------------------------------------------------
//-------------------------------------------------------------------------
void __fastcall TVisualization::DrawObjects()
{

	if(wglMakeCurrent(Visualization->hdc,Visualization->hrc) == false)
		ShowMessage("Could not MakeCurrent");

	double Mx_1[16] = {0.,0.,1.,0., 1.,0.,0.,0., 0.,1.,0.,0., 0.,0.,0.,1.};
	double My_1[16] = {1.,0.,0.,0., 0.,0.,1.,0., 0.,1.,0.,0., 0.,0.,0.,1.};
	double Mz_1[16] = {1.,0.,0.,0., 0.,1.,0.,0., 0.,0.,1.,0., 0.,0.,0.,1.};

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	w = ClientWidth;
	h = ClientHeight;

	if (h == 0) h = 1;

	glViewport(0, 0, w, h);

	glDepthRange(0.,1.);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if (w <= h)
		glOrtho (Visualization->scalex*nRangex_min, Visualization->scalex*nRangex_max, Visualization->scalex*nRangey_min*h/w, Visualization->scalex*nRangey_max*h/w, nRangez_min,nRangez_max);
	else
	glOrtho (Visualization->scalex*nRangex_min*w/h, Visualization->scalex*nRangex_max*w/h, Visualization->scalex*nRangey_min, Visualization->scalex*nRangey_max, nRangez_min, nRangez_max);

	glTranslated(Visualization->tx,Visualization->ty,Visualization->tz);

	glRotated(Visualization->rotx,1.,0.,0.);
	glRotated(Visualization->roty,0.,1.,0.);
	glRotated(Visualization->rotz,0.,0.,1.);

	if(proj_z==1)
	 {
	  glMultMatrixd(Mz_1);
	 }

	if(Visualization->proj_y==1)
     {
      glMultMatrixd(My_1);
     }

	if(Visualization->proj_x==1)
	 {
      glMultMatrixd(Mx_1);
     }

//------------------------------------------------------
    dessiner_axes_repere();

   if(Point_Clouds_Import->CheckBox4->Checked) Point_Clouds_Import->NUAGE_PTS_BEY.dessiner_nuage_pts();
   if(Point_Clouds_Import->CheckBox5->Checked) Point_Clouds_Import->NUAGE_PTS_BEY.dessiner_brut_min();


  if(Adaptive_Triangulation->CheckBox1->Checked)
  {
  for (int i=0;i<Adaptive_Triangulation->nbre_cellule_y;i++)
	  for (int j=0;j<Adaptive_Triangulation->nbre_cellule_x;j++)
	   Point_Clouds_Import->cellule_points_BEY[i][j].dessiner_cellules();
  }

  if(Adaptive_Triangulation->CheckBox2->Checked) Adaptive_Triangulation->dessiner_toutes_listes_points_vector();

  if(Adaptive_Triangulation->CheckBox21->Checked) Point_Clouds_Import->NUAGE_PTS_BEY.dessiner_nuage_pts();
  if(Adaptive_Triangulation->CheckBox24->Checked) Adaptive_Triangulation->dessiner_triangle_BEY();
  if(Adaptive_Triangulation->CheckBox27->Checked) Adaptive_Triangulation->dessiner_triangle_3D_BEY();
  if(Adaptive_Triangulation->CheckBox26->Checked) {Adaptive_Triangulation->dessiner_triangle_3D_f_BEY();Adaptive_Triangulation->dessiner_triangle_3D_Filtres_BEY();}
  if(Adaptive_Triangulation->CheckBox30->Checked) Adaptive_Triangulation->dessiner_pts_proches_sommets_triangle_BEY();

  if(Adaptive_Triangulation->CheckBox29->Checked) Point_Clouds_Import->NUAGE_PTS_BEY.dessiner_brut_min();
  if(Adaptive_Triangulation->CheckBox22->Checked) Adaptive_Triangulation->dessiner_points_triangle_BEY();
  if(Adaptive_Triangulation->CheckBox23->Checked) {Adaptive_Triangulation->dessiner_points_triangle_nf_BEY();Adaptive_Triangulation->dessiner_points_triangle_filtres_BEY();}
  if(Adaptive_Triangulation->CheckBox25->Checked) Adaptive_Triangulation->dessiner_points_triangle_f_BEY();
  if(Adaptive_Triangulation->CheckBox47->Checked) Adaptive_Triangulation->dessiner_pts_proches_milieux_triangle_BEY();

  if(Adaptive_Triangulation->CheckBox48->Checked || Adaptive_Triangulation->CheckBox49->Checked || Adaptive_Triangulation->CheckBox50->Checked || Adaptive_Triangulation->CheckBox52->Checked)Adaptive_Triangulation->dessiner_triangle_3D_Elimination_BEY();

//---------------------------------------------------------------------------
if(Visualization->select_p1==true)
{
	glLoadIdentity();

	if (w <= h)
		glOrtho (0, h, 0, w, nRangez_min,nRangez_max);
	else
		glOrtho (0, w, 0, h, nRangez_min, nRangez_max);

  Visualization->zone.dessiner();
}
//---------------------------------------------------------------------------

 SwapBuffers(hdc);
}
//---------------------------------------------------------------------------
void TVisualization::dessiner_axes_repere()
{
   double axe=50.;

   glLineWidth(1);

   glColor3d(1, 0, 0);

	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(axe,0,0);
   glEnd();

   glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(0,axe,0);
   glEnd();

   glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(0,0,axe);
   glEnd();

   glColor3d(0, 0, 1);

   glRasterPos3d (axe+2,0.,0.);
   glBitmap (8, 10, 0, 0, 10, 0, X_maj);
   glFlush();

   glRasterPos3d (0.,axe+2,0.);
   glBitmap (8, 10, 0, 0, 10, 0, Y_maj);
   glFlush();

   glRasterPos3d (0.,0. ,axe+2);
   glBitmap (8, 10, 0, 0, 10, 0, Z_maj);
   glFlush();
}

//---------------------------------------------------------------------------
void __fastcall TVisualization::IdleLoop(TObject*, bool& done)
{

  if(Point_Clouds_Import->Visible)
  {
  Point_Clouds_Import->Height= Screen->Height-35;
  Point_Clouds_Import->Left=Screen->Width - Point_Clouds_Import->Width-5;
  Point_Clouds_Import->Top=0;

  Visualization->Height= Screen->Height-35;
  Visualization->Width = Screen->Width - Point_Clouds_Import->Width;
  Visualization->Left=0;
  Visualization->Top=0;
  }


  if(Adaptive_Triangulation->Visible)
  {
  Adaptive_Triangulation->Height= Screen->Height-35;
  Adaptive_Triangulation->Left=Screen->Width - Adaptive_Triangulation->Width-5;
  Adaptive_Triangulation->Top=0;


  Visualization->Height= Screen->Height-35;
  Visualization->Width = Screen->Width - Adaptive_Triangulation->Width;
  Visualization->Left=0;
  Visualization->Top=0;
  }


  done = false;
  DrawObjects();
}
//---------------------------------------------------------------------------//---------------------------------------------------------------------------

void __fastcall TVisualization::Vue3D1Click(TObject *Sender)
{
  if (Selection1->Checked)
  {
	 selection=Vue3D;
	 rotx=-60;
	 roty=0;
	 rotz=220;
	 proj_z=0;
	 Visualization->proj_x=0;
	 Visualization->proj_y=0;

	 Visualization->DrawObjects();
  }
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::Zoom1Click(TObject *Sender)
{
selection=Zoom;
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::ZoomRgion1Click(TObject *Sender)
{
Visualization->zoom_region=true;
Visualization->select_p1=false;
transformation_geometrique=false;
Visualization->mettre_a_jour_coordonnees_projetees();

}
//---------------------------------------------------------------------------

void __fastcall TVisualization::ZoomAll1Click(TObject *Sender)
{
Visualization->zoom_all=true;
Visualization->Zoom_All();
Visualization->mettre_a_jour_coordonnees_projetees();
Visualization->zoom_all=false;
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::suivantX1Click(TObject *Sender)
{
selection=Rotx;
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::suivantY1Click(TObject *Sender)
{
selection=Roty;
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::suivantZ1Click(TObject *Sender)
{
selection=Rotz;
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::rotation3D1Click(TObject *Sender)
{
selection=Rotxy;
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::XZ2Click(TObject *Sender)
{
selection=Rotxz;
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::YZ2Click(TObject *Sender)
{
selection=Rotyz;
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::XY1Click(TObject *Sender)
{
  if (Selection1->Checked)
  {
	 selection=projxy;
	 rotx=0;
	 roty=0;
	 rotz=0;
	 proj_z=1;
	 Visualization->proj_x=0;
	 Visualization->proj_y=0;
	 Visualization->DrawObjects();
  }
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::XZ1Click(TObject *Sender)
{
  if (Selection1->Checked)
  {
	 selection=projxz;
	 rotx=0;
	 roty=0;
	 rotz=0;
	 proj_z=0;
	 Visualization->proj_x=0;
	 Visualization->proj_y=1;
	 Visualization->DrawObjects();
  }
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::YZ1Click(TObject *Sender)
{
  if (Selection1->Checked)
  {
	 selection=projyz;
	 rotx=0;
	 roty=0;
	 rotz=0;
	 proj_z=0;
	 Visualization->proj_x=1;
	 Visualization->proj_y=0;
	 Visualization->DrawObjects();
  }
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
MouseButton=Button;
EtatButton=MB_DOWN;

if(MouseButton==mbLeft && Visualization->zoom_region==true) //Zoom région
{
	Visualization->zone.SetX2(X);
	Visualization->zone.SetY2(Visualization->ClientHeight-Y);

	if(Visualization->select_p1==false)
	{
	Visualization->select_p1=true;
	Visualization->zone.SetX1(X);
	Visualization->zone.SetY1(Visualization->ClientHeight-Y);
	Visualization->transformation_geometrique=false;
	}
	else
	{
	Visualization->select_p1=false;
	Visualization->transformation_geometrique=true;


	 if (Visualization->zoom_region==true)
	 {
	   Visualization->zoom_region=false;
	   Visualization->zoomer();
	   Visualization->mettre_a_jour_coordonnees_projetees();
	 }

	}
}

mposx=X;
mposy=Y;
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
if(Visualization->select_p1==true && Visualization->zoom_region==true)
{
	Visualization->zone.SetX2(X);
	Visualization->zone.SetY2(Visualization->ClientHeight-Y);

	DrawObjects();
}

if(Visualization->transformation_geometrique==false)
{
selection=rien;
}

if(selection!=rien && Visualization->transformation_geometrique==true)
{
Visualization->zoom_region = false;
}

Coordonnee_3D_a_partir_ecran(X, Visualization->ClientHeight-Y);

if (MouseButton==mbLeft && EtatButton==MB_DOWN && Selection1->Checked)
 switch (selection)
  {
  case Rotx :
			{
			proj_z=0;Visualization->proj_x=0;Visualization->proj_y=0;rotx+=Y-mposy;DrawObjects();
			break;
			}

  case Roty :
			{
			proj_z=0;Visualization->proj_x=0;Visualization->proj_y=0;roty+=Y-mposy;DrawObjects();
			break;
			}

  case Rotz :
			{
			proj_z=0;Visualization->proj_x=0;Visualization->proj_y=0;rotz+=Y-mposy;DrawObjects();
			break;
			}

  case Rotxy:
			{
			Visualization->proj_z=0;Visualization->proj_x=0;Visualization->proj_y=0;Visualization->rotx+=X-mposx;Visualization->roty+=Y-mposy;DrawObjects();
			break;
			}

  case Rotxz:
			{
			Visualization->proj_z=0;Visualization->proj_x=0;Visualization->proj_y=0;Visualization->rotx+=X-mposx;Visualization->rotz+=Y-mposy;DrawObjects();
			break;
			}

  case Rotyz:
			{
			Visualization->proj_z=0;Visualization->proj_x=0;Visualization->proj_y=0;Visualization->rotz+=X-mposx;Visualization->roty+=Y-mposy;DrawObjects();
			break;
			}

  case Zoom :
			{
			Visualization->scalex+=(Y-mposy)*0.005;
			if(Visualization->scalex<=0)Visualization->scalex=0;
			Visualization->scaley=Visualization->scalex;
			Visualization->scalez=Visualization->scalex;
			DrawObjects();
			break;
			}

  case translation :
			{
			Visualization->tx+=(X-mposx)*0.4;
			Visualization->ty-=(Y-mposy)*0.4;
			DrawObjects();break;
			}

  }

 mposx=X;
 mposy=Y;
}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TVisualization::Coordonnee_3D_a_partir_ecran(int X, int Y)
{
	GLdouble modelMatrix[16];
    GLdouble projMatrix[16];
    GLint    viewport[4];


	glGetDoublev  (GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev  (GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv (GL_VIEWPORT, viewport);

double Z;
GLdouble posX, posY, posZ;
    glReadPixels( X, Y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &Z ); // on lit dans le Zbuffer
    gluUnProject( X, Y, Z, modelMatrix, projMatrix, viewport, &posX, &posY, &posZ); // on récupère les données

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void __fastcall TVisualization::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	MouseButton=Button;
	EtatButton=MB_UP;

	if(MouseButton==mbLeft && (selection==Rotx || selection==Roty || selection==Rotz || selection==Rotxy || selection==Rotxz || selection==Rotyz || selection==Zoom || selection==translation))
	{
	Visualization->mettre_a_jour_coordonnees_projetees();
	}
}
//---------------------------------------------------------------------------

void __fastcall TVisualization::Translation1Click(TObject *Sender)
{
selection=translation;
}
//---------------------------------------------------------------------------


void __fastcall TVisualization::Rglagedelalumire1Click(TObject *Sender)
{
Rendering->Show();
}
//---------------------------------------------------------------------------
 //----------------------------------------------------------
  void Region_Selection::dessiner()
  {
   glLineWidth((float)4);

   glEnable(GL_LINE_STIPPLE);
   glLineStipple(1, 0xFC3F);

//   glColor3d(0.5,1,0.5);
   glColor3d(1,1,1);//BEY
   glBegin(GL_LINE_LOOP);
      glVertex3d(x1,y1,0);
      glVertex3d(x1,y2,0);
      glVertex3d(x2,y2,0);
      glVertex3d(x2,y1,0);
   glEnd();

   glDisable(GL_LINE_STIPPLE);
  }

//--------------------------------------------------------------
//---------------------------------------------------------------------------
 void Region_Selection::modifier_limites_zones()
 {
  double xmin=min(x1, x2);
  double xmax=max(x1, x2);

  double ymin=min(y1, y2);
  double ymax=max(y1, y2);

  x1=xmin+20;
  x2=xmax-20;

  y1=ymin+20;
  y2=ymax-20;
 }
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TVisualization::zoomer()
{
         double W=Visualization->ClientWidth;
         double H=Visualization->ClientHeight;

		double min_w_h_ecran=min(H,W);
        double w_reel=(Visualization->nRangex_max-Visualization->nRangex_min)*W/min_w_h_ecran;
		double h_reel=(Visualization->nRangey_max-Visualization->nRangey_min)*H/min_w_h_ecran;


        double minx=(zone.MinX_ecran()*w_reel*Visualization->scalex/W)+(Visualization->nRangex_min*W*Visualization->scalex/min_w_h_ecran)-Visualization->tx;
        double maxx=(zone.MaxX_ecran()*w_reel*Visualization->scalex/W)+(Visualization->nRangex_min*W*Visualization->scalex/min_w_h_ecran)-Visualization->tx;

        double miny=(zone.MinY_ecran()*h_reel*Visualization->scalex/H)+(Visualization->nRangey_min*H*Visualization->scalex/min_w_h_ecran)-Visualization->ty;
        double maxy=(zone.MaxY_ecran()*h_reel*Visualization->scalex/H)+(Visualization->nRangey_min*H*Visualization->scalex/min_w_h_ecran)-Visualization->ty;


    if(W!=0 && H!=0)
	{
      double ratio=W/H;

         double h=maxy-miny;
         double w=maxx-minx;

	   if(W <= H)
       {

           maxy=maxy*ratio;
           miny=miny*ratio;

       }
       else
	   {

		   maxx=maxx/ratio;
		   minx=minx/ratio;

	   }

		 h=maxy-miny;
		 w=maxx-minx;

	   if(w<h)
	   {
			double rajout_x=(h-w)/2;
//			double rajout_x=(h-w)/10.;//BEY

			minx=minx - rajout_x;
			maxx=maxx + rajout_x;

	   }
	   else if (w>h)
	   {
			double rajout_y=(w-h)/2;
//			double rajout_y=(w-h)/10.;//BEY

			miny=miny - rajout_y;
			maxy=maxy + rajout_y;
	   }

	}

//	  double extension=1;
	  double extension=0; //BEY

	  Visualization->nRangex_min=minx-extension;
	  Visualization->nRangex_max=maxx+extension;
	  Visualization->nRangey_min=miny-extension;
	  Visualization->nRangey_max=maxy+extension;

	  Visualization->tx=Visualization->ty=Visualization->tz=0;
	  Visualization->scalex=1;
	  Visualization->DrawObjects();

}

//---------------------------------------------------------------------------
void TVisualization::activer_zoom()
{
//if(CheckBox8->Checked || CheckBox16->Checked)
if(Visualization->zoom_region==true)// || Visualization->zoom_all==true)
{
select_p1=false;
Visualization->transformation_geometrique=false;
Visualization->mettre_a_jour_coordonnees_projetees();
}
}
//-------------------------------------------------------
//---------------------------------------------------------------------------
 void TVisualization::Zoom_All()
 {
	double w=0;
    double h=0;
    double rajout_x=0;
    double rajout_y=0;

	double W=Visualization->ClientWidth;
    double H=Visualization->ClientHeight;
/*
    int i;
    double w=0;
    double h=0;
    double rajout_x=0;
    double rajout_y=0;


	double minx=1e10;
	double maxx=-1e10;

	double miny=1e10;
	double maxy=-1e10;

	double minz=1e10;
	double maxz=-1e10;

     if(CheckBox1->Checked || CheckBox17->Checked)
      for(i=0;i<Nombre_Sommets;i++)
      {
	   minx=min(minx,vertex[i].GetX());
       miny=min(miny,vertex[i].GetY());
       minz=min(minz,vertex[i].GetZ());

       maxx=max(maxx,vertex[i].GetX());
       maxy=max(maxy,vertex[i].GetY());
       maxz=max(maxz,vertex[i].GetZ());

      }

      if(CheckBox3->Checked || CheckBox17->Checked)
      for(i=0;i<Nombre_Segments;i++)
      {
       minx=min(min(minx,segment[i].GetP1().GetX()),segment[i].GetP2().GetX());
	   miny=min(min(miny,segment[i].GetP1().GetY()),segment[i].GetP2().GetY());
       minz=min(min(minz,segment[i].GetP1().GetZ()),segment[i].GetP2().GetZ());

       maxx=max(max(maxx,segment[i].GetP1().GetX()),segment[i].GetP2().GetX());
       maxy=max(max(maxy,segment[i].GetP1().GetY()),segment[i].GetP2().GetY());
       maxz=max(max(maxz,segment[i].GetP1().GetZ()),segment[i].GetP2().GetZ());
      }

      if(CheckBox4->Checked || CheckBox17->Checked)
      for(i=0;i<Nombre_Triangles;i++)
      {
       minx=min(min(minx,triangle[i].GetP1().GetX()),triangle[i].GetP2().GetX());
       minx=min(minx,triangle[i].GetP3().GetX());

       miny=min(min(miny,triangle[i].GetP1().GetY()),triangle[i].GetP2().GetY());
       miny=min(miny,triangle[i].GetP3().GetY());

       minz=min(min(minz,triangle[i].GetP1().GetZ()),triangle[i].GetP2().GetZ());
       minz=min(minz,triangle[i].GetP3().GetZ());

       maxx=max(max(maxx,triangle[i].GetP1().GetX()),triangle[i].GetP2().GetX());
       maxx=max(maxx,triangle[i].GetP3().GetX());

       maxy=max(max(maxy,triangle[i].GetP1().GetY()),triangle[i].GetP2().GetY());
       maxy=max(maxy,triangle[i].GetP3().GetY());

       maxz=max(max(maxz,triangle[i].GetP1().GetZ()),triangle[i].GetP2().GetZ());
	   maxz=max(maxz,triangle[i].GetP3().GetZ());

      }

      if(CheckBox24->Checked || CheckBox32->Checked || CheckBox25->Checked || CheckBox31->Checked || CheckBox33->Checked || CheckBox30->Checked)
      for(i=0;i<Nombre_Objets;i++)
      {
       if(object[i].GetVisible()==false)continue;
       maxx=max(object[i].GetXmax_reel(),maxx);
       minx=min(object[i].GetXmin_reel(),minx);

       maxy=max(object[i].GetYmax_reel(),maxy);
       miny=min(object[i].GetYmin_reel(),miny);

       maxz=max(object[i].GetZmax_reel(),maxz);
       minz=min(object[i].GetZmin_reel(),minz);

      }

//------------------------------------------------------------------------------

if(Form6000->operation_zoom_all==true)
{
 minx=min(minx,Form6000->liste_points_STL_finition->getx_min());
 miny=min(miny,Form6000->liste_points_STL_finition->gety_min());
 minz=min(minz,Form6000->liste_points_STL_finition->getz_min());

 maxx=max(maxx,Form6000->liste_points_STL_finition->getx_max());
 maxy=max(maxy,Form6000->liste_points_STL_finition->gety_max());
 maxz=max(maxz,Form6000->liste_points_STL_finition->getz_max());
}
*/

//------------------------------------------------------------------------------

          double minx1,miny1,minz1,maxx1,maxy1,maxz1;

          minx1=minx;
          miny1=miny;
          minz1=minz;

		  maxx1=maxx;
          maxy1=maxy;
          maxz1=maxz;

	 if(Visualization->proj_x==1)//projection sur le plan YZ
	 {

      double xmin=minx1;
      double xmax=maxx1;

      minx1=miny;
      maxx1=maxy;

      miny1=minz;
      maxy1=maxz;

      minz1=xmin;
	  maxz1=xmax;
	 }


	 if(Visualization->proj_y==1) //projection sur le plan XZ
	 {

	  double ymin=miny1;
	  double ymax=maxy1;

	  miny1=minz;
	  maxy1=maxz;

	  minz1=ymin;
	  maxz1=ymax;
	 }

       double x1,x2,x3,x4;
       double y1,y2,y3,y4;
       double z1,z2,z3,z4;
       //******************Rotation Z
	   if(Visualization->rotz!=0)
	   {
		x1=minx1*cos(Visualization->rotz*pi/180) - miny1*sin(Visualization->rotz*pi/180);
		y1=minx1*sin(Visualization->rotz*pi/180) + miny1*cos(Visualization->rotz*pi/180);

		x2=maxx1*cos(Visualization->rotz*pi/180) - miny1*sin(Visualization->rotz*pi/180);
		y2=maxx1*sin(Visualization->rotz*pi/180) + miny1*cos(Visualization->rotz*pi/180);

        x3=maxx1*cos(Visualization->rotz*pi/180) - maxy1*sin(Visualization->rotz*pi/180);
		y3=maxx1*sin(Visualization->rotz*pi/180) + maxy1*cos(Visualization->rotz*pi/180);

		x4=minx1*cos(Visualization->rotz*pi/180) - maxy1*sin(Visualization->rotz*pi/180);
		y4=minx1*sin(Visualization->rotz*pi/180) + maxy1*cos(Visualization->rotz*pi/180);

	   minx1=min(x1,min(x2,min(x3,x4)));
       miny1=min(y1,min(y2,min(y3,y4)));
       maxx1=max(x1,max(x2,max(x3,x4)));
       maxy1=max(y1,max(y2,max(y3,y4)));
       }

       //******************Rotation Y
	   if(Visualization->roty!=0)
	   {

		x1= minx1*cos(Visualization->roty*pi/180) + minz1*sin(Visualization->roty*pi/180);
		z1=-minx1*sin(Visualization->roty*pi/180) + minz1*cos(Visualization->roty*pi/180);

		x2= maxx1*cos(Visualization->roty*pi/180) + minz1*sin(Visualization->roty*pi/180);
		z2=-maxx1*sin(Visualization->roty*pi/180) + minz1*cos(Visualization->roty*pi/180);

		x3= maxx1*cos(Visualization->roty*pi/180) + maxz1*sin(Visualization->roty*pi/180);
		z3=-maxx1*sin(Visualization->roty*pi/180) + maxz1*cos(Visualization->roty*pi/180);

		x4= minx1*cos(Visualization->roty*pi/180) + maxz1*sin(Visualization->roty*pi/180);
		z4=-minx1*sin(Visualization->roty*pi/180) + maxz1*cos(Visualization->roty*pi/180);


       minx1=min(x1,min(x2,min(x3,x4)));
       minz1=min(z1,min(z2,min(z3,z4)));
       maxx1=max(x1,max(x2,max(x3,x4)));
       maxz1=max(z1,max(z2,max(z3,z4)));
       }

        //******************Rotation X

	   if(Visualization->rotx!=0)
       {
	   y1=miny1*cos(Visualization->rotx*pi/180) - minz1*sin(Visualization->rotx*pi/180);
	   z1=miny1*sin(Visualization->rotx*pi/180) + minz1*cos(Visualization->rotx*pi/180);

	   y2=maxy1*cos(Visualization->rotx*pi/180) - minz1*sin(Visualization->rotx*pi/180);
	   z2=maxy1*sin(Visualization->rotx*pi/180) + minz1*cos(Visualization->rotx*pi/180);

	   y3=maxy1*cos(Visualization->rotx*pi/180) - maxz1*sin(Visualization->rotx*pi/180);
	   z3=maxy1*sin(Visualization->rotx*pi/180) + maxz1*cos(Visualization->rotx*pi/180);

	   y4=miny1*cos(Visualization->rotx*pi/180) - maxz1*sin(Visualization->rotx*pi/180);
       z4=miny1*sin(Visualization->rotx*pi/180) + maxz1*cos(Visualization->rotx*pi/180);


       miny1=min(y1,min(y2,min(y3,y4)));
       minz1=min(z1,min(z2,min(z3,z4)));
       maxy1=max(y1,max(y2,max(y3,y4)));
       maxz1=max(z1,max(z2,max(z3,z4)));
       }
      //*******************Fin Rotation

         if(W!=0 && H!=0)
    {

      double ratio=W/H;
       if(W <= H)
	   {
          maxy1=maxy1*ratio;
          miny1=miny1*ratio;
       }
       else
	   {
          maxx1=maxx1/ratio;
          minx1=minx1/ratio;
       }

         h=maxy1-miny1;
         w=maxx1-minx1;

	   if(w<h)
       {
			rajout_x=(h-w)/2;
//			rajout_x=(h-w)/10; //BEY

			minx1=minx1 - rajout_x;
			maxx1=maxx1 + rajout_x;
			w=h;
	   }
	   else if(w>h)
	   {
			rajout_y=(w-h)/2;
//			rajout_y=(w-h)/10;//BEY

			miny1=miny1 - rajout_y;
			maxy1=maxy1 + rajout_y;
			h=w;
	   }

   }

//	  double extension=1;
	  double extension=0; //BEY

	  Visualization->nRangex_min=minx1-extension;
	  Visualization->nRangex_max=maxx1+extension;
	  Visualization->nRangey_min=miny1-extension;
	  Visualization->nRangey_max=maxy1+extension;

	  if(-minz1>Visualization->nRangez_max)
	  Visualization->nRangez_max=-(minz1-extension);
	  if(-maxz1<Visualization->nRangez_min)
	  Visualization->nRangez_min=-(maxz1+extension);

	  Visualization->tx=Visualization->ty=Visualization->tz=0;
	  Visualization->scalex=1;

	  Visualization->DrawObjects();

 }
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TVisualization::Calculer_Limites_Globales_Scene(double minx, double miny, double minz, double maxx, double maxy, double maxz)
{
Visualization->minx=1e10;
Visualization->miny=1e10;
Visualization->minz=1e10;

Visualization->maxx=-1e10;
Visualization->maxy=-1e10;
Visualization->maxz=-1e10;

 Visualization->minx=min(Visualization->minx,minx);
 Visualization->miny=min(Visualization->miny,miny);
 Visualization->minz=min(Visualization->minz,minz);

 Visualization->maxx=max(Visualization->maxx,maxx);
 Visualization->maxy=max(Visualization->maxy,maxy);
 Visualization->maxz=max(Visualization->maxz,maxz);

 double h1,w1,d1;

	   h1= Visualization->maxz-Visualization->minz ; //hauteur
	   w1= Visualization->maxx-Visualization->minx ;  //Longeur
	   d1= Visualization->maxy-Visualization->miny ;  ///Largeur


 Visualization->minx=Visualization->minx-(w1/10);
 Visualization->miny=Visualization->miny-(d1/10);
 Visualization->minz=Visualization->minz-(h1/10);
 Visualization->maxx=Visualization->maxx+(w1/10);
 Visualization->maxy=Visualization->maxy+(d1/10);
 Visualization->maxz=Visualization->maxz+(h1/10);

}
//---------------------------------------------------------------------------

