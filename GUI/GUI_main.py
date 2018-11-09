# Full imports
import kivy
import serial
import os
import struct
import kivy.properties as properties
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

#This is for PySerial
import serial
from kivy.graphics import Color, Ellipse, Line, Rectangle
from kivy.uix.video import Video


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
    map = properties.ObjectProperty(None)

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

    # def readSerial(self, dt):
    #     direction = ser.readline().decode('UTF-8')  #The values read with .readline() is byte literals eg. b'56/r/n' When i decode to UTF-8 i this would print as only 56
    #     return direction
        
        
        

class AddButton(Button):
    increment_value = properties.NumericProperty(0)
    # value = properties.ReferenceListProperty(increment_value)


class SubtractButton(Button):
    decrement_value = properties.NumericProperty(0)
    # value = properties.ReferenceListProperty(decrement_value)


class MapWidget(Widget):
    draw_color = properties.ListProperty()
    background = properties.ListProperty([1, 0, 1])

    def on_touch_down(self, touch):
        if self.inside_widget(touch):
            with self.canvas:
                Color(self.draw_color)
                print(self.draw_color, self.background)
                d = 30.
                Ellipse(pos=(touch.x - d / 2, touch.y - d / 2), size=(d, d))
                touch.ud['line'] = Line(points=(touch.x, touch.y))

    def on_touch_move(self, touch):
        if self.inside_widget(touch):  
            Color(self.draw_color) 
            touch.ud['line'].points += [touch.x, touch.y]


    def on_touch_up(self, touch):      
        if self.inside_widget(touch):
            with self.canvas:
                Color(self.draw_color)
                self.inside_widget(touch)
                d = 30.
                Ellipse(pos=(touch.x - d / 2, touch.y - d / 2), size=(d, d))
    
    def inside_widget(self, touch):
        bottom_left_x = self.center_x - self.width/2
        bottom_left_y = self.center_y - self.height/2
        top_right_x = self.center_x + self.width/2
        top_right_y = self.center_y + self.height/2
        x = touch.pos[0]
        y = touch.pos[1]
        
        return x >= bottom_left_x and x <= top_right_x and y >= bottom_left_y and y <= top_right_y


class StatusBar(GridLayout):
    connection = properties.StringProperty("")
    mission = properties.StringProperty("None")
    speed = properties.NumericProperty(0)
    direction = properties.NumericProperty(0)   

    def get_dir(self):
        return self.direction


class MissionBar(GridLayout):
    current_mission = properties.StringProperty("None")

    def set_mission(self, mission):
        self.current_mission = mission

# #Define serial port
# ser = serial.Serial(port='/dev/cu.usbmodem141401', baudrate=9600, parity=serial.PARITY_NONE,
#                      stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=0)

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