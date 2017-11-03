unit main1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  ExtCtrls, Menus, windows, lazUTF8, SynEdit,jclsysutils,dos,utils_serial;

type

  { TForm1 }

  TForm1 = class(TForm)
    ComboCOM: TComboBox;
    IdleTimer1: TIdleTimer;
    Label1: TLabel;
    MainMenu1: TMainMenu;
    Memo1: TMemo;
    mnuPortSelect: TMenuItem;
    mnuUploadHEX: TMenuItem;
    mnuCompile: TMenuItem;
    mnuCompileCore: TMenuItem;
    mnuExit: TMenuItem;
    mnuArduinotools: TMenuItem;
    mnuFichier: TMenuItem;
    Panel1: TPanel;
    SynEdit1: TSynEdit;
    procedure FormActivate(Sender: TObject);
    procedure IdleTimer1Timer(Sender: TObject);
    procedure Memo1Change(Sender: TObject);
    procedure mnuCompileClick(Sender: TObject);
    procedure mnuCompileCoreClick(Sender: TObject);
    procedure mnuExitClick(Sender: TObject);
    procedure mnuPortSelectClick(Sender: TObject);
    procedure mnuUploadHEXClick(Sender: TObject);
    procedure SynEdit1Change(Sender: TObject);
    //procedure JvCreateProcess1Terminate(Sender: TObject; ExitCode: DWORD);
  private
    FPort:string;
    FListOfStrings:TstringList;
    procedure Split(Delimiter: Char; Str: string) ;
    procedure ChangeLastLine(const S: string);
    function FormatForDisplay(const S: string): string;
    //procedure JvCreateProcess1Read(Sender: TObject; const S: string;const StartsOnNewLine: Boolean);



  public
    constructor create(sender:Tobject) ;
    procedure AddNewLine(const S: string);
    procedure ClearScreen;
    procedure InitCommand(cmd:string);
    procedure gereTexte(const Txt: string);
    procedure gereTexte2(const Txt: string);
  end;
const

  AVR_CPP='hardware\tools\avr\bin\avr-c++.exe';
  AVR_GCC='hardware\tools\avr\bin\avr-gcc.exe';
var
  Form1: TForm1;
  Prefix:string;
  handler,handler2:TTextHandler;
implementation

{$R *.lfm}

{ TForm1 }

procedure Tform1.gereTexte(const Txt: string);
begin
self.Memo1.Lines.add(Txt);
end;
procedure Tform1.gereTexte2(const Txt: string);

 var t:string;
 begin

  if (pos('COM',txt)>0)
  //and (pos('Arduino',txt)>0)
  then
    begin
      t:=trim(txt);
      t:=copy(t,1,5);
      FPort:=(trim(t));
      //memo2.lines.add(Fport);
    end;
 end;


constructor TForm1.create(sender:Tobject) ;
  begin
   FListOfStrings:=Tstringlist.create;
end;
procedure TForm1.Split(Delimiter: Char; Str: string) ;
  begin
   FListOfStrings.Clear;
   FListOfStrings.Delimiter       := Delimiter;
   FListOfStrings.StrictDelimiter := True; // Requires D2006 or newer.
   FListOfStrings.DelimitedText   := Str;
end;
procedure Tform1.InitCommand(cmd:string);
var CommandLine:string;
begin
 end;

function Tform1.FormatForDisplay(const S: string): string;
  begin
    //Result := StrReplaceChar(S, #255, ' ');
  end;
procedure Tform1.ClearScreen;
begin
  memo1.Clear;
end;

procedure TForm1.FormActivate(Sender: TObject);
begin
 handler:=@gereTexte;
 handler2:=@gereTexte2;
 //memo2.clear;
  self.InitCommand('INIT');
  self.SynEdit1.Lines.LoadFromFile(getCurrentDir()+'/ino/'+getenv('userdomain')+'_'+getenv('username')+'_default.ino');
end;

procedure TForm1.IdleTimer1Timer(Sender: TObject);
begin
 self.ComboCOM.text:='';
 self.ComboCOM.Items:=lire_com;
 if self.comboCOM.Items.count>=1 then begin self.ComboCOM.ItemIndex:=self.comboCOM.Items.count-1;  Fport:=self.ComboCOM.text; end;
end;


procedure TForm1.Memo1Change(Sender: TObject);
begin

end;

procedure TForm1.mnuCompileClick(Sender: TObject);
begin
 self.SynEdit1.Lines.SaveToFile('ino/'+getenv('userdomain')+'_'+getenv('username')+'_default.ino');
 execute('cmd /c cd '+getcurrentDir()+ ' & .\bat\compilHEX.bat',handler,true,nil);
 //self.JvCreateProcess1.WriteLn(ansistring(GetCurrentDir()+'/bat/compilHEX.bat'));
end;

procedure TForm1.mnuCompileCoreClick(Sender: TObject);
begin
  execute('cmd /c cd '+getcurrentDir()+ ' & .\bat\makeCore.bat',handler,true,nil);
  //self.JvCreateProcess1.WriteLn(ansistring(GetCurrentDir()+'/bat/makeCore.bat'));
end;

procedure TForm1.mnuExitClick(Sender: TObject);
begin
  self.close;
end;

procedure TForm1.mnuPortSelectClick(Sender: TObject);
begin
 //memo2.clear;
 //execute('cmd /c '+getcurrentDir()+ '\..\ & .\tools\listComPorts.exe',handler2,true,nil);
end;

procedure TForm1.mnuUploadHEXClick(Sender: TObject);

var s:string;
begin
 s:= 'cmd /c cd '+getcurrentDir()+ ' & .\bat\uploadHEX.bat '+FPort;
 memo1.lines.add(s);
 if FPort<> '' then execute(s,handler,true,nil);


end;

procedure TForm1.SynEdit1Change(Sender: TObject);
begin

end;


procedure Tform1.ChangeLastLine(const S: string);
begin
  with memo1 do
  begin
    if lines.Count > 0 then
      Lines[lines.Count - 1] := FormatForDisplay(S)
    else
      AddNewLine(S);
    //ItemIndex := Count - 1;
  end;
end;

procedure Tform1.AddNewLine(const S: string);
begin
  with memo1 as Tmemo do
  begin
    Lines.Add(FormatForDisplay(S));
    //ItemIndex := Count - 1;
  end;
end;



end.

