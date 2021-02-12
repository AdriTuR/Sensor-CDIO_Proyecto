package com.LeafTech.gui.application;
	
import com.LeafTech.gui.libs.FunLevelGauge;
import com.LeafTech.gui.libs.SimpleSectionGauge;
import com.LeafTech.gui.managers.DataManager;

import eu.hansolo.medusa.Gauge;
import eu.hansolo.medusa.Gauge.ScaleDirection;
import eu.hansolo.medusa.Gauge.SkinType;
import eu.hansolo.medusa.GaugeBuilder;
import eu.hansolo.medusa.Section;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;

public class Main extends Application {
	
	private GridPane pane;
	private static Main instance;
	
    public static void main(String[] args) {
        launch(args);
        instance = new Main();
    }
    
    public Main() {
    	instance = this;
    }
    
	public static Main getInstance() {
		return instance;
	}
	
	public GridPane getMainPane() {
		return pane;
	}
	
    @Override
    public void start(Stage mainWindow) {
    	StackPane layout = new StackPane();
		pane = new GridPane();
		
		pane.setPadding(new Insets(10, 10, 10, 10)); 
		pane.setHgap(1);
		pane.setVgap(10);
		pane.setAlignment(Pos.CENTER); 
		layout.getChildren().add(pane);
		
		createGauges();

		mainWindow.centerOnScreen();
        mainWindow.setHeight(635);
        mainWindow.setWidth(1015);
    	mainWindow.getIcons().add(new Image(getClass().getResource("/res/icon.png").toExternalForm()));
        mainWindow.setTitle("LeafTech Demo");        
        mainWindow.setResizable(false);   
        
		mainWindow.setScene(new Scene(layout, 300, 250));
		mainWindow.getScene().getStylesheets().add("res/application.css");
		
		mainWindow.show();
    }

	@Override
	public void stop() throws Exception {
		if(DataManager.getInstance() != null){
			DataManager.getInstance().stopThread();
		}
		System.exit(0);
	}
	
	
	private void createGauges() {
		/////SALINITY GAUGE
		Gauge salinityGauge = createSalinityGauge();
		GridPane.setConstraints(salinityGauge, 260, 5);

		////HUMIDITY GAUGE
		FunLevelGauge humidityGauge = new FunLevelGauge();
		humidityGauge.setPrefSize(200, 200);
		GridPane.setConstraints(humidityGauge, 172, 5);
		
		//TEMPERATURE GAUGE
		SimpleSectionGauge temperatureGauge = new SimpleSectionGauge("", "°C",
                -10, 50,
                Color.rgb(69, 106, 207), Color.rgb(150, 150, 150, 0.25),
                true,
                new Section(-10, 15, Color.web("#56bdde")),
                new Section(26, 50, Color.rgb(216, 0, 39))); 
		
	    temperatureGauge.setPrefSize(200, 200);
	    GridPane.setConstraints(temperatureGauge, 40, 5);

	    //TEXT
	    StackPane textBox = new StackPane();
	    Text text = new Text("Last sync: ");
	    text.getStyleClass().add("text-color");
	    textBox.setAlignment(Pos.TOP_CENTER);
	    textBox.getChildren().add(text);
	    textBox.setPadding(new Insets(0, 0, 50, 0));
	    GridPane.setConstraints(textBox, 172, 0);
	    
	    //FINAL
	    pane.getChildren().addAll(salinityGauge, humidityGauge, temperatureGauge, textBox);
	    new DataManager(salinityGauge, humidityGauge, temperatureGauge, text);
		
	}
	
	private Gauge createSalinityGauge() {
		Gauge g = GaugeBuilder.create().skinType(SkinType.SLIM).decimals(0).minValue(0).maxValue(100).unit("%").build();
		g.setValueColor(Color.BLACK);
		g.setValue(0);
		g.setMaxHeight(200);
		g.setScaleDirection(ScaleDirection.BOTTOM_TO_TOP);
		g.setAnimated(true);
		g.setAnimationDuration(1500);
		
        g.setSectionsVisible(true);
        g.setSections(new Section(0, 50, Color.rgb(60, 130, 145, 0.7)),
                  new Section(50, 100, Color.rgb(200, 100, 0, 0.7)));
        return g;
	}
}