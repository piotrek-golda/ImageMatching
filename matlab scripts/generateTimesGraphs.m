W = [];
W_PI = [];
labels = {};
labels_PI = {};

csvTimesFiles = dir('*times.csv');
numfiles = length(csvTimesFiles);
if numfiles == 0
    error('folder does not contain any result files!')
end
for i = 1:numfiles
    fileName = csvTimesFiles(i).name;
    label = regexp(fileName,'[A-Z0-9]+','match');
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

boxplot(W,'Labels',labels, 'LabelOrientation', 'inline', 'Orientation', 'horizontal')
xlabel('Czas (s)')
ylabel(['Algorytmy' char(10)])
