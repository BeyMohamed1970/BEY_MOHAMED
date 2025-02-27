//---------------------------------------------------------------------------

#ifndef RenderingH
#define RenderingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TRendering : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *P1;
        TLabel *P2;
        TLabel *P3;
        TTrackBar *EA;
        TTrackBar *ES;
        TTrackBar *ED;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *P4;
        TLabel *P5;
        TLabel *P6;
        TTrackBar *X;
        TTrackBar *Y;
        TTrackBar *Z;
        TGroupBox *GroupBox3;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *P7;
        TLabel *P8;
        TLabel *P9;
        TLabel *P10;
        TLabel *P11;
        TTrackBar *MD;
        TTrackBar *MS;
        TTrackBar *ME;
        TTrackBar *MB;
        TTrackBar *MA;
        TCheckBox *CheckBox1;
        TGroupBox *GroupBox4;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox7;
	TButton *Button2;
	TGroupBox *GroupBox5;
	TLabel *Label13;
	TComboBox *ComboBox1;
	TButton *Button3;
	TLabel *Label12;
	TEdit *Edit1;
	TButton *Button1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall XChange(TObject *Sender);
        void __fastcall YChange(TObject *Sender);
        void __fastcall ZChange(TObject *Sender);
        void __fastcall EAChange(TObject *Sender);
        void __fastcall EDChange(TObject *Sender);
        void __fastcall ESChange(TObject *Sender);
        void __fastcall MAChange(TObject *Sender);
        void __fastcall MDChange(TObject *Sender);
        void __fastcall MSChange(TObject *Sender);
        void __fastcall MBChange(TObject *Sender);
        void __fastcall MEChange(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TRendering(TComponent* Owner);
        double distance;
        void reglage_eclairage();
        void activation_lumieres();
        void FormShow_BEY();
        void initialiser_limites();

        double limite_surface_x_min;
        double limite_surface_y_min;
        double limite_surface_x_max;
        double limite_surface_y_max;
        double limite_surface_z_min;
        double limite_surface_z_max;
        int pas;
		void lancer_parametrage(TObject *);
		TObject *Sender;

};
//---------------------------------------------------------------------------
extern PACKAGE TRendering *Rendering;
//---------------------------------------------------------------------------
#endif
