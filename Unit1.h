//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *AValue;
	TLabel *Label4;
	TEdit *BValue;
	TLabel *Label5;
	TEdit *CValue;
	TLabel *Label6;
	TEdit *DValue;
	TLabel *Label7;
	TEdit *EValue;
	TButton *CalculateButton;
	TLabel *Label8;
	TLabel *InfixForm;
	TLabel *Label9;
	TLabel *PostfixForm;
	TLabel *Label10;
	TLabel *PostfixResult;
	TLabel *Label11;
	TLabel *ControlResult;
	void __fastcall CalculateButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
