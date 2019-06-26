import java.util.*;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.net.*;
import javax.swing.*;

class ClientFrame extends JFrame{
    private JTextField ip;  // 主机地址
    private JTextField port;  // 端口
    private JButton connect;  // 连接按钮
    private JTextArea content;  // 消息框
    private JTextField cin;  // 输入框
    private JButton send;  // 发送按钮
    private Socket socket;  // 套接字
    ClientFrame(){
        init();
        ConnectListen connectListen = new ConnectListen();
        connect.addActionListener(connectListen);  // 添加connectListen监听
        SendListen sendListen = new SendListen();
        send.addActionListener(sendListen);  // 添加sendListen监听
    }
    private void init(){
        setLayout(new FlowLayout());  // 设置窗体为流式布局
        setSize(380, 355);  // 设置窗体尺寸
        setLocation(800, 100);  // 设置窗体位置
        add(new JLabel("IP:"));  // 添加标签
        ip = new JTextField("127.0.0.1", 8);
        add(ip);  // 添加主机地址
        add(new JLabel("Port:"));
        port = new JTextField("10005", 8);
        add(port);  // 添加端口
        connect = new JButton("Connect");
        add(connect);  // 添加连接按钮
        content = new JTextArea(15, 35);
        JScrollPane scroll = new JScrollPane(content);
        add(scroll);  // 添加滚动内容
        add(new JLabel("Say:"));
        cin = new JTextField("Hello world!", 26);
        add(cin);  // 添加输入框
        send = new JButton("Send");
        add(send);  // 添加发送按钮
    }
    class ConnectListen implements ActionListener{
        public void actionPerformed(ActionEvent e){
            connect.setEnabled(false);  // 点击后不可再次点击
            try{
                content.setText("Connecting to server..\n");  // 显示正在连接
                // 定义socket主机和端口, 创建套接字对象, 从port读取端口号
                socket = new Socket(ip.getText(), Integer.parseInt(port.getText()));
                ClientThread clientThread = new ClientThread();  // 定义服务器线程
                clientThread.start();  // 启动线程
            }
            catch (Exception ex){
                System.out.println("Connect error!!");
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
    class ClientThread extends Thread{
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


public class Client {
    public static void main(String args[]){
        ClientFrame client = new ClientFrame();
        client.setTitle("Client");  // 窗体标题
        client.setVisible(true);  // 窗体可见
        client.setResizable(false);  // 不可调整窗体大小
        client.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  // 设置默认关闭
    }
}
