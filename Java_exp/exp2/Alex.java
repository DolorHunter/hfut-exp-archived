import java.util.*;
import java.lang.Math;
class Point2D
{
    int X, Y;
    public Point2D()
    {
        //无形参的构造方法，一定要有
    }
    public Point2D(int x,int y)
    {
        this.X=x;
        this.Y=y;
    }
    public void offset(int a, int b)//2D平移方法
    {
        this.X+=a;
        this.Y+=b;
    }
    public void printInfo()
    {
        System.out.println("X= "+this.X+"\nY= "+this.Y);
    }
    public void distance(Point2D p)
    {
        double DT=1;
        DT*=(this.X-p.X)*(this.X-p.X)+(this.Y-p.Y)*(this.Y-p.Y);
        System.out.println("2D 距离："+Math.sqrt(DT));
    }
}
class Point3D extends Point2D
{
    int Z;
    public Point3D()
    {
        //无形参的构造方法，一定要有
    }
    public Point3D(int x,int y,int z)
    {
        this.X=x;
        this.Y=y;
        this.Z=z;
    }
    Point3D(Point2D p,int z)
    {
        this.X=p.X;
        this.Y=p.Y;
        this.Z=z;
    }
    public void offset(int a, int b,int c)//3D平移方法
    {
        this.X+=a;
        this.Y+=b;
        this.Z+=c;
    }
    public void printInfo()
    {
        System.out.println("X= "+this.X+"\nY= "+this.Y+"\nZ= "+this.Z);
    }
    public void distance(Point3D p)
    {
        double DT=1;
        DT*=(this.X-p.X)*(this.X-p.X)+(this.Y-p.Y)*(this.Y-p.Y)+(this.Z-p.Z)*(this.Z-p.Z);
        System.out.println("3D 距离："+Math.sqrt(DT));
    }
}
public class Alex
{
    public static void main(String args[])
    {
        System.out.print("*****录入信息*****\n");
        Scanner cin = new Scanner(System.in);
        int x[]=new int[2];
        int y[]=new int[2];
        int z[]=new int[2];
        for(int i=1;i<3;i++)
        {
            System.out.print("录入第 "+ i +" 个 2D 平面坐标\n    输入横坐标X：");
            x[i-1]=cin.nextInt();
            System.out.print("    输入纵坐标Y：");
            y[i-1]=cin.nextInt();
        }
        Point2D _2Dp1=new Point2D(x[0],y[0]);
        Point2D _2Dp2=new Point2D(x[1],y[1]);
        _2Dp1.printInfo();
        _2Dp2.printInfo();
        System.out.println("现在将 2D 平面图，3D 化，请给出 竖坐标Z的值");
        for(int i=1;i<3;i++)
        {
            System.out.print("录入第 "+ i +" 个 3D 平面坐标\n    输入竖坐标Z：");
            z[i-1]=cin.nextInt();
        }
        Point3D _3Dp1=new Point3D(_2Dp1,z[0]);
        Point3D _3Dp2=new Point3D(_2Dp2,z[1]);
        _3Dp1.printInfo();
        _3Dp2.printInfo();
        System.out.println("平移 2D 图形：");
        for(int i=1;i<3;i++)
        {
            System.out.print("录入第 "+ i +" 个 2D 图形的平移量\n    输入横坐标X的平移量：");
            x[i-1]=cin.nextInt();
            System.out.print("    输入纵坐标Y的平移量：");
            y[i-1]=cin.nextInt();
        }
        _2Dp1.offset(x[0], y[0]);
        _2Dp2.offset(x[1], y[1]);
        _2Dp1.printInfo();
        _2Dp2.printInfo();
        for(int i=1;i<3;i++)
        {
            System.out.print("录入第 "+ i +" 个 3D 图形的平移量\n    输入竖坐标Z的平移量：");
            z[i-1]=cin.nextInt();
        }
        _3Dp1.offset(x[0],y[0],z[0]);
        _3Dp2.offset(x[1],y[1],z[1]);
        _3Dp1.printInfo();
        _3Dp2.printInfo();
        _2Dp1.distance(_2Dp2);
        _3Dp1.distance(_3Dp2);
    }
}
