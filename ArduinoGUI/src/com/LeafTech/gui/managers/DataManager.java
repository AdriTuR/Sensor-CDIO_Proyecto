package com.LeafTech.gui.managers;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;
import java.text.SimpleDateFormat;
import java.time.ZoneId;
import java.util.Calendar;
import java.util.TimeZone;

import com.LeafTech.gui.application.Main;
import com.LeafTech.gui.libs.FunLevelGauge;
import com.LeafTech.gui.libs.SimpleSectionGauge;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonIOException;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.JsonSyntaxException;

import eu.hansolo.medusa.Gauge;
import javafx.scene.text.Text;

public class DataManager {

	private static DataManager instance;
	private DataThread t;
	
	private Gauge salinityGauge;
	private FunLevelGauge humidityGauge;
	private SimpleSectionGauge temperatureGauge;
	
	private Text text;
	
	private double lastHumidityVal = -1;
	
	public DataManager(Gauge s, FunLevelGauge h, SimpleSectionGauge t, Text textBox2) {
		this.salinityGauge = s;
		this.humidityGauge = h;
		this.temperatureGauge = t;	
		this.text = textBox2;
		
		instance = this;

		new java.util.Timer().schedule( 
				new java.util.TimerTask() {
					@Override
					public void run() {
						startThread();
					}
				}, 500);
	}

	
	public void startThread() {
		t = new DataThread();
		t.start();	
	}
	
	public void stopThread() {
		t.stopThread();
	}
	
	private void updateText(String t){
		if(t == null) {
			return;
		}
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/M/yyyy HH:mm:ss");
		dateFormat.setTimeZone(TimeZone.getTimeZone(ZoneId.of("Europe/Madrid")));
		Calendar cal = Calendar.getInstance();

		text.setText("Last sync: " + dateFormat.format(cal.getTime()));
	}
	
	public static DataManager getInstance() {
		return instance;
	}
	
	private void updateSalinity(double val) {
		salinityGauge.setValue(val);
	}
	
	private void updateHumidity(double val) {
		if(val != lastHumidityVal) {
			humidityGauge.setLevel(val/100);
			lastHumidityVal = val;
		}
	}
	
	private void updateTemperature(double val) {
		temperatureGauge.setValue(val);
	}
	
	private void updateLuminosity(int val) {
		String style = "";
		switch(val) {
		case 0:
			style = "night";
			break;
		case 1:
			style = "cloudly";
			break;
		case 2:
			style = "day";
			break;
		}
		Main.getInstance().getMainPane().getStyleClass().clear();
		Main.getInstance().getMainPane().getStyleClass().add(style);
	}
	
	class DataThread extends Thread {
		private boolean run = true;
		
		public void stopThread() {
			run = false;
		}
		
		@Override
		public void run() {
			while(run) {
				URLConnection request = null;
				try {
					URL url = new URL("https://dweet.io/get/latest/dweet/for/cdiocurso2020g09");
					request = url.openConnection();
					request.setReadTimeout(8000);
					request.connect();
				} catch (IOException e) {
					e.printStackTrace();
				}

				JsonParser parser = new JsonParser();
				JsonElement rootElement = null;

				try {
					rootElement = parser.parse(new InputStreamReader((InputStream) request.getContent()));
					JsonObject parsedJson = rootElement.getAsJsonObject();
					JsonArray info = parsedJson.get("with").getAsJsonArray();

					JsonObject test = info.get(0).getAsJsonObject();

					JsonObject content = test.get("content").getAsJsonObject();
					updateSalinity(content.get("Salinity").getAsInt());
					updateHumidity(content.get("Humidity").getAsInt());
					updateTemperature(content.get("Temperature").getAsInt());
					updateLuminosity(content.get("Luminity").getAsInt());

					updateText(test.get("created").getAsString());

				} catch (JsonIOException | JsonSyntaxException | IOException | NullPointerException e) {
					e.printStackTrace();
				}
				
				try {
					Thread.sleep(7000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}
}