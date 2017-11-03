program simplehttpserver;

{$mode objfpc}{$H+}
{$define UseCThreads}


uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  synaser,sysutils, Classes, fphttpserver2, fpmimetypes;

const MX=1000;

Type

  { TTestHTTPServer }

  TTestHTTPServer = Class(TFPHTTPServer)
  private
    Frep:char;
    FUrl:string;
    FValue:string;
    Fser:TBlockSerial;
    FBaseDir : String;
    FCount : Integer;
    FListOfStrings:TstringList;
    FMimeLoaded : Boolean;
    FMimeTypesFile: String;
    procedure SetBaseDir(const AValue: String);
    procedure Split(Delimiter: Char; Str: string) ;
  Protected
    Procedure DoIdle(Sender : TObject);
    procedure CheckMimeLoaded;

    Property MimeLoaded : Boolean Read FMimeLoaded;
  public
    procedure HandleRequest(Var ARequest: TFPHTTPConnectionRequest;
                            Var AResponse : TFPHTTPConnectionResponse); override;
    Property BaseDir : String Read FBaseDir Write SetBaseDir;
    Property MimeTypesFile : String Read FMimeTypesFile Write FMimeTypesFile;

  end;

Var
  Serv : TTestHTTPServer;
  s:string;

{ TTestHTTPServer }

procedure TTestHTTPServer.Split(Delimiter: Char; Str: string) ;
  begin
   FListOfStrings.Clear;
   FListOfStrings.Delimiter       := Delimiter;
   FListOfStrings.StrictDelimiter := True; // Requires D2006 or newer.
   FListOfStrings.DelimitedText   := Str;
end;


procedure TTestHTTPServer.SetBaseDir(const AValue: String);
begin
  if FBaseDir=AValue then exit;
  FBaseDir:=AValue;
  If (FBaseDir<>'') then
    FBaseDir:=IncludeTrailingPathDelimiter(FBaseDir);
end;

procedure TTestHTTPServer.DoIdle(Sender: TObject);
begin
  //Writeln('Connectez vous sur http://localhost:8080 waiting for connection', Fcount);
end;

procedure TTestHTTPServer.CheckMimeLoaded;
begin
  If (Not MimeLoaded) and (MimeTypesFile<>'') then
    begin
    MimeTypes.LoadFromFile(MimeTypesFile);
    FMimeLoaded:=true;
    end;
end;

procedure TTestHTTPServer.HandleRequest(var ARequest: TFPHTTPConnectionRequest;
  var AResponse: TFPHTTPConnectionResponse);

Var
  T:TStringStream;
  s:string;
begin
  FUrl:=ARequest.Url;
  Writeln(FUrl);

  if pos('?',FURL) >0 then begin
    Split('?',FURL);
    FRep:=FListOfStrings[1][1];
    Fser.SendByte(ord(FRep));
    If Fser.CanRead(MX) then begin
       s:=Fser.RecvString(MX);
       Fvalue:=s;
       AResponse.ContentType:='text/plain';
       Writeln('Serving data: "',s,'". type Mime: ',AResponse.ContentType);
    end;
  end;

  try
    T:=TStringStream.create(s);
    s:='Access-Control-Allow-Origin: *'+#10#13+s;
    AResponse.ContentLength:=T.Size;
    AResponse.ContentStream:=T;
    AResponse.SendContent;
    AResponse.ContentStream:=Nil;
  finally
    T.Free;
  end;
  Inc(FCount);
  //If FCount>=500 then
    //Active:=False;
end;


begin
  
  Serv:=TTestHTTPServer.Create(Nil);
  try
    Serv.FListOfStrings:=TstringList.create;
    Serv.Fser:=Tblockserial.create;
    Serv.Fser.LinuxLock:=false;
    if not Serv.Fser.InstanceActive then Serv.Fser.connect(paramstr(1));
    Serv.Fser.config(115200,8,'N',SB1,False,False);
    Serv.Fser.purge();
    sleep(800);
    If Serv.Fser.CanRead(MX) then begin
       s:=Serv.Fser.RecvString(MX);
       Writeln(s);
    end;
    Writeln('Starting server');

    Serv.BaseDir:=ExtractFilePath('/home/mistert/public_html/files');
    {$ifdef unix}
    Serv.MimeTypesFile:='/etc/mime.types';
    {$endif}
    Serv.Threaded:=False;
    Serv.Port:=8080;
    Serv.AcceptIdleTimeout:=1000;
    Serv.OnAcceptIdle:=@Serv.DoIdle;
    Serv.Active:=True;
  finally
    Serv.Free;
  end;

end.
