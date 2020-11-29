import processing.serial.*;
import controlP5.*;

Serial arduinoConsole;
ControlP5 cp5;

PFont font;
PImage bg;

String val1, val2, val3, val1V, val2V, val3V;

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
  val3 = "";

  surface.setTitle("LeafTech Demo");

  cp5 = new ControlP5(this);
  cp5.addButton("DEBUG")
    .setPosition(560, 250)
    .setSize(80, 40)
    .setColorBackground(color( 130, 161, 82 ))
    .onPress(new CallbackListener() {
    public void controlEvent(CallbackEvent theEvent) {
      if (debug) {
        debug = false;
      } else {
        debug = true;
      }
    }
  });
}

void runDataThread(){
  new Thread(new Runnable() {
    public void run() {
      if (arduinoConsole.available() > 0) {
      delay(2000);
      String[] data = readData();
      if (data != null) {
        showData(data, 1);
        showData(data, 2);
        showData(data, 3);
      }
     }
    }
  }).start();
  
}
  
void draw() { 
  background(bg);

  fill(255, 255, 255);
  textFont(createFont("Bahnschrift", 64));
  text(val2, 100, 125);
  delay(150);
  text(val1, 430, 125);

  if (debug) {
    textFont(createFont("Bahnschrift", 16));
    text(val2V, 80, 160);
    text(val1V, 455, 160);
  }
  
  runDataThread();
}

void showData(String[] data, int n) {    
  String valLect = "";
  String val = "";

  if (data.length > n-1 && data[n-1] != null) {
    String[] extra = data[n-1].split(";");
    val = extra[0];
    if (debug) {
      valLect = "aRead: " + extra[1];
    }
  } else {
    return;
  }

  switch(n) {
  case 1:
    val1V = valLect;
    val1 = val;
    println("aaa");
    break;
  case 2:
    val2V = valLect;
    val2 = val;
    break;
  case 3:
    val3V = valLect;
    val3 = val;
    break;
  }
}


String[] readData() {
  String readData = arduinoConsole.readString();
  if (readData != null) {
    return readData.split("/");
  } else {
    return null;
  }
}
