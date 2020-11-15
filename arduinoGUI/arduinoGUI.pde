import processing.serial.*;
import controlP5.*;

Serial arduinoConsole;
ControlP5 cp5;

PFont font;
PImage bg;

String val1, val2, val1V, val2V;
boolean debug = false;

void setup() {
  try {
    arduinoConsole = new Serial(this, "COM3", 9600);
  }
  catch(RuntimeException e) {
    print("Can't connect with Arduino Board (Serial)");
    System.exit(0);
  }

  size(650, 300);
  bg = loadImage("/res/bg.jpg");
  val1 = "";
  val2 = "";
  val1V = "";
  val2V = "";

  surface.setTitle("LeafTech Demo");

  cp5 = new ControlP5(this);
  cp5.addButton("DEBUG")
    .setPosition(560, 250)
    .setSize(80, 40)
    .setColorBackground(color( 130, 161, 82 ))
    .onPress(new CallbackListener() {
      public void controlEvent(CallbackEvent theEvent) {
        if(debug) {
          debug = false;
        }else{
          debug = true;
        }
      }});;
}


void draw() { 
  background(bg);

  fill(255, 255, 255);
  textFont(createFont("Bahnschrift", 64));
  text(val1, 100, 125);
  delay(150);
  text(val2, 430, 125);

  if(debug) {
    textFont(createFont("Bahnschrift", 16));
    text(val1V, 80, 160);
    text(val2V, 455, 160);
  }

  while (arduinoConsole.available() > 0) {
    delay(2000);

    String[] data = readData();
    if (data.length > 0 && data[0] != null) {
      if (data[0] != null) {
        String[] extra = data[0].split(";");
        val1 = extra[0];
        if (debug) {
          val1V = "aRead: " + extra[1];
        }
      }

      if (data.length > 1 && data[1] != null) {
        String[] extra = data[1].split(";");
        val2 = extra[0];
        if (debug) {
          val2V = "aRead: " + extra[1];
        }
      }
    }
  }
}

String[] readData() {
  String readData = arduinoConsole.readString();
  return readData.split("/");
}
