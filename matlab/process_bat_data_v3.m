%%  Generically load all .wav files
%   
clc;clear;

folder = '/home/theis/Dropbox/Bat/sound/';
%files = dir(fullfile(folder,'*.wav'));
files = '/home/theis/Dropbox/Bat/sound/2016-05-27-first_sound.wav';
[data, fs] = audioread(files);

data2 = data(:,1);
    for i = 2:size(data,2)
        data2 = data(:,i);
    end

spectrogram(data2,[],[],[],fs, 'yaxis')
%%  Make a spectrogram of the sound file
%   and save it as a .png

fh=figure

for k = 1:length(files)
    baseFileName = files(k).name;
    fullFileName = fullfile(folder, baseFileName);
    fprintf(1, 'Now reading %s\n', fullFileName);
    [data, fs] = audioread(fullFileName);
    
    data2 = data(:,1);
    for i = 2:size(data,2)
        data2 = data(:,i);
    end
    set(gca,'LooseInset',get(gca,'TightInset'))
    figure(fh); 
    spectrogram(data2);

    %frm = getframe(fh);
    %Figname = strcat(baseFileName,'.jpg');
    %imwrite(frm.cdata, Figname);
end



