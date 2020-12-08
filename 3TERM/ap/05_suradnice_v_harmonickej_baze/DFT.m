f = [83.2600021362 82.9599990845 86.9400024414 85.7300033569 86.2200012207 85.3700027466 85.1600036621 95.9700012207 96.8700027466 94.0 96.9100036621 95.5999984741 98.25 101.419998169 102.800003052 98.0999984741 95.9700012207 99.4199981689 103.480003357 104.75 101.709999084 101.989997864 107.150001526 107.059997559 108.739997864 105.839996338 109.699996948 110.430000305 110.0 112.019996643 ];

f = f(1:20);
N = length(f);
t = 0:N-1;
tt = linspace(0,N-1,N*100);
%vypocet harmonickej bazy

H5 = harmBaza(5);
H4 = harmBaza(4);
H = zeros(N,N);
for i = 1:N
    for j = 1:N
        H(i,j) = complex(cos(2*pi/N*(i-1)*(j-1)), sin(2*pi/N*(i-1)*(j-1)));
    end
end
%vypocet c
c = zeros(1,N);
for n = 0:N-1
    suma = 0;
    for k = 0:N-1
        suma = suma + f(k+1)*complex(cos(-2*pi/N*n*k),sin(-2*pi/N*n*k));
    end
    c(n+1) = suma/N;
end
cp = c;
cp(1) = cp(1)/2;
if mod(N,2) == 0
    cp(N/2+1) = cp(N/2+1)/2;
end
ca = abs(c);
fazove_spektrum = 2*pi/20*(0:19);

y0 = perioda(cp,tt,0,N);
y1 = perioda(cp,tt,5,N);
y2 = perioda(cp,tt,7,N);
y3 = perioda(cp,tt,8,N);
y4 = perioda(cp,tt,2,N);
y5 = perioda(cp,tt,9,N);
y6 = perioda(cp,tt,3,N);
y7 = perioda(cp,tt,4,N);
y8 = perioda(cp,tt,10,N);
y9 = perioda(cp,tt,1,N);
y10 = perioda(cp,tt,6,N);

figure(1);
plot(t, f, 'DisplayName', 'Data')
hold on;
plot(tt, y0, 'DisplayName','konstanta e=' + string(chyba(y0, f)));
plot(tt, y0 + y1, 'DisplayName','perioda(1) e=' + string(chyba(y0 + y1, f)));
plot(tt, y0 + y1 + y2, 'DisplayName','perioda(2) e=' + string(chyba(y0 + y1 + y2, f)));
plot(tt, y0 + y1 + y2 +y3, 'DisplayName','perioda(3) e=' + string(chyba(y0 + y1 + y2 +y3, f)));
plot(tt, y0 + y1 + y2 +y3 + y4, 'DisplayName','perioda(4) e=' + string(chyba(y0 + y1 + y2 +y3 + y4, f)));
legend
hold off;

figure(2)
plot(t, f, 'DisplayName', 'Data')
hold on;
plot(tt, y0 + y1 + y2 +y3 + y4 + y5, 'DisplayName','perioda(5) e=' + string(chyba(y0 + y1 + y2 +y3 + y4 + y5, f)));
plot(tt, y0 + y1 + y2 +y3 + y4 + y5 + y6, 'DisplayName','perioda(6) e=' + string(chyba(y0 + y1 + y2 +y3 + y4 + y5 + y6, f)));
plot(tt, y0 + y1 + y2 +y3 + y4 + y5 + y6 + y7, 'DisplayName','perioda(7) e=' + string(chyba(y0 + y1 + y2 +y3 + y4 + y5 + y6 + y7, f)));
plot(tt, y0 + y1 + y2 +y3 + y4 + y5 + y6 + y7 + y8, 'DisplayName','perioda(8) e=' + string(chyba(y0 + y1 + y2 +y3 + y4 + y5 + y6 + y7 + y8, f)));
legend
hold off;

figure(3)
plot(t, f, 'DisplayName', 'Data')
hold on;
plot(tt, y0 + y1 + y2 +y3 + y4 + y5 + y6 + y7 + y8 + y9, 'DisplayName','perioda(9) e=' + string(chyba(y0 + y1 + y2 +y3 + y4 + y5 + y6 + y7 + y8 + y9, f)));
plot(tt, y0 + y1 + y2 +y3 + y4 + y5 + y6 + y7 + y8 + y9 + y10, 'DisplayName','perioda(10) e=' + string(chyba(y0 + y1 + y2 +y3 + y4 + y5 + y6 + y7 + y8 + y9 + y10, f)));
legend
hold off;

%plot(t,f,tt,y0+y1+y2+y3);
%plot(t,f,tt,y0+y1+y2+y3+y4+y5+y6+y7+y8+y9+y10);

