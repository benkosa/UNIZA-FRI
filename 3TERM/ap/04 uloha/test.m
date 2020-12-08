t = linspace(0, 210, 211);
f = [ 83.6660003662 86.0520019531 88.6019973755 90.3079986572 93.81199646 98.4280014038 96.2679977417 95.6299972534 104.972000122 107.583999634 103.699996948 102.697998047 102.099998474 109.440002441 113.912002563 114.440002441 112.963996887 111.603996277 113.379997253 116.197998047 128.162002563 130.113998413 156.0 177.412002563 146.940002441 149.792007446 149.613998413 154.255996704 154.87600708 153.457992554 160.800003052 160.005996704 171.679992676 183.48399353 179.882003784 180.199996948 166.757995605 159.981994629 155.759994507 135.800003052 133.598007202 148.723999023 149.102005005 149.899993896 144.908004761 140.695999146 121.599998474 129.065994263 126.846000671 112.11000061 109.323997498 89.013999939 86.0400009155 72.2440032959 85.5279998779 85.5059967041 86.858001709 101.0 107.849998474 105.632003784 102.872001648 100.426002502 104.800003052 96.31199646 90.8939971924 96.0019989014 103.248001099 109.089996338 109.767997742 114.599998474 130.190002441 141.977996826 145.966003418 149.042007446 150.777999878 149.272003174 137.343994141 146.42199707 141.12600708 145.029998779 159.75 153.824005127 160.102005005 156.37600708 140.264007568 152.238006592 153.641998291 156.51600647 156.007995605 163.884002686 162.257995605 161.882003784 158.192001343 160.666000366 159.833999634 162.725997925 161.602005005 163.111999512 165.520004272 163.37600708 163.774002075 164.046005249 161.162002563 167.0 179.619995117 176.31199646 176.591995239 172.87600708 177.132003784 189.98399353 188.134002686 205.009994507 194.567993164 187.055999756 198.179992676 196.425994873 198.358001709 200.792007446 200.179992676 198.863998413 200.356002808 192.169998169 197.195999146 191.947998047 201.869995117 215.962005615 223.925994873 241.731994629 274.316009521 277.971984863 273.175994873 278.855987549 308.929992676 299.411987305 303.359985352 309.20199585 300.127990723 300.167999268 328.600006104 313.67199707 318.466003418 302.614013672 283.399993896 307.920013428 295.29800415 299.821990967 297.49798584 286.152008057 297.0 297.399993896 297.003997803 297.915985107 290.541992188 283.713989258 274.877990723 310.95199585 324.200012207 330.141998291 367.127990723 377.417999268 375.705993652 400.365997314 409.996002197 402.839996338 404.667999268 430.634002686 447.75 442.679992676 498.320007324 475.049987793 447.369995117 407.0 418.320007324 330.209991455 366.279998779 371.339996338 372.720001221 419.619995117 449.760009766 441.760009766 423.429992676 442.149993896 449.390014648 424.230010986 380.359985352 387.790008545 407.339996338 421.200012207 419.070007324 429.010009766 448.160003662 415.089996338 425.679992676 413.980010986 425.299987793 425.920013428 434.0 442.299987793 446.649993896 461.299987793 448.880004883 439.670013428 430.829986572 421.940002441 422.640014648 425.790008545 420.630004883 420.279998779 424.679992676 406.019989014 410.829986572 ];

b0 = t.^0;
b1 = t;
b2 = t.^2;
b3 = t.^3;
b4 = t.^4;
b5 = t.^5;
b6 = t.^6;
b7 = t.^7;
b8 = t.^8;

B = [b0; b1; b2; b4; b6; b8];
M = B*B';
d = (f*B.')';
c = M\d;
fp = c(1)*b0 + c(2)*b1 + c(3)*b2 + c(4)*b4 + c(5)*b6 +  c(6)*b8;

sfp = sum((f-fp).^2);

plot(t, f, "-", t, fp, "-")
title("prelozit cez data polynom Q8 s odstranenim troch najmensich koeficientov, uviesť chybu");
legend('data',strcat('polynom, chyba: ', num2str(sfp)),'Location','SouthEast');
