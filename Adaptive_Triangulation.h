//---------------------------------------------------------------------------

#ifndef Adaptive_TriangulationH
#define Adaptive_TriangulationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>

#include "Point_Clouds_Import.h"

//---------------------------------------------------------------------------
class TAdaptive_Triangulation : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TEdit *Edit2;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit1;
        TButton *Button1;
        TGroupBox *GroupBox3;
        TButton *Button2;
        TEdit *Edit3;
        TEdit *Edit4;
        TLabel *Label1;
        TLabel *Label4;
        TCheckBox *CheckBox3;
        TComboBox *ComboBox2;
        TCheckBox *CheckBox5;
        TComboBox *ComboBox5;
        TCheckBox *CheckBox7;
        TComboBox *ComboBox7;
        TGroupBox *GroupBox5;
        TPanel *Panel1;
        TButton *Button3;
        TGroupBox *GroupBox6;
        TButton *Button5;
        TGroupBox *GroupBox7;
        TCheckBox *CheckBox6;
        TComboBox *ComboBox6;
        TGroupBox *GroupBox4;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TCheckBox *CheckBox9;
        TComboBox *ComboBox9;
        TCheckBox *CheckBox4;
        TComboBox *ComboBox4;
        TCheckBox *CheckBox10;
        TComboBox *ComboBox10;
        TCheckBox *CheckBox11;
        TComboBox *ComboBox11;
        TCheckBox *CheckBox8;
        TComboBox *ComboBox8;
        TPanel *Panel2;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton4;
        TRadioButton *RadioButton5;
        TButton *Button4;
        TCheckBox *CheckBox12;
        TComboBox *ComboBox12;
        TBitBtn *BitBtn1;
        TGroupBox *GroupBox2;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TComboBox *ComboBox1;
        TComboBox *ComboBox3;
        TCheckBox *CheckBox13;
        TButton *Button6;
        TSaveDialog *SaveDialog1;
        TButton *Button7;
        TCheckBox *CheckBox14;
        TComboBox *ComboBox13;
        TButton *Button8;
        TEdit *Edit7;
        TLabel *Label7;
        TCheckBox *CheckBox15;
        TComboBox *ComboBox14;
        TCheckBox *CheckBox16;
        TComboBox *ComboBox15;
        TCheckBox *CheckBox17;
        TComboBox *ComboBox16;
        TCheckBox *CheckBox18;
        TComboBox *ComboBox17;
        TGroupBox *GroupBox8;
        TLabel *Label8;
        TLabel *Label10;
        TEdit *Edit9;
        TEdit *Edit10;
        TGroupBox *GroupBox9;
        TCheckBox *CheckBox22;
        TComboBox *ComboBox21;
        TCheckBox *CheckBox23;
        TComboBox *ComboBox22;
        TCheckBox *CheckBox24;
        TComboBox *ComboBox23;
        TCheckBox *CheckBox25;
        TComboBox *ComboBox24;
        TCheckBox *CheckBox26;
        TComboBox *ComboBox25;
        TCheckBox *CheckBox27;
        TComboBox *ComboBox26;
        TCheckBox *CheckBox29;
        TButton *Button9;
        TButton *Button10;
        TButton *Button11;
        TCheckBox *CheckBox32;
        TComboBox *ComboBox30;
        TCheckBox *CheckBox33;
        TComboBox *ComboBox31;
        TCheckBox *CheckBox34;
        TComboBox *ComboBox32;
        TCheckBox *CheckBox35;
        TComboBox *ComboBox33;
        TButton *Button12;
        TButton *Button13;
        TGroupBox *GroupBox11;
        TRadioButton *RadioButton8;
        TRadioButton *RadioButton9;
        TRadioButton *RadioButton10;
        TCheckBox *CheckBox36;
        TComboBox *ComboBox34;
        TCheckBox *CheckBox37;
        TComboBox *ComboBox35;
        TCheckBox *CheckBox38;
        TComboBox *ComboBox36;
        TButton *Button14;
        TLabel *Label13;
        TButton *Button16;
        TCheckBox *CheckBox39;
        TComboBox *ComboBox37;
        TGroupBox *GroupBox13;
        TRadioButton *RadioButton13;
        TRadioButton *RadioButton14;
        TRadioButton *RadioButton15;
        TButton *Button17;
        TButton *Button19;
        TLabel *Label20;
        TEdit *Edit23;
        TButton *Button20;
	TGroupBox *GroupBox27;
	TLabel *Label41;
	TLabel *Label42;
	TLabel *Label43;
	TLabel *Label44;
	TEdit *Edit39;
	TEdit *Edit40;
	TEdit *Edit41;
	TEdit *Edit42;
	TCheckBox *CheckBox45;
	TGroupBox *GroupBox14;
	TButton *Button15;
	TCheckBox *CheckBox40;
	TEdit *Edit22;
	TCheckBox *CheckBox41;
	TEdit *Edit24;
	TEdit *Edit26;
	TCheckBox *CheckBox46;
	TEdit *Edit15;
	TLabel *Label17;
	TEdit *Edit20;
	TLabel *Label18;
	TCheckBox *CheckBox44;
	TLabel *Label24;
	TEdit *Edit21;
	TCheckBox *CheckBox48;
	TCheckBox *CheckBox49;
	TCheckBox *CheckBox50;
	TComboBox *ComboBox41;
	TComboBox *ComboBox42;
	TLabel *Label26;
	TLabel *Label27;
	TCheckBox *CheckBox51;
	TEdit *Edit28;
	TCheckBox *CheckBox52;
	TCheckBox *CheckBox53;
	TButton *Button21;
	TLabel *Label14;
	TEdit *Edit13;
	TLabel *Label15;
	TEdit *Edit14;
	TLabel *Label28;
	TEdit *Edit29;
	TLabel *Label29;
	TEdit *Edit30;
	TLabel *Label12;
	TEdit *Edit12;
	TLabel *Label30;
	TEdit *Edit31;
	TColorDialog *ColorDialog1;
	TButton *Button22;
	TCheckBox *CheckBox54;
	TComboBox *ComboBox43;
	TGroupBox *GroupBox15;
	TLabel *Label16;
	TLabel *Label11;
	TLabel *Label25;
	TEdit *Edit19;
	TEdit *Edit11;
	TEdit *Edit27;
	TLabel *Label31;
	TEdit *Edit32;
	TButton *Button18;
	TGroupBox *GroupBox12;
	TLabel *Label32;
	TLabel *Label33;
	TEdit *Edit33;
	TEdit *Edit34;
	TCheckBox *CheckBox30;
	TComboBox *ComboBox28;
	TCheckBox *CheckBox47;
	TComboBox *ComboBox38;
	TCheckBox *CheckBox21;
	TComboBox *ComboBox20;
	TGroupBox *GroupBox17;
	TLabel *Label34;
	TEdit *Edit35;
	TButton *Button23;
	TLabel *Label35;
	TEdit *Edit36;
	TRadioButton *RadioButton12;
	TRadioButton *RadioButton16;
	TButton *Button24;
	TButton *Button25;
	TCheckBox *CheckBox28;
	TComboBox *ComboBox27;
	TEdit *Edit37;
	TLabel *Label36;
	TGroupBox *GroupBox18;
	TCheckBox *CheckBox19;
	TCheckBox *CheckBox20;
	TCheckBox *CheckBox31;
	TCheckBox *CheckBox55;
	TCheckBox *CheckBox56;
	TGroupBox *GroupBox16;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TEdit *Edit16;
	TEdit *Edit17;
	TEdit *Edit18;
	TGroupBox *GroupBox10;
	TRadioButton *RadioButton6;
	TRadioButton *RadioButton7;
	TCheckBox *CheckBox42;
	TComboBox *ComboBox39;
	TCheckBox *CheckBox43;
	TComboBox *ComboBox40; //z_pt_maximum

      // TButton *Button3;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Edit3KeyPress(TObject *Sender, char &Key);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall ComboBox12Click(TObject *Sender);
        void __fastcall CheckBox12Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall ComboBox27Click(TObject *Sender);
		void __fastcall CheckBox28Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
        void __fastcall Button13Click(TObject *Sender);
        void __fastcall Button14Click(TObject *Sender);
        void __fastcall Button15Click(TObject *Sender);
        void __fastcall Button16Click(TObject *Sender);
        void __fastcall Button17Click(TObject *Sender);
        void __fastcall Button18Click(TObject *Sender);
        void __fastcall RadioButton11Click(TObject *Sender);
        void __fastcall Button19Click(TObject *Sender);
        void __fastcall Button20Click(TObject *Sender);
	void __fastcall CheckBox48Click(TObject *Sender);
	void __fastcall CheckBox49Click(TObject *Sender);
	void __fastcall CheckBox50Click(TObject *Sender);
	void __fastcall Edit22Change(TObject *Sender);
	void __fastcall Edit24Change(TObject *Sender);
	void __fastcall Edit26Change(TObject *Sender);
	void __fastcall Button21Click(TObject *Sender);
	void __fastcall CheckBox52Click(TObject *Sender);
	void __fastcall Button22Click(TObject *Sender);
	void __fastcall CheckBox29Click(TObject *Sender);
	void __fastcall Button23Click(TObject *Sender);
	void __fastcall RadioButton16Click(TObject *Sender);
	void __fastcall RadioButton12Click(TObject *Sender);
	void __fastcall Edit32KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Button24Click(TObject *Sender);
	void __fastcall Button25Click(TObject *Sender);
        //void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAdaptive_Triangulation(TComponent* Owner);
		bool approximation_effectuee;
		double pas_cell_x, pas_cell_y;
		int nbre_cellule_x;
        int nbre_cellule_y;
        int nbre_segments_x;
        int nbre_segments_y;
        int nbre_pts_triangle;
        void creer_liste_point_triangle();
        void creer_liste();
        void creer_liste_BEY();

        void dessiner_toutes_listes_points();
        void dessiner_toutes_listes_points_vector();
        void dessiner_toutes_listes_points_vector_int();
		void dessiner_points_plan();
        void dessiner_triangle();
		void dessiner_points_triangle();
        void dessiner_limite_triangle();
        void dessiner_points_triangle_nf();
        void dessiner_points_triangle_f();
        void dessiner_triangle_3D_f();

        double calcul_angle_deux_segments(double,double,double,double,double,double);
        void jordan(double a[2][2],double b[2],double x[2]);
        void gauss_pivot_total(double a[3][3],double b[3],double x[3], bool &prob);
		void gauss_pivot_total_4_4(double a[4][4],double b[4],double x[4], bool &probleme);
		void dessiner_triangle_3D();
        double dist_max,dist_min;
        void subdivision_x(int,int);
        void subdivision_y(int,int);
        double *vx_pas, *vy_pas;
        bool *subdiv_col,*subdiv_lig;
		double px, py;
		double px1, py1;
        bool exception;

        void choix_z_triangle();
        double precision;
		bool maj;
		bool premiere_triangulation;
		bool creation_cellules;
		AnsiString mode;
		bool triangulation_initiale;
		vector <point_nuage_BEY> liste_pts_triangle_BEY_tmp;

		void integration_triangles();
        void determination_voisins();
        void affectation_num_triangle();
        void remplissage_Combobox();
        void affectation_ligne_colonne_pt();
        void traintement_triangles_hors_brut();
        void gestion_checkbox11();

        Char *filename_as,fichier_as[2000];

		void save_fichier_STL();
        
		void determiner_pts_proches_sommets_triangle();
        void dessiner_pts_proches_sommets_triangle();
        void filtrer_triangles_distances_sommets_triangle();
        void calculer_centre_cercle_circonscrit(double x1,double y1,double x2,double y2,double x3,double y3,double &xc,double &yc,double &Rc);
        void dessiner_centre_cercle_circonscrit();
        void dessiner_centre_cercle_circonscrit_sommets_triangle();
        void dessiner_centre_gravite_triangle();
        void dessiner_centre_gravite_pts_triangle();
        void calculer_nbre_pts_triangles();

		bool repartition_pt_correcte_triangle;
		bool appartence_pt_triangle(triangle_initial *, double, double);
		bool appartence_pt_triangle_BEY(double x1, double y1, double x2, double y2, double x3, double y3, double xminT, double yminT, double xmaxT, double ymaxT, double x, double y);
		bool appartence_pt_triangle_BEY_NEW(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3, double &xminT, double &yminT, double &xmaxT, double &ymaxT, double x, double y, double p1p2_x, double p1p2_y, double p1p3_x, double p1p3_y, double p2p3_x, double p2p3_y);
		double calculer_angle_point(double, double);

		triangle_initial_BEY *cible;
		double aire_triangle_subdivise;


        void dessiner_triangle_BEY();
        void dessiner_points_triangle_BEY();
		void dessiner_triangle_3D_BEY();
		void dessiner_triangle_3D_Filtres_BEY();
		void dessiner_triangle_3D_Elimination_BEY();
		void dessiner_triangle_3D_sommets_nuls_BEY();
		void dessiner_points_triangle_nf_BEY();
		void dessiner_points_triangle_filtres_BEY();
        void dessiner_triangle_3D_f_BEY();
		void dessiner_points_triangle_f_BEY();
        void dessiner_triangles_voisins_BEY();
		void dessiner_pts_proches_sommets_triangle_BEY();
		void dessiner_pts_proches_sommets_triangle_sommets_nuls_BEY();
		void dessiner_pts_proches_milieux_triangle_BEY();
		void dessiner_triangle_eliminer_sommet_BEY();

        void dessiner_centre_cercle_circonscrit_BEY();
        void dessiner_centre_cercle_circonscrit_sommets_triangle_BEY();
        void dessiner_centre_gravite_triangle_BEY();
        void dessiner_centre_gravite_pts_triangle_BEY();
        void dessiner_pts_eloingnes_deux_sommets_nulles_triangle_BEY();
        void dessiner_pts_proches_un_sommet_nulles_triangle_BEY();
        void dessiner_segment_intersection_un_sommet_nulle_triangle_BEY();

        void intersection_deux_segment_BEY(triangle_initial *parc, int num_point, double x1,double y1,double x2,double y2, double x3,double y3,double x4,double y4,double & X,double & Y, double & alpha,double & beta);

        void triangulation_initiale_uniforme();
		void affectation_triangles_liste_triangles();
		void voisins_a_modifier(triangle_initial_BEY *parc);
		void subdivision_sommet_1_null(triangle_initial_BEY *, double, double, double, double, double, double, double, double, double, double);
        void subdivision_centre_gravite(triangle_initial *parc);
		void subdivision_quatre_triangles(double &x12_milieu, double &y12_milieu, double &x23_milieu, double &y23_milieu, double &x13_milieu, double &y13_milieu, triangle_initial *parc);
		void subdiviser_triangles_voisins(triangle_initial_BEY*);
		void Lancer_Approche_Subdivision_Triangles();
		void Affectation_Numeros_Sommets_Calcul_Zmax_Zmin_Zmoy_Sommets();
		void Mise_A_Jour_Sommets_Triangles_Calcul_Ecarts_Max_Triangles_Erreurs_Max_Min();
