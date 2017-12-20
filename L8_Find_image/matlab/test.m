[I,map] = imread('result.png','png');
R = I(:,:,1);
G = I(:,:,2);
B = I(:,:,3);
z = fft2(double(R));        % do fourier transform
q = fftshift(z);            % puts u=0,v=0 in the centre
Magq = log(abs(q));         % magnitude spectrum
imagesc(Magq);              % Usually for viewing purposes: 
Phaseq=angle(q);            % phase spectrum
Magq = Magq(1:512, 1:512);

colorbar;
avg = mean(mean(Magq));

resultLast = Magq(1:512, 1:512);
save 'out.txt' '-ascii' resultLast

