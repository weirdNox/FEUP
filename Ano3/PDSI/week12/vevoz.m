[x,FS]=audioread('voz.wav');
x=x*10000.0; % factor de escala para regulação da cor em grafico 3D
N=1024;
shift=N/2;
nwin=(floor(1+(length(x)-N)/shift));
data=zeros(N/2,nwin);
win=hanning(N);
for k=0:nwin-1
    tmpdata=x(1+k*shift:k*shift+N);
    figure(1)
    plot(tmpdata)
    xlabel('Amostras \rightarrow');
    ylabel('Amplitude \rightarrow');
    title('Segmento temporal de voz');
    tmpdata=tmpdata.*win;
    tmpdata=20*log10(1+abs(fft(tmpdata)));
    figure(2)
    plot([0:N/2-1]*FS/N,tmpdata(1:N/2))
    xlabel('Frequência (Hz)');
    ylabel('Magnitude (dB)');
    title('Magnitude espectral');
    data(:,k+1)=tmpdata(1:N/2);
    figure(3)
    meshz([1:nwin], [0:N/2-1], data)
    xlabel('Segmentos \rightarrow');
    ylabel('Frequência \leftarrow');
    zlabel('Magnitude \rightarrow');
    pause;
end

figure(3)
meshz([1:nwin], [0:N/2-1], data)
xlabel('Segmentos \rightarrow');
ylabel('Frequência \leftarrow');
zlabel('Magnitude \rightarrow');
grid off
axis off

figure(4)
spectrogram(x,hann(N),shift,FS,'yaxis')