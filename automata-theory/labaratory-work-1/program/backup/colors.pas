unit Colors;

{$mode ObjFPC}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ColorBox;

type

  { TColorsForm }

  TColorsForm = class(TForm)
    ButtonRandom: TButton;
    ButtonOk: TButton;
    ColorBox1: TColorBox;
    ColorBox10: TColorBox;
    ColorBox2: TColorBox;
    ColorBox3: TColorBox;
    ColorBox4: TColorBox;
    ColorBox5: TColorBox;
    ColorBox6: TColorBox;
    ColorBox7: TColorBox;
    ColorBox8: TColorBox;
    ColorBox9: TColorBox;
    procedure ButtonOkClick(Sender: TObject);
  private

  public

  end;

var
  ColorsForm: TColorsForm;

implementation

{$R *.lfm}

{ TColorsForm }

procedure TColorsForm.ButtonOkClick(Sender: TObject);
begin
  ColorsForm.Close;
end;

end.

