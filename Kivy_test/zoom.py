from kivy.modules.console import Console, ConsoleAddon, ConsoleLabel

class ConsoleAddonAbout(ConsoleAddon):
    def init(self):
        self.console.add_panel("About", self.panel_activate,
                               self.panel_deactivate)

    def panel_activate(self):
        self.console.bind(widget=self.update_content)
        self.update_content()

    def panel_deactivate(self):
        self.console.unbind(widget=self.update_content)

    def deactivate(self):
        self.panel_deactivate()

    def update_content(self, *args):
        widget = self.console.widget
        if not widget:
            return
        text = "Selected widget is: {!r}".format(widget)
        lbl = ConsoleLabel(text=text)
        self.console.set_content(lbl)

Console.register_addon(ConsoleAddonAbout)