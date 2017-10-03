source_image='E:\ѧϰ\��ͼʵ��\1234.png';
patch_image='E:\ѧϰ\��ͼʵ��\1234_patch.png';
source_image=imread(source_image);
source_image=rgb2gray(source_image);
% patch_image=imread(patch_image);
% patch_image=rgb2gray(patch_image);
patch_image=source_image(2:60,3:80);
patch_y8=GXYfft(patch_image);
image_y8=GXYfft(source_image);

n=16;
patch_num=size(patch_y8{1,1},1)*size(patch_y8{1,1},2);
image_num=size(image_y8{1,1},1)*size(image_y8{1,1},2);
%���feature������;
patch_features=zeros(n,patch_num);
image_features=zeros(n,image_num);
n=16;
ordinal=zeros(2,n);%�������η��ʵ�����ֵ;��һ��Ϊ��ֵ���ڶ���Ϊ��Ӧ��ֵ;
sum=2;
i=1;
direction=1;
while n-i>=0
    for j=1:sum-1
        if(rem(direction,2)==1)
            ordinal(1,i)=j;
            ordinal(2,i)=sum-j;
            i=i+1;
            if n-i<0
                break;
            end;
        else
            ordinal(1,i)=sum-j;
            ordinal(2,i)=j;
            i=i+1;
            if n-i<0
                break;
            end;
        end;
    end;
    sum=sum+1;
    direction=direction+1;
end;
for i=1:n
    patch_features(i,:)=reshape(patch_y8{ordinal(1,i),ordinal(2,i)}',1,patch_num);
    image_features(i,:)=reshape(image_y8{ordinal(1,i),ordinal(2,i)}',1,image_num);
end;

patch_offset(patch_features,image_features,patch_image',source_image);
% Output(patch_features,'E:\����\�����޸�.Attachments\matlabʵ������\patch_feature.txt');
% Output(image_features,'E:\����\�����޸�.Attachments\matlabʵ������\image_features.txt');
% Output(source_image,'E:\����\�����޸�.Attachments\matlabʵ������\source_image.txt');
% Output(patch_image,'E:\����\�����޸�.Attachments\matlabʵ������\patch_image.txt');