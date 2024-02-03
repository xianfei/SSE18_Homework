module com.fishlulu.javafxlearn {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.web;

    requires org.controlsfx.controls;
    requires org.kordamp.ikonli.javafx;
    requires org.kordamp.bootstrapfx.core;
    requires eu.hansolo.tilesfx;
    requires junit;

    exports com.fishlulu.javafxlearn.school.expr02;
    exports com.fishlulu.javafxlearn.school.finale.test03;
    opens com.fishlulu.javafxlearn.school.expr02 to javafx.fxml;
}