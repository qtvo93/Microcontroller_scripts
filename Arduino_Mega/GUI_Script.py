# -*- coding: utf-8 -*-
"""
Created on Fri Oct 23 01:04:52 2020

@author: Thinh Vo
"""

import serial
import time
import tkinter as tk
import tkinter.font as tkFont
from tkinter import *
from tkinter import messagebox
import matplotlib.pyplot as plt


plt.close('all')
root=tk.Tk()
root.geometry("800x600")
root.title("Motor GUI")
root.configure(bg='grey')

figure1=plt.Figure(figsize=(12,6), dpi=100)

figure1.subplots_adjust(hspace=0.5)
fontStyle = tkFont.Font(family="Lucida Grande", size=14)
var5=StringVar()
label = Label( root, textvariable=var5, font = fontStyle, bg='lightgrey')
label.place(x=100,y=100)

figure1.subplots_adjust(hspace=0.5)
fontStyle = tkFont.Font(family="Lucida Grande", size=14)
var4=StringVar()
label = Label( root, textvariable=var4, font = fontStyle, bg='lightgrey')
label.place(x=100,y=150)

figure1.subplots_adjust(hspace=0.5)
fontStyle = tkFont.Font(family="Lucida Grande", size=14)
var3=StringVar()
label = Label( root, textvariable=var3, font = fontStyle, bg='lightgrey')
label.place(x=100,y=200)

figure1.subplots_adjust(hspace=0.5)
fontStyle = tkFont.Font(family="Lucida Grande", size=14)
var2=StringVar()
label = Label( root, textvariable=var2, font = fontStyle, bg='lightgrey')
label.place(x=100,y=250)


figure1.subplots_adjust(hspace=0.5)
fontStyle = tkFont.Font(family="Lucida Grande", size=14)
var1=StringVar()
label = Label( root, textvariable=var1, font = fontStyle, bg='lightgrey')
label.place(x=100,y=300)


figure1.subplots_adjust(hspace=0.5)
fontStyle = tkFont.Font(family="Lucida Grande", size=14)
var=StringVar()
label = Label( root, textvariable=var, font = fontStyle, bg='lightgrey')
label.place(x=100,y=350)

def startCallBack():
    arduino=serial.Serial('COM7',9600,timeout=5)
    time.sleep(1)
    Dist=[]
    Temp=[]
    Coolant=[]
    Motor=[]
    Headlight=[]
    
    arduino.reset_output_buffer()
    arduino.reset_input_buffer()
    arduino.write(b'1')
    
    for i in range(10001):
        a=(arduino.readline().decode("utf-8"))
        b=(arduino.readline().decode("utf-8"))
        c=(arduino.readline().decode("utf-8"))
        d=(arduino.readline().decode("utf-8"))
        e=(arduino.readline().decode("utf-8"))
        Dist.append(float(a))
        Temp.append(float(b))
        Coolant.append(float(c))
        Motor.append(float(d))
        Headlight.append(float(e))
        
        """Distance"""
        var.set("Distance: {:.2f} cm".format(Dist[-1]))  
        """Distance"""
        
        """Distance LED"""
        if (float (a) <= 10):
            LED = "Red"
        elif (float (a) <= 30):
            LED = "Yellow"
        else:
            LED ="Green"
             
        var1.set("LED Color: {} ".format(LED)) 
        """Distance LED """
        
        """Headlights"""
        if (float(e) == 0):
            var2.set("Headlights: Off".format(Headlight[-1])) 
        elif (float(e) ==150):
            var2.set("Headlights: Dim".format(Headlight[-1])) 
        elif(float(e) ==255):
            var2.set("Headlights: High".format(Headlight[-1])) 
        """Headlights"""
        
        """Motor Speed"""
        var3.set("Motor Speed: {:.2f} ".format(Motor[-1]))
        """Motor Speed"""
        
        """Coolant LEVEL"""
        if (float(c) <= 10):
            var4.set("Coolant Level: {:.2f} - LOW Warning".format(Coolant[-1])) 
        elif (float(c) <=300):
            var4.set("Coolant Level: {:.2f} Medium ".format(Coolant[-1]))
        else:
            var4.set("Coolant Level: {:.2f} High".format(Coolant[-1]))
        """Coolant LEVEL"""
        
        """TEMP ALARM"""
        if (float(b) >= 90):
            var5.set("Alarm: Temperature is over 90 C") 
        else:
            var5.set("Temperature: {:.2f} C".format(Temp[-1]))
        """TEMP ALARM"""
        time.sleep(1)
            
    arduino.close()
    return

start_button = Button(root,text="Start", font=fontStyle, height=2,width=5,command=startCallBack)
start_button.place(x=100,y=450)
root.mainloop()

