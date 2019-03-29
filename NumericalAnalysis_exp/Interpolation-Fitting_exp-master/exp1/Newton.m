%二次牛顿插值
%x为预测点
function [p, fx, miss] = Newton(x)
l=1;
p=0;
for i = 1:9
    if i==1 || i==4|| i==9
        x_k=i;
        for j = 1:9
            if j==1 || j==4 || j==9
                x_j=j;
                if x_k~=x_j
                    l = l * (x_k-x_j);
                end
            end
        end
        y_k = sqrt(x);
        p = p + y_k/l;
    end
end
%计算真实值
fx = sqrt(x);
%计算误差
miss = fx-p;
%输出结果
fprintf('预测值: %f\t精确值: %f\t误差: %f\n', p, fx, miss);
end