import java.io.*;
public class CopyFile {
    public static void main(String[] args) {
        try {
            FileInputStream fis = new FileInputStream("CopyFile.java");
            FileOutputStream fos = new FileOutputStream("temp.txt");
            int read = fis.read();
            while ( read != -1 ) {
                fos.write(read);
                read = fis.read();
            }
            fis.close();
            fos.close();
        }
        catch (IOException e) {
            System.out.println(e);
        }
    }
}

