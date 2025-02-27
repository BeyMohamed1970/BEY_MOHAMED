//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Triangulation_Results.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTriangulation_Results *Triangulation_Results;
//---------------------------------------------------------------------------
__fastcall TTriangulation_Results::TTriangulation_Results(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTriangulation_Results::Button1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TTriangulation_Results::FormShow(TObject *Sender)
{
Top=0;
Left=0;
}
//---------------------------------------------------------------------------

