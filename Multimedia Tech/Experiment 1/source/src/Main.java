import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.image.*;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.FileChooser;
import javafx.stage.Stage;


public class Main extends Application {

    String defaultImage = "";
    Image image;

    @Override
    public void start(Stage primaryStage) {

        TextField textSrc = new TextField();
        textSrc.setText(defaultImage);
        Button btnDo = new Button("直方图");
        Button btnFile = new Button("浏览文件");
        Button btnUrl = new Button("打开URL");
        Button btnWB = new Button("灰度图");
        Button btn2z = new Button("二值图");
        ImageView imageView = new ImageView();
        imageView.setFitHeight(400);
        imageView.setFitWidth(500);
        imageView.setPreserveRatio(true);
        final CategoryAxis xAxis = new CategoryAxis();
        final NumberAxis yAxis = new NumberAxis();
        final LineChart<String, Number> chartHistogram
                = new LineChart<>(xAxis, yAxis);
        chartHistogram.setCreateSymbols(false);

        // 从url打开图像
        btnUrl.setOnAction(e -> {
            String imageSrc = textSrc.getText();
            image = new Image(imageSrc);
            imageView.setImage(image);
        });

        // 通过文件浏览打开图像
        btnFile.setOnAction(e -> {
            FileChooser fileChooser = new FileChooser();
            fileChooser.setTitle("Open Resource File");
            textSrc.setText(fileChooser.showOpenDialog(primaryStage).toURI().toString());
            String imageSrc = textSrc.getText();
            image = new Image(imageSrc);
            imageView.setImage(image);
        });

        // 转换为灰度图
        btnWB.setOnAction(e -> {
            WritableImage outputImage = new WritableImage((int) image.getWidth(), (int) image.getHeight());
            PixelReader pixelReader = image.getPixelReader();
            PixelWriter pixelWriter = outputImage.getPixelWriter();
            for (int i = 0; i < (int) image.getWidth(); i++) {
                for (int j = 0; j < (int) image.getHeight(); j++) {
                    double num = ((pixelReader.getColor(i, j).getBlue() + pixelReader.getColor(i, j).getGreen()
                            + pixelReader.getColor(i, j).getRed()) / 3);
                    pixelWriter.setColor(i, j, new Color(num, num, num, 1));
                }
            }
            image = outputImage;
            imageView.setImage(image);
        });

        // 转换为二值图
        btn2z.setOnAction(e -> {
            WritableImage outputImage = new WritableImage((int) image.getWidth(), (int) image.getHeight());
            PixelReader pixelReader = image.getPixelReader();
            PixelWriter pixelWriter = outputImage.getPixelWriter();
            for (int i = 0; i < (int) image.getWidth(); i++) {
                for (int j = 0; j < (int) image.getHeight(); j++) {
                    double num = ((pixelReader.getColor(i, j).getBlue() + pixelReader.getColor(i, j).getGreen()
                            + pixelReader.getColor(i, j).getRed()) / 3);
                    num = num > 0.5 ? 1 : 0;
                    pixelWriter.setColor(i, j, new Color(num, num, num, 1));
                }
            }
            image = outputImage;
            imageView.setImage(image);
        });

        // 绘制直方图
        btnDo.setOnAction(e -> {
            chartHistogram.getData().clear();
            ImageHistogram imageHistogram = new ImageHistogram(image);
            if (imageHistogram.isSuccess()) {
                chartHistogram.getData().addAll(
                        imageHistogram.getSeriesRed(),
                        imageHistogram.getSeriesGreen(),
                        imageHistogram.getSeriesBlue());
            }
        });

        HBox hBox = new HBox();
        hBox.getChildren().addAll(imageView, chartHistogram);
        HBox butBox = new HBox(20);
        butBox.getChildren().addAll(btnFile, btnUrl, btnWB, btn2z, btnDo);

        VBox vBox = new VBox(10);
        vBox.setPadding(new Insets(10, 10, 10, 10));
        vBox.getChildren().addAll(textSrc, butBox, hBox);

        StackPane root = new StackPane();
        root.getChildren().add(vBox);

        Scene scene = new Scene(root, 1000, 500);

        primaryStage.setTitle("Xianfei's CV");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

    class ImageHistogram {

        private Image image;
        private long red[] = new long[256];
        private long green[] = new long[256];
        private long blue[] = new long[256];

        XYChart.Series seriesRed;
        XYChart.Series seriesGreen;
        XYChart.Series seriesBlue;

        private boolean success;

        ImageHistogram(Image src) {
            image = src;
            success = false;

            //init
            for (int i = 0; i < 256; i++) {
                red[i] = green[i] = blue[i] = 0;
            }

            PixelReader pixelReader = image.getPixelReader();
            if (pixelReader == null) {
                return;
            }

            //count pixels
            for (int y = 0; y < image.getHeight(); y++) {
                for (int x = 0; x < image.getWidth(); x++) {
                    int argb = pixelReader.getArgb(x, y);
                    int r = (0xff & (argb >> 16));
                    int g = (0xff & (argb >> 8));
                    int b = (0xff & argb);

                    red[r]++;
                    green[g]++;
                    blue[b]++;

                }
            }

            seriesRed = new XYChart.Series();
            seriesGreen = new XYChart.Series();
            seriesBlue = new XYChart.Series();
            seriesRed.setName("red");
            seriesGreen.setName("green");
            seriesBlue.setName("blue");

            for (int i = 0; i < 256; i++) {
                seriesRed.getData().add(new XYChart.Data(String.valueOf(i), red[i]));
                seriesGreen.getData().add(new XYChart.Data(String.valueOf(i), green[i]));
                seriesBlue.getData().add(new XYChart.Data(String.valueOf(i), blue[i]));
            }

            success = true;
        }

        public boolean isSuccess() {
            return success;
        }

        public XYChart.Series getSeriesRed() {
            return seriesRed;
        }

        public XYChart.Series getSeriesGreen() {
            return seriesGreen;
        }

        public XYChart.Series getSeriesBlue() {
            return seriesBlue;
        }
    }

}
