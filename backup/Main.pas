unit Main;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  Buttons, ExtCtrls, IdHTTPServer, IdCustomHTTPServer, IdContext, cef3lcl,
  cef3intf, cef3types, cef3lib, gettext, jclsysutils, registry, dos,
  utils_serial,md5;


type

  { TForm1 }

  TForm1 = class(TForm)
    BitBtn1: TBitBtn;
    Button1: TButton;
    Chromium1: TChromium;
    ComboBox1: TComboBox;
    cmbCard: TComboBox;
    IdHTTPServer1: TIdHTTPServer;
    IdleTimer1: TIdleTimer;
    Label1: TLabel;
    Label2: TLabel;
    Memo1: TMemo;
    Panel1: TPanel;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    RadioButton3: TRadioButton;
    RadioButton4: TRadioButton;
    RadioButton5: TRadioButton;
    procedure BitBtn1Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure cmbCardChange(Sender: TObject);

    procedure ComboBox1Change(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure IdHTTPServer1CommandGet(AContext: TIdContext;
      ARequestInfo: TIdHTTPRequestInfo; AResponseInfo: TIdHTTPResponseInfo);
    procedure IdleTimer1Timer(Sender: TObject);
    procedure RadioButton1Click(Sender: TObject);
    procedure RadioButton2Change(Sender: TObject);
    procedure RadioButton2Click(Sender: TObject);
    procedure RadioButton3Click(Sender: TObject);
    procedure RadioButton4Click(Sender: TObject);
    procedure RadioButton5Change(Sender: TObject);
    procedure RadioButton5Click(Sender: TObject);
  private
     FPort, Fbaud:string;
     handler:TTextHandler;
     procedure gereTexte(const Txt: string);
  public

  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure Tform1.gereTexte(const Txt: string);
begin
self.Memo1.Lines.add(UTF8Encode(Txt));
end;

procedure TForm1.IdHTTPServer1CommandGet(AContext: TIdContext;
  ARequestInfo: TIdHTTPRequestInfo; AResponseInfo: TIdHTTPResponseInfo);

var s,t,postData,sParent,sParent2:string;
    code:TstringList;
    f:file;
    i:integer;
    mustUpload,fn,lang:string;
    ThisMoment:TdateTime;
    mem:Tmemorystream;
begin
  code:=Tstringlist.create;
  case ARequestInfo.Command of
   //sert les pages blockly html/js/images
  'GET':
  begin
    //self.Memo1.Lines.Add(ARequestinfo.RawHTTPCommand);
    s:=copy(ARequestInfo.Document,2,length(ARequestInfo.Document)-1);
    //if pos('favicon',s)>0 then exit;
    if trim(s)='' then s:='index.html';
    AResponseInfo.ResponseNo := 200;
    if pos('.html',s)>0 then AResponseInfo.ContentType := 'text/html';
    if pos('.png',s)>0 then AResponseInfo.ContentType := 'image/png';
     if pos('.jpeg',s)>0 then AResponseInfo.ContentType := 'image/jpeg';
    //
    self.Memo1.Lines.Add(ExtractFilePath(Application.exename)+'web\'+s);
    if fileexists(ExtractFilePath(Application.exename)+'web\'+s) then begin
    AResponseInfo.ContentStream := TMemoryStream.Create;
    try
        mem:=Tmemorystream.Create;
        mem.LoadFromFile(ExtractFilePath(Application.exename)+'web\'+s);
        AResponseInfo.ContentStream.CopyFrom(mem,mem.Size);
        AResponseInfo.ContentStream.Position := 0;
        AResponseInfo.WriteContent;
    finally
        AResponseInfo.ContentStream := nil;
        mem.free;
    end;
    end;
  end;
  'POST':
  begin
       self.Memo1.Clear;
       //self.Memo1.lines.add(ARequestInfo.RawHTTPCommand);
       //self.Memo1.lines.add(ARequestInfo.RawHeaders.CommaText);
       //self.Memo1.lines.Add(ARequestInfo.RawHeaders.CommaText);
    try
       ARequestInfo.PostStream.Position := 0;
       SetLength(postData, ARequestInfo.PostStream.Size);
       ARequestInfo.PostStream.Read(Pointer(postData)^, Length(postData));
       self.Memo1.lines.AddText(postData);

       mustUpload:=self.Memo1.Lines[3];
       fn:=self.Memo1.Lines[7];
       lang:=self.Memo1.Lines[11];
       fn:=fn+'.'+lang;

       t:=MD5Print(md5String(FormatDateTime('ddmmYYYY h:m:s',ThisMoment)));
       s:=ExtractFilePath(ParamStr(0));

       if mustUpload='false' then s:=s+'examples\'+lang+'\'+fn else
       begin
         s:='.\Arduino\ino\'+getenv('userdomain')+'_'+getenv('username')+'_'+'default.ino';
         form1.caption:=s;
       end;
       if fileexists(s) then deletefile(s);
       for i:=15 to self.Memo1.Lines.Count-2 do code.Add(memo1.lines[i]);
       code.SaveToFile(s);
       if mustUpload='false' then exit;
       //pour le reste on uploade !
       if self.ComboBox1.items.Count<1 then begin
          memo1.lines.add('Il faut brancher la carte SVP!');
          exit;
       end;

       execute('cmd /c cd .\Arduino'+ ' & .\bat\compilHEX.bat',handler,true,nil);
       s:= 'cmd /c cd .\Arduino'+ ' & .\bat\uploadHEX.bat '+FPort+' '+Fbaud;
       memo1.lines.add(s);
       if FPort<> '' then execute(s,handler,true,nil);
       //AResponseInfo.ContentType := 'text/plain';
       AResponseInfo.ResponseNo := 200;
       AResponseInfo.ContentStream:=TMemoryStream.Create;
       AResponseInfo.ContentStream.Position := 0;
       AResponseInfo.WriteContent;
    finally
        AResponseInfo.ContentStream := nil;
        code.free;
    end;
  end; //end post
end;//end case
end;

procedure TForm1.IdleTimer1Timer(Sender: TObject);
begin
  self.BitBtn1Click(self);
  if not self.IdHTTPServer1.Active then self.Button1Click(self);
end;

procedure TForm1.RadioButton1Click(Sender: TObject);
begin
   self.Chromium1.Load(Utf8Decode('http://localhost:8080/apps/ardublockly/index.html'));
end;

procedure TForm1.RadioButton2Change(Sender: TObject);
begin

end;

procedure TForm1.RadioButton2Click(Sender: TObject);
begin
  self.Chromium1.Load(Utf8Decode('http://localhost:8080/codejs/demos/code/index.html?lang=fr'));
end;

procedure TForm1.RadioButton3Click(Sender: TObject);
begin
    self.Chromium1.Load(Utf8decode('http://localhost:8080/blocklyg/fr/turtle.html?lang=fr&level=10'));
end;

procedure TForm1.RadioButton4Click(Sender: TObject);
begin
  self.Chromium1.Load(Utf8Decode('http://localhost:8080/blocklyg/fr/movie.html?lang=fr '));
end;

procedure TForm1.RadioButton5Change(Sender: TObject);
begin

end;

procedure TForm1.RadioButton5Click(Sender: TObject);
begin
  self.Chromium1.Load(Utf8Decode('http://localhost:8080/blocksCAD/index.html?lang=fr'));
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  PrjPath: ustring;
  Lang, FallbackLang: string;
begin
  handler:=@self.gereTexte;
  //self.IdHTTPServer1.Active:=true;
  PrjPath := UTF8Decode(GetCurrentDir + PathDelim);
  CefLocalesDirPath := PrjPath + 'Resources\locales';
  GetLanguageIDs(Lang, FallbackLang);
  CefLocale := UTF8Decode(FallbackLang);
  self.BitBtn1Click(self);
  self.cmbCard.itemindex:=0;
  self.Fbaud:='115200';
end;

procedure TForm1.BitBtn1Click(Sender: TObject);

begin
 self.ComboBox1.text:='';
 self.ComboBox1.Items:=lire_com;
 if self.combobox1.Items.count>=1 then begin self.ComboBox1.ItemIndex:=self.combobox1.Items.count-1;  Fport:=self.ComboBox1.text; end;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  self.IdHTTPServer1.Active:=true;
  self.Chromium1.Load(Utf8Decode('http://localhost:8080/apps/ardublockly/index.html'));
end;

procedure TForm1.cmbCardChange(Sender: TObject);
begin
  if cmbCard.ItemIndex=0 then self.Fbaud:='115200';
  if cmbCard.ItemIndex=1 then self.Fbaud:='57600';
end;



procedure TForm1.ComboBox1Change(Sender: TObject);
begin
  self.FPort:=self.ComboBox1.Items[self.ComboBox1.ItemIndex];
end;

procedure TForm1.FormActivate(Sender: TObject);
begin

end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
  //self.IdHTTPServer1.Active:=false;
  self.IdHTTPServer1.Free;
end;

end.

