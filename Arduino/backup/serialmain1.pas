unit serialmain1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  SdpoSerial;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    ComboBox1: TComboBox;
    Edit1: TEdit;
    Memo1: TMemo;
    serial: TSdpoSerial;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure serialRxData(Sender: TObject);
  private
    FFlux:string;
  public

  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.Button1Click(Sender: TObject);
begin
  serial.Device:=self.ComboBox1.Text;
  serial.Active:=true;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
    if edit1.Text='' then exit;
    if serial.Active then serial.WriteData(edit1.text);
    //+chr(13)+chr(10)
end;

procedure TForm1.FormActivate(Sender: TObject);
begin
  memo1.clear;
end;

procedure TForm1.serialRxData(Sender: TObject);
begin
    FFlux:=FFlux+(serial.ReadData);
    self.caption:=Fflux;
    if pos(#13,Fflux)>0 then
      begin
        FFlux:=copy(FFlux,1,pos(#13,Fflux)-1);
        memo1.lines.add(FFlux);
        FFLux:='';
      end;
end;

end.

