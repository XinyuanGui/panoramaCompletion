function [  ] = Output( matrix,path_name )
%UNTITLED �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
file=fopen(path_name,'wt');
[row,col]=size(matrix);
for i=1:row
    for j=1:col
        fprintf(file,'%d ',matrix(i,j));
    end;
    fprintf(file,'\n');
end;

end

