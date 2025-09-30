unit Main;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, Menus, Colors, Initial, About, Author;

type

  { TMainForm }

  TMainForm = class(TForm)
    MainMenu: TMainMenu;
    MenuFile: TMenuItem;
    MenuAuthor: TMenuItem;
    MenuOpen: TMenuItem;
    MenuSave: TMenuItem;
    MenuExit: TMenuItem;
    MenuSettings: TMenuItem;
    MenuColors: TMenuItem;
    MenuInitial: TMenuItem;
    MenuReference: TMenuItem;
    MenuAbout: TMenuItem;
    procedure MenuAboutClick(Sender: TObject);
    procedure MenuAuthorClick(Sender: TObject);
    procedure MenuColorsClick(Sender: TObject);
    procedure MenuExitClick(Sender: TObject);
    procedure MenuInitialClick(Sender: TObject);
  private

  public

  end;

var
  MainForm: TMainForm;

implementation

{$R *.lfm}

{ TMainForm }

procedure TMainForm.MenuAboutClick(Sender: TObject);
begin
  AboutForm.ShowModal;
end;

procedure TMainForm.MenuAuthorClick(Sender: TObject);
begin
  AuthorForm.ShowModal;
end;

procedure TMainForm.MenuColorsClick(Sender: TObject);
begin
  ColorsForm.ShowModal;
end;

procedure TMainForm.MenuExitClick(Sender: TObject);
begin
  MainForm.Close;
end;

procedure TMainForm.MenuInitialClick(Sender: TObject);
begin
  InitialForm.ShowModal;
end;

end.

