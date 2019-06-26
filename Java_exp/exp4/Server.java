import java.util.*;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.net.ServerSocket;
import javax.swing.*;

class ServerFrame extends JFrame{
    private JTextField port;  // 端口
    private JButton start;  //开始
    private JTextArea content;  // 消息框
    private JTextField cin;  // 输入框
    private JButton send;  // 发送按钮
    private static Socket socket;  // 套接字
    ServerFrame(){
        init();
        StartListen startListen = new StartListen();
        start.addActionListener(startListen);  // 添加startListenListen监听
        SendListen sendListen = new SendListen();
        send.addActionListener(sendListen);  // 添加sendListen监听
    }
    private void init(){
        setLayout(new FlowLayout());  // 设置窗体为流式布局
        setSize(380, 355);  // 设置窗体尺寸
        setLocation(200, 100);  // 设置窗体位置
        add(new JLabel("Port:"));  // 添加标签
        port = new JTextField("10005", 25);
        add(port);  // 添加端口
        start = new JButton("Start");
        add(start);  // 添加开始按钮
        content = new JTextArea(15, 35);
        JScrollPane scroll = new JScrollPane(content);
        add(scroll);  // 添加滚动内容
        add(new JLabel("Say:"));
        cin = new JTextField("Hello world!", 26);
        add(cin);  // 添加输入框
        send = new JButton("Send");
        add(send);  // 添加发送按钮
    }
    class StartListen implements ActionListener{
        public void actionPerformed(ActionEvent e){
            start.setEnabled(false);  // 点击后不可再次点击
            try{
                // 创建套接字对象, 从port读取端口号
                ServerSocket serverSocket = new ServerSocket(Integer.parseInt(port.getText()));
                socket = serverSocket.accept();
                // 创建打印输出流对象, 从套接字socket中获取输出流
                PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
                out.println("Connected.");
                content.append("Client connected" + "\n");  // 拼接字符串
                ServerThread serverThread = new ServerThread();  // 创建ServerThread对象st
                serverThread.start();  // 启动线程
            }
            catch (Exception ex){
                System.out.println("Start error!!");
            }
        }
    }
    class SendListen implements ActionListener{
        String message;
        public void actionPerformed(ActionEvent e){
            try{
                // 创建打印输出流对象, 从套接字socket中获取输出流
                PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
                message = cin.getText();
                if(!message.isEmpty()){
                    out.println(new Date() + "\n" + message);  // 打印时间戳和消息
                    content.append(new Date() + "\n 我:" + message + "\n");
                    out.flush();  // 清空缓存区
                }
                cin.setText("");
            }
            catch (Exception ex){
                System.out.println("Send error!!");
            }
        }
    }
    class ServerThread extends Thread{
        public void run(){
            try{
                // 创建缓冲输出流, 从套接字socket中获取输入流
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String message;
                while (true){
                    message = in.readLine();  // 按行读取
                    content.append(message + "\n");
                }
            }
            catch (Exception ex){
                System.out.println("Message error!!");
            }
        }
    }
}


public class Server {
    public static void main(String args[]){
        ServerFrame server = new ServerFrame();
        server.setTitle("Server");  // 窗体标题
        server.setVisible(true);  // 窗体可见
        server.setResizable(false);  // 不可调整窗体大小
        server.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  // 设置默认关闭
    }
}
