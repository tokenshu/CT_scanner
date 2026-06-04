import PySimpleGUI as sg
import serial
import time

INPUT_WIDTH = 20
NAME = "CT set speed"

arduino = serial.Serial(port='COM3', baudrate=115200, timeout=.1)

def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    #time.sleep(0.05)
    #data = arduino.readline()
    return None #data

def main():

    layout_set = [
        [sg.Text('Set speed(RPM):', justification='right')],
        [sg.Input(size=(INPUT_WIDTH, 1), enable_events=True, key='-IN-')],
        [sg.Button("Set", key='set')]
    ]

    window = sg.Window(title = NAME, layout = layout_set, element_justification = 'center', return_keyboard_events=True, margins =(100, 100))
    while True:
        event, values = window.read()
        if event == 'set':
            rpm = values['-IN-']
            write_read(rpm)
            print(rpm)

        if event == sg.WINDOW_CLOSED:
            break

    window.close()

if __name__ == '__main__':
    main()