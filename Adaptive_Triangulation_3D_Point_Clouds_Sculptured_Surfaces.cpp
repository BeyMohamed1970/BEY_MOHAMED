//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Rendering.cpp", Rendering);
USEFORM("Triangulation_Results.cpp", Triangulation_Results);
USEFORM("Visualization.cpp", Visualization);
USEFORM("Adaptive_Triangulation.cpp", Adaptive_Triangulation);
USEFORM("Point_Clouds_Import.cpp", Point_Clouds_Import);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TVisualization), &Visualization);
		Application->CreateForm(__classid(TAdaptive_Triangulation), &Adaptive_Triangulation);
		Application->CreateForm(__classid(TPoint_Clouds_Import), &Point_Clouds_Import);
		Application->CreateForm(__classid(TRendering), &Rendering);
		Application->CreateForm(__classid(TTriangulation_Results), &Triangulation_Results);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
