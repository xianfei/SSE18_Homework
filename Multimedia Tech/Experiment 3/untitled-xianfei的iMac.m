
f=imread('车牌图像.jpg');   
if isa(f,'rgb')
    f = rgb2gray(f);
end
I1 = f;
I3 = function_OTSU_threshold_segmentation(f);
I4 = function_average_threshlod_segmentation(f);
figure;% 开一个新的图像区域
subplot(2, 2, 1); imshow(I1); title('原图像');
subplot(2, 2, 3); imshow(I3, []); title('OTSU阈值分割图像');
subplot(2, 2, 4); imshow(I4, []); title('均值法阈值分割图像');
grid on


function [outputArg1] = function_OTSU_threshold_segmentation(inputArg1)
%   inputArg1 图像 gray
% outputArg1 = inputArg1;
f = inputArg1;
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
    % w0 + w1 = 1
    % numel(f(g)) + numel(f(~g)) =  M * N
    %Tn=0.5*(mean(f(g))+mean(f(~g))); % 备注 mean(f(g)) 是取 f 中所有像素大于 T 的均值 
    tmp = (w0 * w1) * (p0 - p1)^2;
    if (tmp > gmax)
        gmax = tmp;
        result_T =T;
    end
    T = T+1;
end
outputArg1 = im2bw(f,result_T/255);
end


function [outputArg1] = function_average_threshlod_segmentation(inputArg1)
% inputArg1 image gray
f = rgb2gray(inputArg1);
T = mean(mean(f));
outputArg1 = im2bw(f,T/255);
end

%UNTITLED9 此处显示有关此函数的摘要
%   此处显示详细说明

