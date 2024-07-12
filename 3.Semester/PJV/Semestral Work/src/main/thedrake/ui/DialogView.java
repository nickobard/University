package thedrake.ui;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.stage.Stage;

public class DialogView extends GridPane {


    public DialogView(String winnerText, BoardView parentView) {

        setPadding(new Insets(15));
        setVgap(30);
        setPrefSize(300, 300);
        setAlignment(Pos.CENTER);

        Label winnerLabel = new Label(winnerText);
        winnerLabel.setAlignment(Pos.CENTER);
        winnerLabel.setPrefSize(200, 50);
        winnerLabel.setFont(new Font(18));
        add(winnerLabel, 0, 0);


        Button menuBtn = new Button("Go to main menu!");
        menuBtn.setPrefSize(200, 30);
        menuBtn.setOnAction((event -> {
            Stage stage = parentView.getStage();
            stage.setScene(parentView.getMainMenusScene());
            stage.show();
            closeDialog();
        }));
        add(menuBtn, 0, 1);

        Button newGameBtn = new Button("Play new game!");
        newGameBtn.setPrefSize(200, 30);
        newGameBtn.setOnAction((event -> {
            parentView.reloadGame();
            closeDialog();
        }));
        add(newGameBtn, 0, 2);
    }


    private void closeDialog() {
        ((Stage) getScene().getWindow()).close();
    }
}
