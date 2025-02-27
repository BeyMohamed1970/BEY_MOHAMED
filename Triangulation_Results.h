//---------------------------------------------------------------------------

#ifndef Triangulation_ResultsH
#define Triangulation_ResultsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TTriangulation_Results : public TForm
{
__published:	// Composants gérés par l'EDI
        TLabel *Label8;
        TEdit *Edit9;
        TLabel *Label1;
        TEdit *Edit1;
        TLabel *Label2;
        TEdit *Edit2;
        TLabel *Label3;
        TEdit *Edit3;
        TLabel *Label4;
        TEdit *Edit4;
        TLabel *Label5;
        TEdit *Edit5;
        TLabel *Label6;
        TEdit *Edit6;
	TGroupBox *GroupBox14;
	TLabel *Label19;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TEdit *Edit25;
	TEdit *Edit26;
	TEdit *Edit27;
	TEdit *Edit28;
	TEdit *Edit29;
	TEdit *Edit30;
        void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
        __fastcall TTriangulation_Results(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTriangulation_Results *Triangulation_Results;
//---------------------------------------------------------------------------
#endif
