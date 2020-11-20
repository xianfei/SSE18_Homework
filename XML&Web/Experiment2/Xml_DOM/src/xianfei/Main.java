package xianfei;

import javax.xml.parsers.*;
import org.w3c.dom.*;
import java.io.File;
import java.io.FileOutputStream;

public class Main {

    static StringBuilder abc_output = new StringBuilder();
    static StringBuilder ibm_output = new StringBuilder();
    static String input_URL = "/Users/xianfei/Downloads/实验2 基于Java编程语言的DOM & SAX实验/ipo.xml";

    public static void main(String args[]) {
        try {
            //得到DOM解析器的工厂实例
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            //从DOM工厂中获得DOM解析器
            DocumentBuilder dbBuilder = dbFactory.newDocumentBuilder();
            //把要解析的xml文档读入DOM解析器
            Document document = dbBuilder.parse(new File(input_URL));
            abc_output.append("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n" + "<purchaseOrders>\n" +
                    "  <ABC_COMP>\n" );
            ibm_output.append("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"+"<purchaseOrders>\n" +
                    "  <IBM_COMP>\n");
            // 处理根节点
            basedLoop(document);
            abc_output.append("  </ABC_COMP>\n" +
                    "</purchaseOrders>\n");
            ibm_output.append("  </IBM_COMP>\n" +
                    "</purchaseOrders>\n");
        } catch (Exception e) {
            e.printStackTrace();
        }
        try {
            FileOutputStream abc_fos = new FileOutputStream("ABC_COMP.xml");
            abc_fos.write(abc_output.toString().getBytes());
            abc_fos.close();
            FileOutputStream ibm_fos = new FileOutputStream("IBM_COMP.xml");
            ibm_fos.write(ibm_output.toString().getBytes());
            ibm_fos.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void basedLoop(Node node) { // 处理根节点
        if (node == null) {
            return;
        }
        int type = node.getNodeType();
        switch (type) {
            case Node.DOCUMENT_NODE ->
                basedLoop(((Document) node).getDocumentElement());
            case Node.ELEMENT_NODE -> {
                boolean isAbc = false, isIBM = false;
                int length = (node.getAttributes() != null) ? node.getAttributes().getLength() : 0;
                Attr attributes[] = new Attr[length];
                for (int loopIndex = 0; loopIndex < length; loopIndex++)
                    attributes[loopIndex] = (Attr) node.getAttributes().item(loopIndex);
                // 检测是abc还是ibm
                for (Attr attribute : attributes) {
                    if (attribute.getNodeName().equals("comp_name") && attribute.getNodeValue().equals("ABC"))
                        isAbc = true;
                    if (attribute.getNodeName().equals("comp_name") && attribute.getNodeValue().equals("IBM"))
                        isIBM = true;
                }
                if (isAbc) {
                    processChild(node, abc_output);
                } else if (isIBM) {
                    processChild(node, ibm_output);
                } else {
                    NodeList childNodes = node.getChildNodes();
                    if (childNodes != null) {
                        length = childNodes.getLength();
                        for (int loopIndex = 0; loopIndex < length; loopIndex++) {
                            basedLoop(childNodes.item(loopIndex));
                        }
                    }
                }
            }
        }
    }

    private static void processChild(Node node, StringBuilder abc_output) {
        int length;
        abc_output.append("    <purchaseOrder>");
        NodeList childNodes = node.getChildNodes();
        if (childNodes != null) {
            length = childNodes.getLength();
            for (int loopIndex = 0; loopIndex < length; loopIndex++) {
                childLoop(abc_output, childNodes.item(loopIndex), "      ");
            }
            abc_output.append("\n    </purchaseOrder>\n");
        }
    }

    static boolean isNewLine = true;

    private static void childLoop(StringBuilder target, Node node, String indentation) {
        if (node == null) return;
        int type = node.getNodeType();
        switch (type) {
            case Node.ATTRIBUTE_NODE, Node.ELEMENT_NODE -> { // 对于属性和元素节点
                target.append("\n").append(indentation); // 换行与缩进
                target.append("<");
                target.append(node.getNodeName());
                target.append(">");

                int length = (node.getAttributes() != null) ?
                        node.getAttributes().getLength() : 0;
                Attr attributes[] = new Attr[length];
                for (int loopIndex = 0; loopIndex < length; loopIndex++)
                    attributes[loopIndex] = (Attr) node.getAttributes().item(loopIndex);

                for (int loopIndex = 0; loopIndex < attributes.length;
                     loopIndex++) {
                    target.append("\n").append(indentation).append("  "); // 换行与缩进
                    Attr attribute = attributes[loopIndex];
                    target.append("<");
                    target.append(attribute.getNodeName());
                    target.append(">");
                    target.append(attribute.getNodeValue());
                    target.append("</");
                    target.append(attribute.getNodeName());
                    target.append(">");
                }
                NodeList childNodes = node.getChildNodes();
                if (childNodes != null) {
                    length = childNodes.getLength();
                    for (int loopIndex = 0; loopIndex < length; loopIndex++)
                        childLoop(target, childNodes.item(loopIndex), indentation + "  ");
                }
                if (isNewLine) target.append("\n").append(indentation); // 换行与缩进
                isNewLine = true;
                target.append("</");
                target.append(node.getNodeName());
                target.append(">");
            }
            case Node.TEXT_NODE -> { // 对于文字
                String trimmedText = node.getNodeValue().trim();
                if (trimmedText.length() > 0) {
                    target.append(trimmedText);
                    isNewLine = false;
                }
            }
        }
    }
}
