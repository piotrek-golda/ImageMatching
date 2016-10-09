W = [];
W_PI = [];
labels = {};
labels_PI = {};

csvMatchesFiles = dir('*matches.csv');
csvMatchesFiles = flipud(csvMatchesFiles);
numfiles = length(csvMatchesFiles);
if numfiles == 0
    error('folder does not contain any result files!')
end
csvMatchesFiles(1).name
for i = 1:numfiles
    fileName = csvMatchesFiles(i).name;
    label = regexp(fileName,'[A-Z0-9\-]+','match');
    if length(label) == 2
        label = strcat(label(1), {' '}, label(2));
    else
        label = strcat(label(1), {' '}, label(2), {' '}, label(3));
    end
%     fileName = 'SIFT_PI_default_matches.csv';
    M = csvread(fileName);
    M2 = transpose(M);
    
    if length( findstr( char(label), 'PI') ) == 0
        W = [W M2(:)];
        labels = [labels label ];
    else
        W_PI = [W_PI M2(:)];
        labels_PI = [labels_PI label ];
    end
end
W= [W W_PI];
labels = [labels labels_PI];

boxplot(W,'Labels',labels, 'LabelOrientation', 'inline', 'Orientation', 'horizontal')
xlabel('True matches')
ylabel(['Algorytmy' char(10)])
set(gca,'FontSize',10,'XTickLabelRotation',90)


W = [];
W_PI = [];
labels = {};
labels_PI = {};

csvMatchesFiles = dir('*matches.csv');
numfiles = length(csvMatchesFiles);
if numfiles == 0
    error('folder does not contain any result files!')
end
csvMatchesFiles(1).name
for i = 1:numfiles
    fileName = csvMatchesFiles(i).name;
    label = regexp(fileName,'[A-Z0-9\-]+','match');
    if length(label) == 2
        label = strcat(label(1), {' '}, label(2));
    else
        label = strcat(label(1), {' '}, label(2), {' '}, label(3));
    end
%     fileName = 'SIFT_PI_default_matches.csv';
    M = csvread(fileName);
    M2 = transpose(M);
    
    if length( findstr( char(label), 'PI') ) == 0
        W = [W M2(:)];
        labels = [labels label ];
    else
        W_PI = [W_PI M2(:)];
        labels_PI = [labels_PI label ];
    end
end
W= [W_PI W];
labels = [labels_PI labels];


[p,tbl,stats] = kruskalwallis(W,labels)
c = multcompare(stats);
xlabel('True matches')
ylabel(['Algorytmy' char(10)])
title('')
pause(5)

xlabel('True matches')
