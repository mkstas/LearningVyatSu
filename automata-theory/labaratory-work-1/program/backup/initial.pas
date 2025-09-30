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
    SpinEdit1: TSpinEdit;
    procedure ButtonOkClick(Sender: TObject);
    procedure SpinEdit1Change(Sender: TObject);
  private

  public

  end;

var
  InitialForm: TInitialForm;

implementation

{$R *.lfm}

{ TInitialForm }

procedure TInitialForm.ButtonOkClick(Sender: TObject);
begin
  InitialForm.Close;
end;

procedure TInitialForm.SpinEdit1Change(Sender: TObject);
begin
  if SpinEdit1.Value = 10 then
    SpinEdit1.Value := 0;
  if SpinEdit1.Value = -1 then
    SpinEdit1.Value := 9;
end;

end.

