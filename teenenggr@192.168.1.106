
import tkinter as tk
import tkinter.font
from gpiozero import LED
import RPi.GPIO as GPIO
import threading


read = 2
shouldCount = False
win=tk.Tk()
win.configure(bg='white')

win.title("Teenenggr")
win.attributes('-fullscreen',True)
myFont2=tkinter.font.Font(family = "Helvetica", size = 215, weight="bold")
myFont=tkinter.font.Font(family = "Helvetica", size = 12, weight="bold")
c=0


GPIO.setmode(GPIO.BCM)
GPIO.setup(read, GPIO.IN)

def countIncrease():
    global c
    global shouldCount
    if shouldCount:
        shouldCount = False
        c += 1
        labelText.set(str(c))



def exitProgram():
    win.quit()
    GPIO.cleanup() # cleanup all GPIO

def clear():
    global c
    c = 0
    labelText.set(str(c))


labelText = tk.StringVar()
label=tk.Label(win, text='Label', textvariable=labelText, font=myFont2, bg="white", fg="red")
labelText.set(str(c))
label.grid(row=0,sticky=tk.NW)
label.place(relx=0.5, rely=0.5, anchor="center")


button=tk.Button(win,text='CLS', font=myFont, command=clear, bg='bisque2', height=1, width=1)
button.place(relx=0.99, rely=0, anchor="center")

exitB=tk.Button(win,text='X', font=myFont, command=exitProgram, bg='bisque2', height=1, width=1)
exitB.place(relx=0, rely=0, anchor="center")



def check():
    try:
        while 1:
            global shouldCount
            if GPIO.input(read): #High
                shouldCount = True
                print("high")
            else: # Low

                countIncrease()

    except KeyboardInterrupt: # If CTRL+C is pressed, exit cleanly:
        win.quit()
        GPIO.cleanup() # cleanup all GPIO

t1 = threading.Thread(target=check)
t1.start()

tk.mainloop()
