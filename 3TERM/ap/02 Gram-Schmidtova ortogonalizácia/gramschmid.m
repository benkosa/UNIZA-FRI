%t = linspace(0, 9, 10);
%f = [5 3 4 6 8 5 4 5 3 6];
%b = ones (1,10);

%c = (f * b')/(b*b');

%fp = c * b;


%plot(t, f, '*-', t, fp, 'o-');


%%%%%% uloha %%%%%%

t = [0 1 2 3 4];

u = [1 0 1 0 0];
v = [0 1 1 1 0];
w = [0 0 0 1 1];


b1 = u;


c = (v*b1') / (b1*b1');
b2 = v - c*b1;

c1 = (w*b1') / (b1*b1');
c2 = (w*b2') / (b2*b2');
b3 = w - (c1*b1 + c2*b2);

plot (t, u, '*-', t, v, '*-', t, w, '*-');

plot (t, b1, '*-', t, b2, '*-', t, b3, '*-', 0, -1, 4, 2);



