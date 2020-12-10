from tkinter import *
from tkinter import font
import math
from PIL import ImageTk,Image 
root = Tk()
rootHeight = 1080
rootWidth = 960
xMargin = 103 # X Distance to top left corner of the first (top left) cell of the graph
yMargin = 90 # X Distance to top left corner of the first (top left) cell of the graph
geoStr = str(rootHeight) + "x" + str(rootWidth)
print(geoStr)
root.geometry(geoStr)

schedArea = Canvas(root,width=rootWidth+125,height=rootHeight,highlightthickness=0,background='white',bd=-2)
schedArea.grid(row=0,column=1,sticky=N+W,columnspan=100, rowspan=200)

basewidth = 850
img = Image.open('schedTemplate.jpg')
wpercent = (basewidth/float(img.size[0]))
hsize = int((float(img.size[1])*float(wpercent)))
img = img.resize((basewidth,hsize+100), Image.ANTIALIAS)
img.save('schedTemplate2.jpg','JPEG')

img2 = ImageTk.PhotoImage(Image.open("schedTemplate2.jpg"))  
schedArea.create_image(20, 20, anchor=NW, image=img2) 
bg = root.cget("background")
myBg = schedArea.create_rectangle(900, 0, 1000, 1080,fill=bg,width=0) # day width = 107 px, hour height = 48 px

def classAdder():
    dNum = 4
    sTime = 16
    eTime = 17.30
    x_0 = 109*(dNum-1) + xMargin + ((dNum-1)*0.17)
    x_1 = x_0 + 109
    sMins = (sTime - math.floor(sTime))*100 # start time minutes
    sHrs = (sMins/60) + math.floor(sTime) # start time hours
    eMins = ((eTime) - math.floor(eTime))*100 # end time minutes
    eHrs = (eMins/60) + math.floor(eTime) # end time hours
    print(eHrs)
    y_0 = 49*(sHrs-6) + yMargin + ((sHrs-6)*0.6)
    y_1 = 49*(eHrs-6) + yMargin + ((eHrs-6)*0.6)
    print(x_0)
    print(y_0)
    print(x_1)
    print(y_1)
    id2 = schedArea.create_rectangle(x_0, y_0, x_1, y_1,fill="blue") # day width = 107 px, hour height = 48 px
    # id2 = schedArea.create_rectangle(758, 586, 867, 635,fill="blue") # day width = 107 px, hour height = 48 px

# id = schedArea.create_rectangle(103, 90, 212, 139,fill="blue")

# for ()

str = "math: 1,2,3 | 2,3,4 | 4,5,6 | "
endInd = str.find(':')
name = str[0:endInd]
endInd = endInd - 1
print(name)
startInd = 0
print(len(str))
while ((endInd + 3) < len(str)):
    startInd = endInd + 3
    endInd = str.find('|',startInd) - 1
    print(str[startInd:endInd])
classAdder()
def backButton():
   print("back")

def forButton():
   print("forward")

myFont = font.Font(family="Helvetica",size=30,weight="bold")
B = Button(root, text = "⮜ ", command = backButton, font = myFont)
B.grid(row=75, column=0, sticky=N+W)
F = Button(root, text = "⮞", command = forButton, font = myFont)
F.grid(row=75, column=90, sticky=N+W)
root.mainloop()
# id = schedArea.create_rectangle(103, 90, 212, 139,fill="blue")
# root.update()
# str= "hellos "
# num = str.find('l',2) # end is where you want to last check plus one
# print(str[0:1])
# print(len(str))
# print(num)

# old (1,1) = (104,211,91,139)
# (1,1) = (103, 90, 212, 139)
# (4,7) = (430, 388, 540, 437)
# (2,15) = (212, 784, 321, 834)
# (7,11) = (758, 586, 867, 635)