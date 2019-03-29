% 复化辛普森求积算法

% a, b为区间端点
% delta 为误差限
function [S, miss] = Simpson(a, b, delta)
% 假设步长
n=2;
h= (b-a)/n;
% 假设函数为y=sinx/x
% 从0开始积分
x=a + 0.00000001; 
%复化辛普森求积结果
S=0;
%循环标记loop
loop = 1;
while(loop)
    while(x<=b)
        S = S+(sin(x) / x + 4 * sin(x + h/2) / (x + h / 2) + sin(x+h)/(x+h))*h/6;
        x=x+h;
    end
    miss = quad(@(x)sin(x)./x,0,1) - S;
    if (miss < delta)
        loop = 0;
    else
        n = n * 2;
        h= (b-a)/n;
        x=a + 0.00000001;
        S=0;
    end
end
%输出结果
fprintf('当函数为y = sin(x)/x时, 复化辛普森求积结果为:%f, 误差为:%f', S, miss);
end