//		void creer_triangles(double, double, triangle_initial *);
		bool creer_triangles(double, double, triangle_initial_BEY *);
		void calculer_pt_bissectrice(double x, double y, double x1, double y1, double x2, double y2, double & x_milieu, double & y_milieu);
		void creation_triangles_centre_gravite(triangle_initial *);
        void creation_deux_triangles_milieu_cote(triangle_initial_BEY *);
		void mise_a_jour_triangulation();
		void mise_a_jour_triangulation_initiale();
        void determiner_limites_triangles_points_triangles();
		void save_fichier_STL_BEY();
		void gestion_voisins_triangle_filtre_suprime(triangle_initial_BEY *V);
		double determinant_matrice_3_3(double a11, double a12, double a13,
									   double a21, double a22, double a23,
									   double a31, double a32, double a33);
		bool mise_a_jour_informations_triangles;
		void dessiner_sommets_projetes();
		double precision_calcul_approximation;
		double aire_min_triangle;
		double rapport;
        int nbre_total_triangles, nbre_triangles_non_filtres, nbre_triangles_filtres;

		int nbre_pts_total, nbre_pts_non_filtres, nbre_pts_filtres;
		void dessiner_listes_points_cellule_new() ;
		bool voisin_1_supprime, voisin_2_supprime, voisin_3_supprime;
		double X1, Y1, X2, Y2, X3, Y3;
		void verification(triangle_initial_BEY *parc);
		double precision_approximation_impose;
		double seuil_aire_triangle;
		double rapport_limites_triangle_limites_points;
		double nbre_min_points_triangle;
		double ecart_max_droite;
		double red_surface, green_surface, blue_surface;

		AnsiString Type_Z_Coordonnee; //Z_MAX, Z_MIN, Z_MOY
		double px_s, py_s, xmin, ymin, xmax, ymax;
		double processing_time_partiel, processing_time_total;
		int nbre_triangles_a_supprimer;
		vector<triangle_initial_BEY*> Triangles_A_Calculer_Voisins;
		int Nbre_Triangles_A_Calculer_Voisins;
		vector<triangle_initial_BEY*> Triangles_Recherche_Voisins;
		int Nbre_Triangles_Recherche_Voisins;
		vector<triangle_initial_BEY*> Triangles_Supprimes;
		int Nbre_Triangles_Supprimes;
		bool Points_Proches_Seulement_Un_Sommet;
};

//---------------------------------------------------------------------------
extern PACKAGE TAdaptive_Triangulation *Adaptive_Triangulation;
//---------------------------------------------------------------------------
#endif
