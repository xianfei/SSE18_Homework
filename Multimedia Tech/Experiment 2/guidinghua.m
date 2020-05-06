y=(0:255)/256.0;
y=y/sum(y);         %归一化，使函数符合概率分布的sum(y)==1这样一个规律
% plot(y);          %待匹配的直方图
 
G=[];               %函数的累积直方图
for i=1:256
   G=[G sum(y(1:i))]; 
end
 
img=rgb2gray(imread('cat.jpg'));
[m, n]=size(img);
hist=imhist(img);       %待处理图像的直方图
p=hist/(m*n);           
figure,plot(hist)          %原图直方图
 
s=[];                   %待处理图像的累积直方图
for i=1:256
    s=[s sum(p(1:i))];
end
 
for i=1:256
    tmp{i}=G-s(i);
    tmp{i}=abs(tmp{i});         %因为要找距离最近的点，所以取绝对值
    [a, index(i)]=min(tmp{i});   %找到两个累积直方图距离最近的点
end
 
imgn=zeros(m,n);
for i=1:m
   for j=1:n
      imgn(i,j)=index(img(i,j)+1)-1;    %由原图的灰度通过索引映射到新的灰度
   end
end
 
imgn=uint8(imgn);
figure,imshow(imgn);
figure,plot(imhist(imgn));       %新图的直方图