package xianfei;

import java.io.*;
import org.xml.sax.*;
import javax.xml.parsers.*;
import org.xml.sax.helpers.DefaultHandler;

public class Main extends DefaultHandler {
    static String inputURL = "/Users/xianfei/Downloads/实验2 基于Java编程语言的DOM & SAX实验/ipo.xml";

    public static void main(String args[]) {
        SAXParserFactory saxFactory = SAXParserFactory.newInstance();
        try {
            SAXParser saxParser = saxFactory.newSAXParser();
            saxParser.parse(new File(inputURL), new Main());
        } catch (Throwable ignored) {
        }
    }

    public void startElement(String uri, String localName,
                             String qualifiedName, Attributes attributes) {
        if (attributes != null) {
            int numberAttributes = attributes.getLength();
            for (int loopIndex = 0; loopIndex < numberAttributes; loopIndex++) {
                System.out.print("<");
                System.out.print(attributes.getQName(loopIndex));
                System.out.print(":");
                System.out.print(attributes.getValue(loopIndex));
                System.out.println(">");
            }
        }
    }
}
