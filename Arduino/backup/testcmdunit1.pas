unit testcmdunit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,jclsysutils;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Memo1: TMemo;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private

  public
    procedure gereTexte(const Txt: string);
  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure Tform1.gereTexte(const Txt: string);
begin
  self.Memo1.Lines.add(Txt);
end;

procedure TForm1.FormCreate(Sender: TObject);
begin

end;

procedure TForm1.Button1Click(Sender: TObject);
var
  output: ansistring;
  handler:TTextHandler;
begin
  Handler:=@gereTexte;

  Execute('cmd.exe /C ' + 'd:',Handler,true,nil);
  Execute('cmd.exe /C ' + 'cd d:\lazarusXP\stuff\arduino & bat\makeCore.bat',Handler,true,nil);

end;





end.

