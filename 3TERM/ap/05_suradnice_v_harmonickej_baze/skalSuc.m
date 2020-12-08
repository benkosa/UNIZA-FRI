function [vysledok] = skalSuc(vec1,vec2)
%SKALSUC Summary of this function goes here
%   Detailed explanation goes here
vec2 = complex(real(vec2),-imag(vec2));
vysledok = vec1*vec2';
end
