function res = psnr_img(original, con_ruido)

res = psnr(original(:), con_ruido(:));