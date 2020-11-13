import controlP5.*;
import processing.serial.*;

Serial arduinoConsole;
ControlP5 cp5;
PFont font;
String val1, val2;

void setup() {
  arduinoConsole = new Serial(this, "COM3", 9600);

  size(650, 300);

  val1 = "";
  val2 = "";
}


void draw() { 
  background(109, 147, 178);
  textFont(createFont("Arial", 32));
  text("HUMEDAD (%)", 215, 80);
  text("SALINIDAD (%)", 215, 200);

  fill(0, 255, 0);
  textFont(createFont("Arial", 32));
  text(val2, 285, 240);
  delay(100);
  text(val1, 285, 120);

  while (arduinoConsole.available() > 0) {
    delay(2000);

    String[] data = readData();
    if (data.length > 0 && data[0] != null) {
      if (data[0] != null) {
        val1 = data[0];
      }

      if (data.length > 1 && data[1] != null) {
        val2 = data[1];
      }
    }
  }
}

String[] readData() {
  String readData = arduinoConsole.readString();
  String[] data = readData.split(";");

  return data;
}
