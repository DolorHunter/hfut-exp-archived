% 牛顿下山法求解方程

% 输入初值，误差限，迭代最大次数，下山最大次数
% 输出近似根各布下山因子

function lamda = NewtonDownhill(x0, loss, max_time)
% lamda 为 下山因子
lamda = 1;

x = x0;
y = 0;
x_kp = x - lamda * Value(x, y)/Derivative(x, y); % xk+1

% step为步数
step = 1;
while abs(Value(x, y)-x) > loss & step <= max_time
    x = x - lamda * Value(x, y)/Derivative(x, y); % k步
    x_kp = x_kp - lamda * Value(x, y)/Derivative(x, y); % 永远是k+1步
    % 输出因子 lamda
    fprintf('当前为第%d步\t下山因子为:%f\t近似根为:%f\n', step, lamda, x);
    step = step + 1;
    lamda = lamda / 2; % 因子折半
end
if abs(Value(x_kp, y)) < abs(Value(x, y))
    fprintf('经过了%d步运算后,下山失败.', step);
else
    fprintf('经过了%d步运算后,下山成功.', step);

end