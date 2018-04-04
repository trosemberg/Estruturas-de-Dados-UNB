clear 
clc

stud = 1e5;
apto = 1e2;

conservacao = randi([0 100],apto,1);
duplas(1,:) = randi([0 100],stud,1);
duplas(2,:) = randi([6 20],stud,1);

fileID = fopen('data.txt','w');
fprintf(fileID,'tempo\n');
fprintf(fileID,'%d %d\n',apto,stud);
fprintf(fileID,'%d\n',conservacao);
fprintf(fileID,'%d %d\n',duplas);
fclose(fileID);