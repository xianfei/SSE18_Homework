import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.geometry.Insets;
import javafx.stage.Stage;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import java.io.File;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main extends Application {
    private int[] nums =new int[4]; // 存储四张牌是啥
    // 创建js解释器
    private ScriptEngine jse = new ScriptEngineManager().getEngineByName("JavaScript");

    @Override public void start(Stage primaryStage){
        // 顶端区域
        HBox upBox = new HBox(20);
        upBox.setPadding(new Insets(5,3,10,3));
        upBox.setAlignment(Pos.CENTER);
        TextField foundBar=new TextField();
        Button but1=new Button("Refresh");
        Button but2=new Button("Find a solution");
        upBox.getChildren().addAll(but2,foundBar,but1);
        // 卡牌区域
        HBox cardBox = new HBox(10);
        cardBox.setAlignment(Pos.CENTER);
        cardBox.setPadding(new Insets(0,5,10,5));
        putCards(cardBox);
        // 底部区域
        HBox botBox = new HBox(20);
        botBox.setAlignment(Pos.CENTER);
        TextField enterBar=new TextField();
        Button but3=new Button("Verify");
        botBox.getChildren().addAll(new Label("Enter an expression:"),enterBar,but3);
        Label label = new Label("Welcome!");
        // 把这些东东放到一起去
        VBox vbox = new VBox(5);
        vbox.setAlignment(Pos.CENTER);
        vbox.getChildren().addAll(upBox,cardBox,botBox,label);
        Scene scene=new Scene(vbox,500,280);
        // 注册按钮响应事件
        but1.setOnAction(event -> putCards(cardBox));
        but2.setOnAction(event -> foundBar.setText(CardGame.get24Points(nums)));
        but3.setOnAction(event -> {
            Pattern p = Pattern.compile("\\d+"); // 匹配数字
            Matcher m = p.matcher(enterBar.getText());
            // 验证表达式是否使用到牌中四个数
            for(int i=0;m.find( )&&i<4;i++) {
                boolean matched = false;
                for (int j = 0; j < 4; j++) {
                    String str = m.group();
                    if (Integer.parseInt(str) == nums[j]) matched = true;
                }
                if(!matched){
                    label.setText("表达式中数字与牌上数字不匹配！");
                    return;
                }
            }
            // 使用js脚本引擎计算表达式是否成立
            try{ if(Math.abs(Double.parseDouble(jse.eval(enterBar.getText()).toString())-24)<0.000001)
                label.setText("恭喜你！结果正确！ "+enterBar.getText()+" = "+Math.round(Double.parseDouble(jse.eval(enterBar.getText()).toString())));
                else label.setText("计算结果不等于24");
            }
            catch (Throwable obj){label.setText("表达式不合法！");}
        });
        primaryStage.setTitle("24 Points Card Game by xianfei");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    // 向hbox中随机放入卡片 并更新nums数组
    private void putCards(HBox cardBox){
        cardBox.getChildren().clear();
        for(int i=0;i<4;i++) {
            int randNum=(int) (Math.random() * 52 + 1);
            ImageView iv=new ImageView(new Image(
                    new File("card/" + randNum+ ".png").toURI().toString(),
                    140,140,true,true));
            cardBox.getChildren().addAll(iv);
            if(randNum%13==0)nums[i]=13;else nums[i]=randNum%13;
        }
    }
}