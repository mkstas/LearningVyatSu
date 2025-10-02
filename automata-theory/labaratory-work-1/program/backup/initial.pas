unit Initial;

{$mode ObjFPC}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, Spin;

type

  { TInitialForm }

  TInitialForm = class(TForm)
    ButtonCancel: TButton;
    ButtonClear: TButton;
    ButtonOk: TButton;
    StaticText1: TStaticText;
    StaticText2: TStaticText;
    procedure ButtonOkClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure SpinEditChange(Sender: TObject);
  private

  public

  end;

var
  InitialForm: TInitialForm;
  FSpinEdits: array[0..9] of TSpinEdit;
  FLabels: array[0..9] of TLabel;

implementation

{$R *.lfm}

{ TInitialForm }

procedure TInitialForm.ButtonOkClick(Sender: TObject);
begin
  InitialForm.Close;
end;

procedure TInitialForm.FormCreate(Sender: TObject);
var
  i: Integer;
begin
  for i := 0 to 9 do
  begin
    FLabels[i] := TLabel.Create(Self);
    FLabels[i].Parent := Self;
    FLabels[i].Width := 20;
    FLabels[i].Width := 24;
    FLabels[i].Left := 16 + (i mod 2) * 124;
    FLabels[i].Top := 67 + (i div 2) * 40;
    FLabels[i].Name := 'Label' + IntToStr(i);
    FLabels[i].Caption := IntToStr(i + 1) + ':';

    FSpinEdits[i] := TSpinEdit.Create(Self);
    FSpinEdits[i].Parent := Self;
    FSpinEdits[i].Width := 80;
    FSpinEdits[i].Height := 24;
    FSpinEdits[i].Left := 36 + (i mod 2) * 124;
    FSpinEdits[i].Top := 64 + (i div 2) * 40;
    FSpinEdits[i].Name := 'SpinEdit' + IntToStr(i);
    FSpinEdits[i].MinValue := -1;
    FSpinEdits[i].MaxValue := 10;
    FSpinEdits[i].Value := i;

    FSpinEdits[i].OnChange := @SpinEditChange;
  end;
end;

procedure TInitialForm.SpinEditChange(Sender: TObject);
begin

end;

end.

