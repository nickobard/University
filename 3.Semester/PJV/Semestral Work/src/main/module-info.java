module pjv_the_drake_game {
    requires javafx.fxml;
    requires javafx.controls;

    opens assets.images;
    opens thedrake.client;
    opens thedrake.ui;
    opens thedrake.client.controllers;
}