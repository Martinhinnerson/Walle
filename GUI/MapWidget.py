from kivy.uix.widget import Widget
from kivy.graphics import Color, Ellipse, Line, Rectangle, InstructionGroup
import kivy.properties as properties
from pathlib import Path

DATA_FILE = "Data/data_file.txt"

class MapWidget(Widget):
    draw_color = properties.ListProperty([0, 0, 0])
    background = properties.ListProperty([1, 1, 1])
    point_color = properties.ListProperty([0, 0, 0])
    point_size = properties.ListProperty([10, 10])
    draw_from_text_file = properties.BooleanProperty(False)
    dragging_map = properties.BooleanProperty(False)
    translation = properties.ListProperty([0, 0])
    translation_start = properties.ListProperty([0, 0])
    # data_file_path = properties.StringProperty()

    def __init__(self, **kwargs):
        working_dir = Path.cwd()
        self.data_file_path = str(Path(str(working_dir) + "/" + DATA_FILE))
        self.objects = [] # Contains all objects that is drawn on the screen
        # Create empty file
        if not Path.exists(Path(self.data_file_path)):
            open(self.data_file_path, "w")
        super(MapWidget, self).__init__(**kwargs)
        self.bind(pos=self.resize, size=self.resize)

    def resize(self, *args):
        self.pos = self.pos
        self.size = self.size
        self.clear_canvas()

        if self.draw_from_text_file:
            self.draw_from_data_file()

    def on_touch_down(self, touch):
        if self.inside_widget(touch, "touch"):
            self.dragging_map = True
            self.translation_start = [touch.x, touch.y]
            print("Start translation")
            print(self.translation)
            # d = 30.
            # self.obj = InstructionGroup()
            # self.obj.add(Color(*self.draw_color))
            # self.obj.add(Ellipse(pos=(touch.x - d / 2, touch.y - d / 2), size=(d, d)))
            # self.objects.append(self.obj)
            # self.canvas.add(self.obj)
            # with self.canvas:
            #     Color(*self.draw_color)
            #     d = 30.
            #     Ellipse(pos=(touch.x - d / 2, touch.y - d / 2), size=(d, d))
            #     touch.ud['line'] = Line(points=(touch.x, touch.y))

    def on_touch_move(self, touch):
        # print("Touch: %f, %f" % (touch.x - self.center_x, touch.y - self.center_y))
        self.translation[0] = -(self.translation_start[0] - touch.x) # - self.center_x 
        self.translation[1] = -(self.translation_start[1] - touch.y) #- self.center_y
        print(self.translation)
        self.clear_canvas()

        if self.draw_from_text_file:
            self.draw_from_data_file()
        # if self.inside_widget(touch, "touch"):  
        #     Color(*self.draw_color) 
        #     touch.ud['line'].points += [touch.x, touch.y]


    def on_touch_up(self, touch):      
        if self.inside_widget(touch, "touch"):
            if self.dragging_map:
                self.dragging_map = False
                self.translation[0] += -(self.translation_start[0] - touch.x)
                self.translation[1] += -(self.translation_start[1] - touch.y)
                print(self.translation)
                print("End translations")
            # d = 30.
            # self.obj = InstructionGroup()
            # self.obj.add(Color(*self.draw_color))
            # self.obj.add(Ellipse(pos=(touch.x - d / 2, touch.y - d / 2), size=(d, d)))
            # self.objects.append(self.obj)
            # self.canvas.add(self.obj)
            # with self.canvas:
            #     Color(*self.draw_color)
            #     d = 30.
            #     Ellipse(pos=(touch.x - d / 2, touch.y - d / 2), size=(d, d))

    def clear_canvas(self):
        for obj in self.objects:
            self.canvas.remove(obj)

        self.objects.clear()
        # self.canvas.clear()
        # with self.canvas:
        #     Color(*self.background)
        #     Rectangle(pos=self.pos, size=self.size)
    
    def inside_widget(self, touch, type):
        bottom_left_x = self.center_x - self.width/2
        bottom_left_y = self.center_y - self.height/2
        top_right_x = self.center_x + self.width/2
        top_right_y = self.center_y + self.height/2
        if type == "touch":
            x = touch.pos[0]
            y = touch.pos[1]
            return x >= bottom_left_x and x <= top_right_x and y >= bottom_left_y and y <= top_right_y
        elif type == "pos":
            x = touch[0]
            y = touch[1]
            return x >= bottom_left_x and x <= top_right_x and y >= bottom_left_y and y <= top_right_y

    def draw_from_data_file(self):
        if not self.draw_from_text_file:
            self.draw_from_text_file = True

        with open(self.data_file_path, "r") as input_file:
            for line in input_file:
                line = line.rstrip()
                line = line.split(",")
                position = [self.center_x + int(line[0]) + self.translation[0],
                            self.center_y + int(line[1]) + self.translation[1]]

                if self.inside_widget(position, "pos"):
                    self.obj = InstructionGroup()
                    self.obj.add(Color(*self.point_color))
                    self.obj.add(Ellipse(pos=position, size=self.point_size))    
                    self.objects.append(self.obj)
                    self.canvas.add(self.obj)                   
