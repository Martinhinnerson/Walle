import kivy.properties as properties
from kivy.uix.widget import Widget
from kivy.uix.gridlayout import GridLayout

MAX_MEMORY_SIZE = 1000 # lines

class ConsoleWidget(GridLayout):
    previous_commands = properties.ListProperty([])
    console_label = properties.ObjectProperty(None) # Used to write in
    # command = properties.ObjectProperty()

    def __init__(self, **kwargs):
        self.command_line = "Write command here..."
        super(ConsoleWidget, self).__init__(**kwargs)