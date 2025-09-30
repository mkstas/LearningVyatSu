unit Author;

{$mode ObjFPC}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls;

type

  { TAuthorForm }

  TAuthorForm = class(TForm)
    ButtonOk: TButton;
    StaticText1: TStaticText;
    StaticText2: TStaticText;
    StaticText3: TStaticText;
    StaticText4: TStaticText;
    StaticText5: TStaticText;
    procedure ButtonOkClick(Sender: TObject);
  private

  public

  end;

var
  AuthorForm: TAuthorForm;

implementation

{$R *.lfm}

{ TAuthorForm }

procedure TAuthorForm.ButtonOkClick(Sender: TObject);
begin
  AuthorForm.Close;
end;

end.

