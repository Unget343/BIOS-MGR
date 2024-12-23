import ctypes
from tkinter import *

os_manager = ctypes.CDLL("./os_manager.so")  # For Windows: "./os_manager.dll"

os_manager.get_installed_os.restype = ctypes.c_char_p
os_manager.get_os_status.restype = ctypes.c_char_p

def update_os_list():
    os_listbox.delete(0, END)
    for i in range(3):
        os_name = os_manager.get_installed_os(i).decode()
        os_status = os_manager.get_os_status(os_name.encode()).decode()
        os_listbox.insert(END, f"{os_name} - {os_status}")

def launch_selected_os():
    selected = os_listbox.curselection()
    if selected:
        os_name = os_listbox.get(selected[0]).split(" - ")[0]
        os_manager.launch_os(os_name.encode())

root = Tk()
root.title("BIOS Manager")

title_label = Label(root, text="Installed OS", font=("Arial", 16))
title_label.pack(pady=10)

os_listbox = Listbox(root, width=40, height=10)
os_listbox.pack(pady=10)

update_button = Button(root, text="Update List", command=update_os_list)
update_button.pack(pady=5)

launch_button = Button(root, text="Launch OS", command=launch_selected_os)
launch_button.pack(pady=5)

update_os_list()
root.mainloop()
