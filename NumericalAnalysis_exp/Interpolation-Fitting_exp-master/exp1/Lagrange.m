%拉格朗日插值
%x为预测点
function [p, fx, miss]=Lagrange(x)
l=1;
p=0;
for i = -5:5
    x_k = i;
    for j = -5:5
        x_j = j;
        if x_k~=x_j
            l = l * (x-x_j) / (x_k-x_j);
        end
    end
    y_k = 1/(1+x_k*x_k);
    p = p + l * y_k;
end
%计算真实值
fx = 1/(1+x*x);
%计算误差
miss = fx-p;
%输出结果
fprintf('预测值: %f\t精确值: %f\t误差: %f\n', p, fx, miss);
end