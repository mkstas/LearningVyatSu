from PyQt6.QtWidgets import QWidget, QVBoxLayout
from PyQt6.QtSvgWidgets import QSvgWidget

class Person(QWidget):
    def __init__(self, color="black"):
        super().__init__()
        self.color = color
        self.init_ui()

    def init_ui(self):
        self.svg_widget = QSvgWidget()
        self.update_color(self.color)

        layout = QVBoxLayout()
        layout.addWidget(self.svg_widget)
        self.setLayout(layout)
        self.setMinimumSize(115, 235)

    def update_color(self, new_color):
        self.color = new_color
        svg = f'''
        <svg width="115" height="235" viewBox="0 0 115 235" fill="none" xmlns="http://www.w3.org/2000/svg">
        <defs>
            <clipPath id="clip0">
                <rect width="115" height="235" fill="white"/>
            </clipPath>
            <linearGradient id="hookGradient" x1="0" y1="0" x2="1" y2="1">
                <stop offset="0%" stop-color="#E5E5E5"/>
                <stop offset="50%" stop-color="#AAAAAA"/>
                <stop offset="100%" stop-color="#888888"/>
            </linearGradient>
        </defs>

        <g clip-path="url(#clip0)">
            <path d="M20.0422 6L113.231 209.146" 
                  stroke="#000000" stroke-width="6" stroke-linecap="round"/>
            <path d="M20.0422 6L113.231 209.146" 
                  stroke="#883200" stroke-width="2" stroke-linecap="round"/>

            <path d="M7 233C7 232 7.3 231 7.6 230C10 220 12 210 12 200C12 180 15 160 25 145C35 130 45 127 56 127C67 127 77 130 87 145C97 160 100 180 100 200C100 210 102 220 104.4 230C104.7 231 105 232 105 233H7Z" 
                  fill="{self.color}" 
                  stroke="#000000" 
                  stroke-width="4"/>

            <path d="M55 122C69.3594 122 81 108.569 81 92C81 75.4315 69.3594 62 55 62C40.6406 62 29 75.4315 29 92C29 108.569 40.6406 122 55 122Z" 
                  fill="#FED7AA" 
                  stroke="#000000" 
                  stroke-width="4"/>

            <path d="M56 150C75.8823 150 92 141.046 92 130C92 118.954 75.8823 110 56 110C36.1177 110 20 118.954 20 130C20 141.046 36.1177 150 56 150Z" 
                  fill="{self.color}" 
                  stroke="#000000" 
                  stroke-width="4"/>


            <path d="M30 65C26.6667 71.6667 26 79.3333 28 88C30.6667 94.6667 34 98.6667 38 100C44.6667 101.333 50.6667 101.667 56 101C61.3333 101.667 67.3333 101.333 74 100C78 98.6667 81.3333 94.6667 84 88C86 79.3333 85.3333 71.6667 82 65C74 61.6667 65.3333 60 56 60C46.6667 60 38 61.6667 30 65Z" 
                  fill="#2C1810" 
                  stroke="#000000" 
                  stroke-width="4"/>

            <path d="M34.9999 70C31.6666 75.3333 30.6666 81.3333 31.9999 88" stroke="#000000" stroke-width="4"/>
            <path d="M77 70C80.3333 75.3333 81.3333 81.3333 80 88" stroke="#000000" stroke-width="4"/>
            <path d="M41.9999 68C39.3333 72.6667 38.6666 78 39.9999 84" stroke="#000000" stroke-width="4"/>
            <path d="M70 68C72.6667 72.6667 73.3333 78 72 84" stroke="#000000" stroke-width="4"/>

            <path opacity="0.15" d="M56 243C83.6142 243 106 238.523 106 233C106 227.477 83.6142 223 56 223C28.3858 223 6 227.477 6 233C6 238.523 28.3858 243 56 243Z" 
                  fill="#000000" 
                  stroke="#000000" 
                  stroke-width="4"/>

            <path d="M20.5 6.5C20.5 6.5 22.8967 52.9171 20.5 82.5C17.3054 121.93 1.49997 182 1.49997 182" 
                  stroke="#000000" 
                  stroke-width="4" 
                  stroke-linecap="round" 
                  stroke-dasharray="3,3"/>

            <circle cx="2" cy="181" r="2.5" 
                    fill="url(#hookGradient)" 
                    stroke="#000000" 
                    stroke-width="4"/>
            <path d="M1.5 182 Q 0 183.5, 1.5 185 Q 3 183.5, 1.5 182" 
                  fill="none" 
                  stroke="#000000" 
                  stroke-width="4" 
                  stroke-linecap="round"/>
        </g>
        </svg>
        '''
        self.svg_widget.load(svg.encode('utf-8'))
