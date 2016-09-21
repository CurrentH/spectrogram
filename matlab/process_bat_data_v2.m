%%  Input is a sound file of a size.
%   The data is made into a spectrogram which is 
%   save and can be used in a CNN.
clear;clc;
filename = 'bat_sound.wav';
[y, Fs] = audioread(filename);
Fs = Fs/4;
t=[1/Fs:1/Fs:length(y)/Fs];

data1 = y(:,1);

for i = 1:4
    data2 = y(:,i);
end

%%  Normalization of the data. 
%   This might not be a good idea anyway.

A = 2*(data1 - min(data1))/(max(data1) - min(data1)) - 1;

%%  Plot of the spectrograms.
%   
figure(1)
spectrogram(data2)
%figure(2)
%spectrogram(data2)
%figure(3)
%spectrogram(A)


