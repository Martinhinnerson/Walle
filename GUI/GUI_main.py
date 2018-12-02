# Full imports
# import kivy
import serial
import os
import struct
import kivy.properties as properties
import importlib
import threading
import sys
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

    def __init__(self, **kwargs):
        super(GUIWidget, self).__init__(**kwargs)
        #Define serial port
        self.ser = serial.Serial(port="/dev/cu.usbmodem1421", baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=0.1)
        self.serial_data = []
        self.serial_lock = threading.Lock()

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
              
        mission = self.mission.current_mission
        direction = self.get_direction()

        self.set_status(self.status.connection, mission, speed, direction)

    def serial_thread_function(self):
        Clock.schedule_interval(self.readSerial, 1.0 / 60.0)

    def readSerial(self, *args):
        self.serial_lock.acquire()
        try:
            # print("Running")
            if not self.ser.is_open:
                # print("Open serial")
                self.ser.open()
            else:
                # print("Read from serial")
                received_data = self.ser.readline() 
                # print("Finished reading")
                # self.ser.write(b'Hello')

                try:
                    if len(received_data) is not 0:
                        # This will make it a float, if the string is not a float it will throw an error
                        print("Received: %s" % received_data.decode('UTF-8'))

                        self.status_lock.acquire()
                        self.direction = float(received_data.decode('UTF-8'))
                        self.serial_data.append(received_data)
                    
                except ValueError: # this deals will the error
                    print("ValueError")
                    direction = self.get_direction() # if we don't change the value we read the old one
            
            # self.ser.write(b'Read me$')
        finally:
            self.serial_lock.release()

    def check_box_pressed(self, id, status):
        if id == "Draw on map":
            if status:
                self.map.draw_from_data_file()
            else:
                self.map.clear_canvas()
    
    def test_thread(self, *args):
        Clock.schedule_interval(self.test, 1.0 / 1.0)
    
    def test(self, *args):
        self.serial_lock.acquire()
        try:            
            for i in self.serial_data:
                print("Received: %s" % i)
            self.serial_data = []
        finally:
            self.serial_lock.release()
        
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
        # Clock.schedule_interval(GUI.readSerial, 1.0 / 60.0) # Reads from serial port
        try:
            serial_thread = threading.Thread(target=GUI.serial_thread_function, args=GUI.serial_data)
            serial_thread.start()
            # test = threading.Thread(target=GUI.test_thread, args=GUI.serial_data)
            # test.start()
        except (KeyboardInterrupt, SystemExit):
            print("Clean up")
            sys.exit()
        
        Clock.schedule_interval(GUI.update, 1.0 / 60.0)

        return GUI

if __name__ == "__main__":
    GUIApp().run()  