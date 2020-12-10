t = [0, 1, 2 ,3 ,4, 5, 6];
N = 6;
f = [ 1 2 4 0 3 0];

H = harmBaza(N);

c = spektrum(f);

cp = c;

cp(1) = cp(1)/2;
if mod(N,2) == 0
    cp(N/2+1) = cp(N/2+1)/2;
end

ca = abs(c);
