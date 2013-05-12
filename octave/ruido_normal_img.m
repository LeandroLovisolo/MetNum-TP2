function x = ruido_normal_img(n, media, varianza)

x = stdnormal_rnd(n, n);
x = x * varianza + media;