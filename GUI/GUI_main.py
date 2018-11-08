import kivy
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.gridlayout import GridLayout
from kivy.vector import Vector
from kivy.clock import Clock
from random import randint
from kivy.uix.button import Button
from os import listdir 
from kivy.properties import ObjectProperty
from kivy.lang import Builder

# Load all .kv files from /kv
kv_path = './kv/'
for kv in listdir(kv_path):
    Builder.load_file(kv_path+kv)


class GUIWidget(GridLayout):
    display = ObjectProperty()
    
    def add_one(self):
        value = int(self.display.text)
        self.display.text = str(value+1)

    def subtract_one(self):
        value = int(self.display.text)
        self.display.text = str(value-1)


class AddButton(Button):
    pass


class SubtractButton(Button):
    pass

class GUIApp(App):
    def build(self):
        self.title = "Dank GUI"
        GUI = GUIWidget()
        return GUI    


if __name__ == "__main__":
    GUIApp().run()  