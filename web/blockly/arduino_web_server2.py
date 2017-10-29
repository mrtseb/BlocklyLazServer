#!/usr/bin/env python
 
from http.server import BaseHTTPRequestHandler, HTTPServer
 
arduino_cmd = None
#cherche le fichier arduino
def writefile(s,mode = True):
    dirname = "D:/mrt/xampp/htdocs/blockly"
    debug = os.path.join(dirname, "default") + ".txt"
    if mode:
        f2 = open(debug, "a+")
    else:
        f2 = open(debug, "w+")
    f2.write(s+"\n")
    f2.close
def get_arduino_command():
    """Attempt to find or guess the path to the Arduino binary."""
    global arduino_cmd
    if not arduino_cmd:
        if platform.system() == "Darwin":
            arduino_cmd_guesses = ["/Applications/Arduino.app/Contents/MacOS/Arduino"]
        elif platform.system() == "Windows":
            print("Windows!")
            arduino_cmd_guesses = [
                "D:/mrt/techno/progs/Arduino/arduino_debug.exe",
                "D:/mrt/techno/progs/Arduino/arduino.exe"                
            ]
        else:
            arduino_cmd_guesses = []

        for guess in arduino_cmd_guesses:
            if os.path.exists(guess):
                logging.info("Found Arduino command at %s", guess)
                arduino_cmd = guess
                break
        else:
            logging.info("Couldn't find Arduino command; hoping it's on the path!")
            arduino_cmd = "arduino"
    return arduino_cmd

#lit le port COM en base de reg
def guess_port_name():
    """Attempt to guess a port name that we might find an Arduino on."""
    portname = None
    if platform.system() == "Windows":
        import _winreg as winreg
        key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM")
        # We'll guess it's the last COM port.
        for i in itertools.count():
            try:
                portname = winreg.EnumValue(key, i)[1]
            except WindowsError:
                break
    else:
        # We'll guess it's the first non-bluetooth tty. or cu. prefixed device
        ttys = [filename for filename in os.listdir("/dev")
                if (filename.startswith("tty.") or filename.startswith("cu."))
                and not "luetooth" in filename]
        ttys.sort(key=lambda k:(k.startswith("cu."), k))
        if ttys:
            portname = "/dev/" + ttys[0]
    logging.info("Guessing port name as %s", portname)
    return portname 
 
# HTTPRequestHandler class
class Handler(BaseHTTPRequestHandler):
 
  # GET
  def do_HEAD(self):
        """Send response headers"""
        if self.path != "/":
            return BaseHTTPRequestHandler.do_HEAD(self)
        self.send_response(200)
        self.send_header("content-type", "text/html;charset=utf-8")
        self.send_header('Access-Control-Allow-Origin', '*')
        self.end_headers()

  def do_GET(self):
        """Send page text"""
        if self.path != "/":
            self.send_response(200)
            Send headers
            self.send_header('Content-type','text/html')
            self.end_headers()
            message = "Hello world!"
            self.wfile.write(bytes(message, "utf8"))
            return
        else:
            self.send_response(302)
            self.send_header("Location", "/blockly/apps/blocklyduino/index.html")
            self.end_headers()
  #def do_GET(self):
        # Send response status code
        #self.send_response(200)
 
        # Send headers
        #self.send_header('Content-type','text/html')
        #self.end_headers()
 
        # Send message back to client
        #message = "Hello world!"
        # Write content as utf-8 data
        #self.wfile.write(bytes(message, "utf8"))
        #return
  def do_POST(self):
        """Save new page text and display it"""
        if self.path != "/":
            return BaseHTTPRequestHandler.do_POST(self)
 
if __name__ == '__main__':
    print ("Blocklyduino can now be accessed at http://127.0.0.1:8080/")
    server = HTTPServer(("127.0.0.1", 8080), Handler)
    server.pages = {}
    server.serve_forever()
    print('starting server...')
 
 
 
