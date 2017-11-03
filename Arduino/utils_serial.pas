unit utils_serial;

{$mode objfpc}{$H+}

interface



uses
  Classes, SysUtils;

function lire_com:Tstrings;
implementation
uses registry;

function lire_com:Tstrings;
var
  reg: TRegistry;
  t:Tstringlist;
  st:Tstrings;

  i: Integer;
begin
  reg := TRegistry.Create;
  t:=Tstringlist.create;
  try
    reg.RootKey := HKEY_LOCAL_MACHINE;
    reg.OpenKeyReadOnly('hardware\devicemap\serialcomm');
    lire_com := TstringList.Create;
    st := TstringList.Create;

    try
      reg.GetValueNames(st);
      for i := 0 to st.Count - 1 do
        t.Add(reg.Readstring(st.strings[i]));
    finally
      st.Free;
      lire_com:=t;
    end;
    reg.CloseKey;
  finally
    reg.Free;
  end;
end;

end.

