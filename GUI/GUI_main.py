# Full imports
# import kivy
import serial
import os
import struct
import kivy.properties as properties
import importlib
# Specific imports
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.gridlayout import GridLayout
from kivy.vector import Vector
from kivy.clock import Clock
from random import randint
from kivy.uix.button import Button
from os import listdir 
from kivy.lang import Builder
from kivy.uix.checkbox import CheckBox


#This is for PySerial
import serial

from kivy.graphics import Color, Ellipse, Line, Rectangle
from kivy.uix.video import Video

# Load all .kv files from /kv
kv_path = './kv/'
for kv in listdir(kv_path):
    Builder.load_file(kv_path+kv)

importlib.import_module("StatusBar")
importlib.import_module("MapWidget")
importlib.import_module("ConsoleWidget")


class GUIWidget(GridLayout):
    display = properties.ObjectProperty()
    add = properties.ObjectProperty(None)
    subtract = properties.ObjectProperty(None)
    status = properties.ObjectProperty(None)
    mission = properties.ObjectProperty(None)
    map = properties.ObjectProperty(None)
    draw_checkbox = properties.ObjectProperty(None)
    draw_label = properties.ObjectProperty(None)
    console = properties.ObjectProperty(None)

    #Define serial port
    #ser = serial.Serial(port='/dev/cu.usbmodem141401', baudrate=115200, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=5)

    def get_direction(self):
        return self.status.get_dir()

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

    def clear_canvas(self):
        self.check_box_pressed(self.draw_label.text, False)
        self.draw_checkbox.active = False

    def update(self, dt):
        speed = randint(0,10) # m/s
  
        # dir = self.readSerial(1)
        # try:
        #     # This will make it a float, if the string is not a float it will throw an error
        #     print(dir)
        #     direction = float(dir)
            
        # except ValueError: # this deals will the error
        #     direction = self.get_direction() # if we don't change the value we read the old one

        
        mission = self.mission.current_mission
        direction = self.get_direction()

        self.set_status(self.status.connection, mission, speed, direction)

    def readSerial(self, dt):
        direction = 0#self.ser.readline().decode('UTF-8')  #The values read with .readline() is byte literals eg. b'56/r/n' When i decode to UTF-8 i this would print as only 56
        return direction

    def check_box_pressed(self, id, status):
        if id == "Draw on map":
            if status:
                self.map.draw_from_data_file()
            else:
                self.map.clear_canvas()
        
        
class AddButton(Button):
    increment_value = properties.NumericProperty(0)
    # value = properties.ReferenceListProperty(increment_value)


class SubtractButton(Button):
    decrement_value = properties.NumericProperty(0)
    # value = properties.ReferenceListProperty(decrement_value)


class MissionBar(GridLayout):
    current_mission = properties.StringProperty("None")

    def set_mission(self, mission):
        self.current_mission = mission


class GUIApp(App):
    def build(self):
        self.title = "Dank GUI"

        GUI = GUIWidget()
        GUI.set_button_values(2,2)
        GUI.set_status("None", "None", 0, 0)
        #Clock.schedule_interval(GUI.readSerial, 1.0 / 60.0) # Reads from serial port
        Clock.schedule_interval(GUI.update, 1.0 / 60.0)

        return GUI


if __name__ == "__main__":
    GUIApp().run()  