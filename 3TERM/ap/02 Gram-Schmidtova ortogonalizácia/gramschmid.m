%t = linspace(0, 9, 10);
%f = [5 3 4 6 8 5 4 5 3 6];
%b = ones (1,10);

%c = (f * b')/(b*b');

%fp = c * b;


%plot(t, f, '*-', t, fp, 'o-');


%%%%%% uloha %%%%%%

t = [0 1 2 3];

u = [2 0 0 2];
v = [1 1 -1 1];


b1 = u;


c = (v*b1') / (b1*b1');
b2 = v - c*b1;

test = c*b1;

plot (t, u, '*-', t, v, '*-');

plot (t, b1, '*-', t, b2, '*-', 0, -1, 4, 2);



