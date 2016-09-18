#include <ESP8266WiFi.h>



const char* ssid = "WRITE YOUR ROUTER NAME HERE";

const char* password = "WRITE YOUR WIFI PASS HERE";



int ledPin = 13; // GPIO13 (D7 on Nodemcu)

WiFiServer server(80);



void setup() {

  Serial.begin(115200);

  delay(10);



  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);



  // Connect to WiFi network

  Serial.println();

  Serial.println();

  Serial.print("Connecting to ");

  Serial.println(ssid);



  WiFi.begin(ssid, password);



  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.println("WiFi connected");



  // Start the server

  server.begin();

  Serial.println("Server started");



  // Print the IP address

  Serial.print("Use this URL to connect: ");

  Serial.print("http://");

  Serial.print(WiFi.localIP());

  Serial.println("/");



}



void loop() {

  // Check if a client has connected

  WiFiClient client = server.available();

  if (!client) {

    return;

  }



  // Wait until the client sends some data

  Serial.println("new client");

  while(!client.available()){

    delay(1);

  }



  // Read the first line of the request

  String request = client.readStringUntil('\r');

  Serial.println(request);

  client.flush();



  // Match the request



  int value = LOW;

  if (request.indexOf("/LED=ON") != -1)  {

    client.println("HTTP/1.1 200 OK");

    digitalWrite(ledPin, HIGH);

    value = HIGH;

  }

  if (request.indexOf("/LED=OFF") != -1)  {

    client.println("HTTP/1.1 200 OK");

    digitalWrite(ledPin, LOW);

    value = LOW;

  }



// Set ledPin according to the request

//digitalWrite(ledPin, value);



  // Return the response

  if(request.indexOf("/LED=") == -1){client.println("HTTP/1.1 200 OK");

  client.println("Content-Type: text/html");

  client.println(""); //  do not forget this one

  client.println("<!DOCTYPE HTML>");

 client.println("<html>");

 client.println("<style> html{");

 client.println("height: 100%;");

 client.println("background-color: #ff9d79;");

 client.println("display: flex;");

 client.println("align-items: center;");

 client.println("justify-content: center;}");

 client.println("</style>");

 client.println("<svg viewBox='0 0 286 398'");

 client.println(" xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'

xml:space='preserve'  ");

 client.println(" x='0px' y='0px' width='286px' height='398px'");

 client.println(">");

 client.println(" <g id='Layer%201'>");

 client.println("   <path id='Ellipse' d='M 95.2857 282.7273 C 93.8259 205.9716 33 200.9362 33

142.8182 C 33 84.7002 86.1001 34 142 34 C 197.8999 34 251 84.7002 251 142.8182 C 251 200.9362 

188.3161 205.9716 188.7143 282.7273 L 95.2857 282.7273 Z' stroke='#ffffff' stroke-width='15' 

fill='#aaaaaa'/> ");

 client.println("   <path d='M 95.2857 282.7273 L 95.2857 344.9091 L 142 376 L 188.7143

344.9091 L 188.7143 282.7273 L 95.2857 282.7273 Z' stroke='#000000' stroke-width='15'

fill='#aaaaaa'/>");

 client.println("   <path id='wire' d='M 110.8571 271.1818 L 110.8571 142.8182

L 126.4286 189.4545 L 142 142.8182 L 157.5714 189.4545 L 173.1429 142.8182 L 173.1429

271.1818 ' stroke='#555555' stroke-width='11' fill='none'/>");

 client.println("   <path id='Line' d='M 103.5 350 L 187.5 311 ' stroke='#000000'

stroke-width='15' fill='none'/>");

 client.println("   <path id='Line2' d='M 98 323.5 L 179 285.5 ' stroke='#000000' 

stroke-width='15' fill='none'/>");

 client.println(" </g>");

 client.println("</svg>");

 client.println("<script>");

 client.println("   document.onreadystatechange = function(){ ");

 client.println("  if(document.readyState == 'complete'){");

client.println("  var bulb = document.getElementsByTagName('svg')[0];");

 client.println("var bulbElipse = document.getElementsByTagName('svg')[0].getElementById('Ellipse');");

 client.println("    var wire = document.getElementsByTagName('svg')[0].getElementById('wire');");

 client.println("    var onOff = 'off';");

 client.println("bulb.onclick = function(){");

 client.println("    var xhttp = new XMLHttpRequest();");

 client.println("    xhttp.onreadystatechange = function(e) {");

 client.println("     if (xhttp.readyState == 4 && xhttp.status == 200) {");   

 client.println("       if(onOff == 'off'){onOff = 'on';");

 client.println("       bulbElipse.style.fill = 'yellow';");

 client.println("       wire.style.stroke = 'orange';}");

 client.println("       else if(onOff == 'on'){onOff = 'off';");

 client.println("       bulbElipse.style.fill = '#aaaaaa';");

 client.println("       wire.style.stroke = '#555555';}");

 client.println("       }");

 client.println("   };");

 client.println("    var link;");

 client.println("        if(onOff == 'off'){link = '/LED=ON';}");

 client.println("        else if(onOff == 'on'){link = '/LED=OFF';}");

 client.println("xhttp.open('GET', link, true);");

 client.println("   xhttp.send();");

 client.println("} }}");

 client.println(" </script>");

 client.println("</html>");

  }



  delay(1);

  Serial.println("Client disonnected");

  Serial.println("");



}

