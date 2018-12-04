import processing.serial.*;
Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port

String[] cmdPushed = {"/Users/klarefrank/Dev/gitbit-output/pushed.sh"};
String[] cmdPulled = {"/Users/klarefrank/Dev/gitbit-output/pulled.sh"};

void setup(){
  
  // Arduino to processing
  // https://learn.sparkfun.com/tutorials/connecting-arduino-to-processing/all
  String portName = Serial.list()[2]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
  
}

void draw(){
  
  // Push and Pull via soft potentiometer
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.readStringUntil('\n');  // read it and store it in val
  } 
  if (val != null){
    if (val.contains("push")) {
      try { 
        Runtime.getRuntime().exec(cmdPushed);
        val = "";
      } catch (IOException e) {
        System.err.println(e);
      }
    }  
    if (val.contains("pull")) {
      try { 
        Runtime.getRuntime().exec(cmdPulled);
        val = "";
      } catch (IOException e) {
        System.err.println(e);
      }
    }
  }
}
