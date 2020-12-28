function [B] = harmBaza(velkost)
    B = zeros(velkost,velkost);
    for i = 1:velkost
        for j = 1:velkost
            B(i,j) = complex(cos(2*pi/velkost*(i-1)*(j-1)), sin(2*pi/velkost*(i-1)*(j-1)));
        end
    end
end
