from tkinter import *
from PIL import ImageTk,Image 
root = Tk()
rootHeight = 1080
rootWidth = 960
geoStr = str(rootHeight) + "x" + str(rootWidth)
print(geoStr)
root.geometry(geoStr)

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

# for ()
str = "math: 1,2,3 | 2,3,4 | "
endInd = str.find(':')
name = str[0:endInd]
print(name)
startInd = 0
while ((startInd + 2) >= len(str)):
    startInd = endInd + 2
    endInd = str.find('|') - 1
    print(str[startInd:endInd])
# root.mainloop()