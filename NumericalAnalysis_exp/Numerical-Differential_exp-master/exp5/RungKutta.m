% 龙格库塔法求数值解

% 输入求解区间，初值，数值解个数

function [] = RungKutta(a, b, y0, n)

h = (b-a)/n;
x=a;
y=y0;

while x < b
    K1 = Derivative(x, y);
    K2 = Derivative(x + h / 2, y + h / 2 * K1);
    K3 = Derivative(x + h / 2, y + h / 2 * K2);
    K4 = Derivative(x + h, y + h * K3);
    y = y + h / 6 * (K1 + 2 * K2 + 2 * K3 + K4);
    % 输出结果
    fprintf('Xn=%f\tYn=%f\tYXn=%f\tΔ=%f\n', x, y, Value(x), Value(x)-y);
    x = x + h;
end

end