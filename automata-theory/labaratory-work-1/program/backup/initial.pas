unit Initial;

{$mode ObjFPC}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, Spin;

type

  { TInitialForm }

  TInitialForm = class(TForm)
    ButtonRandom: TButton;
    ButtonOk: TButton;
    SpinEdit1: TSpinEdit;
    SpinEdit10: TSpinEdit;
    SpinEdit2: TSpinEdit;
    SpinEdit3: TSpinEdit;
    SpinEdit4: TSpinEdit;
    SpinEdit5: TSpinEdit;
    SpinEdit6: TSpinEdit;
    SpinEdit7: TSpinEdit;
    SpinEdit8: TSpinEdit;
    SpinEdit9: TSpinEdit;
    procedure ButtonOkClick(Sender: TObject);
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

end.

