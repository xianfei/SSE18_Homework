
f=imread('车牌图像.jpg');   
%f=imread('播音员（gray）.jpg');
I1 = f;
I2 = area_growing(f,100);
I3 = OTSU_threshold_segmentation(f);
I4 = average_threshlod_segmentation(f);
figure;% 一个2x2显示区域
subplot(2, 2, 1); imshow(I1); title('原图像');
subplot(2, 2, 2); imshow(I2); title('区域生长');
subplot(2, 2, 3); imshow(I3, []); title('OTSU阈值分割图像');
subplot(2, 2, 4); imshow(I4, []); title('均值法阈值分割图像');
grid on



function [outputArg1] = OTSU_threshold_segmentation(inputArg1)
%   inputArg1 图像 gray
% outputArg1 = inputArg1;
if size(inputArg1,3)==3
    % 取blue通道，便于分隔车牌
    f = inputArg1(:,:,3);
else
    f = inputArg1;
end
[M,N] = size(f);
T = 0;
result_T = 0;
gmax = 0;
while (T<=255)
    g=f>=T;
    w0 = numel(f(g))/(M*N);
    w1 = numel(f(~g))/(M*N);
    p0 = mean(f(g));
    p1 = mean(f(~g));
    tmp = (w0 * w1) * (p0 - p1)^2;
    if (tmp > gmax)
        gmax = tmp;
        result_T =T;
    end
    T = T+1;
end
[height,width]=size(f);
Tmp = im2bw(f,result_T/255);
Tmp2 = inputArg1;
if size(inputArg1,3)==3
    for i2 = 1:height
        for j2 = 1:width
            if Tmp(i2,j2) == 0
                % 用于彩色抠像，保留彩色图片
                Tmp2(i2,j2,1)=0;
                Tmp2(i2,j2,2)=0;
                Tmp2(i2,j2,3)=0;
            end
        end
    end
else
    for i2 = 1:height
        for j2 = 1:width
            if Tmp(i2,j2) == 0
                % 用于黑白抠像，保留原始图片
                Tmp2(i2,j2)=0;
            end
        end
    end
end
    
outputArg1 = Tmp2;
end


function [outputArg1] = average_threshlod_segmentation(input_args)
% inputArg1 image gray
if size(input_args,3)==3
    % 取blue通道，便于分隔车牌
    f = input_args(:,:,3);
else
    f = input_args;
end
T = mean(mean(f));
[height,width]=size(f);
Tmp = im2bw(f,T/255);
Tmp2 = input_args;
if size(input_args,3)==3
    for i2 = 1:height
        for j2 = 1:width
            if Tmp(i2,j2) == 0
                % 用于彩色抠像，保留彩色图片
                Tmp2(i2,j2,1)=0;
                Tmp2(i2,j2,2)=0;
                Tmp2(i2,j2,3)=0;
            end
        end
    end
else
    for i2 = 1:height
        for j2 = 1:width
            if Tmp(i2,j2) == 0
                % 用于黑白抠像，保留原始图片
                Tmp2(i2,j2)=0;
            end
        end
    end
end
    
outputArg1 = Tmp2;
end

function [ output_args ] = area_growing( input_args, thredshold_input)
%   input_args raw image as gray format
%   thredshold_input input thredshold 
%   output_args convert image as gray format
if size(input_args,3)==3
    % 取blue通道，便于分隔车牌
    I = input_args(:,:,3);
else
    I = input_args;
end
% 显示原始图片
figure,imshow(input_args),title('选择区域生长起始点'); 
I=double(I);
[height,width]=size(I);
[y_double,x_double]=ginput(1);  %获得区域生长起始点
x=round(x_double);            %横坐标取整
y=round(y_double);            %纵坐标取整
seed=I(x,y);           %将生长起始点灰度值存入seed中
Tmp = zeros([height,width]);
Tmp(x,y) = 1;
sum = seed; 
seed_save=1;
seed_count = 1;
thredshold = thredshold_input;
close all;
while seed_count>0
    current_seed_gray_level = 0;
    seed_count = 0;
    for i=1:height
        for j=1:width
            if Tmp(i,j) == 1
                if (i-1)>0 && (i+1)<(height+1) ...
                        && (j-1)>0 && (j+1)<(width+1)%判断该点不在边缘
                    for m=-1:1
                        for n=-1:1
                            if Tmp(i+m,j+n)==0 && ...%首先该点周围的点应该没有被纳入生成的内容中
                                    abs(I(i+m,j+n)-seed) <= thredshold ... %其次，该点的灰度值需要小于我们设置的阈值
                                Tmp(i+m,j+n) = 1; % 成功判定，将内容输出到输出矩阵中
                                seed_count= seed_count+1;%种子数量加一
                                current_seed_gray_level = current_seed_gray_level + I(i+m,j+n); %累加灰度，最后求均值
                            end
                        end
                    end
                end
            end
        end
    end
end
seed_save = seed_save + seed_count;%获取所有种子的个数
sum = sum +current_seed_gray_level;
seed = sum/seed_save;%并计算灰度
Tmp2 = input_args;
if size(input_args,3)==3
    for i2 = 1:height
        for j2 = 1:width
            if Tmp(i2,j2) == 0
                % 用于彩色抠像，保留彩色图片
                Tmp2(i2,j2,1)=0;
                Tmp2(i2,j2,2)=0;
                Tmp2(i2,j2,3)=0;
            end
        end
    end
else
    for i2 = 1:height
        for j2 = 1:width
            if Tmp(i2,j2) == 0
                % 用于黑白抠像，保留原始图片
                Tmp2(i2,j2)=0;
            end
        end
    end
end
    
output_args = Tmp2;
end

