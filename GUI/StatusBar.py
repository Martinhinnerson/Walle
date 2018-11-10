import kivy.properties as properties
from kivy.uix.gridlayout import GridLayout

class StatusBar(GridLayout):
    connection = properties.StringProperty("")
    mission = properties.StringProperty("None")
    speed = properties.NumericProperty(0)
    direction = properties.NumericProperty(0)   

    def get_dir(self):
        return self.direction