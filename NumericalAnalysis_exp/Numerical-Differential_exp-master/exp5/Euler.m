% 欧拉法求数值解

% 输入求解区间，初值，数值解个数

function [] = Euler(a, b, y0, n)

h = (b-a)/n;
x=a;
y=y0;

while x < b
    y = y + h * Derivative(x,y);
    % 输出结果
    fprintf('Xn=%f\tYn=%f\tYXn=%f\tΔ=%f\n', x, y, Value(x), Value(x)-y);
    x = x + h;
end

end