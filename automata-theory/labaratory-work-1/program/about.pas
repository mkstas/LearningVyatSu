unit About;

{$mode ObjFPC}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls;

type

  { TAboutForm }

  TAboutForm = class(TForm)
    ButtonOk: TButton;
    AboutStaticText: TStaticText;
    procedure ButtonOkClick(Sender: TObject);
  private

  public

  end;

var
  AboutForm: TAboutForm;

implementation

{$R *.lfm}

{ TAboutForm }

procedure TAboutForm.ButtonOkClick(Sender: TObject);
begin
  AboutForm.Close;
end;

end.

