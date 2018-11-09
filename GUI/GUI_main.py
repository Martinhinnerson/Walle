import kivy
import kivy.properties as properties
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.gridlayout import GridLayout
from kivy.vector import Vector
from kivy.clock import Clock
from random import randint
from kivy.uix.button import Button
from os import listdir 
from kivy.lang import Builder

#This is for PySerial
import serial

# Load all .kv files from /kv
kv_path = './kv/'
for kv in listdir(kv_path):
    Builder.load_file(kv_path+kv)


class GUIWidget(GridLayout):
    display = properties.ObjectProperty()
    add = properties.ObjectProperty(None)
    subtract = properties.ObjectProperty(None)
    status = properties.ObjectProperty(None)
    mission = properties.ObjectProperty(None)
    
    def add_one(self, increment):
        value = int(self.display.text)
        self.display.text = str(value+increment)

    def subtract_one(self, decrement):
        value = int(self.display.text)
        self.display.text = str(value-decrement)

    def set_button_values(self, increase, decrease):
        self.add.increment_value = increase
        self.subtract.decrement_value = decrease

    def set_status(self, connection, mission, speed, direction):
        self.status.connection = connection
        self.status.mission = mission
        self.status.speed = speed
        self.status.direction = direction

    def update(self, dt):
        speed = randint(0,10) # m/s

        #I CALL THE FUNCTION I MADE HERE, THIS DOESNT WORK
        direction = self.readSerial(1) #randint(0,360) # degree 
        mission = self.mission.current_mission
        self.set_status(self.status.connection, mission, speed, direction)

    #I MADE THIS FUNCTION
    def readSerial(self, dt):
        direction = ser.readline().decode('UTF-8')  #The values read with .readline() is byte literals eg. b'56/r/n' When i decode to UTF-8 i this would print as only 56
        print(direction)
        return direction

class AddButton(Button):
    increment_value = properties.NumericProperty(0)
    # value = properties.ReferenceListProperty(increment_value)


class SubtractButton(Button):
    decrement_value = properties.NumericProperty(0)
    # value = properties.ReferenceListProperty(decrement_value)


class StatusBar(GridLayout):
    connection = properties.StringProperty("")
    mission = properties.StringProperty("None")
    speed = properties.NumericProperty(0)
    direction = properties.StringProperty("") #NumericProperty(0)     # I CHANGED THIS TO StringProperty but still doesn't work


class MissionBar(GridLayout):
    current_mission = properties.StringProperty("None")

    def set_mission(self, mission):
        self.current_mission = mission

#Define serial port
ser = serial.Serial(
    port='/dev/cu.usbmodem141401',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
        timeout=0)

class GUIApp(App):
    def build(self):
        self.title = "Dank GUI"

        GUI = GUIWidget()
        GUI.set_button_values(2,2)
        GUI.set_status("None", "None", 0, 0)
        Clock.schedule_interval(GUI.readSerial, 1.0 / 60.0) # Reads from serial port
        Clock.schedule_interval(GUI.update, 1.0 / 60.0)

        return GUI


if __name__ == "__main__":
    GUIApp().run()  