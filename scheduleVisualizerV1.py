from tkinter import *
from PIL import ImageTk,Image 
root = Tk()
rootHeight = 1080
rootWidth = 960
geoStr = str(rootHeight) + "x" + str(rootWidth)
print(geoStr)
root.geometry(geoStr)

size = 120,120

# for r in range(3):
#    for c in range(4):
#       Label(root, text='R%s/C%s'%(r,c),
#          borderwidth=1 ).grid(row=r,column=c)

def helloCallBack():
   print(root.winfo_width())
   print(root.winfo_height())

# B = Button(root, text ="Hello", command = helloCallBack)
# B.pack()
schedArea = Canvas(root,width=rootWidth+125,height=rootHeight,highlightthickness=0,background='white',bd=-2)
schedArea.grid(row=0,column=0,sticky=N+W)#,columnspan=workArea_width, rowspan=workArea_height)

basewidth = 850
img = Image.open('schedTemplate.jpg')
wpercent = (basewidth/float(img.size[0]))
hsize = int((float(img.size[1])*float(wpercent)))
img = img.resize((basewidth,hsize+100), Image.ANTIALIAS)
img.save('schedTemplate2.jpg','JPEG')

img2 = ImageTk.PhotoImage(Image.open("schedTemplate2.jpg"))  
schedArea.create_image(20,20, anchor=NW, image=img2)  
id = schedArea.create_rectangle(104, 91, 211, 139,fill="blue")
# schedArea.pack()

# for ()

root.mainloop()