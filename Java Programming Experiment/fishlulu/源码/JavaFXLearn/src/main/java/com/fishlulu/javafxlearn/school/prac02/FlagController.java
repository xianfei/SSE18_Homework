package com.fishlulu.javafxlearn.school.prac02;

import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class FlagController {

    @FXML
    private Label welcomeText;

    @FXML
    protected void onHelloButtonClick() {
        welcomeText.setText("Sucessfully clicked!");
    }
}