function [c] = spektrum(f)
    N = length(f);
    c = zeros(1,N);
    for n = 0:N-1
        suma = 0;
        for k = 0:N-1
            suma = suma + f(k+1)*complex(cos(-2*pi/N*n*k),sin(-2*pi/N*n*k));
        end
        c(n+1) = suma/N;
    end
end
