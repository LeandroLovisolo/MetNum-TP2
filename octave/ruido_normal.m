function x = ruido_normal(n, media, varianza)

x = stdnormal_rnd(n, 1);
x = x * varianza + media;