clear;clc;
filename = 'bat_sound.wav';
[y, Fs] = audioread(filename);
Fs = Fs/4
t=[1/Fs:1/Fs:length(y)/Fs];

data = y(:,1);
for i = 2:4
   data = data + y(:,i);
end

size(data)
A = 2*(data - min(data))/(max(data) - min(data)) - 1;
size(A)
B = downsample(A,4);
size(A)

figure(1)
spectrogram(A)
figure(2)
spectrogram(B)

%filename = 'bat_sound_post_1x.csv';
%csvwrite(filename,A)
%filename = 'bat_sound_post_4x.csv';
%csvwrite(filename,B)
