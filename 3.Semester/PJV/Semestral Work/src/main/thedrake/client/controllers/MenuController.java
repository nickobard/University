package thedrake.client.controllers;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.layout.Pane;

import java.net.URL;
import java.util.ResourceBundle;

public class MenuController implements Initializable {

    @FXML
    private Pane mainMenu;

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

    }

    public void onExit() {
        Platform.exit();
    }
}
