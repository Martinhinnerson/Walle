import kivy.properties as properties
from kivy.uix.widget import Widget
from kivy.uix.gridlayout import GridLayout
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.textinput import TextInput
from kivy.core.window import Window
from kivy.metrics import sp
from math import floor

MAX_MEMORY_SIZE = 1000 # lines
MINIMUM_VISIBLE_LINES = 8
TEXT_SIZE = "10sp" # This number is given in sp (scale-independet pixels)


class ConsoleWidget(FloatLayout):
    previous_commands = properties.ListProperty([])
    console_label = properties.ObjectProperty(None) # Used to write in
    text_size = properties.NumericProperty(TEXT_SIZE)
    max_memory = properties.NumericProperty(MAX_MEMORY_SIZE)
    max_lines_visible = properties.NumericProperty(MINIMUM_VISIBLE_LINES)
    command_line = properties.StringProperty("[ref=console]" + "Write command here..." + "[/ref]")
    text_input = properties.ObjectProperty()    

    def __init__(self, **kwargs):
        super(ConsoleWidget, self).__init__(**kwargs)
        self.writing_command = False
        self._keyboard = Window.request_keyboard(self._keyboard_closed, self)
        self._keyboard.bind(on_key_down=self._on_keyboard_down)
    
    def command_line_activated(self):
        self.command_line = self.format_string_to_command_line("")
        self.writing_command = True
        print(self.command_line)
        print("Writing command!")

    def format_string_to_command_line(self, string):
        print("New value: " + "[ref=console]" + string + "[/ref]")
        return "[ref=console]" + string + "[/ref]"

    def append_char_to_command_line(self, char):
        line = self.command_line
        line = line.split("[\ref]")
        line[0] += char
        self.command_line = "".join(line)

    def _keyboard_closed(self):
        self._keyboard.unbind(on_key_down=self._on_keyboard_down)
        self._keyboard = None

    def _on_keyboard_down(self, keyboard, keycode, text, modifiers):
        if self.writing_command:
            self.append_char_to_command_line(keycode[1])
