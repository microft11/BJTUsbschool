"""
生成二维码
"""

import qrcode

# 创建QRCode对象
qr = qrcode.QRCode(
    version=5, error_correction=qrcode.constants.ERROR_CORRECT_H, box_size=8, border=4)

# 添加数据
qr.add_data("bjtu ls 21281165, cwx 212512544, zzh ")
qr.make(fit=True)

# 生成二维码图像
img = qr.make_image()
img = img.convert("RGBA")

# 显示图片，可以通过save保存
img.save("myQR.png")
img.show()


# from PIL import Image
# from PIL import Image
# import qrcode
#
# qr = qrcode.QRCode(
#     version=5, error_correction=qrcode.constants.ERROR_CORRECT_H, box_size=8, border=4)
# qr.add_data("组内成员：龙硕 21281165 \n 曹文轩 212512544 \n 赵子皓 ")
# qr.make(fit=True)
#
# img = qr.make_image()
# img = img.convert("RGBA")
#
# icon = Image.open("center.jpg")  # 这里是二维码中心的图片
#
# img_w, img_h = img.size
# factor = 4
# size_w = int(img_w / factor)
# size_h = int(img_h / factor)
#
# icon_w, icon_h = icon.size
# if icon_w > size_w:
#     icon_w = size_w
# if icon_h > size_h:
#     icon_h = size_h
# icon = icon.resize((icon_w, icon_h), Image.ANTIALIAS)
#
# w = int((img_w - icon_w) / 2)
# h = int((img_h - icon_h) / 2)
# icon = icon.convert("RGBA")
# img.paste(icon, (w, h), icon)
# img.show()   # 显示图片,可以通过save保存
