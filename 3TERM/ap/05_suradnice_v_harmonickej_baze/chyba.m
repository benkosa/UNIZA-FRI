function [vysledok] = chyba(vec, f)
    tmp = vec(1 : 100 : end);
    vysledok = sqrt(sum((f-tmp).^2)/length(tmp));
end
