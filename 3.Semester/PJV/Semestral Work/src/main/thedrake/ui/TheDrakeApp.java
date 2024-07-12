package thedrake.ui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import thedrake.board.Board;
import thedrake.board.tiles.BoardTile;
import thedrake.game.GameState;
import thedrake.game.StandardDrakeSetup;
import thedrake.tiles.PositionFactory;

public class TheDrakeApp extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {

        Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
        primaryStage.setTitle("The Drake");
        primaryStage.setScene(new Scene(root, 900, 900));
        primaryStage.show();

    }

}
