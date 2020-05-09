img=imread('lena_noise.bmp');
figure,imshow(img);


x1=1/9*[1 1 1;
    1 1 1;
    1 1 1];
out1 = imfilter(img,x1);
figure,imshow(out1);


x2=1/16*[1 2 1;
    2 4 2;
    1 2 1];
out2 = imfilter(img,x2);
figure,imshow(out2);


[ height, width ] = size(img);
out3 = img;
for i = 1: height-3+1
    for j = 1:width-3+1
        mb = img( i:(i+3-1),  j:(j+3-1) );
        mb = mb(:);
        mm = median(mb);
        out3( i+(3-1)/2,  j+(3-1)/2 ) = mm;
    end
end
figure,imshow(out3);
    