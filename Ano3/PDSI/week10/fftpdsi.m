%
% Processamento Digital de Sinal
% EEC0026            2018/2019
% Semana 10
% AJF/SRC
%

FS=48828.125;
N=64; N2=N/2;
n=[0:N-1];

for freq=3000:25:10000,
    %% x=sin(2*pi*freq*n/FS);
    %% x=sawtooth(2*pi*freq*n/FS);
    x=square(2*pi*freq*n/FS);

    X=fft(x);
    MAG=X.*conj(X);

    figure(1);
    plot(n/FS*1000,x)
    axis([0 N/FS*1000 -1.2 1.2]);
    title('sinal temporal');
    xlabel('Tempo (ms)');
    ylabel('Amplitude');

    figure(2)
    stem([0:N2-1]*FS/N/1000, MAG(1:N2),'filled');
    axis([-0.1 N2*FS/N/1000 0 1050]);
    title('Análise Espectral');
    xlabel('Frequência (kHz)');
    ylabel('Densidade Espetral Potência');

%     stem([0:N2-1]*FS/N/1000, 10*log10(1+MAG(1:N2)),'filled');
%     axis([0 N2*FS/N/1000 0 35]);
%     title('Análise Espectral');
%     xlabel('Frequência (kHz)');
%     ylabel('Densidade Espetral Potência (dB)');

    pause;
end
