module leafTechArduino {
	exports com.LeafTech.gui.managers;
	exports com.LeafTech.gui.libs;
	exports com.LeafTech.gui.application;

	requires eu.hansolo.medusa;
	requires javafx.base;
	requires javafx.controls;
	requires javafx.graphics;
	requires java.desktop;
	requires com.fazecast.jSerialComm;
	requires com.google.gson;
}