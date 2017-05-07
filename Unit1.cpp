//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "RPN.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent *Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void __fastcall TForm1::CalculateButtonClick(TObject *Sender) {
  // Замена запятых на точки для дальнейшего выполенния преобразования в Double
  Form1->AValue->Text =
      StringReplace(Form1->AValue->Text, ".", ",", TReplaceFlags());
  Form1->BValue->Text =
      StringReplace(Form1->BValue->Text, ".", ",", TReplaceFlags());
  Form1->CValue->Text =
      StringReplace(Form1->CValue->Text, ".", ",", TReplaceFlags());
  Form1->DValue->Text =
      StringReplace(Form1->DValue->Text, ".", ",", TReplaceFlags());
  Form1->EValue->Text =
      StringReplace(Form1->EValue->Text, ".", ",", TReplaceFlags());
  double a, b, c, d, e;
  a = Form1->AValue->Text.ToDouble();
  b = Form1->BValue->Text.ToDouble();
  c = Form1->CValue->Text.ToDouble();
  d = Form1->DValue->Text.ToDouble();
  e = Form1->EValue->Text.ToDouble();
  Form1->InfixForm->Caption =
      "(" + AnsiString(a) + "+" + b + "*" + c + ")/(" + d + "-" + e + ")";
  Form1->ControlResult->Caption = (a + b * c) / (d - e);
  string *s = new string[13];
  s[0] = "(";
  s[1] = AnsiString(a).c_str();
  s[2] = "+";
  s[3] = AnsiString(b).c_str();
  s[4] = "*";
  s[5] = AnsiString(c).c_str();
  s[6] = ")";
  s[7] = "/";
  s[8] = "(";
  s[9] = AnsiString(d).c_str();
  s[10] = "-";
  s[11] = AnsiString(e).c_str();
  s[12] = ")";
  RPN rpn(s, 13);
  Form1->PostfixForm->Caption = rpn.postfix.c_str();
  Form1->PostfixResult->Caption = rpn.result;
}
//---------------------------------------------------------------------------
