import processing.serial.*;
import controlP5.*;

Serial arduinoConsole;
ControlP5 cp5;

PFont font;
PImage bg, bgNoche, bgNublado;

String val1, val2, val3, val1V, val2V, val3V, val4, val4V;

boolean debug = false;

void setup() {
  try {
    arduinoConsole = new Serial(this, "COM3", 9600);
  }catch(RuntimeException e) {
    print("Can't connect with Arduino Board (Serial)");
    System.exit(0);
  }

  size(1000, 600);
  bg = loadImage("/res/bg.jpg");
  bgNoche = loadImage("/res/bg1.jpg");
  bgNublado = loadImage("/res/bg2.jpg");
  val1 = "";
  val2 = "";
  val3 = "";
  val4 = "";

  surface.setTitle("LeafTech Demo");

  cp5 = new ControlP5(this);
  cp5.addButton("DEBUG")
    .setPosition(900, 550)
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
        showData(data, 4);
      }
     }
    }
  }).start(); 
}
  
void draw() { 
  if(!val4.isEmpty()){
    try{
      int val4F = Integer.parseInt(val4);
      val4 = "Soleado";
      background(bg);
      if(val4F == 0){
        background(bgNoche);
        val4 = "Noche";
      }else if(val4F == 1){
        background(bgNublado);
        val4 = "Nublado";
      }
    }catch(NumberFormatException e){}
  }else{
    background(bg);
  }
  
  fill(255, 255, 255);
  textFont(createFont("Bahnschrift", 54));
  text(val2, 140, 315);
  delay(200);
  text(val1, 750, 315);
  delay(200);
  text(val3, 120, 125);
  delay(400);
  if(val4.length() > 2){
    text(val4, 735, 120);
  }
    
  if (debug) {
    textFont(createFont("Bahnschrift", 16));
    text(val2V, 120, 340);
    text(val1V, 780, 340);
    text(val3V, 120, 150);
    text(val4V, 780, 140); 
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
      if(extra.length > 1 && extra[1] != null){
        valLect = "aRead: " + extra[1];
      }
    }
  } else {
    return;
  }

  switch(n) {
  case 1:
    val1V = valLect;
    val1 = val;
    break;
  case 2:
    val2V = valLect;
    val2 = val;
    break;
  case 3:
    val3V = valLect;
    val3 = val;
    break;
  case 4:
    val4 = val;
    val4V = valLect;
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
