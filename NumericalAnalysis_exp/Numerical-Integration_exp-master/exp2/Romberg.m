%龙贝格算法

% a, b为区间端点
% delta 为误差限
function [R, miss] = Romberg(a, b, delta)
% 假设步长
n=2;
h= (b-a)/n;
% 假设函数为y=sinx/x

%龙贝格求积结果
R=0;
a=a+0.000000001; % 防止分母为0.
T1=sin(a)/a+sin(b)/b;
k=1;
miss=5;
while(miss>=delta)
S=0;
x=a+h/2;
    while(x<b)
    S=S+sin(x)/x;
    x = x+h;
    end
    T2 = T1/2+h/2*S;
    S2 = T2 + 1/3 *(T2 - T1);
    if k == 1
        k = k + 1;
        h = h / 2;
        T1 = T2;
        S1 = S2;
    else
        C2 = S2 + 1/15*(S2-S1);
        if k == 2
            C1 = C2;
            k = k + 1;
            h = h / 2;
            T1 = T2;
            S1 = S2;
        else
          R2 = C2 + 1/63 * (C2-C1);
             if k == 3
                R1 = R2;
                C1 = C2;
                k = k + 1;
                h = h / 2;
                T1 = T2;
                S1 = S2;
             else
                 if abs(R2-R1)>=delta
                     R1 = R2;
                     C1 = C2;
                     k = k + 1;
                     h = h / 2;
                     T1 = T2;
                     S1 = S2;
                 else
                     miss = abs(R2-R1);
                     % 输出结果
                     fprintf('当函数为y = sin(x)/x时, 龙贝格公式结果为:%f, 误差为:%f', R2, miss);
                     break;
                 end
             end
        end
    end
end
end