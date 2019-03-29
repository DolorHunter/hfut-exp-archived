%分段插值: 拉格朗日一次插值
%x为预测点
function [p, fx, miss] = segLagrange(x)
%确定区间
for i = -5:4
    if i<x && x<i+1
            x_min = i;
            x_max = i+1;
    end
end
%插值点的真实值
f_min = 1/(1+x_min*x_min);
f_max = 1/(1+x_max*x_max);
%预测点的真实值
fx = 1/(1+x*x);
%计算系数l
l1 = (x-x_min)/(x_max-x_min);
l2 = (x-x_max)/(x_min-x_max);
%计算预测值
p = l1 * f_max + l2 * f_min;
%计算误差
miss = fx-p;
%输出结果
fprintf('预测值: %f\t精确值: %f\t误差: %f\n', p, fx, miss);
end