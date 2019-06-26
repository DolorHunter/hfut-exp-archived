import java.util.Random;

public class Main {
    public static void main(String args[]){
        Random random = new Random();
        // 生成5组2D坐标
        Point2D p2d[] = new Point2D[5];
        for(int i=0; i<5; ++i){
            int x = random.nextInt(100);
            int y = random.nextInt(100);
            p2d[i] = new Point2D(x, y);
            System.out.println("第"+i+"个2D坐标为");
            p2d[i].printInfo();
        }
        // 生成5组3D坐标
        Point3D p3d[] = new Point3D[5];
        for(int i=0; i<5; ++i){
            int x = random.nextInt(100);
            int y = random.nextInt(100);
            int z = random.nextInt(100);
            p3d[i] = new Point3D(x, y, z);
            System.out.println("第"+i+"个3D坐标为");
            p3d[i].printInfo();
        }
    }
}
