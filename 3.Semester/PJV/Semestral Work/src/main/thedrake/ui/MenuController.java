package thedrake.ui;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import thedrake.board.Board;
import thedrake.board.tiles.BoardTile;
import thedrake.game.GameState;
import thedrake.game.StandardDrakeSetup;
import thedrake.tiles.PositionFactory;

import java.net.URL;
import java.util.ResourceBundle;

import static thedrake.ui.BoardView.newSampleGameState;

public class MenuController implements Initializable {

    @FXML
    private Pane mainMenu;

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

    }

    public void onExit() {
        Platform.exit();
    }

    public void onTwoPlayersGame(ActionEvent event) {
        Scene mainMenuScene = ((Node) event.getSource()).getScene();
        Stage stage = (Stage) mainMenuScene.getWindow();
        BoardView boardView = new BoardView(newSampleGameState(), mainMenuScene);
        stage.setScene(new Scene(boardView, 900, 900));
        stage.setTitle("The Drake");
        stage.show();
    }


}
