function [y] = perioda(cp,tt,n,N)
    y = 2*real(cp(n+1))*cos(2*pi/N*n*tt) - 2*imag(cp(n+1))*sin(2*pi/N*n*tt);
end

