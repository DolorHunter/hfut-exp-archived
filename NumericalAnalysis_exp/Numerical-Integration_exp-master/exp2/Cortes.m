 %复化牛顿科特斯求积算法% 复化梯形求积算法

% a, b为区间端点
% delta 为误差限
function [C, miss] = Cortes(a, b, delta)
% 假设步长
n=2;
h= (b-a)/n;
% 假设函数为y=sinx/x
% 从0开始积分
x=a + 0.00000001; 
%复化科特斯求积结果
C=0;
%循环标记loop
loop = 1;
while(loop)
    while(x<=b)
        C = C + (32 * sin(x + h / 4) / (x + h / 4) + 12 * sin(x + h / 2) / (x + h / 2) + 32 * sin(x + h * 3 / 4) /(x + h * 3 / 4) + 14 * sin(x + h) / (x + h)) * h / 90;
        x=x+h;
    end
    a=a + 0.00000001; % a=0分母为0无法计算.
    C = C + (7 * (sin(a) / a + sin(b) / b) * h / 90);
    miss = quad(@(x)sin(x)./x,0,1) - C;
    loop=0;
    if (miss < delta)
        loop = 0;
    else
        n = n * 2;
        h= (b-a)/n;
        x=a + 0.00000001;
        C=0;
    end
end
%输出结果
fprintf('当函数为y = sin(x)/x时, 复化科特斯求积结果为:%f, 误差为:%f', C, miss);
end