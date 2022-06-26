# Ecosphere
Ecosphere simulation for course "Data Structure"

## Main Features
- Simulate the ecosphere containing **tiger**, **cow**, and **grass**
- **Zoom in/out** the map
- Map's **grids and axes** can be hidden
- Build-in support of **saving the screenshot** of the ecosphere by choosing "File->Save Image"
- Grass's density is represented by its **transparency**
- Tiger and cow have five kinds of **states**:

    - stray
    - hunt
    - escape
    - alert
    - reproduce

    which can be visualized by toggling the option button in menu bar
- Changing the **initial average density** of grass, and the **number** of cow and tiger, all of which will display the real-time value on the control panel (bottom panel) once the simulation start.
- The **image** representing the three creatures can be changed, and even the background image of the ecospherex

## Source Codes
- Front end:

    Qt (5.12.12)(MinGW 7.3.0 64-bit)
- Back end:

    Pure C++

