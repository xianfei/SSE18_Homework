import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.geometry.Pos;
import javafx.collections.ObservableList;
import javafx.scene.Node;
import javafx.scene.input.KeyCode;

public class main extends Application {
    private HBox textPane = new HBox(5);
    private VBox carsPane = new VBox(1);
    private ObservableList<Node> textFields = textPane.getChildren(); //包含文字及输入框，size=8
    private ObservableList<Node> cars = carsPane.getChildren(); //包含所有车 size=4

    @Override public void start(Stage primaryStage) {
        final int NUMBER_OF_CARS = 4;
        textPane.setAlignment(Pos.CENTER);
        // 把标签和输入框放在pane里面
        for (int i = 1; i <= NUMBER_OF_CARS; i++) textPane.getChildren().addAll(
                    new Label("Car " + i + ":"), new TextField());
        // 设置输入框的大小
        for (int i = 1; i < textFields.size(); i+= 2)
            ((TextField)textFields.get(i)).setPrefColumnCount(2);
        // 把车放在pane里面
        for (int i = 0; i < NUMBER_OF_CARS; i++) carsPane.getChildren().add(new Car());
        // 加个黑框框
        for (Node car: cars) car.setStyle("-fx-border-color: black");
        // 设置监听键盘事件
        for (int i = 1; i < textFields.size(); i += 2) {
            (textFields.get(i)).setOnKeyPressed(e -> {
                if (e.getCode() == KeyCode.ENTER) {
                    setSpeed();
                }
            });
        }
        VBox vbox = new VBox();
        vbox.getChildren().addAll(textPane,carsPane);
        Scene scene = new Scene(vbox, 400, 200);
        primaryStage.setTitle("Java Exercise 1 by wxf");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void setSpeed() {
        for (int i = 1, j = 0; i < textFields.size(); i += 2, j++) {
            if (((TextField)textFields.get(i)).getText().length() > 0) {
                // 设置速度 强行让1最快（手动doge
                ((Car)cars.get(j)).setSpeed(1.0/Double.parseDouble(((TextField)textFields.get(i)).getText())*100);
                ((Car)cars.get(j)).play();
            } else {
                ((Car)cars.get(j)).pause();
            }
        }
    }
}