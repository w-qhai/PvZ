from PIL import Image
from PIL import ImageSequence

import os
import sys
import glob 

def split_gif(image_name) :
    folder = image_name[ : -4]
    if not os.path.exists(folder):
        os.mkdir(folder)

    gif = Image.open(image_name)
    counter = 0
    max_width = 0
    max_heigth = 0
    for frame in ImageSequence.Iterator(gif) :
    # frame = ImageSequence.Iterator(gif)[1]
        real_img = frame.crop(frame.getbbox())
        width, height = real_img.size
        max_width = max(max_width, width)
        max_heigth = max(max_heigth, height)
        transparent = real_img.getcolors().pop()[1]
        # 图片优化
        l_u_w, l_u_h = 0, 0
        # 左上角
        for l_u_h in range(height) :
            for l_u_w in range(width) :
                dot = (l_u_w, l_u_h)
                if real_img.getpixel(dot) == transparent:
                    break
            else:
                continue
            break
        
        r_d_w, r_d_h = 0, 0
        for r_d_h in range(height - 1, -1, -1) :
            for r_d_w in range(width - 1, -1, -1) :
                dot = (r_d_w, r_d_h)
                if real_img.getpixel(dot) == transparent:
                    break
            else:
                continue
            break

        # 上黑条
        for h in range(l_u_h) :
            for w in range(width) :
                real_img.putpixel((w, h), transparent)
        # 左黑条
        for h in range(height) :
            for w in range(l_u_w) :
                real_img.putpixel((w, h), transparent)

        # 下黑条
        for h in range(r_d_h, height) :
            for w in range(width) :
                real_img.putpixel((w, h), transparent)
        # 右黑条
        for h in range(height) :
            for w in range(r_d_w, width) :
                real_img.putpixel((w, h), transparent)

        real_img.save("{}/{:0>3d}.{}".format(folder, counter, "png"))
        counter += 1
    return max_width, max_heigth, counter

        

def gif_to_png_list(image_name) :
    width, heigth, counter = split_gif(image_name)
    folder = image_name[ : -4]
    if not os.path.exists(folder):
        return
    
    img_list = os.listdir(folder)

    target = Image.new("RGBA", (width * counter, heigth))
    left = 0
    for img_name in img_list:
        img = Image.open(folder + '/' + img_name)
        target.paste(img, (left * width, 0))
        left += 1
        os.remove(folder + '/' + img_name)
    target.save(folder + ".png")
    os.rmdir(folder)

if __name__ == "__main__":
    for argv in sys.argv[1:] :
        for img_name in glob.glob(argv):
            gif_to_png_list(img_name)
            print("{}已转换完成".format(img_name))
